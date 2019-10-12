#pragma once

#include <aisaka/command/Command.hpp>
#include <aisaka/command/categories/Category.hpp>
#include <fifo_map.hpp>

namespace Aisaka {
template <class T>
class Commands {
   public:
	nlohmann::fifo_map<std::string, Aisaka::Command<T>> all;
	std::unordered_map<std::string, Aisaka::Category<T>> categories;

	virtual void add_command(Aisaka::Command<T> command, spdlog::logger& log) {
		const auto& category_name = command.category().get_name().data();
		const auto& command_name = command.name().data();
		if (categories.find(category_name) == categories.end()) {
			categories.emplace(category_name, command.category());
		}

		if (all.find(command_name) != all.end()) {
			log.error("Tried to add duplicate command {}!", command_name);
			return;
		}
		log.info("Adding command {} (category {})", command_name,
				 category_name);
		all.emplace(command_name, command);
		if (!command.aliases().empty()) {
			for (const auto& alias : command.aliases()) {
				log.info("Adding alias {} for command {} (category {})",
						 alias.data(), command_name, category_name);
				all.emplace(alias.data(), command);
			}
		}
	}

	virtual const std::optional<Aisaka::Command<T>> find_command(
		const std::string_view& command_name) const {
		const auto& command = all.find(std::string{command_name});
		return command != all.end() ? std::make_optional((*command).second)
									: std::nullopt;
	}

	virtual const std::optional<Aisaka::Category<T>> find_category(
		const std::string_view& category_name) const {
		const auto& category = categories.find(std::string{category_name});
		return category != categories.end()
				   ? std::make_optional((*category).second)
				   : std::nullopt;
	}
};
}  // namespace Aisaka
