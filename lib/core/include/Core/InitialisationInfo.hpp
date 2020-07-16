#ifndef INCLUDED_ADVENT_OF_CODE_CORE_INITIALISATION_INFO_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_INITIALISATION_INFO_HPP_

#include <cstdlib>
#include <iostream>
#include <vector>

namespace core {
	
	struct InitialisationInfo {
		int year{ -1 };
		int day{ -1 };
		bool valid{ false };
		std::vector<std::string> parameters;

		static InitialisationInfo parseArguments(int _argc, char **_argv) {

			InitialisationInfo info{};

			if (_argc < 3) {
				std::cout << "Invalid paramters" << std::endl;
				return info;
			}

			for (int i = 3; i < _argc; i++) {
				info.parameters.push_back(_argv[i]);
			}

			info.year = std::atoi(_argv[1]);
			if (info.year >= 2015 && info.year <= 2020) {
				info.valid = true;
			}
			info.day = std::atoi(_argv[2]);
			if (info.day >= 1 && info.day <= 25) {
				info.valid = true;
			}

			return info;
		}
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_INITIALISATION_INFO_HPP_