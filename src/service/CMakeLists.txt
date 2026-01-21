add_library(service SHARED
  TextChainService.cpp
  TextChainService.hpp
)

target_include_directories(service
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(service
  PUBLIC proto
  PUBLIC graph
  PUBLIC markov
  PUBLIC textchain
)

install(TARGETS service
  LIBRARY DESTINATION lib
)
