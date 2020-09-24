#include <2016/Day19Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <cassert>

namespace TwentySixteen {
	
	Day19Puzzle::Day19Puzzle() :
		core::PuzzleBase("An Elephant Named Joseph", 2016, 19) {

	}
	Day19Puzzle::~Day19Puzzle() {

	}


	void Day19Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day19Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day19Puzzle::fastSolve() {
		const auto part1 = solveElfPresents(std::stoi(m_InputLines[0]));
		const auto part2 = solveElfPresentsAcross(std::stoi(m_InputLines[0]));
		std::cout << "Part 2: 920806 <- is too low" << std::endl;
		return { std::to_string(part1), std::to_string(part2) };
	}

	int Day19Puzzle::solveElfPresents(int _number) {
		struct Elf {

			Elf(int _position) : 
				position(_position) {

			}

			Elf* prev{ nullptr };
			Elf* next{ nullptr };
			int position;
			int presents{ 1 };
		};

		Elf* root = new Elf(1);
		Elf* current = root;

		for (int i = 2; i <= _number; ++i) {
			Elf* next = new Elf(i);
			current->next = next;
			next->prev = current;
			current = next;
		}

		root->prev = current;
		current->next = root;

		current = root;

		while (current != current->next) {
			Elf* thief = current;
			Elf* theftTarget = thief->next;

			thief->presents += theftTarget->presents;

			thief->next = theftTarget->next;
			thief->next->prev = thief;

			current = thief->next;

			delete theftTarget;
		}

		const int position = current->position;
		delete current;
		return position;
	}
	
	int Day19Puzzle::solveElfPresentsAcross(int _number) {
		struct Elf {

			Elf(int _position) :
				position(_position) {

			}

			Elf* prev{ nullptr };
			Elf* next{ nullptr };
			int position;
			int presents{ 1 };
		};

		int numberOfElves = _number;

		Elf* root = new Elf(1);
		Elf* current = root;
		Elf* opposite = nullptr;

		for (int i = 2; i <= _number; ++i) {
			Elf* next = new Elf(i);
			current->next = next;
			next->prev = current;
			current = next;
			if (i == 1 + (_number) / 2) {
				opposite = current;
			}
		}
		root->prev = current;
		current->next = root;

		current = root;

		assert(opposite != nullptr);
		while (current != current->next) {


			Elf* thief = current;
			Elf* victim = opposite;

			const int thiefPosition = thief->position;
			const int victimPosition = victim->position;

			thief->presents += victim->presents;

			Elf* leftOfVictim = victim->prev;
			Elf* rightOfVictim = victim->next;

			delete victim;
			leftOfVictim->next = rightOfVictim;
			rightOfVictim->prev = leftOfVictim;

			current = current->next;
			opposite = rightOfVictim;
			numberOfElves--;
			
			if (numberOfElves % 2 == 0) {
				opposite = opposite->next;
			}

		}

		const int position = current->position;
		delete current;
		return position;
	}
}
