// ----------------------------------------------------------------------------
// 'ClustQAHistManager.cc'
// Derek Anderson
// 03.25.2024
//
// A submodule for the TracksInJetsQAMaker module
// to generate QA plots for track clusters
// ----------------------------------------------------------------------------

#define TRACKSINJETSQAMAKER_CLUSTQAHISTMANAGER_CC

// submodule definition
#include "ClustQAHistManager.h"



// external methods -----------------------------------------------------------

void ClustQAHistManager::GetInfo(const TrkrCluster* cluster, const TrkrDefs::cluskey& clustKey, const ActsGeometry* actsGeom) {

  // check which subsystem cluster is in
  const uint16_t layer  = TrkrDefs::getLayer(clustKey);
  const bool     isMvtx = m_help.IsInMvtx(layer);
  const bool     isIntt = m_help.IsInIntt(layer);
  const bool     isTpc  = m_help.IsInTpc(layer);

  // get cluster position
  Acts::Vector3 actsPos = actsGeom -> getGlobalPosition(clustKey, cluster);

  // collect cluster info
  ClustQAContent content {
    .x = actsPos(0),
    .y = actsPos(1),
    .z = actsPos(2),
    .r = std::hypot( actsPos(0), actsPos(1) )
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

}  // end GetInfo(TrkrCluster*, TrkrDefs::cluskey&, ActsGeometry*)'



// internal methods -----------------------------------------------------------

void ClustQAHistManager::FillHistograms(Type type, ClustQAContent& content) {

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



void ClustQAHistManager::DefineHistograms() {

  // grab binning schemes
  std::vector<BinDef> vecBins = m_hist.GetVecHistBins();

  // set histogram types
  m_vecHistTypes.push_back( "Mvtx" );
  m_vecHistTypes.push_back( "Intt" );
  m_vecHistTypes.push_back( "Tpc"  );
  m_vecHistTypes.push_back( "All"  );

  // define 1d histograms
  m_vecHistDef1D.push_back( std::make_tuple( "ClustPosX", vecBins.at(TracksInJetsQAMakerHistDef::Var::PosXY) ));
  m_vecHistDef1D.push_back( std::make_tuple( "ClustPosY", vecBins.at(TracksInJetsQAMakerHistDef::Var::PosXY) ));
  m_vecHistDef1D.push_back( std::make_tuple( "ClustPosZ", vecBins.at(TracksInJetsQAMakerHistDef::Var::PosZ)  ));
  m_vecHistDef1D.push_back( std::make_tuple( "ClustPosR", vecBins.at(TracksInJetsQAMakerHistDef::Var::PosR)  ));

  // define 2d histograms
  m_vecHistDef2D.push_back(
    std::make_tuple(
      "ClustPosYvsX",
      vecBins.at(TracksInJetsQAMakerHistDef::Var::PosXY),
      vecBins.at(TracksInJetsQAMakerHistDef::Var::PosXY)
    )
  );
  m_vecHistDef2D.push_back(
    std::make_tuple(
      "ClustPosRvsZ",
      vecBins.at(TracksInJetsQAMakerHistDef::Var::PosZ),
      vecBins.at(TracksInJetsQAMakerHistDef::Var::PosR)
    )
  );
  return;

}  // end 'BuildHistograms()'

// end ------------------------------------------------------------------------
