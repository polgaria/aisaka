#include <aisaka/util/String.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>

std::deque<std::string> Aisaka::Util::String::split(
	const std::string_view source, const std::string_view delim) {
	std::deque<std::string> output;

	for (auto first = source.data(), second = source.data(),
			  last = first + source.length();
		 second != last && first != last; first = second + 1) {
		second = std::find_first_of(first, last, std::cbegin(delim),
									std::cend(delim));

		if (first != second) {
			output.emplace_back(first, second - first);
		}
	}

	return output;
}

std::string Aisaka::Util::String::to_lower(const std::string_view source) {
	std::string string_lower(source);

	std::transform(string_lower.begin(), string_lower.end(),
				   string_lower.begin(),
				   [](unsigned char c) { return std::tolower(c); });

	return string_lower;
}