#include <2016/Day14Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <Core/MD5.hpp>
#include <algorithm>
#include <thread>
#include <mutex>

namespace TwentySixteen {
	
	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("One-Time Pad", 2016, 14) {

	}
	Day14Puzzle::~Day14Puzzle() {

	}


	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {
		const auto part1 = getNthKeyIndexMultiThreaded(m_InputLines[0], 64, false);
		const auto part2 = getNthKeyIndexMultiThreaded(m_InputLines[0], 64, true);
		return { std::to_string(part1), std::to_string(part2) };
	}
	
	bool Day14Puzzle::isKey(const std::string& _salt, unsigned _index, bool _part2) {
		char triple;

		const std::string input = _salt + std::to_string(_index);
		std::string hash = core::md5(input);
		if (_part2) {
			for (unsigned hi = 0; hi < 2016; ++hi) {
				hash = core::md5(hash);
			}
		}
		if (!hasTriple(hash, triple)) {
			return false;
		}
		
		for (unsigned i = 0; i < 1000; ++i) {
			const unsigned quintupleIndex = _index + 1 + i;
			const std::string newInput = _salt + std::to_string(quintupleIndex);
			std::string newHash = core::md5(newInput);
			if (_part2) {
				for (unsigned hi = 0; hi < 2016; ++hi) {
					newHash = core::md5(newHash);
				}
			}

			if (hasQuintuple(newHash, triple)) {
				std::cout << _salt << " + " << _index << " -> " << newHash << " is quintuple of '" << triple << "'" << std::endl;
				return true;
			}
		}

		return false;
	}

	unsigned Day14Puzzle::getNthKeyIndex(const std::string& _salt, unsigned _keyNumber, bool _part2) {
		unsigned keysFound = 0;
		unsigned index = 0;
		while (keysFound != _keyNumber) {
			if (isKey(_salt, index, _part2)) {
				keysFound++;
			}
			index++;
		}
		return index - 1;
	}
	unsigned Day14Puzzle::getNthKeyIndexMultiThreaded(const std::string& _salt, unsigned _keyNumber, bool _part2) {
		const auto numThreads = std::thread::hardware_concurrency();

		std::vector<unsigned> keyIndexes;
		std::mutex keyMutex;
		unsigned workIndex = 0;
		std::mutex workIndexMutex;
		std::atomic_bool finish{ false };

		const auto getKeyIndexesInRange = 
		[&keyMutex, &workIndexMutex, &keyIndexes, &finish, &workIndex](const std::string& _salt, bool _part2) -> void {
			constexpr unsigned WORK_SIZE = 100;
	
			while (!finish) {
				unsigned localWorkIndex = 0;
				{
					std::scoped_lock(workIndexMutex);
					localWorkIndex = workIndex++;
				}
				std::cout << localWorkIndex * WORK_SIZE << " -> " << (localWorkIndex + 1) * WORK_SIZE << " started." << std::endl;
				for (unsigned i = localWorkIndex * WORK_SIZE; i < (localWorkIndex + 1) * WORK_SIZE; ++i) {
					if (Day14Puzzle::isKey(_salt, i, _part2)) {
						std::scoped_lock(keyMutex);
						keyIndexes.push_back(i);
						std::cout << keyIndexes.size() << " found." << std::endl;
					}
				}

				std::cout << localWorkIndex * WORK_SIZE << " -> " << (localWorkIndex + 1) * WORK_SIZE << " finished." << std::endl;
			}
		};

		std::vector<std::thread> workers;
		for (unsigned i = 0; i < numThreads; ++i) {
			workers.push_back(std::thread(getKeyIndexesInRange, _salt, _part2));
		}
		while (keyIndexes.size() < _keyNumber) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		finish = true;
		for (auto& t : workers) {
			t.join();
		}

		std::sort(keyIndexes.begin(), keyIndexes.end());
		
		if (!_part2) {
			std::cout << "Part 1 complete, starting part 2" << std::endl;
		}

		return keyIndexes[_keyNumber - 1];
	}
}
