// mutex.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
/*
   기본적인 mutex의 사용을 알아보는 프로그램
   c++에서는 기본적인 mtx외에도 c++14에서 추가된 shared_timed_mutex c++ 17에 추가된 shared등 다양한 mutex들이 존재한다.
   각 뮤텍스별 동작법과 성능이 차이가있으니 알아보고 사용하는걸 추천한다.위에 기술한 shared 스레드의 경우 동시에 여러 스레드들이 접근이 가능하다.
   이 경우에 읽기작업이 빈번하게 일어나는 자원의 경우 읽기는 여러스레드들이 작업을 동시에 하고 쓰기작업은 한스레드만 수행하게 하는 것이다.


*/

#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx; // 뮤텍스 객체 생성


// 하나의 스레드가 작업을 다 수행하고 난 뒤에 다른 스레드가 접근을 원할시 mtx의 위치를 수정하면 된다.
void increment(int id, int &shared_count) {
    for (int i = 0; i < 10000; ++i) {
        mtx.lock(); // 뮤텍스 잠금
        //임계 영역
        std::cout << "실행중인 스레드 thread : "<<id<<" 카운트 : " << shared_count << '\n';
        shared_count++;

        mtx.unlock(); // 뮤텍스 해제
    }
}

int main() {
    int shared_count = 0;

    std::thread t1(increment,1,std::ref(shared_count));
    std::thread t2(increment,2,std::ref(shared_count));

    t1.join();
    t2.join();

    std::cout << "Final count: " << shared_count << std::endl;
    return 0;
}


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
