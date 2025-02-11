# CMake generated Testfile for 
# Source directory: F:/Opencv/opencv/sources/modules/highgui
# Build directory: F:/Opencv/qt_mingw/modules/highgui
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_highgui "F:/Opencv/qt_mingw/bin/opencv_test_highgui.exe" "--gtest_output=xml:opencv_test_highgui.xml")
set_tests_properties(opencv_test_highgui PROPERTIES  LABELS "Main;opencv_highgui;Accuracy" WORKING_DIRECTORY "F:/Opencv/qt_mingw/test-reports/accuracy" _BACKTRACE_TRIPLES "F:/Opencv/opencv/sources/cmake/OpenCVUtils.cmake;1574;add_test;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1283;ocv_add_test_from_target;F:/Opencv/opencv/sources/modules/highgui/CMakeLists.txt;162;ocv_add_accuracy_tests;F:/Opencv/opencv/sources/modules/highgui/CMakeLists.txt;0;")
