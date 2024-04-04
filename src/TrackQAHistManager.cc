// ----------------------------------------------------------------------------
// 'TrackQAHistManager.cc'
// Derek Anderson
// 03.25.2024
//
// A submodule for the TrackJetQAMaker module
// to generate QA plots for track hits
// ----------------------------------------------------------------------------

#define TRACKJETQAMAKER_TRACKQAHISTMANAGER_CC

// submodule definition
#include "TrackQAHistManager.h"



// external methods -----------------------------------------------------------

void TrackQAHistManager::GetInfo(const SvtxTrack* track) {

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



// internal methods -----------------------------------------------------------

void TrackQAHistManager::FillHistograms(Type type, TrackQAContent& content) {

  // fill 1d histograms
  vecHist1D.at(type).at(H1D::Eta)  -> Fill(content.eta);
  vecHist1D.at(type).at(H1D::Phi)  -> Fill(content.phi);
  vecHist1D.at(type).at(H1D::Pt)   -> Fill(content.pt);
  vecHist1D.at(type).at(H1D::Qual) -> Fill(content.qual);

  // fill 2d histograms
  vecHist2D.at(type).at(H2D::EtaVsPhi) -> Fill(content.phi, content.eta);
  vecHist2D.at(type).at(H2D::PtVsQual) -> Fill(content.qual, content.pt);
  return;

}  //  end 'FillHistograms(Type, TrackQAContent&)'



void TrackQAHistManager::DefineHistograms() {

  // grab binning schemes
  std::vector<BinDef> vecBins = m_hist.GetVecHistBins();

  // set histogram types
  m_vecHistTypes.push_back( "All" );

  // define 1d histograms
  m_vecHistDef1D.push_back( std::make_tuple( "TrackEta",  vecBins.at(TrackJetQAMakerHistDef::Var::Eta)  ));
  m_vecHistDef1D.push_back( std::make_tuple( "TrackPhi",  vecBins.at(TrackJetQAMakerHistDef::Var::Phi)  ));
  m_vecHistDef1D.push_back( std::make_tuple( "TrackPt",   vecBins.at(TrackJetQAMakerHistDef::Var::Ene)  ));
  m_vecHistDef1D.push_back( std::make_tuple( "TrackQual", vecBins.at(TrackJetQAMakerHistDef::Var::Qual) ));

  // define 2d histograms
  m_vecHistDef2D.push_back(
    std::make_tuple(
      "TrackEtaVsPhi",
      vecBins.at(TrackJetQAMakerHistDef::Var::Phi),
      vecBins.at(TrackJetQAMakerHistDef::Var::Eta)
    )
  );
  m_vecHistDef2D.push_back(
    std::make_tuple(
      "TrackPtVsQual",
      vecBins.at(TrackJetQAMakerHistDef::Var::Qual),
      vecBins.at(TrackJetQAMakerHistDef::Var::Ene)
    )
  );
  return;

}  // end 'BuildHistograms()'

// end ------------------------------------------------------------------------
