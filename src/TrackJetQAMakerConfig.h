// ----------------------------------------------------------------------------
// 'TrackJetQAMakerConfig.h'
// Derek Anderson
// 03.25.2024
//
// Configurable parameters for the TracksInJetsQAMaker module.
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKERCONFIG_H
#define TRACKSINJETSQAMAKERCONFIG_H

// c++ utilities
#include <string>



struct TrackJetQAMakerConfig {

  // system parameters
  int  verbose     = 0;
  bool doDebug     = false;
  bool doHitQA     = true;
  bool doClustQA   = true;
  bool doTrackQA   = true;

  // i/o parameters
  std::string hitOutDir   = "HitQA";
  std::string clustOutDir = "ClustQA";
  std::string trackOutDir = "TrackQA";

};  // end TrackJetQAMakerConfig

#endif

// end ------------------------------------------------------------------------
