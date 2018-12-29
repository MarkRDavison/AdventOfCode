#ifndef INCLUDED_ADVENT_OF_CODE_2018_CAVE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_CAVE_HPP_

#include <2018/Entity.hpp>
#include <string>
#include <vector>

namespace TwentyEighteen {

	const std::vector<sf::Vector2i> offsets {
		{0,-1},{-1,0},{+1,0},{0,+1}
	};

	struct CaveCell {

		WeakEntityPtr entity;
		
		enum class CellType {
			Wall,
			Empty
		} cellType{ CellType::Wall };

		int neighbourOfElf{ 0 };
		int neighbourOfGoblin{ 0 };

	};

	class Cave {
	public:
		Cave(const std::vector<std::string>& _rows, int _elfAttack);

		const std::size_t Width;
		const std::size_t Height;

		CaveCell& getCell(std::size_t _x, std::size_t _y);
		const CaveCell& getCell(std::size_t _x, std::size_t _y) const;

		std::vector<std::string> dumpCurrentState(bool _includeHealth = true) const;
		bool doesCurrentStateMatch(const std::vector<std::string>& _state) const;

		void doTurn(void);

		EntityPtr findNextEntity();

		void setEntityAt(EntityPtr _entity, Entity::EntityTeam _team);
		void unsetEntityAt(EntityPtr _entity, Entity::EntityTeam _team);

		sf::Vector2u getEntitiesMovementTarget(EntityPtr _entity);
		bool isEntityNextToEnemy(const EntityPtr& _entity) const;
		bool doesEntityHaveTargets(const EntityPtr& _entity) const;

		std::vector<sf::Vector2u> getInRangeCells(Entity::EntityTeam _team);

		void moveEntityToCoordinate(EntityPtr _entity, const sf::Vector2u& _coord);
		void attackWeakestAdjacentEnemy(EntityPtr _entity);

		bool getElfKilled() const noexcept { return m_ElfKilled; }
		bool getComplete() const noexcept { return m_Complete; }
		int getCompletedRound() const noexcept { return m_Round; }
		int getTotalHealthRemaining() const;

	private:
		bool m_Complete{ false };
		int m_Round{ 0 };
		bool m_ElfKilled{ false };
		std::vector<CaveCell> m_Cells;
		std::vector<EntityPtr> m_Entities;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_CAVE_HPP_