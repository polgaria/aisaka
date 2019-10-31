#pragma once

#include <aegis.hpp>
#include <aisaka/command/Commands.hpp>

namespace Aisaka {
class Bot {
   public:
	/// Constructs a Bot.
	/**
	 * @param default_prefix The bot's default prefix.
	 * @param name The bot's name.
	 * @param owner_id The ID of the bot's owner. If not passed, the owner ID will be set to -1.
	 */
	Bot(const std::string_view default_prefix, const std::string_view name,
		const int64_t owner_id = -1)
		: _core(aegis::core(spdlog::level::trace)),
		  _default_prefix(default_prefix),
		  _name(name),
		  _owner_id(owner_id) {
		this->_core.set_on_message_create(std::bind(
			&Aisaka::Bot::on_message_create, this, std::placeholders::_1));
	}
	virtual ~Bot();

	[[nodiscard]] aegis::core& core() noexcept { return this->_core; }

	[[nodiscard]] const Aisaka::Commands<>& commands() const noexcept {
		return this->_commands;
	}

	[[nodiscard]] std::string& default_prefix() noexcept {
		return this->_default_prefix;
	}

	[[nodiscard]] std::string& name() noexcept { return this->_name; }

	[[nodiscard]] int64_t& owner_id() noexcept { return this->_owner_id; }

	/// This is where your commands should be handled.
	virtual void on_message_create(aegis::gateway::events::message_create) {}

   private:
	Aisaka::Commands<> _commands;
	aegis::core _core;

	std::string _default_prefix;
	std::string _name;
	int64_t _owner_id;
};
}  // namespace Aisaka
