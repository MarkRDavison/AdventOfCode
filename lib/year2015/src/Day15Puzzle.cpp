#include <2015/Day15Puzzle.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <unordered_map>
#include <functional>
#include <algorithm>

namespace TwentyFifteen {
	
	Day15Puzzle::Day15Puzzle() :
		core::PuzzleBase("Science for Hungry People", 2015, 15) {

	}
	Day15Puzzle::~Day15Puzzle() {

	}


	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {
		const auto& ingredients = parseInput(m_InputLines);

		int usedIngredients = 0;
		unsigned ingredientIndex = 0;

		struct Result {
			int ingredientCount[5];
			int totals[5];
		};

		const std::function<Result(int, unsigned, int[5], int[5], bool)> recurser = [&recurser,  &ingredients](int _usedIngredients, unsigned _ingredientIndex, int _currentTotals[5], int _currentIngredientCount[5], bool _part2) -> Result {
			int maximums[5] = { 0,0,0,0,0 };
			int maximum = 0;
			int maxIngredientCount[5];
			maxIngredientCount[0] = _currentIngredientCount[0];
			maxIngredientCount[1] = _currentIngredientCount[1];
			maxIngredientCount[2] = _currentIngredientCount[2];
			maxIngredientCount[3] = _currentIngredientCount[3];
			maxIngredientCount[4] = _currentIngredientCount[4];
			const auto& ingredient = ingredients[_ingredientIndex];

			for (int i = 0; i <= 100 - _usedIngredients; ++i) {

				int newTotals[5];

				newTotals[0] = _currentTotals[0] + ingredient.capacity * i;
				newTotals[1] = _currentTotals[1] + ingredient.durability * i;
				newTotals[2] = _currentTotals[2] + ingredient.flavour * i;
				newTotals[3] = _currentTotals[3] + ingredient.texture * i;
				newTotals[4] = _currentTotals[4] + ingredient.calories * i;

				if (_ingredientIndex < ingredients.size() - 1) {
					const auto& answer = recurser(_usedIngredients + i, _ingredientIndex + 1, newTotals, maxIngredientCount, _part2);

					const int t =
						std::max(0, answer.totals[0]) *
						std::max(0, answer.totals[1]) *
						std::max(0, answer.totals[2]) *
						std::max(0, answer.totals[3]);

					const int calories = answer.totals[4];

					if (maximum < t && (calories == 500 || !_part2)) {
						maximum = t;
						maximums[0] = answer.totals[0];
						maximums[1] = answer.totals[1];
						maximums[2] = answer.totals[2];
						maximums[3] = answer.totals[3];
						maximums[4] = answer.totals[4];
						maxIngredientCount[0] = answer.ingredientCount[0];
						maxIngredientCount[1] = answer.ingredientCount[1];
						maxIngredientCount[2] = answer.ingredientCount[2];
						maxIngredientCount[3] = answer.ingredientCount[3];
						maxIngredientCount[4] = answer.ingredientCount[4];
						maxIngredientCount[_ingredientIndex] = i;
					}
				}
				else {

					const int t =
						std::max(0, newTotals[0]) *
						std::max(0, newTotals[1]) *
						std::max(0, newTotals[2]) *
						std::max(0, newTotals[3]);

					const int calories = newTotals[4];

					if (maximum < t && (calories == 500 || !_part2)) {
						maximum = t;
						maximums[0] = newTotals[0];
						maximums[1] = newTotals[1];
						maximums[2] = newTotals[2];
						maximums[3] = newTotals[3];
						maximums[4] = newTotals[4];
						maxIngredientCount[_ingredientIndex] = i;
					}
				}
			}
			Result r;
			r.ingredientCount[0] = maxIngredientCount[0];
			r.ingredientCount[1] = maxIngredientCount[1];
			r.ingredientCount[2] = maxIngredientCount[2];
			r.ingredientCount[3] = maxIngredientCount[3];
			r.ingredientCount[4] = maxIngredientCount[4];
			r.totals[0] = maximums[0];
			r.totals[1] = maximums[1];
			r.totals[2] = maximums[2];
			r.totals[3] = maximums[3];
			r.totals[4] = maximums[4];
			return r;
		};

		int totals1[5] = { 0, 0, 0, 0, 0 };
		int ingredientCount1[5] = { 0, 0, 0, 0, 0 };
		const auto& ingred1Res = recurser(0, 0, totals1, ingredientCount1, false);

		const int answer1 =
			ingred1Res.totals[0] *
			ingred1Res.totals[1] *
			ingred1Res.totals[2] *
			ingred1Res.totals[3];

		int totals2[5] = { 0, 0, 0, 0, 0 };
		int ingredientCount2[5] = { 0, 0, 0, 0, 0 };
		const auto& ingred2Res = recurser(0, 0, totals2, ingredientCount2, true);

		const int answer2 =
			ingred2Res.totals[0] *
			ingred2Res.totals[1] *
			ingred2Res.totals[2] *
			ingred2Res.totals[3];


		return { std::to_string(answer1), std::to_string(answer2) };
	}

	std::vector<Ingredient> Day15Puzzle::parseInput(const std::vector<std::string>& _inputLines) {
		std::vector<Ingredient> result;

		for (const auto& i : _inputLines) {
			const auto& s = ze::StringExtensions::splitStringByDelimeter(i, ":, ");

			Ingredient& ing = result.emplace_back();
			ing.name = s[0];
			ing.capacity = stoi(s[2]);
			ing.durability = stoi(s[4]);
			ing.flavour = stoi(s[6]);
			ing.texture = stoi(s[8]);
			ing.calories = stoi(s[10]);
		}

		return result;
	}
}
