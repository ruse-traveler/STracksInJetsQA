// ----------------------------------------------------------------------------
// 'JetQAMaker.h'
// Derek Anderson
// 03.26.2024
//
// A submodule for the TracksInJetsQAMaker module
// to generate QA plots for track jets
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKER_JETQAMAKER_H
#define TRACKSINJETSQAMAKER_JETQAMAKER_H

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
// tracking libraries
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
// module tools
#include "TracksInJetsQAMakerHelper.h"
#include "TracksInJetsQAMakerHistDef.h"



// JetQAMaker definition ------------------------------------------------------

class JetQAMaker {

  public:

    // histogram accessors
    enum Type {All};
    enum J1D  {JetEta, JetPhi, JetPt, SumPt};
    enum C1D  {CstPt, CstQual};
    enum J2D  {JetPtVsEta, JetVsSumPt};
    enum C2D  {CstQualVsPt};

    // histogram content
    struct JetQAContent {
      double etaJet = std::numeric_limits<double>::max();
      double phiJet = std::numeric_limits<double>::max();
      double ptJet  = std::numeric_limits<double>::max();
      double ptSum  = std::numeric_limits<double>::max();
    };
    struct CstQAContent {
      double ptCst   = std::numeric_limits<double>::max();
      double qualCst = std::numeric_limits<double>::max();
    };

    // ctor/dtor
    JetQAMaker() {};
    ~JetQAMaker() {};

    // public methods
    void Init(TracksInJetsQAMakerHistDef& hist, TracksInJetsQAMakerHelper& help);
    void Process(PHCompositeNode* topNode);
    void End(TFile* outFile, std::string jetDirName, std::string cstDirName);

  private:

    // private methods
    void BuildHistograms();
    void FillHistograms(Type type, JetQAContent& content);
    void FillHistograms(Type type, CstQAContent& content);

    // necessary dst nodes
    JetContainer* m_jetMap = NULL;
    SvtxTrackMap* m_trkMap = NULL;

    // histograms
    std::vector<std::vector<TH1D*>> vecJetHist1D;
    std::vector<std::vector<TH1D*>> vecCstHist1D;
    std::vector<std::vector<TH2D*>> vecJetHist2D;
    std::vector<std::vector<TH2D*>> vecCstHist2D;

    // module utilities
    TracksInJetsQAMakerHelper  m_help;
    TracksInJetsQAMakerHistDef m_hist;

};  // end JetQAMaker

#endif

// end ------------------------------------------------------------------------

