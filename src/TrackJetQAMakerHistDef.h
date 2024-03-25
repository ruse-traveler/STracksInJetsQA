// ----------------------------------------------------------------------------
// 'TrackJetQAMakerHistDef.h'
// Derek Anderson
// 03.25.2024
//
// Configurable parameters for histograms (like binning, etc.)
// for the TracksInJetsQAMaker module.
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKERHISTDEF_H
#define TRACKSINJETSQAMAKERHISTDEF_H

// c++ utilities
#include <string>
#include <utility>



struct TrackJetQAMakerHistDef {

  enum class Var {
    Key,
    Adc,
    ZBin,
    PhiBin,
    Phi,
    Eta,
    Ene
  };

  // no. of bins
  uint32_t nKeyBins    = 10001;
  uint32_t nAdcBins    = 101;
  uint32_t nZBinBins   = 101;
  uint32_t nPhiBinBins = 101;
  uint32_t nPhiBins    = 180;
  uint32_t nEtaBins    = 180;
  uint32_t nEneBins    = 1010;

  // bin ranges
  std::pair<float, float> rKeyBins    = {-0.5, (float) nKeyBins + 0.5};
  std::pair<float, float> rAdcBins    = {-0.5, (float) nAdcBins + 0.5};
  std::pair<float, float> rZBinBins   = {-0.5, (float) nZBinBins + 0.5};
  std::pair<float, float> rPhiBinBins = {-0.5, (float) nPhiBinBins + 0.5};
  std::pair<float, float> rPhiBins    = {-3.15, 3.15};
  std::pair<float, float> rEtaBins    = {-4.0, 4.0};
  std::pair<float, float> rEneBins    = {-0.5, 100.5};

  // construct list of binnings
  std::vector<std::tuple<uint32_t, std::pair<float, float>>> GetVecHistBins() {

    std::vector<std::tuple<uint32_t, std::pair<float, float>>> vecHistBins = {
      std::make_pair(nKeyBins, rKeyBins),
      std::make_pair(nAdcBins, rAdcBins),
      std::make_pair(nZBinBins, rZBinBins),
      std::make_pair(nPhiBinBins, rPhiBinBins),
      std::make_pair(nPhiBins, rPhiBins),
      std::make_pair(nEtaBins, rEtaBins),
      std::make_pair(nEneBins, rEneBins)
    };
    return vecHistBins;

  }  // end 'GetVecHistBins()'

};  // end TrackJetQAMakerHistDef

#endif

// end ------------------------------------------------------------------------

