file(GLOB addressbook_SRCS "*.cpp")

# Find required protobuf package
find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()

include_directories(${PROTOBUF_INCLUDE_DIRS})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS addressbook.proto)

add_library(addressbook ${addressbook_SRCS} ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(addressbook ${PROTOBUF_LIBRARIES})
set_target_properties(addressbook PROPERTIES COMPILE_FLAGS "-std=c++0x")

install(TARGETS addressbook DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/addressbook)

add_subdirectory(tests)

