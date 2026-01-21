#pragma once

#include "AbstractCommand.hpp"
#include "RunCommand.hpp"
#include "TrainCommand.hpp"

class RootCommand : public AbstractCommand {
public:
  explicit RootCommand(CLI::App &app);

  int main(int argc, char *argv[]);

protected:
  void execute() override;

private:
  RunCommand runCommand_;
  TrainCommand trainCommand_;
};
