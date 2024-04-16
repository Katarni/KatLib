cmake_minimum_required(VERSION 3.26)
project(katLib VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_library(katLib INTERFACE)
target_include_directories(katLib INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/Label.h")
set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/Div.h")
set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/Button.h")
set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/ErrorMessage.h")
set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/TextInput.h")
set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/scroll-area/HorScrollArea.h")
set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/scroll-area/ScrollAreaElm.h")
set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/ErrorMessage.h")
set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/DialogWin.h")
set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/scroll-area/CheckBox.h")
set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/scroll-area/ScrollTextInputs.h")
set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/SelectedItem.h")
set_target_properties(katLib PROPERTIES PUBLIC_HEADER "include/KatLib.h")


install(TARGETS katLib
        EXPORT katLibExport
        PUBLIC_HEADER DESTINATION include
        INCLUDES DESTINATION include)

include(CMakePackageConfigHelpers)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(katLib INTERFACE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/data/katLibConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/katLibConfig.cmake"
        INSTALL_DESTINATION cmake)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/katLibConfigVersion.cmake
        COMPATIBILITY AnyNewerVersion)

install(EXPORT katLibExport
        DESTINATION cmake)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/katLibConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/katLibConfigVersion.cmake"
        DESTINATION cmake)

install(FILES "${PROJECT_SOURCE_DIR}/data/config.sh"
        DESTINATION ${CMAKE_INSTALL_PREFIX})
