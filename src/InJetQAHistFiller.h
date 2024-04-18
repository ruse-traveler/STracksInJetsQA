// ----------------------------------------------------------------------------
// 'InJetQAHistFiller.h'
// Derek Anderson
// 04.03.2024
//
// A submodule for the TracksInJetsQAMaker F4A module
// to produce QA histograms for tracks and more in
// jets
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKER_INJETQAHISTFILLER_H
#define TRACKSINJETSQAMAKER_INJETQAHISTFILLER_H

// c+ utilities
#include <vector>
#include <cassert>
// root libraries
#include <TMath.h>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHCompositeNode.h>
// tracking libraries
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
// calorimetry libraries
#include <calobase/RawTowerGeomContainer.h>
// particle flow libraries
#include <particleflowreco/ParticleFlowElement.h>
#include <particleflowreco/ParticleFlowElementContainer.h>
// jet libraries
#include <jetbase/Jet.h>
#include <jetbase/JetContainer.h>
// submodule definitions
#include "BaseQAHistFiller.h"



// type definition ------------------------------------------------------------

typedef ParticleFlowElement PFObject;
typedef ParticleFlowElementContainer PFObjectStore;



// InJetQAHistFiller ----------------------------------------------------------

class InJetQAHistFiller : public BaseQAHistFiller {

  public:

    // ctor/dtor
    InJetQAHistFiller() : BaseQAHistFiller() {};
    ~InJetQAHistFiller() {};

    // inherited public methods
    void Fill(PHCompositeNode* topNode) override;

  private:

    // private methods
    void       FillJetQAHists(PHCompositeNode* topNode);
    void       GetPFNode(PHCompositeNode* topNode);
    void       GetGeomNode(const int geometry, PHCompositeNode* topNode);
    void       GetCstTracks(Jet* jet, PHCompositeNode* topNode);
    void       GetNonCstTracks(Jet* jet, PHCompositeNode* topNode);
    bool       IsCstNotRelevant(const uint32_t type);
    bool       IsTrkInList(const uint32_t id);
    double     GetTrackJetDist(SvtxTrack* track, Jet* jet);
    PFObject*  GetPFObject(const uint32_t id, PHCompositeNode* topNode);
    SvtxTrack* GetTrkFromPFO(PFObject* pfo);

    // inherited private methods
    void GetNodes(PHCompositeNode* topNode) override;

    // necessary dst nodes
    JetContainer*  m_jetMap    = NULL;
    SvtxTrackMap*  m_trkMap    = NULL;
    PFObjectStore* m_flowStore = NULL;

    // for tracks in jet
    std::vector<SvtxTrack*> m_trksInJet;

};  // end InJetQAHistFiller

#endif

// end ------------------------------------------------------------------------
