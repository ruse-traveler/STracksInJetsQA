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
#include <utility>
// f4a libraries
#include <fun4all/PHCompositeNode.h>
// submodule definitions
#include "HitQAHistManager.h"
#include "ClustQAHistManager.h"
#include "TrackQAHistManager.h"
#include "JetQAHistManager.h"



// InclusiveQAHistFiller ----------------------------------------------------------

class InclusiveQAHistFiller {

  public:

    enum JetType {Trk, Full, Calo};

    // ctor/dtor
    InclusiveQAHistFiller()  {};
    ~InclusiveQAHistFiller() {};

    // external methods
    Init();
    Fill(PHCompositeNode* topNode);
    End();

  private:

    // submodules to use
    std::unique_ptr<HitQAHistManager>   m_hitManager   = NULL;
    std::unique_ptr<ClustQAHistManager> m_clustManager = NULL;
    std::unique_ptr<TrackQAHistManager> m_trackManager = NULL;
    std::unique_ptr<JetQAHistManager>   m_jetManager   = NULL;

    // internal methods
    /* TODO fill in */

};  // end InclusiveQAHistFiller

#endif

// end ------------------------------------------------------------------------

