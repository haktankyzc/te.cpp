#ifndef TIMER_HPP
#define TIMER_HPP

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

class MyTimer {
public:
  MyTimer();
  ~MyTimer();

  void start(int intervalMs);
  void stop();
  void setCallback(std::function<void()> cb);

private:
  std::thread worker;
  std::atomic<bool> running;
  std::mutex mutex;
  std::condition_variable cv;
  int interval;
  std::function<void()> callback;
};

#endif
