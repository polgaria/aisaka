#pragma once

#include <aisaka/Bot.hpp>

namespace Aisaka {
/**
 * @verbatim embed:rst:leading-asterisk
 * .. note::
 *	  This class has been deprecated.
 * @endverbatim
 * 
 * @deprecated since 2.1
 * @see Aisaka::Bot
 */
using Client [[deprecated("Renamed to Aisaka::Bot")]] = Aisaka::Bot;
}  // namespace Aisaka
