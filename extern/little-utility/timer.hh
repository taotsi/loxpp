#pragma once
#include <thread>
#include <stdexcept>
#include <experimental/filesystem>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cassert>
#include <numeric>
#include <cmath>

namespace taotsi{

// resolution: ms
class Timer{
public:
    Timer()
        : start_{std::chrono::high_resolution_clock::time_point::min()}{
        id_ = ++timer_count();
    }
    void Clear(){
        start_ = std::chrono::high_resolution_clock::time_point::min();
    }
    bool IsStarted() const{
        return(start_.time_since_epoch() !=
            std::chrono::high_resolution_clock::duration(0));
    }
    void tStart(const char* file, int line, const char* func){
        if(!is_silent()){
            if(!is_plain_text()){
                std::stringstream ss;
                ss << "\033[0;44mTimer(" << id_ << ")\033[0m" << " started, "
                    << file << "(" << line << "), " << func << "\n";
                std::cout << ss.str();
            }
        }
        start_ = std::chrono::high_resolution_clock::now();
    }
    unsigned long long tPutNow(const char* file, int line, const char* func){
        auto t = GetUs();
        if(!is_silent()){
            std::stringstream ss;
            ss.imbue(std::locale(""));
            if(!is_plain_text()){
                ss << "\033[0;44mTimer(" << id_ << ")\033[0m" << " ended,   "
                    << file << "(" << line << "), " << func << "\n"
                    << "> " << t << " ms passed\n";
                std::cout << ss.str();
            }else{
                ss << t << "\n";
                std::cout << ss.str();
            }
        }
        return t;
    }
    unsigned long long GetUs(){
        if(IsStarted()){
            std::chrono::high_resolution_clock::duration diff
                = std::chrono::high_resolution_clock::now() - start_;
            return static_cast<unsigned long long>(
                std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
        }else{
            if(!is_silent()){
                if(is_plain_text()){
                    std::stringstream ss;
                    std::cout << "\033[0;44mTimer(" << id_ << ")\033[0m"
                        << "  You have't started the timer!\n";
                }else{
                    std::cout << "You have't started the timer!\n";
                }
            }
        }
        return 0;
    }
    static void UsePlainText(bool flag){
        is_plain_text() = flag;
    }
    static void Mute(){
        is_silent() = true;
    }
    static void UnMute(){
        is_silent() = false;
    }
private:
    std::chrono::high_resolution_clock::time_point start_;
    int id_;
    static int& timer_count(){
        static int count = 0;
        return count;
    }
    static bool& is_plain_text(){
        static bool is_plain_text_ = false;
        return is_plain_text_;
    }
    static bool& is_silent(){
        static bool is_silent_ = false;
        return is_silent_;
    }
};
#define tStart() tStart(__FILENAME__, __LINE__, __FUNCTION__)
#define tPutNow() tPutNow(__FILENAME__, __LINE__, __FUNCTION__)

} // namespace droneworld