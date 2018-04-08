
#include <stdexcept>
#include <iostream>
#include <string>
#include <chrono>

#include "Json_loader.hpp"

int main(int argc, char *argv[]) {
	using namespace std;

	std::string jsonfile_name;

	auto start_p = chrono::high_resolution_clock::now();

	if(argc == 2) {
		jsonfile_name = argv[1];
	}
	else {
		jsonfile_name = "Default.json";
	}

	try {
		Json_loader jl;
		jl.load_json_filename(jsonfile_name);
		cout << jl.get_parameter<string>("Default.Sample") << endl;
		cout << jl.get_parameter<int>("Default.Value") << endl;
		cout << jl.get_parameter<float>("Default.Value") << endl;
	}
	catch(const std::exception error) {
		cerr << error.what() << endl;
	}

	auto end_p = chrono::high_resolution_clock::now();
	auto interval_time = chrono::duration<double, ratio<1, 1000>>(end_p - start_p).count();

	cout << "Loss time is " << interval_time << "[msec]" << endl;

	return 0;
}
