#include <2019/Day19Puzzle.hpp>
#include <2019/IntcodeMachine.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <cassert>

namespace TwentyNineteen {
	
	Day19Puzzle::Day19Puzzle() :
		core::PuzzleBase("Tractor Beam", 2019, 19) {

	}
	Day19Puzzle::~Day19Puzzle() {

	}


	void Day19Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day19Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	bool getResult(IntcodeMachine& _m, int _x, int _y) {
		_m.resetProgram();
		_m.setInput(_x);
		_m.setInput(_y);

		auto status = _m.executeResult();
		auto output = _m.getOutput();

		return output == 1;
	}

	std::pair<std::string, std::string> Day19Puzzle::fastSolve() {
		core::Region<char> region;
		IntcodeMachine m{};
		m.loadProgram(m_InputLines[0]);

		int part1 = 0;
		for (int x = 0; x < 50; ++x) {
			for (int y = 0; y < 50; ++y) {
				if (getResult(m, x, y)) {
					part1++;
				}
			}
		}

		int x = 500;
		int y = 0;

		const int squareSizeLessOne = 99;

		while (true) {
			if (getResult(m, x, y)) {
				if (getResult(m, x - squareSizeLessOne, y + squareSizeLessOne)) {
					return { std::to_string(part1), std::to_string((x - squareSizeLessOne) * 10000 + y) };
				}
				x++;
			} else {
				y++;
			}
		}
	}
}
