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
	explicit Category(std::string_view name) : _name(name) {}
	virtual ~Category() = default;

	/// The function that initializes this category. It should add all of the
	/// category's commands to the provided Aisaka::Commands.
	virtual void init(spdlog::logger&, Aisaka::Commands<T>&) {}

	[[nodiscard]] const std::string& name() const noexcept {
		return this->_name;
	}

   protected:
	/// Can be used as a short form of the type required to initialize parameters.
	using Examples = const nlohmann::fifo_map<std::string, std::string>;

   private:
	std::string _name;
};
}  // namespace Aisaka