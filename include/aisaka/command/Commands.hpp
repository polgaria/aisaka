#pragma once

#include <robin_hood.h>

#include <aisaka/command/Command.hpp>
#include <aisaka/command/categories/Category.hpp>
#include <fifo_map.hpp>

namespace Aisaka {
template <class T>
class Commands {
   public:
	/// All of the commands that have been added, with the key being the name of each one.
	robin_hood::unordered_map<std::string, Aisaka::Command<T>> all;
	/// All of the categories that have been added, with the key being the name of each one.
	robin_hood::unordered_map<std::string, Aisaka::Category<T>> categories;

	/// Adds a command and its aliases.
	/**
	 * @param command The command to be added.
	 * @param log The logger to be used.
	 */
	void add_command(Aisaka::Command<T> command, spdlog::logger& log) {
		const auto& category_name = command.category().name().data();
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

	/// Searches for a command.
	/**
	 * @param command_name The name of the command to search for.
	 * @return If no command was found, std::nullopt; if one *was* found, the command itself.
	 */
	const std::optional<Aisaka::Command<T>> find_command(
		const std::string& command_name) const {
		const auto& command = all.find(command_name);
		if (command != all.end()) {
			return (*command).second;
		}
		return std::nullopt;
	}

	/// Searches for a category.
	/**
	 * @param category_name The name of the category to search for.
	 * @return If no category was found, return std::nullopt; if one *was* found, the category itself.
	 */
	const std::optional<Aisaka::Category<T>> find_category(
		const std::string& category_name) const {
		const auto& category = categories.find(category_name);
		if (category != categories.end()) {
			return (*categories).second;
		}
		return std::nullopt;
	}
};
}  // namespace Aisaka
