#include <2016/Day11Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <unordered_map>

namespace TwentySixteen {
	
	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Radioisotope Thermoelectric Generators", 2016, 11) {

	}
	Day11Puzzle::~Day11Puzzle() {

	}


	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::string Day11Puzzle::FacilityState::str() const {
		std::string s;

		s += std::to_string(elevator);

		for (auto f : deviceFloors) {
			s += std::to_string(f.first);
			s += std::to_string(f.second);
		}

		return s;
	}
	std::vector<Day11Puzzle::FacilityState> Day11Puzzle::FacilityState::enumerate(const Day11Puzzle::FacilityStateInfo& _info) const {
		std::vector<Day11Puzzle::FacilityState> next;

		static const auto sortDevices = [](const std::pair<int, int>& _lhs, const std::pair<int, int>& _rhs)->bool {
			if (_lhs.first != _rhs.first) {
				return _lhs.first < _rhs.first;
			}

			return _lhs.second < _rhs.second;
		};

		// Move up
		if (elevator < 4) {
			for (unsigned i = 0; i < this->deviceFloors.size() * 2; ++i) {
				auto iFloorPair = this->deviceFloors[i / 2];
				auto iFloor = (i % 2 == 0)
					? iFloorPair.first
					: iFloorPair.second;
				if (iFloor != this->elevator) { continue; } // Device is not on current floor
				for (unsigned j = 0; j < this->deviceFloors.size() * 2; ++j) {
					auto jFloorPajr = this->deviceFloors[j / 2];
					auto jFloor = (j % 2 == 0)
						? jFloorPajr.first
						: jFloorPajr.second;
					if (jFloor != this->elevator) { continue; } // Device is not on current floor
					
					FacilityState state_inner(*this);
					state_inner.elevator++;
					auto& iii = (i % 2 == 0)
						? state_inner.deviceFloors[i / 2].first
						: state_inner.deviceFloors[i / 2].second;
					iii++;
					if (i != j) {
						auto& jjj = (j % 2 == 0)
							? state_inner.deviceFloors[j / 2].first
							: state_inner.deviceFloors[j / 2].second;
						jjj++;
					}
					if (state_inner.valid(_info)) {
						std::sort(
							state_inner.deviceFloors.begin(),
							state_inner.deviceFloors.end(),
							sortDevices);
						next.push_back(state_inner);
					}
				}
			}
		}

		// Move down
		if (elevator > 1) {
			for (unsigned i = 0; i < this->deviceFloors.size() * 2; ++i) {
				auto iFloorPair = this->deviceFloors[i / 2];
				auto iFloor = (i % 2 == 0)
					? iFloorPair.first
					: iFloorPair.second;
				if (iFloor != this->elevator) { continue; } // Device is not on current floor
				for (unsigned j = 0; j < this->deviceFloors.size() * 2; ++j) {
					auto jFloorPajr = this->deviceFloors[j / 2];
					auto jFloor = (j % 2 == 0)
						? jFloorPajr.first
						: jFloorPajr.second;
					if (jFloor != this->elevator) { continue; } // Device is not on current floor

					FacilityState state_inner(*this);
					state_inner.elevator--;
					auto& iii = (i % 2 == 0)
						? state_inner.deviceFloors[i / 2].first
						: state_inner.deviceFloors[i / 2].second;
					iii--;
					if (i != j) {
						auto& jjj = (j % 2 == 0)
							? state_inner.deviceFloors[j / 2].first
							: state_inner.deviceFloors[j / 2].second;
						jjj--;
					}
					if (state_inner.valid(_info)) {
						std::sort(
							state_inner.deviceFloors.begin(),
							state_inner.deviceFloors.end(),
							sortDevices);
						next.push_back(state_inner);
					}
				}
			}
		}

		return next;
	}
	bool Day11Puzzle::FacilityState::valid(const Day11Puzzle::FacilityStateInfo& _info) const {
		for (unsigned i = 0; i < this->deviceFloors.size(); ++i) {
			if (this->deviceFloors[i].first < 1 || this->deviceFloors[i].first > 4) { 
				return false;
			}
			if (this->deviceFloors[i].second < 1 || this->deviceFloors[i].second > 4) { 
				return false; 
			}
			if (this->deviceFloors[i].first == this->deviceFloors[i].second) {
				continue;
			}
			for (unsigned j = 0; j < this->deviceFloors.size(); ++j) {
				if (i == j) { continue; }
				if (this->deviceFloors[i].second == this->deviceFloors[j].first) {
					return false;
				}
			}
		}
		return true;
	}


	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {

		int part1 = 0;
		int part2 = 0;

		{
			std::cout << "Part 1" << std::endl;
			auto [start, end, info] = Day11Puzzle::parseInput(m_InputLines, false);
			part1 = (int)Day11Puzzle::lengthOfPath(start, end, info);
		}
		{
			std::cout << "Part 2" << std::endl;
			auto [start, end, info] = Day11Puzzle::parseInput(m_InputLines, true);
			part2 = (int)Day11Puzzle::lengthOfPath(start, end, info);
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
	std::tuple<Day11Puzzle::FacilityState, Day11Puzzle::FacilityState, Day11Puzzle::FacilityStateInfo> Day11Puzzle::parseInput(const std::vector<std::string>& _input, bool _part2) {
		FacilityState start;
		FacilityStateInfo info;
		std::unordered_map<std::string, int> generatorFloors;
		std::unordered_map<std::string, int> microchipFloors;

		for (unsigned i = 0; i < 4; ++i) {
			const int floor = (int)(i)+1;
			const auto& splits = ze::StringExtensions::splitStringByDelimeter(_input[i], " -.,");
			for (unsigned j = 0; j < splits.size() - 1; ++j) {
				if (splits[j + 1] == "generator") {
					generatorFloors[splits[j]] = floor;
					info.elements.insert(splits[j]);
				}
				else if (splits[j + 1] == "compatible") {
					microchipFloors[splits[j]] = floor;
				}
			}
		}
		if (_part2) {
			info.elements.insert("elerium");
			generatorFloors["elerium"] = 1;
			microchipFloors["elerium"] = 1;

			info.elements.insert("dilithium");
			generatorFloors["dilithium"] = 1;
			microchipFloors["dilithium"] = 1;
		}

		start.elevator = 1;
		for (const auto& element : info.elements) {
			start.deviceFloors.emplace_back(generatorFloors[element], microchipFloors[element]);
		}

		return { start, FacilityState(4, std::vector<int>(info.elements.size() * 2, 4)), info };
	}
}
