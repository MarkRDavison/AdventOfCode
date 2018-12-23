#ifndef INCLUDED_ADVENT_OF_CODE_2018_GAURD_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_GAURD_HPP_

namespace TwentyEighteen {

	struct ParsedGaurdLine {

		ParsedGaurdLine(int _id, int _year, int _month, int _day, int _hour, int _minute, bool _awake) :
			id(_id), year(_year), month(_month), day(_day), hour(_hour), minute(_minute), awake(_awake) {}

		int id{ -1 };
		int year;
		int month;
		int day;
		int hour;
		int minute;
		bool awake;

		bool equals(const ParsedGaurdLine& _other) const {
			return
				this->id == _other.id &&
				this->year == _other.year &&
				this->month == _other.month &&
				this->day == _other.day &&
				this->hour == _other.hour &&
				this->minute == _other.minute &&
				this->awake == _other.awake;
		}
		
		bool operator<(const ParsedGaurdLine& _other) const {
			if (this->year < _other.year) {
				return true;
			}
			if (_other.year < this->year) {
				return false;
			}

			if (this->month < _other.month) {
				return true;
			}
			if (_other.month < this->month) {
				return false;
			}

			if (this->day < _other.day) {
				return true;
			}
			if (_other.day < this->day) {
				return false;
			}

			if (this->hour < _other.hour) {
				return true;
			}
			if (_other.hour < this->hour) {
				return false;
			}

			if (this->minute < _other.minute) {
				return true;
			}
			if (_other.minute < this->minute) {
				return false;
			}

			return false;
		}
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_GAURD_HPP_