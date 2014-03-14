include_directories(../Graphics/)

set(TOOLS_H
objectfileparser.h)

set(TOOLS_SRC
objectfileparser.cpp)

add_library(tools ${TOOLS_H} ${TOOLS_SRC})
target_link_libraries(tools graphics)
