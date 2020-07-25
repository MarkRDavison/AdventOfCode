#include <2015/Day22Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <functional>
#include <algorithm>
#include <cassert>

constexpr const int POISON_TICK{ 3 };
constexpr const int POISON_DURATION{ 6 };
constexpr const int RECHARGE_TICK{ 101 };
constexpr const int RECHARGE_DURATION{ 5 };
constexpr const int SHIELD_BOOST{ 7 };
constexpr const int SHIELD_DURATION{ 6 };
constexpr const bool VERBOSE{ false };
constexpr const bool VERBOSE_VICTORY{ false };
constexpr const bool VERBOSE_DEFEAT{ false };

static int CURRENT_BEST{ std::numeric_limits<int>::max() };

namespace TwentyFifteen {

	const std::vector<Spell> SPELLS{
		Spell(Spell::Type::MagicMissile, 0, 4, 53),
		Spell(Spell::Type::Drain, 2, 2, 73),
		Spell(Spell::Type::Shield, 113),
		Spell(Spell::Type::Poison, 173),
		Spell(Spell::Type::Recharge, 229)
	};
	
	Day22Puzzle::Day22Puzzle() :
		core::PuzzleBase("Wizard Simulator 20XX", 2015, 22) {

	}
	Day22Puzzle::~Day22Puzzle() {

	}


	void Day22Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day22Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::string getSpellName(Spell::Type _type) {
		switch (_type) {
		case Spell::Type::MagicMissile:
			return "Magic Missile";
		case Spell::Type::Drain:
			return "Drain";
		case Spell::Type::Shield:
			return "Shield";
		case Spell::Type::Poison:
			return "Poison";
		case Spell::Type::Recharge:
			return "Recharge";
		default:
			return "Invalid spell";
		}
	}

	bool applyBossEffects(Wizard& _wizard) {
		if (_wizard.poisoned) {
			_wizard.hp -= POISON_TICK;
			_wizard.poisonRemaining -= 1;
			if (VERBOSE) std::cout << "Poison deals " << POISON_TICK << " damage";
			if (_wizard.hp > 0) {
				if (VERBOSE)std::cout << "; its timer is now " << _wizard.poisonRemaining << "." << std::endl;
			} else {
				if (VERBOSE)std::cout << ". This kills the boss, and the player wins." << std::endl << std::endl;
				return true;
			}
			if (_wizard.poisonRemaining <= 0) {
				if (VERBOSE)std::cout << "Poison wears off." << std::endl;
				_wizard.poisoned = false;
			}
		}


		return false;
	};
	
	bool applyPlayerEffects(Player& _player) {
		if (_player.shielded) {
			_player.shieldRemaining -= 1;
			if (VERBOSE)std::cout << "Shield's timer is now " << _player.shieldRemaining << "." << std::endl;
			if (_player.shieldRemaining <= 0) {
				if (VERBOSE)std::cout << "Shield wears off, decreasing armour by " << SHIELD_BOOST << "." << std::endl;
				_player.shielded = false;
				_player.armour -= SHIELD_BOOST;
			}
		}

		if (_player.recharging) {
			_player.rechargeRemaining -= 1;
			_player.mana += RECHARGE_TICK;
			if (VERBOSE)std::cout << "Recharge provides " << RECHARGE_TICK << " mana; its timer is now " << _player.rechargeRemaining << "." << std::endl;
			if (_player.rechargeRemaining <= 0) {
				if (VERBOSE)std::cout << "Recharge wears off." << std::endl;
				_player.recharging = false;
			}
		}

		return false;
	}
	
	void doBossTurn(Wizard& _wizard, Player& _player) {
		if (VERBOSE)std::cout << "-- Boss turn --" << std::endl;
		if (VERBOSE)std::cout << "- Player has " << _player.hp << " hit points, " << _player.armour << " armor, " << _player.mana << " mana" << std::endl;
		if (VERBOSE)std::cout << "- Boss has " << _wizard.hp << " hit points" << std::endl;
		if (applyPlayerEffects(_player)) { return; }
		if (applyBossEffects(_wizard)) { return; }
		int damage = _wizard.damage;
		if (VERBOSE)std::cout << "Boss attacks for " << damage;
		if (_player.armour > 0) {
			damage = std::max(1, damage - _player.armour);
			if (VERBOSE)std::cout << " - " << _player.armour << " = " << damage;
		}
		if (VERBOSE)std::cout << " damage!" << std::endl;
		_player.hp -= damage;
		if (VERBOSE)std::cout << std::endl;
	}
	
