#include <aegis/channel.hpp>
#include <aegis/gateway/events/message_create.hpp>
#include <aegis/guild.hpp>
#include <aegis/user.hpp>
#include <aisaka/Client.hpp>
#include <aisaka/command/Commands.hpp>
#include <aisaka/util/String.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>

Aisaka::Client::Client(const std::string& default_prefix,
					   const std::string& bot_name, const int64_t& owner_id)
	: default_prefix(default_prefix), bot_name(bot_name), owner_id(owner_id) {}
Aisaka::Client::~Client() = default;

void Aisaka::Client::message_create(
	aegis::gateway::events::message_create obj) {
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;

	// don't want it to be responding to other bots
	if (obj.msg.get_user().is_bot()) {
		return;
	}
	auto content{obj.msg.get_content()};

	// try to find an existing custom prefix
	// if not found, use default prefix
	std::string prefix{};
	const auto& mongo_client = get_mongo_pool().acquire();
	const auto& op_result =
		(*mongo_client)[this->bot_name]["prefixes"].find_one(
			document{} << "id" << obj.msg.get_guild().get_id() << finalize);
	if (!op_result && !content.compare(0, this->default_prefix.size(),
									   this->default_prefix)) {
		prefix = this->default_prefix;
	} else if (op_result) {
		for (const auto& res : op_result->view()["prefix"].get_array().value) {
			const auto& _prefix = std::string{res.get_utf8().value};
			if (!content.compare(0, _prefix.size(), _prefix)) {
				prefix = _prefix;
				break;
			}
		}
	} else {
		return;
	}

	// check if it starts with the configured prefix
	if (!prefix.empty()) {
		auto params = Aisaka::Util::String::split_command(
			content.erase(0, prefix.length()), prefix);
		if (
			// only allow if it has at least 1 parameter
			params.size() <= 1 &&
			// only allow if starts with prefix
			params.front() != prefix) {
			return;
		}

		// remove the params as we go
		params.pop_front();
		// make command name lower-case
		const auto& command_name =
			Aisaka::Util::String::to_lower(params.front());
		if (params.empty()) {
			return;
		}

		// get command
		const auto& found_command = this->commands.all.find(command_name);
		if (found_command == this->commands.all.end()) {
			obj.channel.create_message("Command not found.");
			return;
		}
		params.pop_front();

		// if the command is owner-only
		if (found_command->second.owner_only()) {
			// check if user is the bot owner
			const auto& user_id = obj.msg.get_user().get_id().get();
			if (user_id != this->owner_id) {
				obj.channel.create_message("You are not the bot's owner!");
				return;
			}
		}

		// check how many parameters are required
		unsigned short required_params = 0;
		for (const auto& param : found_command->second.params()) {
			if (param.required()) {
				required_params++;
			}
		}
		if (params.size() < required_params) {
			obj.channel.create_message("Too few parameters.");
			return;
		}

		// call command
		found_command->second.function()(obj, *this, params, prefix);
	}
}
