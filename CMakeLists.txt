cmake_minimum_required(VERSION 3.12...3.15)

project(aisaka VERSION 1.1
               DESCRIPTION "aegis.cpp command system"
               LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)    
    set(CMAKE_CXX_EXTENSIONS OFF)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)	
	set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")	
endif()

include(GNUInstallDirs)
set(aisaka_TARGET_NAME                ${PROJECT_NAME})
set(aisaka_CONFIG_INSTALL_DIR         "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE INTERNAL "")
set(aisaka_INCLUDE_INSTALL_DIR        "${CMAKE_INSTALL_INCLUDEDIR}")
set(aisaka_TARGETS_EXPORT_NAME        "${PROJECT_NAME}Targets")
set(aisaka_CMAKE_CONFIG_TEMPLATE      "cmake/${PROJECT_NAME}Config.cmake.in")
set(aisaka_CMAKE_CONFIG_DIR           "${CMAKE_CURRENT_BINARY_DIR}")
set(aisaka_CMAKE_VERSION_CONFIG_FILE  "${aisaka_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(aisaka_CMAKE_PROJECT_CONFIG_FILE  "${aisaka_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake")
set(aisaka_CMAKE_PROJECT_TARGETS_FILE "${aisaka_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake")
set(aisaka_INCLUDE_BUILD_DIR		  "${PROJECT_SOURCE_DIR}/include/")

find_package(fifo_map	 REQUIRED)
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx  REQUIRED)
find_package(Aegis		 REQUIRED)

add_subdirectory(src)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${aisaka_CMAKE_VERSION_CONFIG_FILE} COMPATIBILITY SameMajorVersion
)
configure_file(
    ${aisaka_CMAKE_CONFIG_TEMPLATE}
    ${aisaka_CMAKE_PROJECT_CONFIG_FILE}
    @ONLY
)

install(
	DIRECTORY ${aisaka_INCLUDE_BUILD_DIR}
	DESTINATION ${aisaka_INCLUDE_INSTALL_DIR}
)
install(
	FILES
		${aisaka_CMAKE_PROJECT_CONFIG_FILE}
		${aisaka_CMAKE_VERSION_CONFIG_FILE}
		${CMAKE_CURRENT_LIST_DIR}/cmake/Findfifo_map.cmake
	DESTINATION ${aisaka_CONFIG_INSTALL_DIR}
)
export(
	TARGETS ${aisaka_TARGET_NAME}
	NAMESPACE ${PROJECT_NAME}::
	FILE ${aisaka_CMAKE_PROJECT_TARGETS_FILE}
)
install(
	TARGETS ${aisaka_TARGET_NAME}
	EXPORT ${aisaka_TARGETS_EXPORT_NAME}
	INCLUDES DESTINATION ${aisaka_INCLUDE_INSTALL_DIR}
)
install(
	EXPORT ${aisaka_TARGETS_EXPORT_NAME}
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION ${aisaka_CONFIG_INSTALL_DIR}
)

export(PACKAGE ${PROJECT_NAME})