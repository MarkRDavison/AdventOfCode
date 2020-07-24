#include <2015/Day21Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <unordered_map>
#include <algorithm>
#include <numeric>

namespace TwentyFifteen {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("RPG Simulator 20XX", 2015, 21) {

	}
	Day21Puzzle::~Day21Puzzle() {

	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
		std::vector<Item> weapons = {
			Item{Item::Type::Weapon,   8, 4,  true,  0, "Dagger"},
			Item{Item::Type::Weapon,  10, 5,  true,  1, "Shortsword"},
			Item{Item::Type::Weapon,  25, 6,  true,  2, "Warhammer"},
			Item{Item::Type::Weapon,  40, 7,  true,  3, "Longsword"},
			Item{Item::Type::Weapon,  74, 8,  true,  4, "Greataxe"},
		};
		std::vector<Item> armour = {
			Item{Item::Type::Armour,  13, 1, false,  5, "Leather"},
			Item{Item::Type::Armour,  31, 2, false,  6, "Chainmail"},
			Item{Item::Type::Armour,  53, 3, false,  7, "Splintmain"},
			Item{Item::Type::Armour,  57, 4, false,  8, "Bandedmail"},
			Item{Item::Type::Armour, 100, 5, false,  9, "Platemail"},
		};
		std::vector<Item> rings = {
			Item{Item::Type::Ring,    25, 1,  true, 10, "Damage +1"},
			Item{Item::Type::Ring,    50, 2,  true, 11, "Damage +2"},
			Item{Item::Type::Ring,   100, 3,  true, 12, "Damage +3"},
			Item{Item::Type::Ring,    20, 1, false, 13, "Defense +1"},
			Item{Item::Type::Ring,    40, 2, false, 14, "Defense +2"},
			Item{Item::Type::Ring,    80, 3, false, 15, "Defense +3"},
		};
		std::vector<Item> items;
		for (const auto& i : weapons) { items.push_back(i); }
		for (const auto& i : armour) { items.push_back(i); }
		for (const auto& i : rings) { items.push_back(i); }		

		CharacterStats boss;
		boss.hp = std::stoi(ze::StringExtensions::splitStringByDelimeter(m_InputLines[0], " ").back());
		boss.damage = std::stoi(ze::StringExtensions::splitStringByDelimeter(m_InputLines[1], " ").back());
		boss.armour = std::stoi(ze::StringExtensions::splitStringByDelimeter(m_InputLines[2], " ").back());
		CharacterStats player{ 100,0,0 };

		const auto& result = findBestBattles(boss, player, items);

		std::cout << "Our best battle was using:\n";
		for (const auto& i : result.first.first) {
			std::cout << "\t(" << i.cost << " gold)\t - " << i.name << "\n";
		}
		std::cout << "Our worst battle was using:\n";
		for (const auto& i : result.second.first) {
			std::cout << "\t(" << i.cost << " gold)\t - " << i.name << "\n";
		}

		// part 2: 233 too high
		return { std::to_string(result.first.second), std::to_string(result.second.second) };
	}
	
	bool Day21Puzzle::doesPlayerWin(const CharacterStats _player, const CharacterStats _boss) {
		const int playerDamageToBoss = (std::max(1, _player.damage - _boss.armour));
		const int bossDamageToPlayer = (std::max(1, _boss.damage - _player.armour));

		const int playerTurns = (int)std::ceil(
			static_cast<float>(_boss.hp)
			/
			static_cast<float>(playerDamageToBoss));
		const int bossTurns = (int)std::ceil(
			static_cast<float>(_player.hp)
			/
			static_cast<float>(bossDamageToPlayer));

		return playerTurns <= bossTurns;
	}
	BestWorstBattlesResults Day21Puzzle::findBestBattles(const CharacterStats _boss, const CharacterStats _player, const std::vector<Item>& _items){
		std::vector<Item> items(_items);
		const int NumberWeapons = 1;
		const int MaxNumberArmour = 1;
		const int MaxNumberRings = 2;

		const auto isValidConfig = [&](const std::vector<Item>& _currentItems) -> bool {
			int rings = 0;
			int armour = 0;
			int weapons = 0;
			for (const auto& item : _currentItems) {
				switch (item.type) {
				case Item::Type::Weapon:
					weapons++; break;
				case Item::Type::Armour:
					armour++; break;
				case Item::Type::Ring:
					rings++; break;
				}
			}

			if (rings > MaxNumberRings ||
				armour > MaxNumberArmour ||
				weapons != NumberWeapons) {
				return false;
			}

			return true;
		};
		const auto canWinWithItems = [&isValidConfig, &_boss, &_player](const std::vector<Item>& _currentItems, int& _cost) -> bool {
			if (!isValidConfig(_currentItems)) {
				return false;
			}

			CharacterStats player(_player);
			_cost = 0;
			for (const auto& item : _currentItems) {
				if (item.damage) {
					player.damage += item.effect;
				} else {
					player.armour += item.effect;
				}
				_cost += item.cost;
			}

			return Day21Puzzle::doesPlayerWin(player, _boss);
		}; 
		

		const unsigned TotalNumElements = items.size();
		const unsigned MaxTotalItems = MaxNumberRings + MaxNumberArmour + NumberWeapons;

		int minCost = std::numeric_limits<int>::max();
		int maxCost = std::numeric_limits<int>::min();
		std::vector<Item> bestItems;
		std::vector<Item> worstItems;
		for (unsigned perm = 1; perm <= MaxTotalItems; ++perm) {
			do {
				int cost = 0;
				const std::vector<Item> itms(items.begin(), items.begin() + perm);
				if (canWinWithItems(itms, cost)) {
					if (minCost > cost) {
						minCost = cost;
						bestItems = std::vector<Item>(itms);
					}
				}
				else {
					if (maxCost < cost) {
						maxCost = cost;
						worstItems = std::vector<Item>(itms);
					}
				}
				std::reverse(items.begin() + perm, items.end());
			} while (std::next_permutation(items.begin(), items.end()));
		}

		BattleResult winResult;
		winResult.first = bestItems;
		winResult.second = minCost;
		BattleResult loseResult;
		loseResult.first = worstItems;
		loseResult.second = maxCost;
		return { winResult, loseResult };
	}
}
