#include <2018/Day23Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <SFML/System/Vector3.hpp>
#include <regex>

namespace TwentyEighteen {

	Day23Puzzle::Day23Puzzle()  :
		core::PuzzleBase("Experimental Emergency Teleportation", 2018, 23) {
		
	}
	Day23Puzzle::~Day23Puzzle() {
		
	}

	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}
	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {

		if (getVerbose()) {
			std::cout << "+++++  Solving Day 23 +++++" << std::endl;
		}
		// Parsing
		std::smatch m;
		const std::regex regex("pos=<(-?[0-9]+),(-?[0-9]+),(-?[0-9]+)>, r=(-?[0-9]+)");

		std::vector<Nanobot> nanoBots;
		for (const std::string& _row : m_InputLines) {
			std::regex_match(_row, m, regex);
			nanoBots.emplace_back(std::atoi(m[1].str().c_str()), std::atoi(m[2].str().c_str()), std::atoi(m[3].str().c_str()), std::atoi(m[4].str().c_str()));
		}

		// Part 1
		std::sort(nanoBots.begin(), nanoBots.end(), [](const Nanobot& _lhs, const Nanobot& _rhs) -> bool {
			return _lhs.r > _rhs.r;
		});
		
		NanobotNumber Part1Answer = 0;

		const Nanobot& best = nanoBots.front();
		for (std::size_t i = 0; i < nanoBots.size(); ++i) {
			const Nanobot& current = nanoBots[i];
			const NanobotNumber ManhattenDistance = 
				std::abs(std::max(best.x, current.x) - std::min(best.x, current.x)) + 
				std::abs(std::max(best.y, current.y) - std::min(best.y, current.y)) + 
				std::abs(std::max(best.z, current.z) - std::min(best.z, current.z));
			
			if (ManhattenDistance <= best.r) {
				Part1Answer++;
			}
		}

		// Part 2

		NanobotNumber minX = (*std::min_element(nanoBots.begin(), nanoBots.end(),
		    [](const Nanobot& _lhs, const Nanobot& _rhs) -> bool {
		    return _lhs.x < _rhs.x;
		})).x;
		NanobotNumber maxX = (*std::max_element(nanoBots.begin(), nanoBots.end(),
		    [](const Nanobot& _lhs, const Nanobot& _rhs) -> bool {
		    return _lhs.x < _rhs.x;
	    })).x;
		NanobotNumber minY = (*std::min_element(nanoBots.begin(), nanoBots.end(),
		    [](const Nanobot& _lhs, const Nanobot& _rhs) -> bool {
		    return _lhs.y < _rhs.y;
	    })).x;
		NanobotNumber maxY = (*std::max_element(nanoBots.begin(), nanoBots.end(),
		    [](const Nanobot& _lhs, const Nanobot& _rhs) -> bool {
		    return _lhs.y < _rhs.y;
	    })).x;
		NanobotNumber minZ = (*std::min_element(nanoBots.begin(), nanoBots.end(),
		    [](const Nanobot& _lhs, const Nanobot& _rhs) -> bool {
		    return _lhs.z < _rhs.z;
	    })).x;
		NanobotNumber maxZ = (*std::max_element(nanoBots.begin(), nanoBots.end(),
		    [](const Nanobot& _lhs, const Nanobot& _rhs) -> bool {
		    return _lhs.z < _rhs.z;
	    })).x;

		NanobotNumber Part2Answer = std::numeric_limits<NanobotNumber>::max();

		NanobotNumber inspectionDistance = getPowerOf2GreaterThan(maxX - minX);
		sf::Vector3<NanobotNumber> bestCoordinate = {};


		while (true) {
			NanobotNumber maximumDronesInRangeOfCoordinate = 0; 
			bestCoordinate = {};
			if (getVerbose()) {
				std::cout << "====================================" << std::endl;
				std::cout << "Inspection distance: " << inspectionDistance << ", ranges x " 
				<< minX << "," << maxX << " (Size " << std::abs(maxX - minX) << ") y " 
				<< minY << "," << maxY << " (Size " << std::abs(maxY - minY) << ") z "
				<< minZ << "," << maxZ << " (Size " << std::abs(maxZ - minZ) << ")" << std::endl;
			}

			// This will find the corner that is the best 
			for (NanobotNumber x = minX; x <= maxX; x += inspectionDistance) {
				for (NanobotNumber y = minY; y <= maxY; y += inspectionDistance) {
					for (NanobotNumber z = minZ; z <= maxZ; z += inspectionDistance) {
						NanobotNumber dronesInRangeFuzzy = 0;
						for (const Nanobot& bot : nanoBots) {
							const NanobotNumber manhattenDistance = std::abs(x - bot.x) + std::abs(y - bot.y) + std::abs(z - bot.z);
							const NanobotNumber difference = manhattenDistance - bot.r;
							const NanobotNumber isValid = difference / inspectionDistance;
							if (isValid <= 0) {
								// Within range of coordinate within margin of error with current inspection distance
								dronesInRangeFuzzy++;
							}
						}
						const NanobotNumber currentManhattenToOrigin = std::abs(x) + std::abs(y) + std::abs(z);
						if (dronesInRangeFuzzy > maximumDronesInRangeOfCoordinate) {
							maximumDronesInRangeOfCoordinate = dronesInRangeFuzzy;
							Part2Answer = currentManhattenToOrigin;
							bestCoordinate = { x,y,z };
						} else if (dronesInRangeFuzzy == maximumDronesInRangeOfCoordinate) {
							if (Part2Answer > currentManhattenToOrigin) {
								Part2Answer = currentManhattenToOrigin;
								bestCoordinate = { x,y,z };
							}
						}
					}
				}
			}

			if (inspectionDistance == 1) {
				// We inspected one coordinate at a time, this answer is the answer
				break;
			}

			if (getVerbose()) {
				std::cout << "Best coordinate " << bestCoordinate.x << ", " << bestCoordinate.y << ", " << bestCoordinate.z << std::endl;
			}

			inspectionDistance = inspectionDistance / 2;

			minX = bestCoordinate.x - inspectionDistance;
			maxX = bestCoordinate.x + inspectionDistance;
			minY = bestCoordinate.y - inspectionDistance;
			maxY = bestCoordinate.y + inspectionDistance;
			minZ = bestCoordinate.z - inspectionDistance;
			maxZ = bestCoordinate.z + inspectionDistance;
		}


		if (getVerbose()) {
			std::cout << "Final best coordinate " << bestCoordinate.x << ", " << bestCoordinate.y << ", " << bestCoordinate.z << std::endl;
		}

		return { std::to_string(Part1Answer), std::to_string(Part2Answer) };
	}

	NanobotNumber Day23Puzzle::getPowerOf2GreaterThan(NanobotNumber _number) {
		NanobotNumber po2 = 1;
		while (po2 <= _number) {
			po2 *= 2;
		}
		return po2;
	}

}
