#include <catch/catch.hpp>
#include <2015/Day22Puzzle.hpp>

#define MAGIN_MISSILE 0
#define DRAIN 1
#define SHIELD 2
#define POISON 3
#define RECHARGE 4

namespace TwentyFifteen {

	TEST_CASE("2015 Day 22 Part 1 Example 1 works", "[2015][Day22]") {
		const int player_hp = 10;
		const int player_mana = 250;
		const int boss_hp = 13;
		const int boss_damage = 8;
		const bool hard_mode = false;
	
		const int min_mana_spent = Day22Puzzle::getLeastManaToStillWin(
			player_hp, player_mana, boss_hp, boss_damage, hard_mode
		);
	
		REQUIRE(226 == min_mana_spent);
	}

	TEST_CASE("2015 Day 22 Part 1 Example 2 works", "[2015][Day22]") {
		const int player_hp = 10;
		const int player_mana = 250;
		const int boss_hp = 14;
		const int boss_damage = 8;
		const bool hard_mode = false;

		const int min_mana_spent = Day22Puzzle::getLeastManaToStillWin(
			player_hp, player_mana, boss_hp, boss_damage, hard_mode
		);

		REQUIRE(641 == min_mana_spent);
	}

}
