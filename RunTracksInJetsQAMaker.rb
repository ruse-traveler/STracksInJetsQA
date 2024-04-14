#!/usr/bin/env ruby
# -----------------------------------------------------------------------------
# 'RunTracksInJetsQAMaker.rb'
# Derek Anderson
# 04.13.2024
#
# Short script to run the 'Fun4All_MakeTracksInJetsQA.C' macro
# with default options.
# -----------------------------------------------------------------------------

if ARGV[0] == "condor"
  exec("condor_submit RunTracksInJetsQAMakerOnCondor.job")
else
  exec("root -b -q Fun4All_MakeTracksInJetsQA.C")
end

# end -------------------------------------------------------------------------
