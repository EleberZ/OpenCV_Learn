function(import_lib target_name lib_name)
    set(dll_suffix "${ARGV4}")

    if(NOT TARGET ${target_name})
        message(FATAL_ERROR "${target_name} lib is not exist！")
    endif()
    if(NOT EXISTS "${include_dir}")
        message(FATAL_ERROR "${include_dir} header_dir is not exist！")
    endif()
    if(NOT EXISTS "${lib_dir}")
        message(FATAL_ERROR "${lib_dir} header_dir is not exist！")
    endif()

    target_include_directories(${target_name} PUBLIC "${include_dir}")

    if (WIN32)
        if(MSVC)
            target_link_directories(${target_name} PUBLIC "${lib_dir}")
            target_link_libraries(${target_name} PRIVATE 
                debug "${lib_name}"
                optimized "${lib_name}"
            )
        elseif(MINGW)
            target_link_directories(${target_name} PUBLIC "${lib_dir}")
            target_link_libraries(${target_name} PRIVATE  "${lib_name}")
        endif()
        
        get_target_property(target_output_dir ${target_name} RUNTIME_OUTPUT_DIRECTORY)
        if(NOT target_output_dir)
            # 未显式设置输出目录时，使用默认路径
            set(target_output_dir "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}")
        endif()

    endif(WIN32)
    
    #遍历库
    foreach(lib IN ${lib_name})
        if(NOT TARGET ${lib})
            message(WARNING "库${lib}不是有效目标，跳过dll复制")
            continue()
        endif()
    endforeach(lib)

endfunction()


# ------------------------------------------------------------------------------
# 通用引入库函数：引入库并自动复制DLL到目标路径
# 参数说明：
#   target_name: 要链接库的目标程序名（如可执行文件、动态库）
#   lib_name: 库的名称（用于查找库文件，如 "opencv_world480"）
#   include_dir: 库的头文件目录（绝对路径/相对路径）
#   lib_dir: 库的二进制文件目录（包含.lib/.dll，绝对路径/相对路径）
#   [可选] dll_suffix: DLL文件名后缀（如 Debug 下的 "d"，默认空）
# ------------------------------------------------------------------------------
function(import_library target_name lib_name include_dir lib_dir)
    # 2. 添加头文件目录（PUBLIC：让依赖该目标的其他目标也能访问）
    target_include_directories(${target_name} PUBLIC "${include_dir}")

    # 3. 链接库文件（区分Windows/MSVC的Debug/Release）
    if(MSVC)
        # 多配置编译（Debug/Release）自动匹配库后缀
        target_link_directories(${target_name} PUBLIC "${lib_dir}")
        target_link_libraries(${target_name} PRIVATE 
            debug "${lib_name}${dll_suffix}"
            optimized "${lib_name}"
        ) 
    else()
        # 非Windows系统直接链接
        target_link_directories(${target_name} PUBLIC "${lib_dir}")
        target_link_libraries(${target_name} PRIVATE "${lib_name}")
    endif()

    # 4. 复制DLL到目标输出目录（仅Windows系统）
    if(WIN32)
        # 获取目标的输出目录（自动适配Debug/Release/RelWithDebInfo等）


        # 构造DLL文件名
        set(dll_filename "${lib_name}${dll_suffix}.dll")
        set(dll_source "${lib_dir}/${dll_filename}")

        # 验证DLL文件是否存在
        if(EXISTS "${dll_source}")
            # 配置复制命令（POST_BUILD：编译后执行）
            add_custom_command(TARGET ${target_name} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${dll_source}"
                "${target_output_dir}/"
                COMMENT "复制DLL: ${dll_filename} -> ${target_output_dir}"
            )
        else()
            message(WARNING "未找到DLL文件：${dll_source}，跳过复制")
        endif()
    endif()
endfunction()



