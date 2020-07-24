#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_21_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_21_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyFifteen {

	struct Item {
		enum class Type {
			Weapon,
			Armour,
			Ring
		} type;
		int cost;
		int effect;
		bool damage;
		int id;
		std::string name;

		int operator<(const Item& _other) const {
			return id < _other.id;
		}
	};
	struct CharacterStats {
		int hp;
		int damage;
		int armour;
	};
	
	using BattleResult = std::pair<std::vector<Item>, int>;
	using BestWorstBattlesResults = std::pair< BattleResult, BattleResult>;

	class Day21Puzzle : public core::PuzzleBase {
	public:
		Day21Puzzle();
		~Day21Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static bool doesPlayerWin(const CharacterStats _player, const CharacterStats _boss);

		static BestWorstBattlesResults findBestBattles(const CharacterStats _boss, const CharacterStats _player, const std::vector<Item>& _items);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_21_PUZZLE_HPP_