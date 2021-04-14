#message(STATUS "updateVersion: CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
#message(STATUS "updateVersion: CMAKE_CURRENT_LIST_FILE:  ${CMAKE_CURRENT_LIST_FILE}")
#message(STATUS "updateVersion: CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
#message(STATUS "updateVersion: CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
#message(STATUS "updateVersion: GIT_EXECUTABLE: ${GIT_EXECUTABLE}")

include(gymplDoFindGit)
if (NOT Git_FOUND)
  message(FATAL_ERROR "Cannot update version.hpp without git and Git_FOUND is false")
  return()
endif()


# Grab the version numbers:
include(${CMAKE_CURRENT_SOURCE_DIR}/Version.cmake)
set(GYMPL_VERSION_VERSION ${GYMPL_VERSION_MAJOR}.${GYMPL_VERSION_MINOR}.${GYMPL_VERSION_PATCHLEVEL})

# Try to build a new version.hpp
configure_file(version.hpp.in include/gympl/version.hpp @ONLY)
file(STRINGS ${CMAKE_CURRENT_BINARY_DIR}/include/gympl/version.hpp GYMPL_OLD_VERSION_HPP)
file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/include/gympl/version.hpp GYMPL_NEW_VERSION_HPP)

#message(STATUS "updateVersion: GYMPL_OLD_VERSION_HPP: ${GYMPL_OLD_VERSION_HPP}")
#message(STATUS "updateVersion: GYMPL_NEW_VERSION_HPP: ${GYMPL_NEW_VERSION_HPP}")

# If the new version.hpp is materially different from the one in the source
# directory, update it, commit, and tag.
if(NOT GYMPL_NEW_VERSION_HPP STREQUAL GYMPL_OLD_VERSION_HPP)
  # Check that docs/release_notes.md and Version.cmake are the only changed file:
  execute_process(
    COMMAND ${GIT_EXECUTABLE} -C "${CMAKE_CURRENT_SOURCE_DIR}" status --porcelain -uno
    OUTPUT_VARIABLE GYMPL_GIT_STATUS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if ("${GYMPL_GIT_STATUS}" STREQUAL "")
    # or that there's non change at all because there's no commit yet
  else()
    string(REPLACE "\n" ";"  GYMPL_GIT_STATUS ${GYMPL_GIT_STATUS})
    if (NOT "x${GYMPL_GIT_STATUS}" STREQUAL "x M Version.cmake; M docs/release_notes.md")
      message(FATAL_ERROR "Cannot update version.hpp: the source directory has a dirty status")
	  return()
    endif()
  endif()
  
  file(
    COPY ${CMAKE_CURRENT_BINARY_DIR}/include/gympl/version.hpp
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/gympl
  )
  #execute_process(
  #  COMMAND ${GIT_EXECUTABLE} -C "${CMAKE_CURRENT_SOURCE_DIR}" add -u
  #)
  #execute_process(
  #  COMMAND ${GIT_EXECUTABLE} -C "${CMAKE_CURRENT_SOURCE_DIR}" commit -m "${GYMPL_VERSION_VERSION}"
  #)
  #execute_process(
  #  COMMAND ${GIT_EXECUTABLE} -C "${CMAKE_CURRENT_SOURCE_DIR}" tag -f -a "${GYMPL_VERSION_VERSION}" -m "${GYMPL_VERSION_VERSION}"
  #)
  find_program(CONAN_EXECUTABLE NAMES conan conan.exe)
  if (NOT "x${CONAN_EXECUTABLE}" STREQUAL "xCONAN_EXECUTABLE-NOTFOUND")
    message(STATUS "Exporting conanfile for new version")
    #execute_process(
    #  COMMAND ${CONAN_EXECUTABLE} create . gympl/${GYMPL_VERSION_VERSION}@gyzkard/stable
    #  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    #)
  endif()
  message(STATUS "Version updated to ${GYMPL_VERSION_VERSION}. Don't forget to:")
  message(STATUS "  git push origin <feature-branch>")
  message(STATUS "and (after that is merged to master) then:")
  message(STATUS "  conan remote add gympl https://api.bintray.com/conan/gympl/gympl")
  message(STATUS "  conan create ${CMAKE_CURRENT_SOURCE_DIR} gympl/${GYMPL_VERSION_VERSION}@gyzkard/stable")
  message(STATUS "  conan upload --all gympl/${GYMPL_VERSION_VERSION}@gyzkard/stable -r=gympl")
endif()
