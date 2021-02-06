cmake_minimum_required(VERSION 3.7.0)

project(Microservices)

set (CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_BUILD_TYPE Debug)

#build gateway
add_executable(gateway "")

target_sources(gateway
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/gateway/gateway.c
  )

install(TARGETS gateway DESTINATION bin)

#build service
add_executable(service "")

target_sources(service
  PUBLIC 
  ${CMAKE_CURRENT_LIST_DIR}/src/services/c_service/service.c
  )

install(TARGETS service DESTINATION bin)
