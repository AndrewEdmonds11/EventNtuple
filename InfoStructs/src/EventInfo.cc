#include <iostream>

#include "TrkAna/InfoStructs/inc/EventInfo.hh"

double mu2e::EventInfo::get(std::string leaf) {
  if (leaf == "event") { return event; }
  else if (leaf == "subrun") { return subrun; }
  else if (leaf == "run") { return run; }
  else if (leaf == "nprotons") { return nprotons; }
  else if (leaf == "pbtime") { return pbtime; }
  else if (leaf == "pbterr") { return pbterr; }
  else { std::cout << "ERROR: unknown leaf \"" << leaf << "\"" << std::endl; return -999; }
}

void mu2e::EventInfo::help(std::string leaf) {
  if (leaf == "event") {std::cout << "evtinfo."+leaf+": art event number" << std::endl; }
  else if (leaf == "subrun") {std::cout << "evtinfo."+leaf+": art subrun number" << std::endl; }
  else if (leaf == "run") {std::cout << "evtinfo."+leaf+": art run number" << std::endl; }
  else if (leaf == "nprotons") {std::cout << "evtinfo."+leaf+": estimated number of protons-on-target (POT)" << std::endl; }
  else if (leaf == "pbtime") {std::cout << "evtinfo."+leaf+": estimated proton bunch time" << std::endl; }
  else if (leaf == "pbterr") {std::cout << "evtinfo."+leaf+": estimated proton bunch time uncertainty" << std::endl; }
  else {std::cout << "ERROR: unknown leaf \"" << leaf << "\"" << std::endl; }
}
