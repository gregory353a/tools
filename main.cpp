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


int main() {
    std::cout << "Hello, World!" << std::endl;
    std::promise<int> px;
    std::future<int> fx = px.get_future();
    HWND okno = GetConsoleWindow();
    ShowWindow( okno, SW_HIDE );
    MessageBox(nullptr, "Goodbye, cruel world!", "Note", MB_OK);
    auto time0 = high_resolution_clock::now();
    std::thread t1{fun1, std::move(px)};
    std::thread t2{fun2, std::move(fx)};
    t1.join();
    t2.join();
    ShowWindow( okno, SW_SHOW );
    auto time1 = high_resolution_clock::now();
    std::cout << duration_cast<seconds>(time1-time0).count() << "s" << std::endl;
    std::cin.get();
    std::cin.get();
    return 0;
}