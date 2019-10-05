cmake_minimum_required(VERSION 3.12...3.15)

project(aisaka    VERSION 1.0
                  DESCRIPTION "aegis.cpp command system"
                  LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)    
    set(CMAKE_CXX_EXTENSIONS OFF)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
find_package(Aegis REQUIRED)

add_subdirectory(src)


set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/aisaka)

include(GNUInstallDirs)
install(
    TARGETS
      aisaka
    EXPORT
      aisakaTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT aisakaTargets
    FILE aisakaTargets.cmake
    NAMESPACE aisaka::
    DESTINATION ${INSTALL_CONFIGDIR}
)

install(DIRECTORY include/aisaka
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/aisaka
    FILES_MATCHING PATTERN "*.hpp"
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/aisakaConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/aisakaConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/aisakaConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/aisakaConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/aisakaConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

add_library(aisaka::aisaka ALIAS aisaka)