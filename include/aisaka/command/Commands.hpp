#pragma once

#include <aisaka/command/Command.hpp>
#include <aisaka/command/categories/Category.hpp>
#include <fifo_map.hpp>

namespace Aisaka {
class Commands {
   public:
	nlohmann::fifo_map<std::string, Aisaka::Command> all;
	std::unordered_map<std::string, Aisaka::Category> categories;

	void add_command(Aisaka::Command command, spdlog::logger& log);
};
}  // namespace Aisaka
