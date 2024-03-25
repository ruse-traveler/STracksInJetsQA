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

};  // end TrackJetQAMakerConfig

#endif

// end ------------------------------------------------------------------------
