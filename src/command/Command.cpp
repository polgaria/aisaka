#include <aisaka/command/Command.hpp>
#include <aisaka/command/util/GetterSetterMacro.hpp>

using Command = Aisaka::Command;

Command::Command() {}
Command::Command(std::string _name) : _name(std::move(_name)) {}

using Category = Aisaka::Category;
using Parameter = Aisaka::Parameter;
using Metadata = Aisaka::Metadata;

GETTER_SETTER(name, Command, std::string&)
GETTER_SETTER(category, Command, Category&)
GETTER_SETTER(params, Command, std::deque<Parameter>&)
GETTER_SETTER(aliases, Command, std::unordered_set<std::string>&)
GETTER_SETTER(metadata, Command, Metadata&)
GETTER_SETTER(function, Command, Command::Function&)
GETTER_SETTER(owner_only, Command, bool&)