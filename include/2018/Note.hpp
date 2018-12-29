#ifndef INCLUDED_ADVENT_OF_CODE_2018_NOTE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_NOTE_HPP_

namespace TwentyEighteen {
	struct Note {

		Note(bool _left2, bool _left1, bool _current, bool _right1, bool _right2, bool _resultsInPlant) :
			left2HasPlant(_left2), left1HasPlant(_left1), currentHasPlant(_current), right1HasPlant(_right1), right2HasPlant(_right2),
			resultsInPlant(_resultsInPlant) {}

		const bool left2HasPlant;
		const bool left1HasPlant;
		const bool currentHasPlant;
		const bool right1HasPlant;
		const bool right2HasPlant;

		const bool resultsInPlant;
	};
}

#endif // INCLUDED_ADVENT_OF_CODE_2018_NOTE_HPP_