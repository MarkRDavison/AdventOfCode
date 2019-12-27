#include <catch/catch.hpp>
#include <Core/States.hpp>

struct PointlessStateInfo {};

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

	std::vector<MCState> enumerate(const PointlessStateInfo& _info) const {
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

	unsigned cost(const MCState& _targetState, const PointlessStateInfo& _info) const {
		return 1;
	}

	bool valid(const PointlessStateInfo& _info) const {
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

// Farmer Fox Chicken Grain State
struct FFCGState {

	enum class Side {
		Left = 0,
		Right = 1
	};

	FFCGState() {}
	FFCGState(Side _farmer, Side _fox, Side _chicken, Side _grain) :
		farmer(_farmer),
		fox(_fox),
		chicken(_chicken),
		grain(_grain) { }

	Side farmer{ Side::Left };
	Side fox{ Side::Left };
	Side chicken{ Side::Left };
	Side grain{ Side::Left };

	std::vector<FFCGState> enumerate(const PointlessStateInfo& _info) const {
		std::vector<FFCGState> available;

		if (farmer == Side::Left) {
			available.push_back(FFCGState(Side::Right, fox, chicken, grain));

			if (fox == Side::Left) {
				available.push_back(FFCGState(Side::Right, Side::Right, chicken, grain));
			}
			if (chicken == Side::Left) {
				available.push_back(FFCGState(Side::Right, fox, Side::Right, grain));
			}
			if (grain == Side::Left) {
				available.push_back(FFCGState(Side::Right, fox, chicken, Side::Right));
			}
		} else {
			available.push_back(FFCGState(Side::Left, fox, chicken, grain));

			if (fox == Side::Right) {
				available.push_back(FFCGState(Side::Left, Side::Left, chicken, grain));
			}
			if (chicken == Side::Right) {
				available.push_back(FFCGState(Side::Left, fox, Side::Left, grain));
			}
			if (grain == Side::Right) {
				available.push_back(FFCGState(Side::Left, fox, chicken, Side::Left));
			}
		}

		return available;
	}

	std::string str() const {
		std::stringstream ss;

		ss 
			<< (farmer == Side::Left ? "F" : " ") << " "
			<< (fox == Side::Left ? "f" : " ") << " "
			<< (chicken == Side::Left ? "c" : " ") << " "
			<< (grain == Side::Left ? "g" : " ")
			<< "  ~~~~~  "
			<< (farmer == Side::Right ? "F" : " ") << " "
			<< (fox == Side::Right ? "f" : " ") << " "
			<< (chicken == Side::Right ? "c" : " ") << " "
			<< (grain == Side::Right ? "g" : " ");

		return ss.str();
	}

	unsigned cost(const FFCGState& _targetState, const PointlessStateInfo& _info) const {
		return 1;
	}

	bool valid(const PointlessStateInfo& _info) const {
		if (chicken == grain && chicken != farmer) {
			return false;
		}
		if (fox == chicken && fox != farmer) {
			return false;
		}
		return true;
	}

	inline bool operator==(const FFCGState& _other) const {
		return
			farmer   == _other.farmer &&
			fox      == _other.fox &&
			chicken  == _other.chicken &&
			grain    == _other.grain;
	}

	inline bool operator!=(const FFCGState& _other) const {
		return !(*this == _other);
	}
};

namespace std {
	template<>
	struct hash<MCState> {
		size_t operator()(const MCState& obj) const {
			return std::hash<std::string>()(obj.str());
		}
	};
	template<>
	struct hash<FFCGState> {
		size_t operator()(const FFCGState& obj) const {
			return std::hash<std::string>()(obj.str());
		}
	};
}
namespace core {

	TEST_CASE("Missionaries & Cannibals", "[Core][States]"){
		constexpr int amount = 3;
		PointlessStateInfo info{};
		StateTransitionManager<MCState, PointlessStateInfo> stm(info);

		MCState start(amount, 0, amount, 0, true);
		MCState end(0, amount, 0, amount, false);

		const auto& path = stm.getShortestSolution(start, end);
		REQUIRE_FALSE(path.empty());
		REQUIRE(11 == path.size() - 1);
		REQUIRE(start.str() == path.front().str());
		REQUIRE(end.str() == path.back().str());
	}

	TEST_CASE("Farmer, Fox, Chicken and Grain", "[Core][States]") {
		PointlessStateInfo info{};
		StateTransitionManager<FFCGState, PointlessStateInfo> stm(info);
		FFCGState start(FFCGState::Side::Left, FFCGState::Side::Left, FFCGState::Side::Left, FFCGState::Side::Left);
		FFCGState end(FFCGState::Side::Right, FFCGState::Side::Right, FFCGState::Side::Right, FFCGState::Side::Right);
		
		const auto& path = stm.getShortestSolution(start, end);
 		REQUIRE_FALSE(path.empty());
		REQUIRE(7 == path.size() - 1);
		REQUIRE(start.str() == path.front().str());
		REQUIRE(end.str() == path.back().str());
	}

}