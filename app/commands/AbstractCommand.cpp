#include "AbstractCommand.hpp"

namespace kusai::app {
bool AbstractCommand::run() {
  if (cmd_ && *cmd_) {
    execute();

    return true;
  }

  return false;
}
}  // namespace kusai::app
