#include <2018/Day05Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <map>
#include <stack>
#include <algorithm>

namespace TwentyEighteen {

	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("Alchemical Reduction", 2018, 5) {

	}
	Day05Puzzle::~Day05Puzzle() {

	}

	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {

		const std::string polymer(m_InputLines[0]);


		std::map<char, std::stack<char>> shortenedCharStacks;
		std::stack<char> charStack;
		for (std::size_t i = 0; i < polymer.size();++i) {
			const char c = polymer[i];

			if (!charStack.empty() && polymerRemoves(charStack.top(), c)) {
				charStack.pop();
			}
			else {
				charStack.emplace(c);
			}

			const char upperC = toupper(c);
			for (char removedChar = 'A'; removedChar <= 'Z'; ++removedChar) {
				if (c == removedChar || upperC == removedChar) {
					continue;
				}

				std::stack<char>& removedCharStack = shortenedCharStacks[removedChar];
				if (!removedCharStack.empty() && polymerRemoves(removedCharStack.top(), c)) {
					removedCharStack.pop();
				}
				else {
					removedCharStack.emplace(c);
				}
			}
		}

		const auto& minimum = *std::min_element(shortenedCharStacks.begin(), shortenedCharStacks.end(), [](const std::pair<char, std::stack<char>>& _lhs, const std::pair<char, std::stack<char>>& _rhs) -> bool {
			return _lhs.second.size() < _rhs.second.size();
		});

		return { std::to_string(charStack.size()), std::to_string(minimum.second.size()) };
	}

	bool Day05Puzzle::polymerRemoves(char _first, char _second) {
		if (_first == _second) {
			return false;
		}

		return toupper(_first) == toupper(_second);
	}

}
