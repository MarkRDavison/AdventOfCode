#ifndef INCLUDED_ADVENT_OF_CODE_2018_PARSED_CLAY_VEIN_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_PARSED_CLAY_VEIN_HPP_

namespace TwentyEighteen {

	struct ParsedClayVein {

		ParsedClayVein(int _xmin, int _xmax, int _ymin, int _ymax) :
			xMin(_xmin), xMax(_xmax), yMin(_ymin), yMax(_ymax) {}

		const int xMin;
		const int xMax;
		const int yMin;
		const int yMax;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_PARSED_CLAY_VEIN_HPP_