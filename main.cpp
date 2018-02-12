#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

#include <benchmark/benchmark.h>

static const int minimumSize = 1 << 10;
static const int maximumSize = 1 << 24;

struct Point {
  int x;
  int y;
  int z;

  bool operator<(const Point &rhs) const {
    if (x < rhs.x) {
      return true;
    }
    if (rhs.x < x) {
      return false;
    }
    if (y < rhs.y) {
      return true;
    }
    if (rhs.y < y) {
      return false;
    }
    return z < rhs.z;
  }

  bool operator==(const Point &rhs) const {
    return x == rhs.x && y == rhs.y && z == rhs.z;
  }

  bool operator!=(const Point &rhs) const { return !(rhs == *this); }
};

static void sortReversed(benchmark::State &state) {
  const auto size = static_cast<size_t>(state.range(0));
  for (auto _ : state) {
    std::vector<Point> v(size);
    for (std::size_t i = 0; i < size; i++) {
      v[i].x = rand();
      v[i].y = rand();
      v[i].z = rand();
    }
    std::sort(std::rbegin(v), std::rend(v));
  }
};
BENCHMARK(sortReversed)->RangeMultiplier(2)->Range(minimumSize, maximumSize);

static void sortThenReverse(benchmark::State &state) {
  const auto size = static_cast<size_t>(state.range(0));
  for (auto _ : state) {
    std::vector<Point> v(size);
    for (std::size_t i = 0; i < size; i++) {
      v[i].x = rand();
      v[i].y = rand();
      v[i].z = rand();
    }
    std::sort(std::begin(v), std::end(v));
    std::reverse(std::begin(v), std::end(v));
  }
}
BENCHMARK(sortThenReverse)->RangeMultiplier(2)->Range(minimumSize, maximumSize);

static void sortWithGeneratedComparator(benchmark::State &state) {
  const auto size = static_cast<size_t>(state.range(0));
  for (auto _ : state) {
    std::vector<Point> v(size);
    for (std::size_t i = 0; i < size; i++) {
      v[i].x = rand();
      v[i].y = rand();
      v[i].z = rand();
    }
    std::sort(std::begin(v), std::end(v), [](const auto &lhs, const auto &rhs) {
      return rhs < lhs && lhs != rhs;
    });
  }
}
BENCHMARK(sortWithGeneratedComparator)
    ->RangeMultiplier(2)
    ->Range(minimumSize, maximumSize);

BENCHMARK_MAIN();
