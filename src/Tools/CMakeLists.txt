set(TOOLS_H
objectfileparser.h
materialfileparser.h)

set(TOOLS_SRC
objectfileparser.cpp
materialfileparser.cpp)

add_library(tools ${TOOLS_H} ${TOOLS_SRC})
target_link_libraries(tools graphics)

target_include_directories(tools PRIVATE ..)
