#pragma once

#include <iostream>

static constexpr const bool DEBUG = false;

#ifndef UTIL_DEBUG
#define UTIL_DEBUG

#define LOG_FILE_AND_LINE __FILE_NAME__ << ":" << __LINE__ << "#" << __func__

#define FOO8(func, arg1, arg2, arg3, arg4, arg5, arg6, arg7) ({ \
    auto a1 = arg1;\
    auto a2 = arg2;\
    auto a3 = arg3;\
    auto a4 = arg4;\
    auto a5 = arg5;\
    auto a6 = arg6;\
    auto a7 = arg7;\
    if constexpr (DEBUG) std::cout << LOG_FILE_AND_LINE << " - " << #func << "(" << #arg1 << ", " << #arg2 << ", " << #arg3 << ", " << #arg4 << ", " << #arg5 << ", " << #arg6 << ", " << #arg7 << ")" << " ---> " << #func << "(" << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 <<")" << std::endl;\
    func(arg1, arg2, arg3, arg4, arg5, arg6, arg7);               \
})

#define FOO7(func, arg1, arg2, arg3, arg4, arg5, arg6) ({ \
    auto a1 = arg1;\
    auto a2 = arg2;\
    auto a3 = arg3;\
    auto a4 = arg4;\
    auto a5 = arg5;\
    auto a6 = arg6;\
    if constexpr (DEBUG) std::cout << LOG_FILE_AND_LINE << " - " << #func << "(" << #arg1 << ", " << #arg2 << ", " << #arg3 << ", " << #arg4 << ", " << #arg5 << ", " << #arg6 << ")" << " ---> " << #func << "(" << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 <<")" << std::endl;\
    func(arg1, arg2, arg3, arg4, arg5, arg6);               \
})

#define FOO6(func, arg1, arg2, arg3, arg4, arg5) ({ \
    auto a1 = arg1;\
    auto a2 = arg2;\
    auto a3 = arg3;\
    auto a4 = arg4;\
    auto a5 = arg5;                                      \
    if constexpr (DEBUG) std::cout << LOG_FILE_AND_LINE << " - " << #func << "(" << #arg1 << ", " << #arg2 << ", " << #arg3 << ", " << #arg4 << ", " << #arg5 << ")" << " ---> " << #func << "(" << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 <<")" << std::endl;\
    func(arg1, arg2, arg3, arg4, arg5);               \
})

#define FOO5(func, arg1, arg2, arg3, arg4) ({ \
    auto a1 = arg1;\
    auto a2 = arg2;\
    auto a3 = arg3;\
    auto a4 = arg4;                                \
    if constexpr (DEBUG) std::cout << LOG_FILE_AND_LINE << " - " << #func << "(" << #arg1 << ", " << #arg2 << ", " << #arg3 << ", " << #arg4 << ")" << " ---> " << #func << "(" << a1 << ", " << a2 << ", " << a3 << ", " << a4 <<")" << std::endl;\
    func(arg1, arg2, arg3, arg4);           \
})

#define FOO4(func, arg1, arg2, arg3) ({ \
    auto a1 = arg1; \
    auto a2 = arg2; \
    auto a3 = arg3; \
    if constexpr (DEBUG) std::cout << LOG_FILE_AND_LINE << " - " << #func << "(" << #arg1 << ", " << #arg2 ", " << #arg3")" << " ---> " << #func << "(" << a1 << ", " << a2 << ", " << a3 <<")" << std::endl;\
    func(arg1, arg2, arg3);               \
})

#define FOO3(func, arg1, arg2) ({ \
    auto a1 = arg1; \
    auto a2 = arg2; \
    if constexpr (DEBUG) std::cout << LOG_FILE_AND_LINE << " - " << #func << "(" << #arg1 << ", " << #arg2 << ")" << " ---> " << #func << "(" << a1 << ", " << a2  <<")" << std::endl; \
    func(arg1, arg2);           \
})

#define FOO2(func, arg1) ({ \
    auto a1 = arg1;              \
    if constexpr (DEBUG) std::cout << LOG_FILE_AND_LINE << " - " << #func << "(" << #arg1 << ")" << " ---> " << #func << "(" << a1 <<")" << std::endl; \
    func(arg1);               \
})

#define FOO1(func) ({ \
    if constexpr (DEBUG) std::cout << LOG_FILE_AND_LINE << " - " << #func << "()" << std::endl;\
    func();              \
})

#define FOO0 ({})

#define GET_MACRO(_0, _1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define debugGlCall(...) GET_MACRO(_0, ##__VA_ARGS__, FOO8, FOO7, FOO6, FOO5, FOO4, FOO3, FOO2, FOO1, FOO0)(__VA_ARGS__)

#endif

//#ifndef debugGlCall
//#define debugGlCall(funcName, ...) { if(DEBUG) std::cout << #funcName"("#__VA_ARGS__")" << std::endl; funcName(__VA_ARGS__);; }
//#endif