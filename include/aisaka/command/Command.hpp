#pragma once

#include <aegis.hpp>
#include <aisaka/command/Metadata.hpp>
#include <aisaka/command/Parameter.hpp>
#include <aisaka/command/categories/Category.hpp>
#include <deque>
#include <fifo_map.hpp>
#include <functional>
#include <unordered_set>

#define GETTER_SETTER(fname, type)                                 \
	[[nodiscard]] type fname() const noexcept { return _##fname; } \
	Command& fname(type fname) noexcept {                          \
		_##fname = fname;                                          \
		return *this;                                              \
	}

namespace Aisaka {
class Bot;

template <class T = Aisaka::Bot>
class Command {
   public:
	/// Constructs a command without a name.
	/**
	 * @rst
	 * .. note::
	 *	  This expects that you'll use the name setter to set a name for it later.
	 * @endrst
	 */
	Command() {}
	/// Constructs a command.
	/**
	 * @param name The name of the command
	 */
	explicit Command(std::string_view name) : _name(name) {}
	virtual ~Command() = default;

	/// The function each command should adhere to.
	using Function =
		std::function<void(aegis::gateway::events::message_create& obj,
						   T& client, const std::deque<std::string>& params,
						   const std::string_view command_prefix)>;

	GETTER_SETTER(name, const std::string&)
	GETTER_SETTER(category, const Aisaka::Category<T>&)
	GETTER_SETTER(params, const std::vector<Aisaka::Parameter>&)
	GETTER_SETTER(aliases, const std::unordered_set<std::string>&)
	GETTER_SETTER(metadata, const Aisaka::Metadata&)
	GETTER_SETTER(function, const Function&)
	GETTER_SETTER(owner_only, bool)

   private:
	std::string _name;
	Aisaka::Category<T> _category{"None"};

	std::vector<Aisaka::Parameter> _params;
	std::unordered_set<std::string> _aliases;
	Aisaka::Metadata _metadata;

	Function _function;
	bool _owner_only = false;
};
}  // namespace Aisaka

#undef GETTER_SETTER
