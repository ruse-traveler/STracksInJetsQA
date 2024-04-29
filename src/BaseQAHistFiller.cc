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

BaseQAHistFiller::BaseQAHistFiller(
  TracksInJetsQAMakerConfig& config,
  TracksInJetsQAMakerHistDef& hist
) {

  // grab utilities
  m_config = config;
  m_hist   = hist;

  // initialize managers
  if (m_config.doHitQA)   m_hitManager   = std::make_unique<HitQAHistManager>(m_config, m_hist);
  if (m_config.doClustQA) m_clustManager = std::make_unique<ClustQAHistManager>(m_config, m_hist);
  if (m_config.doTrackQA) m_trackManager = std::make_unique<TrackQAHistManager>(m_config, m_hist);
  if (m_config.doJetQA)   m_jetManager   = std::make_unique<JetQAHistManager>(m_config, m_hist);

}  // end ctor()'



BaseQAHistFiller::~BaseQAHistFiller() {

  // remove dangling pointers
  if (m_actsGeom) {
    delete m_actsGeom;
    m_actsGeom = NULL;
  }
  if (m_hitMap) {
    delete m_hitMap;
    m_hitMap = NULL;
  }
  if (m_clustMap) {
    delete m_clustMap;
    m_clustMap = NULL;
  }
  if (m_trkMap) {
    delete m_trkMap;
    m_trkMap = NULL;
  }
  if (m_jetMap) {
    delete m_jetMap;
    m_jetMap = NULL;
  }

}  // end dtor



// public methods -------------------------------------------------------------

void BaseQAHistFiller::MakeHistograms(std::string label) {

  // initialize relevant submodules
  if (m_config.doHitQA)   m_hitManager   -> MakeHistograms(label);
  if (m_config.doClustQA) m_clustManager -> MakeHistograms(label);
  if (m_config.doTrackQA) m_trackManager -> MakeHistograms(label);
  if (m_config.doJetQA)   m_jetManager   -> MakeHistograms(label);
  return;

}  // end 'MakeHistograms(std::string)'



void BaseQAHistFiller::SaveHistograms(TFile* outFile, std::string outDirName) {

  TDirectory* outDir = outFile -> mkdir(outDirName.data());
  if (!outDir) {
    std::cerr << PHWHERE << ": PANIC: unable to make output directory!" << std::endl;
    assert(outDir);
  }

  if (m_config.doHitQA)   m_hitManager   -> SaveHistograms(outDir, m_config.hitOutDir);
  if (m_config.doClustQA) m_clustManager -> SaveHistograms(outDir, m_config.clustOutDir);
  if (m_config.doTrackQA) m_trackManager -> SaveHistograms(outDir, m_config.trackOutDir);
  if (m_config.doJetQA)   m_jetManager   -> SaveHistograms(outDir, m_config.jetOutDir);
  return;

}  // end 'SaveHistograms(TFile*, std::string)'



// private methods ------------------------------------------------------------

void BaseQAHistFiller::GetNodes(PHCompositeNode* topNode) {

  // grab necessary jet nodes
  if (m_config.doJetQA) {
    m_jetMap = findNode::getClass<JetContainer>(topNode, m_config.jetInNode.data());
    if (!m_jetMap) {
      std::cerr << PHWHERE << ": PANIC: couldn't grab jet map from node tree!" << std::endl;
      assert(m_jetMap);
    }
  }

  // grab necessary track nodes
  if (m_config.doTrackQA) {
    m_trkMap = findNode::getClass<SvtxTrackMap>(topNode, "SvtxTrackMap");
    if (!m_trkMap) {
      std::cerr << PHWHERE << ": PANIC: couldn't grab track map from node tree!" << std::endl;
      assert(m_trkMap);
    }
  }

  // grab necessary cluster nodes
  if (m_config.doClustQA) {

    m_actsGeom = findNode::getClass<ActsGeometry>(topNode, "ActsGeometry");
    if (!m_actsGeom) {
      std::cerr << PHWHERE << ": PANIC: couldn't grab ACTS geometry from node tree!" << std::endl;
      assert(m_actsGeom);
    }

    m_clustMap = findNode::getClass<TrkrClusterContainer>(topNode, "TRKR_CLUSTER");
    if (!m_clustMap) {
      std::cerr << PHWHERE << ": PANIC: couldn't grab cluster map from node tree!" << std::endl;
      assert(m_clustMap);
    }
  }

  // grab necessary hit nodes
  if (m_config.doHitQA) {
    m_hitMap = findNode::getClass<TrkrHitSetContainer>(topNode, "TRKR_HITSET");
    if (!m_hitMap) {
      std::cerr << PHWHERE << ": PANIC: couldn't grab hit map from node tree!" << std::endl;
      assert(m_hitMap);
    }
  }
  return;

}  // end 'GetNodes(PHCompositeNode*)'

// end ------------------------------------------------------------------------
