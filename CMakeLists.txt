cmake_minimum_required(VERSION 3.9)
project(cqcppsdk-demo) # 填写项目名称

set(CMAKE_CXX_STANDARD 17) # 设置 C++ 标准版本为 C++17, 必须

include(extern/cqcppsdk/cqcppsdk.cmake) # 包含 SDK 的 CMake 脚本, 必须
include(zh_custom.cmake) # 自定义的一些方法

#include_directories(src) # 设置 src 目录为包含目录, 可根据实际情况修改

# 从 app_id.txt 文件读取 app id, 也可以直接设置
file(READ "app_id.txt" APP_ID)
string(STRIP "${APP_ID}" APP_ID)


# 切换应用对应的信息
function(set_app_info USER_APP_ID SRC_DIR ARG_NAME ARG_PRIORITY)
    message(STATUS "step  01  id is ${USER_APP_ID}")
    cq_set_app_id(${USER_APP_ID}) # 设置 app id, 必须
    message(STATUS "step  02 SRC_DIR is ${SRC_DIR}")
    file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp) # 递归搜索 src 目录中的源文件, 可根据实际情况修改
    message(STATUS "step  03 src files is  ${SOURCE_FILES}")
    include_directories(${SRC_DIR}/include) # 设置 src 目录为包含目录, 可根据实际情况修改
    message(STATUS "step  04")

    
cq_set_app_id("com.xmalloc.cqapp.adv") # 设置 app id, 必须
file(GLOB_RECURSE SOURCE_FILES src4/*.cpp) # 递归搜索 src 目录中的源文件, 可根据实际情况修改
include_directories(src4/include) # 设置 src 目录为包含目录, 可根据实际情况修改

    SET(APP_NAME ${ARG_NAME})
    SET(APP_PRIVATE_MESSAGE_PRIORITY ${ARG_PRIORITY})

    configure_file ( "${PROJECT_SOURCE_DIR}/app.json.demo" "${PROJECT_SOURCE_DIR}/app.json" )
endfunction()



# 添加子目录

# 设置应用信息，多个应用间切换
# set_app_info(${APP_ID} src "无聊机器人" 20000)
# set_app_info("com.xmalloc.cqapp.greet" src2 "迎新小弟弟" 30000)
# set_app_info("com.xmalloc.cqapp.cmd" src3 "命令和聊天" 30000)
set_app_info("com.xmalloc.cqapp.adv" src4 "优惠播放机" 20000)
cq_set_app_id("com.xmalloc.cqapp.adv") # 设置 app id, 必须
file(GLOB_RECURSE SOURCE_FILES src4/*.cpp) # 递归搜索 src 目录中的源文件, 可根据实际情况修改
include_directories(src4/include) # 设置 src 目录为包含目录, 可根据实际情况修改





if (CQ_CAN_BUILD_STD_MODE)
cq_add_std_app(${SOURCE_FILES}) # 添加 std 模式的动态链接库构建目标
cq_install_std_app("d:/software/CQPro/")
message(STATUS "lalalalalalalla")
endif ()

# 添加 dev 模式的可执行文件构建目标
# cq_add_dev_app(${SOURCE_FILES})




# 添加链接库和include文件目录
link_zhlib(1)



link_third_part(app fileutils "src" 1)
link_third_part(app zhutils include 1)

link_third_part(app myzh src 1)

link_third_part(app cjsonobject src 1)
link_third_part(app sqlite3 "" 1)







