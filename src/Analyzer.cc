// Analyzer.cc

#include"Analyzer.hh"

Analyzer::Analyzer()
{
}

Analyzer::~Analyzer()
{
}

void Analyzer::PrintTrack(Track* track)
{
    std::cout << "--------" << std::endl;
    std::cout << "trackID : " << track->trackID() << std::endl;
    std::cout << "parentTrackID : " << track->parentTrackID() << std::endl;
    std::cout << "pdgID : " << track->pdgID() << std::endl;
}
void Analyzer::Fill(std::string hist_name, Double_t val){
    TH1* hist = (TH1*)_root_file->Get(hist_name.data());
    if(hist){
        hist->Fill(val);
    }
    return;
}
void Analyzer::Fill(std::string hist_name, Double_t val1, Double_t val2){
    TH1* hist = (TH1*)_root_file->Get(hist_name.data());
    if(hist){
        hist->Fill(val1,val2);
    }
    return;
}
void Analyzer::Print(std::vector<std::string> print_th_names, std::vector<std::string> log_th_names, const Int_t dim){
    TStyle* style = new TStyle("Plain","Plain Style (no colors/fill areas)");
    style->SetOptStat(0);
    style->SetOptTitle(0);
    Int_t MyPalette[100];
    Double_t Red[]    = {0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t Green[]  = {0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t Blue[]   = {0.51, 1.00, 0.12, 0.00, 0.00 };
    Double_t Length[] = {0.00, 0.34, 0.61, 0.84, 1.00 };
    Int_t FI = TColor::CreateGradientColorTable(5, Length, Red, Green, Blue, 100);
    for (int i=0;i<100;i++){
        MyPalette[i] = FI+i;
    }
    style->SetPalette(100,MyPalette);

    style->cd();

    TCanvas* canvas = new TCanvas("canvas","canvas",3200,1800);
    Int_t div_x = 3;
    Int_t div_y = 2;
    canvas->Divide(div_x,div_y);
    Int_t total_pads = div_x*div_y;

    for(Int_t i_pad=1; i_pad<=total_pads; ++i_pad){
        TPad* pad = (TPad*)canvas->cd(i_pad);
        pad->SetGrid();
        pad->SetTicks();
        pad->SetLeftMargin(0.16);
        pad->SetRightMargin(0.03);
        pad->SetTopMargin(0.05);
        pad->SetBottomMargin(0.16);
    }

    Int_t i_pad = 1;

    if(dim==k1D){
        // drawing 1D histograms
        Int_t total_th1 = print_th_names.size();
        Int_t total_log_th1 = log_th_names.size();
        for(Int_t i_th1=0; i_th1<total_th1; ++i_th1){
            TPad* pad = (TPad*)canvas->cd(i_pad); i_pad++;
            TH1F* th1 = (TH1F*)_root_file->Get(print_th_names[i_th1].data());
            if(th1){
                SetHistogram(th1);
                pad->SetLogy(0);
                th1->Draw();
                for(Int_t j_th1=0; j_th1<total_log_th1; ++j_th1){
                    if(print_th_names[i_th1].data()==log_th_names[j_th1]){
                        pad->SetLogy();
                        break;
                    }
                }
            }
            else{
                pad->Clear();
            }

            if(i_pad>total_pads){
                canvas->Print(_pdf_file_name.data());
                i_pad=1;
            }
        } 
        if(i_pad!=1){
            for(int j_pad=i_pad; j_pad<=total_pads; j_pad++){
                TPad* pad = (TPad*)canvas->cd(j_pad);
                pad->Clear();
            }
            canvas->Print(_pdf_file_name.data());
            i_pad=1;
        }
    }
    else if(dim==k2D){
        // drawing 2D histograms
        Int_t total_th2 = print_th_names.size();
        Int_t total_log_th2 = log_th_names.size();
        for(Int_t i_th2=0; i_th2<total_th2; i_th2++){
            TPad* pad = (TPad*)canvas->cd(i_pad); i_pad++;
            TH2F* th2 = (TH2F*)_root_file->Get(print_th_names[i_th2].data());
            if(th2){
                SetHistogram(th2);
                th2->Draw("col");
                pad->SetLogz(0);
                for(Int_t j_th2=0; j_th2<total_log_th2; ++j_th2){
                    if(print_th_names[i_th2].data()==log_th_names[j_th2]){
                        pad->SetLogz();
                        break;
                    }
                }
            }
            else{
                pad->Clear();
            }

            if(i_pad>total_pads){
                canvas->Print(_pdf_file_name.data());
                i_pad=1;
            }
        } 
        if(i_pad!=1){
            for(int j_pad=i_pad; j_pad<=total_pads; j_pad++){
                TPad* pad = (TPad*)canvas->cd(j_pad);
                pad->Clear();
            }
            canvas->Print(_pdf_file_name.data());
            i_pad=1;
        }
    }

    //canvas->Print(std::string(_pdf_file_name+"]").data());
    delete canvas;
    delete style;
    return;
}

void Analyzer::PrintSame(std::vector<std::string> th1_names, std::vector<Int_t> line_colors, std::vector<std::string> legend_names){
    TStyle* style = new TStyle("Plain","Plain Style (no colors/fill areas)");
    style->SetOptStat(0);
    style->SetOptTitle(0);
    Int_t MyPalette[100];
    Double_t Red[]    = {0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t Green[]  = {0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t Blue[]   = {0.51, 1.00, 0.12, 0.00, 0.00 };
    Double_t Length[] = {0.00, 0.34, 0.61, 0.84, 1.00 };
    Int_t FI = TColor::CreateGradientColorTable(5, Length, Red, Green, Blue, 100);
    for (int i=0;i<100;i++){
        MyPalette[i] = FI+i;
    }
    style->SetPalette(100,MyPalette);

    style->cd();

    TCanvas* canvas = new TCanvas("canvas","canvas",3200,1800);
    Int_t div_x = 3;
    Int_t div_y = 2;
    canvas->Divide(div_x,div_y);
    Int_t total_pads = div_x*div_y;

    for(Int_t i_pad=1; i_pad<=total_pads; ++i_pad){
        TPad* pad = (TPad*)canvas->cd(i_pad);
        pad->SetGrid();
        pad->SetTicks();
        pad->SetLeftMargin(0.16);
        pad->SetRightMargin(0.03);
        pad->SetTopMargin(0.05);
        pad->SetBottomMargin(0.16);
    }
    canvas->cd(1);

    Int_t total_th1 = th1_names.size();
    if(total_th1 != line_colors.size()) return;
    if(total_th1 != legend_names.size()) return;

    TLegend* legend = new TLegend(0.8,0.6,0.97,0.95);
    legend->SetLineStyle(1);
    legend->SetLineWidth(0);
    legend->SetTextFont(12);
    legend->SetMargin(0.4);
    legend->SetFillStyle(0);
    for(Int_t i_th1=0; i_th1<total_th1; ++i_th1){
        TH1F* th1 = (TH1F*)_root_file->Get(th1_names[i_th1].data());
        if(th1){
            th1->SetLineColor(line_colors[i_th1]);
            if(i_th1==0){
                SetHistogram(th1);
                th1->Draw();
            }
            else{
                th1->Draw("same");
            }
            legend->AddEntry(th1,legend_names[i_th1].data(),"l");
        }
    } 
    legend->Draw();

    canvas->Print(_pdf_file_name.data());

    delete canvas;
    delete style;
    return;
}

void Analyzer::PrintAcceptance(std::vector<std::string> gene_names, std::vector<std::string> acce_names, Double_t maximum){
    if(gene_names.size()!=acce_names.size()){
        std::cout << "number of input histograms are wrong!!" << std::endl;
        return;
    }
    TStyle* style = new TStyle("Plain","Plain Style (no colors/fill areas)");
    style->SetOptStat(0);
    style->SetOptTitle(0);
    Int_t MyPalette[100];
    Double_t Red[]    = {0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t Green[]  = {0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t Blue[]   = {0.51, 1.00, 0.12, 0.00, 0.00 };
    Double_t Length[] = {0.00, 0.34, 0.61, 0.84, 1.00 };
    Int_t FI = TColor::CreateGradientColorTable(5, Length, Red, Green, Blue, 100);
    for (int i=0;i<100;i++){
        MyPalette[i] = FI+i;
    }
    style->SetPalette(100,MyPalette);

    style->cd();

    TCanvas* canvas = new TCanvas("canvas","canvas",2400,900);
    Int_t div_x = 2;
    Int_t div_y = 1;
    canvas->Divide(div_x,div_y);
    Int_t total_pads = div_x*div_y;

    for(Int_t i_pad=1; i_pad<=total_pads; ++i_pad){
        TPad* pad = (TPad*)canvas->cd(i_pad);
        pad->SetGrid();
        pad->SetTicks();
        pad->SetLeftMargin(0.16);
        pad->SetRightMargin(0.20);
        pad->SetTopMargin(0.05);
        pad->SetBottomMargin(0.16);
    }

    Int_t i_pad = 1;


    // drawing 2D histograms
    const Int_t total_th2 = gene_names.size();
    for(Int_t i_th2=0; i_th2<total_th2; ++i_th2){

        TPad* pad = (TPad*)canvas->cd(i_pad); i_pad++;
        TH2F* th2_gene = (TH2F*)_root_file->Get(gene_names[i_th2].data());
        if(!th2_gene){
            pad->Clear();
            continue;
        }
        SetHistogram(th2_gene);
        TH2F* th2_acce = (TH2F*)_root_file->Get(acce_names[i_th2].data());
        if(!th2_acce){ 
            pad->Clear();
            continue;
        }
        TH2F* th2_acceptance = (TH2F*)th2_acce->Clone("tmp");
        SetHistogram(th2_acceptance);
        Int_t xbin_first = th2_acceptance->GetXaxis()->GetFirst();
        Int_t xbin_last = th2_acceptance->GetXaxis()->GetLast();
        Int_t ybin_first = th2_acceptance->GetYaxis()->GetFirst();
        Int_t ybin_last = th2_acceptance->GetYaxis()->GetLast();
        for(int ybin=ybin_first; ybin<=ybin_last; ++ybin){
            for(int xbin=xbin_first; xbin<=xbin_last; ++xbin){
                Double_t val = th2_acceptance->GetBinContent(xbin,ybin);
                if(th2_gene->GetBinContent(xbin,ybin)){
                    val /= th2_gene->GetBinContent(xbin,ybin);
                }
                else{
                    val = 0.;
                }
                val *= 100.;
                val *= kAnalysisEfficiency;
                val *= kSelectionEfficiency;
                th2_acceptance->SetBinContent(xbin,ybin,val);
            }
        }
        th2_acceptance->Draw("colz");
        th2_acceptance->GetZaxis()->SetTitle("#varepsilon (%)");
        th2_acceptance->SetMinimum(0.);
        th2_acceptance->SetMaximum(maximum);
        //th2_acceptance->SetMaximum(th2_acce->GetEntries()/th2_gene->GetEntries()*100.*2.);

        if(i_pad>total_pads){
            canvas->Print(_pdf_file_name.data());
            i_pad=1;
        }
    } 
    if(i_pad!=1){
        for(int j_pad=i_pad; j_pad<=total_pads; j_pad++){
            TPad* pad = (TPad*)canvas->cd(j_pad);
            pad->Clear();
        }
        canvas->Print(_pdf_file_name.data());
        i_pad=1;
    }

    //canvas->Print(std::string(_pdf_file_name+"]").data());
    delete canvas;
    delete style;
    return;
}

void Analyzer::SetHistogram(TH1* hist){
    hist->GetXaxis()->CenterTitle();
    hist->GetXaxis()->SetTitleFont(132);
    hist->GetXaxis()->SetTitleSize(0.07);
    hist->GetXaxis()->SetLabelFont(132);
    hist->GetXaxis()->SetLabelSize(0.05);
    hist->GetXaxis()->SetNdivisions(505);

    hist->GetYaxis()->CenterTitle();
    hist->GetYaxis()->SetTitleFont(132);
    hist->GetYaxis()->SetTitleSize(0.07);
    hist->GetYaxis()->SetLabelFont(132);
    hist->GetYaxis()->SetLabelSize(0.05);
    hist->GetYaxis()->SetNdivisions(505);

    hist->GetZaxis()->CenterTitle();
    hist->GetZaxis()->SetTitleFont(132);
    hist->GetZaxis()->SetTitleSize(0.07);
    hist->GetZaxis()->SetLabelFont(132);
    hist->GetZaxis()->SetLabelSize(0.05);
    hist->GetZaxis()->SetNdivisions(505);

    hist->SetLineColor(kBlack);
    hist->SetLineWidth(2);
    hist->SetMinimum(0);
}

