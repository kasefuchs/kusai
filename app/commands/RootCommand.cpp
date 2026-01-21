#include "RootCommand.hpp"
#include <CLI/CLI.hpp>

RootCommand::RootCommand(CLI::App &app) : AbstractCommand(app), runCommand_(app), trainCommand_(app) {}

int RootCommand::main(const int argc, char *argv[]) {
  CLI11_PARSE(app, argc, argv);

  try {
    execute();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}

void RootCommand::execute() {
  runCommand_.run();
  trainCommand_.run();
}
