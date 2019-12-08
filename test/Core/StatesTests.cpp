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


namespace std {
	template<>
	struct hash<TestState> {
		size_t operator()(const TestState& obj) const {
			return std::hash<int>()(obj.id);
		}
	};
}
namespace core {

	TEST_CASE("Test finding the shortest path for 0-10 +1 int state range", "[Core][States]") {

		StateTransitionManager<TestState> stm;
		stm.setStartState(TestState{ 0 });
		stm.setStopState(TestState{ 10 });

		stm.goToEnd();

	}
}