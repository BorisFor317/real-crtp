#include "crtp.hpp"
#include "normal.hpp"
#include <chrono>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

template <typename T, typename S>
std::size_t benchmark(T &object, S function, const std::string &name) {
  auto start = std::chrono::high_resolution_clock::now();
  std::size_t result = function(&object);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = stop - start;
  std::cout << name << " duration:\t " << duration.count() << "\n";
  std::cout << name << " result:  \t " << object.GetValue() << "\n";

  return duration.count();
}

const std::size_t N = 40000;

std::size_t runNormal(INormalCounter *object) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < i; ++j) {
      object->Count(j);
    }
  }

  return object->GetValue();
}

template <typename T> std::size_t runCRTP(ICrtpCounter<T> *object) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < i; ++j) {
      object->Count(j);
    }
  }

  return object->GetValue();
}

int main(int argc, char *argv[]) {
  NormalCounter normal(0);
  auto normalDuration = benchmark(normal, runNormal, "norm");

  CrtpCounter crtp(0);
  auto crtpDuration = benchmark(crtp, runCRTP<CrtpCounter>, "crtp");

  auto boost = (double)normalDuration / (double)crtpDuration;
  std::cout << "boost: " << boost << std::endl;

  return 0;
}
