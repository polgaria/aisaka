#pragma once

#include <aegis/gateway/events/message_create.hpp>
#include <aisaka/command/Metadata.hpp>
#include <aisaka/command/Parameter.hpp>
#include <aisaka/command/categories/Category.hpp>
#include <deque>
#include <fifo_map.hpp>
#include <functional>
#include <unordered_set>

#define GETTER_SETTER(fname, type)                   \
	type fname() const noexcept { return _##fname; } \
	Command& fname(type fname) noexcept {            \
		_##fname = fname;                            \
		return *this;                                \
	}

namespace Aisaka {
class Client;

template <class T = Aisaka::Client>
class Command {
   public:
	Command() {}
	Command(std::string_view name) : _name(std::move(name)) {}
	virtual ~Command() = default;

	using Function = std::function<void(
		aegis::gateway::events::message_create& obj, T& client,
		const std::deque<std::string_view>& params,
		const std::string& command_prefix)>;

	GETTER_SETTER(name, const std::string_view&)
	GETTER_SETTER(category, const Aisaka::Category<T>&)
	GETTER_SETTER(params, const std::deque<Aisaka::Parameter>&)
	GETTER_SETTER(aliases, const std::unordered_set<std::string_view>&)
	GETTER_SETTER(metadata, const Aisaka::Metadata&)
	GETTER_SETTER(function, const Function&)
	GETTER_SETTER(owner_only, bool)

   private:
	std::string_view _name;
	Aisaka::Category<T> _category{"None"};

	std::deque<Aisaka::Parameter> _params;
	std::unordered_set<std::string_view> _aliases;
	Aisaka::Metadata _metadata = Metadata();

	Function _function;
	bool _owner_only = false;
};
}  // namespace Aisaka

#undef GETTER_SETTER
