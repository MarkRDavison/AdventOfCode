#ifndef INCLUDED_ADVENT_OF_CODE_CORE_STRING_EXTENSIONS_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_STRING_EXTENSIONS_HPP_

#include <vector>
#include <string>

namespace core {
	class StringExtensions {
	public:
		static std::string loadFileToString(const std::string& _path);
		static std::vector<std::string> splitStringByDelimeter(const std::string& _parameter, const std::string& _delimeter);

	private:
		StringExtensions(void) = delete;
		~StringExtensions(void) = delete;
	};
}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_STRING_EXTENSIONS_HPP_