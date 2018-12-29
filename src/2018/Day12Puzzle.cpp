#include <2018/Day12Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <2018/Note.hpp>
#include <2018/Pot.hpp>

namespace TwentyEighteen {

	std::shared_ptr<Pot> addBufferPotsIfNeeded(std::shared_ptr<Pot> _pot) {
		const int BufferSize = 3;

		{ // Adding Buffers to start
			std::shared_ptr<Pot> iteratorPot = _pot;
			while (iteratorPot->prev) {
				iteratorPot = iteratorPot->prev;
			}

			int currentStartBufferSize = 0;
			if (!iteratorPot->plant) {
				currentStartBufferSize++;
				if (!iteratorPot->next->plant) {
					currentStartBufferSize++;
					if (!iteratorPot->next->next->plant) {
						currentStartBufferSize++;
					}
				}
			}

			std::shared_ptr<Pot> startBufferAddingPot = iteratorPot;
			while (currentStartBufferSize != BufferSize) {
				std::shared_ptr<Pot> newBufferPot = std::make_shared<Pot>(false);
				newBufferPot->next = startBufferAddingPot;
				startBufferAddingPot->prev = newBufferPot;
				startBufferAddingPot = newBufferPot;
				currentStartBufferSize++;
			}
		}
		{ // Adding Buffers to end
			std::shared_ptr<Pot> iteratorPot = _pot;
			while (iteratorPot->next) {
				iteratorPot = iteratorPot->next;
			}

			int currentStartBufferSize = 0;
			if (!iteratorPot->plant) {
				currentStartBufferSize++;
				if (!iteratorPot->prev->plant) {
					currentStartBufferSize++;
					if (!iteratorPot->prev->prev->plant) {
						currentStartBufferSize++;
					}
				}
			}

			std::shared_ptr<Pot> startBufferAddingPot = iteratorPot;
			while (currentStartBufferSize != BufferSize) {
				std::shared_ptr<Pot> newBufferPot = std::make_shared<Pot>(false);
				newBufferPot->prev = startBufferAddingPot;
				startBufferAddingPot->next = newBufferPot;
				startBufferAddingPot = newBufferPot;
				currentStartBufferSize++;
			}
		}

		std::shared_ptr<Pot> firstPot = _pot;
		while (firstPot->prev) {
			firstPot = firstPot->prev;
		}

		return firstPot;
	}

	bool noteMatchesPotStates(const Note& _note, std::shared_ptr<Pot> _currentPot) {
		bool left1HasPlant = false;
		bool left2HasPlant = false;

		bool right1HasPlant = false;
		bool right2HasPlant = false;

		if (_currentPot->prev != nullptr) {
			const std::shared_ptr<Pot> prevPot = _currentPot->prev;
			left1HasPlant = prevPot->plant;

			if (prevPot->prev != nullptr) {
				left2HasPlant = prevPot->prev->plant;
			}
		}

		if (_currentPot->next != nullptr) {
			const std::shared_ptr<Pot> nextPot = _currentPot->next;
			right1HasPlant = nextPot->plant;

			if (nextPot->next != nullptr) {
				right2HasPlant = nextPot->next->plant;
			}
		}

		return
			left2HasPlant == _note.left2HasPlant &&
			left1HasPlant == _note.left1HasPlant &&
			_currentPot->plant == _note.currentHasPlant &&
			right1HasPlant == _note.right1HasPlant &&
			right2HasPlant == _note.right2HasPlant;
	}

	int getNumberPlants(std::shared_ptr<Pot> _firstPot) {
		int num = 0;
		std::shared_ptr<Pot>firstPot = _firstPot;
		while (firstPot) {
			if (firstPot->plant) {
				num++;
			}
			firstPot = firstPot->next;
		}

		return num;
	}

	std::vector<int> getPotIndexesWithPlants(std::shared_ptr<Pot>_rootPot) {
		std::vector<int> plantIndexes;

		int index = 0;

		std::shared_ptr<Pot> currentPot = _rootPot;
		while (currentPot) {

			if (currentPot->plant) {
				plantIndexes.emplace_back(index);
			}

			index++;
			currentPot = currentPot->next;
		}

		return plantIndexes;
	}

