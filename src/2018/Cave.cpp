#include <2018/Cave.hpp>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <numeric>
#include <queue>

namespace TwentyEighteen {

	Cave::Cave(const std::vector<std::string>& _rows, int _elfAttack) :
		Width(_rows.front().size()),
		Height(_rows.size()),
		m_Cells(Width * Height) {

		for (std::size_t y = 0; y < Height; ++y) {
			for (std::size_t x = 0; x < Width; ++x) {
				const char cellChar = _rows[y][x];
				CaveCell& cell = getCell(x, y);

				cell.cellType = cellChar == '#'
					? CaveCell::CellType::Wall 
					: CaveCell::CellType::Empty;

				if (cellChar == 'E') {
					m_Entities.emplace_back(std::make_shared<Entity>(Entity::EntityTeam::Elf, _elfAttack, sf::Vector2i(static_cast<int>(x), static_cast<int>(y))));
					cell.entity = WeakEntityPtr(m_Entities.back());
				}
				if (cellChar == 'G') {
					m_Entities.emplace_back(std::make_shared<Entity>(Entity::EntityTeam::Goblin, 3, sf::Vector2i(static_cast<int>(x), static_cast<int>(y)))); 
					cell.entity = WeakEntityPtr(m_Entities.back());
				}
			}
		}

		for (const EntityPtr e : m_Entities) {
			setEntityAt(e, e->team);
		}
	}

	CaveCell& Cave::getCell(std::size_t _x, std::size_t _y) {
		assert(_x < Width);
		assert(_y < Height);
		
		return m_Cells[_y * Width + _x];
	}
	const CaveCell& Cave::getCell(std::size_t _x, std::size_t _y) const {
		assert(_x < Width);
		assert(_y < Height);

		return m_Cells[_y * Width + _x];
	}

	std::vector<std::string> Cave::dumpCurrentState(bool _includeHealth /*= true*/) const {
		std::vector<EntityPtr> entityCopy(m_Entities);
		std::sort(entityCopy.begin(), entityCopy.end(), [this](const EntityPtr& _lhs, const EntityPtr& _rhs) -> bool {
			return _lhs->position.y * Width + _lhs->position.x < _rhs->position.y * Width + _rhs->position.x;
		});
		std::vector<std::string> actualState;
		for (std::size_t y = 0; y < Height; ++y) {
			std::string row;
			for (std::size_t x = 0; x < Width; ++x) {
				const CaveCell& cell = getCell(x, y);
				if (EntityPtr e = cell.entity.lock()) {
					if (e->team == Entity::EntityTeam::Elf) {
						row += 'E';
					}
					else {
						row += 'G';
					}
				}
				else {
					row += (cell.cellType == CaveCell::CellType::Wall ? '#' : '.');
				}
			}
			bool firstForRow = true;
			for (const EntityPtr& _e : entityCopy) {
				if (_e->position.y == y) {
					if (!firstForRow) {
						row += ", ";
					}
					else {
						row += "    ";
					}
					row += (_e->team == Entity::EntityTeam::Elf ? "E" : "G");
					row += "(";
					row += std::to_string(_e->health);
					row += ")";
					firstForRow = false;
				}
			}
			actualState.push_back(row);
		}

		return actualState;
	}

