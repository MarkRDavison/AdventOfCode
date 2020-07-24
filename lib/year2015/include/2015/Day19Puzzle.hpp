#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_19_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_19_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>

namespace TwentyFifteen {

	using Replacements = std::unordered_map<std::string, std::vector<std::string>>;

	class Day19Puzzle : public core::PuzzleBase {
	public:
		Day19Puzzle();
		~Day19Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<Replacements, std::string> parseInput(const std::vector<std::string>& _inputLines);

		static int getDistinctMolecues(const Replacements& _replacements, const std::string& _startingMolecule);
		static int stepsToFabricate(const Replacements& _replacements, const std::string& _target);
		static std::vector<std::string> splitAtCapitalLetter(const std::string& _string);
	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_19_PUZZLE_HPP_