	void doPlayerTurn(Wizard& _wizard, Player& _player, const Spell& _spell, int& _playerManaSpent) {
		if (VERBOSE)std::cout << "-- Player turn --" << std::endl;
		if (VERBOSE)std::cout << "- Player has " << _player.hp << " hit points, " << _player.armour << " armor, " << _player.mana << " mana" << std::endl;
		if (VERBOSE)std::cout << "- Boss has " << _wizard.hp << " hit points" << std::endl;

		if (_player.hardMode) {
			_player.hp -= 1;
			if (VERBOSE)std::cout << "HARD MODE - Player loses 1hp, now on " << _player.hp << std::endl;;
			if (_player.hp <= 0) {
				return;
			}
		}

		if (applyBossEffects(_wizard)) { return; }
		if (applyPlayerEffects(_player)) { return; }
		if (VERBOSE)std::cout << "Player casts " << getSpellName(_spell.type);
		_playerManaSpent += _spell.cost;
		_player.mana -= _spell.cost;
		if (_spell.damage > 0) {
			if (VERBOSE)std::cout << ", dealing " << _spell.damage << " damage";
			_wizard.hp -= _spell.damage;
		}
		if (_spell.heal > 0) {
			if (VERBOSE)std::cout << ", healing " << _spell.heal << " hit points";
			_player.hp += _spell.heal;
		}

		switch (_spell.type) {
		case Spell::Type::Poison:
			assert(!_wizard.poisoned);
			_wizard.poisoned = true;
			_wizard.poisonRemaining = POISON_DURATION;
			break;
		case Spell::Type::Shield:
			assert(!_player.shielded);
			_player.shielded = true;
			_player.shieldRemaining = SHIELD_DURATION;
			_player.armour += SHIELD_BOOST;
			if (VERBOSE)std::cout << ", increasing armor by " << SHIELD_BOOST;
			break;
		case Spell::Type::Recharge:
			assert(!_player.recharging);
			_player.recharging = true;
			_player.rechargeRemaining = RECHARGE_DURATION;
			break;
		default:
			break;
		}

		if (VERBOSE)std::cout << "." << std::endl << std::endl;
	}

	bool SpellValid(const Spell& _spell, const Wizard& _wizard, const Player& _player) {
		if (_spell.cost > _player.mana) {
			return false;
		}
		switch (_spell.type) {
		case Spell::Type::MagicMissile:
		case Spell::Type::Drain:
			return true;
		case Spell::Type::Shield:
			if (!_player.shielded) {
				return true;
			}
			return _player.shieldRemaining == 1;		
		case Spell::Type::Recharge:
			if (!_player.recharging) {
				return true;
			}
			return _player.rechargeRemaining == 1;
		case Spell::Type::Poison:
			if (!_wizard.poisoned) {
				return true;
			}
			return _wizard.poisonRemaining == 1;
		default:
			return false;
		}

	}
	
