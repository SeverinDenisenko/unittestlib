add_executable(simple-test simple_test.cpp)
add_executable(env-test env_test.cpp)

add_test(NAME simple-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/simple-test)
add_test(NAME env-test COMMAND ${CMAKE_CURRENT_BINARY_DIR}/env-test)

target_link_libraries(simple-test unittest)
target_link_libraries(env-test unittest)

if(MSVC)
    target_compile_options(simple-test PRIVATE /W4 /WX)
    target_compile_options(env-test PRIVATE /W4 /WX)
else()
    target_compile_options(simple-test PRIVATE -Wall -Wextra -Werror)
    target_compile_options(env-test PRIVATE -Wall -Wextra -Werror)
endif()
