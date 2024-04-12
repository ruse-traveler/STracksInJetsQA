// ----------------------------------------------------------------------------
// 'BaseQAHistManager.h'
// Derek Anderson
// 04.03.2024
//
// Base hist manager submodule for the TracksInJetsQAMaker module
// which consolidates methods/data common to all of the hist
// managers
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKER_BASEQAHISTMANAGER_H
#define TRACKSINJETSQAMAKER_BASEQAHISTMANAGER_H

// c++ utilities
#include <string>
#include <vector>
#include <utility>
#include <iostream>
// root libraries
#include <TH1.h>
#include <TH2.h>
#include <TDirectory.h>
// phool libraries
#include <phool/phool.h>
// module utilities
#include "TracksInJetsQAMakerHelper.h"
#include "TracksInJetsQAMakerHistDef.h"



// BaseQAHistManager definition -----------------------------------------------

class BaseQAHistManager {

  public:

    // ctor/dtor
    BaseQAHistManager();
    ~BaseQAHistManager();

    // external methods
    void Init(TracksInJetsQAMakerHelper& help, TracksInJetsQAMakerHistDef& hist);
    void SaveHistograms(TDirectory* outFile, std::string outDirName);

  protected:

    // internal methods
    void BuildHistograms();
    void ResetVectors();

    // virtual internal methods
    virtual void DefineHistograms() = 0;

    // histograms
    VecHist1D m_vecHist1D;
    VecHist2D m_vecHist2D;

    // histogram definitions
    VecHistTypes m_vecHistTypes;
    VecHistDef1D m_vecHistDef1D;
    VecHistDef2D m_vecHistDef2D;

    // module utilities
    TracksInJetsQAMakerHelper  m_help;
    TracksInJetsQAMakerHistDef m_hist;

};  // end BaseQAHistManager


#endif

// end ------------------------------------------------------------------------
