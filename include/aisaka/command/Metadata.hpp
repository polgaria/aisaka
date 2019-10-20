#pragma once

#include <fifo_map.hpp>

namespace Aisaka {
class Metadata {
   public:
	[[nodiscard]] const std::string& description() const noexcept;
	Metadata& description(const std::string& description) noexcept;

	[[nodiscard]] const nlohmann::fifo_map<std::string, std::string>& examples()
		const noexcept;
	/// Sets the command's examples.
	/**
	 * @param examples A nlohmann::fifo_map; the key is the user input, while
	 * the value is the result.
	 * @verbatim embed:rst:leading-asterisk
	 *     .. code-block:: cpp
	 * 
	 *        nlohmann::fifo_map<std::string, std::string>{
	 *            {"add test", "Adds `test` to the guild prefixes."}
	 *        }
	 * @endverbatim
	 * could possibly be used in a help command, resulting in
	 * @verbatim embed:rst:leading-asterisk
	 *     .. code-block:: md
	 * 
	 *		  `> t.prefix add test`
	 *		  Adds `test` to the guild prefixes.
	 * @endverbatim
	 */
	Metadata& examples(
		const nlohmann::fifo_map<std::string, std::string>&& examples) noexcept;

   private:
	std::string _description;
	nlohmann::fifo_map<std::string, std::string> _examples;
};
}  // namespace Aisaka
