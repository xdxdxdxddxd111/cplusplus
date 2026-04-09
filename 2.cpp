#include <iostream>
#include <chrono>

#define PI 3.1415926535
std::cout << "PI = " << PI << std::endl;

#define SUM(a, b) ((a) + (b))
std::cout << "SUM(5, 3) = " << SUM(5, 3) << std::endl;

#define MULT_BAD(a, b) a * b
std::cout << "MULT_BAD(2 + 3, 4) = " << MULT_BAD(2 + 3, 4) << std::endl; // 2 + 3 * 4 = 14
#define MULT_GOOD(a, b) ((a) * (b))
std::cout << "MULT_GOOD(2 + 3, 4) = " << MULT_GOOD(2 + 3, 4) << std::endl; // (2 + 3) * 4 = 20

#define SQUARE(x) ((x) * (x))
std::cout << "SQUARE(5) = " << SQUARE(5) << std::endl;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
std::cout << "MIN(10, 7) = " << MIN(10, 7) << std::endl;

#define DEBUG
#ifdef DEBUG
#define DEBUG_LOG(x) std::cout << "[DEBUG] " << x << std::endl
#else
#define DEBUG_LOG(x)
#endif
DEBUG_LOG("Debug message");

#ifdef DEBUG
std::cout << "Debug mode ON" << std::endl;
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

#define LOG(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl
LOG("Test log message");

#define PRINT(x) std::cout << #x << " = " << (x) << std::endl
int testVar = 42;
PRINT(testVar);

#define VAR_NAME(prefix, num) prefix##num
int VAR_NAME(var_, 1) = 100;
int VAR_NAME(var_, 2) = 200;
int VAR_NAME(var_, 3) = 300;
std::cout << var_1 << " " << var_2 << " " << var_3 << std::endl;

#define STRINGIFY(x) #x
std::cout << STRINGIFY(Hello World) << std::endl;

#define CHECK(x) if (!(x)) std::cerr << "CHECK failed: " << #x << " at " << __FILE__ << ":" << __LINE__ << std::endl
CHECK(5 > 3);
CHECK(2 > 10);

#define SAFE_DELETE(ptr) do { delete ptr; ptr = nullptr; } while(0)
int* ptr = new int(42);
SAFE_DELETE(ptr);

#define TIMER_START auto start = std::chrono::high_resolution_clock::now()
#define TIMER_END auto end = std::chrono::high_resolution_clock::now(); \
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); \
    std::cout << "Time: " << duration.count() << " ms" << std::endl
TIMER_START;
// какой‑то код
TIMER_END;

#define CHECK_PTR(p) if (!p) { std::cerr << "Null pointer at " << __FILE__ << ":" << __LINE__ << std::endl; return; }
int* nullPtr = nullptr;
CHECK_PTR(nullPtr);

#define SIMPLE_ASSERT(x) if (!(x)) { std::cerr << "Assert failed: " << #x << " at " << __FILE__ << ":" << __LINE__ << std::endl; exit(1); }
SIMPLE_ASSERT(1 == 1);
SIMPLE_ASSERT(1 == 2);

#ifdef DEBUG
#define DEBUG_LOG(msg) std::cout << "[DEBUG " << __FILE__ << ":" << __LINE__ << "] " << msg << std::endl
#else
#define DEBUG_LOG(msg)
#endif
DEBUG_LOG("Debug system test");
