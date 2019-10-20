#pragma once

#include <spdlog/logger.h>

#include <fifo_map.hpp>

namespace Aisaka {
class Bot;

template <class T = Aisaka::Bot>
class Commands;

template <class T = Aisaka::Bot>
class Category {
   public:
	explicit Category(std::string name) : _name(std::move(name)) {}
	virtual ~Category() = default;

	/// The function that initializes this category. It should add all of the
	/// category's commands to the provided Aisaka::Commands.
	virtual void init(spdlog::logger&, Aisaka::Commands<T>&) {}

	[[deprecated("Renamed to Aisaka::Category::name")]] [[nodiscard]] auto
	get_name() const noexcept -> const std::string& {
		return this->_name;
	}
	[[nodiscard]] auto name() const noexcept -> const std::string& {
		return this->_name;
	}

   protected:
	/// Can be used as a short form of the type required to initialize parameters.
	using Examples = const nlohmann::fifo_map<std::string, std::string>;

   private:
	// perhaps this should be a std::string_view?
	std::string _name;
};
}  // namespace Aisaka