#pragma once

#include <string_view>

namespace Aisaka {
class Parameter {
   public:
	Parameter(std::string_view _name);

	[[nodiscard]] auto name() const noexcept -> const std::string_view&;
	auto name(const std::string_view& name) noexcept -> Parameter&;

	[[nodiscard]] auto required() const noexcept -> bool;
	auto required(bool required) noexcept -> Parameter&;

   private:
	std::string_view _name;
	bool _required = true;
};
}  // namespace Aisaka
