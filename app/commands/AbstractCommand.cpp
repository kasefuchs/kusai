#include "AbstractCommand.hpp"

bool AbstractCommand::run() {
  if (cmd_ && *cmd_) {
    execute();

    return true;
  }

  return false;
}
