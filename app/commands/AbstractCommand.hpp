#pragma once

#include <CLI/App.hpp>

class AbstractCommand {
public:
  CLI::App &app;

  virtual ~AbstractCommand() = default;

  virtual bool run();

protected:
  CLI::App *cmd_ = nullptr;

  explicit AbstractCommand(CLI::App &app) : app(app) {}

  virtual void execute() = 0;
};
