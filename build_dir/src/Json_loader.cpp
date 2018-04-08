
#include <stdexcept>

#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include <boost/foreach.hpp>

#include "Json_loader.hpp"

Json_loader::Json_loader() {
	initialize();
}

Json_loader::Json_loader(std::string file_name) {
	initialize();

	jsonfile = open_json_file(file_name);
}

Json_loader::~Json_loader() {
	destroy();
}

Json_loader &Json_loader::operator = (const Json_loader &json_loader) {
	if(this != &json_loader) {
		this->opened_jsonfile = json_loader.opened_jsonfile;
		this->jsonfile = json_loader.jsonfile;
	}
	return *this;
}

bool Json_loader::operator == (const Json_loader &json_loader) const {
	return (this->jsonfile == json_loader.jsonfile);
}

void Json_loader::load_json_filename(std::string file_name) {
	jsonfile = open_json_file(file_name);
}

template <typename T>
T Json_loader::get_parameter(std::string value_name) {
	if(value_name.size() == 0) {
		throw std::runtime_error("Not found parameter name");
	}
	check_opened_jsonfile();

	if(auto parameter = jsonfile.get_optional<T>(value_name)) {
		return parameter.get();
	}
	else {
		throw std::runtime_error("Parameter value name mismatched");
	}
}

//TODO Low speed algorithm
template <typename T>
std::vector<T> Json_loader::get_parameter_tree(std::string tree_name, std::string value_name) {
	if(tree_name.size() == 0 || value_name.size() == 0) {
		throw std::runtime_error("Not found parameter tree name");
	}
	check_opened_jsonfile();

	std::vector<T> tree_baffer;

	BOOST_FOREACH(const boost::property_tree::ptree::value_type &type, jsonfile.get_child(tree_name.c_str())) {
		const auto &info = type.second;
		
		if(auto parameter_value = info.get_optional<T>(value_name.c_str())) {
			tree_baffer.push_back(parameter_value.get());
		}
		else {
			throw std::runtime_error("Parameter value name mismatched");
		}
	}
	return tree_baffer;
}

boost::property_tree::ptree Json_loader::open_json_file(const std::string &file_name) {
	if(file_name.size() == 0) {
		throw std::runtime_error("Not found json filename");
	}

	boost::property_tree::ptree file;
	if(file_name.size() != 0) {
		read_json(file_name.c_str(), file);

		opened_jsonfile = true;
	}
	else if(file_name.size() == 0) {
		throw std::runtime_error("Set json filename error");
	}

	return file;
}

void Json_loader::check_opened_jsonfile() {
	if(!opened_jsonfile) {
		throw std::runtime_error("Not opened json file");
	}
}

void Json_loader::initialize() {
	opened_jsonfile = false;
}

void Json_loader::destroy() {
}

template int Json_loader::get_parameter<int>(std::string);
template float Json_loader::get_parameter<float>(std::string);
template char Json_loader::get_parameter<char>(std::string);
template std::string Json_loader::get_parameter<std::string>(std::string);

template std::vector<int> Json_loader::get_parameter_tree<int>(std::string, std::string);
template std::vector<float> Json_loader::get_parameter_tree<float>(std::string, std::string);
template std::vector<char> Json_loader::get_parameter_tree<char>(std::string, std::string);
template std::vector<std::string> Json_loader::get_parameter_tree<std::string>(std::string, std::string);

