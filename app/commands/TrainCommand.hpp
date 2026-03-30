#pragma once

#include "AbstractCommand.hpp"
#include "helpers/model.hpp"

namespace kusai::app {
class TrainCommand : public AbstractCommand {
 public:
  explicit TrainCommand(CLI::App& app);

 protected:
  void execute() override;

 private:
  ModelType modelType_ = ModelType::Backoff;
  std::string inputFile_ = "input.txt";
  std::string outputFile_ = "model.json";
  int contextSize_ = 1;
};
}  // namespace kusai::app
