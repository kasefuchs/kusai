#pragma once

#include "AbstractCommand.hpp"
#include "helpers/model.hpp"

class TrainCommand : public AbstractCommand {
public:
  explicit TrainCommand(CLI::App &app);

protected:
  void execute() override;

private:
  ModelType modelType_ = ModelType::Backoff;
  std::string inputFile_;
  std::string outputFile_ = "output.bin";
  std::string gexfFile_;
  int contextSize_ = 1;
};
