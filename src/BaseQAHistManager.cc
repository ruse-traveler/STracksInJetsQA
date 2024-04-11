// ----------------------------------------------------------------------------
// 'BaseQAHistManager.cc'
// Derek Anderson
// 04.03.2024
//
// Base hist manager submodule for the TracksInJetsQAMaker module
// which consolidates methods/data common to all of the hist
// managers
// ----------------------------------------------------------------------------

#define TRACKSINJETSQAMAKER_BASEQAHISTMANAGER_CC

// submodule definition
#include "BaseQAHistManager.h"



// ctor/dtor ------------------------------------------------------------------

BaseQAHistManager::BaseQAHistManager() {

  ResetVectors();

}  // end ctor



BaseQAHistManager::~BaseQAHistManager() {

  ResetVectors();

}  // end dtor



// external methods -----------------------------------------------------------

void BaseQAHistManager::Init(TracksInJetsQAMakerHelper& help, TracksInJetsQAMakerHistDef& hist) {

  // grab helper & hist definitions
  m_help = help;
  m_hist = hist;

  // construct histograms
  DefineHistograms();
  BuildHistograms();
  return;

}  // end 'Init(TracksInJetsQAMakerHelper&, TracksInJetsQAMakerHistDef&)'



void SaveHistograms(TDirectory* topDir, std::string outDirName) {

  TDirectory* outDir = topDir -> mkdir(outDirName.data());
  if (!outDir) {
    std::cerr << PHWHERE << ": PANIC: unable to make output directory!" << std::endl;
    assert(outDir);
  }

  outDir -> cd();
  for (auto hist1Ds : m_vecHist1D) {
    for (TH1D* hist1D : hist1Ds) {
      hist1D -> Write();
    }
  }
  for (auto hist2Ds : m_vecHist2D) {
    for (TH2D* hist2D : hist2Ds) {
      hist2D -> Write();
    }
  }
  return;

}  // end 'SaveHistograms(TFile*, std::string)'



// internal methods -----------------------------------------------------------

void BuildHistograms() {

  // build 1d histograms
  m_vecHist1D.resize( m_vecHistTypes.size() );
  for (size_t iType = 0; iType < m_vecHistTypes.size(); iType++) {
    for (HistDef1D histDef1D : m_vecHistDef1D) {

      // make name
      std::string sHistName("h");
      sHistName += m_vecHistTypes.at(iType);
      sHistName += std::get<0>(histDef1D);

      // create histogram
      m_vecHist1D.at(iType).push_back(
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
  m_vecHist2D.resize( m_vecHistTypes.size() );
  for (size_t iType = 0; iType < m_vecHistTypes.size(); iType++) {
    for (HistDef2D histDef2D : m_vecHistDef2D) {

      // make name
      std::string sHistName("h");
      sHistName += m_vecHistTypes.at(iType);
      sHistName += std::get<0>(histDef2D);

      // create histogram
      m_vecHist2D.at(iType).push_back(
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



void ResetVectors() {

  m_vecHist1D.clear();
  m_vecHist2D.clear();
  m_vecHistTypes.clear();
  m_vecHistDef1D.clear();
  m_vecHistDef2D.clear();
  return;

}  // end 'ResetVectors()'

// end ------------------------------------------------------------------------
