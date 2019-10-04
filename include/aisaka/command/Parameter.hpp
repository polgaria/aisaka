#pragma once

#include <string_view>

namespace Aisaka {
class Parameter {
   public:
	Parameter(std::string_view _name);

	const std::string_view& name() const noexcept;
	Parameter& name(const std::string_view& name) noexcept;

	const bool& required() const noexcept;
	Parameter& required(const bool& required) noexcept;

   private:
	std::string_view _name;
	bool _required = true;
};
}  // namespace Aisaka
