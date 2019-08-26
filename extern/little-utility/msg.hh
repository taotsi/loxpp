#ifndef MSG_HH
#define MSG_HH

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cassert>
#include <numeric>
#include <cmath>
#include <vector>
#include "macros.hh"

namespace taotsi{

class Msg{
public:
    static void tmark(const char* file, int line, const char* func)
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
    static void tmsg(const char* file, int line, const char* func, Args... args)
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
    static void tval(const char* val_name, T val)
    {
      if(!is_silent())
      {
        std::stringstream ss;
        ss << "\033[0;35m" << val_name << "\033[0m = " << val;
        core(ss);
      }
    }
    template<typename T>
    static void tval(const char* val_name, std::vector<T> &vals)
    {
      if(!is_silent())
      {
        std::stringstream ss;
        ss << "\033[0;35m" << val_name << "\033[0m = \n";
        for(auto &it : vals)
        {
            ss << it << "\n";
        }
        core(ss);
      }
    }
    template<typename ...Args>
    static void terr(const char* file, int line, const char* func, Args... args)
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
    static void twarn(const char* file, int line, const char* func, Args... args)
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
    static void ttrap(const char* file, int line, const char* func, Args... args)
    {
        std::stringstream ss;
        ss << "\033[0;41mTRAP\033[0m"
            << " " << file << "(" << line << "), " << func << "\n";
        core(ss, args...);
        assert(false);
    }
    static void tpause(const char* file, int line, const char* func)
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
    static void ti0(Args... args)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "\033[0;35mMESSAGE\033[0m  ";
            core(ss, args...);
        }
    }
    template<typename ...Args>
    static void ti1(Args... args)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "    \033[0;35mMESSAGE\033[0m  ";
            core(ss, args...);
        }
    }
    template<typename ...Args>
    static void ti2(Args... args)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "        \033[0;35mMESSAGE\033[0m  ";
            core(ss, args...);
        }
    }
    template<typename ...Args>
    static void tinfo(Args... args)
    {
        if(!is_silent())
        {
            std::stringstream ss;
            ss << "\033[0;42mINFO\033[0m  ";
            core(ss, args...);
        }
    }

    static void tmute()
    {
        if(!is_locked_silent())
        {
            is_silent() = true;
        }
    }
    static void tunmute()
    {
        if(!is_locked_silent())
        {
            is_silent() = false;
        }
    }
    static void tlockmute()
    {
        is_silent() = true;
        is_locked_silent() = true;
    }
    static void tunlockmute()
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
#define tmark() Msg::tmark(__FILENAME__, __LINE__, __FUNCTION__)
#define tmsg(...) Msg::tmsg(__FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define terr(...) Msg::terr(__FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define twarn(...) Msg::twarn(__FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define ttrap(...) Msg::ttrap(__FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define tpause(...) Msg::tpause(__FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define ti0(...) Msg::ti0(__VA_ARGS__)
#define ti1(...) Msg::ti1(__VA_ARGS__)
#define ti2(...) Msg::ti2(__VA_ARGS__)
#define tinfo(...) Msg::tinfo(__VA_ARGS__)
#define tval(val) Msg::tval(#val, val)

}

#endif // MSG_HH