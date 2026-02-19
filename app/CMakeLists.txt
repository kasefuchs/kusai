add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
  PRIVATE
    main.cpp
    commands/RunCommand.cpp
    commands/AbstractCommand.cpp
    commands/TrainCommand.cpp
    commands/RootCommand.cpp
  PRIVATE
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ..
  FILES
    commands/AbstractCommand.hpp
    commands/RunCommand.hpp
    commands/TrainCommand.hpp
    commands/RootCommand.hpp
    helpers/model.hpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC textchain
  PUBLIC CLI11::CLI11
)
