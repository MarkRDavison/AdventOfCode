#include <2019/Day14Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>
#include <cmath>

#define FUEL "FUEL"
#define ORE "ORE"

namespace TwentyNineteen {

	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("Space Stoichiometry", 2019, 14) {

	}
	Day14Puzzle::~Day14Puzzle() {

	}


	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(core::StringExtensions::splitStringByDelimeter(core::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	static ReactionOutput getMinimumAmountToFillRequirement(ReactionOutput _requiredAmount, ReactionOutput _outputSize) {
		return
			static_cast<ReactionOutput>(std::ceil(
				static_cast<double>(_requiredAmount) /
				static_cast<double>(_outputSize)));
	}

	ReactionOutput Day14Puzzle::howMuchOre(
		ReactionId _chemical, 
		ReactionOutput _amount,
		std::unordered_map<ReactionId, ReactionOutput>& _excess,
		std::unordered_map<ReactionId, Reaction>& _referenceData,
		unsigned _depth) {

		ReactionOutput ore = 0;

		if (_chemical == ORE) {
			return _amount;
		}

		auto recycle = std::min(_amount, _excess[_chemical]);
		_amount -= recycle;
		_excess[_chemical] -= recycle;

		auto reaction = _referenceData[_chemical];
		auto numReactions = getMinimumAmountToFillRequirement(_amount, reaction.output.amount);

		for (const auto& ingrediant : reaction.input) {
			ore += howMuchOre(ingrediant.name, numReactions * ingrediant.amount, _excess, _referenceData, _depth + 1);
		}

		_excess[_chemical] += numReactions * reaction.output.amount - _amount;

		return ore;
	}


	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {
		ReactionOutput part1 = 0;
		std::unordered_map<ReactionId, Reaction> reactions;
		for (const auto& l : m_InputLines) {
			const auto& p = core::StringExtensions::splitStringByDelimeter(l, ", =");
			const std::string outputName = p[p.size() - 1];
			auto& r = reactions[outputName];
			r.output.name = outputName;
			r.output.amount = std::stoi(p[p.size() - 2]);

			for (unsigned i = 0; i < p.size(); i += 2) {
				if (p[i] == ">") {
					break;
				}
				Ingrediant& ing = r.input.emplace_back();
				ing.amount = std::stoi(p[i]);
				ing.name = p[i + 1];
			}
		}

		std::unordered_map<ReactionId, ReactionOutput> excess;
		part1 = howMuchOre(FUEL, 1, excess, reactions, 0);

		ReactionOutput maxOre = 1000000000000;
		ReactionOutput fuel = 1;
		ReactionOutput lastFuel = 1;
		ReactionOutput lastGuess = part1;
		ReactionOutput guessChange = maxOre / 2;
		while (true) {
			std::unordered_map<ReactionId, ReactionOutput> excess2;
			lastFuel = fuel;
			lastGuess = howMuchOre(FUEL, fuel, excess2, reactions, 0);
			if (lastGuess != maxOre) {
				if (lastGuess < maxOre) {
					// increase fuel guess
					fuel = fuel + guessChange;
					guessChange /= 1.5;
				} else {
					// decrease fuel guess
					fuel = fuel - guessChange;
					guessChange /= 1.5;
				}
			}
			if (lastFuel == fuel) {
				break;
			}
		}




		return { std::to_string(part1), std::to_string(fuel) };
	}
}
