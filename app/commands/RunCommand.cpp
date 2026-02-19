#include "RunCommand.hpp"

#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>
#include <stdexcept>

#include "CLI/CLI.hpp"
#include "kusai/graph/MemoryGraph.hpp"
#include "kusai/tokenizer/SimpleTokenizer.hpp"
#include "kusai/textchain/TextChain.hpp"
#include "commands/AbstractCommand.hpp"
#include "helpers/model.hpp"

RunCommand::RunCommand(CLI::App& app) : AbstractCommand(app) {
  cmd_ = app.add_subcommand("run", "Run text generation");

  cmd_->add_option("-i,--input", inputFile_, "Input binary model");
  cmd_->add_option("-c,--context", context_, "Generation context")->required();
  cmd_->add_option("-l,--limit", limit_, "Limit of returned tokens");
  cmd_->add_option("-m,--model", modelType_, "Model type")->transform(modelTypeTransformer());
}

void RunCommand::execute() {
  MemoryGraph graph;
  auto markov = makeModel(modelType_, graph);

  std::ifstream in(inputFile_, std::ios::binary);
  if (!in.is_open()) {
    throw std::runtime_error("Cannot open input file: " + inputFile_);
  }

  SimpleTokenizer tokenizer;
  TextChain chain(*markov, tokenizer);
  chain.deserializeFromIstream(in);

  std::cout << chain.generateTokens(context_, limit_) << std::endl;
}
