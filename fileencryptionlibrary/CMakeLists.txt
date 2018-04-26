# cmake最低的版本
cmake_minimum_required(VERSION 3.4.1)

add_library(

    #库名字
    FileOperation

    #库类型
    SHARED

    #原文件地址
    src/main/cpp/FileOperation.cpp

)


find_library(
    #库的名字
    log-lib

    #库的真实名字
    log
)

#关联库
target_link_libraries(

    FileOperation

    ${log-lib}
)
