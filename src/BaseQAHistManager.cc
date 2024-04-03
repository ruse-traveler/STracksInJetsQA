// ----------------------------------------------------------------------------
// 'BaseQAHistManager.cc'
// Derek Anderson
// 04.03.2024
//
// Base hist manager submodule for the TracksInJetsQAMaker module
// which consolidates methods/data common to all of the hist
// managers
// ----------------------------------------------------------------------------

#define TRACKSINJETSQAMAKER_BASEQAHISTMANAGER_CC

// submodule definition
#include "BaseQAHistManager.h"



// external methods -----------------------------------------------------------

void BaseQAHistManager::Init() {

  BuildHistograms();
  return;

}  // end 'Init()'



void End(TFile* outFile, std::string outDirName) {

  return;

}  // end 'End(TFile*, std::string)'



// internal methods -----------------------------------------------------------

void BuildHistograms() {

  return;

}  // end 'BuildHistograms()'

// end ------------------------------------------------------------------------
