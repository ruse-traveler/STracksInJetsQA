// ----------------------------------------------------------------------------
// 'BaseQAHistFiller.cc'
// Derek Anderson
// 04.11.2024
//
// A submodule for the TracksInJetsQAMaker F4A module
// to produce QA histograms for tracks and more in
// jets
// ----------------------------------------------------------------------------

#define TRACKSINJETSQAMAKER_BASEQAHISTFILLER_CC

#include "BaseQAHistFiller.h"



// ctor/dtor ------------------------------------------------------------------

BaseQAHistFiller::BaseQAHistFiller() {

  /* nothing to do */

}  // end ctor



BaseQAHistFiller::~BaseQAHistFiller() {

  /* nothing to do */

}  // end dtor



// external methods -----------------------------------------------------------

void BaseQAHistFiller::Init(
  TracksInJetsQAMakerConfig& config,
  TracksInJetsQAMakerHelper& helper,
  TracksInJetsQAMakerHistDef& hist
) {

  // set module utilities
  m_config = config;
  m_help   = help;
  m_hist   = hist;

  // initialize relevant submodules
  if (m_config.doHitQA) {
    m_hitManager = std::make_unique<HitQAHistManager>();
    m_hitManager -> Init(m_help, m_hist);
  }
  if (m_config.doClustQA) {
    m_clustManager = std::make_unique<ClustQAHistManager>();
    m_clustManager -> Init(m_help, m_hist);
  }
  if (m_config.doTrackQA) {
    m_trackManager = std::make_unique<TrackQAHistManager>();
    m_trackManager -> Init(m_help, m_hist);
  }
  if (m_config.doJetQA) {
    m_jetManager = std::make_unique<JetQAHistManager>();
    m_jetManager -> Init(m_help, m_hist);
  }
  return;

}  // end 'Init(TracksInJetsQAMakerConfig&, TracksInJetsQAMakerHelper&, TracksInJetsQAMakerHistDef&)'



void BaseQAHistFiller::SaveHistograms(TFile* outFile) {

  TDirectory* outDir = outFile -> mkdir(m_config.inclusiveDir.data());
  if (!outDir) {
    std::cerr << PHWHERE << ": PANIC: unable to make output directory!" << std::endl;
    assert(outDir);
  }

  if (m_config.doHitQA)   m_hitManager   -> SaveHistograms(outDir, m_config.hitOutDir);
  if (m_config.doClustQA) m_clustManager -> SaveHistograms(outDir, m_config.clustOutDir);
  if (m_config.doTrackQA) m_trackManager -> SaveHistograms(outDir, m_config.trackOutDir);
  if (m_config.doJetQA)   m_jetManager   -> SaveHistograms(outDir, m_config.jetOutDir);
  return;

}  // end 'SaveHistograms(TFile*)'

// end ------------------------------------------------------------------------
