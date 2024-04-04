// ----------------------------------------------------------------------------
// 'ClustQAHistManager.h'
// Derek Anderson
// 03.25.2024
//
// A submodule for the TracksInJetsQAMaker module
// to generate QA plots for track clusters
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKER_CLUSTQAHISTMANAGER_H
#define TRACKSINJETSQAMAKER_CLUSTQAHISTMANAGER_H

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
#include <trackbase/TrkrDefs.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrCluster.h>
#include <trackbase/ActsGeometry.h>
// module tools
#include "TracksInJetsQAMakerHelper.h"
#include "TracksInJetsQAMakerHistDef.h"



// ClustQAHistManager definition ----------------------------------------------

class ClustQAHistManager : public BaseQAHistManager {

  public:

    // histogram accessors
    enum Type {Mvtx, Intt, Tpc, All};
    enum H1D  {PosX, PosY, PosZ, PosR};
    enum H2D  {PosYvsX, PosRvsZ};

    // histogram content
    struct ClustQAContent {
      double x = std::numeric_limits<double>::max();
      double y = std::numeric_limits<double>::max();
      double z = std::numeric_limits<double>::max();
      double r = std::numeric_limits<double>::max();
    };

    // ctor/dtor
    ClustQAHistManager() : BaseQAHistManager() {};
    ~ClustQAHistManager() : BaseQAHistManager() {};

    // external methods
    void GetInfo(const TrkrCluster* cluster, const TrkrDefs::clustkey& clustKey, const ActsGeometry* actsGeom);

  private:

    // internal methods
    void FillHistograms(Type type, ClustQAContent& content);

    // inherited internal methods
    void DefineHistograms() override;

};  // end ClustQAHistManager

#endif

// end ------------------------------------------------------------------------

