cmake_minimum_required(VERSION 3.1.3)

set(PROJECT_NAME VivePlugin)
set(PROJECT_DESCRIPTION "")
set(PROJECT_URL "")
set(PROJECT_VERSION 0.0.1)
set(PROJECT_USE_CMAKE_EXPORT TRUE)
set(CMAKE_CXX_STANDARD 11)

include(cmake/base.cmake)
include(FindPkgConfig)

option(AUTOLOAD_VivePlugin_PLUGIN "Automatically load VivePlugin plugin" OFF)

project(${PROJECT_NAME} LANGUAGES CXX VERSION ${PROJECT_VERSION})

# Find mc_rtc if we are not building inside mc_rtc itself
if(NOT TARGET mc_rtc::mc_control)
  find_package(mc_rtc REQUIRED)
endif()

# This creates a target PkgConfig::openvr if openvr is found
pkg_check_modules(openvr REQUIRED IMPORTED_TARGET openvr)

# Configure and install the plugin configuration
configure_file(etc/VivePlugin.in.yaml "${CMAKE_CURRENT_BINARY_DIR}/etc/VivePlugin.yaml")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/etc/VivePlugin.yaml" DESTINATION "${MC_PLUGINS_RUNTIME_INSTALL_PREFIX}/etc")


# Create a library to export plugin data
# This is intended so that other projects can link with mc_vive_plugin::data
add_library(VivePluginData INTERFACE)
add_library(mc_vive_plugin::data ALIAS VivePluginData)
target_include_directories(VivePluginData
  INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)

install(
  TARGETS VivePluginData
  EXPORT "${TARGETS_EXPORT_NAME}"
)
install(DIRECTORY include/mc_vive_plugin DESTINATION include)


set(plugin_SRC
  src/VivePlugin.cpp
  )

set(plugin_HDR
  src/VivePlugin.h
)

# The add_plugin macro is provided by mc_rtc
add_plugin(VivePlugin "${plugin_SRC}" "${plugin_HDR}")
target_link_libraries(VivePlugin PUBLIC VivePluginData)
target_link_libraries(VivePlugin PUBLIC PkgConfig::openvr)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
