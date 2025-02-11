# CMakeList.txt: OpenCV_Learn 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ProjectName "OpenCV_Learn")

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (${ProjectName} VERSION 1.0.0 LANGUAGES CXX)
include ("${PROJECT_SOURCE_DIR}/src/gui/gui.cmake")
if(${PLATFORM} STREQUAL "x64")
    set(mingw_tools $ENV{QT_X64_MinGW_Tool})
    set(qt_lib_path $ENV{QT_LIB_X64_MinGW})
elseif(${PLATFORM} STREQUAL "x86")
    set(mingw_tools $ENV{QT_X86_MinGW_Tool})
    set(qt_lib_path $ENV{QT_LIB_X86_MinGW})
endif()
find_program(CMAKE_CXX_COMPILER "${mingw_tools}/bin/g++.exe" )
find_program(CMAKE_C_COMPILER "${mingw_tools}/bin/gcc.exe" )		
find_program(CMAKE_MAKE_PROGRAM "${mingw_tools}/bin/mingw32-make.exe")
find_program(CMAKE_RC_COMPILER "${mingw_tools}/bin/windres.exe")
find_program(LUPDATE_EXECUTABLE "${qt_lib_path}/bin/lupdate.exe")
find_program(LRELEASE_EXECUTABLE "${qt_lib_path}/bin/lrelease.exe")
message(WARNING ${CMAKE_CXX_COMPILER})

set(CMAKE_GENERATOR	"MinGW Makefiles")
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_PREFIX_PATH "${qt_lib_path}")

if(${PLATFORM} STREQUAL "x64")
    find_library(SELF_DLL YXEngine
        "${PROJECT_SOURCE_DIR}/bin/YXEngine.dll"
        "${PROJECT_SOURCE_DIR}/bin/LTDMC.dll"
    )
    find_library(SELF_LIB YXEngine
        "${PROJECT_SOURCE_DIR}/lib/YXEngine.a"
        "${PROJECT_SOURCE_DIR}/lib/LTDMC.a"
    )
elseif(${PLATFORM} STREQUAL "x86")
    find_library(SELF_DLL YXEngine
        "${PROJECT_SOURCE_DIR}/bin/YXEngine32.dll"
        "${PROJECT_SOURCE_DIR}/bin/LTDMC32.dll"
    )
    find_library(SELF_LIB YXEngine
        "${PROJECT_SOURCE_DIR}/lib/YXEngine32.a"
        "${PROJECT_SOURCE_DIR}/lib/LTDMC32.a"
    )
endif()
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0") 
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -ffast-math -funroll-loops -s") 
endif()
# Enable C++11  
add_definitions(-DHAS_INCLUDE_CHRONO)
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/bin")
set(PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/cmake/build/X64-Debug")
set(LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/cmake/build/X64-Debug/install")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin") 
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_PARALLEL_LEVEL 12)		#用多少线来构建makefile

set(CMAKE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets Network SerialPort SerialBus Xml REQUIRED)
find_package(Qt5 COMPONENTS LinguistTools REQUIRED)
set(GTest_DIR "$ENV{VCPKG_ROOT}/packages/gtest_vcpkg-triplets/share/gtest")
find_package(GTest CONFIG REQUIRED)
set(OpenCV_DIR "$ENV{OpenCV_INSTALL_PATH}")
find_package(OpenCV COMPONENTS REQUIRED)

set(src "${PROJECT_SOURCE_DIR}/src")
set(src_cv "${src}/cv")
set(src_gui "${src}/gui")

set(cpp_h_dir
    ${PROJECT_SOURCE_DIR}
    ${src_cv}
    ${gui_cpp_h_dir}
    ${src_processflow}
    ${src_task}
    ${src_tma}
    ${src_peripherals}
)

set(lib_h_dir
    ${src_engine}
)
#--------------------------头文件路径-----------------------------
set(exclude_header									#排除头文件
        "${gui_exclude_header}"
)
foreach(header_dir_single ${cpp_h_dir})
    file(GLOB header_single "${header_dir_single}/*.h")
    list(APPEND h_list "${header_single}")
endforeach(header_dir_single ${header_dir})
    list(REMOVE_ITEM h_list ${exclude_header})
# 头文件路径  

#--------------------------源文件路径------------------------------
set(exclude_source									#排除源文件
        "${gui_exclude_source}"
)
foreach(source_dir_single ${cpp_h_dir})
    file(GLOB src_list "${source_dir_single}/*.cpp")
    list(APPEND cpp_list "${src_list}")					#cpp源文件列表
