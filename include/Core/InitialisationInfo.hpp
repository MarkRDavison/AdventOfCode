#ifndef INCLUDED_ADVENT_OF_CODE_CORE_INITIALISATION_INFO_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_INITIALISATION_INFO_HPP_

#include <cstdlib>
#include <iostream>
#include <vector>

namespace core {
	
	struct InitialisationInfo {
		int day{ -1 };
		bool valid{ false };
		std::vector<std::string> parameters;

		static InitialisationInfo parseArguments(int _argc, char **_argv) {

			InitialisationInfo info{};

			if (_argc < 2) {
				std::cout << "Invalid paramters" << std::endl;
				return info;
			}

			for (int i = 2; i < _argc; i++) {
				info.parameters.push_back(_argv[i]);
			}

			info.day = std::atoi(_argv[1]);
			if (info.day >= 1 && info.day <= 25) {
				info.valid = true;
			}

			return info;
		}
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_INITIALISATION_INFO_HPP_