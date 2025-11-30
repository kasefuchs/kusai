add_library(idgen
  IdGenerator.cpp
  IdGenerator.hpp
)

target_include_directories(idgen
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(idgen
  PUBLIC proto
)
