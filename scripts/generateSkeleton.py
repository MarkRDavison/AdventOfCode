import sys
import os

def intTryParse(value):
    try:
        return int(value)
    except ValueError:
        return -1

class SkeletonGenerator:
	def __init__(self, year):
		cwd = os.getcwd()
		self.year = year
		self.root = cwd[:cwd.rfind('\\') + 1]

	def alreadyPresent(self):
		return os.path.isfile(self.root + self.createCoreFileName()) 

	def createCoreFileName(self):
		return 'AdventOfCode{y}.cpp'.format(y=self.year)

	def createHeaderFileName(self, day):	
		dayStr = '0' + str(day) if day < 10 else str(day)
		return 'Day' + dayStr + 'Puzzle.hpp'

	def createSourceFileName(self, day):	
		dayStr = '0' + str(day) if day < 10 else str(day)
		return 'Day' + dayStr + 'Puzzle.cpp'

	def createTestMainFileName(self):
		return 'AdventOfCode' + str(self.year) + 'Test.cpp'

	def createTestSourceFileName(self, day):	
		dayStr = '0' + str(day) if day < 10 else str(day)
		return 'Day' + dayStr + 'PuzzleTests.cpp'

	def createNamespace(self):
		if (self.year == 2015):
			return 'TwentyFifteen'
		if (self.year == 2016):
			return 'TwentySixteen'
		if (self.year == 2017):
			return 'TwentySeventeen'
		if (self.year == 2018):
			return 'TwentyEighteen'
		if (self.year == 2019):
			return 'TwentyNineteen'
		if (self.year == 2020):
			return 'TwentyTwenty'
		if (self.year == 2021):
			return 'TwentyTwentyOne'
		if (self.year == 2022):
			return 'TwentyTwentyTwo'
		if (self.year == 2023):
			return 'TwentyTwentyThree'
		if (self.year == 2024):
			return 'TwentyTwentyFour'
		if (self.year == 2025):
			return 'TwentyTwentyFive'
		return 'UPDATE_THE_GEN_FILE_PLEASE_'

	def createCoreFile(self):
		fileName = self.root + self.createCoreFileName()
		f = open(fileName,"w+")
		
		f.write('#include <Core/PuzzleConstructor.hpp>\n')
		f.write('\n')
		f.write('#include <iostream>\n')
		f.write('#include <chrono>\n')
		f.write('\n')
		f.write('#include <{y}/Day01Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day02Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day03Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day04Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day05Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day06Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day07Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day08Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day09Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day10Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day11Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day12Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day13Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day14Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day15Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day16Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day17Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day18Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day19Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day20Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day21Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day22Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day23Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day24Puzzle.hpp>\n'.format(y=self.year))
		f.write('#include <{y}/Day25Puzzle.hpp>\n'.format(y=self.year))
		f.write('\n')
		f.write('int main(int _argc, char **_argv) {\n')
		f.write('\n')
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day01Puzzle>( 1);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day02Puzzle>( 2);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day03Puzzle>( 3);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day04Puzzle>( 4);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day05Puzzle>( 5);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day06Puzzle>( 6);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day07Puzzle>( 7);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day08Puzzle>( 8);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day09Puzzle>( 9);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day10Puzzle>(10);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day11Puzzle>(11);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day12Puzzle>(12);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day13Puzzle>(13);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day14Puzzle>(14);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day15Puzzle>(15);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day16Puzzle>(16);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day17Puzzle>(17);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day18Puzzle>(18);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day19Puzzle>(19);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day20Puzzle>(20);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day21Puzzle>(21);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day22Puzzle>(22);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day23Puzzle>(23);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day24Puzzle>(24);\n'.format(ns=self.createNamespace()))
		f.write('    core::PuzzleConstructor::registerPuzzle<{ns}::Day25Puzzle>(25);\n'.format(ns=self.createNamespace()))
		f.write('\n')
		f.write('	core::IPuzzleBase *puzzle = core::PuzzleConstructor::createPuzzle(core::InitialisationInfo::parseArguments(_argc, _argv));\n')
		f.write('\n')
		f.write('	if (puzzle == nullptr) {\n')
		f.write('		return EXIT_FAILURE;\n')
		f.write('	}\n')
		f.write('\n')
		f.write('	auto start = std::chrono::high_resolution_clock::now();')
		f.write('\n')
		f.write('	std::cout << "Puzzle " << puzzle->getPuzzleYear() << " - Day " << puzzle->getPuzzleDay() << " - " << puzzle->getPuzzleName() << std::endl;\n')
		f.write('\n')
		f.write('	const std::pair<std::string, std::string>& solution = puzzle->fastSolve();\n')
		f.write('\n')
		f.write('	std::cout << "Part 1: " << solution.first << std::endl << "Part 2: " << solution.second << std::endl;\n')
		f.write('\n')
		f.write('	auto elapsed = std::chrono::high_resolution_clock::now() - start;\n')
		f.write('   long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();')
		f.write('	std::cout << "In " << microseconds << "ms." << std::endl;')
		f.write('\n')
		f.write('	delete puzzle;\n')
		f.write('\n')
		f.write('	return EXIT_SUCCESS;\n')
		f.write('}')

		f.close()

	def createHeaderFiles(self):
		self.createHeaderFolder()
		for i in range(1, 26):
			self.createHeaderFile(i)

	def createHeaderFolder(self):
		os.makedirs(self.root + '\\include\\' + str(year))

	def createHeaderFile(self, day):
		fileName = self.root + '\\include\\' + str(self.year) + '\\' + self.createHeaderFileName(day)
		dayStr = '0' + str(day) if day < 10 else str(day)
		f = open(fileName,"w+")

		f.write('#ifndef INCLUDED_ADVENT_OF_CODE_{year}_DAY_{day}_PUZZLE_HPP_\n'.format(year=self.year, day=dayStr))
		f.write('#define INCLUDED_ADVENT_OF_CODE_{year}_DAY_{day}_PUZZLE_HPP_\n'.format(year=self.year, day=dayStr))
		f.write('\n')
		f.write('#include <Core/PuzzleBase.hpp>\n')
		f.write('\n')
		f.write('namespace {ns} {{\n'.format(ns=self.createNamespace()))
		f.write('	\n')
		f.write('	class Day{day}Puzzle : public core::PuzzleBase {{\n'.format(day=dayStr))
		f.write('	public:\n')
		f.write('		Day{day}Puzzle();\n'.format(day=dayStr))
		f.write('		~Day{day}Puzzle() override;\n'.format(day=dayStr))
		f.write('\n')
		f.write('		void initialise(const core::InitialisationInfo& _initialisationInfo) override;\n')
		f.write('		void setInputLines(const std::vector<std::string>& _inputLines);\n')
		f.write('		std::pair<std::string, std::string> fastSolve() override;\n')
		f.write('\n')
		f.write('	private:\n')
		f.write('		std::vector<std::string> m_InputLines;\n')
		f.write('	};\n')
		f.write('\n')
		f.write('}\n')
		f.write('\n')
		f.write('#endif // INCLUDED_ADVENT_OF_CODE_{year}_DAY_{day}_PUZZLE_HPP_'.format(year=self.year, day=dayStr))

		f.close()

	def createSourceFiles(self):
		self.createSourceFolder()
		for i in range(1, 26):
			self.createSourceFile(i)
			
	def createSourceFolder(self):
		os.makedirs(self.root + '\\src\\' + str(year))

	def createSourceFile(self, day):
		fileName = self.root + '\\src\\' + str(self.year) + '\\' + self.createSourceFileName(day)
		dayStr = '0' + str(day) if day < 10 else str(day)
		f = open(fileName,"w+")

		f.write('#include <{year}/Day{day}Puzzle.hpp>\n'.format(year=self.year, day=dayStr))
		f.write('#include <Core/StringExtensions.hpp>\n')
		f.write('\n')
		f.write('namespace {ns} {{\n'.format(ns=self.createNamespace()))
		f.write('	\n')
		f.write('	Day{day}Puzzle::Day{day}Puzzle() :\n'.format(day=dayStr))
		f.write('		core::PuzzleBase("Untitled Puzzle", {year}, {day}) {{\n'.format(year=self.year, day=day))
		f.write('\n')
		f.write('	}\n')
		f.write('	Day{day}Puzzle::~Day{day}Puzzle() {{\n'.format(day=dayStr))
		f.write('\n')
		f.write('	}\n')
		f.write('\n')
		f.write('\n')
		f.write('	void Day{day}Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {{\n'.format(day=dayStr))
		f.write('		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\\n"));\n')
		f.write('	}\n')
		f.write('\n')
		f.write('	void Day{day}Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {{\n'.format(day=dayStr))
		f.write('		m_InputLines = std::vector<std::string>(_inputLines);\n')
		f.write('	}\n')
		f.write('\n')
		f.write('	std::pair<std::string, std::string> Day{day}Puzzle::fastSolve() {{\n'.format(day=dayStr))
		f.write('		return { "Part 1", "Part 2" };\n')
		f.write('	}\n')
		f.write('}\n')

		f.close()

	def createTestFiles(self):
		self.createTestFolder()
		self.createTestMainFile()
		for i in range(1, 26):
			self.createTestFile(i)

	def createTestMainFile(self):		
		fileName = self.root + 'test\\' + self.createTestMainFileName()
		f = open(fileName,"w+")
		f.write('#define CATCH_CONFIG_MAIN\n')
		f.write('#include <catch/catch.hpp>')
		f.close()

	def createTestFolder(self):
		os.makedirs(self.root + '\\test\\' + str(year))

	def createTestFile(self, day):
		fileName = self.root + '\\test\\' + str(self.year) + '\\' + self.createTestSourceFileName(day)
		dayStr = '0' + str(day) if day < 10 else str(day)
		f = open(fileName,"w+")

		f.write('#include <catch/catch.hpp>\n')
		f.write('#include <{year}/Day{day}Puzzle.hpp>\n'.format(year=self.year, day=dayStr))
		f.write('\n')
		f.write('namespace {ns} {{\n'.format(ns=self.createNamespace()))
		f.write('\n')
		f.write('	TEST_CASE("Day {d} Part 1 Example work", "[{year}][Day{day}]") {{\n'.format(year=self.year, day=dayStr, d=day))
		f.write('	    const std::vector<std::string> input = {};\n')
		f.write('\n')
		f.write('	    Day{day}Puzzle puzzle{{}};\n'.format(day=dayStr))
		f.write('	    puzzle.setVerbose(true);\n')
		f.write('	    puzzle.setInputLines(input);\n')
		f.write('\n')
		f.write('	    auto answers = puzzle.fastSolve();\n')
		f.write('	}\n')
		f.write('\n')
		f.write('	TEST_CASE("Day {d} Part 2 Example work", "[{year}][Day{day}]") {{\n'.format(year=self.year, day=dayStr, d=day))
		f.write('	    const std::vector<std::string> input = {};\n')
		f.write('\n')
		f.write('	    Day{day}Puzzle puzzle{{}};\n'.format(day=dayStr))
		f.write('	    puzzle.setVerbose(true);\n')
		f.write('	    puzzle.setInputLines(input);\n')
		f.write('\n')
		f.write('	    auto answers = puzzle.fastSolve();\n')
		f.write('	}\n')
		f.write('\n')
		f.write('}\n')

		f.close()

if __name__ == '__main__':
	if (len(sys.argv) != 2):
		print('Please execute with the desired year only')
		exit()

	year  = intTryParse(sys.argv[1])
	if (year < 2015):
		print('Please enter a valid year')
		exit()

	gen = SkeletonGenerator(year)
	if (gen.alreadyPresent()):
		print('Skeleton for {y} is already present, exiting...'.format(y=year))
		exit()

	print('Generating Skeleton for ', year)

	gen.createCoreFile()
	gen.createHeaderFiles()
	gen.createSourceFiles()
	gen.createTestFiles()