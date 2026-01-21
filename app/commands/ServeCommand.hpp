#pragma once

#include "AbstractCommand.hpp"
#include "helpers/model.hpp"

class ServeCommand : public AbstractCommand {
public:
  explicit ServeCommand(CLI::App &app);

protected:
  void execute() override;

private:
  ModelType modelType_ = ModelType::Backoff;
  std::string bindAddr_ = "127.0.0.1:9080";
  std::string inputFile_ = "model.bin";
};
