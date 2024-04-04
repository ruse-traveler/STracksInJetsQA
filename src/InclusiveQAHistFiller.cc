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

#include "InclusiveQAHistFiller.h"



// external methods -----------------------------------------------------------

void Fill(PHCompositeNode* topNode) {

  GetNodes();

  /* TODO fill methods go here */
  return;

}  // end 'Fill(PHCompositeNode* topNode)'



// internal methods -----------------------------------------------------------

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

  // grab cluster map
  m_clustMap = findNode::getClass<TrkrClusterContainer>(topNode, "TRKR_CLUSTER");
  if (!m_clustMap) {
    std::cerr << PHWHERE << ": PANIC: couldn't grab cluster map from node tree!" << std::endl;
    assert(m_clustMap);
  }
  return;

}  // end 'GetNodes(PHCompositeNode*)'



void InclusiveQAHistFiller::FillHitQAHists(PHCompositeNode* topNode) {

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

}  // end 'FillHitQAHistsPHCompositeNode*)'



void InclusiveQAHistFiller::FillClustQAHists(PHCompositeNode* topNode) {

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

}  // end 'Process(PHCompositeNode*)'

// end ------------------------------------------------------------------------

