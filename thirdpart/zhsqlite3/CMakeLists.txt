file(GLOB_RECURSE SOURCE_FILES src/*.cpp) # 递归搜索 src 目录中的源文件, 可根据实际情况修改
include_directories(include) # 设置 src 目录为包含目录, 可根据实际情况修改
# 生成链接库
add_library (zhsqlite3 ${SOURCE_FILES})
target_compile_options(zhsqlite3  PRIVATE  $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)