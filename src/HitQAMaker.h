// ----------------------------------------------------------------------------
// 'HitQAMaker.h'
// Derek Anderson
// 03.25.2024
//
// A submodule for the TracksInJetsQAMaker module
// to generate QA plots for track hits
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKER_HITQAMAKER_H
#define TRACKSINJETSQAMAKER_HITQAMAKER_H

// c++ utilities
#include <limits>
#include <string>
#include <vector>
#include <cassert>
#include <utility>
#include <optional>
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
#include <trackbase/TpcDefs.h>
#include <trackbase/TrkrDefs.h>
#include <trackbase/InttDefs.h>
#include <trackbase/MvtxDefs.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrHitSetContainer.h>
// module tools
#include "TracksInJetsQAMakerHelper.h"
#include "TracksInJetsQAMakerHistDef.h"



// HitQAMaker definition ------------------------------------------------------

class HitQAMaker {

  public:

    // histogram accessors
    enum Type {Mvtx, Intt, Tpc, All};
    enum H1D  {Ene, ADC, Layer, PhiBin, ZBin};
    enum H2D  {EneVsLayer, EneVsADC, PhiVsZBin};

    // histogram content
    struct HitQAContent {
      double   ene    = std::numeric_limits<double>::max();
      uint64_t adc    = std::numeric_limits<uint64_t>::max();
      uint16_t layer  = std::numeric_limits<uint16_t>::max();
      uint16_t phiBin = std::numeric_limits<uint16_t>::max();
      uint16_t zBin   = std::numeric_limits<uint16_t>::max();
    };

    // ctor/dtor
    HitQAMaker() {};
    ~HitQAMaker() {};

    // public methods
    void Init(TracksInJetsQAMakerHistDef& hist, TracksInJetsQAMakerHelper& help);
    void Process(PHCompositeNode* topNode);
    void End(TFile* outFile, std::string outDirName);

  private:

    // private methods
    void BuildHistograms();
    void FillHistograms(Type type, HitQAContent& content);

    // necessary dst nodes
    TrkrHitSetContainer* m_hitMap = NULL;
    /* TODO add TPC geometry container */

    // histograms
    std::vector<std::vector<TH1D*>> vecHist1D;
    std::vector<std::vector<TH2D*>> vecHist2D;

    // module utilities
    TracksInJetsQAMakerHelper  m_help;
    TracksInJetsQAMakerHistDef m_hist;

};  // end HitQAMaker

#endif

// end ------------------------------------------------------------------------