	bool Cave::doesCurrentStateMatch(const std::vector<std::string>& _state) const {
		if (_state.size() != Height) {
			std::cout << "Height does not match" << std::endl;
			return false;
		}
		if (_state.front().size() != Width) {
			std::cout << "Width does not match" << std::endl;
			return false;
		}

		std::cout << "Comparing expected state with actual state after " << m_Round << " rounds" << std::endl;
		std::vector<std::string> actualState = dumpCurrentState();
		for (std::size_t y = 0; y < Height; ++y) { std::cout << _state[y] << "\t" << actualState[y] << std::endl; }

		for (std::size_t y = 0; y < Height; ++y) {
			for (std::size_t x = 0; x < Width; ++x) {
				const CaveCell& cell = getCell(x, y);
				const char matchingChar = _state[y][x];

				if (matchingChar == '#') {
					if (cell.cellType != CaveCell::CellType::Wall) {
						std::cout << x << ", " << y << " is not a wall" << std::endl;
						return false;
					}
				}
				if (matchingChar == '.') {
					if (cell.cellType != CaveCell::CellType::Empty) {
						std::cout << x << ", " << y << " is not empty" << std::endl;
						return false;
					}
				}
				if (matchingChar == 'E') {
					if (cell.cellType != CaveCell::CellType::Empty) {
						std::cout << "Expected elf at " << x << ", " << y << " is not empty" << std::endl;
						return false;
					}
					const EntityPtr entity = cell.entity.lock();
					if (!entity) {
						std::cout << "Expected elf at " << x << ", " << y << " is not a valid EntityPtr" << std::endl;
						return false;
					}
					if (entity->team != Entity::EntityTeam::Elf) {
						std::cout << "Expected elf at " << x << ", " << y << " is a goblin" << std::endl;
						return false;
					}
				}
				if (matchingChar == 'G') {
					if (cell.cellType != CaveCell::CellType::Empty) {
						std::cout << "Expected goblin at " << x << ", " << y << " is not empty" << std::endl;
						return false;
					}
					const EntityPtr entity = cell.entity.lock();
					if (!entity) {
						std::cout << "Expected goblin at " << x << ", " << y << " is not a valid EntityPtr" << std::endl;
						return false;
					}
					if (entity->team != Entity::EntityTeam::Goblin) {
						std::cout << "Expected goblin at " << x << ", " << y << " is a elf" << std::endl;
						return false;
					}
				}
			}
		}
		return true;
	}

	void Cave::doTurn() {
		bool turnCompleted = true;
		while (EntityPtr e = findNextEntity()) {
			if (!doesEntityHaveTargets(e)) {
				turnCompleted = false;
				m_Complete = true;
				break;
			}
			const sf::Vector2u entityMovementCoordinate = getEntitiesMovementTarget(e);
			moveEntityToCoordinate(e, entityMovementCoordinate);
			attackWeakestAdjacentEnemy(e);
		}
		if (turnCompleted) {
			m_Round++;
		}
		std::for_each(m_Entities.begin(), m_Entities.end(), [](EntityPtr& _e) -> void { _e->hadTurn = false; });
	}

	EntityPtr Cave::findNextEntity() {
		std::vector<EntityPtr> entitiesStillToGo;
		std::copy_if(m_Entities.begin(), m_Entities.end(), std::back_inserter(entitiesStillToGo), [](const EntityPtr _other) -> bool {
			return !_other->hadTurn;
		});

		const auto next = std::min_element(entitiesStillToGo.begin(), entitiesStillToGo.end(), [this](const EntityPtr& _lhs, const EntityPtr& _rhs) -> bool {
			return _lhs->position.y * Width + _lhs->position.x < _rhs->position.y * Width + _rhs->position.x;
		});

		if (next == entitiesStillToGo.end()) {
			return {};
		}

		return *next;
	}

	void Cave::setEntityAt(EntityPtr _entity, Entity::EntityTeam _team) {
		{
			CaveCell& cell = getCell(_entity->position.x, _entity->position.y);
			cell.entity = WeakEntityPtr(_entity);
		}
		for (const auto offset : offsets) {
			const sf::Vector2i coord = offset + sf::Vector2i(_entity->position);
			if (coord.x >= 0 &&
				coord.y >= 0 &&
				coord.x < static_cast<int>(Width) &&
				coord.y < static_cast<int>(Height)) {

				CaveCell& cell = getCell(coord.x, coord.y);

				if (cell.cellType != CaveCell::CellType::Wall) {
					if (_team == Entity::EntityTeam::Elf) {
						cell.neighbourOfElf++;
					}
					if (_team == Entity::EntityTeam::Goblin) {
						cell.neighbourOfGoblin++;
					}
				}
			}
		}
	}

	void Cave::unsetEntityAt(EntityPtr _entity, Entity::EntityTeam _team) {
		{
			CaveCell& cell = getCell(_entity->position.x, _entity->position.y);
			cell.entity = {};
		}
		for (const auto offset : offsets) {
			const sf::Vector2i coord = offset + sf::Vector2i(_entity->position);
			if (coord.x >= 0 &&
				coord.y >= 0 &&
				coord.x < static_cast<int>(Width) &&
				coord.y < static_cast<int>(Height)) {

				CaveCell& cell = getCell(coord.x, coord.y);

				if (cell.cellType != CaveCell::CellType::Wall) {
					if (_team == Entity::EntityTeam::Elf) {
						cell.neighbourOfElf--;
					}
					if (_team == Entity::EntityTeam::Goblin) {
						cell.neighbourOfGoblin--;
					}
				}
			}
		}
	}

