#include <2018/Day09Puzzle.hpp>
#include <2018/Marble.hpp>
#include <Core/StringExtensions.hpp>
#include <regex>
#include <map>

namespace TwentyEighteen {

	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("Marble Mania", 2018, 9) {

	}
	Day09Puzzle::~Day09Puzzle() {

	}

	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	long long Day09Puzzle::runMarbleGame(const int _numberOfPlayers, const int _lastMarblePoints) const {
		std::shared_ptr<Marble> root = std::make_shared<Marble>(0);
		root->next = root;
		root->prev = root;

		std::map<long long, long long> scores;
		int currentPlayer = 0;
		int currentMarbleToPlace = 1;
		std::shared_ptr<Marble> currentMarble = root;

		while (currentMarbleToPlace <= _lastMarblePoints) {
			if (currentMarbleToPlace % 23 == 0) {
				scores[currentPlayer] += currentMarbleToPlace;

				for (int i = 0; i < 7; ++i) {
					currentMarble = currentMarble->prev;
				}

				scores[currentPlayer] += currentMarble->Value;
				std::shared_ptr<Marble>previousMarble = currentMarble->prev;
				std::shared_ptr<Marble>nextMarble = currentMarble->next;

				previousMarble->next = nextMarble;
				nextMarble->prev = previousMarble;

				currentMarble = nextMarble;
			}
			else {
				std::shared_ptr<Marble>preInsertMarble = currentMarble->next;
				std::shared_ptr<Marble>postInsertMarble = preInsertMarble->next;

				std::shared_ptr<Marble>insertedMarble = std::make_shared<Marble>(currentMarbleToPlace);

				preInsertMarble->next = insertedMarble;
				insertedMarble->prev = preInsertMarble;

				insertedMarble->next = postInsertMarble;
				postInsertMarble->prev = insertedMarble;

				currentMarble = insertedMarble;
			}

			currentMarbleToPlace++;
			currentPlayer++;
			if (currentPlayer >= _numberOfPlayers) {
				currentPlayer -= _numberOfPlayers;
			}
		}

		long long maxScore = 0;
		for (const auto& pair : scores) {
			maxScore = std::max(maxScore, pair.second);
		}

		return maxScore;
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {

		std::smatch m;
		const std::regex regex("([0-9]+) players; last marble is worth ([0-9]+) points");

		std::regex_match(m_InputLines[0], m, regex);

		const int NumberOfPlayers = std::atoi(m[1].str().c_str());
		const int LastMarblePoints = std::atoi(m[2].str().c_str());

		const long long part1Score = runMarbleGame(NumberOfPlayers, LastMarblePoints);
		const long long part2Score = runMarbleGame(NumberOfPlayers, LastMarblePoints * 100);

		return { std::to_string(part1Score), std::to_string(part2Score) };
	}

}
