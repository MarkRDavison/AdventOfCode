#include <2019/Day06Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

namespace TwentyNineteen {
	
	struct Orbit {
		Orbit(const std::string& _orbitee, const std::string& _orbiter) :
			Orbitee(_orbitee),
			Orbiter(_orbiter) {

		}

		const std::string& Orbitee;
		const std::string& Orbiter;
	};

	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Universal Orbit Map", 2019, 6) {

	}
	Day06Puzzle::~Day06Puzzle() {

	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {

		std::unordered_map<std::string, std::unordered_set<std::string>> orbits;
		std::unordered_map<std::string, unsigned> memoizedOrbits;
		std::unordered_map<std::string, std::string> whoDoIOrbit;
		std::unordered_set<std::string> allBodies;
		allBodies.insert("COM");
		memoizedOrbits["COM"] = 0;

		for (const auto& str : m_InputLines) {
			const auto& pair = core::StringExtensions::splitStringByDelimeter(str, ")");
			const auto& orbitee = pair[0];
			const auto& orbiter = pair[1];

			orbits[orbitee].insert(orbiter);
			allBodies.insert(orbiter);
		}

		const std::string you = "YOU";
		const std::string santa = "SAN";

		std::vector<std::string> toodos = { "COM" };
		for (unsigned i = 0; i < toodos.size(); ++i) {
			auto& current = memoizedOrbits[toodos[i]];

			for (const auto& orbiter : orbits[toodos[i]]) {
				memoizedOrbits[orbiter] = current + 1;
				toodos.push_back(orbiter);
				whoDoIOrbit[orbiter] = toodos[i];
			}
		}
		unsigned total = 0;
		for (const auto& oc : memoizedOrbits) {
			total += oc.second;
		}

		std::vector<std::string> fromYou;
		std::unordered_set<std::string> fromYouSet;
		std::string currentNode = you;
		while (true) {
			currentNode = whoDoIOrbit[currentNode];
			fromYou.push_back(currentNode);
			fromYouSet.insert(currentNode);
			if (currentNode == "COM") {
				break;
			}
		}

		std::vector<std::string> fromSanta;
		currentNode = santa;
		while (true) {
			currentNode = whoDoIOrbit[currentNode];
			if (fromYouSet.count(currentNode) > 0) {
				break;
			}
		}

		auto memoizedYou = memoizedOrbits[you];
		auto memoizedSanta = memoizedOrbits[santa];
		auto memoizedAncestor = memoizedOrbits[currentNode];

		auto answer = (memoizedYou - memoizedAncestor) + (memoizedSanta - memoizedAncestor) - 2;

		return { std::to_string(total), std::to_string(answer) };
	}
}
