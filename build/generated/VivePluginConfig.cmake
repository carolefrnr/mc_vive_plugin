
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was Config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(skip_this_file TRUE)
if(NOT VivePlugin_FOUND)
  set(skip_this_file FALSE)
endif()
if(skip_this_file)
  foreach(component ${VivePlugin_FIND_COMPONENTS})
    if(NOT "VivePlugin_${component}_FOUND")
      set(skip_this_file FALSE)
    endif()
  endforeach()
endif()
if(skip_this_file)
  return()
endif()

set("VivePlugin_INCLUDE_DIRS" "/usr/local/include")
set("VIVEPLUGIN_INCLUDE_DIRS" "/usr/local/include")
set("VivePlugin_DOXYGENDOCDIR" "${PACKAGE_PREFIX_DIR}/share/doc/VivePlugin/doxygen-html")
set("VIVEPLUGIN_DOXYGENDOCDIR" "${PACKAGE_PREFIX_DIR}/share/doc/VivePlugin/doxygen-html")
set("VivePlugin_DEPENDENCIES" "")
set("VivePlugin_PKG_CONFIG_DEPENDENCIES" "")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} )

# Find absolute library paths for all _PKG_CONFIG_LIBS as CMake expects full paths, while pkg-config does not.
set(_PACKAGE_CONFIG_LIBRARIES "")
set("_VivePlugin_PKG_CONFIG_LIBDIR" "/home/carole/mc_rtc_install/lib")
set("_VivePlugin_PKG_CONFIG_LIBS_LIST" "")
if(_VivePlugin_PKG_CONFIG_LIBS_LIST)
  string(FIND ${_VivePlugin_PKG_CONFIG_LIBS_LIST} ", " _is_comma_space)
  while(_is_comma_space GREATER -1)
    string(REPLACE ", " "," _VivePlugin_PKG_CONFIG_LIBS_LIST "${_VivePlugin_PKG_CONFIG_LIBS_LIST}")
    string(FIND ${_VivePlugin_PKG_CONFIG_LIBS_LIST} ", " _is_comma_space)
  endwhile()
  string(REPLACE " " ";" _VivePlugin_PKG_CONFIG_LIBS_LIST "${_VivePlugin_PKG_CONFIG_LIBS_LIST}")
  set(LIBDIR_HINTS ${_VivePlugin_PKG_CONFIG_LIBDIR})
  foreach(component ${_VivePlugin_PKG_CONFIG_LIBS_LIST})
    string(STRIP ${component} component)
    # If the component is a link directory ("-L/full/path"), append to LIBDIR_HINTS.
    string(FIND ${component} "-L" _is_library_dir)
    if(${_is_library_dir} EQUAL 0)
      string(REGEX REPLACE "^-L" "" lib_path ${component})
      list(APPEND LIBDIR_HINTS "${lib_path}")
      continue()
    endif()
    # If the component is a library name
    string(FIND ${component} "-l" _is_library_name)
    if(${_is_library_name} EQUAL 0)
      string(REGEX REPLACE "^-l" "" lib ${component})
      find_library(abs_lib_${lib} ${lib} HINTS ${LIBDIR_HINTS})
      if(NOT abs_lib_${lib})
        IF(_LIBDIR_HINTS)
          message(STATUS "${lib} searched on ${_LIBDIR_HINTS} not FOUND.")
        ELSE()
          message(STATUS "${lib} not FOUND.")
        ENDIF()
      else()
        IF(_LIBDIR_HINTS)
          message(STATUS "${lib} searched on ${_LIBDIR_HINTS} FOUND. ${lib} at ${abs_lib_${lib}}")
        ELSE()
          message(STATUS "${lib} FOUND. ${lib} at ${abs_lib_${lib}}")
        ENDIF()
        list(APPEND _PACKAGE_CONFIG_LIBRARIES "${abs_lib_${lib}}")
      endif()
      unset(abs_lib_${lib} CACHE)
      continue()
    endif()
    # If the component contains a collection of additional arguments
    string(FIND ${component} "," _is_collection)
    if(${_is_collection} GREATER -1)
      string(REPLACE "," ";" component_list "${component}")
      list(GET component_list -1 lib_info)
      set(options ${component})
      list(REMOVE_AT options -1)
      string(FIND ${lib_info} "-l" _is_library_name)
      if(${_is_library_name} GREATER -1)
        string(REGEX REPLACE "^-l" "" lib ${lib_info})
        find_library(abs_lib_${lib} ${lib} HINTS ${LIBDIR_HINTS})
        if(NOT abs_lib_${lib})
          IF(_LIBDIR_HINTS)
            message(STATUS "${lib} searched on ${_LIBDIR_HINTS} not FOUND.")
          ELSE()
            message(STATUS "${lib} not FOUND.")
          ENDIF()
        else()
          IF(_LIBDIR_HINTS)
            message(STATUS "${lib} searched on ${_LIBDIR_HINTS} FOUND. ${lib} at ${abs_lib_${lib}}")
          ELSE()
            message(STATUS "${lib} FOUND. ${lib} at ${abs_lib_${lib}}")
          ENDIF()
          list(APPEND _PACKAGE_CONFIG_LIBRARIES "${abs_lib_${lib}}")
        endif()
        unset(abs_lib_${lib} CACHE)
        continue()
      else() # This is an absolute lib
        list(APPEND _PACKAGE_CONFIG_LIBRARIES "${component}")
      endif()
      continue()
    endif()
    # Else, this is just an absolute lib
    if(EXISTS "${component}")
      list(APPEND _PACKAGE_CONFIG_LIBRARIES "${component}")
    endif()
  endforeach()
