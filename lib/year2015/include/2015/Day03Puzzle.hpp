#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_03_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_03_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Orientation.hpp>
#include <unordered_map>

namespace TwentyFifteen {

	
	class Day03Puzzle : public core::PuzzleBase {
		template<typename T>
		struct vector2_hash_fxn {
			std::size_t operator()(const ze::Vector2<T>& _vec) const {
				return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y);
			}
		};
	public:

		using VisitMap = std::unordered_map<ze::Vector2i, int, vector2_hash_fxn<int>>;
		Day03Puzzle();
		~Day03Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static core::Orientation getOrientation(char _c);
		static VisitMap visitLocations(const std::string& _directions, unsigned _santas);

		static int getResult(const VisitMap& _map);

	private:

		std::vector<std::string> m_InputLines;

	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_03_PUZZLE_HPP_