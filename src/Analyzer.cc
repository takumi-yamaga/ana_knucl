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
        Int_t total_th1 = (Int_t)print_th_names.size();
        Int_t total_log_th1 = (Int_t)log_th_names.size();
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
        Int_t total_th2 = (Int_t)print_th_names.size();
        Int_t total_log_th2 = (Int_t)log_th_names.size();
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

    Int_t total_th1 = (Int_t)th1_names.size();
    if(total_th1 != (Int_t)line_colors.size()) return;
    if(total_th1 != (Int_t)legend_names.size()) return;

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
    const Int_t total_th2 = (Int_t)gene_names.size();
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

void Analyzer::Print2DSlice(std::string th2_name, Int_t xy, Int_t total_slice){
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
    style->SetTitleFont(132,"XYZ");
    style->SetLabelFont(132,"XYZ");

    style->cd();

    Int_t div_x = 3;
    Int_t div_y = 2+(total_slice-1)/3;
    if(total_slice==0){
        div_y = 1;
    }
    TCanvas* canvas = new TCanvas("canvas","canvas",3200,900*div_y);
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

    TPad* pad_2d = (TPad*)canvas->cd(1);
    TH2F* th2 = (TH2F*)_root_file->Get(th2_name.data());
    if(!th2){
        delete canvas;
        delete style;
        return;
    }
    if(th2->GetEntries()==0){
        delete canvas;
        delete style;
        return;
    }
    SetHistogram(th2);
    th2->Draw("col");

    TH1F* th1_all_region;
    if(xy==kXSlice){
        th1_all_region = (TH1F*)th2->ProjectionY("th1_all_region");
    }
    else if(xy==kYSlice){
        th1_all_region = (TH1F*)th2->ProjectionX("th1_all_region");
    }
    std::cout << std::scientific << std::setprecision(4) << th2_name << " : " << th1_all_region->GetStdDev() << std::endl;

    TProfile* prof;
    if(xy==kXSlice){
        prof = (TProfile*)th2->ProfileX("th2_prof");
    }
    else if(xy==kYSlice){
        prof = (TProfile*)th2->ProfileY("th2_prof");
    }
    prof->SetErrorOption("s");
    prof->Draw("e same");

    Int_t bin_first;
    Int_t bin_last;
    Double_t bin_width;
    Double_t val_min;
    Double_t val_max;
    Double_t xval_min;
    Double_t xval_max;
    Double_t yval_min;
    Double_t yval_max;

    if(xy==kXSlice){
        bin_first = th2->GetXaxis()->GetFirst();
        bin_last = th2->GetXaxis()->GetLast();
        bin_width = th2->GetXaxis()->GetBinWidth(bin_first);
        val_min = th2->GetYaxis()->GetBinCenter(th2->GetYaxis()->GetFirst())-th2->GetYaxis()->GetBinWidth(th2->GetYaxis()->GetFirst())/2.;
        val_max = th2->GetYaxis()->GetBinCenter(th2->GetYaxis()->GetLast())+th2->GetYaxis()->GetBinWidth(th2->GetYaxis()->GetLast())/2.;
    }
    else if(xy==kYSlice){
        bin_first = th2->GetYaxis()->GetFirst();
        bin_last = th2->GetYaxis()->GetLast();
        bin_width = th2->GetYaxis()->GetBinWidth(bin_first);
        val_min = th2->GetXaxis()->GetBinCenter(th2->GetXaxis()->GetFirst())-th2->GetXaxis()->GetBinWidth(th2->GetXaxis()->GetFirst())/2.;
        val_max = th2->GetXaxis()->GetBinCenter(th2->GetXaxis()->GetLast())+th2->GetXaxis()->GetBinWidth(th2->GetXaxis()->GetLast())/2.;
    }
    else{
        delete canvas;
        delete style;
        return;
    }
    yval_min = th2->GetYaxis()->GetBinCenter(th2->GetYaxis()->GetFirst())-th2->GetYaxis()->GetBinWidth(th2->GetYaxis()->GetFirst())/2.;
    yval_max = th2->GetYaxis()->GetBinCenter(th2->GetYaxis()->GetLast())+th2->GetYaxis()->GetBinWidth(th2->GetYaxis()->GetLast())/2.;
    xval_min = th2->GetXaxis()->GetBinCenter(th2->GetXaxis()->GetFirst())-th2->GetXaxis()->GetBinWidth(th2->GetXaxis()->GetFirst())/2.;
    xval_max = th2->GetXaxis()->GetBinCenter(th2->GetXaxis()->GetLast())+th2->GetXaxis()->GetBinWidth(th2->GetXaxis()->GetLast())/2.;

    TLatex* text = new TLatex();
    text->SetTextAlign(21);
    text->SetTextFont(132);
    text->SetTextSize(0.07);

    std::vector<Double_t> x_vals;
    std::vector<Double_t> x_errs;
    std::vector<Double_t> mean_vals;
    std::vector<Double_t> stddev_vals;
    for(Int_t bin=bin_first; bin<=bin_last; ++bin){
        x_vals.push_back(prof->GetBinCenter(bin)); 
        x_errs.push_back(prof->GetBinWidth(bin)); 
        mean_vals.push_back(prof->GetBinContent(bin));
        stddev_vals.push_back(prof->GetBinError(bin));
    }

    TPad* pad_mean = (TPad*)canvas->cd(2);
    TGraphErrors* graph_mean = new TGraphErrors(x_vals.size(),x_vals.data(),mean_vals.data(),x_errs.data(),0);
    if(xy==kXSlice){
        graph_mean->GetXaxis()->SetTitle(th2->GetXaxis()->GetTitle());
        graph_mean->GetYaxis()->SetTitle(Form("mean of %s",th2->GetYaxis()->GetTitle()));
        graph_mean->GetXaxis()->SetRangeUser(xval_min,xval_max);
        graph_mean->GetHistogram()->SetMinimum(yval_min);
        graph_mean->GetHistogram()->SetMaximum(yval_max);
    }
    else if(xy==kYSlice){
        graph_mean->GetXaxis()->SetTitle(th2->GetYaxis()->GetTitle());
        graph_mean->GetYaxis()->SetTitle(Form("mean of %s",th2->GetXaxis()->GetTitle()));
        graph_mean->GetXaxis()->SetRangeUser(yval_min,yval_max);
        graph_mean->GetHistogram()->SetMinimum(xval_min);
        graph_mean->GetHistogram()->SetMaximum(xval_max);
    }
    graph_mean->GetXaxis()->CenterTitle();
    graph_mean->GetXaxis()->SetTitleSize(0.07);
    graph_mean->GetXaxis()->SetLabelSize(0.05);
    graph_mean->GetXaxis()->SetNdivisions(606);
    graph_mean->GetYaxis()->CenterTitle();
    graph_mean->GetYaxis()->SetTitleSize(0.07);
    graph_mean->GetYaxis()->SetLabelSize(0.05);
    graph_mean->GetYaxis()->SetNdivisions(606);
    graph_mean->Draw("apz");

    TPad* pad_stddev = (TPad*)canvas->cd(3);
    TGraphErrors* graph_stddev = new TGraphErrors(x_vals.size(),x_vals.data(),stddev_vals.data(),x_errs.data(),0);
    if(xy==kXSlice){
        graph_stddev->GetXaxis()->SetTitle(th2->GetXaxis()->GetTitle());
        graph_stddev->GetYaxis()->SetTitle(Form("stddev of %s",th2->GetYaxis()->GetTitle()));
        graph_stddev->GetXaxis()->SetRangeUser(xval_min,xval_max);
        graph_stddev->GetHistogram()->SetMinimum(0.);
        graph_stddev->GetHistogram()->SetMaximum(yval_max);
    }
    else if(xy==kYSlice){
        graph_stddev->GetXaxis()->SetTitle(th2->GetYaxis()->GetTitle());
        graph_stddev->GetYaxis()->SetTitle(Form("stddev of %s",th2->GetXaxis()->GetTitle()));
        graph_stddev->GetXaxis()->SetRangeUser(yval_min,yval_max);
        graph_stddev->GetHistogram()->SetMinimum(0.);
        graph_stddev->GetHistogram()->SetMaximum(xval_max);
    }
    graph_stddev->GetXaxis()->CenterTitle();
    graph_stddev->GetXaxis()->SetTitleSize(0.07);
    graph_stddev->GetXaxis()->SetLabelSize(0.05);
    graph_stddev->GetXaxis()->SetNdivisions(606);
    graph_stddev->GetYaxis()->CenterTitle();
    graph_stddev->GetYaxis()->SetTitleSize(0.07);
    graph_stddev->GetYaxis()->SetLabelSize(0.05);
    graph_stddev->GetYaxis()->SetNdivisions(606);
    graph_stddev->Draw("apz");

    if(total_slice){
        Int_t i_pad = 4;
        Int_t pitch = (bin_last-bin_first+1)/total_slice;
        for(Int_t i_slice=0; i_slice<total_slice; ++i_slice){
            Int_t bin_ll;
            Double_t val_ll;
            if(i_slice==0){
                bin_ll = bin_first;
            }
            else{
                bin_ll = i_slice*pitch;
            }
            if(xy==kXSlice){
                val_ll = th2->GetXaxis()->GetBinCenter(bin_ll)-bin_width/2.;
            }
            else if(xy==kYSlice){
                val_ll = th2->GetYaxis()->GetBinCenter(bin_ll)-bin_width/2.;
            }

            Int_t bin_ul;
            Double_t val_ul;
            if(i_slice==total_slice-1){
                bin_ul = bin_last;
            }
            else{
                bin_ul = (i_slice+1)*pitch -1;
            }
            if(xy==kXSlice){
                val_ul = th2->GetXaxis()->GetBinCenter(bin_ul)+bin_width/2.;
            }
            else if(xy==kYSlice){
                val_ul = th2->GetYaxis()->GetBinCenter(bin_ul)+bin_width/2.;
            }

            TPad* pad = (TPad*)canvas->cd(i_pad); i_pad++;
            TH1F* th1_slice;
            if(xy == kXSlice){
                th1_slice = (TH1F*)th2->ProjectionY(Form("tmp_py_%d",i_slice),bin_ll,bin_ul);
            }
            else if(xy == kYSlice){
                th1_slice = (TH1F*)th2->ProjectionX(Form("tmp_px_%d",i_slice),bin_ll,bin_ul);
            }

            SetHistogram(th1_slice);
            th1_slice->Draw("hist");    
            pad->Update();
            text->DrawLatex((val_max+val_min)/2.,pad->GetUymax(),Form("%1.2f - %1.2f",val_ll,val_ul));

            if(i_slice>0){
                pad_2d->cd();
                TLine* line = new TLine(val_ll,val_min,val_ll,val_max);
                line->SetLineWidth(2);
                line->SetLineColor(kRed-4);
                line->Draw("same");
            }
        } 
    }

    canvas->Print(_pdf_file_name.data());

    delete canvas;
    delete style;
    delete text;
    delete graph_mean;
    delete graph_stddev;

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

