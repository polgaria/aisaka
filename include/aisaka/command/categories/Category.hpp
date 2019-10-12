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
	const std::string& get_name() const noexcept { return this->name; }

   protected:
	using Examples = const nlohmann::fifo_map<std::string, std::string>;

   private:
	std::string name;
};
}  // namespace Aisaka