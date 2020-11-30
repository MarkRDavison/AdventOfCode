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
		self.createHeaderFolder()
		self.createSourceFolder()
		fileName = self.root + '\\lib\\year' + str(self.year) + '\\CMakeLists.txt'
		f = open(fileName,"w+")
		
		f.write('SET(MODULE_NAME "Year{year}")\n'.format(year=self.year))
		f.write('STRING(TOLOWER ${MODULE_NAME} MODULE_NAME_LOWER)\n')
		f.write('SET(LIB_NAME "advent-of-code-${MODULE_NAME_LOWER}${LIBRARY_EXTENSION}")\n')
		f.write('\n')
		f.write('SET(LIBRARY_MODULE_PATH "${PROJECT_SOURCE_DIR}/lib/${MODULE_NAME_LOWER}")\n')
		f.write('SET(LIBRARY_SRC_PATH "${LIBRARY_MODULE_PATH}/src" )\n')
		f.write('SET(LIBRARY_INCLUDE_PATH "${LIBRARY_MODULE_PATH}/include")\n')
		f.write('\n')
		f.write('FILE(GLOB_RECURSE LIB_HEADER_FILES "${LIBRARY_INCLUDE_PATH}/${MODULE_NAME}/*.hpp")\n')
		f.write('FILE(GLOB_RECURSE LIB_INLINE_FILES "${LIBRARY_INCLUDE_PATH}/${MODULE_NAME}/*.inl")\n')
		f.write('FILE(GLOB_RECURSE LIB_SOURCE_FILES "${LIBRARY_SRC_PATH}/*.cpp")\n')
		f.write('\n')
		f.write('SET(LIB_HEADER_FILES ${LIB_HEADER_FILES} ${LIB_INLINE_FILES})\n')
		f.write('\n')
		f.write('ADD_LIBRARY(${LIB_NAME} ${LIB_SOURCE_FILES} ${LIB_HEADER_FILES})\n')
		f.write('TARGET_INCLUDE_DIRECTORIES(${LIB_NAME} PUBLIC ${LIBRARY_INCLUDE_PATH})\n')
		f.write('TARGET_LINK_LIBRARIES(${LIB_NAME} PUBLIC advent-of-code-core)\n')
		f.write('TARGET_LINK_LIBRARIES(${LIB_NAME} PUBLIC zeno)\n')

		f.close()
		

	def createHeaderFiles(self):
		self.createPuzzlesHeaderFile()
		for i in range(1, 26):
			self.createHeaderFile(i)

	def createHeaderFolder(self):
		os.makedirs(self.root + '\\lib\\year' + str(year) + '\\include\\' + str(year))
		
	def createPuzzlesHeaderFile(self):
		fileName = self.root + '\\lib\\year' + str(self.year) + '\\include\\Puzzles{year}.hpp'.format(year=self.year)
		
		f = open(fileName,"w+")

		f.write('#ifndef INCLUDED_ADVENT_OF_CODE_PUZZLES_{year}_HPP_\n'.format(year=year))
		f.write('#define INCLUDED_ADVENT_OF_CODE_PUZZLES_{year}_HPP_\n'.format(year=year))
		f.write('\n')

		for day in range(1, 26):
			dayStr = '0' + str(day) if day < 10 else str(day)
			f.write('#include <{year}/Day{dayStr}Puzzle.hpp>\n'.format(dayStr=dayStr, year=year))

		f.write('\n')
		f.write('#endif // INCLUDED_ADVENT_OF_CODE_PUZZLES_{year}_HPP_\n'.format(year=year))

		f.close()

	def createHeaderFile(self, day):
		fileName = self.root + '\\lib\\year' + str(self.year) + '\\include\\'  + str(self.year) + '\\' + self.createHeaderFileName(day)
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
		f.write('		~Day{day}Puzzle() override = default;\n'.format(day=dayStr))
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
		for i in range(1, 26):
			self.createSourceFile(i)
			
	def createSourceFolder(self):
		os.makedirs(self.root + '\\lib\\year' + str(year) + '\\src\\')

	def createSourceFile(self, day):
		fileName = self.root + '\\lib\\year' + str(year) + '\\src\\' + self.createSourceFileName(day)
		dayStr = '0' + str(day) if day < 10 else str(day)
		f = open(fileName,"w+")

		f.write('#include <{year}/Day{day}Puzzle.hpp>\n'.format(year=self.year, day=dayStr))
		f.write('#include <zeno/Utility/StringExtensions.hpp>\n')
		f.write('\n')
		f.write('namespace {ns} {{\n'.format(ns=self.createNamespace()))
		f.write('	\n')
		f.write('	Day{day}Puzzle::Day{day}Puzzle() :\n'.format(day=dayStr))
		f.write('		core::PuzzleBase("Untitled Puzzle", {year}, {day}) {{\n'.format(year=self.year, day=day))
		f.write('	}\n')
		f.write('\n')
		f.write('\n')
		f.write('	void Day{day}Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {{\n'.format(day=dayStr))
		f.write('		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\\n"));\n')
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

		
		fileName = self.root + '\\test\\' + str(year) + '\\CMakeLists.txt'
		f = open(fileName,"w+")

		f.write('SET(MODULE_NAME "Year{year}")\n'.format(year=self.year))
		f.write('STRING(TOLOWER ${MODULE_NAME} MODULE_NAME_LOWER)\n')
		f.write('SET(EXE_NAME "advent-of-code-${MODULE_NAME_LOWER}-test")\n')
		f.write('SET(LIB_NAME "advent-of-code-${MODULE_NAME_LOWER}")\n')
		f.write('\n')
		f.write('FILE(GLOB_RECURSE LIB_TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")\n')
		f.write('\n')
		f.write('ADD_EXECUTABLE(${EXE_NAME} "../main.cpp" ${LIB_TEST_FILES})\n')
		f.write('TARGET_LINK_LIBRARIES(${EXE_NAME} PUBLIC advent-of-code-core)\n')
		f.write('TARGET_LINK_LIBRARIES(${EXE_NAME} PUBLIC "advent-of-code-${MODULE_NAME_LOWER}")\n')
		f.write('TARGET_LINK_LIBRARIES(${EXE_NAME} PUBLIC zeno)\n')
		f.write('TARGET_INCLUDE_DIRECTORIES(${EXE_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/thirdparty/catch/include")\n')
		f.write('SET_PROPERTY(TARGET ${EXE_NAME} PROPERTY CXX_STANDARD 17)\n')
		f.write('SET_PROPERTY(TARGET ${EXE_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)\n')
		f.write('\n')
		f.write('ParseAndAddCatchTests(${EXE_NAME})\n')

		f.close()

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

	print('Generating Skeleton for ', year)

	gen.createCoreFile()
	gen.createHeaderFiles()
	gen.createSourceFiles()
	gen.createTestFiles()