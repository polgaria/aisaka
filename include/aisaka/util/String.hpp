#pragma once

#include <deque>
#include <iterator>
#include <optional>
#include <sstream>

namespace Aisaka::Util {
class String {
   public:
	// https://stackoverflow.com/questions/5288396/c-ostream-out-manipulation/5289170#5289170
	template <typename Range, typename Value = typename Range::value_type>
	static std::string join(const Range& elements,
							const std::string& delimiter) {
		std::ostringstream os;
		auto b = begin(elements);
		auto e = end(elements);

		if (b != e) {
			std::copy(b, prev(e),
					  std::ostream_iterator<Value>(os, delimiter.c_str()));
			b = prev(e);
		}
		if (b != e) {
			os << *b;
		}

		return os.str();
	}

	static std::deque<std::string_view> split(const std::string_view& source,
											  char delim);
	static std::deque<std::string_view> split_command(
		const std::string_view& source, const std::string_view& prefix);
	static std::string to_lower(const std::string_view&);
};
}  // namespace Aisaka::Util
