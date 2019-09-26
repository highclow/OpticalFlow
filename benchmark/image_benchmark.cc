#include <benchmark/benchmark.h>
#include "image.h"

static void BM_IMAGE(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    DImage im;
    im.generate2DGaussian(5, 0.5);
    DImage im2(im);
  }
}
// Register the function as a benchmark
BENCHMARK(BM_IMAGE);
// Run the benchmark
BENCHMARK_MAIN();
