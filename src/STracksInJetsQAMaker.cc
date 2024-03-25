//____________________________________________________________________________..
//
// This is a template for a Fun4All SubsysReco module with all methods from the
// $OFFLINE_MAIN/include/fun4all/SubsysReco.h baseclass
// You do not have to implement all of them, you can just remove unused methods
// here and in STracksInJetsQAMaker.h.
//
// STracksInJetsQAMaker(const std::string &name = "STracksInJetsQAMaker")
// everything is keyed to STracksInJetsQAMaker, duplicate names do work but it makes
// e.g. finding culprits in logs difficult or getting a pointer to the module
// from the command line
//
// STracksInJetsQAMaker::~STracksInJetsQAMaker()
// this is called when the Fun4AllServer is deleted at the end of running. Be
// mindful what you delete - you do loose ownership of object you put on the node tree
//
// int STracksInJetsQAMaker::Init(PHCompositeNode *topNode)
// This method is called when the module is registered with the Fun4AllServer. You
// can create historgrams here or put objects on the node tree but be aware that
// modules which haven't been registered yet did not put antyhing on the node tree
//
// int STracksInJetsQAMaker::InitRun(PHCompositeNode *topNode)
// This method is called when the first event is read (or generated). At
// this point the run number is known (which is mainly interesting for raw data
// processing). Also all objects are on the node tree in case your module's action
// depends on what else is around. Last chance to put nodes under the DST Node
// We mix events during readback if branches are added after the first event
//
// int STracksInJetsQAMaker::process_event(PHCompositeNode *topNode)
// called for every event. Return codes trigger actions, you find them in
// $OFFLINE_MAIN/include/fun4all/Fun4AllReturnCodes.h
//   everything is good:
//     return Fun4AllReturnCodes::EVENT_OK
//   abort event reconstruction, clear everything and process next event:
//     return Fun4AllReturnCodes::ABORT_EVENT; 
//   proceed but do not save this event in output (needs output manager setting):
//     return Fun4AllReturnCodes::DISCARD_EVENT; 
//   abort processing:
//     return Fun4AllReturnCodes::ABORT_RUN
// all other integers will lead to an error and abort of processing
//
// int STracksInJetsQAMaker::ResetEvent(PHCompositeNode *topNode)
// If you have internal data structures (arrays, stl containers) which needs clearing
// after each event, this is the place to do that. The nodes under the DST node are cleared
// by the framework
//
// int STracksInJetsQAMaker::EndRun(const int runnumber)
// This method is called at the end of a run when an event from a new run is
// encountered. Useful when analyzing multiple runs (raw data). Also called at
// the end of processing (before the End() method)
//
// int STracksInJetsQAMaker::End(PHCompositeNode *topNode)
// This is called at the end of processing. It needs to be called by the macro
// by Fun4AllServer::End(), so do not forget this in your macro
//
// int STracksInJetsQAMaker::Reset(PHCompositeNode *topNode)
// not really used - it is called before the dtor is called
//
// void STracksInJetsQAMaker::Print(const std::string &what) const
// Called from the command line - useful to print information when you need it
//
//____________________________________________________________________________..

#include "STracksInJetsQAMaker.h"

#include <fun4all/Fun4AllReturnCodes.h>

#include <phool/PHCompositeNode.h>

//____________________________________________________________________________..
STracksInJetsQAMaker::STracksInJetsQAMaker(const std::string &name):
 SubsysReco(name)
{
  std::cout << "STracksInJetsQAMaker::STracksInJetsQAMaker(const std::string &name) Calling ctor" << std::endl;
}

//____________________________________________________________________________..
STracksInJetsQAMaker::~STracksInJetsQAMaker()
{
  std::cout << "STracksInJetsQAMaker::~STracksInJetsQAMaker() Calling dtor" << std::endl;
}

//____________________________________________________________________________..
int STracksInJetsQAMaker::Init(PHCompositeNode *topNode)
{
  std::cout << "STracksInJetsQAMaker::Init(PHCompositeNode *topNode) Initializing" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int STracksInJetsQAMaker::InitRun(PHCompositeNode *topNode)
{
  std::cout << "STracksInJetsQAMaker::InitRun(PHCompositeNode *topNode) Initializing for Run XXX" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int STracksInJetsQAMaker::process_event(PHCompositeNode *topNode)
{
  std::cout << "STracksInJetsQAMaker::process_event(PHCompositeNode *topNode) Processing Event" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int STracksInJetsQAMaker::ResetEvent(PHCompositeNode *topNode)
{
  std::cout << "STracksInJetsQAMaker::ResetEvent(PHCompositeNode *topNode) Resetting internal structures, prepare for next event" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int STracksInJetsQAMaker::EndRun(const int runnumber)
{
  std::cout << "STracksInJetsQAMaker::EndRun(const int runnumber) Ending Run for Run " << runnumber << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int STracksInJetsQAMaker::End(PHCompositeNode *topNode)
{
  std::cout << "STracksInJetsQAMaker::End(PHCompositeNode *topNode) This is the End..." << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int STracksInJetsQAMaker::Reset(PHCompositeNode *topNode)
{
 std::cout << "STracksInJetsQAMaker::Reset(PHCompositeNode *topNode) being Reset" << std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
void STracksInJetsQAMaker::Print(const std::string &what) const
{
  std::cout << "STracksInJetsQAMaker::Print(const std::string &what) const Printing info for " << what << std::endl;
}
