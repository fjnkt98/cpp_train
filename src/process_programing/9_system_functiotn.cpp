#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
  std::system("./dummy_loop.out");

  std::this_thread::sleep_for(std::chrono::seconds(5));

  return 0;
}