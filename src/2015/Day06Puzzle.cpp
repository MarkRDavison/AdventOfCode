#include <2015/Day06Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <regex>

namespace TwentyFifteen {
	
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Probably a Fire Hazard", 2015, 6) {

	}
	Day06Puzzle::~Day06Puzzle() {

	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {
		bool *grid = new bool[1000000]();
		int* grid2 = new int[1000000]();

		for (const auto& l : m_InputLines) {
			const LightInstruction instr = parseLine(l);


			for (int y = instr.start.y; y <= instr.end.y; ++y) {
				for (int x = instr.start.x; x <= instr.end.x; ++x) {
					bool& light = grid[static_cast<unsigned>(y) * 1000 + static_cast<unsigned>(x)];
					int& intensity = grid2[static_cast<unsigned>(y) * 1000 + static_cast<unsigned>(x)];

					switch (instr.type) {
					case LightInstruction::Type::TurnOn:
						light = true;
						intensity++;
						break;
					case LightInstruction::Type::TurnOff:
						light = false;
						intensity--;
						if (intensity < 0) {
							intensity = 0;
						}
						break;
					case LightInstruction::Type::Toggle:
						light = !light;
						intensity += 2;
						break;
					}
				}
			}
		}

		unsigned part1Count = 0;
		unsigned part2Count = 0;
		for (unsigned i = 0; i < 1000 * 1000; ++i) {
			part1Count += grid[i] ? 1 : 0;
			part2Count += grid2[i];
		}

		delete[] grid;
		delete[] grid2;

		return { std::to_string(part1Count), std::to_string(part2Count) };
	}
	
	Day06Puzzle::LightInstruction Day06Puzzle::parseLine(const std::string& _line) {
		std::smatch m;
		const std::regex regex("([a-z]+ ?[a-z]+?) ([0-9]+),([0-9]+) through ([0-9]+),([0-9]+)");
		std::regex_match(_line, m, regex);

		LightInstruction instr{};

		instr.start = {
			std::atoi(m[2].str().c_str()),
			std::atoi(m[3].str().c_str())
		};
		instr.end = {
			std::atoi(m[4].str().c_str()),
			std::atoi(m[5].str().c_str())
		};

		if (m[1].str() == "toggle") {
			instr.type = LightInstruction::Type::Toggle;
		}
		else if (m[1].str() == "turn on") {
			instr.type = LightInstruction::Type::TurnOn;
		} 
		else {
			instr.type = LightInstruction::Type::TurnOff;
		}

		return instr;
	}
}
