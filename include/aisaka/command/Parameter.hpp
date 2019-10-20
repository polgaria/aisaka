#pragma once

#include <string_view>

namespace Aisaka {
class Parameter {
   public:
	/// Constructs a command parameter.
	/**
	 * @rst
	 * .. note::
	 *    By default, command parameters are required.
	 * @endrst
	 *
	 * @param name The parameter's name.
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
