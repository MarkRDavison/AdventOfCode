#include <2018/Day03Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <regex>
#include <tuple>
#include <unordered_set>

namespace TwentyEighteen {

	using ClaimCell = std::pair<int, int>;

	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("No Matter How You Slice It", 2018, 3) {

	}
	Day03Puzzle::~Day03Puzzle() {

	}

	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {
		std::smatch m;
		const std::regex regex("#([0-9]+) @ ([0-9]+),([0-9]+): ([0-9]+)x([0-9]+)");	

		std::size_t collidedClaimCells = 0;
		core::Region<ClaimCell> region;
		std::unordered_set<int> unCollidedClaimIds;

		for (const std::string& _row : m_InputLines) {
			std::regex_match(_row, m, regex);

			const int claimId = std::atoi(m[1].str().c_str());
			const int offsetX = std::atoi(m[2].str().c_str());
			const int offsetY = std::atoi(m[3].str().c_str());
			const int sizeX =   std::atoi(m[4].str().c_str());
			const int sizeY =   std::atoi(m[5].str().c_str());

			bool claimValid = true;
			for (int y = offsetY; y < offsetY + sizeY; ++y) {
				for (int x = offsetX; x < offsetX + sizeX; ++x) {
					ClaimCell& cell = region.getCell(x, y);
					if (cell.second == 0) {
						// We are the first claim for this cell
						cell.first = claimId;
						cell.second = 1;
					}
					else if (cell.second == 1) {
						cell.second++;
						collidedClaimCells++;
						unCollidedClaimIds.erase(cell.first);
						claimValid = false;
					}
				}
			}

			if (claimValid) {
				unCollidedClaimIds.emplace(claimId);
			}
		}

		return { std::to_string(collidedClaimCells), std::to_string(*unCollidedClaimIds.begin()) };
	}

}
