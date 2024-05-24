//
// swig interface file to wrap c++ code for python
//

%module TrkAna

%include "std_string.i"
%include "std_vector.i"
%include "stdint.i"

%apply const std::string& {std::string* foo};

%{
#include "TrkAna/InfoStructs/inc/EventInfo.hh"
#include "TrkAna/InfoStructs/inc/TrkInfo.hh"
%}

%include "TrkAna/InfoStructs/inc/EventInfo.hh"
%include "TrkAna/InfoStructs/inc/TrkInfo.hh"
