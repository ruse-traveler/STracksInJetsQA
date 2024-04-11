// ----------------------------------------------------------------------------
// 'InJetQAHistFiller.cc'
// Derek Anderson
// 04.03.2024
//
// A submodule for the TracksInJetsQAMaker F4A module
// to produce QA histograms for tracks and more in
// jets
// ----------------------------------------------------------------------------

#define TRACKSINJETSQAMAKER_INJETQAHISTFILLER_CC

// submodule definition
#include "InJetQAHistFiller.h"



// external methods -----------------------------------------------------------

void Fill(PHCompositeNode* topNode) {

  GetNodes(topNode);

  if (m_config.doJetQA) FillJetQAHists();
  return;

}  // end 'Fill(PHCompositeNode* topNode)'



// internal methods -----------------------------------------------------------

void InJetQAHistFiller::FillJetQAHists() {

  /* OLD CODE FOR REFERENCE
    // loop over jet constituents
    auto csts = jet -> get_comp_vec();
    for (
      auto cst = csts.begin();
      cst != csts.end();
      ++cst
    ) {

      // skip if cst is not a track
      uint32_t src = cst -> first;
      if (src != Jet::SRC::TRACK) continue;

      // grab track
      SvtxTrack* track = m_trkMap -> get(cst -> second);

      // collect cst info
      CstQAContent cstContent {
        .ptCst   = track -> get_pt(),
        .qualCst = track -> get_quality()
      };

      // fill histograms
      FillHistograms(Type::All, cstContent);

    }  // end cst loop
  */
  return;

}  // end 'FillJetQAHists()'



void InJetQAHistFiller::GetNodes(PHCompositeNode* topNode) {

  // grab jet map from node tree
  m_jetMap = findNode::getClass<JetContainer>(topNode, "AntiKt_Track_r04");
  if (!m_jetMap) {
    std::cerr << PHWHERE << ": PANIC: couldn't grab jet map from node tree!" << std::endl;
    assert(m_jetMap);
  }
  return;

}  // end 'GetNodes(PHCompositeNode*)'

// end ------------------------------------------------------------------------
