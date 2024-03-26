// ----------------------------------------------------------------------------
// 'ClustQAMaker.cc'
// Derek Anderson
// 03.25.2024
//
// A submodule for the TrackJetQAMaker module
// to generate QA plots for track clusters
// ----------------------------------------------------------------------------

#define TRACKJETQAMAKER_CLUSTQAMAKER_CC

// submodule definition
#include "ClustQAMaker.h"



// public methods -------------------------------------------------------------

void ClustQAMaker::Init(TrackJetQAMakerHistDef& hist, TrackJetQAMakerHelper& help) {

  // grab module utilities
  m_help = help;
  m_hist = hist;

  // make histograms
  BuildHistograms();
  return;

}  // end 'Init(TrackJetQAMakerHistDef&, TrackJetQAMakerHelper&)'



void ClustQAMaker::Process(PHCompositeNode* topNode) {

  return;

}  // end 'Process(PHCompositeNode*)'



void ClustQAMaker::End(TFile* outFile, std::string outDirName) {

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

void ClustQAMaker::BuildHistograms() {

  // grab binning schemes
  std::vector<BinDef> vecBins = m_hist.GetVecHistBins();

  // histogram labels/definitions
  const std::vector<std::string> vecHistTypes  = {
    "Mvtx",
    "Intt",
    "Tpc",
    "All"
  };
  const std::vector<HistDef1D> vecHistDef1D = {
    std::make_tuple( "ClustPosX", vecBins.at(TrackJetQAMakerHistDef::Var::PosXY) ),
    std::make_tuple( "ClustPosY", vecBins.at(TrackJetQAMakerHistDef::Var::PosXY) ),
    std::make_tuple( "ClustPosZ", vecBins.at(TrackJetQAMakerHistDef::Var::PosZ) ),
    std::make_tuple( "ClustPosR", vecBins.at(TrackJetQAMakerHistDef::Var::PosR) )
  };
  const std::vector<HistDef2D> vecHistDef2D = {
    std::make_tuple(
      "ClustPosYvsX",
      vecBins.at(TrackJetQAMakerHistDef::Var::PosXY),
      vecBins.at(TrackJetQAMakerHistDef::Var::PosXY)
    ),
    std::make_tuple(
      "ClustPosRvsZ",
      vecBins.at(TrackJetQAMakerHistDef::Var::PosZ),
      vecBins.at(TrackJetQAMakerHistDef::Var::PosR)
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



void ClustQAMaker::FillHistograms(Type type, ClustQAContent& content) {

  // fill 1d histograms
  vecHist1D.at(type).at(H1D::PosX) -> Fill(content.x);
  vecHist1D.at(type).at(H1D::PosY) -> Fill(content.y);
  vecHist1D.at(type).at(H1D::PosZ) -> Fill(content.z);
  vecHist1D.at(type).at(H1D::PosR) -> Fill(content.r);

  // fill 2d histograms
  vecHist2D.at(type).at(H2D::PosYvsX) -> Fill(content.x, content.y);
  vecHist2D.at(type).at(H2D::PosRvsZ) -> Fill(content.z, content.r);
  return;

}  //  end 'FillHistograms(Type, ClustQAContent&)'

// end ------------------------------------------------------------------------

