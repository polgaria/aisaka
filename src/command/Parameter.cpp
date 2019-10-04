#include <aisaka/command/Parameter.hpp>
#include <aisaka/command/util/GetterSetterMacro.hpp>

using Parameter = Aisaka::Parameter;

Parameter::Parameter(std::string_view _name) : _name(std::move(_name)) {}

GETTER_SETTER(required, Parameter, bool&)
GETTER_SETTER(name, Parameter, std::string_view&)