	int getPotSum(std::shared_ptr<Pot>_rootPot) {
		int sum = 0;

		{
			int negativeIndex = -1;
			std::shared_ptr<Pot>negativePots = _rootPot->prev;
			while (negativePots) {
				if (negativePots->plant) {
					sum += negativeIndex;
				}
				negativePots = negativePots->prev;
				negativeIndex -= 1;
			}
		}
		{
			int positiveIndex = 1;
			std::shared_ptr<Pot>positivePots = _rootPot->next;
			while (positivePots) {
				if (positivePots->plant) {
					sum += positiveIndex;
				}
				positivePots = positivePots->next;
				positiveIndex += 1;
			}
		}

		return sum;
	}

	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("Subterranean Sustainability", 2018, 12) {

	}
	Day12Puzzle::~Day12Puzzle() {

	}

	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {
		const std::string initialState(core::StringExtensions::splitStringByDelimeter(m_InputLines[0], " ").back());

		std::vector<Note> notes;
		for (std::size_t i = 2; i < m_InputLines.size(); ++i) {
			const std::string& noteRow = m_InputLines[i];
			notes.emplace_back(
				noteRow[0] == '#',
				noteRow[1] == '#',
				noteRow[2] == '#',
				noteRow[3] == '#',
				noteRow[4] == '#',
				noteRow[9] == '#'
			);
		}
		
		std::shared_ptr<Pot> rootPot = std::make_shared<Pot>(initialState[0] == '#');
		rootPot->isRoot = true;
		std::shared_ptr<Pot> currentPot = rootPot;
		for (std::size_t i = 1; i < initialState.size(); ++i) {
			std::shared_ptr<Pot> newPot = std::make_shared<Pot>(initialState[i] == '#');
			currentPot->next = newPot;
			newPot->prev = currentPot;
			currentPot = newPot;
		}

		std::shared_ptr<Pot> firstPot = rootPot;

		std::string Part1Answer;
		std::string Part2Answer;

		firstPot = addBufferPotsIfNeeded(firstPot);
		int i = 0;
		int prevnumberPlants = 0;
		while (true) {
			if (i == 20) {
				Part1Answer = std::to_string(getPotSum(rootPot));
			}

			std::shared_ptr<Pot> potToGenerate = firstPot;
			while (potToGenerate != nullptr) {
				for (const Note& note : notes) {
					if (note.currentHasPlant != potToGenerate->plant) {
						continue;
					}

					if (noteMatchesPotStates(note, potToGenerate)) {
						potToGenerate->hasPlantNext = note.resultsInPlant;
					}
				}

				potToGenerate = potToGenerate->next;
			}

			std::shared_ptr<Pot> potToUpdate = firstPot;
			while (potToUpdate != nullptr) {
				potToUpdate->plant = potToUpdate->hasPlantNext;
				potToUpdate->hasPlantNext = false;

				potToUpdate = potToUpdate->next;
			}

			firstPot = addBufferPotsIfNeeded(firstPot);


			const int currentNumberPlants = getNumberPlants(firstPot);

			if (currentNumberPlants == prevnumberPlants && i > 200) {
				const long long TargetGeneration = 50000000000;
				const long long CurrentGeneration = static_cast<long long>(i + 1);
				const long long OffsetGeneration = TargetGeneration - CurrentGeneration;

				long long sum = 0;

				const std::vector<int> plantIndexes = getPotIndexesWithPlants(rootPot);

				for (int _index : plantIndexes) {
					sum += static_cast<long long>(_index);
				}

				sum += static_cast<long long>(plantIndexes.size()) * OffsetGeneration;

				Part2Answer = std::to_string(sum);
				break;
			}
			else {
				prevnumberPlants = currentNumberPlants;
			}
			i++;
		}

		return { Part1Answer, Part2Answer };
	}

}
