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
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHCompositeNode.h>
// tracking libraries
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
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

    // inherited external methods
    void Fill(PHCompositeNode* topNode) override;

  private:

    // internal methods
    void GetCstTracks(Jet* jet, PHCompositeNode* topNode);
    void FillJetQAHists(PHCompositeNode* topNode);

    // inherited internal methods
    void GetNodes(PHCompositeNode* topNode) override;

    // internal helper methods
    void       GetPFNode(PHCompositeNode* topNode);
    bool       IsCstNotRelevant(const uint32_t type);
    PFObject*  GetPFObject(const uint32_t id, PHCompositeNode* topNode);
    SvtxTrack* GetTrkFromPFO(PFObject* pfo);

    // necessary dst nodes
    JetContainer*  m_jetMap    = NULL;
    SvtxTrackMap*  m_trkMap    = NULL;
    PFObjectStore* m_flowStore = NULL;

    // for tracks in jet
    std::vector<SvtxTrack*> m_trksInJet;

};  // end InJetQAHistFiller

#endif

// end ------------------------------------------------------------------------
