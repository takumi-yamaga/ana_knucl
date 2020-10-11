// AnalyzedData.hh

#ifndef AnalyzedData_hh
#define AnalyzedData_hh

#include "KnuclRootData.h"
#include "KnuclCommon.h"

#include "AnaKnuclCommon.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include "TColor.h"
#include "TRandom3.h"
#include "TDatabasePDG.h"

class AnalyzedData
{
    public:
        AnalyzedData();
        ~AnalyzedData();

        void DoAnalysis(MCData* mcData, DetectorData* detectorData);
        void Clear();
        
    private:
        bool CheckTrackAlreadyMeasured(std::vector<Track*> measured_tracks, DetectorHit* hit);
        Track* CreateTrack(DetectorHit* hit);

    private:
        TRandom3* random;
        TDatabasePDG* pdg;

    public:
        std::vector<Track*> measured_beam_tracks(){ return _measured_beam_tracks; }
        std::vector<Track*> measured_charged_tracks(){ return _measured_charged_tracks; }
        std::vector<Track*> measured_charged_capb_tracks(){ return _measured_charged_capb_tracks; }
        std::vector<Track*> measured_charged_capf_tracks(){ return _measured_charged_capf_tracks; }
        std::vector<Track*> measured_neutral_tracks(){ return _measured_neutral_tracks; }
        std::vector<Track*> measured_neutral_capb_tracks(){ return _measured_neutral_capb_tracks; }
        std::vector<Track*> measured_neutral_capf_tracks(){ return _measured_neutral_capf_tracks; }
        std::vector<Double_t> measured_neutral_energy_deposits(){ return _measured_neutral_energy_deposits; }
        std::vector<Double_t> measured_neutral_capb_energy_deposits(){ return _measured_neutral_capb_energy_deposits; }
        std::vector<Double_t> measured_neutral_capf_energy_deposits(){ return _measured_neutral_capf_energy_deposits; }
        std::vector<Double_t> measured_neutral_over_betas(){ return _measured_neutral_over_betas; }
        std::vector<Double_t> measured_neutral_capb_over_betas(){ return _measured_neutral_capb_over_betas; }
        std::vector<Double_t> measured_neutral_capf_over_betas(){ return _measured_neutral_capf_over_betas; }
        std::vector<Double_t> measured_neutral_times(){ return _measured_neutral_times; }
        std::vector<Double_t> measured_neutral_capb_times(){ return _measured_neutral_capb_times; }
        std::vector<Double_t> measured_neutral_capf_times(){ return _measured_neutral_capf_times; }
    private:
        std::vector<Track*> _measured_beam_tracks;
        std::vector<Track*> _measured_charged_tracks;
        std::vector<Track*> _measured_charged_capb_tracks;
        std::vector<Track*> _measured_charged_capf_tracks;
        std::vector<Track*> _measured_neutral_tracks;
        std::vector<Track*> _measured_neutral_capb_tracks;
        std::vector<Track*> _measured_neutral_capf_tracks;
        std::vector<Double_t> _measured_neutral_energy_deposits;
        std::vector<Double_t> _measured_neutral_capb_energy_deposits;
        std::vector<Double_t> _measured_neutral_capf_energy_deposits;
        std::vector<Double_t> _measured_neutral_over_betas;
        std::vector<Double_t> _measured_neutral_capb_over_betas;
        std::vector<Double_t> _measured_neutral_capf_over_betas;
        std::vector<Double_t> _measured_neutral_times;
        std::vector<Double_t> _measured_neutral_capb_times;
        std::vector<Double_t> _measured_neutral_capf_times;

    public:
        std::vector<DetectorHit*> t0_hits(){ return _t0_hits; }
        std::vector<DetectorHit*> def_hits(){ return _def_hits; }
        std::vector<DetectorHit*> chcbarrel_hits(){ return _chcbarrel_hits; }
        std::vector<DetectorHit*> chccapb_hits(){ return _chccapb_hits; }
        std::vector<DetectorHit*> chccapf_hits(){ return _chccapf_hits; }
        std::vector<DetectorHit*> ncbarrel_hits(){ return _ncbarrel_hits; }
        std::vector<DetectorHit*> nccapb_hits(){ return _nccapb_hits; }
        std::vector<DetectorHit*> nccapf_hits(){ return _nccapf_hits; }
    private:
        std::vector<DetectorHit*> _t0_hits;
        std::vector<DetectorHit*> _def_hits;
        std::vector<DetectorHit*> _chcbarrel_hits;
        std::vector<DetectorHit*> _chccapb_hits;
        std::vector<DetectorHit*> _chccapf_hits;
        std::vector<DetectorHit*> _ncbarrel_hits;
        std::vector<DetectorHit*> _nccapb_hits;
        std::vector<DetectorHit*> _nccapf_hits;

    public:
        std::vector<DetectorHit*>* cdc_hits(){ return _cdc_hits; }
        std::vector<DetectorHit*>* bdc1_hits(){ return _bdc1_hits; }
        std::vector<DetectorHit*>* bdc2_hits(){ return _bdc2_hits; }
        std::vector<DetectorHit*>* bdc3_hits(){ return _bdc3_hits; }
        std::vector<DetectorHit*>* fdc1_hits(){ return _fdc1_hits; }
        std::vector<DetectorHit*>* fdc2_hits(){ return _fdc2_hits; }
        std::vector<DetectorHit*>* fdc3_hits(){ return _fdc3_hits; }
    private:
        std::vector<DetectorHit*> _cdc_hits[15];
        std::vector<DetectorHit*> _bdc1_hits[8];
        std::vector<DetectorHit*> _bdc2_hits[8];
        std::vector<DetectorHit*> _bdc3_hits[8];
        std::vector<DetectorHit*> _fdc1_hits[8];
        std::vector<DetectorHit*> _fdc2_hits[8];
        std::vector<DetectorHit*> _fdc3_hits[8];

    public:
        TVector3 vec_reaction_vertex(){ return _vec_reaction_vertex; }
    private:
        TVector3 _vec_reaction_vertex;

};

#endif

