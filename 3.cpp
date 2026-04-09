```cpp
#include <iostream>
#include <chrono>

#define PI 3.1415926535

#define SUM(a, b) ((a) + (b))

#define MULT_BAD(a, b) a * b
#define MULT_GOOD(a, b) ((a) * (b))

#define SQUARE(x) ((x) * (x))

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define DEBUG

#ifdef DEBUG
#define DEBUG_LOG(x) std::cout << "[DEBUG] " << x << std::endl
#else
#define DEBUG_LOG(x)
#endif

#ifndef RELEASE
std::cout << "RELEASE is not defined" << std::endl;
#endif

#define VERSION 1

#if VERSION == 1
std::cout << "v1" << std::endl;
#else
std::cout << "other version" << std::endl;
#endif

// 10. include guard — шаблон заголовочного файла
#ifndef MY_HEADER_H
#define MY_HEADER_H

// Здесь может быть код заголовочного файла

#endif // MY_HEADER_H

#define LOG(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl

#define PRINT(x) std::cout << #x << " = " << (x) << std::endl

#define VAR_NAME(prefix, num) prefix##num

#define STRINGIFY(x) #x

#define CHECK(x) \
    if (!(x)) { \
        std::cerr << "CHECK failed: " << #x << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
    }

#define SAFE_DELETE(ptr) do { delete ptr; ptr = nullptr; } while (0)

#define TIMER_START auto start = std::chrono::high_resolution_clock::now()
#define TIMER_END \
    auto end = std::chrono::high_resolution_clock::now(); \
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); \
    std::cout << "Time: " << duration.count() << " ms" << std::endl

#define CHECK_PTR(p) \
    if (!p) { \
        std::cerr << "Null pointer at " << __FILE__ << ":" << __LINE__ << std::endl; \
        return; \
    }

#define SIMPLE_ASSERT(x) \
    if (!(x)) { \
        std::cerr << "Assert failed: " << #x << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
        exit(1); \
    }

#ifdef DEBUG
#define MINI_DEBUG_LOG(msg) \
    std::cout << "[DEBUG " << __FILE__ << ":" << __LINE__ << "] " << msg << std::endl
#else
#define MINI_DEBUG_LOG(msg)
#endif

int main() {
    std::cout << "PI = " << PI << std::endl;

    std::cout << "SUM(5, 3) = " << SUM(5, 3) << std::endl;

    std::cout << "MULT_BAD(2 + 3, 4) = " << MULT_BAD(2 + 3, 4) << std::endl;
    std::cout << "MULT_GOOD(2 + 3, 4) = " << MULT_GOOD(2 + 3, 4) << std::endl;
