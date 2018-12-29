#include <2018/Day13Puzzle.hpp>
#include <2018/Cart.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>

namespace TwentyEighteen {

	void tick(const std::vector<std::string>& _board, std::vector<Cart>& _carts, std::vector<std::pair<int, int>>& _collisionLocations) {
		std::sort(_carts.begin(), _carts.end());


		for (Cart& _cart : _carts) {
			_cart.x += _cart.directionX;
			_cart.y += _cart.directionY;


			const char NewPositionChar = _board[static_cast<unsigned>(_cart.y)][static_cast<unsigned>(_cart.x)];

			if (NewPositionChar == '\\') {
				if (_cart.directionX == 1) {
					// We are going right, and have hit a top right corner, so need to go down
					_cart.charIndex = cart.find('v');
					_cart.directionX = dx[_cart.charIndex];
					_cart.directionY = dy[_cart.charIndex];
				}
				else if (_cart.directionX == -1) {
					// We are going left, and have hit a bottom leftcorner, so need to go up
					_cart.charIndex = cart.find('^');
					_cart.directionX = dx[_cart.charIndex];
					_cart.directionY = dy[_cart.charIndex];
				}
				else if (_cart.directionY == -1) {
					// We are going up, and have hit a top right corner, so need to go left
					_cart.charIndex = cart.find('<');
					_cart.directionX = dx[_cart.charIndex];
					_cart.directionY = dy[_cart.charIndex];
				}
				else if (_cart.directionY == 1) {
					// We are going down, and have hit a bottom left corner, so need to go right
					_cart.charIndex = cart.find('>');
					_cart.directionX = dx[_cart.charIndex];
					_cart.directionY = dy[_cart.charIndex];
				}
			}
			else if (NewPositionChar == '/') {
				if (_cart.directionY == 1) {
					// We are going down, and have hit bottom right corner, so need to go left
					_cart.charIndex = cart.find('<');
					_cart.directionX = dx[_cart.charIndex];
					_cart.directionY = dy[_cart.charIndex];
				}
				else if (_cart.directionY == -1) {
					// We are going up and have hit top left corner, so need to go right
					_cart.charIndex = cart.find('>');
					_cart.directionX = dx[_cart.charIndex];
					_cart.directionY = dy[_cart.charIndex];
				}
				else if (_cart.directionX == 1) {
					// We are going right, and have hit bottom right corner, so need to go up
					_cart.charIndex = cart.find('^');
					_cart.directionX = dx[_cart.charIndex];
					_cart.directionY = dy[_cart.charIndex];
				}
				else if (_cart.directionX == -1) {
					// We are going left, and have hit top left corner, so need to go down
					_cart.charIndex = cart.find('v');
					_cart.directionX = dx[_cart.charIndex];
					_cart.directionY = dy[_cart.charIndex];
				}
			}
			else if (NewPositionChar == '+') {
				if (_cart.direction == Left) {
					_cart.charIndex += 1;
					_cart.charIndex %= 4;
					_cart.directionX = dx[_cart.charIndex];
					_cart.directionY = dy[_cart.charIndex];
					_cart.direction = Straight;
				}
				else if (_cart.direction == Straight) {
					_cart.direction = Right;
				}
				else if (_cart.direction == Right) {
					_cart.charIndex += 3;
					_cart.charIndex %= 4;
					_cart.directionX = dx[_cart.charIndex];
					_cart.directionY = dy[_cart.charIndex];
					_cart.direction = Left;
				}
			}

			std::for_each(_carts.begin(), _carts.end(), [&](Cart& _cartToCompareAgainst) -> void {
				if (_cart.id == _cartToCompareAgainst.id) {
					return;
				}

				if (_cart.x == _cartToCompareAgainst.x &&
					_cart.y == _cartToCompareAgainst.y &&
					!_cart.dead && !_cartToCompareAgainst.dead) {
					_cart.dead = true;
					_cartToCompareAgainst.dead = true;
					_collisionLocations.emplace_back(_cart.x, _cart.y);
				}
			});
		}

		_carts.erase(std::remove_if(_carts.begin(), _carts.end(), [](const Cart& _cart) -> bool {return _cart.dead; }), _carts.end());
	}

	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("???", 2018, 13) {

	}
	Day13Puzzle::~Day13Puzzle() {

	}

	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {
		std::vector<std::string> grid(m_InputLines);
		std::vector<Cart> carts;
		const int Height = static_cast<int>(grid.size());
		const int Width = static_cast<int>(grid[0].size());

		for (int y = 0; y < Height; ++y) {
			for (int x = 0; x < Width; ++x) {
				const std::size_t cartDirectionIndex = cart.find(grid[y][x]);
				if (cartDirectionIndex != std::string::npos) {
					carts.emplace_back(x, y, cartDirectionIndex);
					if (dx[cartDirectionIndex] == 0) {
						// We are going vertical, replace with Pipe
						grid[y][x] = '|';
					}
					else {
						// We are going horizontal, replace with hyphen
						grid[y][x] = '-';
					}
				}
			}
		}

		std::vector<std::pair<int, int>> collisions;
		while (carts.size() > 1) {
			tick(grid, carts, collisions);
		}

		std::string Part1Answer = std::to_string(collisions[0].first) + "," + std::to_string(collisions[0].second);
		std::string Part2Answer = carts.empty() ? "No carts left at end (even number)" : std::to_string(carts[0].x) + "," + std::to_string(carts[0].y);

		return { Part1Answer, Part2Answer };
	}

}
