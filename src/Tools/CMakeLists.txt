include_directories("../graphics")
include_directories("../ThirdParty")
include_directories(${ASSIMP_INCLUDE_DIRS})
set(TOOLS_H
FileReader.h)

set(TOOLS_SRC
FileReader.cpp)

add_library(tools ${TOOLS_H} ${TOOLS_SRC})
target_link_libraries(tools graphics)
