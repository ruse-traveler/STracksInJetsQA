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
#include <limits>
#include <string>
#include <vector>
#include <cassert>
// root libraries
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TDirectory.h>
// f4a libraries
#include <phool/PHCompositeNode.h>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
// tracking libraries
#include <trackbase/TrkrHit.h>
#include <trackbase/TrkrDefs.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrHitSetContainer.h>
// module tools
#include "TrackJetQAMakerConfig.h"
#include "TrackJetQAMakerHistDef.h"



// HitQAMaker definition ------------------------------------------------------

class HitQAMaker {

  public:

    // histogram accessors
    enum Type {Mvtx, Intt, Tpc, Tpot, All};
    enum Var  {ID, Adc, Ene, Layer, Phi, Z};

    // histogram content
    struct HitQAContent {
      int      layr = std::numeric_limits<int>::max();
      double   ene  = std::numeric_limits<double>::max();
      uint64_t id   = std::numeric_limits<uint64_t>::max();
      uint64_t adc  = std::numeric_limits<uint64_t>::max();
    };

    // ctor/dtor
    HitQAMaker() {};
    ~HitQAMaker() {};

    // public methods
    void Init(TrackJetQAMakerHistDef& hist);
    void Process(PHCompositeNode* topNode);
    void End(TFile* outFile);

  private:

    // private methods
    void FillHistograms(Type type, HitQAContent& content);

    // necessary dst nodes
    TrkrHitSetContainer* m_hitMap = NULL;

    // histograms
    std::vector<TH1D*> vecHist1D;
    std::vector<TH2D*> vecHist2D;

};  // end HitQAMaker

#endif

// end ------------------------------------------------------------------------
