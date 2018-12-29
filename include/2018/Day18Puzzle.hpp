#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_18_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_18_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyEighteen {

	struct NeighbourCount {
		int Open{ 0 };
		int Trees{ 0 };
		int Lumberyards{ 0 };

		bool operator==(const NeighbourCount& _other) const {
			return 
				this->Trees == _other.Trees &&
				this->Lumberyards == _other.Lumberyards;
		}

		bool operator<(const NeighbourCount& _other) const {
			return this->Trees * this->Lumberyards < _other.Trees * _other.Lumberyards;
		}
	};

	enum class BufferType {
		Front,
		Back
	};

	class Day18Puzzle : public core::PuzzleBase {
	public:
		Day18Puzzle();
		~Day18Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		void printForest() const;
		void performIteration();
		NeighbourCount calculateNeighbourCount(std::size_t _x, std::size_t _y) const;
		NeighbourCount calculateForestCount() const;

	private:
		NeighbourCount m_CurrentCount{};
		int m_Minutes{ 0 };
		BufferType m_Type{ BufferType::Front };
		std::vector<std::string> m_InputLines;
		std::vector<std::vector<std::pair<char, char>>> m_DoubleBufferedForest;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_18_PUZZLE_HPP_