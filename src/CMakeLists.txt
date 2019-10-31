configure_file("${aisaka_SOURCE_DIR}/include/aisaka/Version.hpp.in"
			   "${aisaka_SOURCE_DIR}/include/aisaka/Version.hpp")

set(HEADER_LIST
	"${aisaka_SOURCE_DIR}/include/aisaka/Bot.hpp"
	"${aisaka_SOURCE_DIR}/include/aisaka/Version.hpp"
    "${aisaka_SOURCE_DIR}/include/aisaka/command/Command.hpp"
    "${aisaka_SOURCE_DIR}/include/aisaka/command/Commands.hpp"
    "${aisaka_SOURCE_DIR}/include/aisaka/command/Parameter.hpp"
    "${aisaka_SOURCE_DIR}/include/aisaka/command/Metadata.hpp"
	"${aisaka_SOURCE_DIR}/include/aisaka/command/categories/Category.hpp"
    "${aisaka_SOURCE_DIR}/include/aisaka/command/util/GetterSetterMacro.hpp"
    "${aisaka_SOURCE_DIR}/include/aisaka/util/String.hpp"
	CACHE INTERNAL "Header Files")

add_library(aisaka Bot.cpp util/String.cpp ${HEADER_LIST})
set_target_properties(aisaka PROPERTIES POSITION_INDEPENDENT_CODE 1)
set_target_properties(aisaka PROPERTIES SOVERSION ${aisaka_SOVERSION})
add_library(aisaka::aisaka ALIAS aisaka)

target_include_directories(
  aisaka
  PUBLIC $<BUILD_INTERFACE:${aisaka_SOURCE_DIR}/include>
		 $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${Aegis_INCLUDE_DIRS}>
		 $<BUILD_INTERFACE:${robin_hood_INCLUDE_DIRS}>
         ${LIBMONGOCXX_INCLUDE_DIRS})

target_link_libraries(aisaka PUBLIC fifo_map
									${Aegis_LIBRARIES}
									${LIBMONGOCXX_LIBRARIES})

target_compile_definitions(aisaka PUBLIC ${LIBMONGOCXX_DEFINITIONS})

target_compile_features(aisaka PRIVATE cxx_std_17 ${Aegis_CFLAGS_OTHER})
if(MSVC)
  target_compile_options(aisaka PRIVATE $<$<CONFIG:RELEASE>:/Ox> /W4)
else()
  target_compile_options(aisaka PRIVATE $<$<CONFIG:RELEASE>:-O3> -Wall -Wextra
                                        -pedantic)
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(CMAKE_BUILD_TYPE STREQUAL Release AND result)
  message(STATUS "IPO/LTO enabled")
  set_target_properties(aisaka PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

source_group(TREE "${aisaka_SOURCE_DIR}/include" PREFIX "Header Files" FILES
             ${HEADER_LIST})

export(
  TARGETS ${aisaka_TARGET_NAME}
  NAMESPACE ${PROJECT_NAME}::
  FILE ${aisaka_CMAKE_PROJECT_TARGETS_FILE})
install(
  TARGETS ${aisaka_TARGET_NAME}
  EXPORT ${aisaka_TARGETS_EXPORT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${aisaka_INCLUDE_INSTALL_DIR})
