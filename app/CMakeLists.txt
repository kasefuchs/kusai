add_executable(${PROJECT_NAME}
  main.cpp
  commands/AbstractCommand.cpp
  commands/AbstractCommand.hpp
  commands/RunCommand.cpp
  commands/RunCommand.hpp
  commands/ServeCommand.cpp
  commands/ServeCommand.hpp
  commands/TrainCommand.cpp
  commands/TrainCommand.hpp
  commands/RootCommand.cpp
  commands/RootCommand.hpp
  helpers/model.hpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE service
  PRIVATE textchain
  PRIVATE CLI11::CLI11
)
