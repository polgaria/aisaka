#pragma once

#include <fifo_map.hpp>

namespace Aisaka {
class Metadata {
   public:
	const std::string& description() const noexcept;
	Metadata& description(const std::string& description) noexcept;

	const nlohmann::fifo_map<std::string, std::string>& examples() const
		noexcept;
	Metadata& examples(
		const nlohmann::fifo_map<std::string, std::string>&& examples) noexcept;

   private:
	std::string _description;
	nlohmann::fifo_map<std::string, std::string> _examples;
};
}  // namespace Aisaka
