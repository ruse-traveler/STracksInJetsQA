// ----------------------------------------------------------------------------
// 'HitQAHistManager.cc'
// Derek Anderson
// 03.25.2024
//
// A submodule for the TracksInJetsQAMaker module
// to generate QA plots for track hits
// ----------------------------------------------------------------------------

#define TRACKSINJETSQAMAKER_HITQAHISTMANAGER_CC

// submodule definition
#include "HitQAHistManager.h"



// external methods -----------------------------------------------------------

void HitQAHistManager::GetInfo(TrkrHit* hit, TrkrDefs::hitsetkey& setKey, TrkrDefs::hitkey& hitKey) {

  // check which subsystem hit is in
  const uint16_t layer  = TrkrDefs::getLayer(setKey);
  const bool     isMvtx = m_help.IsInMvtx(layer);
  const bool     isIntt = m_help.IsInIntt(layer);
  const bool     isTpc  = m_help.IsInTpc(layer);

  // get phi and z values
  //   - FIXME should be more explicit about
  //     row/column vs. z/phi...
  uint16_t phiBin = std::numeric_limits<uint16_t>::max();
  uint16_t zBin   = std::numeric_limits<uint16_t>::max();
  if (isMvtx) {
    phiBin = MvtxDefs::getCol(hitKey);
    zBin   = MvtxDefs::getRow(hitKey);
  } else if (isIntt) {
    phiBin = InttDefs::getCol(hitKey);
    zBin   = InttDefs::getRow(hitKey);
  } else if (isTpc) {
    phiBin = TpcDefs::getPad(hitKey);
    /* TODO put in z calculation */
  }

  // collect hit info
  HitQAContent content {
    .ene    = hit -> getEnergy(),
    .adc    = hit -> getAdc(),
    .layer  = layer,
    .phiBin = phiBin,
    .zBin   = zBin
  };

  // fill histograms
  FillHistograms(Type::All, content);
  if (isMvtx) {
    FillHistograms(Type::Mvtx, content);
  } else if (isIntt) {
    FillHistograms(Type::Intt, content);
  } else if (isTpc) {
    FillHistograms(Type::Tpc, content);
  }
  return;

}  // end 'GetInfo(TrkrHit*, TrkrDefs::hitsetkey&, TrkrDefs::hitkey&)'



// internal methods -----------------------------------------------------------

void HitQAHistManager::FillHistograms(const int type, HitQAContent& content) {

  // fill 1d histograms
  m_vecHist1D.at(type).at(H1D::Ene)    -> Fill(content.ene);
  m_vecHist1D.at(type).at(H1D::ADC)    -> Fill(content.adc);
  m_vecHist1D.at(type).at(H1D::Layer)  -> Fill(content.layer);
  m_vecHist1D.at(type).at(H1D::PhiBin) -> Fill(content.phiBin);
  m_vecHist1D.at(type).at(H1D::ZBin)   -> Fill(content.zBin);

  // fill 2d histograms
  m_vecHist2D.at(type).at(H2D::EneVsLayer) -> Fill(content.layer, content.ene);
  m_vecHist2D.at(type).at(H2D::EneVsADC)   -> Fill(content.adc, content.ene);
  m_vecHist2D.at(type).at(H2D::PhiVsZBin)  -> Fill(content.zBin, content.phiBin);
  return;

}  //  end 'FillHistograms(Type, HitQAContent&)'



void HitQAHistManager::DefineHistograms() {

  // grab binning schemes
  std::vector<BinDef> vecBins = m_hist.GetVecHistBins();

  // set histogram types
  m_vecHistTypes.push_back( "Mvtx" );
  m_vecHistTypes.push_back( "Intt" );
  m_vecHistTypes.push_back( "Tpc"  );
  m_vecHistTypes.push_back( "All"  );

  // define 1d histograms
  m_vecHistDef1D.push_back( std::make_tuple( "HitEne",    vecBins.at(TracksInJetsQAMakerHistDef::Var::Ene)    ));
  m_vecHistDef1D.push_back( std::make_tuple( "HitAdc",    vecBins.at(TracksInJetsQAMakerHistDef::Var::Adc)    ));
  m_vecHistDef1D.push_back( std::make_tuple( "HitLayer",  vecBins.at(TracksInJetsQAMakerHistDef::Var::Layer)  ));
  m_vecHistDef1D.push_back( std::make_tuple( "HitPhiBin", vecBins.at(TracksInJetsQAMakerHistDef::Var::PhiBin) ));
  m_vecHistDef1D.push_back( std::make_tuple( "HitZBin",   vecBins.at(TracksInJetsQAMakerHistDef::Var::ZBin)   ));

  // define 2d histograms
  m_vecHistDef2D.push_back(
    std::make_tuple(
      "HitEneVsLayer",
      vecBins.at(TracksInJetsQAMakerHistDef::Var::Layer),
      vecBins.at(TracksInJetsQAMakerHistDef::Var::Ene)
    )
  );
  m_vecHistDef2D.push_back(
    std::make_tuple(
      "HitEneVsADC",
      vecBins.at(TracksInJetsQAMakerHistDef::Var::Adc),
      vecBins.at(TracksInJetsQAMakerHistDef::Var::Ene)
    )
  );
  m_vecHistDef2D.push_back(
    std::make_tuple(
      "HitPhiVsZBin",
      vecBins.at(TracksInJetsQAMakerHistDef::Var::ZBin),
      vecBins.at(TracksInJetsQAMakerHistDef::Var::PhiBin)
    )
  );
  return;

}  // end 'DefineHistograms()'

// end ------------------------------------------------------------------------
