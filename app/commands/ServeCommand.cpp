#include <grpcpp/grpcpp.h>

#include "ServeCommand.hpp"

#include "TextChain.hpp"
#include "TextChainService.hpp"

ServeCommand::ServeCommand(CLI::App &app) : AbstractCommand(app) {
  cmd_ = app.add_subcommand("serve", "Run gRPC server");

  cmd_->add_option("-b,--bind", bindAddr_, "The address to bind to");
  cmd_->add_option("-i,--input", inputFile_, "Input binary model")->required();
  cmd_->add_option("-m,--model", modelType_, "Model type")->transform(modelTypeTransformer());
}

void ServeCommand::execute() {
  Graph graph;
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
  builder.BuildAndStart()->Wait();
}
