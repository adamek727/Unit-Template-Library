add_executable(usage_example usage_example.cpp)
target_link_libraries(usage_example utl::utl)
target_compile_options(usage_example PRIVATE $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>)
