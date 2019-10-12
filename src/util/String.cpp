#include <aisaka/util/String.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>

std::deque<std::string_view> Aisaka::Util::String::split(
	const std::string_view& source, const char delim) {
	std::deque<std::string_view> tokens;
	std::size_t start = 0, end = 0;
	while ((end = source.find(delim, start)) != std::string::npos) {
		tokens.push_back(source.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(source.substr(start));
	return tokens;
}

std::deque<std::string_view> Aisaka::Util::String::split_command(
	const std::string_view& source, const std::string_view& prefix) {
	auto arguments = Aisaka::Util::String::split(source, ' ');
	arguments.push_front(prefix);

	return arguments;
}

std::string Aisaka::Util::String::to_lower(const std::string_view& source) {
	std::string string_lower{source};
	std::transform(string_lower.begin(), string_lower.end(),
				   string_lower.begin(),
				   [](unsigned char c) { return std::towlower(c); });

	return string_lower;
}