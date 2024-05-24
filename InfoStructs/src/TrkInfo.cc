#include "TrkAna/InfoStructs/inc/TrkInfo.hh"

#include <iostream>

const double mu2e::TrkInfo::get(std::string leaf) const {
  if (leaf == "status") { return status; }
  else if (leaf == "nhits") { return nhits; }
  else if (leaf == "nactive") { return nactive; }
  else { std::cout << "ERROR: unknown leaf \"" << leaf << "\"" << std::endl; return -999; }
}

void mu2e::TrkInfo::help(std::string leaf) const {
  if (leaf == "status") { std::cout << "status = Kalman fit status" << std::endl; }
  else if (leaf == "nhits") { std::cout << "nhits = total number of hits (used+unused) on the track" << std::endl; }
  else if (leaf == "nactive") { std::cout << "nactive = total number of used hits on the track" << std::endl; }
  else {std::cout << "ERROR: unknown leaf \"" << leaf << "\"" << std::endl; }
}