	bool Cave::isEntityNextToEnemy(const EntityPtr& _entity) const {
		for (const auto offset : offsets) {
			const sf::Vector2i coord = offset + _entity->position;
			if (coord.x >= 0 &&
				coord.y >= 0 &&
				coord.x < static_cast<int>(Width) &&
				coord.y < static_cast<int>(Height)) {

				const sf::Vector2u caveCoord(coord);

				const CaveCell& cell = getCell(caveCoord.x, caveCoord.y);
				if (const EntityPtr e = cell.entity.lock()) {
					if (e->team == Entity::getOppositeTeam(_entity->team)) {
						return true;
					}
				}
			}
		}

		return false;
	}

	bool Cave::doesEntityHaveTargets(const EntityPtr& _entity) const {
		const Entity::EntityTeam targetTeam = Entity::getOppositeTeam(_entity->team);

		return std::any_of(m_Entities.begin(), m_Entities.end(), [targetTeam](const EntityPtr& _other) -> bool {
			return _other->team == targetTeam;
		});
	}

	sf::Vector2u Cave::getEntitiesMovementTarget(EntityPtr _entity) {
		if (isEntityNextToEnemy(_entity)) {
			return sf::Vector2u(_entity->position);
		}

		const std::vector<sf::Vector2u>& inRangeCells = getInRangeCells(Entity::getOppositeTeam(_entity->team));

		if (inRangeCells.empty()) {
			return sf::Vector2u(_entity->position);
		}

		std::vector<int> distanceMap(Width * Height, std::numeric_limits<int>::max());
		{
			distanceMap[_entity->position.y * Width + _entity->position.x] = 0;
			std::queue<sf::Vector2u> queue;
			queue.emplace(sf::Vector2u(_entity->position));

			while (!queue.empty()) {
				const sf::Vector2u current = queue.front();
				const int currentDistance = distanceMap[current.y * Width + current.x];
				queue.pop();


				for (const auto offset : offsets) {
					const sf::Vector2i coord = offset + sf::Vector2i(current);
					if (coord.x >= 0 &&
						coord.y >= 0 &&
						coord.x < static_cast<int>(Width) &&
						coord.y < static_cast<int>(Height)) {

						const sf::Vector2u caveCoord(coord);

						const CaveCell& cell = getCell(caveCoord.x, caveCoord.y);
						if (cell.cellType != CaveCell::CellType::Empty ||
							!cell.entity.expired()) {
							continue;
						}

						int& distance = distanceMap[caveCoord.y * Width + caveCoord.x];
						if (distance > currentDistance + 1) {
							distance = currentDistance + 1;
							queue.emplace(caveCoord);
						}
					}
				}
			}
		}

		sf::Vector2u targetCell{ std::numeric_limits<unsigned>::max(), std::numeric_limits<unsigned>::max() };
		{
			int minDistance = std::numeric_limits<int>::max();
			for (const sf::Vector2u inRange : inRangeCells) {
				const int distance = distanceMap[inRange.y * Width + inRange.x];

				if (distance != std::numeric_limits<int>::max()) {
					if (distance < minDistance) {
						minDistance = distance;
						targetCell = inRange;
					}
					else if (distance == minDistance) {
						if (targetCell.y * Width + targetCell.x > inRange.y * Width + inRange.x) {
							targetCell = inRange;
						}
					}
				}
			}
		}

		if (targetCell == sf::Vector2u(std::numeric_limits<unsigned>::max(), std::numeric_limits<unsigned>::max())) {
			return sf::Vector2u(_entity->position);
		}

		sf::Vector2u movementCell(_entity->position);
		{
			distanceMap = std::vector<int>(Width * Height, std::numeric_limits<int>::max()); 
			distanceMap[targetCell.y * Width + targetCell.x] = 0;
			std::queue<sf::Vector2u> queue;
			queue.emplace(targetCell);

			while (!queue.empty()) {
				const sf::Vector2u current = queue.front();
				const int currentDistance = distanceMap[current.y * Width + current.x];
				queue.pop();

				for (const auto offset : offsets) {
					const sf::Vector2i coord = offset + sf::Vector2i(current);
					if (coord.x >= 0 &&
						coord.y >= 0 &&
						coord.x < static_cast<int>(Width) &&
						coord.y < static_cast<int>(Height)) {

						const sf::Vector2u caveCoord(coord);

						const CaveCell& cell = getCell(caveCoord.x, caveCoord.y);
						if (cell.cellType != CaveCell::CellType::Empty ||
							!cell.entity.expired()) {
							continue;
						}

						int& distance = distanceMap[caveCoord.y * Width + caveCoord.x];
						if (distance > currentDistance + 1) {
							distance = currentDistance + 1;
							queue.emplace(caveCoord);
						}
					}
				}
			}

			int minimumDistance{ std::numeric_limits<int>::max() };
			for (const auto offset : offsets) {
				const sf::Vector2i coord = offset + _entity->position;
				if (coord.x >= 0 &&
					coord.y >= 0 &&
					coord.x < static_cast<int>(Width) &&
					coord.y < static_cast<int>(Height)) {

					const sf::Vector2u caveCoord(coord);
					const int distance = distanceMap[caveCoord.y * Width + caveCoord.x];

					if (distance < minimumDistance) {
						minimumDistance = distance;
						movementCell = caveCoord;
					}
					else if (distance == minimumDistance) {
						if (movementCell.y * Width + movementCell.x > caveCoord.y * Width + caveCoord.x) {
							movementCell = caveCoord;
						}
					}
				}
			}
		}

		return movementCell;
	}

