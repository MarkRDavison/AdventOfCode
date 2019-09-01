#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_11_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_11_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_set>

namespace TwentySixteen {

	struct ParsedComponent {

		ParsedComponent(int _floor, char _symbol1, char _symbol2, char _machineType) : floor(_floor), symbol1(_symbol1), symbol2(_symbol2), machineType(_machineType) {}

		int floor;
		char symbol1;
		char symbol2;
		char machineType;

		bool operator<(const ParsedComponent& _other) const {
			if (this->symbol1 == _other.symbol1 && 
				this->symbol2 == _other.symbol2) {
				return this->machineType < _other.machineType;
			}

			if (this->symbol1 == _other.symbol1) {
				return this->symbol2 < _other.symbol2;
			}

			return this->symbol1 < _other.symbol1;
		}

	};

	static constexpr const std::size_t Floors{ 4 };

	using HashValue = unsigned long long;

	struct State {
		int elevator;
		std::vector<int> microchips;
		std::vector<int> generators;

		HashValue calculateHash() const {
			HashValue hash = std::pow(10, generators.size() + microchips.size()) * elevator;
			for (unsigned i = 0; i < generators.size(); ++i) {
				hash += std::pow(10, generators.size() * 2 - 2 * i - 1) * generators[i];
				hash += std::pow(10, generators.size() * 2 - 2 * i - 2) * microchips[i];
			}

			return hash;
		}

		bool isStateValid() const {
			// if Microchip is on the same floor as another generator, without its own, state is not valid

			for (unsigned i = 0; i < microchips.size(); ++i) {
				const auto mFloor = microchips[i];
				if (mFloor == generators[i]) {
					continue;
				}
				for (unsigned j = 0; j < generators.size(); ++j) {
					if (i == j) continue;

					if (generators[j] == mFloor) {
						return false;
					}
				}
			}

			return true;
		}


		bool operator ==(const State& obj) const {
			if (obj.calculateHash() == calculateHash())
				return true;
			else
				return false;
		}
	};
	
	class Day11Puzzle : public core::PuzzleBase {
	public:
		Day11Puzzle();
		~Day11Puzzle() override;

		std::vector<ParsedComponent> parseInput(const std::vector<std::string>& _input) const;
		std::vector<std::string> dumpState(const State& _state, const std::vector<ParsedComponent>& _parsedComponents) const;
		State createStartState(const std::vector<ParsedComponent>& _parsedComponents) const;
		State createEndState(const std::vector<ParsedComponent>& _parsedComponents) const;
		std::unordered_set<State> enumerateAdjacentStates(const State& _currentState) const;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

	private:
		std::vector<std::string> m_InputLines;
	};

}

namespace std {
	template<>
	struct hash<TwentySixteen::State> {
		size_t operator()(const TwentySixteen::State& obj) const {
			return std::hash<TwentySixteen::HashValue>()(obj.calculateHash());
		}
	};
}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_11_PUZZLE_HPP_