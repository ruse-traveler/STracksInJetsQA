// ----------------------------------------------------------------------------
// 'TrackQAMaker.h'
// Derek Anderson
// 03.25.2024
//
// A plugin for the TracksInJetsQAMaker module
// to generate QA plots for tracks, inclusive
// and in jets
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKER_TRACKQAMAKER_H
#define TRACKSINJETSQAMAKER_TRACKQAMAKER_H

// c++ utilities
#include <string>
#include <vector>
// root libraries
#include <TH1.h>
#include <TH2.h>
// f4a libraries
#include <phool/PHCompositeNode.h>
// module tools
#include "TrackJetQAMakerConfig.h"
#include "TrackJetQAMakerHistDef.h"



// TrackQAMaker definition ------------------------------------------------------

class TrackQAMaker {

  public:

    // ctor/dtor
    TrackQAMaker() {};
    ~TrackQAMaker() {};

    // public methods
    void Init();
    void Process(PHCompositeNode* topNode);
    void End();

  private:

    // histograms
    std::vector<TH1*> vecHist1D;
    std::vector<TH2*> vecHist2D;

};  // end TrackQAMaker

#endif

// end ------------------------------------------------------------------------

