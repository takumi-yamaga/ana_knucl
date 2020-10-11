// Analyzer.hh

#ifndef Analyzer_hh
#define Analyzer_hh

#include <iomanip>

#include "KnuclRootData.h"
#include "KnuclCommon.h"

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
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"
#include "TProfile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"

class Analyzer
{
    public:
        Analyzer();
        virtual ~Analyzer();

        virtual void DoAnalysis(MCData*, DetectorData*, AnalyzedData*){}
        virtual void PrintHistogram(std::string){}

    protected:
        virtual void CreateRootFile(std::string){};
        void PrintTrack(Track* track);
        void Fill(std::string hist_name, Double_t val);
        void Fill(std::string hist_name, Double_t val1, Double_t val2);
        void Print(std::vector<std::string>,std::vector<std::string>,const Int_t);
        void PrintSame(std::vector<std::string>,std::vector<Int_t>,std::vector<std::string>);
        void PrintAcceptance(std::vector<std::string> gene_names, std::vector<std::string> acce_names, Double_t maximum);
        void Print2DSlice(std::string th2_name, Int_t xy, Int_t total_slice);
        void SetHistogram(TH1*);

    protected:
        bool _is_created;
        TFile* _root_file;
        std::string _root_file_name;
        std::string _pdf_file_name;

        TRandom3* random;

};

#endif

