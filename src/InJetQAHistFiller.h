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
#include <cassert>
// phool libraries
#include <phool/phool.h>
#include <phool/getClass.h>
#include <phool/PHCompositeNode.h>
// jet libraries
#include <jetbase/Jet.h>
#include <jetbase/JetContainer.h>
// submodule definitions
#include "BaseQAHistFiller.h"



// InJetQAHistFiller ----------------------------------------------------------

class InJetQAHistFiller : public BaseQAHistFiller {

  public:

    enum JetType {Trk, Full, Calo};

    // ctor/dtor
    InJetQAHistFiller() : BaseQAHistFiller() {};
    ~InJetQAHistFiller() {};

    // inherited external methods
    void Fill(PHCompositeNode* topNode) override;

  private:

    // internal methods
    void FillJetQAHists();

    // inherited internal methods
    void GetNodes(PHCompositeNode* topNode) override;

    // necessary dst nodes
    JetContainer* m_jetMap = NULL;

};  // end InJetQAHistFiller

#endif

// end ------------------------------------------------------------------------
