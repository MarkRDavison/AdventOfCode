#include <catch/catch.hpp>
#include <Core/States.hpp>


struct TestState {
	int id{ 0 };

	std::string str() const {
		return std::to_string(id);
	}

	std::vector<TestState> enumerate() const {
		std::vector<TestState> available{};

		available.push_back(TestState{ id - 1 });
		available.push_back(TestState{ id + 1 });

		return available;
	}

	unsigned cost(const TestState& _targetState) const {
		return 1;
	}

	bool valid() const {
		return id >= 0 && id <= 10;
	}

	inline bool operator==(const TestState& _other) const {
		return id == _other.id;
	}

	inline bool operator!=(const TestState& _other) const {
		return id != _other.id;
	}

};

struct MCState {

	MCState() : MCState(-1, -1, -1, -1, false) {}
	MCState(int _mLeft, int _mRight, int _cLeft, int _cRight, bool _bLeft) :
		mLeft(_mLeft),
		mRight(_mRight),
		cLeft(_cLeft),
		cRight(_cRight),
		bLeft(_bLeft) {

	}

	int mLeft;
	int mRight;

	bool bLeft;

	int cLeft;
	int cRight;

	std::string str() const {
		std::stringstream ss;

		ss << "M(" << mLeft << ") C(" << cLeft << ") " << (bLeft ? "(B)      " : "      (B)") << " ~~ M("
			<< mRight << ") C(" << cRight << ")";

		return ss.str();
	}

	std::vector<MCState> enumerate() const {
		std::vector<MCState> available{};

		if (bLeft) {
			// Can move some to the right
			if (mLeft > 0) {
				available.push_back(MCState(mLeft-1, mRight+1, cLeft, cRight, false));
			}
			if (cLeft > 0) {
				// move 1 c ->
				available.push_back(MCState(mLeft, mRight, cLeft-1, cRight+1, false));
			}
			if (mLeft > 1) {
				// move 2 m ->
				available.push_back(MCState(mLeft-2, mRight+2, cLeft, cRight, false));
			}
			if (cLeft > 1) {
				// move 2 c ->
				available.push_back(MCState(mLeft, mRight, cLeft-2, cRight+2, false));
			}
			if (mLeft > 0 &&
				cLeft > 0) {
				// move 1 m & 1 c ->
				available.push_back(MCState(mLeft-1, mRight+1, cLeft-1, cRight+1, false));
			}

		} else {
			// Can move some to the left
			if (mRight > 0) {
				// move 1 m <-
				available.push_back(MCState(mLeft+1, mRight-1, cLeft, cRight, true));
			}
			if (cRight > 0) {
				// move 1 c <-
				available.push_back(MCState(mLeft, mRight, cLeft+1, cRight-1, true));
			}
			if (mRight > 1) {
				// move 2 m <-
				available.push_back(MCState(mLeft+2, mRight-2, cLeft, cRight, true));
			}
			if (cRight > 1) {
				// move 2 c <-
				available.push_back(MCState(mLeft, mRight, cLeft+2, cRight-2, true));
			}
			if (mRight > 0 &&
				cRight > 0) {
				// move 1 m & 1 c <-
				available.push_back(MCState(mLeft+1, mRight-1, cLeft+1, cRight-1, true));
			}
		}

		return available;
	}

	unsigned cost(const MCState& _targetState) const {
		return 1;
	}

	bool valid() const {
		return 
			(mLeft == 0 ||mLeft >= cLeft) &&
			(mRight == 0 || mRight >= cRight);
	}

	inline bool operator==(const MCState& _other) const {
		return
			mLeft == _other.mLeft &&
			mRight == _other.mRight &&
			cLeft == _other.cLeft &&
			cRight == _other.cRight &&
			bLeft == _other.bLeft;
	}

	inline bool operator!=(const MCState& _other) const {
		return !((*this) == _other);
	}
};

namespace std {
	template<>
	struct hash<TestState> {
		size_t operator()(const TestState& obj) const {
			return std::hash<int>()(obj.id);
		}
	};
	template<>
	struct hash<MCState> {
		size_t operator()(const MCState& obj) const {
			return std::hash<std::string>()(obj.str());
		}
	};
}
namespace core {

	TEST_CASE("Test finding the shortest path for 0-10 +1 int state range", "[Core][States]") {

		StateTransitionManager<TestState> stm;
		stm.getShortestSolution(TestState{ 0 }, TestState{ 10 });
	}



	TEST_CASE("Missionaries & Cannibals", "[Core][States]"){
		constexpr int amount = 3;
		StateTransitionManager<MCState> stm;

		MCState start(amount, 0, amount, 0, true);
		MCState end(0, amount, 0, amount, false);

		const auto& path = stm.getShortestSolution(start, end);
		REQUIRE_FALSE(path.empty());
		REQUIRE(12 == path.size());
		REQUIRE(start.str() == path.front().str());
		REQUIRE(end.str() == path.back().str());
		for (const auto& p : path) {
			std::cout << p.str() << std::endl;
		}
	}

}