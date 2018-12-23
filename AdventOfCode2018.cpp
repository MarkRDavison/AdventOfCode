#include <Core/PuzzleConstructor.hpp>

#include <iostream>

#include <2018/Day01Puzzle.hpp>
#include <2018/Day02Puzzle.hpp>
#include <2018/Day03Puzzle.hpp>
#include <2018/Day04Puzzle.hpp>
#include <2018/Day05Puzzle.hpp>
#include <2018/Day06Puzzle.hpp>
#include <2018/Day07Puzzle.hpp>
#include <2018/Day08Puzzle.hpp>
#include <2018/Day09Puzzle.hpp>
#include <2018/Day10Puzzle.hpp>
#include <2018/Day11Puzzle.hpp>
#include <2018/Day12Puzzle.hpp>
#include <2018/Day13Puzzle.hpp>
#include <2018/Day14Puzzle.hpp>
#include <2018/Day15Puzzle.hpp>
#include <2018/Day16Puzzle.hpp>
#include <2018/Day17Puzzle.hpp>
#include <2018/Day18Puzzle.hpp>
#include <2018/Day19Puzzle.hpp>
#include <2018/Day20Puzzle.hpp>
#include <2018/Day21Puzzle.hpp>
#include <2018/Day22Puzzle.hpp>
#include <2018/Day23Puzzle.hpp>
#include <2018/Day24Puzzle.hpp>
#include <2018/Day25Puzzle.hpp>

int main(int _argc, char **_argv) {

	{	// Register Puzzles
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day01Puzzle>(1);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day02Puzzle>(2);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day03Puzzle>(3);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day04Puzzle>(4);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day05Puzzle>(5);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day06Puzzle>(6);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day07Puzzle>(7);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day08Puzzle>(8);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day09Puzzle>(9);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day10Puzzle>(10);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day11Puzzle>(11);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day12Puzzle>(12);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day13Puzzle>(13);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day14Puzzle>(14);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day15Puzzle>(15);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day16Puzzle>(16);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day17Puzzle>(17);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day18Puzzle>(18);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day19Puzzle>(19);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day20Puzzle>(20);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day21Puzzle>(21);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day22Puzzle>(22);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day23Puzzle>(23);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day24Puzzle>(24);
		core::PuzzleConstructor::registerPuzzle<TwentyEighteen::Day25Puzzle>(25);
	}

	core::IPuzzleBase *puzzle = core::PuzzleConstructor::createPuzzle(core::InitialisationInfo::parseArguments(_argc, _argv));
	puzzle->setVerbose(true);

	if (puzzle == nullptr) {
		return EXIT_FAILURE;
	}

	std::cout << "Puzzle " << puzzle->getPuzzleYear() << " - Day " << puzzle->getPuzzleDay() << " - " << puzzle->getPuzzleName() << std::endl;

	const std::pair<std::string, std::string>& solution = puzzle->fastSolve();

	std::cout << "Part 1: " << solution.first << std::endl << "Part 2: " << solution.second << std::endl;

	delete puzzle;

	return EXIT_SUCCESS;
}