#include "TrainCommand.hpp"

#include <fstream>
#include <ios>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "CLI/CLI.hpp"
#include "kusai/graph/MemoryGraph.hpp"
#include "kusai/tokenizer/SimpleTokenizer.hpp"
#include "kusai/textchain/TextChain.hpp"
#include "commands/AbstractCommand.hpp"
#include "helpers/model.hpp"

TrainCommand::TrainCommand(CLI::App& app) : AbstractCommand(app) {
  cmd_ = app.add_subcommand("train", "Train model");

  cmd_->add_option("-i,--input", inputFile_, "Input text file")->required();
  cmd_->add_option("-o,--output", outputFile_, "Output binary model");
  cmd_->add_option("-s,--size", contextSize_, "Context size")->required();
  cmd_->add_option("-m,--model", modelType_, "Model type")->transform(modelTypeTransformer());
}

void TrainCommand::execute() {
  MemoryGraph graph;
  auto markov = makeModel(modelType_, graph, contextSize_);

  std::ifstream in(inputFile_);
  if (!in.is_open()) {
    throw std::runtime_error("Cannot open input file: " + inputFile_);
  }

  std::vector<std::string> data;
  std::string line;

  while (std::getline(in, line)) {
    if (!line.empty()) data.push_back(std::move(line));
  }

  SimpleTokenizer tokenizer;
  TextChain chain(*markov, tokenizer);
  chain.train(data);

  std::ofstream out(outputFile_, std::ios::binary);
  if (!out.is_open()) {
    throw std::runtime_error("Cannot open output file: " + outputFile_);
  }

  chain.serializeToOstream(out);
}
