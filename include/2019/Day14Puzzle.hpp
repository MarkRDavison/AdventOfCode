#ifndef INCLUDED_ADVENT_OF_CODE_2019_DAY_14_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2019_DAY_14_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>

namespace TwentyNineteen {

	using ReactionId = std::string;
	using ReactionOutput = long long;
	struct Ingrediant {
		ReactionId name;
		ReactionOutput amount;

	};
	struct Reaction {
		Ingrediant output;
		std::vector<Ingrediant> input;
	};
	
	class Day14Puzzle : public core::PuzzleBase {
	public:
		Day14Puzzle();
		~Day14Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;
		ReactionOutput howMuchOre(
			ReactionId _chemical,
			ReactionOutput _amount,
			std::unordered_map<ReactionId, ReactionOutput>& _excess,
			std::unordered_map<ReactionId, Reaction>& _referenceData,
			unsigned _depth);
	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2019_DAY_14_PUZZLE_HPP_