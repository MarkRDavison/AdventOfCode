#include <Core/PuzzleConstructor.hpp>

#include <iostream>
#include <chrono>

#include <2019/Day01Puzzle.hpp>
#include <2019/Day02Puzzle.hpp>
#include <2019/Day03Puzzle.hpp>
#include <2019/Day04Puzzle.hpp>
#include <2019/Day05Puzzle.hpp>
#include <2019/Day06Puzzle.hpp>
#include <2019/Day07Puzzle.hpp>
#include <2019/Day08Puzzle.hpp>
#include <2019/Day09Puzzle.hpp>
#include <2019/Day10Puzzle.hpp>
#include <2019/Day11Puzzle.hpp>
#include <2019/Day12Puzzle.hpp>
#include <2019/Day13Puzzle.hpp>
#include <2019/Day14Puzzle.hpp>
#include <2019/Day15Puzzle.hpp>
#include <2019/Day16Puzzle.hpp>
#include <2019/Day17Puzzle.hpp>
#include <2019/Day18Puzzle.hpp>
#include <2019/Day19Puzzle.hpp>
#include <2019/Day20Puzzle.hpp>
#include <2019/Day21Puzzle.hpp>
#include <2019/Day22Puzzle.hpp>
#include <2019/Day23Puzzle.hpp>
#include <2019/Day24Puzzle.hpp>
#include <2019/Day25Puzzle.hpp>

int main(int _argc, char **_argv) {

    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day01Puzzle>( 1);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day02Puzzle>( 2);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day03Puzzle>( 3);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day04Puzzle>( 4);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day05Puzzle>( 5);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day06Puzzle>( 6);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day07Puzzle>( 7);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day08Puzzle>( 8);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day09Puzzle>( 9);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day10Puzzle>(10);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day11Puzzle>(11);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day12Puzzle>(12);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day13Puzzle>(13);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day14Puzzle>(14);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day15Puzzle>(15);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day16Puzzle>(16);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day17Puzzle>(17);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day18Puzzle>(18);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day19Puzzle>(19);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day20Puzzle>(20);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day21Puzzle>(21);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day22Puzzle>(22);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day23Puzzle>(23);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day24Puzzle>(24);
    core::PuzzleConstructor::registerPuzzle<TwentyNineteen::Day25Puzzle>(25);

	core::IPuzzleBase *puzzle = core::PuzzleConstructor::createPuzzle(core::InitialisationInfo::parseArguments(_argc, _argv));

	if (puzzle == nullptr) {
		return EXIT_FAILURE;
	}

	std::cout << "Puzzle " << puzzle->getPuzzleYear() << " - Day " << puzzle->getPuzzleDay() << " - " << puzzle->getPuzzleName() << std::endl;

	auto t1 = std::chrono::high_resolution_clock::now();
	const std::pair<std::string, std::string>& solution = puzzle->fastSolve();
	auto t2 = std::chrono::high_resolution_clock::now();

	std::cout << "Part 1: " << solution.first << std::endl << "Part 2: " << solution.second << std::endl;
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	if (duration != 0) {
		std::cout << "In " << duration << "ms" << std::endl;
	} else {
		std::cout << "In " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " micro seconds" << std::endl;
	}

	delete puzzle;

	return EXIT_SUCCESS;
}