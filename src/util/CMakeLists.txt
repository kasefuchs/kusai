add_library(util INTERFACE
  hash.hpp
)

target_include_directories(util
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
