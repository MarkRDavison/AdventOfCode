#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_08_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_08_PUZZLE_HPP_

#include <2018/MetadataNode.hpp>
#include <Core/PuzzleBase.hpp>
#include <stack>

namespace TwentyEighteen {

	class Day08Puzzle : public core::PuzzleBase {
	public:
		Day08Puzzle();
		~Day08Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;
		
		static void addChildrenRecursively(MetadataNode& _node, std::stack<int>& _values);
		static int sumMetadata(const MetadataNode& _node);
		static int calculateMetadataSum(const MetadataNode& _node);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_08_PUZZLE_HPP_