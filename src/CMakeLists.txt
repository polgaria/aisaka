set(HEADER_LIST
	"${aisaka_SOURCE_DIR}/include/aisaka/command/Command.hpp"
	"${aisaka_SOURCE_DIR}/include/aisaka/command/Commands.hpp"	
	"${aisaka_SOURCE_DIR}/include/aisaka/command/Parameter.hpp"
	"${aisaka_SOURCE_DIR}/include/aisaka/command/Metadata.hpp"
	"${aisaka_SOURCE_DIR}/include/aisaka/command/util/GetterSetterMacro.hpp"	
	"${aisaka_SOURCE_DIR}/include/aisaka/command/categories/Category.hpp"
	"${aisaka_SOURCE_DIR}/include/aisaka/Client.hpp"
	"${aisaka_SOURCE_DIR}/include/aisaka/util/String.hpp"
)

add_library(aisaka
	command/Command.cpp
	command/Commands.cpp
	command/Parameter.cpp
	command/Metadata.cpp
	command/categories/Category.cpp
	util/String.cpp
	Client.cpp
	${HEADER_LIST}
)

target_include_directories(aisaka PUBLIC
	$<BUILD_INTERFACE:${aisaka_SOURCE_DIR}/include>  
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${aisaka_SOURCE_DIR}/lib/fifo_map/src>  
	$<INSTALL_INTERFACE:lib/fifo_map/src>
	${LIBMONGOCXX_INCLUDE_DIRS}
	${Aegis_INCLUDE_DIRS}
)

target_link_libraries(aisaka PUBLIC
	${LIBMONGOCXX_LIBRARIES}
	${Aegis_LIBRARIES}
)

target_compile_definitions(aisaka PUBLIC
	${LIBMONGOCXX_DEFINITIONS}
)

target_compile_features(aisaka PRIVATE cxx_std_17 ${Aegis_CFLAGS_OTHER})
if(MSVC)
  target_compile_options(aisaka PRIVATE $<$<CONFIG:RELEASE>:/Ox> /W4)
else()
  target_compile_options(aisaka PRIVATE $<$<CONFIG:RELEASE>:-O3> -Wall -Wextra -pedantic)
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
  set_target_properties(aisaka PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

source_group(TREE "${aisaka_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
