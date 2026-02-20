add_executable(kusai
  main.cpp
  commands/AbstractCommand.cpp
  commands/AbstractCommand.hpp
  commands/RunCommand.cpp
  commands/RunCommand.hpp
  commands/TrainCommand.cpp
  commands/TrainCommand.hpp
  commands/RootCommand.cpp
  commands/RootCommand.hpp
  helpers/model.hpp
)

target_include_directories(kusai
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(kusai
  PRIVATE textchain
  PRIVATE CLI11::CLI11
)
