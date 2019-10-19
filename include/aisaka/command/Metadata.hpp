#pragma once

#include <fifo_map.hpp>

namespace Aisaka {
class Metadata {
   public:
	[[nodiscard]] auto description() const noexcept -> const std::string&;
	auto description(const std::string& description) noexcept -> Metadata&;

	[[nodiscard]] auto examples() const noexcept
		-> const nlohmann::fifo_map<std::string, std::string>&;
	auto examples(
		const nlohmann::fifo_map<std::string, std::string>&& examples) noexcept
		-> Metadata&;

   private:
	std::string _description;
	nlohmann::fifo_map<std::string, std::string> _examples;
};
}  // namespace Aisaka
