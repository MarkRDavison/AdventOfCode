#include <2016/Day02Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Orientation.hpp>

namespace TwentySixteen {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("Bathroom Security", 2016, 2) {

	}
	Day02Puzzle::~Day02Puzzle() {

	}

	core::Orientation charToOrientation(char _c) {
		switch (_c) {
		case 'U':
			return core::Orientation::Up;
		case 'D':
			return core::Orientation::Down;
		case 'R':
			return core::Orientation::Right;
		case 'L':
			return core::Orientation::Left;
		default:
			return core::Orientation::None;
		}
	}

	char locationToPart1ButtonValue(const core::Vector2i& _location) {
		if (_location == core::Vector2i{ -1, +1 }) {
			return '1';
		}
		if (_location == core::Vector2i{ +0, +1 }) {
			return '2';
		}
		if (_location == core::Vector2i{ +1, +1 }) {
			return '3';
		}
		if (_location == core::Vector2i{ -1, +0 }) {
			return '4';
		}
		if (_location == core::Vector2i{ +0, +0 }) {
			return '5';
		}
		if (_location == core::Vector2i{ +1, +0 }) {
			return '6';
		}
		if (_location == core::Vector2i{ -1, -1 }) {
			return '7';
		}
		if (_location == core::Vector2i{ +0, -1 }) {
			return '8';
		}
		if (_location == core::Vector2i{ +1, -1 }) {
			return '9';
		}

		return '?';
	}
	char locationToPart2ButtonValue(const core::Vector2i& _location) {
		if (_location == core::Vector2i{ +0, +2 }) {
			return '1';
		}

		if (_location == core::Vector2i{ -1, +1 }) {
			return '2';
		}
		if (_location == core::Vector2i{ +0, +1 }) {
			return '3';
		}
		if (_location == core::Vector2i{ +1, +1 }) {
			return '4';
		}

		if (_location == core::Vector2i{ -2, +0 }) {
			return '5';
		}
		if (_location == core::Vector2i{ -1, +0 }) {
			return '6';
		}
		if (_location == core::Vector2i{ +0, +0 }) {
			return '7';
		}
		if (_location == core::Vector2i{ +1, +0 }) {
			return '8';
		}
		if (_location == core::Vector2i{ +2, +0 }) {
			return '9';
		}

		if (_location == core::Vector2i{ -1, -1 }) {
			return 'A';
		}
		if (_location == core::Vector2i{ +0, -1 }) {
			return 'B';
		}
		if (_location == core::Vector2i{ +1, -1 }) {
			return 'C';
		}

		if (_location == core::Vector2i{ +0, -2 }) {
			return 'D';
		}

		return '?';
	}

	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {

		/*
		Part 1

		1 2 3
		4 5 6
		7 8 9

		*/
		/*
		Part 2

			1
		  2 3 4
		5 6 7 8 9
		  A B C
			D
		*/

		const core::Vector2i part1StartLocation = { 0, 0 };
		const core::Vector2i part2StartLocation = { -2, 0 };
		core::Vector2i part1Location = part1StartLocation;
		core::Vector2i part2Location = part2StartLocation;
		const auto part1CanMove = [](const core::Orientation & _orientation, const core::Vector2i & _location) -> bool {
			const auto offset = core::OrientationHelper::toDirection(_orientation);
			const auto destination = core::Vector2i{ offset.x + _location.x, offset.y + _location.y };
			if (destination.x >= 2 || destination.x <= -2) {
				return false;
			}
			if (destination.y >= 2 || destination.y <= -2) {
				return false;
			}
			return true;
		};
		const auto part2CanMove = [](const core::Orientation & _orientation, const core::Vector2i & _location) -> bool {
			const auto offset = core::OrientationHelper::toDirection(_orientation);
			const auto destination = core::Vector2i{ offset.x + _location.x, offset.y + _location.y };

			const auto displacement = std::abs(destination.x) + std::abs(destination.y);

			return displacement <= 2;
		};

		std::string part1;
		std::string part2;

		for (const auto& line : m_InputLines) {
			for (char c : line) {
				const auto orientation = charToOrientation(c);
				const auto direction = core::OrientationHelper::toDirection(orientation);

				if (part1CanMove(orientation, part1Location)) {
					part1Location = direction + part1Location;
				}
				if (part2CanMove(orientation, part2Location)) {
					part2Location = direction + part2Location;
				}
			}

			part1 += locationToPart1ButtonValue(part1Location);
			part2 += locationToPart2ButtonValue(part2Location);
		}


		return { part1, part2 };
	}
}
