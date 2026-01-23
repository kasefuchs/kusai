#include "RootCommand.hpp"

#include <CLI/CLI.hpp>

#include "RunCommand.hpp"
#include "ServeCommand.hpp"
#include "TrainCommand.hpp"

RootCommand::RootCommand(CLI::App &app) : AbstractCommand(app) {
  commands_.push_back(std::make_unique<RunCommand>(app));
  commands_.push_back(std::make_unique<ServeCommand>(app));
  commands_.push_back(std::make_unique<TrainCommand>(app));
}

int RootCommand::main(const int argc, char *argv[]) {
  CLI11_PARSE(app, argc, argv);

  try {
    execute();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::flush;
    return 1;
  }

  return 0;
}

void RootCommand::execute() {
  for (const auto &cmd : commands_) {
    if (const auto it = cmd->run(); it) {
      return;
    }
  }

  std::cerr << app.help() << std::flush;
}