endif(_VivePlugin_PKG_CONFIG_LIBS_LIST)

set("VivePlugin_LIBRARIES" ${_PACKAGE_CONFIG_LIBRARIES})
set("VIVEPLUGIN_LIBRARIES" ${_PACKAGE_CONFIG_LIBRARIES})

include(CMakeFindDependencyMacro)
if(${CMAKE_VERSION} VERSION_LESS "3.15.0")
  
else()
  
endif()

IF(COMMAND ADD_REQUIRED_DEPENDENCY)
  FOREACH(pkgcfg_dep ${VivePlugin_PKG_CONFIG_DEPENDENCIES})
    # Avoid duplicated lookup.
    LIST (FIND $_PKG_CONFIG_REQUIRES "${pkgcfg_dep}" _index)
    IF(${_index} EQUAL -1)
      ADD_REQUIRED_DEPENDENCY(${pkgcfg_dep})
    ENDIF()
  ENDFOREACH()
ENDIF(COMMAND ADD_REQUIRED_DEPENDENCY)

include("${CMAKE_CURRENT_LIST_DIR}/VivePluginTargets.cmake")

foreach(component ${VivePlugin_FIND_COMPONENTS})
  set(comp_file "${CMAKE_CURRENT_LIST_DIR}/${component}Config.cmake")
  if(EXISTS ${comp_file})
    include(${comp_file})
  else()
    set(VivePlugin_${component}_FOUND FALSE)
  endif()
  if(VivePlugin_${component}_FOUND)
    message(STATUS "VivePlugin: ${component} found.")
  else()
    message(STATUS "VivePlugin: ${component} not found.")
  endif()
endforeach()
check_required_components("VivePlugin")


# C++ standard compatibility check/enforcement
set(_MINIMAL_CXX_STANDARD 11)

#
# Copyright (C) 2020 LAAS-CNRS
#
# Author: Guilhem Saurel
#

#.rst:
# .. ifmode:: internal
#
#   .. variable:: ENFORCE_MINIMAL_CXX_STANDARD
#
#      When this is ON, every call to :cmake:command:`CHECK_MINIMAL_CXX_STANDARD` updates the :cmake:variable:`CMAKE_CXX_STANDARD`.
option(ENFORCE_MINIMAL_CXX_STANDARD "Set CMAKE_CXX_STANDARD if a dependency require it" OFF)

