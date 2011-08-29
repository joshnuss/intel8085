#include "token.h"
#include "lexer.h"
#include "instruction.h"
#include "parser.h"

#include <fstream>

#define VERSION "0.1.0"

#include <boost/program_options.hpp>

namespace po = boost::program_options;

class Runner {
  private:
    string outputFile;
    vector<string> inputFiles;
    bool verbose;

  public:
    Runner() {
      outputFile = "";
      verbose = false;
    }

    string getOutputFile() {
      return outputFile;
    }
    void setOutputFile(string val) {
      outputFile = val;
    }

    void setInputFiles(vector<string> val) {
      inputFiles = val;
    }
    vector<string> getInputFiles() {
      return inputFiles;
    }
    
    bool getVerbose() {
      return verbose;
    }
    void setVerbose(bool val) {
      verbose = val;
    }

    void printPrelude() {
      if (verbose) {
        cout << "iasm " << VERSION << endl;
        cout << "outputing to " << outputFile << endl;

        cout << "input files ";
        for (vector<string>::iterator it = inputFiles.begin(); it != inputFiles.end(); it++)
          cout << *it << " ";
        cout << endl;
      }
    }

    void compile() {
      Lexer lexer;
      string line;
      for (vector<string>::iterator it=inputFiles.begin(); it != inputFiles.end(); it++) {
        string path = *it;
        ifstream input(path.c_str(), std::ios_base::in);
        while (getline(input, line, '\n'))
        {
          lexer.parse_line(line);
        }
        input.close();
      }

      if (verbose) {
        cout << "=================" << endl;
        cout << "Lexer" << endl;
        cout << "=================" << endl;
        cout << lexer.toString() << endl;
      }

      Parser parser;
      parser.parse(lexer.getTokens());

      if (verbose) {
        cout << "=================" << endl;
        cout << "Parser" << endl;
        cout << "=================" << endl;
        cout << parser.toString() << endl;
      }
    }
};

int main(int argc, char** argv) {
  po::options_description desc("iasm - Intel 8085 assembler");
  po::options_description generic("Generic options");
  generic.add_options()
        ("version,v", "version information")
        ("verbose,V", po::value<bool>()->zero_tokens()->default_value(false), "show verbose output")
        ("help,h", "shows this message");

  po::options_description config("Configuration");
  config.add_options()
        ("input,i", po::value<vector<string> >(), "specify input asm files")
        ("output,o", po::value<string>()->default_value("a.rom"), "specify output rom file");

  po::positional_options_description input;
  input.add("input", -1);

  desc.add(generic).add(config);

  po::variables_map vm;
  store(po::command_line_parser(argc, argv).options(desc).positional(input).run(), vm);
  notify(vm);    

  if (vm.count("help")) {
      cout << desc << endl;
      return 1;
  }

  if (vm.count("version")) {
      cout << VERSION << endl;
      return 0;
  }

  if (!vm.count("input")) {
      cout << "Sorry, no input files were specified" << endl;
      return -1;
  }

  Runner runner;
  runner.setOutputFile(vm["output"].as<string>());
  runner.setVerbose(vm["verbose"].as<bool>());
  runner.setInputFiles(vm["input"].as< vector<string> >());

  runner.printPrelude();
  runner.compile();

}
