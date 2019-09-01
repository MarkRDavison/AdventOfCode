#include <2016/Day11Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <regex>
#include <stack>

namespace TwentySixteen {
	
	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Radioisotope Thermoelectric Generators", 2016, 11) {

	}
	Day11Puzzle::~Day11Puzzle() {

	}


	std::vector<ParsedComponent> Day11Puzzle::parseInput(const std::vector<std::string>& _input) const {
		std::vector<ParsedComponent> components;

		std::smatch m;
		const std::regex microchipRegex("([a-z]+)-compatible microchip");
		const std::regex generatorRegex("([a-z]+) generator");

		int floor = 1;

		for (const std::string& _line : _input) {

			std::string line(_line);
			while (std::regex_search(line, m, microchipRegex)) {
				components.emplace_back(floor, toupper(m[0].str()[0]), toupper(m[0].str()[1]), 'M');
				line = m.suffix();
			}

			line = _line;
			while (std::regex_search(line, m, generatorRegex)) {
				components.emplace_back(floor, toupper(m[0].str()[0]), toupper(m[0].str()[1]), 'G');
				line = m.suffix();

			}

			floor++;
		}

		return components;
	}
	std::vector<std::string> Day11Puzzle::dumpState(const State& _state, const std::vector<ParsedComponent>& _parsedComponents) const {
		std::vector<std::string> result;

		for (int f = Floors; f >= 1; --f) {
			std::string floor = "F" + std::to_string(f);
			floor += (std::string(" ") + (_state.elevator == f ? "E" : "."));

			for (unsigned i = 0; i < _parsedComponents.size() / 2; ++i) {
				const auto& genComp = _parsedComponents[i * 2 + 0];
				const auto& micComp = _parsedComponents[i * 2 + 1];
				if (f == _state.generators[i]) {
					floor += " " + std::string(1, genComp.symbol1) + std::string(1, genComp.symbol2) + "G";
				}
				else {
					floor += " .  ";
				}
				if (f == _state.microchips[i]) {
					floor += " " + std::string(1, micComp.symbol1) + std::string(1, micComp.symbol2) + "M";
				} else {
					floor += " .  ";
				}
			}
			result.push_back(floor);
		}

		std::string hash = "Hash: " + std::to_string(_state.calculateHash());
		std::string valid = _state.isStateValid() ? "State is valid" : "State is not valid";;
		result.push_back(hash);
		result.push_back(valid);
		return result;
	}
	State Day11Puzzle::createStartState(const std::vector<ParsedComponent>& _parsedComponents) const {
		State state{};
		state.elevator = 1;
		state.generators.resize(_parsedComponents.size() / 2);
		state.microchips.resize(_parsedComponents.size() / 2);

		for (unsigned i = 0; i < _parsedComponents.size() / 2; ++i) {
			const auto& gen = _parsedComponents[i * 2 + 0];
			state.generators[i] = gen.floor;

			const auto& mic = _parsedComponents[i * 2 + 1];
			state.microchips[i] = mic.floor;
		}

		return state;
	}
	State Day11Puzzle::createEndState(const std::vector<ParsedComponent>& _parsedComponents) const {
		State state{};
		state.elevator = 4;
		state.generators.resize(_parsedComponents.size() / 2);
		state.microchips.resize(_parsedComponents.size() / 2);
		for (unsigned i = 0; i < _parsedComponents.size() / 2; ++i) {
			state.generators[i] = 4;
			state.microchips[i] = 4;
		}
		return state;
	}

	std::unordered_set<State> Day11Puzzle::enumerateAdjacentStates(const State& _currentState) const {
		std::unordered_set<State> states;

		// Move 2 things up
		// Move 1 thing up
		// Move 0 things up
		// Move 0 things down
		// Move 1 thing down
		// Move 2 things down

		if (_currentState.elevator < Floors) {
			{	// Can move up
				State up(_currentState);
				up.elevator++;
				states.emplace(up);
			}

			for (unsigned i = 0; i < _currentState.generators.size() + _currentState.microchips.size(); ++i) {
				if (i % _currentState.generators.size() == 0) {
					// i == Gen
					const auto gi = i / 2;
					auto genFloor = _currentState.generators[gi];
					if (genFloor == _currentState.elevator) {
						// We can move this up!
						State genUp(_currentState);
						genUp.elevator++;
						genUp.generators[gi]++;
						if (genUp.isStateValid()) {
							states.emplace(genUp);
						}
					}
				} else {
					// i == Mic
					const auto mi = (i - 1) / 2;
					auto micFloor = _currentState.microchips[mi];
					if (micFloor == _currentState.elevator) {
						// We can move this up!
						State micUp(_currentState);
						micUp.elevator++;
						micUp.microchips[mi]++;
						if (micUp.isStateValid()) {
							states.emplace(micUp);
						}
					}
				}

				for (unsigned j = i+1; j < _currentState.generators.size() + _currentState.microchips.size(); ++j) {
					bool component1IsGenerator = i % _currentState.generators.size() == 0;
					bool component2IsGenerator = j % _currentState.generators.size() == 0;
					unsigned component1Index = (i - (component1IsGenerator ? 0 : 1)) / 2;
					unsigned component2Index = (j - (component2IsGenerator ? 0 : 1)) / 2;
					int component1Floor = component1IsGenerator ? _currentState.generators[component1Index] : _currentState.microchips[component1Index];
					int component2Floor = component2IsGenerator ? _currentState.generators[component2Index] : _currentState.microchips[component2Index];

					if (component1Floor != _currentState.elevator ||
						component2Floor != _currentState.elevator) {
						continue;
					}

					State _2up(_currentState);
					_2up.elevator++;
					if (component1IsGenerator) {
						_2up.generators[component1Index]++;
					} else {
						_2up.microchips[component1Index]++;
					}
					if (component2IsGenerator) {
						_2up.generators[component2Index]++;
					} else {
						_2up.microchips[component2Index]++;
					}
					if (_2up.isStateValid()) {
						states.emplace(_2up);
					}
				}
			}
		}

		if (_currentState.elevator > 1) {
			{	// Can move down
				State down(_currentState);
				down.elevator--;
				states.emplace(down);
			}
			for (unsigned i = 0; i < _currentState.generators.size() + _currentState.microchips.size(); ++i) {
				if (i < _currentState.generators.size()) {
					// i == Gen
					const auto gi = i;
					auto genFloor = _currentState.generators[gi];
					if (genFloor == _currentState.elevator) {
						// We can move this down!
						State genDown(_currentState);
						genDown.elevator--;
						genDown.generators[gi]--;
						if (genDown.isStateValid()) {
							states.emplace(genDown);
						}
					}
				} else {
					// i == Mic
					const auto mi = i - _currentState.generators.size();
					auto micFloor = _currentState.microchips[mi];
					if (micFloor == _currentState.elevator) {
						// We can move this down!
						State micDown(_currentState);
						micDown.elevator--;
						micDown.microchips[mi]--;
						if (micDown.isStateValid()) {
							states.emplace(micDown);
						}
					}
				}
			}
		}

		return states;
	}

	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {
		std::vector<ParsedComponent> components = parseInput(m_InputLines);

		std::sort(components.begin(), components.end());

		const State startState = createStartState(components);
		const State endState = createEndState(components);

		std::unordered_set<State> seenStates;
		std::stack<State> nextStates;
		nextStates.push(startState);
		std::unordered_map<State, int> distances;
		distances[startState] = 0;

		std::cout << std::endl << "===== Start State =====" << std::endl;
		for (const auto& s : dumpState(startState, components)) {
			std::cout << s << std::endl;
		}
		std::cout << std::endl << "===== End State =====" << std::endl;
		for (const auto& s : dumpState(endState, components)) {
			std::cout << s << std::endl;
		}

		std::cout << std::endl << "===== Next States =====" << std::endl;

		int dist = std::numeric_limits<int>::max();
		int results = 0;

		while (!nextStates.empty()) {
			State currentState = nextStates.top();
			nextStates.pop();
			const auto currentDistance = distances[currentState];
			for (const auto& _next : enumerateAdjacentStates(currentState)) {
				if (seenStates.count(_next) > 0) { 
					auto prevDistance = distances[_next];
					auto currDistance = currentDistance + 1;
					if (currDistance >= prevDistance) {
						continue;
					}
				}
				seenStates.emplace(_next);
				nextStates.emplace(_next);
				distances[_next] = currentDistance + 1;

				if (nextStates.size() % 100 == 0) {
					std::cout << "Seen: " << seenStates.size() << ", Next: " << nextStates.size() << ", Completed " << results  << " times." << std::endl;
				}
				
				if (_next == endState) {
					results++;
					std::cout << "Found end after " << currentDistance + 1 << "!!!!!" << std::endl; 
					std::cout << std::endl << "----------" << std::endl;
					for (const auto& s : dumpState(_next, components)) {
						std::cout << s << std::endl;
					}
					std::cout << std::endl;
					dist = std::min(dist, currentDistance + 1);
				}
			}

		}

		std::cout << "Completed: " << dist << std::endl;
		getchar();

		return { std::to_string(dist), "Part 2" };
	}
}
