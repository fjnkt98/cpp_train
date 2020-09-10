#include <iostream>
#include <thread>
#include <chrono>

int main() {

  std::cout << "This is a loop dummy program!" << std::endl;

  int i = 0;

  while (true) {
    std::cout << "Loop count: " << i << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    i++;
  }
}