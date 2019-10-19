#pragma once

#include <aegis.hpp>
#include <aisaka/command/Commands.hpp>
#include <mongocxx/pool.hpp>
#include <unordered_map>

namespace Aisaka {
class Client {
   public:
	Client(const std::string_view& default_prefix, const std::string& bot_name,
		   const int64_t& owner_id)
		: _default_prefix(default_prefix),
		  _bot_name(bot_name),
		  _owner_id(owner_id) {}
	virtual ~Client();

	void bot(aegis::core& bot) noexcept { this->_bot = &bot; }
	void mongo_pool(mongocxx::pool&& client) noexcept {
		this->_mongo_pool = &client;
	}
	[[nodiscard]] auto bot() noexcept -> aegis::core& { return *this->_bot; }
	[[nodiscard]] auto mongo_pool() noexcept -> mongocxx::pool& {
		return *this->_mongo_pool;
	}

	[[nodiscard]] auto commands() const noexcept -> const Aisaka::Commands<>& {
		return this->_commands;
	}

	[[nodiscard]] auto default_prefix() noexcept -> std::string_view& {
		return this->_default_prefix;
	}
	[[nodiscard]] auto bot_name() noexcept -> std::string& {
		return this->_bot_name;
	}
	[[nodiscard]] auto owner_id() noexcept -> int64_t& {
		return this->_owner_id;
	}

	virtual void on_message_create(aegis::gateway::events::message_create) {}

   private:
	aegis::core* _bot;
	mongocxx::pool* _mongo_pool;

	std::string_view _default_prefix;
	std::string _bot_name;
	int64_t _owner_id;

	Aisaka::Commands<> _commands;
};
}  // namespace Aisaka
