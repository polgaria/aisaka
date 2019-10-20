#pragma once

#include <aisaka/Bot.hpp>

namespace Aisaka {
/**
 * @rst
 * .. note::
 *	  This class has been deprecated.
 * @endrst
 * 
 * @deprecated since 2.1
 * @see Aisaka::Bot
 */
using Client [[deprecated("Renamed to Aisaka::Bot")]] = Aisaka::Bot;
}  // namespace Aisaka
