#include "ServeCommand.hpp"

#include <absl/log/log.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/server_credentials.h>

#include <fstream>
#include <ios>
#include <stdexcept>

#include "CLI/CLI.hpp"
#include "MemoryGraph.hpp"
#include "TextChain.hpp"
#include "TextChainService.hpp"
#include "commands/AbstractCommand.hpp"
#include "helpers/model.hpp"

ServeCommand::ServeCommand(CLI::App& app) : AbstractCommand(app) {
  cmd_ = app.add_subcommand("serve", "Run gRPC server");

  cmd_->add_option("-b,--bind", bindAddr_, "The address to bind to");
  cmd_->add_option("-i,--input", inputFile_, "Input binary model");
  cmd_->add_option("-m,--model", modelType_, "Model type")->transform(modelTypeTransformer());
}

void ServeCommand::execute() {
  MemoryGraph graph;
  auto markov = makeModel(modelType_, graph);

  std::ifstream in(inputFile_, std::ios::binary);
  if (!in.is_open()) {
    throw std::runtime_error("Cannot open input file: " + inputFile_);
  }

  markov->deserializeFromIstream(in);

  TextChain chain(*markov);

  TextChainService chainService(chain);

  grpc::ServerBuilder builder;
  builder.RegisterService(&chainService);
  builder.AddListeningPort(bindAddr_, grpc::InsecureServerCredentials());

  auto server = builder.BuildAndStart();
  LOG(INFO) << "Server listening on " << bindAddr_;
  server->Wait();
}
