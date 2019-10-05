#pragma once

#include <spdlog/logger.h>
#include <fifo_map.hpp>

namespace Aisaka {
class Commands;

class Category {
   public:
	Category(std::string name);
	virtual ~Category();

	virtual void init(spdlog::logger&, Aisaka::Commands&) {}
	const std::string& get_name() const noexcept { return name; }

   protected:
	using Examples = const nlohmann::fifo_map<std::string, std::string>;

   private:
	std::string name;
};
}  // namespace Aisaka