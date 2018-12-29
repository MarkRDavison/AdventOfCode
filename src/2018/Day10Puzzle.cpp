#include <2018/Day10Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <regex>

namespace TwentyEighteen {

	void dumpPoints(const std::vector<Particle>& _points, int _minX, int _maxX, int _minY, int _maxY) {
		const unsigned Height = static_cast<unsigned>(_maxY - _minY) + 1;
		const unsigned Width = static_cast<unsigned>(_maxX - _minX) + 1;

		if (Width >= 1000 || Height >= 1000) {
			return;
		}

		const unsigned CellSize = Width * Height;
		std::vector<char> pointMap(CellSize, '.');


		for (const Particle& _pp : _points) {
			const unsigned xIndex = static_cast<unsigned>(_pp.position.x - _minX);
			const unsigned yIndex = static_cast<unsigned>(_pp.position.y - _minY);

			const unsigned Index = static_cast<unsigned>(yIndex) * Width + static_cast<unsigned>(xIndex);

			if (xIndex < 0 || yIndex < 0 || xIndex >= Width || yIndex >= Height) {
				continue;
			}
			if (Index >= CellSize) {
				continue;
			}

			pointMap[Index] = '#';
		}

		for (unsigned y = 0; y < Height; ++y) {
			for (unsigned x = 0; x < Width; ++x) {

				std::cout << pointMap[y * Width + x];
			}

			std::cout << std::endl;
		}
	}
	void update(std::vector<Particle>& _points, bool _forwards) {
		for (Particle& _pp : _points) {
			_pp.position.x += _pp.velocity.x * (_forwards ? 1 : -1);
			_pp.position.y += _pp.velocity.y * (_forwards ? 1 : -1);
		}
	}

	Day10Puzzle::Day10Puzzle() :
		core::PuzzleBase("The Stars Align", 2018, 10) {

	}
	Day10Puzzle::~Day10Puzzle() {

	}

	void Day10Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day10Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day10Puzzle::fastSolve() {
		std::smatch m;
		const std::regex regex("position=<(?: )?(-?[0-9]+), (?: )?(-?[0-9]+)> velocity=<(?: )?(-?[0-9]+), (?: )?(-?[0-9]+)>");

		std::vector<Particle> points;
		for (const std::string& _row : m_InputLines) {
			std::regex_match(_row, m, regex);

			points.emplace_back(std::atoi(m[1].str().c_str()), std::atoi(m[2].str().c_str()), std::atoi(m[3].str().c_str()), std::atoi(m[4].str().c_str()));
		}

		int minX = std::numeric_limits<int>::max();
		int maxX = 0;
		int minY = std::numeric_limits<int>::max();
		int maxY = 0;

		for (const Particle& _pp : points) {
			minX = std::min(minX, _pp.position.x);
			maxX = std::max(maxX, _pp.position.x);
			minY = std::min(minY, _pp.position.y);
			maxY = std::max(maxY, _pp.position.y);
		}

		unsigned prevHeight = std::numeric_limits<unsigned>::max();

		int seconds = 0;
		while (true) {
			update(points, true);
			minX = std::numeric_limits<int>::max();
			maxX = 0;
			minY = std::numeric_limits<int>::max();
			maxY = 0;
			for (const Particle& _pp : points) {
				minX = std::min(minX, _pp.position.x);
				maxX = std::max(maxX, _pp.position.x);
				minY = std::min(minY, _pp.position.y);
				maxY = std::max(maxY, _pp.position.y);
			}
			++seconds;
			const unsigned Height = static_cast<unsigned>(maxY - minY) + 1;

			if (prevHeight < Height) {
				update(points, false);
				dumpPoints(points, minX, maxX, minY, maxY);

				return { "See above output", std::to_string(seconds - 1) };
			}

			if (getVerbose()) {
				dumpPoints(points, minX, maxX, minY, maxY);
			}
			prevHeight = Height;
		}
	}

}
