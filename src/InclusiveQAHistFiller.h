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
#include <string>
#include <cassert>
#include <utility>
// f4a libraries
#include <phool/PHCompositeNode.h>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
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
// submodule definitions
#include "HitQAHistManager.h"
#include "ClustQAHistManager.h"
#include "TrackQAHistManager.h"
#include "JetQAHistManager.h"



// InclusiveQAHistFiller ----------------------------------------------------------

class InclusiveQAHistFiller {

  public:

    // ctor/dtor
    InclusiveQAHistFiller()  {};
    ~InclusiveQAHistFiller() {};

    // external methods
    Init();
    Fill(PHCompositeNode* topNode);
    End();

  private:

    // internal methods
    //   - FIXME the hist fillers probably don't need PHCompositeNode
    GetNodes(PHCompositeNode* topNode);
    FillHitQAHists(PHCompositeNode* topNode);
    FillClustQAHists(PHCompositeNode* topNode);
    FillTrackQAHists(PHCompositeNode* topNode);

    // submodules to use
    std::unique_ptr<HitQAHistManager>   m_hitManager   = NULL;
    std::unique_ptr<ClustQAHistManager> m_clustManager = NULL;
    std::unique_ptr<TrackQAHistManager> m_trackManager = NULL;
    std::unique_ptr<JetQAHistManager>   m_jetManager   = NULL;

    // necessary dst nodes
    ActsGeometry*         m_actsGeom = NULL;
    TrkrHitSetContainer*  m_hitMap   = NULL;
    TrkrClusterContainer* m_clustMap = NULL;
    SvtxTrackMap*         m_trkMap   = NULL;

};  // end InclusiveQAHistFiller

#endif

// end ------------------------------------------------------------------------

