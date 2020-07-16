#ifndef INCLUDED_ADVENT_OF_CODE_CORE_I_PUZZLE_BASE_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_I_PUZZLE_BASE_HPP_

#include <string>
#include <Core/InitialisationInfo.hpp>

namespace core {

	class IPuzzleBase {
	public:
		virtual ~IPuzzleBase() = 0;

		virtual const std::string& getPuzzleName() const = 0;
		virtual int getPuzzleYear() const = 0;
		virtual int getPuzzleDay() const = 0;

		virtual void setVerbose(bool _verbose) = 0;
		virtual bool getVerbose() const = 0;

		virtual void initialise(const core::InitialisationInfo& _initialisationInfo) = 0;
		virtual std::pair<std::string, std::string> fastSolve() = 0;
	};

	inline IPuzzleBase::~IPuzzleBase() = default;
	
}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_I_PUZZLE_BASE_HPP_