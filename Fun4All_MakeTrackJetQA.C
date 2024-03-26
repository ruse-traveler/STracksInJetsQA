// ----------------------------------------------------------------------------
// 'Fun4All_MakeTrackJetQA.C'
// Derek Anderson
// 03.25.2024
//
// A Fun4All macro to run the TrackJetQAMaker module.
// ----------------------------------------------------------------------------

#define FUN4ALL_MAKETRACKSINJETSQA_C

// c++ utilities
#include <string>
#include <vector>
// fun4all libraries
#include <fun4all/SubsysReco.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllOutputManager.h>
#include <fun4all/Fun4AllDstInputManager.h>
#include <fun4all/Fun4AllDstOutputManager.h>
// phool libraries
#include <phool/recoConsts.h>
#include <phool/PHRandomSeed.h>
// jet base software
#include <jetbase/Jet.h>
#include <jetbase/JetReco.h>
#include <jetbase/FastJetAlgo.h>
#include <jetbase/TrackJetInput.h>
// module definition
#include </sphenix/user/danderson/install/include/trackjetqamaker/TrackJetQAMaker.h>
#include </sphenix/user/danderson/install/include/trackjetqamaker/TrackJetQAMakerConfig.h>

// load libraries
R__LOAD_LIBRARY(libg4dst.so)
R__LOAD_LIBRARY(libg4jets.so)
R__LOAD_LIBRARY(libjetbase.so)
R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(/sphenix/user/danderson/install/lib/libtrackjetqamaker.so)



// macro body -----------------------------------------------------------------

void Fun4All_MakeTrackJetQA(
  const int         verb           = 1,
  const int64_t     nEvts          = 1,
  const std::string outFile        = "test.root",
  const std::string inTrkDSTs      = "input/lists/dst_tracks.list",
  const std::string inTrkHitDSTs   = "input/lists/dst_trkr_hit.list",
  const std::string inTrkClustDSTs = "input/lists/dst_trkr_cluster.list"
) {

  // initialize f4a server etc
  Fun4AllServer* f4a = Fun4AllServer::instance();

  // run jet reconstruction
  JetReco* reco = new JetReco();
  reco -> add_input(new TrackJetInput(Jet::SRC::TRACK));
  reco -> add_algo(new FastJetAlgo(Jet::ALGO::ANTIKT, 0.4), "AntiKt_Track_r04");
  reco -> set_algo_node("ANTIKT");
  reco -> set_input_node("TRACK");
  reco -> Verbosity(verb);
  f4a  -> registerSubsystem(reco);

  // set up input managers
  Fun4AllDstInputManager* trkManager   = new Fun4AllDstInputManager("TrackDstManager");
  Fun4AllDstInputManager* hitManager   = new Fun4AllDstInputManager("TrackHitDstManager");
  Fun4AllDstInputManager* clustManager = new Fun4AllDstInputManager("TrackClusterDstManager");
  trkManager   -> AddListFile(inTrkDSTs.data(), 1);
  hitManager   -> AddListFile(inTrkHitDSTs.data(), 1);
  clustManager -> AddListFile(inTrkClustDSTs.data(), 1);
  f4a -> registerInputManager(trkManager);
  f4a -> registerInputManager(hitManager);
  f4a -> registerInputManager(clustManager);

  // initialize and register qa module
  TrackJetQAMaker* maker = new TrackJetQAMaker("TrackJetQAMaker", outFile);
  maker -> Configure(
    {
      .verbose   = verb,
      .doDebug   = true,
      .doHitQA   = true,
      .doClustQA = true,
      .doTrackQA = false
    }
  );
  f4a -> registerSubsystem(maker);

  // run4all
  f4a -> run(nEvts);
  f4a -> End();
  delete f4a;

  // close and exit
  gSystem -> Exit(0);
  return;

}

// end ------------------------------------------------------------------------
