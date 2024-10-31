#pragma once
#include "const.h"
#include <sw/redis++/redis++.h>
using namespace sw::redis;
class RedisConPool {
public:
    RedisConPool(const std::string& host, int port, const std::string& password = "");
    Redis& GetRedis();

private:
    Redis _redis;
};
class RedisMgr : public Singleton<RedisMgr>
{
    friend class Singleton;
public:
    bool Get(const std::string& key, std::string& value);
private:
    RedisMgr();
    std::unique_ptr<RedisConPool> _redis_pool;
    
};
//
