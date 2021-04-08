#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

class MyTimer
{
public:
    MyTimer(){}

    void start()
    {
        start_point = high_resolution_clock::now();
    }

    void stop()
    {
        stop_point = high_resolution_clock::now();
    }

    double get_time()
    {
        return duration_cast<nanoseconds>(stop_point - start_point).count() / 1e9;
    }

private:
    high_resolution_clock::time_point start_point;
    high_resolution_clock::time_point stop_point;
};
