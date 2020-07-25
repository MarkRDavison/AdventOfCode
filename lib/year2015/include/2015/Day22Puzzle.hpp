#ifndef INCLUDED_ADVENT_OF_CODE_2015_DAY_22_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2015_DAY_22_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>

namespace TwentyFifteen {

	struct Spell {
		enum class Type {
			MagicMissile,
			Drain,
			Shield,
			Poison,
			Recharge
		} type;

		Spell(Type _type, int _cost) :
			type(_type),
			cost(_cost),
			damage(0),
			heal(0){

		}
		Spell(Type _type, int _heal, int _damage, int _cost) :
			type(_type),
			damage(_damage),
			heal(_heal),
			cost(_cost) {

		}
		
		int damage;
		int heal;
		int cost;
	};
	struct Player {
		int hp; 
		int mana;
		int armour;

		bool hardMode{ false };
		bool recharging{ false };
		bool shielded{ false };
		int rechargeRemaining{ 0 };
		int shieldRemaining{ 0 };
	};
	struct Wizard {
		int hp;
		int damage;
		bool poisoned{ false };
		int poisonRemaining{ 0 };
	};
	using SpellList = std::vector<unsigned>;

	struct WizardBattleResult {
		bool victory{ false };
		int manacost;
		SpellList spells;
	};

	class Day22Puzzle : public core::PuzzleBase {
	public:
		Day22Puzzle();
		~Day22Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static int getLeastManaToStillWin(int _playerHp, int _playerMana, int _bossHp, int _bossDamage, bool _hardMode);

		static void doSpellList(int _playerHp, int _playerMana, int _bossHp, int _bossDamage, bool _hardMode, const SpellList& _spells);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2015_DAY_22_PUZZLE_HPP_