#.rst:
# .. ifmode:: user
#
#   .. command:: CHECK_MINIMAL_CXX_STANDARD(STANDARD [ENFORCE])
#
#      Ensure that a minimal C++ standard will be used.
#
#      This will check the default standard of the current compiler,
#      and set :cmake:variable:`CMAKE_CXX_STANDARD` if necessary, and `ENFORCE` is provided,
#      or :cmake:variable:`ENFORCE_MINIMAL_CXX_STANDARD` is `ON`.
#      Multiple calls to this macro will keep the highest standard.
#
#      Supported values are 98, 11, 14, 17, and 20.
#
macro(CHECK_MINIMAL_CXX_STANDARD STANDARD)
  set(options ENFORCE)
  set(oneValueArgs)
  set(multiValueArgs)
  cmake_parse_arguments(MINIMAL_CXX_STANDARD "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  # Get compiler default cxx standard, by printing "__cplusplus" (only once)
  if(NOT DEFINED _COMPILER_DEFAULT_CXX_STANDARD AND (NOT CMAKE_CROSSCOMPILING OR (CMAKE_CROSSCOMPILING AND CMAKE_CROSSCOMPILING_EMULATOR)))
    if(MSVC)
      # See https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
      string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus")
    endif()
    write_file(${CMAKE_CURRENT_BINARY_DIR}/cmake/tmp-cxx-standard.cpp "#include <iostream>\nint main(){std::cout << __cplusplus << std::endl;return 0;}")
    try_run(_cxx_standard_run_status _cxx_standard_build_status
      ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/cmake/tmp-cxx-standard.cpp
      RUN_OUTPUT_VARIABLE _COMPILER_DEFAULT_CXX_STANDARD)
    if(_cxx_standard_run_status EQUAL FAILED_TO_RUN OR _cxx_standard_build_status EQUAL FALSE)
      message(WARNING "Impossible to build or run the script to retrive the _COMPILER_DEFAULT_CXX_STANDARD quantity from current compiler. Setting _COMPILER_DEFAULT_CXX_STANDARD to 199711")
      set(_COMPILER_DEFAULT_CXX_STANDARD "199711")
    endif()
    string(STRIP "${_COMPILER_DEFAULT_CXX_STANDARD}" _COMPILER_DEFAULT_CXX_STANDARD)
    message(STATUS "Default C++ standard: ${_COMPILER_DEFAULT_CXX_STANDARD}")
  endif()

  # Check if we need to upgrade the current minimum
  if(NOT DEFINED _MINIMAL_CXX_STANDARD
      OR (NOT ${STANDARD} EQUAL "98"
        AND (_MINIMAL_CXX_STANDARD EQUAL "98" OR _MINIMAL_CXX_STANDARD LESS ${STANDARD})))
    set(_MINIMAL_CXX_STANDARD "${STANDARD}" CACHE INTERNAL "")
    message(STATUS "Minimal C++ standard upgraded to ${_MINIMAL_CXX_STANDARD}")
  endif()

  # Check if a non-trivial minimum has been requested
  if(DEFINED _MINIMAL_CXX_STANDARD AND NOT _MINIMAL_CXX_STANDARD EQUAL 98)

    if (DEFINED CMAKE_CXX_STANDARD)
      set(_CURRENT_STANDARD ${CMAKE_CXX_STANDARD})
    elseif(DEFINED _COMPILER_DEFAULT_CXX_STANDARD)
      # ref https://en.cppreference.com/w/cpp/preprocessor/replace#Predefined_macros for constants
      if(_COMPILER_DEFAULT_CXX_STANDARD EQUAL 199711)
        set(_CURRENT_STANDARD 98)
      elseif(_COMPILER_DEFAULT_CXX_STANDARD EQUAL 201103)
        set(_CURRENT_STANDARD 11)
      elseif(_COMPILER_DEFAULT_CXX_STANDARD EQUAL 201402)
        set(_CURRENT_STANDARD 14)
      elseif(_COMPILER_DEFAULT_CXX_STANDARD EQUAL 201703)
        set(_CURRENT_STANDARD 17)
      # C++20: g++-9 defines c++2a with literal 201709, g++-11 & clang-10 define c++2a with literal 202002
      elseif(_COMPILER_DEFAULT_CXX_STANDARD EQUAL 201709 OR _COMPILER_DEFAULT_CXX_STANDARD EQUAL 202002)
        set(_CURRENT_STANDARD 20)
      else()
        message(FATAL_ERROR "Unknown current C++ standard ${_COMPILER_DEFAULT_CXX_STANDARD} while trying to check for >= ${_MINIMAL_CXX_STANDARD}")
      endif()
    else()
      set(_CURRENT_STANDARD 98)
    endif()

    # Check that the requested minimum is higher than the currently selected
    if(_CURRENT_STANDARD EQUAL 98 OR _CURRENT_STANDARD LESS _MINIMAL_CXX_STANDARD)
      message(STATUS "Incompatible C++ standard detected: upgrade required from ${_CURRENT_STANDARD} to >= ${_MINIMAL_CXX_STANDARD}")
      # Check that the requested minimum is higher than any pre-existing CMAKE_CXX_STANDARD
      if(NOT CMAKE_CXX_STANDARD OR CMAKE_CXX_STANDARD EQUAL 98 OR CMAKE_CXX_STANDARD LESS _MINIMAL_CXX_STANDARD)
        # Throw error if a specific version is required and the currently desired one is incompatible
        if(CMAKE_CXX_STANDARD_REQUIRED)
          message(FATAL_ERROR "CMAKE_CXX_STANDARD_REQUIRED set - cannot upgrade incompatible standard")
        endif()
        # Enforcing a standard version is required - check if we can upgrade automatically
        if(ENFORCE_MINIMAL_CXX_STANDARD OR MINIMAL_CXX_STANDARD_ENFORCE)
          set(CMAKE_CXX_STANDARD ${_MINIMAL_CXX_STANDARD})
          message(AUTHOR_WARNING "CMAKE_CXX_STANDARD automatically upgraded from ${_CURRENT_STANDARD} to ${CMAKE_CXX_STANDARD}")
        else()
          message(FATAL_ERROR "CMAKE_CXX_STANDARD upgrade from ${_CURRENT_STANDARD} to >= ${_MINIMAL_CXX_STANDARD} required")
        endif()
      endif()
    else()  # requested minimum is higher than the currently selected
      message(STATUS "C++ standard sufficient: Minimal required ${_MINIMAL_CXX_STANDARD}, currently defined: ${_CURRENT_STANDARD}")
    endif()  # requested minimum is higher than the currently selected
  endif()
endmacro()

CHECK_MINIMAL_CXX_STANDARD(11 ENFORCE)
