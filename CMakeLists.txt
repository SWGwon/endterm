CMAKE_MINIMUM_REQUIRED(VERSION 3.1 FATAL_ERROR)
PROJECT(endterm)

SET(CMAKE_CXX_STANDARD 17)

SET(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET(SRC_FILES 
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Function.cpp
    )

LIST(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
FIND_PACKAGE(ROOT REQUIRED COMPONENTS RIO Net)
INCLUDE(${ROOT_USE_FILE})

ADD_LIBRARY(_endterm SHARED ${SRC_FILES})
TARGET_LINK_LIBRARIES(_endterm ${ROOT_LIBRARIES})

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${SRC_FILES})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} _endterm)
