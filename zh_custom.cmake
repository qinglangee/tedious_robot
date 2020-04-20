
# 链接内部的第三方库
# needBuild 0:不编译  1:需要编译 
function (link_third_part target thirdPartName includeFold needBuild)
    if(${needBuild} LESS 1)
        add_library(${thirdPartName} STATIC IMPORTED)
        set_property(TARGET ${thirdPartName} PROPERTY IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/thirdpart/${thirdPartName}/${thirdPartName}.lib)  
        # set_property(TARGET sqlite3 PROPERTY IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/thirdpart/sqlite3/sqlite3.lib)

    else()
        add_subdirectory(thirdpart/${thirdPartName})
    endif()
    
    target_link_libraries(${target} ${thirdPartName})
    target_include_directories(${target} PUBLIC ${PROJECT_SOURCE_DIR}/thirdpart/${thirdPartName}/${includeFold})
 
endfunction ()

function(link_zhlib needBuild)
    if(${needBuild} LESS 1)
        add_library(zhlib STATIC IMPORTED)
        set_property(TARGET zhlib PROPERTY IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/zhlib/zhlib.lib) 
    else()
        add_subdirectory(zhlib)
    endif()

    target_link_libraries(app zhlib)
    target_include_directories(app PUBLIC zhlib/include)
endfunction()

# 切换应用对应的信息
function(set_app_info ARG_APP_ID SRC_DIR ARG_NAME ARG_PRIORITY)
    message(STATUS "step  01")
    
    set(USER_APP_ID ${ARG_APP_ID} PARENT_SCOPE)
    message(STATUS "step  02 SRC_DIR is ${SRC_DIR}")
    file(GLOB_RECURSE fun_SOURCE_FILES ${SRC_DIR}/*.cpp) # 递归搜索 src 目录中的源文件, 可根据实际情况修改
    set(SOURCE_FILES ${fun_SOURCE_FILES} PARENT_SCOPE)
    include_directories(${SRC_DIR}/include) # 设置 src 目录为包含目录, 可根据实际情况修改

    SET(APP_NAME ${ARG_NAME})
    SET(APP_PRIVATE_MESSAGE_PRIORITY ${ARG_PRIORITY})

    configure_file ( "${PROJECT_SOURCE_DIR}/app.json.demo" "${PROJECT_SOURCE_DIR}/app.json" )
endfunction()