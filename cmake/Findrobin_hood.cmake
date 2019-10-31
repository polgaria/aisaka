find_path(robin_hood_INCLUDE_DIR NAMES "robin_hood.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/lib/robin_hood/src/include/")
if(robin_hood_INCLUDE_DIR STREQUAL "robin_hood_INCLUDE_DIR-NOTFOUND")
	message(FATAL_ERROR "Could not find robin_hood.")
	set(robin_hood_FOUND FALSE)
endif()

set(robin_hood_FOUND TRUE)

if(robin_hood_FOUND)
	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(robin_hood
		REQUIRED_VARS robin_hood_INCLUDE_DIR
		FOUND_VAR robin_hood_FOUND
		FAIL_MESSAGE "Could not find robin_hood.")

	if(NOT TARGET robin_hood)
		add_library(robin_hood INTERFACE IMPORTED)
		set_target_properties(robin_hood PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES ${robin_hood_INCLUDE_DIR})
	endif()

    mark_as_advanced(robin_hood_INCLUDE_DIR)
endif()
