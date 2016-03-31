#include <iostream>

using namespace std;

#include <iostream>
#include <thread>
#include <deque>
#include <mutex>
#include <condition_variable>

using namespace std;

std::condition_variable cond;
std::mutex mu;
std::deque<int> q;


void Producer(void)
{
    cout << "Producer" << endl;
    auto count = 10;
    while(count > 0)
    {
        std::unique_lock<mutex> locker(mu);
        q.push_front(count);
        locker.unlock();
        cond.notify_one();
        count--;
    }
    return;
}


void Consumer(void)
{
    auto data = 0;
    cout << "Consumer" << endl;
    while(data != 1)
    {
        std::unique_lock<mutex> locker(mu);
        cond.wait(locker, [](){return !q.empty();});
        data = q.back();
        q.pop_back();
        cout << data << endl;
        locker.unlock();
    }
    return;
}


int main()
{
    cout << "Producer Consumer problem simulate" << endl;
    std::thread t1(&Producer) ;
    std::thread t2(&Consumer) ;
    t1.join();
    t2.join();
    cout << "Done" << endl;
    return 0;
}

