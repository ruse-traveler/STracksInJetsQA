// ----------------------------------------------------------------------------
// 'JetQAMaker.h'
// Derek Anderson
// 03.26.2024
//
// A submodule for the TrackJetQAMaker module
// to generate QA plots for track jets
// ----------------------------------------------------------------------------

#ifndef TRACKJETQAMAKER_JETQAMAKER_H
#define TRACKJETQAMAKER_JETQAMAKER_H

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
// jet libraries
#include <jetbase/Jet.h>
#include <jetbase/JetContainer.h>
// module tools
#include "TrackJetQAMakerHelper.h"
#include "TrackJetQAMakerHistDef.h"



// JetQAMaker definition ------------------------------------------------------

class JetQAMaker {

  public:

    // histogram accessors
    enum Type {All};
    enum H1D  {JetEta, JetPhi, JetPt, SumPt};
    enum H2D  {JetPtVsEta, JetVsSumPt};

    // histogram content
    struct JetQAContent {
      double etaJet = std::numeric_limits<double>::max();
      double phiJet = std::numeric_limits<double>::max();
      double ptJet  = std::numeric_limits<double>::max();
      double ptSum  = std::numeric_limits<double>::max();
    };

    // ctor/dtor
    JetQAMaker() {};
    ~JetQAMaker() {};

    // public methods
    void Init(TrackJetQAMakerHistDef& hist, TrackJetQAMakerHelper& help);
    void Process(PHCompositeNode* topNode);
    void End(TFile* outFile, std::string outDirName);

  private:

    // private methods
    void BuildHistograms();
    void FillHistograms(Type type, JetQAContent& content);

    // necessary dst nodes
    JetContainer* m_jetMap = NULL;

    // histograms
    std::vector<std::vector<TH1D*>> vecHist1D;
    std::vector<std::vector<TH2D*>> vecHist2D;

    // module utilities
    TrackJetQAMakerHelper  m_help;
    TrackJetQAMakerHistDef m_hist;

};  // end JetQAMaker

#endif

// end ------------------------------------------------------------------------

