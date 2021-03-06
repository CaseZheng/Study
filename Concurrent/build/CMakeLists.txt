#1.指定cmake版本
cmake_minimum_required(VERSION 2.8)

#2.PROJECT命令表明产生的工作空间的名称
PROJECT(Project)

MESSAGE(STATUS "Project Name: ${PROJECT_NAME}")               # 打印相关消息消息 
MESSAGE(STATUS "Project Directory: ${PROJECT_SOURCE_DIR}")

SET(CMAKE_BUILE_TYPE DEBUG)                     # 指定编译类型，debug 或者为 release
                                                # debug 版会生成相关调试信息，可以使用 GDB 进行 
                                                # release不会生成调试信息。当无法进行调试时查看此处是否设置为 debug
SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")           # 指定编译器 
                                                # CMAKE_C_FLAGS_DEBUG            ----  C 编译器
                                                # CMAKE_CXX_FLAGS_DEBUG        ----  C++ 编译器
                                                # -g：只是编译器，在编译的时候，产生调试信息。
                                                # -Wall：生成所有警告信息。一下是具体的选项，可以单独使用

include(CheckCXXCompilerFlag) 
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)  
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)  
if(COMPILER_SUPPORTS_CXX11)  
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")  
elseif(COMPILER_SUPPORTS_CXX0X)  
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")  
else()  
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")  
endif() 


SET(PROJECT_BINARY_DIR .)
SET(EXECUTABLE_OUTPUT_PATH .)

#3.头文件目录
INCLUDE_DIRECTORIES(../ ../libco)

#4.源文件目录
AUX_SOURCE_DIRECTORY(../ ../libco)

#5.设置环境变量等

# 进程 process
SET(SOURCE_LIST_PROCESS ../process_study.cpp)
SET(BIN_NAME_PROCESS process_study)
ADD_EXECUTABLE(${BIN_NAME_PROCESS} ${SOURCE_LIST_PROCESS})

# 线程 thread
SET(SOURCE_LIST_THREAD ../thread_study.cpp)
SET(BIN_NAME_THREAD thread_study)
ADD_EXECUTABLE(${BIN_NAME_THREAD} ${SOURCE_LIST_THREAD})

#需要链接的动态库
SET(SO_LIST pthread boost_thread boost_system boost_chrono)
TARGET_LINK_LIBRARIES(${BIN_NAME_THREAD} ${SO_LIST})


# 协程 libco
SET(SOURCE_LIST_LIBCO_COROUTINE ../libco_coroutine_study.cpp)
SET(BIN_NAME_LIBCO_COROUTINE libco_coroutine_study)
ADD_EXECUTABLE(${BIN_NAME_LIBCO_COROUTINE} ${SOURCE_LIST_LIBCO_COROUTINE})

SET(SO_LIST pthread)
TARGET_LINK_LIBRARIES(${BIN_NAME_LIBCO_COROUTINE} ${SO_LIST})

FIND_LIBRARY(LIBCOLIB libcolib.a ../libco/)                                                                                                                                                            
#需要链接的静态库                            
TARGET_LINK_LIBRARIES(${BIN_NAME_LIBCO_COROUTINE} ${LIBCOLIB})
