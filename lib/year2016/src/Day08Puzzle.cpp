#include <2016/Day08Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <numeric>
#include <cassert>
#include <queue>

namespace TwentySixteen {
	
	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Two-Factor Authentication", 2016, 8) {

	}
	Day08Puzzle::~Day08Puzzle() {

	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {
		std::string screen;
		const auto part1 = doPart1(m_InputLines, 50, 6, screen);
		std::cout << std::endl;
		for (unsigned y = 0; y < 6; ++y) {
			for (unsigned x = 0; x < 50; ++x) {
				if (x > 0 && x % 5 == 0) {
					std::cout << "\t";
				}
				std::cout << (screen[y * 50 + x] == '#' ? '@' : ' ');
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		return { std::to_string(part1), "See above" };
	}

	void Day08Puzzle::applyInstruction(const std::string& _instruction, unsigned _width, unsigned _height, char* _screen) {
		const auto& s = ze::StringExtensions::splitStringByDelimeter(_instruction, " xy=");
		if (s[0] == "rect") {
			applyRectInstruction(_width, _height, _screen, (unsigned)std::stoi(s[1]), (unsigned)std::stoi(s[2]));
		} else if (s[1] == "row") {
			applyRotateRowInstruction(_width, _height, _screen, (unsigned)std::stoi(s[2]), (unsigned)std::stoi(s[4]));
		} else if (s[1] == "column") {
			applyRotateColumnInstruction(_width, _height, _screen, (unsigned)std::stoi(s[2]), (unsigned)std::stoi(s[4]));
		}
	}

	void Day08Puzzle::applyRectInstruction(unsigned _width, unsigned _height, char* _screen, unsigned _x, unsigned _y) {
		for (unsigned y = 0; y < _y; ++y) {
			for (unsigned x = 0; x < _x; ++x) {
				_screen[y * _width + x] = '#';
			}
		}
	}

	void Day08Puzzle::applyRotateColumnInstruction(unsigned _width, unsigned _height, char* _screen, unsigned _column, unsigned _amount) {

		std::queue<char> previous;
		for (unsigned y = 0; y < _height; ++y) {
			previous.push(_screen[y * _width + _column]);
		}

		for (unsigned i = 0; i < _height; ++i) {
			unsigned y = (i + _amount) % _height; 
			_screen[y * _width + _column] = previous.front();
			previous.pop();
		}

	}

	void Day08Puzzle::applyRotateRowInstruction(unsigned _width, unsigned _height, char* _screen, unsigned _row, unsigned _amount) {

		std::queue<char> previous;
		for (unsigned x = 0; x < _width; ++x) {
			previous.push(_screen[_row * _width + x]);
		}

		for (unsigned i = 0; i < _width; ++i) {
			unsigned x = (i + _amount) % _width;
			_screen[_row * _width + x] = previous.front();
			previous.pop();
		}
	}

	int Day08Puzzle::doPart1(const std::vector<std::string>& _input, unsigned _width, unsigned _height, std::string& _screen) {
		_screen = std::string(_width * _height, '.');

		for (const auto& i : _input) {
			applyInstruction(i, _width, _height, _screen.data());
		}

		return std::accumulate(_screen.begin(), _screen.end(), 0,
			[](int _acc, char _value) -> int {
				return _acc + (_value == '#' ? 1 : 0); 
			});
	}
}
