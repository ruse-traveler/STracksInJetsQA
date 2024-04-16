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

  FillJetQAHists(topNode);
  return;

}  // end 'Fill(PHCompositeNode* topNode)'



// internal methods -----------------------------------------------------------

void InJetQAHistFiller::FillJetQAHists(PHCompositeNode* topNode) {

  // loop over jets
  for (
    uint64_t iJet = 0;
    iJet < m_jetMap -> size();
    ++iJet
  ) {

    // grab jet
    Jet* jet = m_jetMap -> get_jet(iJet);

    // make sure track vector is clear
    m_trksInJet.clear();

    // get all tracks "in" a jet
    GetCstTracks(jet, topNode);
    GetNonCstTracks(jet, topNode);

    // grab info and fill histograms
    m_jetManager -> GetInfo(jet, m_trksInJet);

    /* TODO fill track, hit, clust histograms here
    for (SvtxTrack* track : m_trksInJet) {
      if (m_config.doTrackQA) FillTrackQAHists(track);
      if (m_config.doClustQA) FillClustQAHists(track);
      if (m_config.doHitQA)   FillHitQAHists(track);
    }
    */
  }  // end track loop
  return;

}  // end 'FillJetQAHists(PHCompositeNode*)'



void InJetQAHistFiller::GetPFNode(PHCompositeNode* topNode) {

  m_flowStore = findNode::getClass<ParticleFlowElementContainer>(topNode, "ParticleFlowElements");
  if (!m_flowStore) {
    std::cerr << PHWHERE << ": PANIC: Couldn't grab particle flow container from node tree!" << std::endl;
    assert(m_flowStore);
  }
  return;

}  // end 'GetPFNode(PHCompositeNode*)'



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

    // if cst is track, add to list
    if (src == Jet::SRC::TRACK) {
      m_trksInJet.push_back( m_trkMap -> get(cst -> second) );
    }

    // if pfo, grab track if needed
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



void InJetQAHistFiller::GetNonCstTracks(Jet* jet, PHCompositeNode* topNode) {

  // loop over tracks
  for (
    SvtxTrackMap::Iter itTrk = m_trkMap -> begin();
    itTrk != m_trkMap -> end();
    ++itTrk
  ) {

    // grab track
    SvtxTrack* track = itTrk -> second;

    // ignore tracks we've already added to the list
    if ( IsTrkInList(track -> get_id()) ) continue;

    // FIXME this can be improved!
    //   - jets don't necessarily have areas of
    //     pi*(Rjet)^2
    //   - it may be better to instead check
    //     if a track projection falls in
    //     a constituent tower/clsuter

    /* TODO
     *  get eta/phi of track, jet
     *  calculate dr
     *  if dr < tower/cluster dimensions
     *    add to list
     *  end
     */

  }  // end track loop
  return;

}  // end 'GetNonCstTracks(Jet* jet, PHCompositeNode* topNode)'



bool InJetQAHistFiller::IsCstNotRelevant(const uint32_t type) {

  const bool isVoid   = (type == Jet::SRC::VOID);
  const bool isImport = (type == Jet::SRC::HEPMC_IMPORT);
  const bool isProbe  = (type == Jet::SRC::JET_PROBE);
  return (isVoid || isImport || isProbe);

}  // end 'IsCstNotRelevant(uint32_t)'



bool InJetQAHistFiller::IsTrkInList(const uint32_t id) {

  bool isAdded = false;
  for (SvtxTrack* trkInJet : m_trksInJet) {
    if (id == trkInJet -> get_id() ) {
      isAdded = true;
      break;
    }
  }
  return isAdded;

}  // end 'IsTrkInList(uint32_t)'



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



void InJetQAHistFiller::GetNodes(PHCompositeNode* topNode) {

  // grab jet map from node tree
  //   - TODO make user configurable
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

// end ------------------------------------------------------------------------
