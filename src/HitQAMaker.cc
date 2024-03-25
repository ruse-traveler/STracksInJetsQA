// ----------------------------------------------------------------------------
// 'HitQAMaker.cc'
// Derek Anderson
// 03.25.2024
//
// A plugin for the TracksInJetsQAMaker module
// to generate QA plots for track hits
// ----------------------------------------------------------------------------

#define TRACKSINJETSQAMAKER_HITQAMAKER_CC

// plugin definition
#include "HitQAMaker.h"



// public methods -------------------------------------------------------------

void HitQAMaker::Init(TrackJetQAMakerHistDef& hist) {

  /* TODO histogram initialization goes here */
  return;

}  // end 'Init(TrackJetQAMakerHistDef& hist)'



void HitQAMaker::Process(PHCompositeNode* topNode) {


  // grab hit map from node tree
  m_hitMap = findNode::getClass<TrkrHitSetContainer>(topNode, "TRKR_HITSET");
  if (!m_hitMap) {
    std::cerr << PHWHERE << " PANIC: couldn't grab hit map from node tree!" << std::endl;
  }

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

/* TODO put in checks
      // check which subsystem this hit is in
      const bool isInMvtx = false;
      const bool isInIntt = false;
      const bool isInTpc  = false;
      const bool isInTpot = false;
*/

      // collect hit info
      HitQAContent content {
        .layr = TrkrDefs::getLayer(setKey),
        .ene  = hit -> getEnergy(),
        .id   = hitKey,
        .adc  = hit -> getAdc()
      };
/* TODO make plugins friend of module 
      std::cout << "CHECK hit content:\n"
                << "  id   = " << content.id   << "\n"
                << "  adc  = " << content.adc  << "\n"
                << "  layr = " << content.layr << "\n"
                << "  ene  = " << content.ene
                << std::endl;
*/

    }  // end hit loop
  }  // end hit set loop
  return;

}  // end 'Process(PHCompositeNode*)'



void HitQAMaker::End(TFile* outFile) {

  /* TODO histogram saving goes here */
  return;

}  // end 'End(TFile*)'

// end ------------------------------------------------------------------------
