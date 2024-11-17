#include "MysqlDao.h"
#include <chrono>
#include "ConfigMgr.h"
struct UserInfo {
	std::string name;
	std::string email;
	std::string password;
};
MysqlPool::MysqlPool(std::string url, std::string user, std::string password, 
	std::string schema, int poolsize) :
	_url(url), _user(user), _password(password), _schema(schema), _pool_size(poolsize), _stop(false) {
	try
	{
		for (int i =  0;i < _pool_size;i++) {
			sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
			auto* con = driver->connect(_url, _user, _password);
			con->setSchema(_schema);
			//当前时间戳
			auto now = std::chrono::system_clock::now();
			std::time_t timestamp = std::chrono::system_clock::to_time_t(now);
			_pool.push_back(std::make_unique<SqlConnection>(con, timestamp));
		}
		_check_thread = std::thread([this] {
			CheckConnection();
			std::this_thread::sleep_for(std::chrono::seconds(60)); //每一分钟检查一次连接，防止mysql连接中断
			});
		_check_thread.detach();//分离出主线程，交由操作系统管理.
	}
	catch (const std::exception& e)
	{
		std::cout << "mysql init error: " << e.what()<<"  current url: "<<_url << std::endl;
	}
}

std::unique_ptr<SqlConnection> MysqlPool::GetConnection()
{
	std::unique_lock<std::mutex> lock(_mutex);
	_cond.wait(lock, [this] {
		if (_stop) {
			return true;
		}
		return !_pool.empty();
		});
	if (_stop) {
		return nullptr;
	}
	std::unique_ptr<SqlConnection> con(std::move(_pool.back()));
	_pool.pop_back();
	return con;
}

void MysqlPool::ReturnConnection(std::unique_ptr<SqlConnection> con)
{
	std::unique_lock<std::mutex> lock(_mutex);
	if (_stop) {
		return;
	}
	_pool.push_back(std::move(con));
	_cond.notify_one();
	return;
}

MysqlPool::~MysqlPool()
{
	std::unique_lock<std::mutex> lock(_mutex);
	Close();
	while (!_pool.empty()) {
		_pool.pop_back();
	}
}

void MysqlPool::CheckConnection()
{
	std::lock_guard<std::mutex> lock(_mutex);
	//当前时间戳
	auto now = std::chrono::system_clock::now();
	std::time_t timestamp = std::chrono::system_clock::to_time_t(now);
	for (int i = 0;i < _pool.size();i++) {
		std::unique_ptr<SqlConnection> con = std::move(_pool[i]);
		Defer defer([this, &con, i] {
			_pool[i] = std::move(con);
			});
		if (timestamp - con->_last_oper_time < 600) { //超过十分钟没进行操作，则需要操作一下
			continue;
		}
		try
		{
			std::unique_ptr<sql::Statement> stmt(con->_con->createStatement());//执行具体 SQL 语句的关键接口之一
			stmt->executeQuery("select 1");
			con->_last_oper_time = timestamp;
			std::cout << "execute timer alive query, now timesatmp is: " << timestamp << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Error keep mysql connection alive: " << e.what() << std::endl;
			//重新创建连接
			sql::mysql::MySQL_Driver* driver = sql::mysql::get_driver_instance();
			auto* newcon = driver->connect(_url, _user, _password);
			newcon->setSchema(_schema);
			con->_con.reset(newcon);
			con->_last_oper_time = timestamp;


		}
	}

}

void MysqlPool::Close()
{
	_stop = true;
	_cond.notify_all();
}

MysqlDao::MysqlDao()
{
	auto& configMgr = ConfigMgr::Inst();
	const auto& host = configMgr["Mysql"]["host"];
	const auto& port = configMgr["Mysql"]["port"];
	const auto& pwd = configMgr["Mysql"]["password"];
	const auto& schema = configMgr["Mysql"]["schema"];
	const auto& user = configMgr["Mysql"]["user"];
	_pool.reset(new MysqlPool(host + ":" + port, user, pwd, schema, 5));
}

MysqlDao::~MysqlDao()
{
	_pool->~MysqlPool();
}

int MysqlDao::RegUser(const std::string& name, const std::string& email, const std::string& password)
{
	try
	{
		auto con = _pool->GetConnection();
		if (con == nullptr) {
			std::cout << "no mysql connection" << std::endl;
			return 0;
		}
		std::cout << password << std::endl;
		std::unique_ptr<sql::PreparedStatement> stmt(con->_con->prepareStatement("CALL reg_user(?,?,?,@result)"));
		stmt->setString(1,name);
		stmt->setString(2, email);
		stmt->setString(3, password);

		stmt->execute();
		unique_ptr<sql::Statement> stmtResult(con->_con->createStatement());
		unique_ptr<sql::ResultSet> res(stmtResult->executeQuery("SELECT @result AS result"));
		if (res->next()) {
			int result = res->getInt("result");
			std::cout << "Result: " << result << std::endl;
			_pool->ReturnConnection(std::move(con));
			return result;
		}
		_pool->ReturnConnection(std::move(con));
		return -1;
	}
	catch (const std::exception& e)
	{
		std::cout << "mysql execute error: " << e.what() << std::endl;
		return -1;

	}
}
