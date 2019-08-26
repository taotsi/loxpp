#ifndef MACROS_HH
#define MACROS_HH

#define DEFAULT_SPECIAL_FUNCTIONS(T)\
  T(const T&) = default;\
  T(T&&) = default;\
  T& operator=(const T&) = default;\
  T& operator=(T&&) = default;\
  ~T() = default;

#define DELETE_COPY_MOVE(T)\
  T(const T&) = delete;\
  T(T&&) = delete;\
  T& operator=(const T&) = delete;\
  T& operator=(T&&) = delete;

#define __FILENAME__                                                       \
  (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 \
                                    : __FILE__)

#endif // MACROS_HH