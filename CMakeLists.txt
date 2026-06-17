cmake_minimum_required(VERSION 3.14)
project(UnitTemplateLibrary VERSION 3.1.0 LANGUAGES CXX)

option(ENABLE_TESTS "Build unit tests" OFF)
option(ENABLE_EXAMPLES "Build usage examples" OFF)
option(ENABLE_WERROR "Treat warnings as errors in tests and examples" OFF)

function(utl_apply_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
        if(ENABLE_WERROR)
            target_compile_options(${target} PRIVATE /WX)
        endif()
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra)
        if(ENABLE_WERROR)
            target_compile_options(${target} PRIVATE -Werror)
        endif()
    endif()
endfunction()

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
