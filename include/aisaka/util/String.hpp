#pragma once

#include <deque>
#include <numeric>
#include <optional>
#include <sstream>

namespace Aisaka::Util {
class String {
   public:
	// https://stackoverflow.com/a/12155571
	template <typename Range, typename Value = typename Range::value_type>
	static std::string join(const Range& elements,
							const std::string_view delimiter) {
		return std::accumulate(
			elements.begin(), elements.end(), std::string(),
			[&delimiter](const std::string& a,
						 const std::string& b) -> std::string {
				return a + (a.length() > 0 ? delimiter.data() : "") + b;
			});
	}

	static std::deque<std::string> split(const std::string_view source,
										 const std::string_view delim);
	static std::string to_lower(const std::string_view);
};
}  // namespace Aisaka::Util
