#pragma once

#include <spdlog/logger.h>

#include <fifo_map.hpp>

namespace Aisaka {
class Client;

template <class T = Aisaka::Client>
class Commands;

template <class T = Aisaka::Client>
class Category {
   public:
	Category(std::string name) : name(std::move(name)) {}
	virtual ~Category() = default;

	virtual void init(spdlog::logger&, Aisaka::Commands<T>&) {}
	[[nodiscard]] auto get_name() const noexcept -> const std::string& {
		return this->name;
	}

   protected:
	using Examples = const nlohmann::fifo_map<std::string, std::string>;

   private:
	std::string name;
};
}  // namespace Aisaka