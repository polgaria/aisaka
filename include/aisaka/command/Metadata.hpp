#pragma once

#include <fifo_map.hpp>

namespace Aisaka {
class Metadata {
   public:
	[[nodiscard]] const std::string& description() const noexcept {
		return this->_description;
	}
	Metadata& description(const std::string_view description) noexcept {
		this->_description = description;
		return *this;
	}

	[[nodiscard]] const nlohmann::fifo_map<std::string, std::string>& examples()
		const noexcept {
		return this->_examples;
	}
	/// Sets the command's examples.
	/**
	 * @param examples A nlohmann::fifo_map; the key is the user input, while
	 * the value is the result.
	 * @rst
	 *     .. code-block:: cpp
	 *
	 *        nlohmann::fifo_map<std::string, std::string>{
	 *            {"add test", "Adds `test` to the guild prefixes."}
	 *        }
	 * @endrst
	 * could possibly be used in a help command, resulting in
	 * @rst
	 *     .. code-block:: md
	 *
	 *		  `> t.prefix add test`
	 *		  Adds `test` to the guild prefixes.
	 * @endrst
	 */
	Metadata& examples(const nlohmann::fifo_map<std::string, std::string>&&
						   examples) noexcept {
		this->_examples = examples;
		return *this;
	}

   private:
	std::string _description;
	nlohmann::fifo_map<std::string, std::string> _examples;
};
}  // namespace Aisaka
