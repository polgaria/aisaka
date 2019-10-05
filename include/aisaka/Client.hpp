#pragma once

#include <aegis/core.hpp>
#include <aegis/gateway/events/message_create.hpp>
#include <aegis/gateway/events/message_reaction_add.hpp>
#include <aisaka/command/Commands.hpp>
#include <mongocxx/pool.hpp>

namespace Aisaka {
class Client {
   public:
	Client(const std::string& default_prefix, const std::string& bot_name,
		   const int64_t& owner_id)
		: default_prefix(default_prefix),
		  bot_name(bot_name),
		  owner_id(owner_id) {}

	void set_bot(aegis::core& bot) { this->bot = &bot; }
	aegis::core& get_bot() { return *bot; }

	void set_mongo_pool(mongocxx::pool&& client) { this->mongo_pool = &client; }
	mongocxx::pool& get_mongo_pool() { return *mongo_pool; }

	void message_create(aegis::gateway::events::message_create obj);

   protected:
	aegis::core* bot;
	mongocxx::pool* mongo_pool;

	std::string default_prefix;
	std::string bot_name;
	int64_t owner_id;

	Aisaka::Commands commands;
};
}  // namespace Aisaka
