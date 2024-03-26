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



// type definitions -----------------------------------------------------------

typedef std::pair<float, float>                 BinRange;
typedef std::pair<uint32_t, BinRange>           BinDef;
typedef std::tuple<std::string, BinDef>         HistDef1D;
typedef std::tuple<std::string, BinDef, BinDef> HistDef2D;



// TrackJetQAMakerHistDef definition ------------------------------------------

struct TrackJetQAMakerHistDef {

  enum Var {
    Adc,
    ZBin,
    PhiBin,
    Layer,
    Phi,
    Eta,
    Ene
  };

  // no. of bins
  //   - FIXME the phi/z bin binning needs
  //     some more thought...
  uint32_t nAdcBins    = 101;
  uint32_t nZBinBins   = 101;
  uint32_t nPhiBinBins = 101;
  uint32_t nLayerBins  = 101;
  uint32_t nPhiBins    = 180;
  uint32_t nEtaBins    = 180;
  uint32_t nEneBins    = 1010;

  // bin ranges
  BinRange rAdcBins    = {-0.5, (float) nAdcBins + 0.5};
  BinRange rZBinBins   = {-0.5, (float) nZBinBins + 0.5};
  BinRange rPhiBinBins = {-0.5, (float) nPhiBinBins + 0.5};
  BinRange rLayerBins  = {-0.5, (float) nLayerBins + 0.5};
  BinRange rPhiBins    = {-3.15, 3.15};
  BinRange rEtaBins    = {-4.0, 4.0};
  BinRange rEneBins    = {-0.5, 100.5};

  // construct list of binnings
  std::vector<BinDef> GetVecHistBins() {

    std::vector<BinDef> vecHistBins = {
      std::make_pair(nAdcBins,    rAdcBins),
      std::make_pair(nZBinBins,   rZBinBins),
      std::make_pair(nPhiBinBins, rPhiBinBins),
      std::make_pair(nLayerBins,  rLayerBins),
      std::make_pair(nPhiBins,    rPhiBins),
      std::make_pair(nEtaBins,    rEtaBins),
      std::make_pair(nEneBins,    rEneBins)
    };
    return vecHistBins;

  }  // end 'GetVecHistBins()'

};  // end TrackJetQAMakerHistDef

#endif

// end ------------------------------------------------------------------------

