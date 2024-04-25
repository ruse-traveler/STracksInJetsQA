#!/usr/bin/env ruby
# -----------------------------------------------------------------------------
# 'copy-to-analysis.rb'
# Derek Anderson
# 12.21.2023
#
# Script to automate copying files over to
# a fork of the sPHENIX analysis repo.
# -----------------------------------------------------------------------------

# modules to use
require 'fileutils'

# top directory to copy from/to
copy_from = "/sphenix/user/danderson/tracking/TracksInJetQA"
copy_to   = "/sphenix/user/danderson/sphenix/analysis/JS-Jet/TracksInJetsQAMaker"

# what files to copy
to_copy = [
  "README.md",
  "Fun4All_MakeTracksInJetsQA.C",
  "RunTracksInJetsQAMaker.rb",
  "RunTracksInJetsQAMakerOnCondor.sh",
  "RunTracksInJetsQAMakerOnCondor.job",
  "input/pp200py8run11jet30.dst_global.list",
  "input/pp200py8run11jet30.dst_tracks.list",
  "input/pp200py8run11jet30.dst_trkr_cluster.list",
  "input/pp200py8run11jet30.dst_trkr_hit.list",
  "scripts/copy-to-analysis.rb",
  "scripts/wipe-source.sh",
  "src/ClustQAHistManager.cc",
  "src/ClustQAHistManager.h",
  "src/HitQAHistManager.cc",
  "src/HitQAHistManager.h",
  "src/JetQAHistManager.cc",
  "src/JetQAHistManager.h",
  "src/TrackQAHistManager.cc",
  "src/TrackQAHistManager.h",
  "src/BaseQAHistFiller.cc",
  "src/BaseQAHistFiller.h",
  "src/InJetQAHistFiller.cc",
  "src/InJetQAHistFiller.h",
  "src/InclusiveQAHistFiller.cc",
  "src/InclusiveQAHistFiller.h",
  "src/BaseQAHistManager.cc",
  "src/BaseQAHistManager.h",
  "src/TracksInJetsQAMaker.cc",
  "src/TracksInJetsQAMaker.h",
  "src/TracksInJetsQAMakerConfig.h",
  "src/TracksInJetsQAMakerHistDef.h",
  "src/autogen.sh",
  "src/configure.ac",
  "src/Makefile.am",
  "src/sphx-build"
]

# do copying
to_copy.each do |file|

  # make directory in target if needed
  if file.include? "/"

    # grab relative path to file
    relative_path = file.clone
    relative_path.gsub!(copy_from, "")

    # clean up and isolate path
    relative_path.gsub!("//",  "/")
    relative_path.gsub!("/./", "/")
    relative_path.slice!(relative_path.rindex("/")..-1)

    # make directory
    to_make = copy_to + "/" + relative_path
    FileUtils.mkdir_p(to_make, :verbose => true) unless File.exists?(to_make)
  end

  # make source and target paths
  source = copy_from + "/" + file
  target = copy_to + "/" + file

  # remove any unwanted patterns
  source.gsub!("//",  "/")
  target.gsub!("//",  "/")
  source.gsub!("/./", "/")
  target.gsub!("/./", "/")

  # copy file
  FileUtils.cp_r(source, target, :verbose => true)
end

# end -------------------------------------------------------------------------
