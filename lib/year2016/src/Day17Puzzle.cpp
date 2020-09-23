#include <2016/Day17Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <zeno/Core/Vector2.hpp>
#include <Core/MD5.hpp>
#include <functional>

namespace TwentySixteen {
	
	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("Two Steps Forward", 2016, 17) {

	}
	Day17Puzzle::~Day17Puzzle() {

	}


	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {
		const auto part1 = explore(m_InputLines[0], true);
		const auto part2 = explore(m_InputLines[0], false);
		return { part1, part2 + "\nLength: " + std::to_string(part2.size()) };
	}

	RoomDoorState Day17Puzzle::getRoomDoorState(const std::string& _passcode, const std::string& _path) {
		RoomDoorState state;

		static const auto isDoorOpen = [](char _c) -> bool {
			return 'b' <= _c && _c <= 'f';
		};

		const std::string hash = core::md5(_passcode + _path);

		state.U = isDoorOpen(hash[0]);
		state.D = isDoorOpen(hash[1]);
		state.L = isDoorOpen(hash[2]);
		state.R = isDoorOpen(hash[3]);

		return state;
	}
	
	std::string Day17Puzzle::explore(const std::string& _passcode, bool _shortest) {

		const std::function<std::string(const ze::Vector2i&, const std::string&, unsigned)> recurserShortest =
			[&_passcode, &recurserShortest](const ze::Vector2i& _pos, const std::string& _path, unsigned _bestPathLength) -> std::string {const auto state = getRoomDoorState(_passcode, _path);

		std::string bestPath;

		if (_pos == ze::Vector2i(3, 3)) {
			return _path;
		}

		if (_path.size() >= _bestPathLength) {
			return "";
		}

		if (state.D && _pos.y < 3) {
			// Can go down
			const auto path = recurserShortest(_pos + ze::Vector2i(0, +1), _path + 'D', _bestPathLength);
			if (!path.empty()) {
				if (path.size() < _bestPathLength) {
					_bestPathLength = path.size();
					bestPath = path;
				}
			}
		}

		if (state.R && _pos.x < 3) {
			// Can go right
			const auto path = recurserShortest(_pos + ze::Vector2i(+1, 0), _path + 'R', _bestPathLength);
			if (!path.empty()) {
				if (path.size() < _bestPathLength) {
					_bestPathLength = path.size();
					bestPath = path;
				}
			}
		}

		if (state.U && _pos.y > 0) {
			// Can go up
			const auto path = recurserShortest(_pos + ze::Vector2i(0, -1), _path + 'U', _bestPathLength);
			if (!path.empty()) {
				if (path.size() < _bestPathLength) {
					_bestPathLength = path.size();
					bestPath = path;
				}
			}
		}

		if (state.L && _pos.x > 0) {
			// Can go left
			const auto path = recurserShortest(_pos + ze::Vector2i(-1, 0), _path + 'L', _bestPathLength);
			if (!path.empty()) {
				if (path.size() < _bestPathLength) {
					_bestPathLength = path.size();
					bestPath = path;
				}
			}
		}

		return bestPath;
		};

		const std::function<std::string(const ze::Vector2i&, const std::string&, unsigned)> recurserLongest =
			[&_passcode, &recurserLongest](const ze::Vector2i& _pos, const std::string& _path, unsigned _bestPathLength) -> std::string {const auto state = getRoomDoorState(_passcode, _path);

			std::string bestPath;

			if (_pos == ze::Vector2i(3, 3)) {
				return _path;
			}


			if (state.D && _pos.y < 3) {
				// Can go down
				const auto path = recurserLongest(_pos + ze::Vector2i(0, +1), _path + 'D', _bestPathLength);
				if (!path.empty()) {
					if (path.size() > _bestPathLength) {
						_bestPathLength = path.size();
						bestPath = path;
					}
				}
			}

			if (state.R && _pos.x < 3) {
				// Can go right
				const auto path = recurserLongest(_pos + ze::Vector2i(+1, 0), _path + 'R', _bestPathLength);
				if (!path.empty()) {
					if (path.size() > _bestPathLength) {
						_bestPathLength = path.size();
						bestPath = path;
					}
				}
			}

			if (state.U && _pos.y > 0) {
				// Can go up
				const auto path = recurserLongest(_pos + ze::Vector2i(0, -1), _path + 'U', _bestPathLength);
				if (!path.empty()) {
					if (path.size() > _bestPathLength) {
						_bestPathLength = path.size();
						bestPath = path;
					}
				}
			}

			if (state.L && _pos.x > 0) {
				// Can go left
				const auto path = recurserLongest(_pos + ze::Vector2i(-1, 0), _path + 'L', _bestPathLength);
				if (!path.empty()) {
					if (path.size() > _bestPathLength) {
						_bestPathLength = path.size();
						bestPath = path;
					}
				}
			}

			return bestPath;
		};

		if (_shortest) {
			return recurserShortest(ze::Vector2i(0, 0), "", std::numeric_limits<unsigned>::max());
		}
		else {
			return recurserLongest(ze::Vector2i(0, 0), "", std::numeric_limits<unsigned>::min());
		}
	}
}
