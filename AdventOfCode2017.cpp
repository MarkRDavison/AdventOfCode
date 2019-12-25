#include <Core/PuzzleConstructor.hpp>

#include <iostream>
#include <chrono>

#include <2017/Day01Puzzle.hpp>
#include <2017/Day02Puzzle.hpp>
#include <2017/Day03Puzzle.hpp>
#include <2017/Day04Puzzle.hpp>
#include <2017/Day05Puzzle.hpp>
#include <2017/Day06Puzzle.hpp>
#include <2017/Day07Puzzle.hpp>
#include <2017/Day08Puzzle.hpp>
#include <2017/Day09Puzzle.hpp>
#include <2017/Day10Puzzle.hpp>
#include <2017/Day11Puzzle.hpp>
#include <2017/Day12Puzzle.hpp>
#include <2017/Day13Puzzle.hpp>
#include <2017/Day14Puzzle.hpp>
#include <2017/Day15Puzzle.hpp>
#include <2017/Day16Puzzle.hpp>
#include <2017/Day17Puzzle.hpp>
#include <2017/Day18Puzzle.hpp>
#include <2017/Day19Puzzle.hpp>
#include <2017/Day20Puzzle.hpp>
#include <2017/Day21Puzzle.hpp>
#include <2017/Day22Puzzle.hpp>
#include <2017/Day23Puzzle.hpp>
#include <2017/Day24Puzzle.hpp>
#include <2017/Day25Puzzle.hpp>

int main(int _argc, char **_argv) {

    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day01Puzzle>( 1);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day02Puzzle>( 2);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day03Puzzle>( 3);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day04Puzzle>( 4);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day05Puzzle>( 5);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day06Puzzle>( 6);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day07Puzzle>( 7);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day08Puzzle>( 8);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day09Puzzle>( 9);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day10Puzzle>(10);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day11Puzzle>(11);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day12Puzzle>(12);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day13Puzzle>(13);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day14Puzzle>(14);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day15Puzzle>(15);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day16Puzzle>(16);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day17Puzzle>(17);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day18Puzzle>(18);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day19Puzzle>(19);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day20Puzzle>(20);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day21Puzzle>(21);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day22Puzzle>(22);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day23Puzzle>(23);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day24Puzzle>(24);
    core::PuzzleConstructor::registerPuzzle<TwentySeventeen::Day25Puzzle>(25);

	core::IPuzzleBase *puzzle = core::PuzzleConstructor::createPuzzle(core::InitialisationInfo::parseArguments(_argc, _argv));

	if (puzzle == nullptr) {
		return EXIT_FAILURE;
	}

	auto start = std::chrono::high_resolution_clock::now();
	std::cout << "Puzzle " << puzzle->getPuzzleYear() << " - Day " << puzzle->getPuzzleDay() << " - " << puzzle->getPuzzleName() << std::endl;

	const std::pair<std::string, std::string>& solution = puzzle->fastSolve();

	std::cout << "Part 1: " << solution.first << std::endl << "Part 2: " << solution.second << std::endl;

	auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();   std::cout << "In " << microseconds << "ms." << std::endl;
	delete puzzle;

	return EXIT_SUCCESS;
}