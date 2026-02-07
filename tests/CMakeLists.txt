add_executable(test_serial test_serial.c ../src/serial.c)
target_include_directories(test_serial PRIVATE ../src)
target_compile_definitions(test_serial PRIVATE _GNU_SOURCE)
add_test(NAME test_serial COMMAND test_serial)
