// ----------------------------------------------------------------------------
// 'InclusiveQAHistFiller.cc'
// Derek Anderson
// 04.03.2024
//
// A submodule for the TracksInJetsQAMaker F4A module
// to produce QA histograms for tracks and more in
// jets
// ----------------------------------------------------------------------------

#define TRACKSINJETSQAMAKER_INCLUSIVEQAHISTFILLER_CC

// submodule definition
#include "InclusiveQAHistFiller.h"



// external methods -----------------------------------------------------------

void InclusiveQAHistFiller::Fill(PHCompositeNode* topNode) {

  GetNodes(topNode);

  if (m_config.doHitQA)   FillHitQAHists();
  if (m_config.doClustQA) FillClustQAHists();
  if (m_config.doTrackQA) FillTrackQAHists();
  if (m_config.doJetQA)   FillJetQAHists();
  return;

}  // end 'Fill(PHCompositeNode* topNode)'



// internal methods -----------------------------------------------------------

void InclusiveQAHistFiller::FillHitQAHists() {

  // loop over hit sets
  TrkrHitSetContainer::ConstRange hitSets = m_hitMap -> getHitSets();
  for (
    TrkrHitSetContainer::ConstIterator itSet = hitSets.first;
    itSet != hitSets.second;
    ++itSet
  ) {

    // grab hit set
    TrkrDefs::hitsetkey setKey = itSet -> first;
    TrkrHitSet*         set    = itSet -> second;

    // loop over all hits in hit set
    TrkrHitSet::ConstRange hits = set -> getHits();
    for (
      TrkrHitSet::ConstIterator itHit = hits.first;
      itHit != hits.second;
      ++itHit
    ) {

      // grab hit
      TrkrDefs::hitkey hitKey = itHit -> first;
      TrkrHit*         hit    = itHit -> second;

      // grab info and fill histograms
      m_hitManager -> GetInfo(hit, setKey, hitKey);

    }  // end hit loop
  }  // end hit set loop
  return;

}  // end 'FillHitQAHists()'



void InclusiveQAHistFiller::FillClustQAHists() {

  // loop over hit sets
  TrkrHitSetContainer::ConstRange hitSets = m_hitMap -> getHitSets();
  for (
    TrkrHitSetContainer::ConstIterator itSet = hitSets.first;
    itSet != hitSets.second;
    ++itSet
  ) {

    // loop over clusters associated w/ hit set
    TrkrDefs::hitsetkey              setKey   = itSet      -> first;
    TrkrClusterContainer::ConstRange clusters = m_clustMap -> getClusters(setKey);
    for (
      TrkrClusterContainer::ConstIterator itClust = clusters.first;
      itClust != clusters.second;
      ++itClust
    ) {

      // grab cluster
      TrkrDefs::cluskey clustKey = itClust    -> first;
      TrkrCluster*      cluster  = m_clustMap -> findCluster(clustKey);

      // grab cluster info
      m_clustManager -> GetInfo(cluster, clustKey, m_actsGeom);

    }  // end cluster loop
  }  // end hit set loop
  return;

}  // end 'Process()'



void InclusiveQAHistFiller::FillTrackQAHists() {

  // loop over tracks
  for (
    SvtxTrackMap::Iter itTrk = m_trkMap -> begin();
    itTrk != m_trkMap -> end();
    ++itTrk
  ) {

    // grab track
    SvtxTrack* track = itTrk -> second;

    // grab info and fill histograms
    m_trackManager -> GetInfo(track);

  }  // end track loop
  return;

}  // end 'Process()'



void InclusiveQAHistFiller::FillJetQAHists() {

  // loop over jets
  for (
    uint64_t iJet = 0;
    iJet < m_jetMap -> size();
    ++iJet
  ) {

    // grab jet
    Jet* jet = m_jetMap -> get_jet(iJet);

    // grab info and fill histograms
    m_jetManager -> GetInfo(jet);

  }  // end track loop
  return;

}  // end 'FillJetQAHists()'



void InclusiveQAHistFiller::GetNodes(PHCompositeNode* topNode) {

  // grab acts geometry from node tree
  m_actsGeom = findNode::getClass<ActsGeometry>(topNode, "ActsGeometry");
  if (!m_actsGeom) {
    std::cerr << PHWHERE << ": PANIC: couldn't grab ACTS geometry from node tree!" << std::endl;
    assert(m_actsGeom);
  }

  // grab hit map from node tree
  m_hitMap = findNode::getClass<TrkrHitSetContainer>(topNode, "TRKR_HITSET");
  if (!m_hitMap) {
    std::cerr << PHWHERE << ": PANIC: couldn't grab hit map from node tree!" << std::endl;
    assert(m_hitMap);
  }

  // grab cluster map from node tree
  m_clustMap = findNode::getClass<TrkrClusterContainer>(topNode, "TRKR_CLUSTER");
  if (!m_clustMap) {
    std::cerr << PHWHERE << ": PANIC: couldn't grab cluster map from node tree!" << std::endl;
    assert(m_clustMap);
  }

  // grab track map from node tree
  m_trkMap = findNode::getClass<SvtxTrackMap>(topNode, "SvtxTrackMap");
  if (!m_trkMap) {
    std::cerr << PHWHERE << ": PANIC: couldn't grab track map from node tree!" << std::endl;
    assert(m_trkMap);
  }

  // grab jet map from node tree
  m_jetMap = findNode::getClass<JetContainer>(topNode, "AntiKt_Track_r04");
  if (!m_jetMap) {
    std::cerr << PHWHERE << ": PANIC: couldn't grab jet map from node tree!" << std::endl;
    assert(m_jetMap);
  }
  return;

}  // end 'GetNodes(PHCompositeNode*)'

// end ------------------------------------------------------------------------

