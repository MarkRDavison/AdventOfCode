#include <2016/Day04Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>

namespace {
	struct LetterOccurence {

		LetterOccurence(char _c) : letter(_c) {}

		char letter{ '?' };
		unsigned occurence{ 0 };

		bool operator<(const LetterOccurence& _other) const {
			if (this->occurence > _other.occurence) {
				return true;
			}
			if (this->occurence < _other.occurence) {
				return false;
			}

			return this->letter < _other.letter;
		}
	};

	struct ParsedRoom {

		ParsedRoom() {
			for (char c = 'a'; c <= 'z'; ++c) {
				occurences.push_back(LetterOccurence(c));
			}
		}

		void decryptRoom() {
			const int offset = id % 26;

			for (char c : letters) {
				decryptedName += static_cast<char>(((static_cast<int>(c - 'a') + offset) % 26) + 'a');
			}
		}

		void validateRoom() {
			std::sort(occurences.begin(), occurences.end());

			bool valid = true;
			for (unsigned i = 0; i < checksum.size(); ++i) {
				if (checksum[i] != occurences[i].letter) {
					valid = false;
					break;
				}
			}
			isRoomValid = valid;
		}

		std::string decryptedName;
		std::string letters;
		int id{ 0 };
		std::string checksum;

		std::vector<LetterOccurence> occurences;
		bool isRoomValid{ false };
	};

}

namespace TwentySixteen {
	
	Day04Puzzle::Day04Puzzle() :
		core::PuzzleBase("Security Through Obscurity", 2016, 4) {

	}
	Day04Puzzle::~Day04Puzzle() {

	}


	void Day04Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day04Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day04Puzzle::fastSolve() {

		unsigned part2Id = std::numeric_limits<unsigned>::max();
		unsigned part1SectorIdSum = 0;
		std::vector<ParsedRoom> rooms;
		for (const auto& line : m_InputLines) {
			ParsedRoom room;

			const auto& parts = core::StringExtensions::splitStringByDelimeter(line, "-[]");
			
			room.id = std::atoi(parts[parts.size() - 2].c_str());
			room.checksum = parts.back();
			for (unsigned i = 0; i < parts.size() - 2; ++i) {
				for (char c : parts[i]) {
					room.letters += c;
					room.occurences[c - 'a'].occurence++;
				}
			}
			room.validateRoom();
			room.decryptRoom();
			if (room.isRoomValid) {
				part1SectorIdSum += room.id;
			}
			if (part2Id == std::numeric_limits<unsigned>::max() &&
				room.decryptedName.find("north") != std::string::npos) {
				part2Id = room.id;
				if (getVerbose()) {
					std::cout << "North pole objects found at: " << room.decryptedName << std::endl;
				}
			}

			rooms.push_back(room);
		}

		return { std::to_string(part1SectorIdSum), std::to_string(part2Id) };
	}
}
