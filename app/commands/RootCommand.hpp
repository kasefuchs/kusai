#pragma once

#include "AbstractCommand.hpp"

namespace kusai::app {
class RootCommand : public AbstractCommand {
 public:
  explicit RootCommand(CLI::App& app);

  int main(int argc, char* argv[]);

 protected:
  void execute() override;

 private:
  std::vector<std::unique_ptr<AbstractCommand>> commands_;
};
}  // namespace kusai::app
