#ifndef UTILITY_HH
#define UTILITY_HH

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cassert>
#include <numeric>
#include <cmath>

namespace loxpp{

class Msg{
public:
    static void lmark(const char* file, int line, const char* func)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "\033[0;45mMARK\033[0m"
                << " " << file << "(" << line << "), " << func << "\n";
            std::cout << ss.str();
        }
    }
    template<typename ...Args>
    static void lmsg(const char* file, int line, const char* func, Args... args)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "\033[0;45mMESSAGE\033[0m"
                << " " << file << "(" << line << "), " << func << "\n";
            core(ss, args...);
        }
    }
    template<typename T>
    static void lval(const char* val_name, T val)
    {
      if(!is_silent())
      {
        std::stringstream ss;
        ss << "\033[0;35m" << val_name << "\033[0m = " << val;
        core(ss);
      }
    }
    template<typename ...Args>
    static void lerr(const char* file, int line, const char* func, Args... args)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "\033[0;41mERROR\033[0m"
                << " " << file << "(" << line << "), " << func << "\n";
            core(ss, args...);
        }
    }
    template<typename ...Args>
    static void lwarn(const char* file, int line, const char* func, Args... args)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "\033[0;43mWARNING\033[0m"
                << " " << file << "(" << line << "), " << func << "\n";
            core(ss, args...);
        }
    }
    template<typename ...Args>
    static void ltrap(const char* file, int line, const char* func, Args... args)
    {
        std::stringstream ss;
        ss << "\033[0;41mTRAP\033[0m"
            << " " << file << "(" << line << "), " << func << "\n";
        core(ss, args...);
        assert(false);
    }
    static void lpause(const char* file, int line, const char* func)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "\033[0;43mPAUSE\033[0m"
                << " " << file << "(" << line << "), " << func << "\n";
            std::cout << ss.str();
            char in;
            std::cin >> in;
        }
    }
    template<typename ...Args>
    static void li0(Args... args)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "\033[0;35mMESSAGE\033[0m  ";
            core(ss, args...);
        }
    }
    template<typename ...Args>
    static void li1(Args... args)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "    \033[0;35mMESSAGE\033[0m  ";
            core(ss, args...);
        }
    }
    template<typename ...Args>
    static void li2(Args... args)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "        \033[0;35mMESSAGE\033[0m  ";
            core(ss, args...);
        }
    }
    template<typename ...Args>
    static void linfo(Args... args)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "\033[0;42mINFO\033[0m  ";
            core(ss, args...);
        }
    }

    static void lmute()
    {
        if(!is_locked_silent())
        {
            is_silent() = true;
        }
    }
    static void lunmute()
    {
        if(!is_locked_silent())
        {
            is_silent() = false;
        }
    }
    static void llockmute()
    {
        is_silent() = true;
        is_locked_silent() = true;
    }
    static void lunlockmute()
    {
        is_silent() = false;
        is_locked_silent() = false;
    }
private:
    static void core(std::stringstream &ss)
    {
        std::cout << ss.str() << "\n";
    }
    template<typename T>
    static void core(std::stringstream &&ss, T val)
    {
        ss << val;
        core(ss);
    }
    template<typename T, typename ...Args>
    static void core(std::stringstream &ss, T val, Args... args)
    {
        ss << val;
        core(ss, args...);
    }
    static bool& is_silent()
    {
        static bool is_silent_ = false;
        return is_silent_;
    }
    static bool& is_locked_silent()
    {
        static bool is_locked_silent_ = false;
        return is_locked_silent_;
    }
};
#define lmark() Msg::lmark(__FILE__, __LINE__, __FUNCTION__)
#define lmsg(...) Msg::lmsg(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define lerr(...) Msg::lerr(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define lwarn(...) Msg::lwarn(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define ltrap(...) Msg::ltrap(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define lpause(...) Msg::lpause(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define li0(...) Msg::li0(__VA_ARGS__)
#define li1(...) Msg::li1(__VA_ARGS__)
#define li2(...) Msg::li2(__VA_ARGS__)
#define linfo(...) Msg::linfo(__VA_ARGS__)
#define lval(val) Msg::lval(#val, val)

}

#endif // UTILITY_HH