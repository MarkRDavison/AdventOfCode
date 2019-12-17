#include <2019/Day17Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>

namespace TwentyNineteen {

	struct Cell {
		char value{ ' ' };
		bool intersection{ false };
	};
	
	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("Set and Forget", 2019, 17) {

	}
	Day17Puzzle::~Day17Puzzle() {

	}


	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	void dumpRegion(core::Region<Cell>& _region) {
		for (int y = _region.minY; y <= _region.maxY; ++y) {
			for (int x = _region.minX; x <= _region.maxX; ++x) {
				auto& c = _region.getCell(x, y);
				if (c.intersection) {
					std::cout << 'O';
				} else {
					std::cout << c.value;
				}
			}
			std::cout << std::endl;
		}
	}

	std::vector<IntcodeValue> Day17Puzzle::transform(std::string _input) {
		std::vector<IntcodeValue> r;

		for (char c : _input) {
			r.push_back(c);
		}
		return r;
	}

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {
		IntcodeMachine m{};
		m.loadProgram(m_InputLines[0]);

		core::Region<Cell> region;
		core::Vector2i coord;

		while (!m.hasHaltedFromOpCode()) {
			auto status = m.executeResult();
			if (status == IntcodeMachine::ExecutionResult::Output) {
				IntcodeValue output = m.getOutput();
				if (output == 10) {
					coord.y++;
					coord.x = 0;
				} else {
					auto& c = region.getCell(coord.x, coord.y);
					char v = (char)output;
					c.value = (char)output;

					coord.x++;
				}
			}
		}

		int alignment = 0;
		for (int y = region.minY; y <= region.maxY; ++y) {
			for (int x = region.minX; x <= region.maxX; ++x) {

				if (region.getCell(x, y).value == '#') {
					if (region.getCell(x + 0, y - 1).value == '#' &&
						region.getCell(x + 0, y + 1).value == '#' &&
						region.getCell(x + 1, y + 0).value == '#' &&
						region.getCell(x - 1, y + 0).value == '#') {
						alignment += x * y;
					}
				}
			}
		}
		std::string main = "A,A,B,C,B,C,B,C,B,A\n";
		std::string A = "L,10,L,8,R,8,L,8,R,6\n";
		std::string B = "R,6,R,8,R,8\n";
		std::string C = "R,6,R,6,L,8,L,10\n";
		std::string display = "n\n";

		std::string total = main + A + B + C + display;

		auto mainAscii = transform(main);
		auto aAscii = transform(A);
		auto bAscii = transform(B);
		auto cAscii = transform(C);

		IntcodeValue res = 0;
		{
			IntcodeMachine m1{};
			m1.loadProgram(m_InputLines[0]);
			m1.setValue(2, 0);
			for (auto i : transform(total)) {
				m1.setInput(i);
			}

			while (true) {
				auto stat = m1.executeResult();

				if (stat == IntcodeMachine::ExecutionResult::Output) {
					res = m1.getOutput();
				}
				else {
					break;
				}
			}
		}
		return { std::to_string(alignment), std::to_string(res) };
	}
}
