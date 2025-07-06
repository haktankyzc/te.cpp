#include "timer.hpp"
#include <chrono>
#include <iostream>

MyTimer::MyTimer() : running(false), interval(1000) {}

MyTimer::~MyTimer() { stop(); }

void MyTimer::start(int intervalMs) {
  interval = intervalMs;
  if (running)
    return;

  running = true;
  worker = std::thread([this]() {
    std::unique_lock<std::mutex> lock(mutex);
    while (running) {
      if (cv.wait_for(lock, std::chrono::milliseconds(interval)) ==
          std::cv_status::timeout) {
        if (callback)
          callback();
        else {
          std::cerr << "There is no callback for timer" << std::endl;
          running = false;
        }
      }
    }
  });
}

void MyTimer::stop() {
  if (!running)
    return;

  {
    std::lock_guard<std::mutex> lock(mutex);
    running = false;
  }
  cv.notify_all();
  if (worker.joinable())
    worker.join();
}

void MyTimer::setCallback(std::function<void()> cb) {
  callback = std::move(cb);
}
