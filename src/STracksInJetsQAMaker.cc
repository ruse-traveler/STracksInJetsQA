// ----------------------------------------------------------------------------
// 'STracksInJetsQAMaker.cc'
// Derek Anderson
// 03.25.2024
//
// A small Fun4All module to produce QA plots for tracks,
// hits, and more.
// ----------------------------------------------------------------------------

#define STRACKSINJETSQAMAKER_CC

// module defintion
#include "STracksInJetsQAMaker.h"



// ctor/dtor ------------------------------------------------------------------

STracksInJetsQAMaker::STracksInJetsQAMaker(const std::string& name, const std::string& sOutFileName) : SubsysReco(name) {

  std::cout << "STracksInJetsQAMaker::STracksInJetsQAMaker(const std::string &name) Calling ctor" << std::endl;

}  // end ctor(std::string, st::string)



STracksInJetsQAMaker::~STracksInJetsQAMaker() {

  std::cout << "STracksInJetsQAMaker::~STracksInJetsQAMaker() Calling dtor" << std::endl;

}  // end dtor



// fun4all methods ------------------------------------------------------------

int STracksInJetsQAMaker::Init(PHCompositeNode* topNode) {

  std::cout << "STracksInJetsQAMaker::Init(PHCompositeNode* topNode) Initializing" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'Init(PHCompositeNode*)'



int STracksInJetsQAMaker::InitRun(PHCompositeNode* topNode) {

  std::cout << "STracksInJetsQAMaker::InitRun(PHCompositeNode* topNode) Initializing for Run XXX" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'InitRun(PHCompositeNode*)'



int STracksInJetsQAMaker::process_event(PHCompositeNode* topNode) {

  std::cout << "STracksInJetsQAMaker::process_event(PHCompositeNode* topNode) Processing Event" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'process_event(PHCompositeNode*)'



int STracksInJetsQAMaker::ResetEvent(PHCompositeNode* topNode) {

  std::cout << "STracksInJetsQAMaker::ResetEvent(PHCompositeNode* topNode) Resetting internal structures, prepare for next event" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'ResetEvent(PHCompositeNode*)'



int STracksInJetsQAMaker::EndRun(const int runnumber) {

  std::cout << "STracksInJetsQAMaker::EndRun(const int runnumber) Ending Run for Run " << runnumber << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'EndRun(int)'



int STracksInJetsQAMaker::End(PHCompositeNode* topNode) {

  std::cout << "STracksInJetsQAMaker::End(PHCompositeNode* topNode) This is the End..." << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'End(PHCompositeNode*)'



int STracksInJetsQAMaker::Reset(PHCompositeNode* topNode) {

  std::cout << "STracksInJetsQAMaker::Reset(PHCompositeNode* topNode) being Reset" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'Reset(PHCompositeNode*)'

// end ------------------------------------------------------------------------
