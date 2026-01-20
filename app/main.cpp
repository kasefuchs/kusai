#include <CLI/CLI.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "NGramMarkov.hpp"
#include "TextChain.hpp"

enum class ModelType { Markov, NGram };

auto modelTypeTransformer = CLI::CheckedTransformer(
    std::map<std::string, ModelType>{{"markov", ModelType::Markov}, {"ngram", ModelType::NGram}}, CLI::ignore_case);

int main(int argc, char *argv[]) {
  auto modelType = ModelType::NGram;
  std::string inputFile;
  std::string gexfFile;
  int contextSize = 1;

  CLI::App app{"CLI tool for TextChain Markov models"};
  app.add_option("-m,--model", modelType, "Model type")->transform(modelTypeTransformer);
  app.add_option("-g,--gexf", gexfFile, "Optional GEXF output");

  int limit;
  std::string context;

  auto runSubcommand = app.add_subcommand("run");
  runSubcommand->add_option("-i,--input", inputFile, "Input binary file")->required();
  runSubcommand->add_option("-c,--context", context, "Generation context")->required();
  runSubcommand->add_option("-l,--limit", limit, "Limit of returned tokens");

  std::string outputFile = "output.bin";

  auto trainSubcommand = app.add_subcommand("train");
  trainSubcommand->add_option("-i,--input", inputFile, "Input text file")->required();
  trainSubcommand->add_option("-o,--output", outputFile, "Output binary model");
  trainSubcommand->add_option("-s,--size", contextSize, "Context size of NGram model");

  CLI11_PARSE(app, argc, argv);

  Graph graph;
  AbstractMarkov *markov = nullptr;

  switch (modelType) {
  case ModelType::Markov:
    markov = new Markov(graph);
    break;

  case ModelType::NGram:
    markov = new NGramMarkov(graph, contextSize);
    break;
  }

  // ReSharper disable once CppDFANullDereference
  TextChain chain(*markov);

  try {
    std::ifstream in(inputFile);
    if (!in.is_open()) {
      throw std::runtime_error("Cannot open input file: " + inputFile);
    }

    if (*runSubcommand) {
      markov->deserializeFromIstream(in);

      std::cout << chain.generateTokens(context, limit) << std::endl;
    }

    if (*trainSubcommand) {
      std::string line;
      std::vector<std::string> data;
      while (std::getline(in, line)) {
        if (!line.empty())
          data.push_back(std::move(line));
      }
      chain.train(data);

      std::ofstream out(outputFile, std::ios::binary);
      if (!out.is_open()) {
        throw std::runtime_error("Cannot open output file: " + outputFile);
      }
      markov->serializeToOstream(out);
    }

    if (!gexfFile.empty()) {
      std::ofstream gexfOut(gexfFile);
      if (!gexfOut.is_open()) {
        throw std::runtime_error("Cannot open GEXF file: " + gexfFile);
      }
      gexfOut << graph.toGEXF();
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
