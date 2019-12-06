#include <2015/Day08Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyFifteen {
	
	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Matchsticks", 2015, 8) {

	}
	Day08Puzzle::~Day08Puzzle() {

	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {

		StringInfo totalInfo{};
		for (const auto& line : m_InputLines) {
			StringInfo lineInfo = getInfo(line);
			totalInfo.characterSize += lineInfo.characterSize;
			totalInfo.memorySize += lineInfo.memorySize;
			totalInfo.reincodeSize += encodeSize(line);
		}

		return { 
			std::to_string(totalInfo.characterSize - totalInfo.memorySize), 
			std::to_string(totalInfo.reincodeSize - totalInfo.characterSize)
		};
	}

	Day08Puzzle::StringInfo Day08Puzzle::getInfo(const std::string& _line) {
		StringInfo info{};
		info.characterSize = _line.size();

		for (unsigned i = 1; i < _line.size() - 1; ++i) {
			if (_line.at(i) != '\\') {
				info.memorySize++;
				continue;
			}

			i++;
			if (_line.at(i) == '\\' ||
				_line.at(i) == '"') {
				info.memorySize++;
				continue;
			}

			if (_line.at(i) == 'x') {
				info.memorySize++;
				i += 2;
			}
		}

		return info;
	}
	unsigned Day08Puzzle::encodeSize(const std::string& _line) {
		unsigned size{ 2 }; // To include the surrounding quotes

		for (unsigned i = 0; i < _line.size(); ++i) {
			if (_line.at(i) == '"') {
				size += 2;
				continue;
			}
			if (_line.at(i) == '\\') {
				if (_line.at(i) != 'x') {
					// just a single escape character to be escaped
					size += 2;
					continue;
				}

				// hex number escaped
				size += 4;
				i += 3;
			} else {
				// Regular character
				size++;
			}
		}

		return size;
	}
}
