#include "MysqlMgr.h"

MysqlMgr::~MysqlMgr()
{
}

int MysqlMgr::RegUser(const std::string& name,const std::string& email, const std::string& password)
{
	return _dao.RegUser(name, email, password);
}

MysqlMgr::MysqlMgr()
{
}