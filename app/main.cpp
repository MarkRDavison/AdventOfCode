#include <cstdlib>
#include <iostream>
#include <chrono>
#include <zeno/Core/Clock.hpp>
#include <Core/PuzzleConstructor.hpp>
#include <Puzzles2015.hpp>
#include <Puzzles2016.hpp>
#include <Puzzles2017.hpp>
#include <Puzzles2018.hpp>
#include <Puzzles2019.hpp>

int main(int _argc, char** _argv) {
    REGISTER_YEAR(TwentyFifteen, 2015);
    REGISTER_YEAR(TwentySixteen, 2016);
    REGISTER_YEAR(TwentySeventeen, 2017);
    REGISTER_YEAR(TwentyEighteen, 2018);
    REGISTER_YEAR(TwentyNineteen, 2019);

	core::IPuzzleBase* puzzle = core::PuzzleConstructor::createPuzzle(core::InitialisationInfo::parseArguments(_argc, _argv));

	if (puzzle == nullptr) {
		return EXIT_FAILURE;
	}

    ze::Clock clock;
    std::cout << "Puzzle " << puzzle->getPuzzleYear() << " - Day " << puzzle->getPuzzleDay() << " - " << puzzle->getPuzzleName() << std::endl;

    const std::pair<std::string, std::string>& solution = puzzle->fastSolve();

    std::cout << "Part 1: " << solution.first << std::endl << "Part 2: " << solution.second << std::endl;

    std::cout << "In " << clock.getElapsedTime() << "s." << std::endl;
    delete puzzle;
    getchar();

	return EXIT_SUCCESS;
}