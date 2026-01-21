#include "RunCommand.hpp"

#include "Graph.hpp"
#include "TextChain.hpp"

RunCommand::RunCommand(CLI::App &app) : AbstractCommand(app) {
  cmd_ = app.add_subcommand("run", "Run text generation");

  cmd_->add_option("-i,--input", inputFile_, "Input binary model")->required();
  cmd_->add_option("-c,--context", context_, "Generation context")->required();
  cmd_->add_option("-l,--limit", limit_, "Limit of returned tokens");
  cmd_->add_option("-s,--size", contextSize_, "Context size");
  cmd_->add_option("-m,--model", modelType_, "Model type")->transform(modelTypeTransformer());
}

void RunCommand::execute() {
  Graph graph;
  auto markov = makeModel(modelType_, graph, contextSize_);

  std::ifstream in(inputFile_, std::ios::binary);
  if (!in.is_open()) {
    throw std::runtime_error("Cannot open input file: " + inputFile_);
  }

  markov->deserializeFromIstream(in);

  TextChain chain(*markov);

  std::cout << chain.generateTokens(context_, limit_) << std::endl;
}
