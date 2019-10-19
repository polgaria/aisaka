#include <aisaka/command/Metadata.hpp>
#include <aisaka/command/util/GetterSetterMacro.hpp>

using Metadata = Aisaka::Metadata;
using Examples = nlohmann::fifo_map<std::string, std::string>;

GETTER_SETTER(description, Metadata, const std::string&)
GETTER_SETTER_ARG(examples, Metadata, const Examples&, const Examples&&)