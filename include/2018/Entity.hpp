#ifndef INCLUDED_ADVENT_OF_CODE_2018_ENTITY_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_ENTITY_HPP_

#include <SFML/System/Vector2.hpp>
#include <memory>

namespace TwentyEighteen {
	
	struct Entity {

		enum class EntityTeam {
			Goblin,
			Elf
		} team;

		Entity(EntityTeam _team, int _attackPower, const sf::Vector2i& _position) : team(_team), attackPower(_attackPower), position(_position) {}

		static EntityTeam getOppositeTeam(EntityTeam _team) {
			return _team == EntityTeam::Elf ? EntityTeam::Goblin : EntityTeam::Elf;
		}

		bool hadTurn{ false };
		int attackPower;
		int health{ 200 };

		sf::Vector2i position;
	};

	using EntityPtr = std::shared_ptr<Entity>;
	using WeakEntityPtr = std::weak_ptr<Entity>;

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_ENTITY_HPP_