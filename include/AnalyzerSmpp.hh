// AnalyzerSmpp.hh

#ifndef AnalyzerSmpp_hh
#define AnalyzerSmpp_hh

#include "KnuclRootData.h"
#include "KnuclCommon.h"

#include "KinFitter/TKinFitter.h"
#include "KinFitter/TFitParticlePxPyPz.h"
#include "KinFitter/TFitConstraintM.h"
#include "KinFitter/TFitConstraintEp.h"

#include "Analyzer.hh"
#include "AnalyzedData.hh"
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
#include "TLatex.h"
#include "TDatabasePDG.h"

class AnalyzerSmpp : public Analyzer
{
    public:
        AnalyzerSmpp();
        AnalyzerSmpp(std::string file_name,std::string option="");
        ~AnalyzerSmpp();

        void DoAnalysis(MCData* mcData, DetectorData* detectorData, AnalyzedData*);
        void PrintHistogram(std::string file_name="");

    private:
        void CreateRootFile(std::string option="");

    private:
        std::vector<std::string> _meas_type;
        TDatabasePDG* pdg;
        bool is_pdg_created;

};

#endif

