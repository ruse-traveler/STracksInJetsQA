// ----------------------------------------------------------------------------
// 'TracksInJetsQAMaker.cc'
// Derek Anderson
// 03.25.2024
//
// A "small" Fun4All module to produce QA plots for tracks,
// hits, and more.
// ----------------------------------------------------------------------------

#define TRACKSINJETSQAMAKER_CC

// module defintion
#include "TracksInJetsQAMaker.h"



// ctor/dtor ------------------------------------------------------------------

TracksInJetsQAMaker::TracksInJetsQAMaker(const std::string& name, const std::string& outFileName) : SubsysReco(name) {

  // print debug message
  if (m_config.doDebug && (m_config.verbose > 4)) {
    std::cout << "TracksInJetsQAMaker::TracksInJetsQAMaker(const std::string& name, const std::string& outFileName) Calling ctor" << std::endl;
  }

  // initialize output file
  m_outFile = new TFile(outFileName.data(), "RECREATE");
  if (!m_outFile) {
    std::cerr << PHWHERE << ": PANIC: couldn't create output file!" << std::endl;
    assert(m_outFile); 
  }

}  // end ctor(std::string, st::string)



TracksInJetsQAMaker::~TracksInJetsQAMaker() {

  // print debug messages
  if (m_config.doDebug && (m_config.verbose > 4)) {
    std::cout << "TracksInJetsQAMaker::~TracksInJetsQAMaker() Calling dtor" << std::endl;
  }

  // clean up any dangling pointers
  if (m_outFile) delete m_outFile;

}  // end dtor



// public methods -------------------------------------------------------------

void TracksInJetsQAMaker::Configure(TracksInJetsQAMakerConfig config, std::optional<TracksInJetsQAMakerHistDef> hist) {

  // print debug messages
  if (m_config.doDebug && (m_config.verbose > 3)) {
    std::cout << "TracksInJetsQAMaker::~TracksInJetsQAMaker() Calling dtor" << std::endl;
  }

  m_config = config;
  if (hist.has_value()) {
    m_hist = hist.value();
  }
  return;

}  // end 'Configure(TracksInJetsQAMakerConfig, std::optional<TracksInJetsQAMakerHistDef>)'



// fun4all methods ------------------------------------------------------------

int TracksInJetsQAMaker::Init(PHCompositeNode* topNode) {

  // print debug message
  if (m_config.doDebug && (m_config.verbose > 0)) {
    std::cout << "TracksInJetsQAMaker::Init(PHCompositeNode* topNode) Initializing" << std::endl;
  }

  // initialize needed submodules
  if (m_config.doInJet) {
    m_inJet = std::make_unique<InJetQAHistFiller>();
    m_inJet -> Init(m_config, m_help, m_hist, "InJet");
  }
  if (m_config.doInclusive) {
    m_inclusive = std::make_unique<InclusiveQAHistFiller>();
    m_inclusive -> Init(m_config, m_help, m_hist, "Inclusive");
  }
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'Init(PHCompositeNode*)'



int TracksInJetsQAMaker::process_event(PHCompositeNode* topNode) {

  // print debug message
  if (m_config.doDebug && (m_config.verbose > 2)) {
    std::cout << "TracksInJetsQAMaker::process_event(PHCompositeNode* topNode) Processing Event" << std::endl;
  }

  // run submodules
  if (m_config.doInJet)     m_inJet     -> Fill(topNode);
  if (m_config.doInclusive) m_inclusive -> Fill(topNode);
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'process_event(PHCompositeNode*)'



int TracksInJetsQAMaker::End(PHCompositeNode* topNode) {

  // print debug message
  if (m_config.doDebug && (m_config.verbose > 0)) {
    std::cout << "TracksInJetsQAMaker::End(PHCompositeNode* topNode) This is the End..." << std::endl;
  }

  // save histograms
  if (m_config.doInJet)     m_inJet     -> SaveHistograms(m_outFile, "InJet");
  if (m_config.doInclusive) m_inclusive -> SaveHistograms(m_outFile, "Inclusive");

  // close file
  m_outFile -> cd();
  m_outFile -> Close();
  return Fun4AllReturnCodes::EVENT_OK;

}  // end 'End(PHCompositeNode*)'

// end ------------------------------------------------------------------------
