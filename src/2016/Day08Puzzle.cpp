#include <2016/Day08Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace {
	struct Cell {
		bool curr{ false };
		bool next{ false };
	};

	using Screen = std::vector<std::vector<Cell>>;
}

namespace TwentySixteen {
	
	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Two-Factor Authentication", 2016, 8) {

	}
	Day08Puzzle::~Day08Puzzle() {

	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void printScreen(const Screen& _screen) {
		std::cout << "==================================================" << std::endl;
		for (unsigned y = 0; y < _screen.size(); ++y) {
			for (unsigned x = 0; x < _screen[y].size(); ++x) {
				std::cout << (_screen[y][x].curr ? '#' : '.');
			}
			std::cout << std::endl;
		}
	}

	void rotateColumn(Screen& _screen, int _index, int _amount) {
		int amount = _amount % _screen.size();

		for (int currentY = 0; currentY < static_cast<int>(_screen.size()); ++currentY) {
			const int fetchY = (currentY - _amount + _screen.size()) % _screen.size();

			_screen[currentY][_index].next = _screen[fetchY][_index].curr;
		}
	}

	void rotateRow(Screen& _screen, int _index, int _amount) {
		int amount = _amount % _screen[_index].size();

		for (int currentX = 0; currentX < static_cast<int>(_screen[_index].size()); ++currentX) {
			const int fetchX = (currentX - _amount + _screen[_index].size()) % _screen[_index].size();

			_screen[_index][currentX].next = _screen[_index][fetchX].curr;
		}
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {

		Screen screen;
		for (unsigned y = 0; y < m_Height; ++y) {
			screen.emplace_back();
			for (unsigned x = 0; x < m_Width; ++x) {
				screen.back().emplace_back();
			}
		}

		for (const std::string& instruction : m_InputLines) {
			const auto& parts = core::StringExtensions::splitStringByDelimeter(instruction, " ");
			if (parts[0] == "rect") {
				// New rect
				const auto& size = core::StringExtensions::splitStringByDelimeter(parts[1], "x");
				const unsigned x = static_cast<unsigned>(std::atoi(size[0].c_str()));
				const unsigned y = static_cast<unsigned>(std::atoi(size[1].c_str()));

				for (unsigned j = 0; j < y; ++j) {
					for (unsigned i = 0; i < x; ++i) {
						screen[j][i].next = true;
					}
				}
			} else {
				bool rotateX = parts[2][0] == 'x';
				const int columnOrRowIndex = std::atoi(parts[2].substr(2).c_str());
				const int amount = std::atoi(parts[4].c_str());

				if (rotateX) {
					rotateColumn(screen, columnOrRowIndex, amount);
				} else {
					rotateRow(screen, columnOrRowIndex, amount);
				}
			}

			for (unsigned y = 0; y < m_Height; ++y) {
				for (unsigned x = 0; x < m_Width; ++x) {
					Cell& c = screen[y][x];
					c.curr = c.next;
				}
			}

			if (getVerbose()) {
				printScreen(screen);
			}
		}

		int countLit = 0;
		for (unsigned y = 0; y < m_Height; ++y) {
			for (unsigned x = 0; x < m_Width; ++x) {
				if (screen[y][x].curr) {
					countLit++;
				}
			}
		}

		printScreen(screen);

		return { std::to_string(countLit), "See print output." };
	}
}
