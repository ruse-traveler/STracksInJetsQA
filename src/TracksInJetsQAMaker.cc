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

  std::cout << "TracksInJetsQAMaker::TracksInJetsQAMaker(const std::string &name) Calling ctor" << std::endl;

}  // end ctor(std::string, st::string)



TracksInJetsQAMaker::~TracksInJetsQAMaker() {

  std::cout << "TracksInJetsQAMaker::~TracksInJetsQAMaker() Calling dtor" << std::endl;

}  // end dtor



// fun4all methods ------------------------------------------------------------

int TracksInJetsQAMaker::Init(PHCompositeNode* topNode) {

  std::cout << "TracksInJetsQAMaker::Init(PHCompositeNode* topNode) Initializing" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'Init(PHCompositeNode*)'



int TracksInJetsQAMaker::InitRun(PHCompositeNode* topNode) {

  std::cout << "TracksInJetsQAMaker::InitRun(PHCompositeNode* topNode) Initializing for Run XXX" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'InitRun(PHCompositeNode*)'



int TracksInJetsQAMaker::process_event(PHCompositeNode* topNode) {

  std::cout << "TracksInJetsQAMaker::process_event(PHCompositeNode* topNode) Processing Event" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'process_event(PHCompositeNode*)'



int TracksInJetsQAMaker::ResetEvent(PHCompositeNode* topNode) {

  std::cout << "TracksInJetsQAMaker::ResetEvent(PHCompositeNode* topNode) Resetting internal structures, prepare for next event" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'ResetEvent(PHCompositeNode*)'



int TracksInJetsQAMaker::EndRun(const int runnumber) {

  std::cout << "TracksInJetsQAMaker::EndRun(const int runnumber) Ending Run for Run " << runnumber << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'EndRun(int)'



int TracksInJetsQAMaker::End(PHCompositeNode* topNode) {

  std::cout << "TracksInJetsQAMaker::End(PHCompositeNode* topNode) This is the End..." << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'End(PHCompositeNode*)'



int TracksInJetsQAMaker::Reset(PHCompositeNode* topNode) {

  std::cout << "TracksInJetsQAMaker::Reset(PHCompositeNode* topNode) being Reset" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'Reset(PHCompositeNode*)'

// end ------------------------------------------------------------------------
