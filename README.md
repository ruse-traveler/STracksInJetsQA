# TracksInJetsQAMaker

A Fun4All package to generate QA plots for tracks in jets and related objects. Can be
run as a plain `SubsysReco` module (`TracksInJetsQAMaker.*`) or as a QA module (TBD).

The top-level macro included here illustrates both use cases.

## General Usage

There are four categories of plots that can be produced -- tracker hits, tracker clusters,
tracks, and jets -- both inclusively and inside of jets (track, calo, or otherwise).

The most relevant user-configurable options (set in the `Configure` call) are:

```
  .verbose     # verbosity
  .doDebug     # turn on debugging comments
  .doInclusive # make inclusive plots
  .doInJet     # make in-jet plots
  .doHitQA     # make tracker hit plots
  .doClustQA   # make tracker cluster plots
  .doTrackQA   # make track plots
  .doJetQA     # make jet plots
  .rJet        # resolution parameter of jets analyzed
  .jetInNode   # DST node with jets to be analyzed
```

Where additional configurable options can seen in `src/TracksInJetsQAMakerConfig.h`.

Finally, code is compiled in the usual way:

```
# in src/
cd build
../autogen.sh --prefix=$MYINSTALL
make -j 4
make install
```

## Code Structure

The code is organized into 3 layers:

  1. **Histogram Managers:** the lowest level, which define what histograms are
     going to be generated and how they're going to be filled for each category
     (hit, cluster, track, jet).
  2. **Histogram Fillers:** these call the histogram managers and define the
     various loops for each mode (inclusive, in-jet).
  3. **Top Level Modules:** finally, these call the histogram fillers and pass
     along the generated histograms to the relevant places.

All chunks of code that are common to the 4 managers and 2 fillers are
consolidated into relevant base classes -- `BaseHistogramManager`, `BaseHistogramFiller`.

Lastly, alongside the core pieces described above, there are 3 helper objects used to
streamline the code and centralize related information.

  - `TracksInJetsQAMakerConfig.h:` defines a struct used to collect **all** user-configurable options.
  - `TracksInJetsQAMakerHelper.h:` consolidates a variety of useful methods and information (e.g.
    checks on whether or not a particular hit/cluster is in a given subsystem).
  - `TracksInJetsQAMakerHistDef.h:` consoldiates the binning schemes used across all three sub-modules,
