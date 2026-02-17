#pragma once

#include "AbstractCommand.hpp"
#include "helpers/model.hpp"

class RunCommand : public AbstractCommand {
 public:
  explicit RunCommand(CLI::App& app);

 protected:
  void execute() override;

 private:
  ModelType modelType_ = ModelType::Backoff;
  std::string inputFile_ = "model.bin";
  std::string context_;
  int limit_ = INT8_MAX;
};
