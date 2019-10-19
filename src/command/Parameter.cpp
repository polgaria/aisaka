#include <aisaka/command/Parameter.hpp>
#include <aisaka/command/util/GetterSetterMacro.hpp>

using Parameter = Aisaka::Parameter;

Parameter::Parameter(std::string_view name) : _name(name) {}

GETTER_SETTER(required, Parameter, bool)
GETTER_SETTER(name, Parameter, const std::string_view&)