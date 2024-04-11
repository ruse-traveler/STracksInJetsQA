// ----------------------------------------------------------------------------
// 'TracksInJetsQAMaker.h'
// Derek Anderson
// 03.25.2024
//
// A "small" Fun4All module to produce QA plots for tracks,
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
#include <TFile.h>
// f4a/phool libraries
#include <fun4all/SubsysReco.h>
#include <phool/PHCompositeNode.h>
#include <fun4all/Fun4AllReturnCodes.h>
// module utilities
#include "TracksInJetsQAMakerConfig.h"
#include "TracksInJetsQAMakerHelper.h"
#include "TracksInJetsQAMakerHistDef.h"
// submodule definitions
#include "InJetQAHistFiller.h"
#include "InclusiveQAHistFiller.h"



// TracksInJetsQAMaker definition ---------------------------------------------

class TracksInJetsQAMaker : public SubsysReco {

  public:

    // ctor/dtor
    TracksInJetsQAMaker(const std::string &name = "TracksInJetsQAMaker", const std::string& sOutFileName = "tracksinjets.root");
    ~TracksInJetsQAMaker() override;

    // public methods
    void Configure(TracksInJetsQAMakerConfig config, std::optional<TracksInJetsQAMakerHistDef> hist = std::nullopt);

    // f4a methods
    int Init(PHCompositeNode* topNode)          override;
    int process_event(PHCompositeNode* topNode) override;
    int End(PHCompositeNode* topNode)           override;

  private:

    // io members
    TFile*      m_outFile     = NULL;
    std::string m_outFileName = "";

    // submodules to run
    std::unique_ptr<InJetQAHistFiller>     m_inJet;
    std::unique_ptr<InclusiveQAHistFiller> m_inclusive;

    // module utilities
    TracksInJetsQAMakerConfig  m_config;
    TracksInJetsQAMakerHelper  m_help;
    TracksInJetsQAMakerHistDef m_hist;

};  // end TracksInJetsQAMaker

#endif

// end ------------------------------------------------------------------------
