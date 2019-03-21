#include <benchmark/benchmark.h>
#include <functional>
#include <iostream>

extern "C" {
#include "closing.h"
}

#define DO_STR(X) # X
#define STR(X) DO_STR(X)


class BMBase : public benchmark::Fixture
{
public:
  BMBase()
    {
      const char* filename = STR(IMAGE_PATH);
      input = load_image(filename);
      if (input == NULL)
      {
        std::cerr << "Impossible de charger l'image de test: " << filename << "\n";
        std::abort();
      }
    }

  ~BMBase()
    {
      destroy_image(input);
    }

  void exec(benchmark::State& st, std::function<image2d*(const image2d*, int)> foo)
    {
      int N = st.range(0);
      for (auto _ : st)
      {
        image2d* output = foo(input, N);
        destroy_image(output);
      }
    }

  image2d* input;
};

BENCHMARK_DEFINE_F(BMBase, V1)(benchmark::State &st) { this->exec(st, closing_1); }
BENCHMARK_DEFINE_F(BMBase, V2)(benchmark::State &st) { this->exec(st, closing_2); }
BENCHMARK_DEFINE_F(BMBase, V3)(benchmark::State &st) { this->exec(st, closing_3); }

BENCHMARK_REGISTER_F(BMBase, V1)->Arg(3)->Arg(11)->Arg(51)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(BMBase, V2)->Arg(3)->Arg(11)->Arg(51)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(BMBase, V3)->Arg(3)->Arg(11)->Arg(51)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
