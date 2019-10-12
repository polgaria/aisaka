#pragma once

#include <aegis/core.hpp>
#include <aegis/gateway/events/message_create.hpp>
#include <aegis/gateway/events/message_reaction_add.hpp>
#include <aisaka/command/Commands.hpp>
#include <mongocxx/pool.hpp>
#include <unordered_map>

namespace Aisaka {
class Client {
   public:
	Client(const std::string_view& default_prefix, const std::string& bot_name,
		   const int64_t& owner_id)
		: default_prefix(default_prefix),
		  bot_name(bot_name),
		  owner_id(owner_id) {}
	virtual ~Client() = default;

	virtual void set_bot(aegis::core& bot) noexcept { this->bot = &bot; }
	virtual aegis::core& get_bot() noexcept { return *bot; }

	const Aisaka::Commands<>& get_commands() const noexcept {
		return this->commands;
	}
	virtual std::unordered_multimap<int64_t, std::string>&
	get_prefix_cache() noexcept {
		return this->prefix_cache;
	}

	virtual void set_mongo_pool(mongocxx::pool&& client) noexcept {
		this->mongo_pool = &client;
	}
	virtual mongocxx::pool& get_mongo_pool() noexcept { return *mongo_pool; }

	virtual void message_create(aegis::gateway::events::message_create obj);

   protected:
	aegis::core* bot;
	mongocxx::pool* mongo_pool;

	std::string_view default_prefix;
	std::string bot_name;
	int64_t owner_id;

	Aisaka::Commands<> commands;

	std::unordered_multimap<int64_t, std::string> prefix_cache;
};
}  // namespace Aisaka
