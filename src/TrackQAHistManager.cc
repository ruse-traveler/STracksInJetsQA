// ----------------------------------------------------------------------------
// 'TrackQAHistManager.cc'
// Derek Anderson
// 03.25.2024
//
// A submodule for the TracksInJetsQAMaker module
// to generate QA plots for track hits
// ----------------------------------------------------------------------------

#define TRACKJETQAMAKER_TRACKQAHISTMANAGER_CC

// submodule definition
#include "TrackQAHistManager.h"



// public methods -------------------------------------------------------------

void TrackQAHistManager::GetInfo(SvtxTrack* track) {

  // collect track info
  TrackQAContent content = {
    .eta  = track -> get_eta(),
    .phi  = track -> get_phi(),
    .pt   = track -> get_pt(),
    .qual = track -> get_quality()
  };

  // fill histograms
  FillHistograms(Type::All, content);
  return;

}  // end 'GetInfo(SvtxTrack*)'



// private methods ------------------------------------------------------------

void TrackQAHistManager::FillHistograms(const int type, TrackQAContent& content) {

  // fill 1d histograms
  m_vecHist1D.at(type).at(H1D::Eta)  -> Fill(content.eta);
  m_vecHist1D.at(type).at(H1D::Phi)  -> Fill(content.phi);
  m_vecHist1D.at(type).at(H1D::Pt)   -> Fill(content.pt);
  m_vecHist1D.at(type).at(H1D::Qual) -> Fill(content.qual);

  // fill 2d histograms
  m_vecHist2D.at(type).at(H2D::EtaVsPhi) -> Fill(content.phi, content.eta);
  m_vecHist2D.at(type).at(H2D::PtVsQual) -> Fill(content.qual, content.pt);
  return;

}  //  end 'FillHistograms(Type, TrackQAContent&)'



void TrackQAHistManager::DefineHistograms() {

  // grab binning schemes
  std::vector<BinDef> vecBins = m_hist.GetVecHistBins();

  // set histogram types
  m_vecHistTypes.push_back( "All" );

  // define 1d histograms
  m_vecHistDef1D.push_back( std::make_tuple( "TrackEta",  vecBins.at(TracksInJetsQAMakerHistDef::Var::Eta)  ));
  m_vecHistDef1D.push_back( std::make_tuple( "TrackPhi",  vecBins.at(TracksInJetsQAMakerHistDef::Var::Phi)  ));
  m_vecHistDef1D.push_back( std::make_tuple( "TrackPt",   vecBins.at(TracksInJetsQAMakerHistDef::Var::Ene)  ));
  m_vecHistDef1D.push_back( std::make_tuple( "TrackQual", vecBins.at(TracksInJetsQAMakerHistDef::Var::Qual) ));

  // define 2d histograms
  m_vecHistDef2D.push_back(
    std::make_tuple(
      "TrackEtaVsPhi",
      vecBins.at(TracksInJetsQAMakerHistDef::Var::Phi),
      vecBins.at(TracksInJetsQAMakerHistDef::Var::Eta)
    )
  );
  m_vecHistDef2D.push_back(
    std::make_tuple(
      "TrackPtVsQual",
      vecBins.at(TracksInJetsQAMakerHistDef::Var::Qual),
      vecBins.at(TracksInJetsQAMakerHistDef::Var::Ene)
    )
  );
  return;

}  // end 'BuildHistograms()'

// end ------------------------------------------------------------------------
