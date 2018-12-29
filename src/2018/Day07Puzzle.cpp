#include <2018/Day07Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <regex>
#include <unordered_set>
#include <set>
#include <map>
#include <numeric>

namespace TwentyEighteen {

	Day07Puzzle::Day07Puzzle(int _numWorkers /*= 5*/, int _timeBase /*= 60*/) :
		core::PuzzleBase("The Sum of Its Parts", 2018, 7),
		m_Workers(_numWorkers),
		m_TimeBase(_timeBase) {

	}
	Day07Puzzle::~Day07Puzzle() {

	}

	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {

		std::smatch m;
		const std::regex regex("Step ([A-Z]) must be finished before step ([A-Z]) can begin.");

		std::vector<std::pair<char, char>> inputs;

		for (const std::string& _row : m_InputLines) {
			std::regex_match(_row, m, regex);
			inputs.emplace_back(m[1].str()[0], m[2].str()[0]);
		}

		const auto part1 = solveForWorkers(1, 0, inputs, true);
		const auto part2 = solveForWorkers(m_Workers, m_TimeBase, inputs, false);

		return { part1.first, std::to_string(part2.second) };
	}

	std::pair<std::string, int> Day07Puzzle::solveForWorkers(int _workers, int _timeBase, const std::vector<std::pair<char, char>>& _inputPairs, bool _singleStepSteps) {
		int allocatedWorkers = 0;
		int totalWork = 0;
		std::string completedStepSequence;
				
		std::map<char, int> remainingWork;
		std::set<char> inProgressSteps;
		std::map<char, std::set<char>> stepsNotInProgress;

		std::set<char> validSteps;

		for (const std::pair<char, char>& _pair : _inputPairs) {
			validSteps.emplace(_pair.first);
			validSteps.emplace(_pair.second);

			remainingWork[_pair.first] = _singleStepSteps ? 1 : static_cast<int>(_pair.first - 'A') + _timeBase + 1;
			remainingWork[_pair.second] = _singleStepSteps ? 1 : static_cast<int>(_pair.second - 'A') + _timeBase + 1;
		}

		const std::size_t resultSize = validSteps.size();

		for (const std::pair<char, char>& _pair : _inputPairs) {
			validSteps.erase(_pair.second);
			stepsNotInProgress[_pair.second].emplace(_pair.first);
		}
		
		while (completedStepSequence.size() < resultSize) {
			while (allocatedWorkers < _workers && !validSteps.empty()) {
				const char nextStep = *validSteps.begin();
				validSteps.erase(nextStep);
				inProgressSteps.emplace(nextStep);
				allocatedWorkers++;
			}

			std::unordered_set<char> completedSteps;
			for (char inProgressStep : inProgressSteps) {
				remainingWork[inProgressStep]--;
				if (remainingWork[inProgressStep] <= 0) {
					completedSteps.emplace(inProgressStep);
				}
			}

			std::unordered_set<char> newlyValidSteps;
			for (char c : completedSteps) {
				inProgressSteps.erase(c);
				allocatedWorkers--;
				completedStepSequence += c;

				for (auto& nextSteps : stepsNotInProgress) {
					nextSteps.second.erase(c);
					if (nextSteps.second.empty()) {
						newlyValidSteps.emplace(nextSteps.first);
					}
				}
			}
			
			for (char newlyValid : newlyValidSteps) {
				stepsNotInProgress.erase(newlyValid);
				validSteps.emplace(newlyValid);
			}

			totalWork++;
		}

		return { completedStepSequence, totalWork };
	}

}
