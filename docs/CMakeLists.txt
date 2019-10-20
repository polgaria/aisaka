find_package(Doxygen)
find_package(Sphinx)

set(DOC_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/index.rst"
	"${CMAKE_CURRENT_SOURCE_DIR}/api.rst")

if(Doxygen_FOUND AND Sphinx_FOUND)
  set(DOXYGEN_INPUT_DIR ${aisaka_SOURCE_DIR}/include/aisaka/)
  set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen)
  set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
  set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
  set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

  file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})
  add_custom_command(
    OUTPUT ${DOXYGEN_INDEX_FILE}
    DEPENDS ${HEADER_LIST}
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
    MAIN_DEPENDENCY ${DOXYFILE_OUT}
    ${DOXYFILE_IN}
    COMMENT "Generating docs")

  add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

  set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
  set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)
  set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

  # Only regenerate Sphinx when:
  # - Doxygen has rerun
  # - Our doc files have been updated
  # - The Sphinx config has been updated
  add_custom_command(
    OUTPUT ${SPHINX_INDEX_FILE}
    COMMAND
      ${SPHINX_EXECUTABLE} -b html

      # Tell Breathe where to find the Doxygen output
      -Dbreathe_projects.aisaka=${DOXYGEN_OUTPUT_DIR}/xml ${SPHINX_SOURCE}
      ${SPHINX_BUILD}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${DOC_FILES} ${DOXYGEN_INDEX_FILE}
    MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
    COMMENT "Generating documentation with Sphinx")

  # Nice named target so we can run the job easily
  add_custom_target(Sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})

  # Add an install target to install the docs
  include(GNUInstallDirs)
  install(DIRECTORY ${SPHINX_BUILD} DESTINATION ${CMAKE_INSTALL_DOCDIR})
else()
  message(WARNING "Could not find Sphinx and Doxygen; not generating docs")
endif()
