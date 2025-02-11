# CMake generated Testfile for 
# Source directory: F:/Opencv/opencv/sources/modules/gapi
# Build directory: F:/Opencv/qt_mingw/modules/gapi
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_gapi "F:/Opencv/qt_mingw/bin/opencv_test_gapi.exe" "--gtest_output=xml:opencv_test_gapi.xml")
set_tests_properties(opencv_test_gapi PROPERTIES  LABELS "Main;opencv_gapi;Accuracy" WORKING_DIRECTORY "F:/Opencv/qt_mingw/test-reports/accuracy" _BACKTRACE_TRIPLES "F:/Opencv/opencv/sources/cmake/OpenCVUtils.cmake;1574;add_test;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1283;ocv_add_test_from_target;F:/Opencv/opencv/sources/modules/gapi/CMakeLists.txt;105;ocv_add_accuracy_tests;F:/Opencv/opencv/sources/modules/gapi/CMakeLists.txt;0;")
add_test(opencv_perf_gapi "F:/Opencv/qt_mingw/bin/opencv_perf_gapi.exe" "--gtest_output=xml:opencv_perf_gapi.xml")
set_tests_properties(opencv_perf_gapi PROPERTIES  LABELS "Main;opencv_gapi;Performance" WORKING_DIRECTORY "F:/Opencv/qt_mingw/test-reports/performance" _BACKTRACE_TRIPLES "F:/Opencv/opencv/sources/cmake/OpenCVUtils.cmake;1574;add_test;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1190;ocv_add_test_from_target;F:/Opencv/opencv/sources/modules/gapi/CMakeLists.txt;115;ocv_add_perf_tests;F:/Opencv/opencv/sources/modules/gapi/CMakeLists.txt;0;")
add_test(opencv_sanity_gapi "F:/Opencv/qt_mingw/bin/opencv_perf_gapi.exe" "--gtest_output=xml:opencv_perf_gapi.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_gapi PROPERTIES  LABELS "Main;opencv_gapi;Sanity" WORKING_DIRECTORY "F:/Opencv/qt_mingw/test-reports/sanity" _BACKTRACE_TRIPLES "F:/Opencv/opencv/sources/cmake/OpenCVUtils.cmake;1574;add_test;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1191;ocv_add_test_from_target;F:/Opencv/opencv/sources/modules/gapi/CMakeLists.txt;115;ocv_add_perf_tests;F:/Opencv/opencv/sources/modules/gapi/CMakeLists.txt;0;")
