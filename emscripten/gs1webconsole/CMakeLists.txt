set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_FUNCTIONS=\"['_eval_string', '_free_string']\"")

add_executable(gs1webconsole Main.cpp
        GOutputLibrary.hpp GFlagLibrary.hpp GStringLibrary.hpp)

target_link_libraries(gs1webconsole gs1common gs1parse gs1compiler gs1vm)