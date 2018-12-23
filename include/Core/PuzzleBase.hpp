#ifndef INCLUDED_ADVENT_OF_CODE_CORE_PUZZLE_BASE_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_PUZZLE_BASE_HPP_

#include <Core/IPuzzleBase.hpp>

namespace core {
	
	class PuzzleBase : public IPuzzleBase {
	public:
		PuzzleBase(const std::string& _puzzleName, int _puzzleYear, int _puzzleDay);
		~PuzzleBase() override;

		const std::string& getPuzzleName() const override;
		int getPuzzleYear() const override;
		int getPuzzleDay() const override;

		void setVerbose(bool _verbose) override;
		bool getVerbose() const override;

	private:
		std::string m_PuzzleName;
		int m_PuzzleYear;
		int m_PuzzleDay;
		bool m_Verbose{ false };
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_PUZZLE_BASE_HPP_