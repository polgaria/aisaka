#include <aisaka/command/Command.hpp>
#include <aisaka/command/Commands.hpp>

void Aisaka::Commands::add_command(Aisaka::Command command,
								   spdlog::logger& log) {
	if (categories.find(command.category().get_name()) == categories.end()) {
		categories.emplace(command.category().get_name(), command.category());
	}

	if (all.find(command.name()) != all.end()) {
		log.error("Tried to add duplicate command {}!", command.name());
		return;
	}
	log.info("Adding command {} (category {})", command.name(),
			 command.category().get_name());
	all.emplace(command.name(), command);
	if (!command.aliases().empty()) {
		for (const auto& alias : command.aliases()) {
			log.info("Adding alias {} for command {} (category {})", alias,
					 command.name(), command.category().get_name());
			all.emplace(alias, command);
		}
	}
}