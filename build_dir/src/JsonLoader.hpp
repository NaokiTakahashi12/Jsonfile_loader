
#pragma once

#include <vector>
#include <string>

#include <boost/property_tree/ptree.hpp>

class JsonLoader {
	public :
		JsonLoader();
		JsonLoader(const std::string &file_name);

		void load_json_filename(const std::string &file_name);

		template <typename T>
		T get_parameter(const std::string &value_name);

		template <typename T>
		std::vector<T> get_parameter_tree(const std::string &tree_name, const std::string &value_name); 

		template <typename T>
		std::vector<T> get_parameter_vector(const std::string &value_name);

		template <typename T>
		std::vector<std::vector<T>> get_parameter_tree_vector(const std::string &tree_name, const  std::string &value_name);

		JsonLoader &operator = (const JsonLoader &);
		bool operator == (const JsonLoader &) const;

	private :
		bool opened_jsonfile;

		boost::property_tree::ptree jsonfile;

		boost::property_tree::ptree open_json_file(const std::string &file_name);

		void check_opened_jsonfile();

		void initialize();

};

