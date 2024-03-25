// ----------------------------------------------------------------------------
// 'HitQAMaker.h'
// Derek Anderson
// 03.25.2024
//
// A plugin for the TracksInJetsQAMaker module
// to generate QA plots for track hits
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKER_HITQAMAKER_H
#define TRACKSINJETSQAMAKER_HITQAMAKER_H

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



// HitQAMaker definition ------------------------------------------------------

class HitQAMaker {

  public:

    // ctor/dtor
    HitQAMaker() {};
    ~HitQAMaker() {};

    // public methods
    void Init();
    void Process(PHCompositeNode* topNode);
    void End();

  private:

    // histograms
    std::vector<TH1*> vecHist1D;
    std::vector<TH2*> vecHist2D;

};  // end HitQAMaker

#endif

// end ------------------------------------------------------------------------