	WizardBattleResult recurser(
		const SpellList& _spells,
		const Wizard& _wizard,
		const Player& _player,
		int _playerManaSpent,
		int _currentBest
		) {
			if (_player.hardMode && _player.hp == 1 ||
				CURRENT_BEST < _playerManaSpent) {
				return WizardBattleResult();
			}
			WizardBattleResult res;
			res.manacost = std::numeric_limits<int>::max();
			res.spells = SpellList(_spells);

			for (unsigned i = 0; i < SPELLS.size(); ++i) {
				const Spell& s = SPELLS[i];
				if (!SpellValid(s, _wizard, _player)) {
					continue;
				}

				SpellList spells(_spells);
				spells.push_back(i);
				Wizard boss(_wizard);
				Player player(_player);
				int playerManaSpent = _playerManaSpent;
				doPlayerTurn(boss, player, s, playerManaSpent);
				if (player.hp <= 0) {
					// BAD NEWS EVERYONE
					if (VERBOSE_DEFEAT) {
						std::cout << "Player died trying:";
						for (const auto& si : spells) {
							std::cout << " " << getSpellName(SPELLS[si].type);
						}
						std::cout << std::endl;
					}
					continue;
				}
				if (boss.hp <= 0) {
					// GOOD NEWS EVERYONE
					if (CURRENT_BEST > playerManaSpent){
						CURRENT_BEST = playerManaSpent;
					}
					if (res.manacost > playerManaSpent) {
						res.manacost = playerManaSpent;
						res.spells = SpellList(_spells);
						res.spells.push_back(i);
						res.victory = true;
						if (VERBOSE_VICTORY) {
							std::cout << "Player won trying (" << res.manacost << " mana)";
							for (const auto& si : res.spells) {
								std::cout << " - " << getSpellName(SPELLS[si].type);
							}
							std::cout << std::endl;
						}
					}
					continue;
				}
				doBossTurn(boss, player);
				if (player.hp <= 0) {
					// BAD NEWS EVERYONE
					if (VERBOSE_DEFEAT) {
						std::cout << "Player died trying:";
						for (const auto& si : spells) {
							std::cout << " " << getSpellName(SPELLS[si].type);
						}
						std::cout << std::endl;
					}
					continue;
				}
				if (boss.hp <= 0) {
					// GOOD NEWS EVERYONE
					if (CURRENT_BEST > playerManaSpent) {
						CURRENT_BEST = playerManaSpent;
					}
					if (res.manacost > playerManaSpent) {
						res.manacost = playerManaSpent;
						res.spells = SpellList(_spells);
						res.spells.push_back(i);
						res.victory = true;
						if (VERBOSE_VICTORY) {
							std::cout << "Player won trying (" << res.manacost << " mana)";
							for (const auto& si : res.spells) {
								std::cout << " - " << getSpellName(SPELLS[si].type);
							}
							std::cout << std::endl;
						}
						continue;
					}
				}
				if (playerManaSpent < res.manacost) {
					const auto& result = recurser(spells, boss, player, playerManaSpent, res.manacost);
					if (!result.victory) {
						continue;
					}

					if (res.manacost > result.manacost) {
						res.manacost = result.manacost;
						res.spells = result.spells;
						res.victory = true;
					}
				}
			}

			return res;
	}
		


	std::pair<std::string, std::string> Day22Puzzle::fastSolve() {
		const int boss_hp = std::stoi(ze::StringExtensions::splitStringByDelimeter(m_InputLines[0], " ").back());
		const int boss_damage = std::stoi(ze::StringExtensions::splitStringByDelimeter(m_InputLines[1], " ").back());

		CURRENT_BEST = std::numeric_limits<int>::max();
		const int part1 = getLeastManaToStillWin(50, 500, boss_hp, boss_damage, false);
		CURRENT_BEST = std::numeric_limits<int>::max();
		const int part2 = getLeastManaToStillWin(50, 500, boss_hp, boss_damage, true);

		return { std::to_string(part1), std::to_string(part2) };
	}

	int Day22Puzzle::getLeastManaToStillWin(int _playerHp, int _playerMana, int _bossHp, int _bossDamage, bool _hardMode) {

		Wizard boss;
		boss.hp = _bossHp;
		boss.damage = _bossDamage;
		Player player;
		player.hp = _playerHp;
		player.armour = 0;
		player.mana = _playerMana;
		player.hardMode = _hardMode;

		const auto& result = recurser(SpellList(), boss, player, 0, std::numeric_limits<int>::max());

		if (result.victory) {
			return result.manacost;
		}

		return -1;
	}
	
	void Day22Puzzle::doSpellList(int _playerHp, int _playerMana, int _bossHp, int _bossDamage, bool _hardMode, const SpellList& _spells) {

		Wizard boss;
		boss.hp = _bossHp;
		boss.damage = _bossDamage;
		Player player;
		player.hp = _playerHp;
		player.armour = 0;
		player.mana = _playerMana;
		player.hardMode = _hardMode;

		int playerManaSpent = 0;
		for (const auto& si : _spells) {
			const auto& s = SPELLS[si];
			assert(SpellValid(s, boss, player));
			doPlayerTurn(boss, player, s, playerManaSpent);
			if (player.hp <= 0) {
				// BAD NEWS EVERYONE
				break;
			}
			if (boss.hp <= 0) {
				// GOOD NEWS EVERYONE
				break;
			}
			doBossTurn(boss, player);
			if (player.hp <= 0) {
				// BAD NEWS EVERYONE
				break;
			}
			if (boss.hp <= 0) {
				// GOOD NEWS EVERYONE
				break;
			}

		}

	}
}
