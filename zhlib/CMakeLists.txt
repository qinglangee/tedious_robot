


# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
# aux_source_directory(./src DIR_LIB_SRCS)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp) # 递归搜索 src 目录中的源文件, 可根据实际情况修改
include_directories(include) # 设置 src 目录为包含目录, 可根据实际情况修改
# 生成链接库
add_library (zhlib ${SOURCE_FILES})
# add_library (zhlib ${DIR_LIB_SRCS})
target_compile_options(zhlib  PRIVATE  $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
target_include_directories(zhlib PUBLIC ../extern/cqcppsdk/include)

target_include_directories(zhlib PUBLIC ../thirdpart/cjsonobject/src)
target_include_directories(zhlib PUBLIC ../thirdpart/sqlite3)


target_include_directories(zhlib PUBLIC ../thirdpart/fileutils/src)
target_include_directories(zhlib PUBLIC ../thirdpart/zhutils/include)