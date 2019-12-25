#include <Core/PuzzleConstructor.hpp>

#include <iostream>

#include <2015/Day01Puzzle.hpp>
#include <2015/Day02Puzzle.hpp>
#include <2015/Day03Puzzle.hpp>
#include <2015/Day04Puzzle.hpp>
#include <2015/Day05Puzzle.hpp>
#include <2015/Day06Puzzle.hpp>
#include <2015/Day07Puzzle.hpp>
#include <2015/Day08Puzzle.hpp>
#include <2015/Day09Puzzle.hpp>
#include <2015/Day10Puzzle.hpp>
#include <2015/Day11Puzzle.hpp>
#include <2015/Day12Puzzle.hpp>
#include <2015/Day13Puzzle.hpp>
#include <2015/Day14Puzzle.hpp>
#include <2015/Day15Puzzle.hpp>
#include <2015/Day16Puzzle.hpp>
#include <2015/Day17Puzzle.hpp>
#include <2015/Day18Puzzle.hpp>
#include <2015/Day19Puzzle.hpp>
#include <2015/Day20Puzzle.hpp>
#include <2015/Day21Puzzle.hpp>
#include <2015/Day22Puzzle.hpp>
#include <2015/Day23Puzzle.hpp>
#include <2015/Day24Puzzle.hpp>
#include <2015/Day25Puzzle.hpp>

int main(int _argc, char **_argv) {

    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day01Puzzle>( 1);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day02Puzzle>( 2);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day03Puzzle>( 3);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day04Puzzle>( 4);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day05Puzzle>( 5);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day06Puzzle>( 6);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day07Puzzle>( 7);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day08Puzzle>( 8);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day09Puzzle>( 9);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day10Puzzle>(10);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day11Puzzle>(11);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day12Puzzle>(12);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day13Puzzle>(13);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day14Puzzle>(14);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day15Puzzle>(15);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day16Puzzle>(16);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day17Puzzle>(17);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day18Puzzle>(18);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day19Puzzle>(19);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day20Puzzle>(20);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day21Puzzle>(21);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day22Puzzle>(22);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day23Puzzle>(23);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day24Puzzle>(24);
    core::PuzzleConstructor::registerPuzzle<TwentyFifteen::Day25Puzzle>(25);

	core::IPuzzleBase *puzzle = core::PuzzleConstructor::createPuzzle(core::InitialisationInfo::parseArguments(_argc, _argv));

	if (puzzle == nullptr) {
		return EXIT_FAILURE;
	}

	std::cout << "Puzzle " << puzzle->getPuzzleYear() << " - Day " << puzzle->getPuzzleDay() << " - " << puzzle->getPuzzleName() << std::endl;

	const std::pair<std::string, std::string>& solution = puzzle->fastSolve();

	std::cout << "Part 1: " << solution.first << std::endl << "Part 2: " << solution.second << std::endl;

	delete puzzle;

	return EXIT_SUCCESS;
}