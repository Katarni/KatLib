cmake_minimum_required(VERSION 3.26)
project(KatLib VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)

add_library(KatLib INTERFACE)
target_include_directories(KatLib INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/KatLib.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/Label.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/Div.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/Button.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/ErrorMessage.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/TextInput.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/scroll-area/VerScrollArea.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/scroll-area/HorScrollArea.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/ErrorMessage.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/DialogWin.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/SelectedItem.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/scroll-area/ScrollArea.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/Image.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/ProgressBar.h")
set_target_properties(KatLib PROPERTIES PUBLIC_HEADER "include/Animation.h")


install(TARGETS KatLib
        EXPORT KatLibExport
        PUBLIC_HEADER DESTINATION include
        INCLUDES DESTINATION include)

include(CMakePackageConfigHelpers)

if (WIN32)
    set(SFML_INCLUDE_DIRS "path/to/sfml/include")
    set(SFML_DIR "path/to/sfml/lib/cmake/SFML")
    include_directories(${SFML_INCLUDE_DIRS})
else()
    include_directories(/usr/local/include)
endif (WIN32)

find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(KatLib INTERFACE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/data/KatLibConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/KatLibConfig.cmake"
        INSTALL_DESTINATION cmake)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/KatLibConfigVersion.cmake
        COMPATIBILITY AnyNewerVersion)

install(EXPORT KatLibExport
        DESTINATION cmake)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/KatLibConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KatLibConfigVersion.cmake"
        DESTINATION cmake)

install(FILES "${PROJECT_SOURCE_DIR}/data/config.sh"
        DESTINATION ${CMAKE_INSTALL_PREFIX})
