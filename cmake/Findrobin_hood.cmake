find_path(robin_hood_INCLUDE_DIR NAMES "robin_hood.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/lib/robin_hood/src/include/")
if(robin_hood_INCLUDE_DIR STREQUAL "robin_hood_INCLUDE_DIR-NOTFOUND")
	message(FATAL_ERROR "Could not find robin_hood.")
endif()

set(robin_hood_INCLUDE_DIRS ${robin_hood_INCLUDE_DIR})
