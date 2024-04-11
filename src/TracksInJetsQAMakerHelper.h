// ----------------------------------------------------------------------------
// 'TracksInJetsQAMakerHelper.h'
// Derek Anderson
// 03.25.2024
//
// Small class to help calculations in the TracksInJetsQAMaker module.
// ----------------------------------------------------------------------------

#ifndef TRACKSINJETSQAMAKERHELPER_H
#define TRACKSINJETSQAMAKERHELPER_H



// TracksInJetsQAMakerHelper definition ---------------------------------------

class TracksInJetsQAMakerHelper {

  private:

    uint16_t m_nMvtxLayer = 3;
    uint16_t m_nInttLayer = 4;
    uint16_t m_nTpcLayer  = 48;

  public:

    TracksInJetsQAMakerHelper()  {};
    ~TracksInJetsQAMakerHelper() {};

    // setters
    void SetNMvtxLayer(const uint16_t num) {m_nMvtxLayer = num;}
    void SetNInttLayer(const uint16_t num) {m_nInttLayer = num;}
    void SetNTpcLayer(const uint16_t num)  {m_nTpcLayer = num;}

    // helper methods ---------------------------------------------------------

    bool IsInMvtx(const uint16_t layer) {
      return (layer < m_nMvtxLayer);
    }  // end 'IsInMvtx(uint16_t)'

    bool IsInIntt(const uint16_t layer) {
      return (
        (layer >= m_nMvtxLayer) &&
        (layer <  m_nInttLayer + m_nMvtxLayer)
      );
    }  // end 'IsInIntt(uint16_t)'

    bool IsInTpc(const uint16_t layer) {
      return (layer >= m_nMvtxLayer + m_nInttLayer);
    }  // end 'IsInTpc(uint16_t)'

};  // end TracksInJetsQAMakerHelper

#endif

// end ------------------------------------------------------------------------
