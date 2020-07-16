#include <2018/Day17Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <zeno/Core/Vector2.hpp>
#include <queue>

#define CLAY '#'
#define SAND ' '
#define SOURCE '+'
#define SETTLED '~'
#define FLOW '|'

#define IS_EMPTY(s) (s == SAND || s == 0)
#define IS_SOLID(s) (s == CLAY || s == SETTLED)
#define IS_CLAY(s) (s == CLAY)

namespace TwentyEighteen {
	
	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("Reservoir Research", 2018, 17) {

	}
	Day17Puzzle::~Day17Puzzle() {

	}


	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void dumpMap(core::Region<char>& _map) {
		std::cout << "=======================" << std::endl;
		for (int y = _map.minY; y <= _map.maxY; ++y) {
			for (int x = _map.minX; x <= _map.maxX; ++x) {
				std::cout << _map.getCell(x, y);
			}
			std::cout << std::endl;
		}
	}

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {
		core::Region<char> map;

		map.getCell(500, 0) = SOURCE;
		map.minX = 500;
		map.maxX = 500;
		populateMap(map, parseInput(m_InputLines));
		std::queue<ze::Vector2i> locations;
		locations.push({ 500, 0 });

		dumpMap(map);

		while (!locations.empty()) {
			//int v = getchar();

			ze::Vector2i loc = locations.front();locations.pop();
			auto& below = map.getCell(loc.x, loc.y + 1);
			if (IS_EMPTY(below)) {
				locations.push({ loc.x, loc.y + 1 });
				below = FLOW;
			}
			else if (IS_SOLID(below)) {
				bool containedLeft = false;
				bool containedRight = false;
				int minX = loc.x;
				int maxX = loc.x;

				for (int x = minX;; --x) {
					if (IS_CLAY(map.getCell(x - 1, loc.y))) {
						break;
					}
					if (IS_CLAY(map.getCell(x - 1, loc.y + 1))) {
						break;
					}
					minX--;
				}
				for (int x = maxX;; ++x) {
					if (IS_CLAY(map.getCell(x + 1, loc.y))) {
						break;
					}
					if (IS_CLAY(map.getCell(x + 1, loc.y + 1))) {
						break;
					}
					maxX++;
				}
				std::cout << "On level " << loc.y << " goes from " << minX << " to " << maxX << std::endl;
			}


			dumpMap(map);
		}


		return { "Part 1", "Part 2" };
	}

	std::vector<Day17Puzzle::ParsedClayVein> Day17Puzzle::parseInput(const std::vector<std::string>& _input) {
		std::vector<Day17Puzzle::ParsedClayVein> parsed;

		for (const auto& line : _input) {
			const auto& parts = ze::StringExtensions::splitStringByDelimeter(line, "=,.");
			auto c1 = std::stoi(parts[1]);
			auto c2_s = std::stoi(parts[3]);
			auto c2_e = std::stoi(parts[4]);

			auto& pcv = parsed.emplace_back();
			if (parts[0] == "x") {
				pcv.minX = c1;
				pcv.maxX = c1;
				pcv.minY = c2_s;
				pcv.maxY = c2_e;
			}
			else {
				pcv.minY = c1;
				pcv.maxY = c1;
				pcv.minX = c2_s;
				pcv.maxX = c2_e;
			}
		}

		return parsed;
	}
	void Day17Puzzle::populateMap(core::Region<char>& _map, const std::vector<ParsedClayVein>& _parsedInput) {
		for (const auto& pcv : _parsedInput) {
			for (int y = pcv.minY; y <= pcv.maxY; ++y){
				for (int x = pcv.minX; x <= pcv.maxX; ++x) {
					_map.getCell(x, y) = CLAY;
				}
			}
		}
	}
}
