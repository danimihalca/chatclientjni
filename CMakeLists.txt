project(chatClientJNI)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-DENABLE_LOG_DEBUG)
endif()

INCLUDE_DIRECTORIES(inc)
INCLUDE_DIRECTORIES(${HEADERS_INSTALL_PATH})
INCLUDE_DIRECTORIES(${CHAT_UTILS_PATH})

LINK_DIRECTORIES(${LIBRARY_INSTALL_PATH})

SET (HEADER_FILES inc/dm_chatclient_controller_NativeChatClientController.h
                  inc/JNIChatClientListener.hpp)
SET (SOURCE_FILES src/dm_chatclient_controller_NativeChatClientController.cpp
                  src/JNIChatClientListener.cpp)

SET (LIBRARIES log
               chatClientAPI)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${LIBRARY_INSTALL_PATH})
