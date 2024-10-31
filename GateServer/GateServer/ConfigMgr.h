#pragma once
#include "const.h"
struct SectionInfo {
	std::map<std::string, std::string> _sections_datas;
	SectionInfo() {};
	~SectionInfo() {
		_sections_datas.clear();
	}
	SectionInfo(const SectionInfo& ser) {
		_sections_datas = ser._sections_datas;
	}
	SectionInfo& operator = (const SectionInfo& s) {
		if (&s == this) {
			return *this;
		}
		this->_sections_datas = s._sections_datas;
		//return *this;
	}
	std::string operator[](const std::string& key) {
		if (_sections_datas.find(key) == _sections_datas.end()) {
			return "";
		}
		// 这里可以添加一些边界检查  
		return _sections_datas[key];
	}
};
class ConfigMgr
{
public:
	~ConfigMgr() {
		_config_mgr.clear();
	}
	static ConfigMgr& Inst() { //单例模式
		static ConfigMgr cfgMgr; //使得每次使用Inst得到的都是同一个对象
		return cfgMgr;
	}
	SectionInfo operator[](const std::string& section) {
		if (_config_mgr.find(section) != _config_mgr.end()) {
			return _config_mgr[section];
		}
		return SectionInfo();
	}

private:
	ConfigMgr();
	std::map<std::string, SectionInfo> _config_mgr;
	ConfigMgr(const ConfigMgr& src) { //拷贝
		this->_config_mgr = src._config_mgr;
	}
	ConfigMgr& operator = (const ConfigMgr& src) {
		if (this == &src) {
			return *this;
		}
		this->_config_mgr = src._config_mgr;
		return *this;
	}
};

