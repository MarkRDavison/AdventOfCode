#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_11_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_11_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/States.hpp>
#include <tuple>
#include <set>

namespace TwentySixteen {

	
	class Day11Puzzle : public core::PuzzleBase {
	public:
		struct FacilityStateInfo {
			std::set<std::string> elements;
		};
		struct FacilityState {

			FacilityState() {}
			FacilityState(int _elevator, const std::vector<int>& _floors) :
				elevator(_elevator) {

				for (unsigned i = 0; i < _floors.size(); i += 2) {
					deviceFloors.emplace_back(_floors[i], _floors[i + 1]);
				}

			}

			int elevator{ 1 };
			std::vector<std::pair<int, int>> deviceFloors;

			std::string str() const;
			std::vector<FacilityState> enumerate(const FacilityStateInfo& _info) const;
			bool valid(const FacilityStateInfo& _info) const;
			inline bool operator==(const FacilityState& _other) const {
				return this->str() == _other.str();
			}
			inline bool operator!=(const FacilityState& _other) const {
				return !(*this == _other);
			}
		};

		struct FacilityStateHashFxn {
			std::size_t operator() (const Day11Puzzle::FacilityState& _key) const {
				return std::hash<std::string>()(_key.str());
			}
		};

		using SeenCostMap = std::unordered_map<FacilityState, unsigned, FacilityStateHashFxn>;
		using CameFromMap = std::unordered_map<FacilityState, std::pair<FacilityState, unsigned>, FacilityStateHashFxn>;

		static unsigned recursedLength(const FacilityState& _stop, FacilityStateInfo& _info, FacilityState _current, SeenCostMap& _seenCost, CameFromMap& _cameFrom, unsigned _currentMinCost, unsigned _currentCost) {
			
			_seenCost[_current] = _currentCost;
			if (_current.str() == _stop.str()) {
				std::cout << "Found path, length: " << _currentCost << std::endl;
				return _currentCost;
			}

			if (_currentCost > _currentMinCost) {
				return std::numeric_limits<unsigned>::max();
			}
			for (const auto& n : _current.enumerate(_info)) {
				auto nextCost = _currentCost + 1;

				if (_seenCost.find(n) != _seenCost.end()) {
					if (_seenCost[n] > nextCost) {
						_seenCost[n] = nextCost;
					}
					else {
						continue;
					}
				}

				unsigned l = recursedLength(_stop, _info, n, _seenCost, _cameFrom, _currentMinCost, nextCost);

				if (l < _currentMinCost) {
					_currentMinCost= l;
				}
			}

			return _currentMinCost;
		}

		static unsigned lengthOfPath(const FacilityState& _start, const FacilityState& _stop, FacilityStateInfo& _info) {
			SeenCostMap seenCost;
			CameFromMap cameFrom;

			return recursedLength(_stop, _info, _start, seenCost, cameFrom, std::numeric_limits<unsigned>::max(), 0);
		}

		Day11Puzzle();
		~Day11Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::tuple<FacilityState, FacilityState, FacilityStateInfo> parseInput(const std::vector<std::string>& _input, bool _part2);

	private:
		std::vector<std::string> m_InputLines;
	};

}


#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_11_PUZZLE_HPP_