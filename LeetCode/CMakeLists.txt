#1.指定cmake版本
cmake_minimum_required(VERSION 2.8)

#2.PROJECT命令表明产生的工作空间的名称
PROJECT(Alogorithm_sort)

MESSAGE(STATUS "Project Name: ${PROJECT_NAME}")               # 打印相关消息消息 
MESSAGE(STATUS "Project Directory: ${PROJECT_SOURCE_DIR}")

SET(CMAKE_BUILE_TYPE DEBUG)                     # 指定编译类型，debug 或者为 release
                                                # debug 版会生成相关调试信息，可以使用 GDB 进行 
                                                # release不会生成调试信息。当无法进行调试时查看此处是否设置为 debug
SET(CMAKE_CXX_FLAGS_DEBUG "")           # 指定编译器 
                                                # CMAKE_C_FLAGS_DEBUG            ----  C 编译器
                                                # CMAKE_CXX_FLAGS_DEBUG        ----  C++ 编译器
                                                # -g：只是编译器，在编译的时候，产生调试信息。
                                                # -Wall：生成所有警告信息。一下是具体的选项，可以单独使用

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")  
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

SET(PROJECT_BINARY_DIR ./build)

ADD_EXECUTABLE(run0001 0001_two_sum.cpp)
ADD_EXECUTABLE(run0002 0002_add_two_numbers.cpp)
ADD_EXECUTABLE(run0003 0003_longest_substring_without_repeating_characters.cpp)
ADD_EXECUTABLE(run0004 0004_median_of_two_sorted_arrays.cpp)
ADD_EXECUTABLE(run0023 0023_merge_k_sorted_lists.cpp)
ADD_EXECUTABLE(run0124 0124_binary_tree_maximum_path_sum.cpp)
ADD_EXECUTABLE(run0146 0146_LRU_cache.cpp)
ADD_EXECUTABLE(run0148 0148_sort_list.cpp)
ADD_EXECUTABLE(run0215 0215_kth_largest_element_in_an_array.cpp)
ADD_EXECUTABLE(run0235 0235_lowest_common_ancestor_of_a_binary_search_tree.cpp)
ADD_EXECUTABLE(run0236 0236_lowest_common_ancestor_of_a_binary_tree.cpp)
