#pragma once
#include "const.h"
#include "MysqlDao.h"
class MysqlMgr :public Singleton<MysqlMgr>
{
	friend class Singleton<MysqlMgr>;
public:
	~MysqlMgr();
	int RegUser(const std::string& name,const std::string& email, const std::string& password);
private:
	MysqlMgr();
	MysqlDao _dao;
};

