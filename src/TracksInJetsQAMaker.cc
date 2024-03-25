// ----------------------------------------------------------------------------
// 'TracksInJetsQAMaker.cc'
// Derek Anderson
// 03.25.2024
//
// A small Fun4All module to produce QA plots for tracks,
// hits, and more.
// ----------------------------------------------------------------------------

#define TRACKSINJETSQAMAKER_CC

// module defintion
#include "TracksInJetsQAMaker.h"



// ctor/dtor ------------------------------------------------------------------

TracksInJetsQAMaker::TracksInJetsQAMaker(const std::string& name, const std::string& sOutFileName) : SubsysReco(name) {

  // print debug message
  if (m_config.doDebug && (m_config.verbose > 4)) {
    std::cout << "TracksInJetsQAMaker::TracksInJetsQAMaker(const std::string &name) Calling ctor" << std::endl;
  }

  // set output file name
  m_outFileName = sOutFileName;

}  // end ctor(std::string, st::string)



TracksInJetsQAMaker::~TracksInJetsQAMaker() {

  // print debug messages
  if (m_config.doDebug && (m_config.verbose > 4)) {
    std::cout << "TracksInJetsQAMaker::~TracksInJetsQAMaker() Calling dtor" << std::endl;
  }

  // clean up any dangling pointers
  if (m_outFile)    delete m_outFile;
  if (m_hitMaker)   delete m_hitMaker;
  if (m_clustMaker) delete m_clustMaker;
  if (m_trackMaker) delete m_trackMaker;

}  // end dtor



// public methods -------------------------------------------------------------

void TracksInJetsQAMaker::Configure(TrackJetQAMakerConfig config, std::optional<TrackJetQAMakerHistDef> hist) {

  // print debug messages
  if (m_config.doDebug && (m_config.verbose > 3)) {
    std::cout << "TracksInJetsQAMaker::~TracksInJetsQAMaker() Calling dtor" << std::endl;
  }

  m_config = config;
  if (hist.has_value()) {
    m_hist = hist.value();
  }
  return;

}  // end 'Configure(TrackJetQAMakerConfig, std::optional<TrackJetQAMakerHistDef>)'



// fun4all methods ------------------------------------------------------------

int TracksInJetsQAMaker::Init(PHCompositeNode* topNode) {

  // print debug message
  if (m_config.doDebug && (m_config.verbose > 0)) {
    std::cout << "TracksInJetsQAMaker::Init(PHCompositeNode* topNode) Initializing" << std::endl;
  }

  // initialize output file
  m_outFile = new TFile(m_outFileName.data(), "RECREATE");

  // instantiate needed plugins
  if (m_config.doHitQA)   m_hitMaker   = new HitQAMaker();
  if (m_config.doClustQA) m_clustMaker = new ClustQAMaker();
  if (m_config.doTrackQA) m_trackMaker = new TrackQAMaker();

  // intialize plugins
  if (m_config.doHitQA)   m_hitMaker   -> Init(m_hist);
  if (m_config.doClustQA) m_clustMaker -> Init();
  if (m_config.doTrackQA) m_trackMaker -> Init();
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'Init(PHCompositeNode*)'



int TracksInJetsQAMaker::InitRun(PHCompositeNode* topNode) {

  // print debug message
  if (m_config.doDebug && (m_config.verbose > 1)) {
    std::cout << "TracksInJetsQAMaker::InitRun(PHCompositeNode* topNode) Initializing for Run XXX" << std::endl;
  }

  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'InitRun(PHCompositeNode*)'



int TracksInJetsQAMaker::process_event(PHCompositeNode* topNode) {

  // print debug message
  if (m_config.doDebug && (m_config.verbose > 2)) {
    std::cout << "TracksInJetsQAMaker::process_event(PHCompositeNode* topNode) Processing Event" << std::endl;
  }

  // run plugins
  if (m_config.doHitQA)   m_hitMaker   -> Process(topNode);
  if (m_config.doClustQA) m_clustMaker -> Process(topNode);
  if (m_config.doTrackQA) m_trackMaker -> Process(topNode);
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'process_event(PHCompositeNode*)'



int TracksInJetsQAMaker::ResetEvent(PHCompositeNode* topNode) {

  // print debug message
  if (m_config.doDebug && (m_config.verbose > 3)) {
    std::cout << "TracksInJetsQAMaker::ResetEvent(PHCompositeNode* topNode) Resetting internal structures, prepare for next event" << std::endl;
  }

  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'ResetEvent(PHCompositeNode*)'



int TracksInJetsQAMaker::EndRun(const int runnumber) {

  // print debug message
  if (m_config.doDebug && (m_config.verbose > 1)) {
    std::cout << "TracksInJetsQAMaker::EndRun(const int runnumber) Ending Run for Run " << runnumber << std::endl;
  }

  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'EndRun(int)'



int TracksInJetsQAMaker::End(PHCompositeNode* topNode) {

  // print debug message
  if (m_config.doDebug && (m_config.verbose > 0)) {
    std::cout << "TracksInJetsQAMaker::End(PHCompositeNode* topNode) This is the End..." << std::endl;
  }

  // terminate plugins
  if (m_config.doHitQA)   m_hitMaker   -> End(m_outFile);
  if (m_config.doClustQA) m_clustMaker -> End();
  if (m_config.doTrackQA) m_trackMaker -> End();

  // close file
  m_outFile -> cd();
  m_outFile -> Close();
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'End(PHCompositeNode*)'



int TracksInJetsQAMaker::Reset(PHCompositeNode* topNode) {

  // print debug message
  if (m_config.doDebug && (m_config.verbose > 3)) {
    std::cout << "TracksInJetsQAMaker::Reset(PHCompositeNode* topNode) being Reset" << std::endl;
  }

  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'Reset(PHCompositeNode*)'

// end ------------------------------------------------------------------------
