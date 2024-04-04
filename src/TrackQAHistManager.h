// ----------------------------------------------------------------------------
// 'TrackQAHistManager.h'
// Derek Anderson
// 03.25.2024
//
// A submodule for the TrackJetQAMaker module
// to generate QA plots for tracks, inclusive
// and in jets
// ----------------------------------------------------------------------------

#ifndef TRACKJETQAMAKER_TRACKQAHISTMANAGER_H
#define TRACKJETQAMAKER_TRACKQAHISTMANAGER_H

// c++ utilities
#include <limits>
#include <vector>
#include <utility>
// root libraries
#include <TH1.h>
#include <TH2.h>
// tracking libraries
#include <trackbase_historic/SvtxTrack.h>
// module tools
#include "TrackJetQAMakerHelper.h"
#include "TrackJetQAMakerHistDef.h"



// TrackQAHistManager definition ----------------------------------------------

class TrackQAHistManager : public BaseQAHistManager {

  public:

    // histogram accessors
    //   - TODO split tracks into seed types
    enum Type {All};
    enum H1D  {Eta, Phi, Pt, Qual};
    enum H2D  {EtaVsPhi, PtVsQual};

    // histogram content
    struct TrackQAContent {
      double eta  = std::numeric_limits<double>::max();
      double phi  = std::numeric_limits<double>::max();
      double pt   = std::numeric_limits<double>::max();
      double qual = std::numeric_limits<double>::max();
    };

    // ctor/dtor
    TrackQAHistManager() : BaseQAHistManager() {};
    ~TrackQAHistManager() : ~BaseQAHistManager() {};

    // external methods
    void GetInfo(const SvtxTrack* track);

  private:

    // internal methods
    void FillHistograms(const int type, TrackQAContent& content);

    // inherited internal methods
    void DefineHistograms();

};  // end TrackQAHistManager

#endif

// end ------------------------------------------------------------------------

