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
// root libraries
#include <TH1.h>
#include <TH2.h>
// module definitions
#include "TracksInJetsQAMakerHelper.h"
#include "TracksInJetsQAMakerHistDef.h"



// BaseQAHistManager definition -----------------------------------------------

class BaseQAHistManager {

  public:

    // ctor/dtor
    BaseQAHistManager()  {};
    ~BaseQAHistManager() {};

    // external methods
    void Init();
    void End(TFile* outFile, std::string outDirName);

    // setters
    void SetBinDefs(TracksInjetsQAMakerHistDef hist) {m_hist         = hist;}
    void SetHistDefs1D(VecHistDef1D vecDef1D)        {m_vecHistDef1D = vecDef1D;}
    void SetHistDefs2D(VecHistDef2D vecDef2D)        {m_vecHistDef2D = vecDef2D;}

  protected:

    // internal methods
    void BuildHistograms(vector<HistDef1D> vecDefs1D, vector<HistDef2D> vecDefs2D);

    // histograms
    std::vector<std::vector<TH1D*>> m_vecHist1D;
    std::vector<std::vector<TH2D*>> m_vecHist2D;

    // histogram definitions
    VecHistDef1D m_vecHistDef1D;
    VecHistDef2D m_vecHistDef2D;

    // module utilities
    TracksInJetsQAMakerHelper  m_help;
    TracksInJetsQAMakerHistDef m_hist;

};  // end BaseQAHistManager


#endif

// end ------------------------------------------------------------------------
