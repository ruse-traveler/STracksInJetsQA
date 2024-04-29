// ----------------------------------------------------------------------------
// 'BaseQAHistFiller.h'
// Derek Anderson
// 04.11.2024
//
// A submodule for the TracksInJetsQAMaker F4A module
// to produce QA histograms for tracks and more in
// jets
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKER_BASEQAHISTFILLER_H
#define TRACKSINJETSQAMAKER_BASEQAHISTFILLER_H

// c++ utilities
#include <string>
// root libraries
#include <TFile.h>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHCompositeNode.h>
// tracking libraries
#include <trackbase/ActsGeometry.h>
#include <trackbase/TrkrHitSetContainer.h>
#include <trackbase/TrkrClusterContainer.h>
#include <trackbase_historic/SvtxTrackMap.h>
// jet libraries
#include <jetbase/JetContainer.h>
// submodule definitions
#include "HitQAHistManager.h"
#include "ClustQAHistManager.h"
#include "TrackQAHistManager.h"
#include "JetQAHistManager.h"
// module utilties
#include "TracksInJetsQAMakerConfig.h"
#include "TracksInJetsQAMakerHistDef.h"



// BaseQAHistFiller -----------------------------------------------------------

class BaseQAHistFiller {

  public:

    // ctor/dtor
    BaseQAHistFiller(TracksInJetsQAMakerConfig& config, TracksInJetsQAMakerHistDef& hist);
    ~BaseQAHistFiller();

    // public methods
    void MakeHistograms(std::string label = "");
    void SaveHistograms(TFile* outFile, std::string outDirName);

    // virtual public methods
    virtual void Fill(PHCompositeNode* topNode) = 0;

  protected:

    // private methods
    void GetNodes(PHCompositeNode* topNode);

    // necessary dst nodes
    ActsGeometry*         m_actsGeom = NULL;
    TrkrHitSetContainer*  m_hitMap   = NULL;
    TrkrClusterContainer* m_clustMap = NULL;
    SvtxTrackMap*         m_trkMap   = NULL;
    JetContainer*         m_jetMap   = NULL;

    // submodules to use
    std::unique_ptr<HitQAHistManager>   m_hitManager   = NULL;
    std::unique_ptr<ClustQAHistManager> m_clustManager = NULL;
    std::unique_ptr<TrackQAHistManager> m_trackManager = NULL;
    std::unique_ptr<JetQAHistManager>   m_jetManager   = NULL;

    // module utilities
    TracksInJetsQAMakerConfig  m_config;
    TracksInJetsQAMakerHistDef m_hist;

};  // end BaseQAHistFiller

#endif

// end ------------------------------------------------------------------------
