#pragma once

#include <aegis.hpp>
#include <aisaka/command/Commands.hpp>
#include <mongocxx/pool.hpp>
#include <unordered_map>

namespace Aisaka {
class Bot {
   public:
	/// Constructs a Bot.
	/**
	 * @param default_prefix The bot's default prefix
	 * @param bot_name The bot's name
	 * @param owner_id The ID of the bot's owner
	 */
	Bot(const std::string_view& default_prefix, const std::string& name,
		const int64_t& owner_id)
		: _default_prefix(default_prefix), _name(name), _owner_id(owner_id) {}
	virtual ~Bot();

	void core(aegis::core& core) noexcept { this->_core = &core; }
	[[nodiscard]] aegis::core& core() noexcept { return *this->_core; }

	/**
	 * @deprecated since 2.1
	 * @see core(aegis::core& core)
	 */
	[[deprecated("Renamed to Aisaka::Bot::core")]] void bot(
		aegis::core& bot) noexcept {
		this->_core = &bot;
	}
	/**
	 * @deprecated since 2.1
	 * @see core()
	 */
	[[deprecated("Renamed to Aisaka::Bot::core")]] [[nodiscard]] aegis::core&
	bot() noexcept {
		return *this->_core;
	}

	/**
	 * @deprecated since 2.1
	 */
	[[deprecated]] void mongo_pool(mongocxx::pool&& client) noexcept {
		this->_mongo_pool = &client;
	}
	/**
	 * @deprecated since 2.1
	 */
	[[deprecated]] [[nodiscard]] mongocxx::pool& mongo_pool() noexcept {
		return *this->_mongo_pool;
	}

	[[nodiscard]] const Aisaka::Commands<>& commands() const noexcept {
		return this->_commands;
	}

	[[nodiscard]] std::string_view& default_prefix() noexcept {
		return this->_default_prefix;
	}

	[[nodiscard]] std::string& name() noexcept { return this->_name; }
	/**
	 * @deprecated since 2.1
	 * @see name()
	 */
	[[deprecated("Renamed to Aisaka::Bot::name")]] [[nodiscard]] std::string&
	bot_name() noexcept {
		return this->_name;
	}

	[[nodiscard]] int64_t& owner_id() noexcept { return this->_owner_id; }

	virtual void on_message_create(aegis::gateway::events::message_create) {}

   private:
	aegis::core* _core;
	/**
	 * @deprecated since 2.1
	 */
	[[deprecated]] mongocxx::pool* _mongo_pool;

	std::string_view _default_prefix;
	std::string _name;
	int64_t _owner_id;

	Aisaka::Commands<> _commands;
};
}  // namespace Aisaka
