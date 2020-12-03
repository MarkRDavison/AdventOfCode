#include <2020/Day03Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace TwentyTwenty {
	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2020, 3) {
	}


	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	long long Day03Puzzle::getTreesForSlope(unsigned _x, unsigned _y) const {
		const unsigned width = m_InputLines[0].size();
		const unsigned height = m_InputLines.size();

		long long trees = 0;
		unsigned currentX = 0;
		for (unsigned yy = 0; yy < height; yy += _y) {
			const unsigned xMod = currentX % width;

			if (m_InputLines[yy][xMod] == '#') {
				trees++;
			}

			currentX += _x;
		}

		return trees;
	}

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {
		long long trees1 = 
			getTreesForSlope(3, 1);

		long long trees2 =
			getTreesForSlope(1, 1) *
			getTreesForSlope(3, 1) *
			getTreesForSlope(5, 1) *
			getTreesForSlope(7, 1) *
			getTreesForSlope(1, 2);

		return { std::to_string(trees1), std::to_string(trees2) };
	}
}
