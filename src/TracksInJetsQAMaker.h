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
#include <cassert>
#include <utility>
#include <optional>
// root libraries
#include <TFile.h>
// f4a libraries
#include <fun4all/SubsysReco.h>
#include <fun4all/Fun4AllReturnCodes.h>
#include <fun4all/Fun4AllHistoManager.h>
// phool libraries
#include <phool/phool.h>
#include <phool/PHCompositeNode.h>
// qa utilities
#include <qautils/QAHistManagerDef.h>
// module utilities
#include "TracksInJetsQAMakerConfig.h"
#include "TracksInJetsQAMakerHistDef.h"
// submodule definitions
#include "InJetQAHistFiller.h"
#include "InclusiveQAHistFiller.h"



// TracksInJetsQAMaker definition ---------------------------------------------

class TracksInJetsQAMaker : public SubsysReco {

  public:

    //  output modes
    enum OutMode {File, QA};

    // ctor/dtor
    TracksInJetsQAMaker(const std::string& name);
    ~TracksInJetsQAMaker() override;

    // setters
    void SetOutFileName(const std::string& name)  {m_outFileName = name;}
    void SetHistSuffix(const std::string& suffix) {m_histSuffix  = suffix;}

    // public methods
    void Configure(
      TracksInJetsQAMakerConfig config,
      std::optional<TracksInJetsQAMakerHistDef> hist = std::nullopt
    );


    // f4a methods
    int Init(PHCompositeNode* topNode)          override;
    int process_event(PHCompositeNode* topNode) override;
    int End(PHCompositeNode* topNode)           override;

  private:

    // io members
    TFile*               m_outFile     = NULL;
    std::string          m_outFileName = "tracksInJetsQA.root";
    Fun4AllHistoManager* m_manager     = NULL;

    // optional suffix for histograms
    std::optional<std::string> m_histSuffix  = std::nullopt;

    // submodules to run
    std::unique_ptr<InJetQAHistFiller>     m_inJet;
    std::unique_ptr<InclusiveQAHistFiller> m_inclusive;

    // module utilities
    TracksInJetsQAMakerConfig  m_config;
    TracksInJetsQAMakerHistDef m_hist;

};  // end TracksInJetsQAMaker

#endif

// end ------------------------------------------------------------------------
