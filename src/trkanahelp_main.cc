#include <iostream>
#include "unistd.h"

#include "TrkAna/InfoStructs/inc/EventInfo.hh"
#include "TrkAna/InfoStructs/inc/TrkInfo.hh"

void trkanahelp_usage() {
  std::cout
    << "  \n"
    "      trkanahelp [OPTIONS] BRANCH.LEAF [BRANCH.LEAF2 ... ]\n"
    "  \n"
    " Get help with trkana. \n"
    " \n"
    " Command line options: \n"
    "  -h print this help message\n"
    "  \n"
    " Examples: \n"
    "  trkanahelp evtinfo.nprotons evtinfo.run"
    " \n"
    " \n";
    }

void getBranchAndLeaf(const std::string& question, std::string& branch, std::string& leaf) {

  auto period = question.find(".");
  branch = question.substr(0, period);
  leaf = question.substr(period+1, question.size()-period-1);
}

int main(int argc, char** argv) {

  if (argc == 1) {
    trkanahelp_usage();
    return 0;
  }

  mu2e::EventInfo evtinfo;
  mu2e::TrkInfo trkinfo;

  char c;
  opterr = 0;
  while ((c = getopt(argc, argv, "h")) != -1) {
    switch (c) {
    case 'h':
      trkanahelp_usage();
      return 0;

    default:
      trkanahelp_usage();
      return 0;
    }
  }

  for (int i_question = optind; i_question < argc; ++i_question) {
    std::string question(argv[i_question]);
    //    std::cout << question << std::endl;
    std::string branch, leaf;
    getBranchAndLeaf(question, branch, leaf);
    if (branch == "evtinfo") {
      evtinfo.help(leaf);
    }
    else if (branch == "dem" || branch == "uem" || branch == "dep" || branch == "uep") {
      trkinfo.help(leaf);
    }
    else {
      std::cout << "Unknown branch: \"" << branch << "\"" << std::endl;
    }
  }
}