	std::vector<sf::Vector2u> Cave::getInRangeCells(Entity::EntityTeam _team) {
		std::vector<sf::Vector2u> cells;

		for (std::size_t y = 0; y < Height; ++y) {
			for (std::size_t x = 0; x < Width; ++x) {
				CaveCell& cell = getCell(x, y);
				
				if (_team == Entity::EntityTeam::Elf) {
					if (cell.neighbourOfElf > 0) {
						cells.emplace_back(x, y);
					}
				} else {
					if (cell.neighbourOfGoblin > 0) {
						cells.emplace_back(x, y);
					}
				}
			}
		}

		return cells;
	}

	void Cave::moveEntityToCoordinate(EntityPtr _entity, const sf::Vector2u& _coord) {
		if (sf::Vector2u(_entity->position) == _coord) {
			return;
		}

		unsetEntityAt(_entity, _entity->team);
		_entity->position = sf::Vector2i(_coord);
		setEntityAt(_entity, _entity->team);
	}

	void Cave::attackWeakestAdjacentEnemy(EntityPtr _entity) {
		std::vector<EntityPtr> adjacentEnemies;
		std::copy_if(m_Entities.begin(), m_Entities.end(), std::back_inserter(adjacentEnemies), [_entity](const EntityPtr _other) -> bool {
			const int distance = std::abs(_entity->position.x - _other->position.x) + std::abs(_entity->position.y - _other->position.y);
			return distance == 1 && _other->team == Entity::getOppositeTeam(_entity->team);
		});

		if (!adjacentEnemies.empty()) {
			auto target = *std::min_element(adjacentEnemies.begin(), adjacentEnemies.end(), [&](const EntityPtr& _lhs, const EntityPtr& _rhs) -> bool {
				if (_lhs->health < _rhs->health) {
					return true;
				}
				if (_rhs->health < _lhs->health) {
					return false;
				}

				return _lhs->position.y * Width + _lhs->position.x < _rhs->position.y * Width + _rhs->position.x;
			});

			target->health -= _entity->attackPower;

			if (target->health <= 0) {
				if (target->team == Entity::EntityTeam::Elf) {
					m_ElfKilled = true;
				}
				unsetEntityAt(target, target->team);
				m_Entities.erase(std::remove_if(m_Entities.begin(), m_Entities.end(), [target](const EntityPtr& _e) -> bool {
					return _e->team == target->team &&
						_e->position == target->position &&
						_e->health <= 0;
				}), m_Entities.end());
			}
		}

		_entity->hadTurn = true;
	}

	int Cave::getTotalHealthRemaining() const {
		return std::accumulate(m_Entities.begin(), m_Entities.end(), 0, [](int _sum, const EntityPtr& _e) -> int {
			return _sum + _e->health;
		});
	}
}
