#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <CLI/CLI.hpp>

#include "NGramMarkov.hpp"
#include "TextChain.hpp"

enum class ModelType {
  Markov,
  NGram
};

auto modelTypeTransformer = CLI::CheckedTransformer(
  std::map<std::string, ModelType>{
    {"markov", ModelType::Markov},
    {"ngram", ModelType::NGram}
  },
  CLI::ignore_case
);

CLI::App app{"CLI tool to train TextChain Markov models"};

int main(int argc, char *argv[]) {
  auto modelType = ModelType::NGram;
  int contextSize = 2;
  std::string inputFile = "input.txt";
  std::string outputFile = "output.bin";
  std::string gexfFile;

  app.add_option("-m,--model", modelType, "Model type")->transform(modelTypeTransformer);
  app.add_option("-c,--context", contextSize, "Context size for NGram model");
  app.add_option("-i,--input", inputFile, "Input text file");
  app.add_option("-o,--output", outputFile, "Output binary model");
  app.add_option("-g,--gexf", gexfFile, "Optional GEXF output");

  CLI11_PARSE(app, argc, argv);

  Markov *markov = nullptr;

  switch (modelType) {
    case ModelType::Markov:
      markov = new Markov;
      break;

    case ModelType::NGram:
      markov = new NGramMarkov(contextSize);
      break;
  }

  // ReSharper disable once CppDFANullDereference
  TextChain chain(*markov);

  try {
    std::ifstream in(inputFile);
    if (!in.is_open()) {
      throw std::runtime_error("Cannot open input file: " + inputFile);
    }

    std::string line;
    std::vector<std::string> data;
    while (std::getline(in, line)) {
      if (!line.empty()) data.push_back(std::move(line));
    }
    chain.train(data);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) {
      throw std::runtime_error("Cannot open output file: " + outputFile);
    }
    markov->serializeToOstream(out);

    if (!gexfFile.empty()) {
      std::ofstream gexfOut(gexfFile);
      if (!gexfOut.is_open()) {
        throw std::runtime_error("Cannot open GEXF file: " + gexfFile);
      }
      gexfOut << markov->toGEXF();
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
