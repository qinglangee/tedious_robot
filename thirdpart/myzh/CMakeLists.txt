# 查找当前目录下的所有源文件

# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(./src DIR_LIB_SRCS)

# 生成链接库
add_library (myzh ${DIR_LIB_SRCS})

target_compile_options(myzh  PRIVATE  $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)