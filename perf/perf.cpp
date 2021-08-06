#include <benchmark/benchmark.h>
#include <cmath>
#include <cstring>
#include <random>
#include "common/math/hilbert.h"

static void BM_Hilbert2D(benchmark::State& state) {
  std::random_device                     r;
  std::default_random_engine             e1(r());
  std::uniform_real_distribution<double> uniform_dist(0, 1);

  //todo: use circular container
  static constexpr int64_t no_randnum = 1000;
  std::vector<double> randnums(no_randnum);
  for(int64_t i =0; i < no_randnum; ++i){
    randnums[i] = uniform_dist(e1);
  }

  int64_t i = 0;
  for(auto _ : state) {
    VectorD<2> quadrant1 = {randnums[i++], randnums[i++]}; // only relevant at hilbertLevel = 1
    hilbert::index<2>(quadrant1, state.range(0)); //linear behaviour -> level * 1.1 ns (GNU10) 3.4 ns (clang10)
    if(i == 990){
      i = 0;
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_Hilbert2D)->DenseRange(1, 10, 1);

static void BM_Hilbert3D(benchmark::State& state) {
  std::random_device                     r;
  std::default_random_engine             e1(r());
  std::uniform_real_distribution<double> uniform_dist(0, 1);

  //todo: use circular container
  static constexpr int64_t no_randnum = 1000;
  std::vector<double> randnums(no_randnum);
  for(int64_t i =0; i < no_randnum; ++i){
    randnums[i] = uniform_dist(e1);
  }


  int64_t i = 0;
  for(auto _ : state) {
    VectorD<3> quadrant1 = {randnums[i++], randnums[i++], randnums[i++]}; // only relevant at hilbertLevel = 1
    hilbert::index<3>(quadrant1, state.range(0)); //linear behaviour -> level * 1.9 ns(GNU10) 4ns (clang10)
    if(i == 990){
      i = 0;
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_Hilbert3D)->DenseRange(1, 10, 1);

// example
static void BM_memcpy(benchmark::State& state) {
  char* src = new char[state.range(0)];
  char* dst = new char[state.range(0)];
  memset(src, 'x', state.range(0));
  for(auto _ : state)
    memcpy(dst, src, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(state.range(0)));
  delete[] src;
  delete[] dst;
}
BENCHMARK(BM_memcpy)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(8 << 10);

BENCHMARK_MAIN();