#ifndef INCLUDED_ADVENT_OF_CODE_CORE_PUZZLE_CONSTRUCTOR_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_PUZZLE_CONSTRUCTOR_HPP_

#include <Core/InitialisationInfo.hpp>
#include <Core/IPuzzleBase.hpp>
#include <functional>
#include <map>

#define REGISTER_YEAR(ns, y) \
    core::PuzzleConstructor::registerPuzzle<ns::Day01Puzzle>(y,  1);\
    core::PuzzleConstructor::registerPuzzle<ns::Day02Puzzle>(y,  2);\
    core::PuzzleConstructor::registerPuzzle<ns::Day03Puzzle>(y,  3);\
    core::PuzzleConstructor::registerPuzzle<ns::Day04Puzzle>(y,  4);\
    core::PuzzleConstructor::registerPuzzle<ns::Day05Puzzle>(y,  5);\
    core::PuzzleConstructor::registerPuzzle<ns::Day06Puzzle>(y,  6);\
    core::PuzzleConstructor::registerPuzzle<ns::Day07Puzzle>(y,  7);\
    core::PuzzleConstructor::registerPuzzle<ns::Day08Puzzle>(y,  8);\
    core::PuzzleConstructor::registerPuzzle<ns::Day09Puzzle>(y,  9);\
    core::PuzzleConstructor::registerPuzzle<ns::Day10Puzzle>(y, 10);\
    core::PuzzleConstructor::registerPuzzle<ns::Day11Puzzle>(y, 11);\
    core::PuzzleConstructor::registerPuzzle<ns::Day12Puzzle>(y, 12);\
    core::PuzzleConstructor::registerPuzzle<ns::Day13Puzzle>(y, 13);\
    core::PuzzleConstructor::registerPuzzle<ns::Day14Puzzle>(y, 14);\
    core::PuzzleConstructor::registerPuzzle<ns::Day15Puzzle>(y, 15);\
    core::PuzzleConstructor::registerPuzzle<ns::Day16Puzzle>(y, 16);\
    core::PuzzleConstructor::registerPuzzle<ns::Day17Puzzle>(y, 17);\
    core::PuzzleConstructor::registerPuzzle<ns::Day18Puzzle>(y, 18);\
    core::PuzzleConstructor::registerPuzzle<ns::Day19Puzzle>(y, 19);\
    core::PuzzleConstructor::registerPuzzle<ns::Day20Puzzle>(y, 20);\
    core::PuzzleConstructor::registerPuzzle<ns::Day21Puzzle>(y, 21);\
    core::PuzzleConstructor::registerPuzzle<ns::Day22Puzzle>(y, 22);\
    core::PuzzleConstructor::registerPuzzle<ns::Day23Puzzle>(y, 23);\
    core::PuzzleConstructor::registerPuzzle<ns::Day24Puzzle>(y, 24);\
    core::PuzzleConstructor::registerPuzzle<ns::Day25Puzzle>(y, 25);

namespace core {
	using PuzzleConstructionFxn = std::function<core::IPuzzleBase*(const InitialisationInfo&)>;
	
	class PuzzleConstructor {
	public:		
		template <typename T>
		static void registerPuzzle(int _year, int _day) {
			constructorMethods[_year * 100 + _day] = [](const InitialisationInfo& _info) -> core::IPuzzleBase * {
				return new T();
			};
		}

		static core::IPuzzleBase *createPuzzle(const InitialisationInfo& _info) {
			if (!_info.valid) {
				return nullptr;
			}

			core::IPuzzleBase *puzzle = constructorMethods[_info.year * 100 + _info.day](_info);
			puzzle->initialise(_info);
			return puzzle;
		}

	private:
		PuzzleConstructor() = delete;
		~PuzzleConstructor() = delete;

		static std::map<int, PuzzleConstructionFxn> constructorMethods;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_PUZZLE_CONSTRUCTOR_HPP_