#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_10_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_10_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>

namespace TwentySixteen {
	
	class Day10Puzzle : public core::PuzzleBase {
	public:
		Day10Puzzle();
		~Day10Puzzle() override;

		struct Robot {
			int id;
			std::vector<int> input;

			enum class OutputType {
				Robot,
				Output,
				None
			};

			OutputType high{ OutputType::None };
			OutputType low{ OutputType::None };
			int highOutputNumber;
			int lowOutputNumber;

			int process1;
			int process2;
		};

		struct RobotInfo {
			std::unordered_map<int, Robot> robots;
			std::unordered_map<int, int> output;
		};

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static RobotInfo initialiseRobotInfo(const std::vector<std::string>& _input);
		static void iterateProcess(RobotInfo& _info);
		static int getRobotNumberProcessingMicrochips(const RobotInfo& _info, int _first, int _second);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_10_PUZZLE_HPP_