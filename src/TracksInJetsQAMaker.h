// ----------------------------------------------------------------------------
// 'TracksInJetsQAMaker.h'
// Derek Anderson
// 03.25.2024
//
// A small Fun4All module to produce QA plots for tracks,
// hits, and more.
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKER_H
#define TRACKSINJETSQAMAKER_H

// c++ utilities
#include <string>
#include <vector>
#include <utility>
#include <optional>
// root libraries
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
// fun4all libraries
#include <fun4all/SubsysReco.h>
#include <phool/PHCompositeNode.h>
#include <fun4all/Fun4AllReturnCodes.h>
// module tools
#include "TrackJetQAMakerConfig.h"
#include "TrackJetQAMakerHistDef.h"
// plugin definitions
#include "HitQAMaker.h"
#include "ClustQAMaker.h"
#include "TrackQAMaker.h"



// TracksInJetsQAMaker definition --------------------------------------------

class TracksInJetsQAMaker : public SubsysReco {

  public:

    // ctor/dtor
    TracksInJetsQAMaker(const std::string &name = "TracksInJetsQAMaker", const std::string& sOutFileName = "tracksinjets.root");
    ~TracksInJetsQAMaker() override;

    // public methods
    void Configure(TrackJetQAMakerConfig config, std::optional<TrackJetQAMakerHistDef> hist = std::nullopt);

    // f4a methods
    int Init(PHCompositeNode* topNode)          override;
    int InitRun(PHCompositeNode* topNode)       override;
    int process_event(PHCompositeNode* topNode) override;
    int ResetEvent(PHCompositeNode* topNode)    override;
    int EndRun(const int runnumber)             override;
    int End(PHCompositeNode* topNode)           override;
    int Reset(PHCompositeNode*  /*topNode*/)    override;

  private:

    // io members
    TFile*      m_outFile     = NULL;
    std::string m_outFileName = "";

    // plugins to run
    HitQAMaker*   m_hitMaker   = NULL;
    ClustQAMaker* m_clustMaker = NULL;
    TrackQAMaker* m_trackMaker = NULL;

    // configurable parameters and histogram definitions
    TrackJetQAMakerConfig  m_config;
    TrackJetQAMakerHistDef m_hist;

};  // end TracksInJetsQAMaker

#endif

// end ------------------------------------------------------------------------
