#pragma once

#include <iostream>

#ifndef NDEBUG
    #define T_Assert(Expr, Msg) __T_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
    #define T_Fail(Expr, Msg) __T_Fail(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
    #define T_Assert(Expr, Msg) ;
    #define T_Fail(Expr, Msg) ;
#endif

void __T_Assert(const char* exprStr, bool expr, const char* file, int line, const char* msg)
{
    if (!expr)
    {
        std::cerr << "Assert failed:\t" << msg << "\n"
            << "Expected:\t" << exprStr << "\n"
            << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}

bool __T_Fail(const char* exprStr, bool expr, const char* file, int line, const char* msg)
{
    if (!expr)
    {
        std::cerr << "Expression failed:\t" << msg << "\n"
            << "Expected:\t" << exprStr << "\n"
            << "Source:\t\t" << file << ", line " << line << "\n";
    }
    return !expr;
}
