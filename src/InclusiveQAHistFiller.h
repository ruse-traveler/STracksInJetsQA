// ----------------------------------------------------------------------------
// 'InclusiveQAHistFiller.h'
// Derek Anderson
// 04.03.2024
//
// A submodule for the TracksInJetsQAMaker F4A module
// to produce QA histograms for tracks and more in
// jets
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKER_INCLUSIVEQAHISTFILLER_H
#define TRACKSINJETSQAMAKER_INCLUSIVEQAHISTFILLER_H

// c+ utilities
#include <cassert>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHCompositeNode.h>
// tracking libraries
#include <trackbase/TrkrHit.h>
#include <trackbase/TpcDefs.h>
#include <trackbase/InttDefs.h>
#include <trackbase/MvtxDefs.h>
#include <trackbase/TrkrDefs.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrCluster.h>
#include <trackbase/ActsGeometry.h>
#include <trackbase/TrkrHitSetContainer.h>
#include <trackbase/TrkrHitSetContainer.h>
#include <trackbase/TrkrClusterContainer.h>
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
// jet libraries
#include <jetbase/Jet.h>
#include <jetbase/JetContainer.h>
// submodule definitions
#include "BaseQAHistFiller.h"



// InclusiveQAHistFiller ------------------------------------------------------

class InclusiveQAHistFiller : public BaseQAHistFiller {

  public:

    // ctor/dtor
    InclusiveQAHistFiller() : BaseQAHistFiller() {};
    ~InclusiveQAHistFiller() : ~BaseQAHistFiller() {};

    // inherited external methods
    void Fill(PHCompositeNode* topNode) override;

  private:

    // internal methods
    void FillHitQAHists();
    void FillClustQAHists();
    void FillTrackQAHists();
    void FillJetQAHists();

    // inherited internal methods
    void GetNodes(PHCompositeNode* topNode) override;

    // necessary dst nodes
    ActsGeometry*         m_actsGeom = NULL;
    TrkrHitSetContainer*  m_hitMap   = NULL;
    TrkrClusterContainer* m_clustMap = NULL;
    SvtxTrackMap*         m_trkMap   = NULL;
    JetContainer*         m_jetMap   = NULL;

};  // end InclusiveQAHistFiller

#endif

// end ------------------------------------------------------------------------
