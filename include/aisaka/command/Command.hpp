#pragma once

#include <aegis/gateway/events/message_create.hpp>
#include <aisaka/command/Metadata.hpp>
#include <aisaka/command/Parameter.hpp>
#include <aisaka/command/categories/Category.hpp>
#include <deque>
#include <fifo_map.hpp>
#include <functional>
#include <unordered_set>

namespace Aisaka {
class Client;
class Command {
   public:
	using Parameter = Aisaka::Parameter;
	using Metadata = Aisaka::Metadata;

	using Function = std::function<void(
		aegis::gateway::events::message_create& obj, Aisaka::Client& client,
		const std::deque<std::string>& params,
		const std::string& command_prefix)>;

	Command();
	Command(std::string _name);

	const std::string& name() const noexcept;
	Command& name(const std::string& name) noexcept;

	const Aisaka::Category& category() const noexcept;
	Command& category(const Aisaka::Category& category) noexcept;

	const std::deque<Parameter>& params() const noexcept;
	Command& params(const std::deque<Parameter>& params) noexcept;

	const std::unordered_set<std::string>& aliases() const noexcept;
	Command& aliases(const std::unordered_set<std::string>& aliases) noexcept;

	const Metadata& metadata() const noexcept;
	Command& metadata(const Metadata& metadata) noexcept;

	const Function& function() const noexcept;
	Command& function(const Function& function) noexcept;

	const bool& owner_only() const noexcept;
	Command& owner_only(const bool& is_owner_only) noexcept;

   private:
	std::string _name;
	Aisaka::Category _category = Aisaka::Category("None");

	std::deque<Parameter> _params;
	std::unordered_set<std::string> _aliases;
	Metadata _metadata = Metadata();

	Function _function;
	bool _owner_only = false;
};
}  // namespace Aisaka
