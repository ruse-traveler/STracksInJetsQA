// ----------------------------------------------------------------------------
// 'TracksInJetsQAMakerConfig.h'
// Derek Anderson
// 03.25.2024
//
// Configurable parameters for the TracksInJetsQAMaker module.
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKERCONFIG_H
#define TRACKSINJETSQAMAKERCONFIG_H

// c++ utilities
#include <string>



// TracksInJetsQAMakerConfig definition ---------------------------------------

struct TracksInJetsQAMakerConfig {

  // system parameters
  int  verbose     = 0;
  bool doDebug     = false;
  bool doInclusive = true;
  bool doInJet     = true;
  bool doHitQA     = false;
  bool doClustQA   = false;
  bool doTrackQA   = true;
  bool doJetQA     = true;

  // i/o options
  std::string outFileName  = "test.root";
  std::string inclusiveDir = "Inclusive";
  std::string inJetDir     = "InJet";
  std::string hitOutDir    = "Hit";
  std::string clustOutDir  = "Clust";
  std::string trackOutDir  = "Track";
  std::string jetOutDir    = "Jet";

  // tracker parameters
  uint16_t nMvtxLayer = 3;
  uint16_t nInttLayer = 4;
  uint16_t nTpcLayer  = 48;

};  // end TracksInJetsQAMakerConfig

#endif

// end ------------------------------------------------------------------------
