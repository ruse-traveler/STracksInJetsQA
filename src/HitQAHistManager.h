// ----------------------------------------------------------------------------
// 'HitQAHistManager.h'
// Derek Anderson
// 03.25.2024
//
// A submodule for the TracksInJetsQAMaker module
// to generate QA plots for track hits
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKER_HITQAHISTMANAGER_H
#define TRACKSINJETSQAMAKER_HITQAHISTMANAGER_H

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
// tracking libraries
#include <trackbase/TrkrHit.h>
#include <trackbase/TpcDefs.h>
#include <trackbase/TrkrDefs.h>
#include <trackbase/InttDefs.h>
#include <trackbase/MvtxDefs.h>
// module tools
#include "BaseQAHistManager.h"
#include "TracksInJetsQAMakerHelper.h"
#include "TracksInJetsQAMakerHistDef.h"



// HitQAHistManager definition ------------------------------------------------

class HitQAHistManager : public BaseQAHistManager {

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
    HitQAHistManager() : BaseQAHistManager() {};
    ~HitQAHistManager() : ~BaseQAHistManager() {};

    // external methods
    void GetInfo(const TrkrHit* hit, const TrkrDefs::hitsetkey setKey, const TrkrDefs::hitkey hitKey);

  private:

    // internal methods
    void FillHistograms(const int type, const HitQAContent& content);

    // inherited internal methods
    void DefineHistograms() override;

};  // end HitQAHistManager

#endif

// end ------------------------------------------------------------------------
