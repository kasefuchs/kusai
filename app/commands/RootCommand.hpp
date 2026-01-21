#pragma once

#include "AbstractCommand.hpp"
#include "RunCommand.hpp"
#include "ServeCommand.hpp"
#include "TrainCommand.hpp"

class RootCommand : public AbstractCommand {
public:
  explicit RootCommand(CLI::App &app);

  int main(int argc, char *argv[]);

protected:
  void execute() override;

private:
  RunCommand runCommand_;
  ServeCommand serveCommand_;
  TrainCommand trainCommand_;
};
