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

// root libraries
#include <TFile.h>
// phool libraries
#include <phool/PHCompositeNode.h>
// submodule definitions
#include "HitQAHistManager.h"
#include "ClustQAHistManager.h"
#include "TrackQAHistManager.h"
#include "JetQAHistManager.h"
// module utilties
#include "TracksInJetsQAMakerConfig.h"
#include "TracksInJetsQAMakerHelper.h"
#include "TracksInJetsQAMakerHistDef.h"



// BaseQAHistFiller -----------------------------------------------------------

class BaseQAHistFiller {

  public:

    // ctor/dtor
    BaseQAHistFiller();
    ~BaseQAHistFiller();

    // external methods
    void Init(TracksInJetsQAMakerConfig& config, TracksInJetsQAMakerHelper& helper, TracksInJetsQAMakerHistDef& hist);
    void SaveHistograms(TFile* outFile);

    // virtual external methods
    virtual void Fill(PHCompositeNode* topNode) = 0;

  protected:

    // virtual internal methods
    virtual void GetNodes(PHCompositeNode* topNode) = 0;

    // submodules to use
    std::unique_ptr<HitQAHistManager>   m_hitManager   = NULL;
    std::unique_ptr<ClustQAHistManager> m_clustManager = NULL;
    std::unique_ptr<TrackQAHistManager> m_trackManager = NULL;
    std::unique_ptr<JetQAHistManager>   m_jetManager   = NULL;

    // module utilities
    TracksInJetsQAMakerConfig  m_config;
    TracksInJetsQAMakerHelper  m_help;
    TracksInJetsQAMakerHistDef m_hist;

};  // end BaseQAHistFiller

#endif

// end ------------------------------------------------------------------------
