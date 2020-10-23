#include "AnalyzerLpn.hh"
#include "AnalyzerSmpp.hh"

#include <iostream>
#include <sstream>
#include <time.h>

#include "TFile.h"
#include "TTree.h"

int main(int argc,char** argv)
{
    std::string analyzer_name="";
    std::string in_file_name="";
    std::string pdf_file_name="";

    std::istringstream iss;
    std::cout<<"argc : "<<argc<<std::endl;
    for (int i = 0 ; i < argc ; i++) {
        std::string arg = argv[i];
        std::cout<<"argv["<<i<<"] : "<<argv[i]<<std::endl;
        iss.str("");
        iss.clear();
        if (arg.substr(0, 11) == "--analyzer=") {
            iss.str(arg.substr(11));
            iss >> analyzer_name;
        }
        else if (arg.substr(0, 9) == "--infile=") {
            iss.str(arg.substr(9));
            iss >> in_file_name;
        }
        else if (arg.substr(0, 10) == "--pdffile=") {
            iss.str(arg.substr(10));
            iss >> pdf_file_name;
        }
    }
    std::cout<<"#############################################################"<<std::endl;
    std::cout<<"Analyzer          [--analyzer=]  = "<<analyzer_name<<std::endl;
    std::cout<<"InFile            [--infile=]  = "<<in_file_name<<std::endl;
    std::cout<<"PDFFile           [--pdffile=] = "<<pdf_file_name<<std::endl;
    std::cout<<"#############################################################"<<std::endl;
    std::cout << std::endl;


    AnalyzerLpn* analyzer_lpn = 0;
    if(analyzer_name == "lpn"){
        analyzer_lpn = new AnalyzerLpn(in_file_name,"read");
    }

    AnalyzerSmpp* analyzer_smpp = 0;
    if(analyzer_name == "smpp"){
        analyzer_smpp = new AnalyzerSmpp(in_file_name,"read");
    }

    if(analyzer_lpn){
        analyzer_lpn->PrintHistogram(pdf_file_name);
    }
    if(analyzer_smpp){
        analyzer_smpp->PrintHistogram(pdf_file_name);
    }
    
    if(analyzer_lpn){
        delete analyzer_lpn;
    }
    if(analyzer_smpp){
        delete analyzer_smpp;
    }


    return 0;
}

