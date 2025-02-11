# CMake generated Testfile for 
# Source directory: F:/Opencv/opencv/sources/modules/dnn
# Build directory: F:/Opencv/qt_mingw/modules/dnn
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_dnn "F:/Opencv/qt_mingw/bin/opencv_test_dnn.exe" "--gtest_output=xml:opencv_test_dnn.xml")
set_tests_properties(opencv_test_dnn PROPERTIES  LABELS "Main;opencv_dnn;Accuracy" WORKING_DIRECTORY "F:/Opencv/qt_mingw/test-reports/accuracy" _BACKTRACE_TRIPLES "F:/Opencv/opencv/sources/cmake/OpenCVUtils.cmake;1574;add_test;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1283;ocv_add_test_from_target;F:/Opencv/opencv/sources/modules/dnn/CMakeLists.txt;104;ocv_add_accuracy_tests;F:/Opencv/opencv/sources/modules/dnn/CMakeLists.txt;0;")
add_test(opencv_perf_dnn "F:/Opencv/qt_mingw/bin/opencv_perf_dnn.exe" "--gtest_output=xml:opencv_perf_dnn.xml")
set_tests_properties(opencv_perf_dnn PROPERTIES  LABELS "Main;opencv_dnn;Performance" WORKING_DIRECTORY "F:/Opencv/qt_mingw/test-reports/performance" _BACKTRACE_TRIPLES "F:/Opencv/opencv/sources/cmake/OpenCVUtils.cmake;1574;add_test;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1190;ocv_add_test_from_target;F:/Opencv/opencv/sources/modules/dnn/CMakeLists.txt;109;ocv_add_perf_tests;F:/Opencv/opencv/sources/modules/dnn/CMakeLists.txt;0;")
add_test(opencv_sanity_dnn "F:/Opencv/qt_mingw/bin/opencv_perf_dnn.exe" "--gtest_output=xml:opencv_perf_dnn.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_dnn PROPERTIES  LABELS "Main;opencv_dnn;Sanity" WORKING_DIRECTORY "F:/Opencv/qt_mingw/test-reports/sanity" _BACKTRACE_TRIPLES "F:/Opencv/opencv/sources/cmake/OpenCVUtils.cmake;1574;add_test;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1191;ocv_add_test_from_target;F:/Opencv/opencv/sources/modules/dnn/CMakeLists.txt;109;ocv_add_perf_tests;F:/Opencv/opencv/sources/modules/dnn/CMakeLists.txt;0;")
