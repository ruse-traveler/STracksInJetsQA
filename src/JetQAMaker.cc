// ----------------------------------------------------------------------------
// 'JetQAMaker.cc'
// Derek Anderson
// 03.25.2024
//
// A submodule for the TrackJetQAMaker module
// to generate QA plots for track jets
// ----------------------------------------------------------------------------

#define TRACKJETQAMAKER_JETQAMAKER_CC

// submodule definition
#include "JetQAMaker.h"



// public methods -------------------------------------------------------------

void JetQAMaker::Init(TrackJetQAMakerHistDef& hist, TrackJetQAMakerHelper& help) {

  // grab module utilities
  m_help = help;
  m_hist = hist;

  // make histograms
  BuildHistograms();
  return;

}  // end 'Init(TrackJetQAMakerHistDef&, TrackJetQAMakerHelper&)'



void JetQAMaker::Process(PHCompositeNode* topNode) {

  // grab jet map from node tree
  m_jetMap = findNode::getClass<JetContainer>(topNode, "AntiKt_Track_r04");
  if (!m_jetMap) {
    std::cerr << PHWHERE << ": PANIC: couldn't grab jet map from node tree!" << std::endl;
    assert(m_jetMap);
  }

  // loop over jets
  for (
    uint64_t iJet = 0;
    iJet < m_jetMap -> size();
    ++iJet
  ) {

    // grab jet
    Jet* jet = m_jetMap -> get_jet(iJet);

    // collect jet info
    JetQAContent jetContent {
      .etaJet = jet -> get_eta(),
      .phiJet = jet -> get_phi(),
      .ptJet  = jet -> get_pt(),
      .ptSum  = std::numeric_limits<double>::max()  // TODO put in calc
    };

    // fill histograms
    FillHistograms(Type::All, jetContent);

  }  // end jet loop
  return;

}  // end 'Process(PHCompositeNode*)'



void JetQAMaker::End(TFile* outFile, std::string outDirName) {

  TDirectory* outDir = outFile -> mkdir(outDirName.data());
  if (!outDir) {
    std::cerr << PHWHERE << ": PANIC: unable to make output directory!" << std::endl;
    assert(outDir);
  }

  outDir -> cd();
  for (auto hist1Ds : vecHist1D) {
    for (TH1D* hist1D : hist1Ds) {
      hist1D -> Write();
    }
  }
  for (auto hist2Ds : vecHist2D) {
    for (TH2D* hist2D : hist2Ds) {
      hist2D -> Write();
    }
  }
  return;

}  // end 'End()'



// private methods ------------------------------------------------------------

void JetQAMaker::BuildHistograms() {

  // grab binning schemes
  std::vector<BinDef> vecBins = m_hist.GetVecHistBins();

  // histogram labels/definitions
  const std::vector<std::string> vecHistTypes  = {
    "All"
  };
  const std::vector<HistDef1D> vecHistDef1D = {
    std::make_tuple( "JetEta", vecBins.at(TrackJetQAMakerHistDef::Var::Eta) ),
    std::make_tuple( "JetPhi", vecBins.at(TrackJetQAMakerHistDef::Var::Phi) ),
    std::make_tuple( "JetPt",  vecBins.at(TrackJetQAMakerHistDef::Var::Ene) ),
    std::make_tuple( "SumPt",  vecBins.at(TrackJetQAMakerHistDef::Var::Ene) )
  };
  const std::vector<HistDef2D> vecHistDef2D = {
    std::make_tuple(
      "JetPtVsEta",
      vecBins.at(TrackJetQAMakerHistDef::Var::Eta),
      vecBins.at(TrackJetQAMakerHistDef::Var::Ene)
    ),
    std::make_tuple(
      "JetVsSumPt",
      vecBins.at(TrackJetQAMakerHistDef::Var::Ene),
      vecBins.at(TrackJetQAMakerHistDef::Var::Ene)
    )
  };

  // build 1d histograms
  vecHist1D.resize( vecHistTypes.size() );
  for (size_t iType = 0; iType < vecHistTypes.size(); iType++) {
    for (HistDef1D histDef1D : vecHistDef1D) {

      // make name
      std::string sHistName("h");
      sHistName += vecHistTypes.at(iType);
      sHistName += std::get<0>(histDef1D);

      // create histogram
      vecHist1D.at(iType).push_back(
        new TH1D(
          sHistName.data(),
          "",
          std::get<1>(histDef1D).first,
          std::get<1>(histDef1D).second.first,
          std::get<1>(histDef1D).second.second
        )
      );
    }  // end hist loop
  }  // end type loop

  // build 2d histograms
  vecHist2D.resize( vecHistTypes.size() );
  for (size_t iType = 0; iType < vecHistTypes.size(); iType++) {
    for (HistDef2D histDef2D : vecHistDef2D) {

      // make name
      std::string sHistName("h");
      sHistName += vecHistTypes.at(iType);
      sHistName += std::get<0>(histDef2D);

      // create histogram
      vecHist2D.at(iType).push_back(
        new TH2D(
          sHistName.data(),
          "",
          std::get<1>(histDef2D).first,
          std::get<1>(histDef2D).second.first,
          std::get<1>(histDef2D).second.second,
          std::get<2>(histDef2D).first,
          std::get<2>(histDef2D).second.first,
          std::get<2>(histDef2D).second.second
        )
      );
    }  // end hist loop
  }  // end type loop
  return;

}  // end 'BuildHistograms()'



void JetQAMaker::FillHistograms(Type type, JetQAContent& content) {

  // fill 1d histograms
  vecHist1D.at(type).at(H1D::JetEta) -> Fill(content.etaJet);
  vecHist1D.at(type).at(H1D::JetPhi) -> Fill(content.phiJet);
  vecHist1D.at(type).at(H1D::JetPt)  -> Fill(content.ptJet);
  vecHist1D.at(type).at(H1D::SumPt)  -> Fill(content.ptSum);

  // fill 2d histograms
  vecHist2D.at(type).at(H2D::JetPtVsEta) -> Fill(content.etaJet, content.ptJet);
  vecHist2D.at(type).at(H2D::JetVsSumPt) -> Fill(content.ptSum, content.ptJet);
  return;

}  //  end 'FillHistograms(Type, JetQAContent&)'

// end ------------------------------------------------------------------------


