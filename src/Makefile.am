AUTOMAKE_OPTIONS = foreign

lib_LTLIBRARIES = \
    libtracksinjetsqamaker.la

AM_LDFLAGS = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib

AM_CPPFLAGS = \
  -I$(includedir) \
  -I$(OFFLINE_MAIN)/include \
  -I$(ROOTSYS)/include

pkginclude_HEADERS = \
  TracksInJetsQAMaker.h \
  TracksInJetsQAMakerConfig.h \
  TracksInJetsQAMakerHelper.h \
  TracksInJetsQAMakerHistDef.h \
  BaseQAHistFiller.h \
  InJetQAHistFiller.h \
  InclusiveQAHistFiller.h \
  BaseQAHistManager.h \
  HitQAHistManager.h \
  ClustQAHistManager.h \
  TrackQAHistManager.h \
  JetQAHistManager.h

if ! MAKEROOT6
  ROOT5_DICTS = \
    TracksInJetsQAMaker_Dict.cc
endif

libtracksinjetsqamaker_la_SOURCES = \
  $(ROOT5_DICTS) \
  TracksInJetsQAMaker.cc \
  BaseQAHistFiller.cc \
  InJetQAHistFiller.cc \
  InclusiveQAHistFiller.cc \
  BaseQAHistManager.cc \
  HitQAHistManager.cc \
  ClustQAHistManager.cc \
  TrackQAHistManager.cc \
  JetQAHistManager.cc

libtracksinjetsqamaker_la_LDFLAGS = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib \
  -lcalo_io \
  -lfun4all \
  -lg4detectors_io \
  -lphg4hit \
  -lg4dst \
  -lg4eval \
  `fastjet-config --libs`


################################################
# linking tests

noinst_PROGRAMS = \
  testexternals

testexternals_SOURCES = testexternals.C
testexternals_LDADD = libtracksinjetsqamaker.la

testexternals.C:
	echo "//*** this is a generated file. Do not commit, do not edit" > $@
	echo "int main()" >> $@
	echo "{" >> $@
	echo "  return 0;" >> $@
	echo "}" >> $@

# Rule for generating table CINT dictionaries.
%_Dict.cc: %.h %LinkDef.h
	rootcint -f $@ @CINTDEFS@ -c $(DEFAULT_INCLUDES) $(AM_CPPFLAGS) $^

clean-local:
	rm -f *Dict* $(BUILT_SOURCES) *.pcm
