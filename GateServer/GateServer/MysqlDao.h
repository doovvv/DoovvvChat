#pragma once
#include "const.h"
#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/exception.h>
#include <mysql/jdbc.h>
#include <thread>
#include <queue>
#include <vector>
class SqlConnection {
public:
	SqlConnection(sql::Connection* con, int64_t lasttime) :_con(con) , _last_oper_time(lasttime) {

	}
	std::unique_ptr<sql::Connection> _con;
	int64_t _last_oper_time;
};
class MysqlPool
{
public:
	MysqlPool(std::string url, std::string user, std::string password, std::string schema, int poolsize);
	std::unique_ptr < SqlConnection > GetConnection(); //从连接池中得到一个连接
	void ReturnConnection(std::unique_ptr<SqlConnection> con);
	~MysqlPool();
private:
	std::string _url;
	std::string _user;
	std::string _password;
	std::string _schema;//数据库名称
	int _pool_size;
	std::vector<std::unique_ptr<SqlConnection>> _pool;
	std::condition_variable _cond;
	std::thread _check_thread; //同来检测
	std::atomic<bool> _stop;
	std::mutex _mutex;
	void CheckConnection();
	void Close();
};
class MysqlDao {
public:
	MysqlDao();
	~MysqlDao();
	int RegUser(const std::string& name, const std::string& email, const std::string& password);
private:
	std::unique_ptr<MysqlPool> _pool;
};
