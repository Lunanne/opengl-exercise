include_directories(../Global/)
message(${Boost_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
set(TOOLS_H
objectfileparser.h)

set(TOOLS_SRC
objectfileparser.cpp)

add_library(tools ${TOOLS_H} ${TOOLS_SRC})