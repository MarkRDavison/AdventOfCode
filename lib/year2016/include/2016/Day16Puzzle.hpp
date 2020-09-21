#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_16_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_16_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySixteen {
	
	class Day16Puzzle : public core::PuzzleBase {
	public:
		Day16Puzzle();
		~Day16Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::string performDragonProcess(const std::string& _input);
		static std::string performDragonProcessForDesiredSize(const std::string& _input, unsigned _size);
		static std::string calculateChecksum(const std::string& _input);
		static std::string calculateChecksumFromStateForSize(const std::string& _state, unsigned _length);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_16_PUZZLE_HPP_