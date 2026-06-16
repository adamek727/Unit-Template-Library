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

## CMake with FetchContent

```cmake
include(FetchContent)
FetchContent_Declare(utl
        GIT_REPOSITORY https://github.com/adamek727/Unit-Template-Library
        GIT_TAG v3.0.0)
FetchContent_MakeAvailable(utl)
target_link_libraries(your_target utl::utl)
```

## Conan

A header-only recipe ships in `conanfile.py`. Until the package is on Conan
Center, export it locally with `conan create .`, then depend on
`unit-template-library/3.0.0` and link `utl::utl`.

## vcpkg

An overlay port lives in `packaging/vcpkg/ports`:

```bash
vcpkg install unit-template-library --overlay-ports=packaging/vcpkg/ports
```

In every case the imported CMake target is `utl::utl`.

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
