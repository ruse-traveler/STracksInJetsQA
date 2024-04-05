// ----------------------------------------------------------------------------
// 'InJetQAHistFiller.cc'
// Derek Anderson
// 04.03.2024
//
// A submodule for the TracksInJetsQAMaker F4A module
// to produce QA histograms for tracks and more in
// jets
// ----------------------------------------------------------------------------

#define TRACKSINJETSQAMAKER_INJETQAHISTFILLER_CC

    // loop over jet constituents
    auto csts = jet -> get_comp_vec();
    for (
      auto cst = csts.begin();
      cst != csts.end();
      ++cst
    ) {

      // skip if cst is not a track
      uint32_t src = cst -> first;
      if (src != Jet::SRC::TRACK) continue;

      // grab track
      SvtxTrack* track = m_trkMap -> get(cst -> second);

      // collect cst info
      CstQAContent cstContent {
        .ptCst   = track -> get_pt(),
        .qualCst = track -> get_quality()
      };

      // fill histograms
      FillHistograms(Type::All, cstContent);

    }  // end cst loop

// end ------------------------------------------------------------------------
