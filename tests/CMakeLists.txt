add_executable(test_utils test_utils.c ../src/utils.c)
target_include_directories(test_utils PRIVATE ../src)
add_test(NAME test_utils COMMAND test_utils)