endforeach(source_dir_single ${cpp_h_dir})
    list(REMOVE_ITEM cpp_list ${exclude_source})
# 源文件路径 

#--------------------------翻译文件--------------------------------
set(exclude_ts
    ""
)
set(ts_dir
    ${PROJECT_SOURCE_DIR}
)
foreach(ts_files ${ts_dir})
    file(GLOB ts_file "${ts_files}/*.ts")
    list(APPEND ts_list "${ts_file}")
endforeach(ts_files ${ts_dir})
    list(REMOVE_ITEM ts_list ${exclude_ts})

set(exclude_qm
    ""
)
set(qm_dir
    ${PROJECT_SOURCE_DIR}
)
foreach(qm_files ${qm_dir})
    file(GLOB qm_file "${qm_files}/*.qm")
    list(APPEND qm_list "${qm_file}")
endforeach(qm_files ${qm_dir})
    list(REMOVE_ITEM qm_list ${exclude_qm})

# 查找 lupdate 和 lrelease 工具
find_program(LUPDATE_EXECUTABLE lupdate)
find_program(LRELEASE_EXECUTABLE lrelease)

# 提取翻译字符串生成.ts文件
execute_process( 
    COMMAND ${LUPDATE_EXECUTABLE} ${cpp_list} -ts ${CMAKE_SOURCE_DIR}/TMA_CN.ts
)
# 编译.ts为.qm
execute_process( 
    COMMAND ${LRELEASE_EXECUTABLE} ${CMAKE_SOURCE_DIR}/TMA_CN.ts
    -qm ${CMAKE_SOURCE_DIR}/TMA_CN.qm
)
# 翻译文件

add_executable(${ProjectName} 
    "${cpp_list}" 
    "${h_list}" 
    "${qrc_file}" 
    "${ts_file}"
    "${CMAKE_SOURCE_DIR}/resource.rc"
    #"${CMAKE_SOURCE_DIR}/cpp.hint"
)  
# 将生成.qm作为依赖

set_target_properties(${ProjectName} PROPERTIES WIN32_EXECUTABLE true)
target_compile_definitions(${ProjectName} PRIVATE QT_DEPRECATED_WARNINGS)  
target_include_directories(${ProjectName} PRIVATE  
    "${cpp_h_dir}"
    "${lib_h_dir}"
)
target_link_directories(${ProjectName} PUBLIC "${PROJECT_SOURCE_DIR}/lib")
target_link_directories(${ProjectName} PUBLIC "${PROJECT_SOURCE_DIR}/bin")
target_link_libraries(${ProjectName} PUBLIC 
    Qt5::Core 
    Qt5::Gui 
    Qt5::Widgets 
    Qt5::Network 
    Qt5::SerialPort 
    Qt5::SerialBus 
    Qt5::Xml
)

target_link_libraries(${ProjectName} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
# Add libraries to the target  
if(${PLATFORM} STREQUAL "x64")
    target_link_libraries(${ProjectName} PUBLIC 
        ${PROJECT_SOURCE_DIR}/lib/DxImageProc.lib
        ${PROJECT_SOURCE_DIR}/lib/GxIAPI.lib
        ${PROJECT_SOURCE_DIR}/lib/LTDMC.lib
        ${PROJECT_SOURCE_DIR}/lib/libYXEngine.a
        ${PROJECT_SOURCE_DIR}/lib/libopencv_core411.dll.a
        ${PROJECT_SOURCE_DIR}/lib/libopencv_imgproc411.dll.a
    )
elseif(${PLATFORM} STREQUAL "x86")
    target_link_libraries(${ProjectName} PUBLIC 
        ${PROJECT_SOURCE_DIR}/lib/DxImageProc.lib
        ${PROJECT_SOURCE_DIR}/lib/GxIAPI.lib
        ${PROJECT_SOURCE_DIR}/lib/LTDMC32.lib
        ${PROJECT_SOURCE_DIR}/lib/libYXEngine32.a
        ${PROJECT_SOURCE_DIR}/lib/libopencv_core411.dll.a
        ${PROJECT_SOURCE_DIR}/lib/libopencv_imgproc411.dll.a
    )
endif()

add_test(AllTestIn ${ProjectName} ${ProjectName})

if(NOT TARGET_PATH STREQUAL "")  
    install(TARGETS ${ProjectName} DESTINATION ${TARGET_PATH})  
endif()  

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${ProjectName} PROPERTY CXX_STANDARD 17)
endif()

# TODO: 如有需要，请添加测试并安装目标。
