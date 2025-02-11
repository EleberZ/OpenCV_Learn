# Install script for directory: F:/Opencv/opencv/sources/modules

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "F:/Opencv/qt_mingw/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Qt/Qt5.14.1/Tools/mingw730_64/bin/objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/licenses" TYPE FILE RENAME "ade-LICENSE" FILES "F:/Opencv/qt_mingw/3rdparty/ade/ade-0.1.1d/LICENSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/licenses" TYPE FILE RENAME "ffmpeg-license.txt" FILES "F:/Opencv/opencv/sources/3rdparty/ffmpeg/license.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/licenses" TYPE FILE RENAME "ffmpeg-readme.txt" FILES "F:/Opencv/opencv/sources/3rdparty/ffmpeg/readme.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("F:/Opencv/qt_mingw/modules/.firstpass/calib3d/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/core/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/dnn/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/features2d/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/flann/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/gapi/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/highgui/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/imgcodecs/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/imgproc/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/java/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/js/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/ml/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/objdetect/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/photo/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/python/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/stitching/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/ts/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/video/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/videoio/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/.firstpass/world/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/core/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/flann/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/imgproc/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/java_bindings_generator/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/ml/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/photo/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/dnn/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/features2d/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/gapi/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/imgcodecs/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/videoio/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/calib3d/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/highgui/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/objdetect/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/stitching/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/ts/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/video/cmake_install.cmake")
  include("F:/Opencv/qt_mingw/modules/python_bindings_generator/cmake_install.cmake")

endif()

