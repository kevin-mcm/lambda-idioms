cmake_minimum_required(VERSION 3.0.0)
project(lambda-idioms VERSION 0.1.0)

set(BIN lambda-idioms)

add_definitions(-DNDEBUG)
add_definitions(-D_REENTRANT)
add_definitions(-DC7_Q)
add_definitions(-DLINUX)
add_definitions(-DXDR_FEATURE)
add_definitions(-DOCCI_ON)
add_definitions(-D_NO_ALERT_)
add_definitions(-DGUARD_FEATURE)
add_definitions(-DSESSION_SEND_WRAPPER)
add_definitions(-D_RH6)
add_definitions(-DCOMMON_ACTIONS_ONLY)
add_definitions(-DSMS_DIGITS_NORMALIZER_FEATURE)
add_definitions(-DDIA_EXTERNAL_SEND)
add_definitions(-DDB_HSM_LOAD)
add_definitions(-DBOOST_MPL_CFG_NO_PREPROCESSED_HEADERS)
add_definitions(-DBOOST_MPL_LIMIT_VECTOR_SIZE=30)
add_definitions(-DBOOST_MPL_LIMIT_LIST_SIZE=30)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fconcepts -Os -g -m64")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(REQUIRED_LIBRARIES
    boost_system
    boost_chrono
    boost_thread
    boost_filesystem
    boost_date_time
    boost_program_options
    boost_regex
    boost_iostreams
    pthread)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

file(GLOB_RECURSE INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.*)
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include(CTest)
enable_testing()

add_executable(${BIN} ${INC_FILES} ${SRC_FILES})

target_link_libraries(${BIN} ${REQUIRED_LIBRARIES}
        "-Wl,--whole-archive" "-Wl,--no-whole-archive")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
