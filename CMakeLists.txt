
cmake_minimum_required(VERSION 3.6)

project(Oblibiate)

set(SOURCE_MAIN 
    "src/test/MyAllocate.h"
    "src/test/StackAlloc.h"
    "src/MemoryPool.h"
    "src/MemoryPool.cpp"
    "src/MemoryChunk.h"
    "src/MemoryChunk.cpp"
    "src/main.cpp"
)

set(SOURCE 
    ${SOURCE_MAIN}
)

add_executable(Oblibiate ${SOURCE})


include_directories(src)
