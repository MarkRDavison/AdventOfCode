#include <2019/Day08Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <vector>

namespace TwentyNineteen {
	
	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Space Image Forma", 2019, 8) {

	}
	Day08Puzzle::~Day08Puzzle() {

	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {

		const unsigned width = 25;
		const unsigned height = 6;
		const unsigned size = m_InputLines[0].size();
		const unsigned numlayers = size / (width * height);

		unsigned minZero = 999999999;
		unsigned answer = 0;

		for (unsigned i = 0; i < numlayers; ++i) {
			unsigned count_0 = 0;
			unsigned count_1 = 0;
			unsigned count_2 = 0;

			for (char c : m_InputLines[0].substr(i* width* height, width* height)) {
				unsigned number = c - '0';

				if (number == 0) {
					count_0++;
				}
				if (number == 1) {
					count_1++;
				}
				if (number == 2) {
					count_2++;
				}

			}
			if (count_0 < minZero) {
				minZero = count_0;
				answer = count_1 * count_2;
			}
		}

		std::cout << "=========================" << std::endl;
		for (unsigned y = 0; y < height; ++y) {
			for (unsigned x = 0; x < width; ++x) {
				
				for (unsigned i = 0; i < numlayers; ++i) {
					unsigned index = i * height * width + y * width + x;
					char c = m_InputLines[0][index];
					bool black = c == '0';
					bool clear = c == '2';

					if (!clear) {
						std::cout << (black ? ' ' : 'X');
						break;
					}
				}

			}
			std::cout << std::endl;
		}
		std::cout << "=========================" << std::endl;



		return { std::to_string(answer), "Part 2" };
	}
}
