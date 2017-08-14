#include <iostream>
#include <thread>
#include <future>
#include <windows.h>

using namespace std::chrono;

void fun1(std::promise<int> px){
    int y=5;
    try {
        px.set_value(y);
    } catch(...){
        px.set_exception(std::current_exception());
    }
}

void fun2(std::future<int> fx){
    std::cout<< "Czekam" << std::endl;
    try{
        int x = fx.get();
        std::cout << "Otrzymałem: " << x << std::endl;
    } catch(...){
        std::cout << "Błąd" << std::endl;
    }
}

void timeMeter(){
    auto time = steady_clock::now();
    while(true){
        if(duration_cast<seconds>(steady_clock::now()-time).count()>30){
            std::cout << "peek" << std::endl;
            time = steady_clock::now();
        }
    }
}
void lunchBreak(int duration = 30){
    std::this_thread::sleep_for((std::chrono::seconds(duration*60)));
}
void breakClock() {
    while(TRUE){
        std::this_thread::sleep_for(std::chrono::seconds(50*60));
        {
            std::cout << "in\a" << std::endl;
            MessageBox(nullptr, "Czas na przerwe!", "Uwaga, uwaga!!!", MB_OK);
        }
        std::this_thread::sleep_for(std::chrono::seconds(10*60));//to rm
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::promise<int> px;
    std::future<int> fx = px.get_future();
    HWND okno = GetConsoleWindow();
   ShowWindow( okno, SW_HIDE );

    std::thread thirtySek{timeMeter};
    std::thread breakThread{breakClock};

    thirtySek.join();
    breakThread.join();
//    auto time0 = high_resolution_clock::now();
//    std::thread t1{fun1, std::move(px)};
//    std::thread t2{fun2, std::move(fx)};
//    t1.join();
//    t2.join();
    ShowWindow( okno, SW_SHOW );
//    auto time1 = high_resolution_clock::now();
//    std::cout << duration_cast<seconds>(time1-time0).count() << "s" << std::endl;
    std::cin.get();
    std::cin.get();
    return 0;
}
