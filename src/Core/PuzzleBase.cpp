#include <Core/PuzzleBase.hpp>

namespace core {

	PuzzleBase::PuzzleBase(const std::string& _puzzleName, int _puzzleYear, int _puzzleDay) :
		m_PuzzleName(_puzzleName),
		m_PuzzleYear(_puzzleYear), 
		m_PuzzleDay(_puzzleDay) {
		
	}

	PuzzleBase::~PuzzleBase() {

	}

	const std::string& PuzzleBase::getPuzzleName() const { return m_PuzzleName; }
	int PuzzleBase::getPuzzleYear() const { return m_PuzzleYear; }
	int PuzzleBase::getPuzzleDay() const { return m_PuzzleDay; }

	void PuzzleBase::setVerbose(bool _verbose) {
		m_Verbose = _verbose;
	}
	bool PuzzleBase::getVerbose() const {
		return m_Verbose;
	}

}
