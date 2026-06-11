cmake_minimum_required(VERSION 3.14)
project(UnitTemplateLibrary VERSION 1.0.0 LANGUAGES CXX)

option(ENABLE_TESTS "Build unit tests" OFF)
option(ENABLE_EXAMPLES "Build usage examples" OFF)

add_library(utl INTERFACE)
add_library(utl::utl ALIAS utl)
target_include_directories(utl INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
target_compile_features(utl INTERFACE cxx_std_17)

include(GNUInstallDirs)
install(TARGETS utl EXPORT utlTargets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT utlTargets
        FILE utlConfig.cmake
        NAMESPACE utl::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/utl)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(ENABLE_EXAMPLES)
    add_subdirectory(examples)
endif()
