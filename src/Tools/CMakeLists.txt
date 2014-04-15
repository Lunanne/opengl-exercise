include_directories("../graphics")

set(TOOLS_H
objectfileparser.h
materialfileparser.h
FileReader.h)

set(TOOLS_SRC
objectfileparser.cpp
materialfileparser.cpp
FileReader.cpp)

add_library(tools ${TOOLS_H} ${TOOLS_SRC})
target_link_libraries(tools graphics)
