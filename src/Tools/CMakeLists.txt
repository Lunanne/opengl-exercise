include_directories(../Global/)
set(TOOLS_H
objectfileparser.h
structs.h)

set(TOOLS_SRC
objectfileparser.cpp)

add_library(tools ${TOOLS_H} ${TOOLS_SRC})
target_link_libraries(tools graphics)
