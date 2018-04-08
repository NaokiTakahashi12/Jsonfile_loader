
#pragma once

#include <vector>
#include <string>

#include <boost/property_tree/ptree.hpp>

class Json_loader {
	public :
		Json_loader();
		Json_loader(std::string file_name);
		virtual ~Json_loader();

		void load_json_filename(std::string file_name);

		template <typename T>
		T get_parameter(std::string value_name);

		template <typename T>
		std::vector<T> get_parameter_tree(std::string tree_name, std::string value_name); 

		Json_loader &operator = (const Json_loader &);
		bool operator == (const Json_loader &) const;

	private :
		bool opened_jsonfile;

		boost::property_tree::ptree jsonfile;

		boost::property_tree::ptree open_json_file(const std::string &file_name);

		void check_opened_jsonfile();

		void initialize(),
			 destroy();

};

