#include <2015/Day04Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/MD5.hpp>
#include <functional>
#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>

namespace TwentyFifteen {
	
	Day04Puzzle::Day04Puzzle() :
		core::PuzzleBase("The Ideal Stocking Stuffer", 2015, 4) {

	}
	Day04Puzzle::~Day04Puzzle() {

	}


	void Day04Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day04Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void Day04Puzzle::findZeroedMd5(std::string _input, unsigned _starting, unsigned _count, std::mutex& _mutex, std::vector<unsigned>& _output5, std::vector<unsigned>& _output6) {
		for (unsigned i = _starting; i < _starting + _count; i++) {
			const std::string& hash = core::md5(_input + std::to_string(i));
			if (hash.size() >= 5) {
				if (hash[0] == '0' &&
					hash[1] == '0' &&
					hash[2] == '0' &&
					hash[3] == '0' &&
					hash[4] == '0' &&
					hash[5] == '0') {
					_mutex.lock();
					_output6.emplace_back(i);
					_mutex.unlock();
					break;
				}
				else if (hash[0] == '0' &&
					hash[1] == '0' &&
					hash[2] == '0' &&
					hash[3] == '0' &&
					hash[4] == '0') {
					_mutex.lock();
					_output5.emplace_back(i);
					_mutex.unlock();
					break;
				}
			}
		}
	}

	std::pair<std::string, std::string> Day04Puzzle::fastSolve() {

		const std::string input = m_InputLines[0];
		unsigned concurentThreadsSupported = std::thread::hardware_concurrency();

		std::vector<std::thread> threads;
		const unsigned threadWorkQueueSize = 10000;

		unsigned index = 0;

		std::mutex mutex;
		std::vector<unsigned> idsWith5ZeroedMd5;
		std::vector<unsigned> idsWith6ZeroedMd5;

		std::string part1;
		std::string part2;

		auto t1 = std::chrono::high_resolution_clock::now();

		while (1) {
			for (unsigned i = 0; i < concurentThreadsSupported; ++i) {
				threads.push_back(std::thread(&Day04Puzzle::findZeroedMd5, input, index, threadWorkQueueSize, std::ref(mutex), std::ref(idsWith5ZeroedMd5), std::ref(idsWith6ZeroedMd5)));
				index += threadWorkQueueSize;
			}

			for (auto& thread : threads) {
				thread.join();
			}
			threads.clear();
			if (part1.empty() && !idsWith5ZeroedMd5.empty()) {
				unsigned min = *std::min_element(idsWith5ZeroedMd5.begin(), idsWith5ZeroedMd5.end(), [](const unsigned& _l, const unsigned& _r) -> int {
					return _l < _r;
					});
				part1 = std::to_string(min);
			}
			if (part2.empty() && !idsWith6ZeroedMd5.empty()) {
				unsigned min = *std::min_element(idsWith6ZeroedMd5.begin(), idsWith6ZeroedMd5.end(), [](const unsigned& _l, const unsigned& _r) -> int {
					return _l < _r;
					});
				part2 = std::to_string(min);
			}
			if (!part1.empty() && !part2.empty()) {
				break;
			}
		}
		auto t2 = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

		if (getVerbose()) {
			std::cout << "With " << concurentThreadsSupported << " threads and block size of " << threadWorkQueueSize << ", took " << duration << "ms." << std::endl;
		}
		
		return { part1, part2 };
	}
}
