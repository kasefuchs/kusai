#include "AbstractCommand.hpp"

void AbstractCommand::run() {
  if (cmd_ && *cmd_)
    execute();
}
