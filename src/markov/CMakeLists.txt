add_library(markov
  AbstractMarkov.cpp
  BackoffMarkov.cpp
  Markov.cpp
  NGramMarkov.cpp
)

target_sources(markov
  PUBLIC
    FILE_SET HEADERS
      TYPE HEADERS
      BASE_DIRS ${CMAKE_SOURCE_DIR}/include
      FILES
        ${CMAKE_SOURCE_DIR}/include/kusai/markov/AbstractMarkov.hpp
        ${CMAKE_SOURCE_DIR}/include/kusai/markov/BackoffMarkov.hpp
        ${CMAKE_SOURCE_DIR}/include/kusai/markov/Markov.hpp
        ${CMAKE_SOURCE_DIR}/include/kusai/markov/NGramMarkov.hpp
)

target_include_directories(markov
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_libraries(markov
  PUBLIC proto
  PUBLIC graph
  PUBLIC absl::log_internal_check_op
  PUBLIC xxHash::xxhash
)
