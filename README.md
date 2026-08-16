# Kusai

## Building

```bash
git clone https://codeberg.org/kasefuchs/kusai.git
mkdir cmake-build && cd cmake-build
cmake ..
cmake --build .
```

Install to system with

```bash
cmake --build . --target install
```

## Using

### CMake

```cmake
find_package(kusai REQUIRED)
target_link_libraries(<your-target> kusai::textchain)
```

Or FetchContent version

```cmake
include(FetchContent)
FetchContent_Declare(kusai
    GIT_REPOSITORY https://codeberg.org/kasefuchs/kusai.git
    GIT_TAG <tag>
)
FetchContent_MakeAvailable(kusai)
target_link_libraries(<your-target> kusai::textchain)
```

### Hello World

```cpp
#include <kusai/graph/MemoryGraph.hpp>
#include <kusai/markov/SimpleMarkov.hpp>
#include <kusai/tokenizer/SimpleTokenizer.hpp>
#include <kusai/textchain/TextChain.hpp>

int main() {
  const auto graph = std::make_shared<kusai::MemoryGraph>();
  const auto markov = std::make_shared<kusai::SimpleMarkov>(graph);
  const auto tokenizer = std::make_shared<kusai::SimpleTokenizer>();
  const auto chain = std::make_shared<kusai::TextChain>(markov, tokenizer);

  chain->train({
    "wur a fox",
    "fox the chorni"
  });

  std::cout << chain->generateText("wur") << std::endl;

  chain->serializeToOstream(std::cout);

  return 0;
}
```
