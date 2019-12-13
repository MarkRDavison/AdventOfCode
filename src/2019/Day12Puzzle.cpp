#include <2019/Day12Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

namespace TwentyNineteen {
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("The N-Body Problem", 2019, 12) {

	}
	Day12Puzzle::~Day12Puzzle() {

	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Moon {
		Moon(int _xp, int _yp, int _zp, int _xv, int _yv, int _zv) :
			xp(_xp),
			yp(_yp),
			zp(_zp),
			xv(_xv),
			yv(_yv),
			zv(_zv) {

		}
		int xp{ 0 };
		int yp{ 0 };
		int zp{ 0 };
		int xv{ 0 };
		int yv{ 0 };
		int zv{ 0 };
	};

	void step(std::vector<Moon>& _moons) {
		std::vector<Moon> newMoons(_moons);
		for (unsigned mi_1 = 0; mi_1 < _moons.size(); ++mi_1) {
			const Moon& m1 = _moons[mi_1];
			Moon& m1_edit = newMoons[mi_1];
			for (unsigned mi_2 = mi_1 + 1; mi_2 < _moons.size(); ++mi_2) {
				const Moon& m2 = _moons[mi_2];
				Moon& m2_edit = newMoons[mi_2];

				if (m1.xp < m2.xp) {
					m1_edit.xv++;
					m2_edit.xv--;
				} else if (m1.xp > m2.xp) {
					m1_edit.xv--;
					m2_edit.xv++;
				}
				if (m1.yp < m2.yp) {
					m1_edit.yv++;
					m2_edit.yv--;
				} else if (m1.yp > m2.yp) {
					m1_edit.yv--;
					m2_edit.yv++;
				}
				if (m1.zp < m2.zp) {
					m1_edit.zv++;
					m2_edit.zv--;
				} else if (m1.zp > m2.zp) {
					m1_edit.zv--;
					m2_edit.zv++;
				}
			}
		}

		for (unsigned i = 0; i < _moons.size(); ++i) {
			Moon& m1 = _moons[i];
			const Moon& m_Edit = newMoons[i];

			m1.xp += m_Edit.xv;
			m1.yp += m_Edit.yv;
			m1.zp += m_Edit.zv;
			m1.xv = m_Edit.xv;
			m1.yv = m_Edit.yv;
			m1.zv = m_Edit.zv;
		}
	}

	void dumpMoons(unsigned steps, const std::vector<Moon>& _moons) {
		std::cout << "After " << steps << " steps:" << std::endl;
		for (const Moon& _m : _moons) {
			std::cout
				<< "pos=<x=" << _m.xp << ",\ty=" << _m.yp << ",\tz=" << _m.zp
				<< ">,\t vel=<x=" << _m.xv << ",\ty=" << _m.yv << ",\tz=" << _m.zv << ">" << std::endl;
		}
	}

	int getEnergy(const std::vector<Moon>& _moons) {
		int total = 0;

		for (const Moon& _moon : _moons) {
			auto pot = std::abs(_moon.xp) + std::abs(_moon.yp) + std::abs(_moon.zp);
			auto kin = std::abs(_moon.xv) + std::abs(_moon.yv) + std::abs(_moon.zv);

			total += pot * kin;
		}

		return total;
	}

	std::size_t getHash(const std::vector<Moon>& _moons) {
		std::string state;
		for (const Moon& _moon : _moons) {
			state +=
				std::to_string(_moon.xp) +
				std::to_string(_moon.yp) +
				std::to_string(_moon.zp) +
				std::to_string(_moon.xv) +
				std::to_string(_moon.yv) +
				std::to_string(_moon.zv);
		}

		return std::hash<std::string>()(state);
	}

	std::string getMoonState(const Moon& _moon, int _dim) {
		switch (_dim) {
		case 1:
			return std::to_string(_moon.xp) + std::to_string(_moon.xv);
		case 2:
			return std::to_string(_moon.yp) + std::to_string(_moon.yv);
		case 3:
			return std::to_string(_moon.zp) + std::to_string(_moon.zv);
		}
		throw std::runtime_error("Bad dimension index");
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {
		std::vector<Moon> moons;
		for (const auto& str : m_InputLines) {
			const auto& parts = core::StringExtensions::splitStringByDelimeter(str, "=,>");

			const int x = std::stoi(parts[1]);
			const int y = std::stoi(parts[3]);
			const int z = std::stoi(parts[5]);

			moons.emplace_back(x,y,z,0,0,0);
		}
		
		std::unordered_map<std::string, std::vector<unsigned>> locationCount[3];

		std::vector<long long> vv{ };

		std::string part1;
		unsigned steps = 0;
		std::unordered_set<int> stateHashSet;
		while (true) {
			const Moon& m0 = moons[0];
			const Moon& m1 = moons[1];
			const Moon& m2 = moons[2];
			const Moon& m3 = moons[3];

			auto moonState_x = getMoonState(m0, 1) + getMoonState(m1, 1) + getMoonState(m2, 1) + getMoonState(m3, 1);
			auto moonState_y = getMoonState(m0, 2) + getMoonState(m1, 2) + getMoonState(m2, 2) + getMoonState(m3, 2);
			auto moonState_z = getMoonState(m0, 3) + getMoonState(m1, 3) + getMoonState(m2, 3) + getMoonState(m3, 3);

			locationCount[0][moonState_x].push_back(steps);
			locationCount[1][moonState_y].push_back(steps);
			locationCount[2][moonState_z].push_back(steps);

			if (steps == 1000) {
				part1 = std::to_string(getEnergy(moons));
			}

			if (steps % 50000 == 0) {
				bool valid = true;
				for (unsigned d = 0; d < 3; ++d) {
					for (auto& thing : locationCount[d]) {
						if (thing.second.size() >= 2) {
							vv.push_back(thing.second[1] - thing.second[0]);
							break;
						} else {
							valid = false;
							break;
						}
					}

				}
				if (valid) {
					auto lc = std::accumulate(vv.begin(), vv.end(), 1ll, [](auto _1, auto _2) { return std::lcm(_1, _2); });
					return { part1, std::to_string(lc) };
				}
			}

			step(moons);
			steps++;
		}
	}
}
