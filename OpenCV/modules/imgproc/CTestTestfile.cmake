# CMake generated Testfile for 
# Source directory: F:/Opencv/opencv/sources/modules/imgproc
# Build directory: F:/Opencv/qt_mingw/modules/imgproc
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_imgproc "F:/Opencv/qt_mingw/bin/opencv_test_imgproc.exe" "--gtest_output=xml:opencv_test_imgproc.xml")
set_tests_properties(opencv_test_imgproc PROPERTIES  LABELS "Main;opencv_imgproc;Accuracy" WORKING_DIRECTORY "F:/Opencv/qt_mingw/test-reports/accuracy" _BACKTRACE_TRIPLES "F:/Opencv/opencv/sources/cmake/OpenCVUtils.cmake;1574;add_test;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1283;ocv_add_test_from_target;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1070;ocv_add_accuracy_tests;F:/Opencv/opencv/sources/modules/imgproc/CMakeLists.txt;12;ocv_define_module;F:/Opencv/opencv/sources/modules/imgproc/CMakeLists.txt;0;")
add_test(opencv_perf_imgproc "F:/Opencv/qt_mingw/bin/opencv_perf_imgproc.exe" "--gtest_output=xml:opencv_perf_imgproc.xml")
set_tests_properties(opencv_perf_imgproc PROPERTIES  LABELS "Main;opencv_imgproc;Performance" WORKING_DIRECTORY "F:/Opencv/qt_mingw/test-reports/performance" _BACKTRACE_TRIPLES "F:/Opencv/opencv/sources/cmake/OpenCVUtils.cmake;1574;add_test;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1190;ocv_add_test_from_target;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1071;ocv_add_perf_tests;F:/Opencv/opencv/sources/modules/imgproc/CMakeLists.txt;12;ocv_define_module;F:/Opencv/opencv/sources/modules/imgproc/CMakeLists.txt;0;")
add_test(opencv_sanity_imgproc "F:/Opencv/qt_mingw/bin/opencv_perf_imgproc.exe" "--gtest_output=xml:opencv_perf_imgproc.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_imgproc PROPERTIES  LABELS "Main;opencv_imgproc;Sanity" WORKING_DIRECTORY "F:/Opencv/qt_mingw/test-reports/sanity" _BACKTRACE_TRIPLES "F:/Opencv/opencv/sources/cmake/OpenCVUtils.cmake;1574;add_test;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1191;ocv_add_test_from_target;F:/Opencv/opencv/sources/cmake/OpenCVModule.cmake;1071;ocv_add_perf_tests;F:/Opencv/opencv/sources/modules/imgproc/CMakeLists.txt;12;ocv_define_module;F:/Opencv/opencv/sources/modules/imgproc/CMakeLists.txt;0;")
