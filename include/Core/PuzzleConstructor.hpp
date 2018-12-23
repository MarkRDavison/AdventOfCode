#ifndef INCLUDED_ADVENT_OF_CODE_CORE_PUZZLE_CONSTRUCTOR_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_PUZZLE_CONSTRUCTOR_HPP_

#include <Core/InitialisationInfo.hpp>
#include <Core/IPuzzleBase.hpp>
#include <functional>
#include <map>

namespace core {
	using PuzzleConstructionFxn = std::function<core::IPuzzleBase*(const InitialisationInfo&)>;
	
	class PuzzleConstructor {
	public:
		template <typename T>
		static void registerPuzzle(int _day) {
			constructorMethods[_day] = [](const InitialisationInfo& _info) -> core::IPuzzleBase * {
				return new T();
			};;
		}

		static core::IPuzzleBase *createPuzzle(const InitialisationInfo& _info) {
			if (!_info.valid) {
				return nullptr;
			}

			core::IPuzzleBase *puzzle = constructorMethods[_info.day](_info);
			puzzle->initialise(_info);
			return puzzle;
		}

	private:
		PuzzleConstructor() = delete;
		~PuzzleConstructor() = delete;

		static std::map<int, PuzzleConstructionFxn> constructorMethods;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_PUZZLE_CONSTRUCTOR_HPP_