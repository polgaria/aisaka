#pragma once

#include <string>
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
	explicit Parameter(std::string_view name) : _name(name) {}

	[[nodiscard]] const std::string& name() const noexcept {
		return this->_name;
	}
	Parameter& name(const std::string_view name) noexcept {
		this->_name = name;
		return *this;
	}

	[[nodiscard]] bool required() const noexcept { return this->_required; }
	Parameter& required(bool required) noexcept {
		this->_required = required;
		return *this;
	}

   private:
	std::string _name;
	bool _required = true;
};
}  // namespace Aisaka
