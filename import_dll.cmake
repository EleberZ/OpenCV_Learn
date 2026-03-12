cmake_minimum_required(VERSION 3.20)

# ===================== 通用复制DLL函数 =====================
# 函数名：copy_target_dlls
# 参数说明：
#   TARGET          必选：目标可执行文件/库的名称（如 MyApp）
#   LIBRARIES       可选：需要复制DLL的库列表（如 OpenCV::Core Qt6::Widgets，默认所有已导入的库）
#   BIN_DIR         可选：DLL复制的目标路径（默认：目标的输出目录 $<TARGET_FILE_DIR:${TARGET}>）
function(copy_target_dlls)
    # 解析函数参数
    set(options "")
    set(oneValueArgs TARGET BIN_DIR)
    set(multiValueArgs LIBRARIES)
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT DEFINED ARGS_TARGET)
        message(FATAL_ERROR "copy_target_dlls 函数必须指定 TARGET 参数！")
    endif()

    if(NOT WIN32)
        message(STATUS "非Windows系统，跳过DLL复制逻辑")
        return()
    endif()

    # 确定DLL目标路径（默认：目标可执行文件的输出目录）
    if(DEFINED ARGS_BIN_DIR)
        set(target_bin_dir "${ARGS_BIN_DIR}/$<CONFIG>")
    else()
        set(target_bin_dir "$<TARGET_FILE_DIR:${ARGS_TARGET}>")
    endif()

    # 确定需要处理的库列表（未指定则取目标链接的所有库）
    if(DEFINED ARGS_LIBRARIES)
        set(libraries ${ARGS_LIBRARIES})
    else()
        # 获取目标链接的所有库
        get_target_property(linked_libs ${ARGS_TARGET} LINK_LIBRARIES)
        if(NOT linked_libs)
            message(STATUS "目标 ${ARGS_TARGET} 未链接任何库，跳过DLL复制")
            return()
        endif()
        set(libraries ${linked_libs})
    endif()

    # 遍历库列表，提取DLL路径并添加复制命令
    foreach(lib ${libraries})
        # 跳过非目标类型的库（如普通字符串、别名）
        if(NOT TARGET ${lib})
            continue()
        endif()

        # 获取库的类型（仅处理 SHARED_LIBRARY/IMPORTED_SHARED_LIBRARY 类型）
        get_target_property(lib_type ${lib} TYPE)
        if(NOT "${lib_type}" MATCHES "SHARED_LIBRARY")
            message(STATUS "库 ${lib} 不是动态库，跳过DLL复制")
            continue()
        endif()

        # 核心：获取不同配置下的DLL路径（IMPORTED_LOCATION_<CONFIG>）
        # 生成器表达式自动匹配 Debug/Release
        set(dll_path "$<TARGET_FILE:${lib}>")

        # 添加构建后复制命令
        add_custom_command(TARGET ${ARGS_TARGET} POST_BUILD
            # 复制DLL到目标bin目录（覆盖已存在的旧DLL）
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${dll_path}
                ${target_bin_dir}
            # 打印日志（方便调试）
            COMMENT "Copying DLL: ${dll_path} -> ${target_bin_dir}"
        )
    endforeach()

    # 提示：创建bin目录（避免路径不存在）
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Debug")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Release")
endfunction()