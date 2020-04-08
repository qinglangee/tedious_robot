cmake_minimum_required(VERSION 3.9)
project(cqcppsdk-demo) # 填写项目名称

set(CMAKE_CXX_STANDARD 17) # 设置 C++ 标准版本为 C++17, 必须

include(extern/cqcppsdk/cqcppsdk.cmake) # 包含 SDK 的 CMake 脚本, 必须
include(zh_custom.cmake) # 自定义的一些方法

#include_directories(src) # 设置 src 目录为包含目录, 可根据实际情况修改

# 从 app_id.txt 文件读取 app id, 也可以直接设置
file(READ "app_id.txt" APP_ID)
string(STRIP "${APP_ID}" APP_ID)

# 添加子目录

# 第一个应用 无聊机器人
# cq_set_app_id(${APP_ID}) # 设置 app id, 必须
# file(GLOB_RECURSE SOURCE_FILES src/*.cpp) # 递归搜索 src 目录中的源文件, 可根据实际情况修改
# include_directories(src/include) # 设置 src 目录为包含目录, 可根据实际情况修改

# 第二个应用 迎新小弟弟
# cq_set_app_id("com.xmalloc.cqapp.greet") # 设置 app id, 必须
# file(GLOB_RECURSE SOURCE_FILES src2/*.cpp) # 递归搜索 src 目录中的源文件, 可根据实际情况修改
# include_directories(src2/include) # 设置 src 目录为包含目录, 可根据实际情况修改

# 第三个应用 命令聊天
# cq_set_app_id("com.xmalloc.cqapp.cmd") # 设置 app id, 必须
# file(GLOB_RECURSE SOURCE_FILES src3/*.cpp) # 递归搜索 src 目录中的源文件, 可根据实际情况修改
# include_directories(src3/include) # 设置 src 目录为包含目录, 可根据实际情况修改

# 第四个应用 优惠播放机
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
link_zhlib(0)



link_third_part(app fileutils "src" 0)
link_third_part(app zhutils include 0)

link_third_part(app myzh src 0)

link_third_part(app cjsonobject src 0)
link_third_part(app sqlite3 "" 0)







