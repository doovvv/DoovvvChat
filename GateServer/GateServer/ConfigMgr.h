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
		// �����������һЩ�߽���  
		return _sections_datas[key];
	}
};
class ConfigMgr
{
public:
	ConfigMgr();
	~ConfigMgr() {
		_config_mgr.clear();
	}
	SectionInfo operator[](const std::string& section) {
		if (_config_mgr.find(section) != _config_mgr.end()) {
			return _config_mgr[section];
		}
		return SectionInfo();
	}
	ConfigMgr(const ConfigMgr& src){ //����
		this->_config_mgr = src._config_mgr;
	} 
	ConfigMgr& operator = (const ConfigMgr& src) {
		if (this == &src) {
			return *this;
		}
		this->_config_mgr = src._config_mgr;
		return *this;
	}
private:
	std::map<std::string, SectionInfo> _config_mgr;
};
