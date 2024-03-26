// ----------------------------------------------------------------------------
// 'TrackJetQAMakerConfig.h'
// Derek Anderson
// 03.25.2024
//
// Configurable parameters for the TrackJetQAMaker module.
// ----------------------------------------------------------------------------

#ifndef TRACKJETQAMAKERCONFIG_H
#define TRACKJETQAMAKERCONFIG_H

// c++ utilities
#include <string>



struct TrackJetQAMakerConfig {

  // system parameters
  int  verbose   = 0;
  bool doDebug   = false;
  bool doHitQA   = true;
  bool doClustQA = true;
  bool doTrackQA = true;

  // i/o parameters
  std::string hitOutDir   = "HitQA";
  std::string clustOutDir = "ClustQA";
  std::string trackOutDir = "TrackQA";

  // tracker parameters
  uint16_t nMvtxLayer = 3;
  uint16_t nInttLayer = 4;
  uint16_t nTpcLayer  = 48;

};  // end TrackJetQAMakerConfig

#endif

// end ------------------------------------------------------------------------
