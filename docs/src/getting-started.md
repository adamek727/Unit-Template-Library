# Getting Started

UTL requires a C++17 compiler. There are no runtime dependencies; the tests
use GoogleTest.

## CMake with find_package

Install the library once:

```bash
git clone https://github.com/adamek727/Unit-Template-Library
cd Unit-Template-Library
cmake -B build
cmake --install build
```

Then in your project:

```cmake
find_package(utl REQUIRED)
target_link_libraries(your_target utl::utl)
```

## CMake with add_subdirectory

Add the repository as a git submodule:

```bash
git submodule add https://github.com/adamek727/Unit-Template-Library libs/utl
```

And in your `CMakeLists.txt`:

```cmake
add_subdirectory(libs/utl)
target_link_libraries(your_target utl::utl)
```

## Include the headers

```cpp
#include <utl/utl.hpp>
```

## Building the examples and tests

```bash
git clone https://github.com/adamek727/Unit-Template-Library
cd Unit-Template-Library
cmake -B build -DENABLE_TESTS=1 -DENABLE_EXAMPLES=1
cmake --build build -j
ctest --test-dir build
./build/examples/usage_example
```
