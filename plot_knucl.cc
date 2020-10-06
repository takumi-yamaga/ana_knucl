#include "AnalyzerLpn.hh"

#include <iostream>
#include <sstream>
#include <time.h>

#include "TFile.h"
#include "TTree.h"

int main(int argc,char** argv)
{
    std::string in_file_name="";
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
        else if (arg.substr(0, 10) == "--pdffile=") {
            iss.str(arg.substr(10));
            iss >> pdf_file_name;
        }
    }
    std::cout<<"#############################################################"<<std::endl;
    std::cout<<"InFile            [--infile=]  = "<<in_file_name<<std::endl;
    std::cout<<"PDFFile           [--pdffile=] = "<<pdf_file_name<<std::endl;
    std::cout<<"#############################################################"<<std::endl;
    std::cout << std::endl;


    AnalyzerLpn* analyzer = new AnalyzerLpn(in_file_name,"read");
    analyzer->PrintHistogram(pdf_file_name);

    delete analyzer;

    return 0;
}

