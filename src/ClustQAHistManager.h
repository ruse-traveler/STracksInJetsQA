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
// f4a libraries
#include <phool/PHCompositeNode.h>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
// tracking libraries
#include <trackbase/TrkrDefs.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrCluster.h>
#include <trackbase/ActsGeometry.h>
#include <trackbase/TrkrHitSetContainer.h>
#include <trackbase/TrkrClusterContainer.h>
// module tools
#include "TracksInJetsQAMakerHelper.h"
#include "TracksInJetsQAMakerHistDef.h"



// ClustQAHistManager definition ------------------------------------------------------

class ClustQAHistManager {

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
    ClustQAHistManager() {};
    ~ClustQAHistManager() {};

    // public methods
    void Init(TracksInJetsQAMakerHistDef& hist, TracksInJetsQAMakerHelper& help);
    void Process(PHCompositeNode* topNode);
    void End(TFile* outFile, std::string outDirName);

  private:

    // private methods
    void BuildHistograms();
    void FillHistograms(Type type, ClustQAContent& content);

    // necessary dst nodes
    ActsGeometry*         m_actsGeom = NULL;
    TrkrHitSetContainer*  m_hitMap   = NULL;
    TrkrClusterContainer* m_clustMap = NULL;

    // histograms
    std::vector<std::vector<TH1D*>> vecHist1D;
    std::vector<std::vector<TH2D*>> vecHist2D;

    // module utilities
    TracksInJetsQAMakerHelper  m_help;
    TracksInJetsQAMakerHistDef m_hist;

};  // end ClustQAHistManager

#endif

// end ------------------------------------------------------------------------

