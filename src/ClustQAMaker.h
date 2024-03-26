// ----------------------------------------------------------------------------
// 'ClustQAMaker.h'
// Derek Anderson
// 03.25.2024
//
// A submodule for the TrackJetQAMaker module
// to generate QA plots for track clusters
// ----------------------------------------------------------------------------

#ifndef TRACKJETQAMAKER_CLUSTQAMAKER_H
#define TRACKJETQAMAKER_CLUSTQAMAKER_H

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



// ClustQAMaker definition ------------------------------------------------------

class ClustQAMaker {

  public:

    // ctor/dtor
    ClustQAMaker() {};
    ~ClustQAMaker() {};

    // public methods
    void Init();
    void Process(PHCompositeNode* topNode);
    void End();

  private:

    // histograms
    std::vector<TH1*> vecHist1D;
    std::vector<TH2*> vecHist2D;

};  // end ClustQAMaker

#endif

// end ------------------------------------------------------------------------

