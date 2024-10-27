#include "ConfigMgr.h"
ConfigMgr::ConfigMgr() {
	//get current file path
	boost::filesystem::path currentPath = boost::filesystem::current_path();
	//create complete path of config.ini
	boost::filesystem::path configPath = currentPath / "config.ini";

	//use boost::prosperty_tree
	boost::property_tree::ptree pt;
	boost::property_tree::read_ini(configPath.string(), pt);

	for (const auto& seciton : pt) {
		const std::string sectionName = seciton.first;
		const boost::property_tree::ptree ptChild = seciton.second;
		std::map<std::string, std::string> sectionConfig;
		for (const auto& kv : ptChild) {
			const std::string key = kv.first;
			const std::string value = kv.second.get_value<string>(); //ptree תstring
			sectionConfig[key] = value;
		}

		SectionInfo sectionInfo;
		sectionInfo._sections_datas = sectionConfig;
		this->_config_mgr[sectionName] = sectionInfo;
	}
}