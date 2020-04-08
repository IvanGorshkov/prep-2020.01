# CMake generated Testfile for 
# Source directory: /Users/ivangorshkov/prep-2020.01/project/tests
# Build directory: /Users/ivangorshkov/prep-2020.01/build/project/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BaseTest "/Users/ivangorshkov/prep-2020.01/build/project/tests/tests" "/Users/ivangorshkov/prep-2020.01/project/tests/data" "--gtest_filter=-*Extra*")
set_tests_properties(BaseTest PROPERTIES  _BACKTRACE_TRIPLES "/Users/ivangorshkov/prep-2020.01/project/tests/CMakeLists.txt;17;ADD_TEST;/Users/ivangorshkov/prep-2020.01/project/tests/CMakeLists.txt;0;")
add_test(ExtraTest "/Users/ivangorshkov/prep-2020.01/build/project/tests/tests" "/Users/ivangorshkov/prep-2020.01/project/tests/data" "--gtest_filter=*Extra*")
set_tests_properties(ExtraTest PROPERTIES  _BACKTRACE_TRIPLES "/Users/ivangorshkov/prep-2020.01/project/tests/CMakeLists.txt;21;ADD_TEST;/Users/ivangorshkov/prep-2020.01/project/tests/CMakeLists.txt;0;")
