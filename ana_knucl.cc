#include "KnuclRootData.h"
#include "KnuclCommon.h"

#include "AnalyzedData.hh"
#include "AnalyzerLpn.hh"

#include <iostream>
#include <sstream>
#include <time.h>

#include "TFile.h"
#include "TTree.h"

int main(int argc,char** argv)
{
    std::string in_file_name="";
    std::string out_file_name="";
    std::string pdf_file_name="";

    std::istringstream iss;
    std::cout<<"argc : "<<argc<<std::endl;
    for (int i = 0 ; i < argc ; i++) {
        std::string arg = argv[i];
        std::cout<<"argv["<<i<<"] : "<<argv[i]<<std::endl;
        iss.str("");
        iss.clear();
        if (arg.substr(0, 9) == "--infile=") {
            iss.str(arg.substr(9));
            iss >> in_file_name;
        }
        else if (arg.substr(0, 10) == "--outfile=") {
            iss.str(arg.substr(10));
            iss >> out_file_name;
        }
        else if (arg.substr(0, 10) == "--pdffile=") {
            iss.str(arg.substr(10));
            iss >> pdf_file_name;
        }
    }
    std::cout<<"#############################################################"<<std::endl;
    std::cout<<"InFile            [--infile=]  = "<<in_file_name<<std::endl;
    std::cout<<"OutFile           [--outfile=] = "<<out_file_name<<std::endl;
    std::cout<<"PDFFile           [--pdffile=] = "<<pdf_file_name<<std::endl;
    std::cout<<"#############################################################"<<std::endl;
    std::cout << std::endl;


    TFile* in_file = new TFile(in_file_name.data(),"read");
    if(!in_file->IsOpen()){
        std::cout << "!!! The InFile : [" << in_file_name << "] can not be opened.!!!" << std::endl;
        return 0;
    }

    TTree *tree = (TTree*)in_file->Get("tree");
    TTree *tree2 = (TTree*)in_file->Get("tree2");

    RunHeaderMC*    runHeaderMC=0;
    EventHeaderMC*  eventHeaderMC=0;
    DetectorData*   detectorData=0;
    MCData*         mcData=0;
    ReactionData*   reactionData=0;

    tree2->SetBranchAddress( "RunHeaderMC", &runHeaderMC );
    tree->SetBranchAddress( "EventHeaderMC", &eventHeaderMC );
    tree->SetBranchAddress( "DetectorData", &detectorData );
    tree->SetBranchAddress( "MCData", &mcData );
    tree->SetBranchAddress( "ReactionData", &reactionData );

    tree2->GetEvent(0);
    double totalCS  = runHeaderMC->CStable().TotalCS();
    int totalEv     = 0;
    int generatedEv = 0;
    for( int i=0; i<tree2->GetEntries(); i++ ){
        tree2->GetEvent(i);
        totalEv     += runHeaderMC->numEvent();
        generatedEv += runHeaderMC->numGenerated();
    }
    std::cerr<<"********************************"<<std::endl;
    std::cerr<<" seed                  = "<<runHeaderMC->seed()<<std::endl;
    std::cerr<<" # of total events     = "<<totalEv<<std::endl;
    std::cerr<<" # of events in tree   = "<<tree->GetEntries()<<std::endl;
    std::cerr<<"--------------------------------"<<std::endl;
    std::cerr<<" # of generated events = "<<generatedEv<<std::endl;
    std::cerr<<" total CrossSection    = "<<totalCS<<" mb"<<std::endl;
    std::cerr<<"********************************"<<std::endl;

    time_t timer;
    double time_0 = time(&timer);

    AnalyzedData* analyzedData = new AnalyzedData();

    std::string out_file_name_lpn = out_file_name.substr(0,out_file_name.find_last_of("."));
    out_file_name_lpn.append("_lpn.root");
    AnalyzerLpn* analyzer = new AnalyzerLpn(out_file_name_lpn,"recreate");

    // ----------------------------------------------------------------
    // Event loop -----------------------------------------------------
    // ----------------------------------------------------------------
    Int_t total_events = tree->GetEntries();
    //total_events = 10;
    std::cout<<"Start to fill histgrams. Entries = "<<total_events<<std::endl;
    for (Int_t i_event=0; i_event<total_events; i_event++) {
        tree->GetEvent(i_event);
        analyzedData->DoAnalysis(mcData,detectorData);

        analyzer->DoAnalysis(mcData,detectorData,analyzedData);

        analyzedData->Clear();

        double time_now = time(&timer);
        Int_t print_progress = (Int_t)log10(i_event+1);
        print_progress = pow(10,print_progress);
        if((i_event+1)%print_progress==0){
            std::cout << i_event+1 << " : " << time_now - time_0 << std::endl;
        }
    }
    std::cout<<"end of filling"<<std::endl;
    // ----------------------------------------------------------------
    // Event loop -----------------------------------------------------
    // ----------------------------------------------------------------

    analyzer->PrintHistogram(pdf_file_name);
    delete analyzedData;
    delete analyzer;

    return 0;
}

