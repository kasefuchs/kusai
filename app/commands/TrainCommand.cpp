#include "TrainCommand.hpp"

#include "Graph.hpp"
#include "TextChain.hpp"

#include <fstream>
#include <stdexcept>
#include <vector>

TrainCommand::TrainCommand(CLI::App &app) : AbstractCommand(app) {
  cmd_ = app.add_subcommand("train", "Train model");

  cmd_->add_option("-i,--input", inputFile_, "Input text file")->required();
  cmd_->add_option("-o,--output", outputFile_, "Output binary model");
  cmd_->add_option("-g,--gexf", gexfFile_, "Output graph in GEXF format");
  cmd_->add_option("-s,--size", contextSize_, "Context size")->required();
  cmd_->add_option("-m,--model", modelType_, "Model type")->transform(modelTypeTransformer());
}

void TrainCommand::execute() {
  Graph graph;
  auto markov = makeModel(modelType_, graph, contextSize_);

  std::ifstream in(inputFile_);
  if (!in.is_open()) {
    throw std::runtime_error("Cannot open input file: " + inputFile_);
  }

  std::vector<std::string> data;
  std::string line;

  while (std::getline(in, line)) {
    if (!line.empty())
      data.push_back(std::move(line));
  }

  TextChain chain(*markov);
  chain.train(data);

  std::ofstream out(outputFile_, std::ios::binary);
  if (!out.is_open()) {
    throw std::runtime_error("Cannot open output file: " + outputFile_);
  }

  markov->serializeToOstream(out);

  if (!gexfFile_.empty()) {
    std::ofstream gexfOut(gexfFile_);
    if (!gexfOut.is_open()) {
      throw std::runtime_error("Cannot open GEXF file: " + gexfFile_);
    }

    gexfOut << graph.toGEXF();
  }
}
