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

void InJetQAHistFiller::Fill(PHCompositeNode* topNode) {

  GetNodes(topNode);

  if (m_config.doJetQA) FillJetQAHists();
  return;

}  // end 'Fill(PHCompositeNode* topNode)'



// internal methods -----------------------------------------------------------

void InJetQAHistFiller::GetCstTracks(Jet* jet, PHCompositeNode* topNode) {

  // loop over consituents
  auto csts = jet -> get_comp_vec();
  for (
    auto cst = csts.begin();
    cst != csts.end();
    ++cst
  ) {

    // ignore cst if non-relevent type
    const uint32_t src = cst -> first;
    if ( IsCstNotRelevant(src) ) continue;

    // if track, add to list
    if (src == Jet::SRC::TRACK) {
      m_trksInJet.push_back( m_trkMap -> get(cst -> second) );
    }

    // if pfo w/ track info, grab track and add it to list
    if (src == Jet::SRC::PARTICLE) {
      PFObject*  pfo   = GetPFObject(cst -> second, topNode);
      SvtxTrack* track = GetTrkFromPFO(pfo);
      if (track) {
        m_trksInJet.push_back( track );
      }
    }
  }  // end cst loop
  return;

}  // end 'GetCstTracks(Jet* jet, PHCompositeNode* topNode)'



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

  // grab track map from node tree
  m_trkMap = findNode::getClass<SvtxTrackMap>(topNode, "SvtxTrackMap");
  if (!m_trkMap) {
    std::cerr << PHWHERE << ": PANIC: couldn't grab track map from node tree!" << std::endl;
    assert(m_trkMap);
  }
  return;

}  // end 'GetNodes(PHCompositeNode*)'



void InJetQAHistFiller::GetPFNode(PHCompositeNode* topNode) {

  m_flowStore = findNode::getClass<ParticleFlowElementContainer>(topNode, "ParticleFlowElements");
  if (!m_flowStore) {
    std::cerr << PHWHERE << ": PANIC: Couldn't grab particle flow container from node tree!" << std::endl;
    assert(m_flowStore);
  }
  return;

}  // end 'GetPFNode(PHCompositeNode*)'



bool InJetQAHistFiller::IsCstNotRelevant(const uint32_t type) {

  const bool isVoid   = (type == Jet::SRC::VOID);
  const bool isImport = (type == Jet::SRC::HEPMC_IMPORT);
  const bool isProbe  = (type == Jet::SRC::JET_PROBE);
  return (isVoid || isImport || isProbe);

}  // end 'IsCstNotRelevant(uint32_t)'



PFObject* InJetQAHistFiller::GetPFObject(const uint32_t id, PHCompositeNode* topNode) {

  // pointer to pfo 
  PFObject* pfoToFind = NULL;

  // grab pf node if needed
  if (!m_flowStore) GetPFNode(topNode);

  // loop over pfos
  for (
      ParticleFlowElementContainer::ConstIterator itFlow = m_flowStore -> getParticleFlowElements().first;
      itFlow != m_flowStore -> getParticleFlowElements().second;
      ++itFlow
  ) {

    // get pfo
    PFObject* pfo = itFlow -> second;

    // if has provided id, set pointer and exit
    if (id == pfo -> get_id()) {
      pfoToFind = pfo;
      break;
    }
  }  // end pfo loop
  return pfoToFind;

}  // end 'GetPFObject(uint32_t, PHCompositeNode*)'



SvtxTrack* InJetQAHistFiller::GetTrkFromPFO(PFObject* pfo) {

  // pointer to track
  SvtxTrack* track = NULL;

  // if pfo has track, try to grab
  const auto type = pfo -> get_type();
  if (
    (type == ParticleFlowElement::PFLOWTYPE::MATCHED_CHARGED_HADRON) ||
    (type == ParticleFlowElement::PFLOWTYPE::UNMATCHED_CHARGED_HADRON)
  ) {
    track = pfo -> get_track();
  }
  return track;

}  // end 'GetTrkFromPFO(PFObject*)'

// end ------------------------------------------------------------------------
