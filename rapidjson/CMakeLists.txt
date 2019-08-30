add_executable(json_test json_test.cpp)
#target_link_libraries(json_test addressbook)
add_test(NAME json_test COMMAND json_test)
