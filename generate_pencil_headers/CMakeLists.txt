cmake_minimum_required (VERSION 2.8.7)

project(PENCIL_generate_headers)

######################### Compiler switches ##########################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_COMPILE_FLAGS} -std=c++0x")

########################## Dependencies ##########################
set(Boost_USE_STATIC_LIBS    OFF)
set(Boost_USE_MULTITHREADED  ON )
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED regex)

######################### Add project files ##########################

set( COMMON_INCLUDE_DIRS ${Boost_INCLUDE_DIRS} )
set( COMMON_LINK_LIBRARIES ${Boost_LIBRARIES} )

add_executable( generate_headers
                main.cpp
                function.cpp
                pencil_stdlib.cpp
                types.cpp
              )

if(${CMAKE_VERSION} VERSION_LESS 2.8.11)
    include_directories( ${Boost_INCLUDE_DIRS} )
else()
    target_include_directories( generate_headers PRIVATE ${Boost_INCLUDE_DIRS} )
endif()

target_link_libraries( generate_headers ${Boost_LIBRARIES} )
