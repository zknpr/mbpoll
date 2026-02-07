add_executable(test_serial test_serial.c ../src/serial.c)
target_include_directories(test_serial PRIVATE ../src)
add_test(NAME test_serial COMMAND test_serial)
