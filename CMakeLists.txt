cmake_minimum_required(VERSION 3.15)

set(namespace "librw")

project("librw-wx"
    VERSION 1.0.0
    DESCRIPTION "Classes interfacing wxWidgets with librw"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/extdeps/usr/local")

set(librwwx_MAINPROJECT ON)
if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(librwwx_MAINPROJECT OFF)
    message(STATUS "Project ${PROJECT_NAME} has a top-level one called [${CMAKE_PROJECT_NAME}].")
else()
    message(STATUS "Project ${PROJECT_NAME} is a top-level one.")

    if (NOT EXISTS "${CMAKE_PREFIX_PATH}/")
        message(FATAL_ERROR "Failed to find external dependencies.\n"
            "Prefix path ${CMAKE_PREFIX_PATH} not found.\n"
            "Please build external dependencies first." )
    endif()
endif()

option(LIBRWWX_INSTALL "Install librw-wx files" ${librwwx_MAINPROJECT})

if (NOT TARGET OpenGL::OpenGL)
    find_package(OpenGL REQUIRED)
endif()

if (NOT TARGET librw::librw)
    find_package(librw REQUIRED)
endif()

if (NOT TARGET wxWidgets)
    find_package(wxWidgets 3.2.1 CONFIG REQUIRED COMPONENTS html adv gl aui core base)
endif()

add_library(${PROJECT_NAME} STATIC)

# without it public headers won't get installed
set(public_headers
    include/librw-wx.h
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${public_headers}
        src/wxRwCanvas.cpp
        src/wxRwGLContext.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DwxDEBUG_LEVEL=0)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        librw::librw
        ${wxWidgets_LIBRARIES}
)

# not for MSVC
if(CMAKE_COMPILER_IS_GNUCXX)
    # compile options for this target only
    # treat warnings as errors
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
endif()

# where to find our CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(LIBRWWX_INSTALL)
    include(installing)
endif()
