#include <2019/Day10Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>
#include <queue>
#include <vector>
#include <numeric>

namespace TwentyNineteen {

	struct Cell {
		bool asteroid{ false };
		unsigned visibleFromHere{ 0 };
		int destroyedCycle{ -1 };
		int order{ -1 };
		float angle{ 0.0f };
	};
	
	Day10Puzzle::Day10Puzzle() :
		core::PuzzleBase("Monitoring Station", 2019, 10) {

	}
	Day10Puzzle::~Day10Puzzle() {

	}


	void Day10Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day10Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	static int calculateVisibleAsteroids(core::Region<Cell>& _region, unsigned _x, unsigned _y, unsigned _width, unsigned _height) {
		int count = 0;
		for (unsigned int y = 0; y < _height; ++y) {
			for (unsigned int x = 0; x < _width; ++x) {
				if (x == _x && y == _y) { continue; }
				if (!_region.getCell(x, y).asteroid) { continue; }

				int x_rel = static_cast<int>(x) - static_cast<int>(_x);
				int y_rel = static_cast<int>(y) - static_cast<int>(_y);
				int gcd = std::gcd(x_rel, y_rel);
				int x_step = x_rel / gcd;
				int y_step = y_rel / gcd;

				int x_curr = static_cast<int>(_x) + x_step;
				int y_curr = static_cast<int>(_y) + y_step;
				bool blocked = false;
				while (true) {

					if (x_curr == static_cast<int>(x) &&
						y_curr == static_cast<int>(y)) {
						break;
					}

					if (_region.getCell(x_curr, y_curr).asteroid) {
						blocked = true;
						break;
					}

					x_curr += x_step;
					y_curr += y_step;
				}
				if (!blocked) {
					count++;
				}
			}
		}

		return count;
	}

	static std::string destroyQuadrant(core::Region<Cell>& _region, int _source_x, int _source_y, int _width, int _height, int _x_axis_multi, int _y_axis_multi, int _cycle, int& _destroyedOrder) {

		std::vector<core::Vector2i> locs;

		for (unsigned int y = 0; y < _height; ++y) {
			for (unsigned int x = 0; x < _width; ++x) {
				if (x == _source_x && y == _source_y) { continue; }
				if (!_region.getCell(x, y).asteroid) { continue; }

				int x_rel = static_cast<int>(x) - static_cast<int>(_source_x);
				int y_rel = static_cast<int>(y) - static_cast<int>(_source_y);
				int gcd = std::gcd(x_rel, y_rel);
				int x_step = x_rel / gcd;
				int y_step = y_rel / gcd;

				int x_curr = static_cast<int>(_source_x) + x_step;
				int y_curr = static_cast<int>(_source_y) + y_step;
				bool blocked = false;
				while (true) {

					if (x_curr == static_cast<int>(x) &&
						y_curr == static_cast<int>(y)) {
						break;
					}

					if (_region.getCell(x_curr, y_curr).asteroid) {
						blocked = true;
						break;
					}

					x_curr += x_step;
					y_curr += y_step;
				}
				if (!blocked) {
					locs.push_back({ static_cast<int>(x),static_cast<int>(y) });
				}
			}
		}

		std::sort(locs.begin(), locs.end(), [_source_x, _source_y](const core::Vector2i& _lhs, const core::Vector2i& _rhs) -> bool {
			auto source = core::Vector2i(_source_x, _source_y);

			auto relative_lhs = _lhs -source;
			auto relative_rhs = _rhs - source;

			float angle_lhs = core::VectorMath::toAngle(core::Vector2f(relative_lhs)) + 90.0f;
			float angle_rhs = core::VectorMath::toAngle(core::Vector2f(relative_rhs)) + 90.0f;

			if (angle_lhs > 360.0f) {
				angle_lhs -= 360.0f;
			}
			if (angle_lhs < 0.0f) {
				angle_lhs += 360.0f;
			}
			if (angle_rhs > 360.0f) {
				angle_rhs -= 360.0f;
			}
			if (angle_rhs < 0.0f) {
				angle_rhs += 360.0f;
			}

			return angle_lhs < angle_rhs;
		});

		while (!locs.empty()) {
			auto f = locs.front();
			locs.erase(locs.begin());
			int x_rel = static_cast<int>(f.x) - static_cast<int>(_source_x);
			int y_rel = static_cast<int>(f.y) - static_cast<int>(_source_y);
			int gcd = std::gcd(x_rel, y_rel);
			int x_step = x_rel / gcd;
			int y_step = y_rel / gcd;

			if (gcd != 1) {
				core::Vector2i blockCheck = { x_step + _source_x, y_step + _source_y };
				bool blocked = false;
				while (blockCheck != f) {
					auto& bcell = _region.getCell(blockCheck.x, blockCheck.y);
					if (bcell.asteroid && bcell.destroyedCycle >= _cycle) {
						bcell.destroyedCycle = _cycle;
						blocked = true;
						break;
					}
					blockCheck.x += x_step;
					blockCheck.y += y_step;
				}
				if (blocked) {
					continue;
				}
			}
			auto& fcell = _region.getCell(f.x, f.y);
			if (fcell.asteroid && fcell.destroyedCycle == -1) {
				fcell.destroyedCycle = _cycle;
				fcell.order = _destroyedOrder;
				if (_destroyedOrder == 200) {
					return std::to_string(f.x * 100 + f.y);
				}
				_destroyedOrder++;
			}			
		}

		return "";
	}

	static std::string destroyAsteroids(core::Region<Cell>& _region, int _source_x, int _source_y, int _width, int _height) {
		int x_axis_multi = -1;
		int y_axis_multi = -1;
		int cycle = 1;
		int order = 1;
		int pastOrder = 0;
		std::string result;
		while (result.empty() && pastOrder != order) {
			pastOrder = order;
			result = destroyQuadrant(_region, _source_x, _source_y, _width, _height, x_axis_multi, y_axis_multi, cycle, order);
			cycle++;
		}

		return result;
	}
	
	std::pair<std::string, std::string> Day10Puzzle::fastSolve() {

		core::Region<Cell> region;
		const unsigned height = m_InputLines.size();
		const unsigned width = m_InputLines[0].size();

		for (unsigned int y = 0; y < height; ++y) {
			for (unsigned int x = 0; x < width; ++x) {
				if (m_InputLines[y][x] == '#') {
					region.getCell(x, y).asteroid = true;
				}
			}
		}

		unsigned max = 0;
		int x__ = 0, y__ = 0;
		for (unsigned int y = 0; y < height; ++y) {
			for (unsigned int x = 0; x < width; ++x) {
				Cell& cell = region.getCell(x, y);
				if (!cell.asteroid) { continue; }
				cell.visibleFromHere = calculateVisibleAsteroids(region, x, y, width, height);
				if (max < cell.visibleFromHere) {
					max = cell.visibleFromHere;
					x__ = x;
					y__ = y;
				}
			}
		}

		auto part2 = destroyAsteroids(region, x__, y__, static_cast<int>(width), static_cast<int>(height));

		return { std::to_string(max), part2 };
	}
}
