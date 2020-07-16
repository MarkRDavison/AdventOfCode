#include <Core/StringExtensions.hpp>

#include <sstream>
#include <fstream>
#include <iostream>

namespace core {

	std::string StringExtensions::loadFileToString(const std::string& _path) {
		std::string result;
		std::ifstream input;
		input.open(_path);

		if (!input.good()) {
			std::cout << "Failed to load file: " << _path << std::endl;
			return std::string();
		}

		input.seekg(0, std::ios::end);
		result.reserve(static_cast<unsigned int>(input.tellg()));
		input.seekg(0, std::ios::beg);

		result.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

		return result;
	}

	std::vector<std::string> StringExtensions::splitStringByDelimeter(const std::string& _parameter, const std::string& _delimeter) {
		std::vector<std::string> result;
		std::stringstream stringStream(_parameter);
		std::string line;
		while (std::getline(stringStream, line)) {
			std::size_t prev = 0, pos;
			while ((pos = line.find_first_of(_delimeter, prev)) != std::string::npos) {
				if (pos > prev) {
					result.push_back(line.substr(prev, pos - prev));
				}
				prev = pos + 1;
			}
			if (prev < line.length()) {
				result.push_back(line.substr(prev, std::string::npos));
			}
		}

		return result;
	}
}