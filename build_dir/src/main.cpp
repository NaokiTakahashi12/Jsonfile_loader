
#include <iostream>

#include <JsonLoader.hpp>

int main() {
	JsonLoader json("sample.json");

	auto single = json.get_parameter<int>("sample.value");
	auto vector = json.get_parameter_vector<int>("sample.vector");
	auto tree_single = json.get_parameter_tree<int>("sample.tree", "value");
	auto tree_vector = json.get_parameter_tree_vector<int>("sample.tree", "vector");

	std::cout << "value is " << single << std::endl;
	std::cout << std::endl;

	for(auto &&vv : vector) {
		std::cout << "vector is " << vv << std::endl;
	}

	std::cout << std::endl;

	for(auto &&ts : tree_single) {
		std::cout << "tree value is " << ts << std::endl;
	}

	std::cout << std::endl;

	for(auto &&t : tree_vector) {
		for(auto &&v : t) {
			std::cout << "tree vector is " << v << std::endl;
		}
		std::cout << std::endl;
	}
}

