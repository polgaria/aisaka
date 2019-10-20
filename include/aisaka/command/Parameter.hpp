#pragma once

#include <string_view>

namespace Aisaka {
class Parameter {
   public:
	/// Constructs a parameter.
	/**
	 * @verbatim embed:rst:leading-asterisk
	 * .. note::
	 *    By default, prefixes are required.
	 * @endverbatim
	 *
	 * @param name The parameter's name
	 */
	explicit Parameter(std::string_view name);

	[[nodiscard]] const std::string_view& name() const noexcept;
	Parameter& name(const std::string_view& name) noexcept;

	[[nodiscard]] bool required() const noexcept;
	Parameter& required(bool required) noexcept;

   private:
	std::string_view _name;
	bool _required = true;
};
}  // namespace Aisaka
