#include <2015/Day06Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Probably a Fire Hazard", 2015, 6) {

	}
	Day06Puzzle::~Day06Puzzle() {

	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {
		constexpr std::size_t size{ 1000 };

		int* grid1 = new int[size * size]{ 0 };
		int* grid2 = new int[size * size]{ 0 };

		for (const auto& l : parseLines(m_InputLines)) {
			applyLinePart1<size>(grid1, l);
			applyLinePart2<size>(grid2, l);
		}

		int part1On = 0;
		int part2On = 0;
		for (auto y = 0; y < size; ++y){
			for (auto x = 0; x < size; ++x) {
				part1On += grid1[y * size + x];
				part2On += grid2[y * size + x];
			}
		}
		delete[]grid1;
		delete[]grid2;

		return { std::to_string(part1On), std::to_string(part2On) };
	}

	std::vector<Day06InputLine> Day06Puzzle::parseLines(const std::vector<std::string>& _input) {
		std::vector<Day06InputLine> parsed;

		for (const auto& i : _input) {
			const auto& strs = ze::StringExtensions::splitStringByDelimeter(i, " ,");

			int x;
			int y;
			int xx;
			int yy;
			Day06InputLine::Action state;
			
			if (strs[0] == "toggle") {
				x = std::stoi(strs[1]);
				y = std::stoi(strs[2]);
				xx = std::stoi(strs[4]);
				yy = std::stoi(strs[5]);
				state = Day06InputLine::Action::Toggle;
			} else {
				x = std::stoi(strs[2]);
				y = std::stoi(strs[3]);
				xx = std::stoi(strs[5]);
				yy = std::stoi(strs[6]);
				if (strs[1] == "on") {
					state = Day06InputLine::Action::On;
				}
				else {
					state = Day06InputLine::Action::Off;
				}
			}

			parsed.emplace_back(ze::IntRect(x, y, xx - x + 1, yy - y + 1), state);
		}

		return parsed;
	}
}
