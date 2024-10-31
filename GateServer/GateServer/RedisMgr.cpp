#include "RedisMgr.h"
#include "ConfigMgr.h"


bool RedisMgr::Get(const std::string& key, std::string& value)
{
	Redis& redis = _redis_pool->GetRedis();
	auto val = redis.get(key); //自动使用连接池

	if (val) {
		//std::cout << "key: " << *val << std::endl;
		value = *val;
		return true;
	}
	else {
		std::cout << "key does not exist" << std::endl;
		return false;
	}
}

RedisMgr::RedisMgr()
{
	ConfigMgr& configMgr = ConfigMgr::Inst();
	std::string host = configMgr["Redis"]["host"];
	std::string port = configMgr["Redis"]["port"];
	std::string password = configMgr["Redis"]["password"];

	// 创建 Redis 对象，使用连接池
	_redis_pool.reset(new RedisConPool(host, atoi(port.c_str()), password));
}

RedisConPool::RedisConPool(const std::string& host, int port, const std::string& password):
	_redis(sw::redis::ConnectionOptions{ ConnectionType::TCP,host, port,"","default" ,password},
		ConnectionPoolOptions{5,std::chrono::milliseconds(100)})
{
}

Redis& RedisConPool::GetRedis()
{
	return _redis;
}
