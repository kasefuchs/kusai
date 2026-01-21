#pragma once

#include "AbstractCommand.hpp"
#include "helpers/model.hpp"

class RunCommand : public AbstractCommand {
public:
  explicit RunCommand(CLI::App &app);

protected:
  void execute() override;

private:
  ModelType modelType_ = ModelType::Backoff;
  std::string inputFile_;
  std::string context_;
  int limit_ = INT32_MAX;
  int contextSize_ = 1;
};
