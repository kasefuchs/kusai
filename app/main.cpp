#include <CLI/CLI.hpp>
#include <string>

#include "commands/RootCommand.hpp"

int main(const int argc, char *argv[]) {
  CLI::App app{"CLI tool for TextChain Markov models"};

  return RootCommand(app).main(argc, argv);
}
