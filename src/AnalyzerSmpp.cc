// AnalyzerSmpp.cc
#include"AnalyzerSmpp.hh"

#define USE_CAP
//#define PROTON_DECISION_SUCCESS
//#define PROTON_DECISION_FAILURE

AnalyzerSmpp::AnalyzerSmpp()
{
    _is_created = false;
    _root_file_name = "tmp.root";
    _pdf_file_name = _root_file_name.substr(_root_file_name.find_last_of("/"),_root_file_name.find_first_of("."));
    _pdf_file_name.append(".pdf");
    _pdf_file_name.insert(0,"./fig/tmp");
    CreateRootFile("recreate");
    random = new TRandom3(0);

    pdg = TDatabasePDG::Instance();
    if(!pdg){
    pdg = new TDatabasePDG();
    const char* tmp_root_sys = "/sw/packages/root/5.34.38";
    const char* env_root_sys = std::getenv("ROOTSYS");
    std::string pdg_file_name;
    if(env_root_sys != 0){
        pdg_file_name = env_root_sys;
    }
    else{
        pdg_file_name = tmp_root_sys;
    }
    pdg_file_name += "/etc/pdg_table.txt";
    pdg->ReadPDGTable(pdg_file_name.data());
    }

}

AnalyzerSmpp::AnalyzerSmpp(std::string file_name, std::string option)
{
    _is_created = false;
    _root_file_name = file_name;
    _pdf_file_name = _root_file_name.substr(_root_file_name.find_last_of("/"),_root_file_name.find_last_of(".")-_root_file_name.find_last_of("/"));
    _pdf_file_name.append(".pdf");
    _pdf_file_name.insert(0,"./fig/tmp");
    CreateRootFile(option);
    random = new TRandom3(0);

    pdg = TDatabasePDG::Instance();
    if(!pdg){
        is_pdg_created = true;
        pdg = new TDatabasePDG();
        const char* tmp_root_sys = "/sw/packages/root/5.34.38";
        const char* env_root_sys = std::getenv("ROOTSYS");
        std::string pdg_file_name;
        if(env_root_sys != 0){
            pdg_file_name = env_root_sys;
        }
        else{
            pdg_file_name = tmp_root_sys;
        }
        pdg_file_name += "/etc/pdg_table.txt";
        pdg->ReadPDGTable(pdg_file_name.data());
    }
    else{
        is_pdg_created = false;
    }

}

AnalyzerSmpp::~AnalyzerSmpp()
{
    if(_root_file){
        if(_is_created){
            _root_file->Write();
        }
        _root_file->Close();
    }
    if(random) delete random;
    if(is_pdg_created) delete pdg;
}
void AnalyzerSmpp::CreateRootFile(std::string option)
{
    _meas_type.push_back("gene");
    _meas_type.push_back("acce_smp1");
    _meas_type.push_back("meas_smp1");
    _meas_type.push_back("kfit_smp1");
    _meas_type.push_back("acce_smp1_true");
    _meas_type.push_back("meas_smp1_true");
    _meas_type.push_back("kfit_smp1_true");
    _meas_type.push_back("acce_smp1_fake");
    _meas_type.push_back("meas_smp1_fake");
    _meas_type.push_back("kfit_smp1_fake");
    _meas_type.push_back("acce_smp2");
    _meas_type.push_back("meas_smp2");
    _meas_type.push_back("kfit_smp2");
    _meas_type.push_back("acce_smp2_true");
    _meas_type.push_back("meas_smp2_true");
    _meas_type.push_back("kfit_smp2_true");
    _meas_type.push_back("acce_smp2_fake");
    _meas_type.push_back("meas_smp2_fake");
    _meas_type.push_back("kfit_smp2_fake");
    _meas_type.push_back("acce_smpp");
    _meas_type.push_back("meas_smpp");
    _meas_type.push_back("kfit_smpp");
    _meas_type.push_back("acce_smpp_true");
    _meas_type.push_back("meas_smpp_true");
    _meas_type.push_back("kfit_smpp_true");
    _meas_type.push_back("acce_smpp_fake");
    _meas_type.push_back("meas_smpp_fake");
    _meas_type.push_back("kfit_smpp_fake");

    _root_file = new TFile(_root_file_name.data(),option.data());
    if(option=="read"||option=="READ"){
        return;
    }
    _root_file->cd();

    for(UInt_t i_type=0; i_type<_meas_type.size(); ++i_type){

        // 1D histograms ------------------------------------------------------------------------------
        new TH1F(Form("beam_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of K^{-}-beam;#font[12]{p}_{K^{-}}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("sigmam_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of #Sigma^{-};#font[12]{p}_{#Sigma^{-}}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("proton1_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of proton1;#font[12]{p}_{#font[12]{p}_{1}}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("proton2_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of proton2;#font[12]{p}_{#font[12]{n}_{2}}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("pi_from_sigmam_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of #pi from #Sigma^{-};#font[12]{p}_{#pi from #Sigma^{-}}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("nucleon_from_sigmam_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of nucleon from #Sigma^{-};#font[12]{p}_{#font[12]{N} from #Sigma^{-}}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("sigmam_mass_%s",_meas_type[i_type].data()),"Mass of #Sigma^{-};#font[12]{m}_{#Sigma^{-}}^{lab} (GeV/#font[12]{c}^{2});Counts", 200, 1.00, 1.40);
        new TH1F(Form("proton1_mass_%s",_meas_type[i_type].data()),"Mass of proton;#font[12]{m}_{#font[12]{p}_{1}}^{lab} (GeV/#font[12]{c}^{2});Counts", 150, 0.3, 1.8);
        new TH1F(Form("proton2_mass_%s",_meas_type[i_type].data()),"Mass of neutron;#font[12]{m}_{#font[12]{p}_{2}}^{lab} (GeV/#font[12]{c}^{2});Counts", 150, 0.3, 1.8);
        new TH1F(Form("smp1_mass_%s",_meas_type[i_type].data()),"Mass of #Sigma^{-}p_{1};#font[12]{m}_{#Sigma^{-}#font[12]{p}_{1}}^{lab} (GeV/#font[12]{c}^{2});Counts", 100, 2.0, 3.0);
        new TH1F(Form("smp1_momtrans_%s",_meas_type[i_type].data()),"Momentum transfer of #Sigma^{-}p_{1};#font[12]{q}_{#Sigma^{-}#font[12]{p}_{2}}^{lab} (GeV/#font[12]{c});Counts", 200, 0.0, 2.0);
        new TH1F(Form("smp2_mass_%s",_meas_type[i_type].data()),"Mass of #Sigma^{-}p_{2};#font[12]{m}_{#Sigma^{-}#font[12]{p}_{2}}^{lab} (GeV/#font[12]{c}^{2});Counts", 100, 2.0, 3.0);
        new TH1F(Form("smp2_momtrans_%s",_meas_type[i_type].data()),"Momentum transfer of #Sigma^{-}p_{2};#font[12]{q}_{#Sigma^{-}#font[12]{p}_{2}}^{lab} (GeV/#font[12]{c});Counts", 200, 0.0, 2.0);

        new TH1F(Form("neutral_energy_deposit_%s",_meas_type[i_type].data()),"Energy depoist of neutral particle;#font[12]{dE} (MeVee);Counts", 200, 0.0, 200.0);
        new TH1F(Form("neutral_over_beta_%s",_meas_type[i_type].data()),"1/#beta of neutral particle;1/#beta;Counts", 100, 0.0, 100.0);
        new TH1F(Form("neutral_time_%s",_meas_type[i_type].data()),"Hit time of neutral particle;#font[12]{t} (ns);Counts", 100, 0.0, 100.0);
        new TH1F(Form("neutral_generation_%s",_meas_type[i_type].data()),"Generation of neutral particle;Generation;Counts", 11, -0.5, 10.5);
        new TH1F(Form("neutral_charge_%s",_meas_type[i_type].data()),"Charge of neutral particle;Charge;Counts", 7, -3.5, 3.5);
        new TH1F(Form("neutral_parent_charge_%s",_meas_type[i_type].data()),"Charge of parent neutral particle;Charge;Counts", 7, -3.5, 3.5);
        new TH1F(Form("neutral_grand_parent_charge_%s",_meas_type[i_type].data()),"Charge of grand parent neutral particle;Charge;Counts", 7, -3.5, 3.5);
        new TH1F(Form("neutral_2grand_parent_charge_%s",_meas_type[i_type].data()),"Charge of 2grand parent neutral particle;Charge;Counts", 7, -3.5, 3.5);
        new TH1F(Form("neutral_3grand_parent_charge_%s",_meas_type[i_type].data()),"Charge of 3grand parent neutral particle;Charge;Counts", 7, -3.5, 3.5);
        new TH1F(Form("neutral_4grand_parent_charge_%s",_meas_type[i_type].data()),"Charge of 4grand parent neutral particle;Charge;Counts", 7, -3.5, 3.5);

        new TH1F(Form("reduced_chisquare_%s",_meas_type[i_type].data()),"Reduced chi-square of kinemataical fitting;#chi^{2}/ndf;Counts", 100, 0., 10.);
        // 1D histograms ------------------------------------------------------------------------------


        // 2D histograms ------------------------------------------------------------------------------
        new TH2F(Form("beam_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of K^{-}-beam (lab. frame);cos#theta_{K^{-}}^{lab};#phi_{K^{-}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("sigmam_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of #Sigma^{-} (lab. frame);cos#theta_{#Sigma^{-}}^{lab};#phi_{#Sigma^{-}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("proton1_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of proton1 (lab. frame);cos#theta_{#font[12]{p}_{1}}^{lab};#phi_{#font[12]{p}_{1}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("proton2_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of proton2 (lab. frame);cos#theta_{#font[12]{p}_{2}}^{lab};#phi_{#font[12]{p}_{2}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("pi_from_sigmam_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of pi_from_sigmam (lab. frame);cos#theta_{#pi from #Sigma^{-}}^{lab};#phi_{#font[12]{n}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("nucleon_from_sigmam_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of nucleon_from_sigmam (lab. frame);cos#theta_{#font[12]{N} from #Sigma^{-}}^{lab};#phi_{#font[12]{N} from #Sigma^{-}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());

        new TH2F(Form("smp1_mass_vs_momtrans_%s",_meas_type[i_type].data()),"Mass vs. momentum transfer of #Sigma^{-}p_{1};#font[12]{m}_{#Sigma^{-}#font[12]{p}_{1}} (GeV/#font[12]{c}^{2});#font[12]{q}_{#Sigma^{-}#font[12]{p}_{1}} (GeV/#font[12]{c})", 50,2.,3.,100,0.,2.);
        new TH2F(Form("smp2_mass_vs_momtrans_%s",_meas_type[i_type].data()),"Mass vs. momentum transfer of #Sigma^{-}p_{2};#font[12]{m}_{#Sigma^{-}#font[12]{p}_{2}} (GeV/#font[12]{c}^{2});#font[12]{q}_{#Sigma^{-}#font[12]{p}_{2}} (GeV/#font[12]{c})", 50,2.,3.,100,0.,2.);

        new TH2F(Form("neutral_generated_position_r_vs_z_%s",_meas_type[i_type].data()),"R vs. Z of neutral generated position;#font[12]{z} (cm);#font[12]{r} (cm);Counts", 100,-200.,200.,40,0.,160.);
        new TH2F(Form("neutral_parent_generated_position_r_vs_z_%s",_meas_type[i_type].data()),"R vs. Z of neutral parent generated position;#font[12]{z} (cm);#font[12]{r} (cm);Counts", 100,-200.,200.,40,0.,160.);
        new TH2F(Form("neutral_grand_parent_generated_position_r_vs_z_%s",_meas_type[i_type].data()),"R vs. Z of neutral grand parent generated position;#font[12]{z} (cm);#font[12]{r} (cm);Counts", 100,-200.,200.,40,0.,160.);
        new TH2F(Form("neutral_2grand_parent_generated_position_r_vs_z_%s",_meas_type[i_type].data()),"R vs. Z of neutral 2grand parent generated position;#font[12]{z} (cm);#font[12]{r} (cm);Counts", 100,-200.,200.,40,0.,160.);
        new TH2F(Form("neutral_3grand_parent_generated_position_r_vs_z_%s",_meas_type[i_type].data()),"R vs. Z of neutral 3grand parent generated position;#font[12]{z} (cm);#font[12]{r} (cm);Counts", 100,-200.,200.,40,0.,160.);
        new TH2F(Form("neutral_4grand_parent_generated_position_r_vs_z_%s",_meas_type[i_type].data()),"R vs. Z of neutral 4grand parent generated position;#font[12]{z} (cm);#font[12]{r} (cm);Counts", 100,-200.,200.,40,0.,160.);

        new TH2F(Form("proton1_momentum_lab_vs_proton2_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of proton1 vs. momentum of proton2;#font[12]{p}_{#font[12]{p}_{1}} (GeV/#font[12]{c});#font[12]{p}_{#font[12]{p}_{2}} (GeV/#font[12]{c});Counts", 100,0.,2.,100,0.,2.);

        // resolution plots
        new TH2F(Form("resolution_beam_momentum_%s",_meas_type[i_type].data()),"Resolution of beam momentum;#font[12]{p}_{K^{-}} (GeV/#font[12]{c});#Delta#font[12]{p}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("resolution_sigmam_momentum_%s",_meas_type[i_type].data()),"Resolution of #Sigma^{-} momentum;#font[12]{p}_{#Sigma^{-}} (GeV/#font[12]{c});#Delta#font[12]{p}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("resolution_proton1_momentum_%s",_meas_type[i_type].data()),"Resolution of proton momentum;#font[12]{p}_{#font[12]{p}_{1}} (GeV/#font[12]{c});#Delta#font[12]{p}/#font[12]{p}_{1};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("resolution_proton2_momentum_%s",_meas_type[i_type].data()),"Resolution of proton momentum;#font[12]{p}_{#font[12]{p}_{2}} (GeV/#font[12]{c});#Delta#font[12]{p}/#font[12]{p}_{2};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("resolution_pi_from_sigmam_momentum_%s",_meas_type[i_type].data()),"Resolution of #pi from #Sigma^{-} momentum;#font[12]{p}_{#pi from #Sigma^{-}} (GeV/#font[12]{c});#Delta#font[12]{p}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("resolution_nucleon_from_sigmam_momentum_%s",_meas_type[i_type].data()),"Resolution of nucleon from #Sigma^{-} momentum;#font[12]{p}_{#font[12]{N} from #Sigma^{-}} (GeV/#font[12]{c});#Delta#font[12]{p}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);

        new TH2F(Form("resolution_smp1_mass_%s",_meas_type[i_type].data()),"Resolution of #Sigma^{-}p_{1} mass;#font[12]{m}_{#Sigma^{-}#font[12]{p}_{1}} (GeV/#font[12]{c}^{2});#Delta#font[12]{m}/#font[12]{m};Counts", 50,2.,3.,80,-0.2,0.2);
        new TH2F(Form("resolution_smp1_momtrans_%s",_meas_type[i_type].data()),"Resolution of #Sigma^{-}p_{1} momentum transfer;#font[12]{q}_{#Sigma^{-}#font[12]{p}_{1}} (GeV/#font[12]{c});#Delta#font[12]{q}/#font[12]{q};Counts", 100,0.,2.,80,-0.2,0.2);
        new TH2F(Form("resolution_smp2_mass_%s",_meas_type[i_type].data()),"Resolution of #Sigma^{-}p_{2} mass;#font[12]{m}_{#Sigma^{-}#font[12]{p}_{2}} (GeV/#font[12]{c}^{2});#Delta#font[12]{m}/#font[12]{m};Counts", 50,2.,3.,80,-0.2,0.2);
        new TH2F(Form("resolution_smp2_momtrans_%s",_meas_type[i_type].data()),"Resolution of #Sigma^{-}p_{2} momentum transfer;#font[12]{q}_{#Sigma^{-}#font[12]{p}_{2}} (GeV/#font[12]{c});#Delta#font[12]{q}/#font[12]{q};Counts", 100,0.,2.,80,-0.2,0.2);

        // covariance for kinematical fitting
        new TH2F(Form("covariance_beam_px_%s",_meas_type[i_type].data()),"Covariance of beam p_{x};#font[12]{p}_{K^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{x}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_sigmam_px_%s",_meas_type[i_type].data()),"Covariance of #Sigma^{-} p_{x};#font[12]{p}_{#Sigma^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{x}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_proton1_px_%s",_meas_type[i_type].data()),"Covariance of proton1 p_{x};#font[12]{p}_{#font[12]{p}_{1}} (GeV/#font[12]{c});#Delta#font[12]{p_{x}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_proton2_px_%s",_meas_type[i_type].data()),"Covariance of proton2 p_{x};#font[12]{p}_{#font[12]{p}_{2}} (GeV/#font[12]{c});#Delta#font[12]{p_{x}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_pi_from_sigmam_px_%s",_meas_type[i_type].data()),"Covariance of #pi from #Sigma^{-} p_{x};#font[12]{p}_{#pi from #Sigma^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{x}}/#font[12]{p};Counts", 75,0.,0.5,80,-0.1,0.1);
        new TH2F(Form("covariance_nucleon_from_sigmam_px_%s",_meas_type[i_type].data()),"Covariance of nucleon from #Sigma^{-} p_{x};#font[12]{p}_{#font[12]{N} from #Sigma^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{x}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);

        new TH2F(Form("covariance_beam_py_%s",_meas_type[i_type].data()),"Covariance of beam p_{y};#font[12]{p}_{K^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{y}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_sigmam_py_%s",_meas_type[i_type].data()),"Covariance of #Sigma^{-} p_{y};#font[12]{p}_{#Sigma^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{y}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_proton1_py_%s",_meas_type[i_type].data()),"Covariance of proton1 p_{y};#font[12]{p}_{#font[12]{p}_{1}} (GeV/#font[12]{c});#Delta#font[12]{p_{y}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_proton2_py_%s",_meas_type[i_type].data()),"Covariance of proton2 p_{y};#font[12]{p}_{#font[12]{p}_{2}} (GeV/#font[12]{c});#Delta#font[12]{p_{y}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_pi_from_sigmam_py_%s",_meas_type[i_type].data()),"Covariance of #pi from #Sigma^{-} p_{y};#font[12]{p}_{#pi from #Sigma^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{y}}/#font[12]{p};Counts", 75,0.,0.5,80,-0.1,0.1);
        new TH2F(Form("covariance_nucleon_from_sigmam_py_%s",_meas_type[i_type].data()),"Covariance of nucleon from #Sigma^{-} p_{y};#font[12]{p}_{#font[12]{N} from #Sigma^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{y}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);

        new TH2F(Form("covariance_beam_pz_%s",_meas_type[i_type].data()),"Covariance of beam p_{z};#font[12]{p}_{K^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{z}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_sigmam_pz_%s",_meas_type[i_type].data()),"Covariance of #Sigma^{-} p_{z};#font[12]{p}_{#Sigma^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{z}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_proton1_pz_%s",_meas_type[i_type].data()),"Covariance of proton1 p_{z};#font[12]{p}_{#font[12]{p}_{1}} (GeV/#font[12]{c});#Delta#font[12]{p_{z}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_proton2_pz_%s",_meas_type[i_type].data()),"Covariance of proton2 p_{z};#font[12]{p}_{#font[12]{p}_{2}} (GeV/#font[12]{c});#Delta#font[12]{p_{z}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_pi_from_sigmam_pz_%s",_meas_type[i_type].data()),"Covariance of #pi from #Sigma^{-} p_{z};#font[12]{p}_{#pi from #Sigma^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{z}}/#font[12]{p};Counts", 75,0.,0.5,80,-0.1,0.1);
        new TH2F(Form("covariance_nucleon_from_sigmam_pz_%s",_meas_type[i_type].data()),"Covariance of nucleon from #Sigma^{-} p_{z};#font[12]{p}_{#font[12]{N} from #Sigma^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{z}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);

        // 2D histograms ------------------------------------------------------------------------------
    }


    // for neutral detection
    new TH2F("neutral_over_beta_vs_energy_deposit_meas","1/#beta vs. dE of neutral particle;1/#beta;dE (MeVee)", 100, 0.0, 10.0, 100, 0.0, 100.0);

    _is_created = true;
}

void AnalyzerSmpp::DoAnalysis(MCData* mcData, DetectorData* detectorData, AnalyzedData* analyzedData)
{

    // ============================================================================================
    // For MCData =================================================================================
    // ============================================================================================
    Int_t total_tracks = mcData->trackSize();   

    TVector3 vec_vertex_reaction(0.,0.,0.);
    TLorentzVector lv_beam_mc(0.,0.,0.,0.);
    TLorentzVector lv_sigmam_mc(0.,0.,0.,0.);
    TLorentzVector lv_proton1_mc(0.,0.,0.,0.); // having smaller track id
    TLorentzVector lv_proton2_mc(0.,0.,0.,0.); // having larger track id
    Int_t track_id_proton_smaller = 0;
    Int_t track_id_sigmam = 0;
    // check generated particle (parentTrackID==0)
    for(Int_t i_track = 0; i_track<total_tracks; i_track++){
        Track* track = mcData->track(i_track);
        if(track->parentTrackID()!=0) continue;
        Int_t pdg_id = track->pdgID();
        if(pdg_id==321){ // K-beam
            vec_vertex_reaction = track->vertex()*0.1; // cm
            lv_beam_mc.SetVectM(-track->momentum()*0.001,kKaonMass);
        }
        else if(pdg_id==3112){ // Sigma-
            track_id_sigmam = track->trackID();
            lv_sigmam_mc.SetVectM(track->momentum()*0.001,kSigmaMinusMass);
        }
        else if(pdg_id==2212){ // proton
            if(track_id_proton_smaller == 0){
                lv_proton1_mc.SetVectM(track->momentum()*0.001,kProtonMass);
                track_id_proton_smaller = track->trackID();
            }
            else{
                if(track->trackID()>track_id_proton_smaller){
                    lv_proton2_mc.SetVectM(track->momentum()*0.001,kProtonMass);
                }
                else{
                    lv_proton2_mc.SetVectM(lv_proton1_mc.Vect(),kProtonMass);
                    lv_proton1_mc.SetVectM(track->momentum()*0.001,kProtonMass);
                    track_id_proton_smaller = track->trackID();
                }
            }
        }
    }

    TVector3 vec_vertex_sigmam_decay(0.,0.,0.);
    TLorentzVector lv_pi_from_sigmam_mc(0.,0.,0.,0.);
    TLorentzVector lv_nucleon_from_sigmam_mc(0.,0.,0.,0.);
    // check decay product (parentTrackID == track_id_sigmam)
    for(Int_t i_track = 0; i_track<total_tracks; i_track++){
        Track* track = mcData->track(i_track);
        if(track->parentTrackID()!=track_id_sigmam) continue;
        Int_t pdg_id = track->pdgID();
        if(pdg_id==-211){ // pi-
            vec_vertex_sigmam_decay = track->vertex()*0.1; // cm
            lv_pi_from_sigmam_mc.SetVectM(track->momentum()*0.001,kPiMass);
        }
        else if(pdg_id==2112){ // neutron
            lv_nucleon_from_sigmam_mc.SetVectM(track->momentum()*0.001,kNeutronMass);
        }
    }
    // ============================================================================================
    // ============================================================================================
    // ============================================================================================


    // ============================================================================================
    // For AnalyzedData ===========================================================================
    // ============================================================================================
    std::vector<Track*> measured_beam_tracks = analyzedData->measured_beam_tracks();
    std::vector<Track*> measured_charged_tracks = analyzedData->measured_charged_tracks();
    std::vector<Track*> measured_charged_capb_tracks = analyzedData->measured_charged_capb_tracks();
    std::vector<Track*> measured_charged_capf_tracks = analyzedData->measured_charged_capf_tracks();
    std::vector<Track*> measured_neutral_tracks = analyzedData->measured_neutral_tracks();
    std::vector<Track*> measured_neutral_capb_tracks = analyzedData->measured_neutral_capb_tracks();
    std::vector<Track*> measured_neutral_capf_tracks = analyzedData->measured_neutral_capf_tracks();
    std::vector<Double_t> measured_neutral_energy_deposits = analyzedData->measured_neutral_energy_deposits();
    std::vector<Double_t> measured_neutral_capb_energy_deposits = analyzedData->measured_neutral_capb_energy_deposits();
    std::vector<Double_t> measured_neutral_capf_energy_deposits = analyzedData->measured_neutral_capf_energy_deposits();
    std::vector<Double_t> measured_neutral_over_betas = analyzedData->measured_neutral_over_betas();
    std::vector<Double_t> measured_neutral_capb_over_betas = analyzedData->measured_neutral_capb_over_betas();
    std::vector<Double_t> measured_neutral_capf_over_betas = analyzedData->measured_neutral_capf_over_betas();
    std::vector<Double_t> measured_neutral_times = analyzedData->measured_neutral_times();
    std::vector<Double_t> measured_neutral_capb_times = analyzedData->measured_neutral_capb_times();
    std::vector<Double_t> measured_neutral_capf_times = analyzedData->measured_neutral_capf_times();
#ifdef USE_CAP
    measured_charged_tracks.insert(measured_charged_tracks.end(),measured_charged_capb_tracks.begin(),measured_charged_capb_tracks.end());
    measured_charged_tracks.insert(measured_charged_tracks.end(),measured_charged_capf_tracks.begin(),measured_charged_capf_tracks.end());
    measured_neutral_tracks.insert(measured_neutral_tracks.end(),measured_neutral_capb_tracks.begin(),measured_neutral_capb_tracks.end());
    measured_neutral_tracks.insert(measured_neutral_tracks.end(),measured_neutral_capf_tracks.begin(),measured_neutral_capf_tracks.end());
    measured_neutral_energy_deposits.insert(measured_neutral_energy_deposits.end(),measured_neutral_capb_energy_deposits.begin(),measured_neutral_capb_energy_deposits.end());
    measured_neutral_energy_deposits.insert(measured_neutral_energy_deposits.end(),measured_neutral_capf_energy_deposits.begin(),measured_neutral_capf_energy_deposits.end());
    measured_neutral_over_betas.insert(measured_neutral_over_betas.end(),measured_neutral_capb_over_betas.begin(),measured_neutral_capb_over_betas.end());
    measured_neutral_over_betas.insert(measured_neutral_over_betas.end(),measured_neutral_capf_over_betas.begin(),measured_neutral_capf_over_betas.end());
    measured_neutral_times.insert(measured_neutral_times.end(),measured_neutral_capb_times.begin(),measured_neutral_capb_times.end());
    measured_neutral_times.insert(measured_neutral_times.end(),measured_neutral_capf_times.begin(),measured_neutral_capf_times.end());
#endif
    TLorentzVector lv_beam_meas(0.,0.,0.,0.);
    TLorentzVector lv_proton1_meas(0.,0.,0.,0.);
    TLorentzVector lv_proton2_meas(0.,0.,0.,0.);
    TLorentzVector lv_nucleon_from_sigmam_meas(0.,0.,0.,0.);
    TLorentzVector lv_pi_from_sigmam_meas(0.,0.,0.,0.);
    TLorentzVector lv_target_meas(0.,0.,0.,kThreeHeMass);
    TLorentzVector lv_sigmam_meas(0.,0.,0.,0.);
    TLorentzVector lv_detected_proton1_meas(0.,0.,0.,0.);
    TLorentzVector lv_detected_proton2_meas(0.,0.,0.,0.);
    TLorentzVector lv_missing_proton1_meas(0.,0.,0.,0.);
    TLorentzVector lv_missing_proton2_meas(0.,0.,0.,0.);
    Int_t measured_neutral_generation = -999;
    TVector3 vec_neutral_generated_position(999.,999.,999.);
    Double_t measured_neutral_charge = -999.;
    std::vector<TVector3> vec_neutral_parent_generated_positions;
    std::vector<Double_t> measured_parent_neutral_charges;
    Double_t measured_neutral_energy_deposit = -999.;
    Double_t measured_neutral_over_beta = -999.;
    Double_t measured_neutral_time = -999.;

    bool is_beam_detected = false;
    bool is_proton1_detected = false;
    bool is_proton2_detected = false;
    bool is_proton_decision_success = false;
    bool is_neutron_from_sigmam_detected = false;
    bool is_true_neutron_from_sigmam_detected = false;
    bool is_fake_neutron_from_sigmam_detected = false;
    bool is_pim_from_sigmam_detected = false;

    // beam
    if(measured_beam_tracks.size()==1){
        if(measured_beam_tracks[0]->pdgID()==-321){
            is_beam_detected = true;
            lv_beam_meas.SetVectM(measured_beam_tracks[0]->momentum(),kKaonMass);
        }
    }

    // two protons & one pi-
    for(std::vector<Track*>::iterator itr_measured_charged_tracks=measured_charged_tracks.begin(); itr_measured_charged_tracks!=measured_charged_tracks.end(); itr_measured_charged_tracks++){
        Track* track = *itr_measured_charged_tracks;
        if(track->pdgID()==2212){
            if(is_proton1_detected == false){
                is_proton1_detected = true;
                lv_detected_proton1_meas.SetVectM(track->momentum(),kProtonMass);
                if(track->trackID()==track_id_sigmam){
                    is_proton_decision_success = true;
                }
                else{
                    is_proton_decision_success = false;
                }
            }
            else if(track->momentum().Mag()>lv_detected_proton1_meas.P()){
                is_proton2_detected = true;
                lv_detected_proton2_meas.SetVectM(track->momentum(),kProtonMass);
            }
            else{
                is_proton2_detected = true;
                lv_detected_proton2_meas.SetVectM(lv_detected_proton1_meas.Vect(),kProtonMass);
                lv_detected_proton1_meas.SetVectM(track->momentum(),kProtonMass);
                if(track->trackID()==track_id_sigmam){
                    is_proton_decision_success = true;
                }
                else{
                    is_proton_decision_success = false;
                }
            }

        }
        else if(track->pdgID()==-211&&track->parentTrackID()!=0){
            is_pim_from_sigmam_detected = true;
            lv_pi_from_sigmam_meas.SetVectM(track->momentum(),kPiMass);
        }
    }

    // neutron
    if(measured_neutral_tracks.size()==1){
        is_neutron_from_sigmam_detected = true;
        Int_t parent_id = measured_neutral_tracks[0]->parentTrackID();
        lv_nucleon_from_sigmam_meas.SetVectM(measured_neutral_tracks[0]->momentum(),kNeutronMass);
        measured_neutral_energy_deposit = measured_neutral_energy_deposits[0];
        measured_neutral_over_beta = measured_neutral_over_betas[0];
        measured_neutral_time = measured_neutral_times[0];
        Int_t track_id = measured_neutral_tracks[0]->trackID();
        for(Int_t i_track = 0; i_track<total_tracks; i_track++){
            Track* track = mcData->track(i_track);
            if(track->trackID()==track_id){
                vec_neutral_generated_position = track->vertex()*0.1; // cm 
            }
            TParticlePDG* particle = pdg->GetParticle(track->pdgID());
            if(particle){
                measured_neutral_charge = particle->Charge()/3.; // unit in |e|
            }
            else{
                measured_neutral_charge = -999.;
            }
        }

        for(Int_t i_track = 0; i_track<total_tracks; i_track++){
            Track* track = mcData->track(i_track);
            if(track->trackID()==parent_id){
                vec_neutral_parent_generated_positions.push_back(track->vertex()*0.1); // cm 
                TParticlePDG* particle = pdg->GetParticle(track->pdgID());
                if(particle){
                    measured_parent_neutral_charges.push_back(particle->Charge()/3.); // unit in |e|
                }
                else{
                    measured_parent_neutral_charges.push_back(-999.);
                }
                if(track->parentTrackID()!=track_id_sigmam){
                    parent_id = track->parentTrackID();
                    i_track=-1;
                }
                else{
                    parent_id = track_id_sigmam;
                    if(track->pdgID()==2112){
                        is_true_neutron_from_sigmam_detected = true;
                    }
                    else{
                        is_fake_neutron_from_sigmam_detected = true;
                    }
                }
            }
            if(parent_id==0) break;
        }
        if(parent_id!=track_id_sigmam){
            is_fake_neutron_from_sigmam_detected = true;
        }
    }
    measured_neutral_generation = vec_neutral_parent_generated_positions.size();

    if(measured_neutral_generation!=1){
        is_true_neutron_from_sigmam_detected = false;
        is_fake_neutron_from_sigmam_detected = is_neutron_from_sigmam_detected;
    }

    lv_sigmam_meas = lv_nucleon_from_sigmam_meas + lv_pi_from_sigmam_meas;
    lv_missing_proton1_meas = (lv_beam_meas+lv_target_meas) - (lv_sigmam_meas+lv_detected_proton2_meas);
    lv_missing_proton2_meas = (lv_beam_meas+lv_target_meas) - (lv_sigmam_meas+lv_detected_proton1_meas);

    bool is_accepted_smp1 = is_beam_detected & is_proton1_detected & is_neutron_from_sigmam_detected & is_pim_from_sigmam_detected;
    bool is_accepted_smp1_true = is_beam_detected & is_proton1_detected & is_true_neutron_from_sigmam_detected & is_pim_from_sigmam_detected;
    bool is_accepted_smp1_fake = is_beam_detected & is_proton1_detected & is_fake_neutron_from_sigmam_detected & is_pim_from_sigmam_detected;
    bool is_accepted_smp2 = is_beam_detected & is_proton2_detected & is_neutron_from_sigmam_detected & is_pim_from_sigmam_detected;
    bool is_accepted_smp2_true = is_beam_detected & is_proton2_detected & is_true_neutron_from_sigmam_detected & is_pim_from_sigmam_detected;
    bool is_accepted_smp2_fake = is_beam_detected & is_proton2_detected & is_fake_neutron_from_sigmam_detected & is_pim_from_sigmam_detected;
    bool is_accepted_smpp = is_accepted_smp1 & is_accepted_smp2;
    bool is_accepted_smpp_true = is_accepted_smp1_true & is_accepted_smp2_true;
    bool is_accepted_smpp_fake = is_accepted_smp1_fake & is_accepted_smp2_fake;
#ifdef PROTON_DECISION_SUCCESS
    is_accepted_smp1 = is_accepted_smp1 & is_proton_decision_success;
    is_accepted_smp1_true = is_accepted_smp1_true & is_proton_decision_success;
    is_accepted_smp1_fake = is_accepted_smp1_fake & is_proton_decision_success;
    is_accepted_smp2 = is_accepted_smp2 & is_proton_decision_success;
    is_accepted_smp2_true = is_accepted_smp2_true & is_proton_decision_success;
    is_accepted_smp2_fake = is_accepted_smp2_fake & is_proton_decision_success;
    is_accepted_smpp = is_accepted_smpp & is_proton_decision_success;
    is_accepted_smpp_true = is_accepted_smpp_true & is_proton_decision_success;
    is_accepted_smpp_fake = is_accepted_smpp_fake & is_proton_decision_success;
#endif
#ifdef PROTON_DECISION_FAILURE
    is_accepted_smp1 = is_accepted_smp1 & !is_proton_decision_success;
    is_accepted_smp1_true = is_accepted_smp1_true & !is_proton_decision_success;
    is_accepted_smp1_fake = is_accepted_smp1_fake & !is_proton_decision_success;
    is_accepted_smp2 = is_accepted_smp2 & !is_proton_decision_success;
    is_accepted_smp2_true = is_accepted_smp2_true & !is_proton_decision_success;
    is_accepted_smp2_fake = is_accepted_smp2_fake & !is_proton_decision_success;
    is_accepted_smpp = is_accepted_smpp & !is_proton_decision_success;
    is_accepted_smpp_true = is_accepted_smpp_true & !is_proton_decision_success;
    is_accepted_smpp_fake = is_accepted_smpp_fake & !is_proton_decision_success;
#endif
    // ============================================================================================
    // ============================================================================================
    // ============================================================================================


    // ============================================================================================
    // Kinematical fitting ========================================================================
    // ============================================================================================
    TLorentzVector lv_beam_kfit;
    TLorentzVector lv_sigmam_kfit;
    TLorentzVector lv_proton1_kfit;
    TLorentzVector lv_proton2_kfit;
    TLorentzVector lv_pi_from_sigmam_kfit;
    TLorentzVector lv_nucleon_from_sigmam_kfit;
    Double_t reduced_chisquare_kfit;

    // for smp1 detection -----------------------------------
    Double_t reduced_chisquare_smp1 = -999.;
    const Int_t total_particles_smp1 = 7;
    TLorentzVector lv_kfit_smp1[total_particles_smp1];
    if(is_accepted_smp1){
        // [0] : target
        // [1] : beam
        // [2] : sigma-
        // [3] : proton
        // [4] : proton (missing)
        // [5] : pi- from sigmam
        // [6] : neutron from sigmam
        Double_t val_covariance_proton[9];
        GetCovarianceProton(lv_detected_proton1_meas.P(),val_covariance_proton);
        Double_t val_covariance_pi_from_sigmam[9];
        GetCovariancePi(lv_pi_from_sigmam_meas.P(),val_covariance_pi_from_sigmam);
        Double_t val_covariance_nucleon_from_sigmam[9];
        GetCovarianceNeutron(lv_nucleon_from_sigmam_meas.P(),val_covariance_nucleon_from_sigmam);

        TLorentzVector* lv_meas[total_particles_smp1] = {&lv_target_meas,&lv_beam_meas,&lv_sigmam_meas,&lv_detected_proton1_meas,&lv_missing_proton2_meas,&lv_pi_from_sigmam_meas,&lv_nucleon_from_sigmam_meas};
        Double_t masses[total_particles_smp1] = {kThreeHeMass,kKaonMass,kSigmaMinusMass,kProtonMass,kProtonMass,kPiMass,kNeutronMass};
        TMatrixD* covariances[total_particles_smp1];
        covariances[0] = new TMatrixD(3,3,kValCovarianceZero);                  // : target
        covariances[1] = new TMatrixD(3,3,kValCovarianceBeam);                  // : beam
        covariances[2] = new TMatrixD(3,3,kValCovarianceZero);                  // : sigma-
        covariances[3] = new TMatrixD(3,3,val_covariance_proton);               // : proton
        covariances[4] = new TMatrixD(3,3,kValCovarianceZero);                  // : proton (missing)
        covariances[5] = new TMatrixD(3,3,val_covariance_pi_from_sigmam);       // : pim from sigmam
        covariances[6] = new TMatrixD(3,3,val_covariance_nucleon_from_sigmam);  // : neutron from sigmam
        TFitParticlePxPyPz particles[total_particles_smp1];
        for(Int_t i_particle=0; i_particle<total_particles_smp1; ++i_particle){
            TVector3 vec_momentum = lv_meas[i_particle]->Vect();
            particles[i_particle] = TFitParticlePxPyPz(Form("particle_%d",i_particle), Form("particle_%d",i_particle), &vec_momentum, masses[i_particle], covariances[i_particle]);
        }

        // constraint :: mass of sigmam
        TFitConstraintM constraint_sigmam_mass = TFitConstraintM("sigmam_mass", "sigmam_mass", 0, 0, kSigmaMinusMass);
        constraint_sigmam_mass.addParticles1(&particles[5], &particles[6]);
        // constraint :: 4-momentum conservation
        TFitConstraintEp constraint_conservation[4];
        for(Int_t i_element=0; i_element<4; ++i_element){
            constraint_conservation[i_element] = TFitConstraintEp(Form("element_%d",i_element),Form("element_%d",i_element), 0, TFitConstraintEp::component(i_element), 0);
            constraint_conservation[i_element].addParticles1(&particles[0], &particles[1]);
            constraint_conservation[i_element].addParticles2(&particles[3], &particles[4], &particles[5], &particles[6]);
        }

        TKinFitter kinfitter;
        kinfitter.addMeasParticles(&particles[1], &particles[3], &particles[5], &particles[6]);
        kinfitter.addUnmeasParticles(&particles[4]);
        // add constraints
        kinfitter.addConstraint(&constraint_sigmam_mass);
        for(Int_t i_element=0; i_element<4; ++i_element){
            kinfitter.addConstraint(&constraint_conservation[i_element]);
        }
        // fitting
        kinfitter.setMaxNbIter(50);       // max number of iterations
        kinfitter.setMaxDeltaS(5e-5);     // max delta chi2
        kinfitter.setMaxF(1e-4);          // max sum of constraints
        kinfitter.setVerbosity(0);        // verbosity level
        kinfitter.fit();
        // fitting results
        reduced_chisquare_smp1 = kinfitter.getS()/kinfitter.getNDF();
        for(Int_t i_particle=0; i_particle<total_particles_smp1; ++i_particle){
            lv_kfit_smp1[i_particle] = (*particles[i_particle].getCurr4Vec());
            delete covariances[i_particle];
        }
    }
    // for smp1 detection -----------------------------------

    // for smp2 detection -----------------------------------
    Double_t reduced_chisquare_smp2 = -999.;
    const Int_t total_particles_smp2 = 7;
    TLorentzVector lv_kfit_smp2[total_particles_smp2];
    if(is_accepted_smp2){
        // [0] : target
        // [1] : beam
        // [2] : sigma-
        // [3] : proton (missing)
        // [4] : proton 
        // [5] : pi- from sigmam
        // [6] : neutron from sigmam
        Double_t val_covariance_proton[9];
        GetCovarianceProton(lv_detected_proton2_meas.P(),val_covariance_proton);
        Double_t val_covariance_pi_from_sigmam[9];
        GetCovariancePi(lv_pi_from_sigmam_meas.P(),val_covariance_pi_from_sigmam);
        Double_t val_covariance_nucleon_from_sigmam[9];
        GetCovarianceNeutron(lv_nucleon_from_sigmam_meas.P(),val_covariance_nucleon_from_sigmam);

        TLorentzVector* lv_meas[total_particles_smp2] = {&lv_target_meas,&lv_beam_meas,&lv_sigmam_meas,&lv_missing_proton1_meas,&lv_detected_proton2_meas,&lv_pi_from_sigmam_meas,&lv_nucleon_from_sigmam_meas};
        Double_t masses[total_particles_smp2] = {kThreeHeMass,kKaonMass,kSigmaMinusMass,kProtonMass,kProtonMass,kPiMass,kNeutronMass};
        TMatrixD* covariances[total_particles_smp2];
        covariances[0] = new TMatrixD(3,3,kValCovarianceZero);                  // : target
        covariances[1] = new TMatrixD(3,3,kValCovarianceBeam);                  // : beam
        covariances[2] = new TMatrixD(3,3,kValCovarianceZero);                  // : sigma-
        covariances[3] = new TMatrixD(3,3,kValCovarianceZero);                  // : proton (missing)
        covariances[4] = new TMatrixD(3,3,val_covariance_proton);               // : proton
        covariances[5] = new TMatrixD(3,3,val_covariance_pi_from_sigmam);       // : pim from sigmam
        covariances[6] = new TMatrixD(3,3,val_covariance_nucleon_from_sigmam);  // : neutron from sigmam
        TFitParticlePxPyPz particles[total_particles_smp2];
        for(Int_t i_particle=0; i_particle<total_particles_smp2; ++i_particle){
            TVector3 vec_momentum = lv_meas[i_particle]->Vect();
            particles[i_particle] = TFitParticlePxPyPz(Form("particle_%d",i_particle), Form("particle_%d",i_particle), &vec_momentum, masses[i_particle], covariances[i_particle]);
        }

        // constraint :: mass of sigmam
        TFitConstraintM constraint_sigmam_mass = TFitConstraintM("sigmam_mass", "sigmam_mass", 0, 0, kSigmaMinusMass);
        constraint_sigmam_mass.addParticles1(&particles[5], &particles[6]);
        // constraint :: 4-momentum conservation
        TFitConstraintEp constraint_conservation[4];
        for(Int_t i_element=0; i_element<4; ++i_element){
            constraint_conservation[i_element] = TFitConstraintEp(Form("element_%d",i_element),Form("element_%d",i_element), 0, TFitConstraintEp::component(i_element), 0);
            constraint_conservation[i_element].addParticles1(&particles[0], &particles[1]);
            constraint_conservation[i_element].addParticles2(&particles[3], &particles[4], &particles[5], &particles[6]);
        }

        TKinFitter kinfitter;
        kinfitter.addMeasParticles(&particles[1], &particles[4], &particles[5], &particles[6]);
        kinfitter.addUnmeasParticles(&particles[3]);
        // add constraints
        kinfitter.addConstraint(&constraint_sigmam_mass);
        for(Int_t i_element=0; i_element<4; ++i_element){
            kinfitter.addConstraint(&constraint_conservation[i_element]);
        }
        // fitting
        kinfitter.setMaxNbIter(50);       // max number of iterations
        kinfitter.setMaxDeltaS(5e-5);     // max delta chi2
        kinfitter.setMaxF(1e-4);          // max sum of constraints
        kinfitter.setVerbosity(0);        // verbosity level
        kinfitter.fit();
        // fitting results
        reduced_chisquare_smp2 = kinfitter.getS()/kinfitter.getNDF();
        for(Int_t i_particle=0; i_particle<total_particles_smp2; ++i_particle){
            lv_kfit_smp2[i_particle] = (*particles[i_particle].getCurr4Vec());
            delete covariances[i_particle];
        }
    }
    // for smp2 detection -----------------------------------


    // ============================================================================================
    // ============================================================================================
    // ============================================================================================

    // ============================================================================================
    // FILLING HISTOGRAMS =========================================================================
    // ============================================================================================
    Fill("beam_momentum_lab_gene",lv_beam_mc.P());
    Fill("sigmam_momentum_lab_gene",lv_sigmam_mc.P());
    Fill("proton1_momentum_lab_gene",lv_proton1_mc.P());
    Fill("proton2_momentum_lab_gene",lv_proton2_mc.P());
    Fill("pi_from_sigmam_momentum_lab_gene",lv_pi_from_sigmam_mc.P());
    Fill("nucleon_from_sigmam_momentum_lab_gene",lv_nucleon_from_sigmam_mc.P());
    Fill("sigmam_mass_gene",lv_sigmam_mc.M());
    Fill("proton1_mass_gene",lv_proton1_mc.M());
    Fill("proton2_mass_gene",lv_proton2_mc.M());
    Fill("smp1_mass_gene",(lv_sigmam_mc+lv_proton1_mc).M());
    Fill("smp1_momtrans_gene",(lv_sigmam_mc+lv_proton1_mc).P());
    Fill("smp2_mass_gene",(lv_sigmam_mc+lv_proton2_mc).M());
    Fill("smp2_momtrans_gene",(lv_sigmam_mc+lv_proton2_mc).P());

    Fill("beam_cos_theta_vs_phi_lab_gene",lv_beam_mc.CosTheta(),lv_beam_mc.Phi());
    Fill("sigmam_cos_theta_vs_phi_lab_gene",lv_sigmam_mc.CosTheta(),lv_sigmam_mc.Phi());
    Fill("proton1_cos_theta_vs_phi_lab_gene",lv_proton1_mc.CosTheta(),lv_proton1_mc.Phi());
    Fill("proton2_cos_theta_vs_phi_lab_gene",lv_proton2_mc.CosTheta(),lv_proton2_mc.Phi());
    Fill("pi_from_sigmam_cos_theta_vs_phi_lab_gene",lv_pi_from_sigmam_mc.CosTheta(),lv_pi_from_sigmam_mc.Phi());
    Fill("nucleon_from_sigmam_cos_theta_vs_phi_lab_gene",lv_nucleon_from_sigmam_mc.CosTheta(),lv_nucleon_from_sigmam_mc.Phi());

    Fill("smp1_mass_vs_momtrans_gene",(lv_sigmam_mc+lv_proton1_mc).M(),(lv_sigmam_mc+lv_proton1_mc).P());
    Fill("smp2_mass_vs_momtrans_gene",(lv_sigmam_mc+lv_proton2_mc).M(),(lv_sigmam_mc+lv_proton2_mc).P());

    Fill("proton1_momentum_lab_vs_proton2_momentum_lab_gene",lv_proton1_mc.P(),lv_proton2_mc.P());

    for(UInt_t i_meas=0; i_meas<measured_neutral_energy_deposits.size(); i_meas++){
        Fill("neutral_over_beta_vs_energy_deposit_meas",measured_neutral_over_betas[i_meas],measured_neutral_energy_deposits[i_meas]);
    }

    bool fill_flag[9] = {is_accepted_smp1, is_accepted_smp1_true, is_accepted_smp1_fake, 
        is_accepted_smp2, is_accepted_smp2_true, is_accepted_smp2_fake,
        is_accepted_smpp, is_accepted_smpp_true, is_accepted_smpp_fake};
    std::string meas[9] = {"smp1","smp1_true","smp1_fake","smp2","smp2_true","smp2_fake","smpp","smpp_true","smpp_fake"};
    for(Int_t i_meas=0; i_meas<9; i_meas++){
        switch(i_meas){
            case 0: // Smp1 detection
                lv_proton1_meas = lv_detected_proton1_meas;
                lv_proton2_meas = lv_missing_proton2_meas;
                lv_beam_kfit = lv_kfit_smp1[1];
                lv_proton1_kfit = lv_kfit_smp1[3];
                lv_proton2_kfit = lv_kfit_smp1[4];
                lv_pi_from_sigmam_kfit = lv_kfit_smp1[5];
                lv_nucleon_from_sigmam_kfit = lv_kfit_smp1[6];
                lv_sigmam_kfit = lv_pi_from_sigmam_kfit + lv_nucleon_from_sigmam_kfit;
                reduced_chisquare_kfit = reduced_chisquare_smp1;
                break;
            case 1: // Smp1 detection (TRUE)
                lv_proton1_meas = lv_detected_proton1_meas;
                lv_proton2_meas = lv_missing_proton2_meas;
                lv_beam_kfit = lv_kfit_smp1[1];
                lv_proton1_kfit = lv_kfit_smp1[3];
                lv_proton2_kfit = lv_kfit_smp1[4];
                lv_pi_from_sigmam_kfit = lv_kfit_smp1[5];
                lv_nucleon_from_sigmam_kfit = lv_kfit_smp1[6];
                lv_sigmam_kfit = lv_pi_from_sigmam_kfit + lv_nucleon_from_sigmam_kfit;
                reduced_chisquare_kfit = reduced_chisquare_smp1;
                break;
            case 2: // Smp1 detection (FAKE)
                lv_proton1_meas = lv_detected_proton1_meas;
                lv_proton2_meas = lv_missing_proton2_meas;
                lv_beam_kfit = lv_kfit_smp1[1];
                lv_proton1_kfit = lv_kfit_smp1[3];
                lv_proton2_kfit = lv_kfit_smp1[4];
                lv_pi_from_sigmam_kfit = lv_kfit_smp1[5];
                lv_nucleon_from_sigmam_kfit = lv_kfit_smp1[6];
                lv_sigmam_kfit = lv_pi_from_sigmam_kfit + lv_nucleon_from_sigmam_kfit;
                reduced_chisquare_kfit = reduced_chisquare_smp1;
                break;
            case 3: // Smp2 detection
                lv_proton1_meas = lv_missing_proton1_meas;
                lv_proton2_meas = lv_detected_proton2_meas;
                lv_beam_kfit = lv_kfit_smp2[1];
                lv_proton1_kfit = lv_kfit_smp2[3];
                lv_proton2_kfit = lv_kfit_smp2[4];
                lv_pi_from_sigmam_kfit = lv_kfit_smp2[5];
                lv_nucleon_from_sigmam_kfit = lv_kfit_smp2[6];
                lv_sigmam_kfit = lv_pi_from_sigmam_kfit + lv_nucleon_from_sigmam_kfit;
                reduced_chisquare_kfit = reduced_chisquare_smp2;
                break;
            case 4: // Smp2 detection (TRUE)
                lv_proton1_meas = lv_missing_proton1_meas;
                lv_proton2_meas = lv_detected_proton2_meas;
                lv_beam_kfit = lv_kfit_smp2[1];
                lv_proton1_kfit = lv_kfit_smp2[3];
                lv_proton2_kfit = lv_kfit_smp2[4];
                lv_pi_from_sigmam_kfit = lv_kfit_smp2[5];
                lv_nucleon_from_sigmam_kfit = lv_kfit_smp2[6];
                lv_sigmam_kfit = lv_pi_from_sigmam_kfit + lv_nucleon_from_sigmam_kfit;
                reduced_chisquare_kfit = reduced_chisquare_smp2;
                break;
            case 5: // Smp2 detection (FAKE)
                lv_proton1_meas = lv_missing_proton1_meas;
                lv_proton2_meas = lv_detected_proton2_meas;
                lv_beam_kfit = lv_kfit_smp2[1];
                lv_proton1_kfit = lv_kfit_smp2[3];
                lv_proton2_kfit = lv_kfit_smp2[4];
                lv_pi_from_sigmam_kfit = lv_kfit_smp2[5];
                lv_nucleon_from_sigmam_kfit = lv_kfit_smp2[6];
                lv_sigmam_kfit = lv_pi_from_sigmam_kfit + lv_nucleon_from_sigmam_kfit;
                reduced_chisquare_kfit = reduced_chisquare_smp2;
                break;
            case 6: // Smpp detection
                lv_proton1_meas = lv_detected_proton1_meas;
                lv_proton2_meas = lv_detected_proton2_meas;
                break;
            case 7: // Smpp detection (TRUE)
                lv_proton1_meas = lv_detected_proton1_meas;
                lv_proton2_meas = lv_detected_proton2_meas;
                break;
            case 8: // Smpp detection (FAKE)
                lv_proton1_meas = lv_detected_proton1_meas;
                lv_proton2_meas = lv_detected_proton2_meas;
                break;
            default:
                break;
        }


        if(fill_flag[i_meas]){
            // acce -----
            Fill(Form("beam_momentum_lab_acce_%s",meas[i_meas].data()),lv_beam_mc.P());
            Fill(Form("sigmam_momentum_lab_acce_%s",meas[i_meas].data()),lv_sigmam_mc.P());
            Fill(Form("proton1_momentum_lab_acce_%s",meas[i_meas].data()),lv_proton1_mc.P());
            Fill(Form("proton2_momentum_lab_acce_%s",meas[i_meas].data()),lv_proton2_mc.P());
            Fill(Form("pi_from_sigmam_momentum_lab_acce_%s",meas[i_meas].data()),lv_pi_from_sigmam_mc.P());
            Fill(Form("nucleon_from_sigmam_momentum_lab_acce_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_mc.P());
            Fill(Form("sigmam_mass_acce_%s",meas[i_meas].data()),lv_sigmam_mc.M());
            Fill(Form("proton1_mass_acce_%s",meas[i_meas].data()),lv_proton1_mc.M());
            Fill(Form("proton2_mass_acce_%s",meas[i_meas].data()),lv_proton2_mc.M());
            Fill(Form("smp1_mass_acce_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton1_mc).M());
            Fill(Form("smp1_momtrans_acce_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton1_mc).P());
            Fill(Form("smp2_mass_acce_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton2_mc).M());
            Fill(Form("smp2_momtrans_acce_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton2_mc).P());

            Fill(Form("beam_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_beam_mc.CosTheta(),lv_beam_mc.Phi());
            Fill(Form("sigmam_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_sigmam_mc.CosTheta(),lv_sigmam_mc.Phi());
            Fill(Form("proton1_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_proton1_mc.CosTheta(),lv_proton1_mc.Phi());
            Fill(Form("proton2_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_proton2_mc.CosTheta(),lv_proton2_mc.Phi());
            Fill(Form("pi_from_sigmam_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_pi_from_sigmam_mc.CosTheta(),lv_pi_from_sigmam_mc.Phi());
            Fill(Form("nucleon_from_sigmam_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_mc.CosTheta(),lv_nucleon_from_sigmam_mc.Phi());

            Fill(Form("smp1_mass_vs_momtrans_acce_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton1_mc).M(),(lv_sigmam_mc+lv_proton1_mc).P());
            Fill(Form("smp2_mass_vs_momtrans_acce_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton2_mc).M(),(lv_sigmam_mc+lv_proton2_mc).P());

            Fill(Form("proton1_momentum_lab_vs_proton2_momentum_lab_acce_%s",meas[i_meas].data()),lv_proton1_mc.P(),lv_proton2_mc.P());

            // meas -----
            Fill(Form("beam_momentum_lab_meas_%s",meas[i_meas].data()),lv_beam_meas.P());
            Fill(Form("sigmam_momentum_lab_meas_%s",meas[i_meas].data()),lv_sigmam_meas.P());
            Fill(Form("proton1_momentum_lab_meas_%s",meas[i_meas].data()),lv_proton1_meas.P());
            Fill(Form("proton2_momentum_lab_meas_%s",meas[i_meas].data()),lv_proton2_meas.P());
            Fill(Form("pi_from_sigmam_momentum_lab_meas_%s",meas[i_meas].data()),lv_pi_from_sigmam_meas.P());
            Fill(Form("nucleon_from_sigmam_momentum_lab_meas_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_meas.P());
            Fill(Form("sigmam_mass_meas_%s",meas[i_meas].data()),lv_sigmam_meas.M());
            Fill(Form("proton1_mass_meas_%s",meas[i_meas].data()),lv_proton1_meas.M());
            Fill(Form("proton2_mass_meas_%s",meas[i_meas].data()),lv_proton2_meas.M());
            Fill(Form("smp1_mass_meas_%s",meas[i_meas].data()),(lv_sigmam_meas+lv_proton1_meas).M());
            Fill(Form("smp1_momtrans_meas_%s",meas[i_meas].data()),(lv_sigmam_meas+lv_proton1_meas).P());
            Fill(Form("smp2_mass_meas_%s",meas[i_meas].data()),(lv_sigmam_meas+lv_proton2_meas).M());
            Fill(Form("smp2_momtrans_meas_%s",meas[i_meas].data()),(lv_sigmam_meas+lv_proton2_meas).P());
            Fill(Form("neutral_energy_deposit_meas_%s",meas[i_meas].data()),measured_neutral_energy_deposit);
            Fill(Form("neutral_over_beta_meas_%s",meas[i_meas].data()),measured_neutral_over_beta);
            Fill(Form("neutral_time_meas_%s",meas[i_meas].data()),measured_neutral_time);
            Fill(Form("neutral_generation_meas_%s",meas[i_meas].data()),(Double_t)measured_neutral_generation);
            Fill(Form("neutral_charge_meas_%s",meas[i_meas].data()),measured_neutral_charge);
            if(measured_neutral_generation>0){
                Fill(Form("neutral_parent_charge_meas_%s",meas[i_meas].data()),measured_parent_neutral_charges[0]);
            }
            if(measured_neutral_generation>1){
                Fill(Form("neutral_grand_parent_charge_meas_%s",meas[i_meas].data()),measured_parent_neutral_charges[1]);
            }
            if(measured_neutral_generation>2){
                Fill(Form("neutral_2grand_parent_charge_meas_%s",meas[i_meas].data()),measured_parent_neutral_charges[2]);
            }
            if(measured_neutral_generation>3){
                Fill(Form("neutral_3grand_parent_charge_meas_%s",meas[i_meas].data()),measured_parent_neutral_charges[3]);
            }
            if(measured_neutral_generation>4){
                Fill(Form("neutral_4grand_parent_charge_meas_%s",meas[i_meas].data()),measured_parent_neutral_charges[4]);
            }

            Fill(Form("beam_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_beam_meas.CosTheta(),lv_beam_meas.Phi());
            Fill(Form("sigmam_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_sigmam_meas.CosTheta(),lv_sigmam_meas.Phi());
            Fill(Form("proton1_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_proton1_meas.CosTheta(),lv_proton1_meas.Phi());
            Fill(Form("proton2_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_proton2_meas.CosTheta(),lv_proton2_meas.Phi());
            Fill(Form("pi_from_sigmam_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_pi_from_sigmam_meas.CosTheta(),lv_pi_from_sigmam_meas.Phi());
            Fill(Form("nucleon_from_sigmam_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_meas.CosTheta(),lv_nucleon_from_sigmam_meas.Phi());

            Fill(Form("smp1_mass_vs_momtrans_meas_%s",meas[i_meas].data()),(lv_sigmam_meas+lv_proton1_meas).M(),(lv_sigmam_meas+lv_proton1_meas).P());
            Fill(Form("smp2_mass_vs_momtrans_meas_%s",meas[i_meas].data()),(lv_sigmam_meas+lv_proton2_meas).M(),(lv_sigmam_meas+lv_proton2_meas).P());

            Fill(Form("proton1_momentum_lab_vs_proton2_momentum_lab_meas_%s",meas[i_meas].data()),lv_proton1_meas.P(),lv_proton2_meas.P());


            Fill(Form("neutral_generated_position_r_vs_z_meas_%s",meas[i_meas].data()),vec_neutral_generated_position.Z(),sqrt(pow(vec_neutral_generated_position.X(),2.)+pow(vec_neutral_generated_position.Y(),2.)));
            if(measured_neutral_generation>0){
                Fill(Form("neutral_parent_generated_position_r_vs_z_meas_%s",meas[i_meas].data()),vec_neutral_parent_generated_positions[0].Z(),sqrt(pow(vec_neutral_parent_generated_positions[0].X(),2.)+pow(vec_neutral_parent_generated_positions[0].Y(),2.)));
            }
            if(measured_neutral_generation>1){
                Fill(Form("neutral_grand_parent_generated_position_r_vs_z_meas_%s",meas[i_meas].data()),vec_neutral_parent_generated_positions[1].Z(),sqrt(pow(vec_neutral_parent_generated_positions[1].X(),2.)+pow(vec_neutral_parent_generated_positions[1].Y(),2.)));
            }
            if(measured_neutral_generation>2){
                Fill(Form("neutral_2grand_parent_generated_position_r_vs_z_meas_%s",meas[i_meas].data()),vec_neutral_parent_generated_positions[2].Z(),sqrt(pow(vec_neutral_parent_generated_positions[2].X(),2.)+pow(vec_neutral_parent_generated_positions[2].Y(),2.)));
            }
            if(measured_neutral_generation>3){
                Fill(Form("neutral_3grand_parent_generated_position_r_vs_z_meas_%s",meas[i_meas].data()),vec_neutral_parent_generated_positions[3].Z(),sqrt(pow(vec_neutral_parent_generated_positions[3].X(),2.)+pow(vec_neutral_parent_generated_positions[3].Y(),2.)));
            }
            if(measured_neutral_generation>4){
                Fill(Form("neutral_4grand_parent_generated_position_r_vs_z_meas_%s",meas[i_meas].data()),vec_neutral_parent_generated_positions[4].Z(),sqrt(pow(vec_neutral_parent_generated_positions[4].X(),2.)+pow(vec_neutral_parent_generated_positions[4].Y(),2.)));
            }

            // resolutions
            Fill(Form("resolution_beam_momentum_meas_%s",meas[i_meas].data()),lv_beam_mc.P(),(lv_beam_mc.P()-lv_beam_meas.P())/lv_beam_mc.P());
            Fill(Form("resolution_sigmam_momentum_meas_%s",meas[i_meas].data()),lv_sigmam_mc.P(),(lv_sigmam_mc.P()-lv_sigmam_meas.P())/lv_sigmam_mc.P());
            Fill(Form("resolution_proton1_momentum_meas_%s",meas[i_meas].data()),lv_proton1_mc.P(),(lv_proton1_mc.P()-lv_proton1_meas.P())/lv_proton1_mc.P());
            Fill(Form("resolution_proton2_momentum_meas_%s",meas[i_meas].data()),lv_proton2_mc.P(),(lv_proton2_mc.P()-lv_proton2_meas.P())/lv_proton2_mc.P());
            Fill(Form("resolution_pi_from_sigmam_momentum_meas_%s",meas[i_meas].data()),lv_pi_from_sigmam_mc.P(),(lv_pi_from_sigmam_mc.P()-lv_pi_from_sigmam_meas.P())/lv_pi_from_sigmam_mc.P());
            Fill(Form("resolution_nucleon_from_sigmam_momentum_meas_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_mc.P(),(lv_nucleon_from_sigmam_mc.P()-lv_nucleon_from_sigmam_meas.P())/lv_nucleon_from_sigmam_mc.P());

            Fill(Form("resolution_smp1_mass_meas_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton1_mc).M(),( (lv_sigmam_mc+lv_proton1_mc).M()-(lv_sigmam_meas+lv_proton1_meas).M() )/(lv_sigmam_mc+lv_proton1_mc).M());
            Fill(Form("resolution_smp1_momtrans_meas_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton1_mc).P(),( (lv_sigmam_mc+lv_proton1_mc).P()-(lv_sigmam_meas+lv_proton1_meas).P() )/(lv_sigmam_mc+lv_proton1_mc).P());
            Fill(Form("resolution_smp2_mass_meas_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton2_mc).M(),( (lv_sigmam_mc+lv_proton2_mc).M()-(lv_sigmam_meas+lv_proton2_meas).M() )/(lv_sigmam_mc+lv_proton2_mc).M());
            Fill(Form("resolution_smp2_momtrans_meas_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton2_mc).P(),( (lv_sigmam_mc+lv_proton2_mc).P()-(lv_sigmam_meas+lv_proton2_meas).P() )/(lv_sigmam_mc+lv_proton2_mc).P());

            // covariance
            Fill(Form("covariance_beam_px_meas_%s",meas[i_meas].data()),lv_beam_meas.P(),(lv_beam_mc.Px()-lv_beam_meas.Px())/lv_beam_meas.P());
            Fill(Form("covariance_sigmam_px_meas_%s",meas[i_meas].data()),lv_sigmam_meas.P(),(lv_sigmam_mc.Px()-lv_sigmam_meas.Px())/lv_sigmam_meas.P());
            Fill(Form("covariance_proton1_px_meas_%s",meas[i_meas].data()),lv_proton1_meas.P(),(lv_proton1_mc.Px()-lv_proton1_meas.Px())/lv_proton1_meas.P());
            Fill(Form("covariance_proton2_px_meas_%s",meas[i_meas].data()),lv_proton2_meas.P(),(lv_proton2_mc.Px()-lv_proton2_meas.Px())/lv_proton2_meas.P());
            Fill(Form("covariance_pi_from_sigmam_px_meas_%s",meas[i_meas].data()),lv_pi_from_sigmam_meas.P(),(lv_pi_from_sigmam_mc.Px()-lv_pi_from_sigmam_meas.Px())/lv_pi_from_sigmam_meas.P());
            Fill(Form("covariance_nucleon_from_sigmam_px_meas_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_meas.P(),(lv_nucleon_from_sigmam_mc.Px()-lv_nucleon_from_sigmam_meas.Px())/lv_nucleon_from_sigmam_meas.P());

            Fill(Form("covariance_beam_py_meas_%s",meas[i_meas].data()),lv_beam_meas.P(),(lv_beam_mc.Py()-lv_beam_meas.Py())/lv_beam_meas.P());
            Fill(Form("covariance_sigmam_py_meas_%s",meas[i_meas].data()),lv_sigmam_meas.P(),(lv_sigmam_mc.Py()-lv_sigmam_meas.Py())/lv_sigmam_meas.P());
            Fill(Form("covariance_proton1_py_meas_%s",meas[i_meas].data()),lv_proton1_meas.P(),(lv_proton1_mc.Py()-lv_proton1_meas.Py())/lv_proton1_meas.P());
            Fill(Form("covariance_proton2_py_meas_%s",meas[i_meas].data()),lv_proton2_meas.P(),(lv_proton2_mc.Py()-lv_proton2_meas.Py())/lv_proton2_meas.P());
            Fill(Form("covariance_pi_from_sigmam_py_meas_%s",meas[i_meas].data()),lv_pi_from_sigmam_meas.P(),(lv_pi_from_sigmam_mc.Py()-lv_pi_from_sigmam_meas.Py())/lv_pi_from_sigmam_meas.P());
            Fill(Form("covariance_nucleon_from_sigmam_py_meas_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_meas.P(),(lv_nucleon_from_sigmam_mc.Py()-lv_nucleon_from_sigmam_meas.Py())/lv_nucleon_from_sigmam_meas.P());

            Fill(Form("covariance_beam_pz_meas_%s",meas[i_meas].data()),lv_beam_meas.P(),(lv_beam_mc.Pz()-lv_beam_meas.Pz())/lv_beam_meas.P());
            Fill(Form("covariance_sigmam_pz_meas_%s",meas[i_meas].data()),lv_sigmam_meas.P(),(lv_sigmam_mc.Pz()-lv_sigmam_meas.Pz())/lv_sigmam_meas.P());
            Fill(Form("covariance_proton1_pz_meas_%s",meas[i_meas].data()),lv_proton1_meas.P(),(lv_proton1_mc.Pz()-lv_proton1_meas.Pz())/lv_proton1_meas.P());
            Fill(Form("covariance_proton2_pz_meas_%s",meas[i_meas].data()),lv_proton2_meas.P(),(lv_proton2_mc.Pz()-lv_proton2_meas.Pz())/lv_proton2_meas.P());
            Fill(Form("covariance_pi_from_sigmam_pz_meas_%s",meas[i_meas].data()),lv_pi_from_sigmam_meas.P(),(lv_pi_from_sigmam_mc.Pz()-lv_pi_from_sigmam_meas.Pz())/lv_pi_from_sigmam_meas.P());
            Fill(Form("covariance_nucleon_from_sigmam_pz_meas_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_meas.P(),(lv_nucleon_from_sigmam_mc.Pz()-lv_nucleon_from_sigmam_meas.Pz())/lv_nucleon_from_sigmam_meas.P());

            // kfit -----
            Fill(Form("beam_momentum_lab_kfit_%s",meas[i_meas].data()),lv_beam_kfit.P());
            Fill(Form("sigmam_momentum_lab_kfit_%s",meas[i_meas].data()),lv_sigmam_kfit.P());
            Fill(Form("proton1_momentum_lab_kfit_%s",meas[i_meas].data()),lv_proton1_kfit.P());
            Fill(Form("proton2_momentum_lab_kfit_%s",meas[i_meas].data()),lv_proton2_kfit.P());
            Fill(Form("pi_from_sigmam_momentum_lab_kfit_%s",meas[i_meas].data()),lv_pi_from_sigmam_kfit.P());
            Fill(Form("nucleon_from_sigmam_momentum_lab_kfit_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_kfit.P());
            Fill(Form("sigmam_mass_kfit_%s",meas[i_meas].data()),lv_sigmam_kfit.M());
            Fill(Form("proton1_mass_kfit_%s",meas[i_meas].data()),lv_proton1_kfit.M());
            Fill(Form("proton2_mass_kfit_%s",meas[i_meas].data()),lv_proton2_kfit.M());
            Fill(Form("smp1_mass_kfit_%s",meas[i_meas].data()),(lv_sigmam_kfit+lv_proton1_kfit).M());
            Fill(Form("smp1_momtrans_kfit_%s",meas[i_meas].data()),(lv_sigmam_kfit+lv_proton1_kfit).P());
            Fill(Form("smp2_mass_kfit_%s",meas[i_meas].data()),(lv_sigmam_kfit+lv_proton2_kfit).M());
            Fill(Form("smp2_momtrans_kfit_%s",meas[i_meas].data()),(lv_sigmam_kfit+lv_proton2_kfit).P());

            Fill(Form("beam_cos_theta_vs_phi_lab_kfit_%s",meas[i_meas].data()),lv_beam_kfit.CosTheta(),lv_beam_kfit.Phi());
            Fill(Form("sigmam_cos_theta_vs_phi_lab_kfit_%s",meas[i_meas].data()),lv_sigmam_kfit.CosTheta(),lv_sigmam_kfit.Phi());
            Fill(Form("proton1_cos_theta_vs_phi_lab_kfit_%s",meas[i_meas].data()),lv_proton1_kfit.CosTheta(),lv_proton1_kfit.Phi());
            Fill(Form("proton2_cos_theta_vs_phi_lab_kfit_%s",meas[i_meas].data()),lv_proton2_kfit.CosTheta(),lv_proton2_kfit.Phi());
            Fill(Form("pi_from_sigmam_cos_theta_vs_phi_lab_kfit_%s",meas[i_meas].data()),lv_pi_from_sigmam_kfit.CosTheta(),lv_pi_from_sigmam_kfit.Phi());
            Fill(Form("nucleon_from_sigmam_cos_theta_vs_phi_lab_kfit_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_kfit.CosTheta(),lv_nucleon_from_sigmam_kfit.Phi());

            Fill(Form("smp1_mass_vs_momtrans_kfit_%s",meas[i_meas].data()),(lv_sigmam_kfit+lv_proton1_kfit).M(),(lv_sigmam_kfit+lv_proton1_kfit).P());
            Fill(Form("smp2_mass_vs_momtrans_kfit_%s",meas[i_meas].data()),(lv_sigmam_kfit+lv_proton2_kfit).M(),(lv_sigmam_kfit+lv_proton2_kfit).P());

            Fill(Form("proton1_momentum_lab_vs_proton2_momentum_lab_kfit_%s",meas[i_meas].data()),lv_proton1_kfit.P(),lv_proton2_kfit.P());

            // resolutions
            Fill(Form("resolution_beam_momentum_kfit_%s",meas[i_meas].data()),lv_beam_mc.P(),(lv_beam_mc.P()-lv_beam_kfit.P())/lv_beam_mc.P());
            Fill(Form("resolution_sigmam_momentum_kfit_%s",meas[i_meas].data()),lv_sigmam_mc.P(),(lv_sigmam_mc.P()-lv_sigmam_kfit.P())/lv_sigmam_mc.P());
            Fill(Form("resolution_proton1_momentum_kfit_%s",meas[i_meas].data()),lv_proton1_mc.P(),(lv_proton1_mc.P()-lv_proton1_kfit.P())/lv_proton1_mc.P());
            Fill(Form("resolution_proton2_momentum_kfit_%s",meas[i_meas].data()),lv_proton2_mc.P(),(lv_proton2_mc.P()-lv_proton2_kfit.P())/lv_proton2_mc.P());
            Fill(Form("resolution_pi_from_sigmam_momentum_kfit_%s",meas[i_meas].data()),lv_pi_from_sigmam_mc.P(),(lv_pi_from_sigmam_mc.P()-lv_pi_from_sigmam_kfit.P())/lv_pi_from_sigmam_mc.P());
            Fill(Form("resolution_nucleon_from_sigmam_momentum_kfit_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_mc.P(),(lv_nucleon_from_sigmam_mc.P()-lv_nucleon_from_sigmam_kfit.P())/lv_nucleon_from_sigmam_mc.P());

            Fill(Form("resolution_smp1_mass_kfit_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton1_mc).M(),( (lv_sigmam_mc+lv_proton1_mc).M()-(lv_sigmam_kfit+lv_proton1_kfit).M() )/(lv_sigmam_mc+lv_proton1_mc).M());
            Fill(Form("resolution_smp1_momtrans_kfit_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton1_mc).P(),( (lv_sigmam_mc+lv_proton1_mc).P()-(lv_sigmam_kfit+lv_proton1_kfit).P() )/(lv_sigmam_mc+lv_proton1_mc).P());
            Fill(Form("resolution_smp2_mass_kfit_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton2_mc).M(),( (lv_sigmam_mc+lv_proton2_mc).M()-(lv_sigmam_kfit+lv_proton2_kfit).M() )/(lv_sigmam_mc+lv_proton2_mc).M());
            Fill(Form("resolution_smp2_momtrans_kfit_%s",meas[i_meas].data()),(lv_sigmam_mc+lv_proton2_mc).P(),( (lv_sigmam_mc+lv_proton2_mc).P()-(lv_sigmam_kfit+lv_proton2_kfit).P() )/(lv_sigmam_mc+lv_proton2_mc).P());

            // covariance
            Fill(Form("covariance_beam_px_kfit_%s",meas[i_meas].data()),lv_beam_kfit.P(),(lv_beam_mc.Px()-lv_beam_kfit.Px())/lv_beam_kfit.P());
            Fill(Form("covariance_sigmam_px_kfit_%s",meas[i_meas].data()),lv_sigmam_kfit.P(),(lv_sigmam_mc.Px()-lv_sigmam_kfit.Px())/lv_sigmam_kfit.P());
            Fill(Form("covariance_proton1_px_kfit_%s",meas[i_meas].data()),lv_proton1_kfit.P(),(lv_proton1_mc.Px()-lv_proton1_kfit.Px())/lv_proton1_kfit.P());
            Fill(Form("covariance_proton2_px_kfit_%s",meas[i_meas].data()),lv_proton2_kfit.P(),(lv_proton2_mc.Px()-lv_proton2_kfit.Px())/lv_proton2_kfit.P());
            Fill(Form("covariance_pi_from_sigmam_px_kfit_%s",meas[i_meas].data()),lv_pi_from_sigmam_kfit.P(),(lv_pi_from_sigmam_mc.Px()-lv_pi_from_sigmam_kfit.Px())/lv_pi_from_sigmam_kfit.P());
            Fill(Form("covariance_nucleon_from_sigmam_px_kfit_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_kfit.P(),(lv_nucleon_from_sigmam_mc.Px()-lv_nucleon_from_sigmam_kfit.Px())/lv_nucleon_from_sigmam_kfit.P());

            Fill(Form("covariance_beam_py_kfit_%s",meas[i_meas].data()),lv_beam_kfit.P(),(lv_beam_mc.Py()-lv_beam_kfit.Py())/lv_beam_kfit.P());
            Fill(Form("covariance_sigmam_py_kfit_%s",meas[i_meas].data()),lv_sigmam_kfit.P(),(lv_sigmam_mc.Py()-lv_sigmam_kfit.Py())/lv_sigmam_kfit.P());
            Fill(Form("covariance_proton1_py_kfit_%s",meas[i_meas].data()),lv_proton1_kfit.P(),(lv_proton1_mc.Py()-lv_proton1_kfit.Py())/lv_proton1_kfit.P());
            Fill(Form("covariance_proton2_py_kfit_%s",meas[i_meas].data()),lv_proton2_kfit.P(),(lv_proton2_mc.Py()-lv_proton2_kfit.Py())/lv_proton2_kfit.P());
            Fill(Form("covariance_pi_from_sigmam_py_kfit_%s",meas[i_meas].data()),lv_pi_from_sigmam_kfit.P(),(lv_pi_from_sigmam_mc.Py()-lv_pi_from_sigmam_kfit.Py())/lv_pi_from_sigmam_kfit.P());
            Fill(Form("covariance_nucleon_from_sigmam_py_kfit_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_kfit.P(),(lv_nucleon_from_sigmam_mc.Py()-lv_nucleon_from_sigmam_kfit.Py())/lv_nucleon_from_sigmam_kfit.P());

            Fill(Form("covariance_beam_pz_kfit_%s",meas[i_meas].data()),lv_beam_kfit.P(),(lv_beam_mc.Pz()-lv_beam_kfit.Pz())/lv_beam_kfit.P());
            Fill(Form("covariance_sigmam_pz_kfit_%s",meas[i_meas].data()),lv_sigmam_kfit.P(),(lv_sigmam_mc.Pz()-lv_sigmam_kfit.Pz())/lv_sigmam_kfit.P());
            Fill(Form("covariance_proton1_pz_kfit_%s",meas[i_meas].data()),lv_proton1_kfit.P(),(lv_proton1_mc.Pz()-lv_proton1_kfit.Pz())/lv_proton1_kfit.P());
            Fill(Form("covariance_proton2_pz_kfit_%s",meas[i_meas].data()),lv_proton2_kfit.P(),(lv_proton2_mc.Pz()-lv_proton2_kfit.Pz())/lv_proton2_kfit.P());
            Fill(Form("covariance_pi_from_sigmam_pz_kfit_%s",meas[i_meas].data()),lv_pi_from_sigmam_kfit.P(),(lv_pi_from_sigmam_mc.Pz()-lv_pi_from_sigmam_kfit.Pz())/lv_pi_from_sigmam_kfit.P());
            Fill(Form("covariance_nucleon_from_sigmam_pz_kfit_%s",meas[i_meas].data()),lv_nucleon_from_sigmam_kfit.P(),(lv_nucleon_from_sigmam_mc.Pz()-lv_nucleon_from_sigmam_kfit.Pz())/lv_nucleon_from_sigmam_kfit.P());


        }
    }

    // ============================================================================================
    // FILLING HISTOGRAMS =========================================================================
    // ============================================================================================

    return;
}

void AnalyzerSmpp::PrintHistogram(std::string file_name){
    if(file_name!=""){
        _pdf_file_name = file_name;
        _pdf_file_name = _pdf_file_name.substr(0,_pdf_file_name.find_last_of("."));
        _pdf_file_name.append("_smpp.pdf");
    }
    TCanvas* tmp_canvas = new TCanvas("tmp_canvas","canvas",3200,1800);
    tmp_canvas->Draw();
    tmp_canvas->Print(std::string(_pdf_file_name+"[").data());


    std::vector<std::string> meas_type;
    meas_type.push_back("gene");
    //meas_type.push_back("acce_smp1");
    //meas_type.push_back("meas_smp1");
    //meas_type.push_back("kfit_smp1");
    meas_type.push_back("acce_smp1_true");
    meas_type.push_back("meas_smp1_true");
    meas_type.push_back("kfit_smp1_true");
    //meas_type.push_back("acce_smp1_fake");
    //meas_type.push_back("meas_smp1_fake");
    //meas_type.push_back("kfit_smp1_fake");
    //meas_type.push_back("acce_smp2");
    //meas_type.push_back("meas_smp2");
    //meas_type.push_back("kfit_smp2");
    meas_type.push_back("acce_smp2_true");
    meas_type.push_back("meas_smp2_true");
    meas_type.push_back("kfit_smp2_true");
    //meas_type.push_back("acce_smp2_fake");
    //meas_type.push_back("meas_smp2_fake");
    //meas_type.push_back("kfit_smp2_fake");
    //meas_type.push_back("acce_smpp");
    //meas_type.push_back("meas_smpp");
    //meas_type.push_back("kfit_smpp");
    meas_type.push_back("acce_smpp_true");
    meas_type.push_back("meas_smpp_true");
    meas_type.push_back("kfit_smpp_true");
    //meas_type.push_back("acce_smpp_fake");
    //meas_type.push_back("meas_smpp_fake");
    //meas_type.push_back("kfit_smpp_fake");


    Int_t total_meas_type = meas_type.size();
    std::vector<std::string> print_th1_names;
    std::vector<std::string> log_th1_names;
    std::vector<std::string> print_th2_names;
    std::vector<std::string> log_th2_names;

    TLatex* text = new TLatex();
    text->SetTextSize(0.2);
    text->SetTextFont(132);
    text->SetTextAlign(22);
    for(Int_t i_meas = 0; i_meas<total_meas_type; ++i_meas){

        tmp_canvas->cd();
        tmp_canvas->Clear();
        text->DrawLatex(0.5,0.5,meas_type[i_meas].data());
        tmp_canvas->Print(std::string(_pdf_file_name).data());
        // 1D histograms to be drawn
        print_th1_names.clear();
        // --
        print_th1_names.push_back("beam_momentum_lab_"+meas_type[i_meas]);
        print_th1_names.push_back("sigmam_momentum_lab_"+meas_type[i_meas]);
        print_th1_names.push_back("proton1_momentum_lab_"+meas_type[i_meas]);
        print_th1_names.push_back("proton2_momentum_lab_"+meas_type[i_meas]);
        print_th1_names.push_back("pi_from_sigmam_momentum_lab_"+meas_type[i_meas]);
        print_th1_names.push_back("nucleon_from_sigmam_momentum_lab_"+meas_type[i_meas]);
        // --
        print_th1_names.push_back("sigmam_mass_"+meas_type[i_meas]);
        print_th1_names.push_back("proton1_mass_"+meas_type[i_meas]);
        print_th1_names.push_back("proton2_mass_"+meas_type[i_meas]);
        print_th1_names.push_back("");
        print_th1_names.push_back("");
        print_th1_names.push_back("");
        // --
        print_th1_names.push_back("smp1_mass_"+meas_type[i_meas]);
        print_th1_names.push_back("smp1_momtrans_"+meas_type[i_meas]);
        print_th1_names.push_back("");
        print_th1_names.push_back("smp2_mass_"+meas_type[i_meas]);
        print_th1_names.push_back("smp2_momtrans_"+meas_type[i_meas]);
        print_th1_names.push_back("");
        // --
        print_th1_names.push_back("neutral_energy_deposit_"+meas_type[i_meas]);
        print_th1_names.push_back("neutral_over_beta_"+meas_type[i_meas]);
        print_th1_names.push_back("neutral_time_"+meas_type[i_meas]);
        print_th1_names.push_back("neutral_generation_"+meas_type[i_meas]);
        print_th1_names.push_back("");
        print_th1_names.push_back("");
        // --
        print_th1_names.push_back("neutral_charge_"+meas_type[i_meas]);
        print_th1_names.push_back("neutral_parent_charge_"+meas_type[i_meas]);
        print_th1_names.push_back("neutral_grand_parent_charge_"+meas_type[i_meas]);
        print_th1_names.push_back("neutral_2grand_parent_charge_"+meas_type[i_meas]);
        print_th1_names.push_back("neutral_3grand_parent_charge_"+meas_type[i_meas]);
        print_th1_names.push_back("neutral_4grand_parent_charge_"+meas_type[i_meas]);
        // --
        print_th1_names.push_back("reduced_chisquare_"+meas_type[i_meas]);
        print_th1_names.push_back("");
        print_th1_names.push_back("");
        print_th1_names.push_back("");
        print_th1_names.push_back("");
        print_th1_names.push_back("");
        // --
        // 1D histograms drawn logarithmic
        log_th1_names.clear();
        // --
        //_log_th1_names.push_back("");
        // --
        Print(print_th1_names,log_th1_names,k1D);

        // 2D histograms to be drawn
        print_th2_names.clear();
        // --
        print_th2_names.push_back("beam_cos_theta_vs_phi_lab_"+meas_type[i_meas]);
        print_th2_names.push_back("sigmam_cos_theta_vs_phi_lab_"+meas_type[i_meas]);
        print_th2_names.push_back("proton1_cos_theta_vs_phi_lab_"+meas_type[i_meas]);
        print_th2_names.push_back("proton2_cos_theta_vs_phi_lab_"+meas_type[i_meas]);
        print_th2_names.push_back("pi_from_sigmam_cos_theta_vs_phi_lab_"+meas_type[i_meas]);
        print_th2_names.push_back("nucleon_from_sigmam_cos_theta_vs_phi_lab_"+meas_type[i_meas]);
        // --
        print_th2_names.push_back("smp1_mass_vs_momtrans_"+meas_type[i_meas]);
        print_th2_names.push_back("smp2_mass_vs_momtrans_"+meas_type[i_meas]);
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        // --
        print_th2_names.push_back("proton1_momentum_lab_vs_proton2_momentum_lab_"+meas_type[i_meas]);
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        // --
        print_th2_names.push_back("neutral_generated_position_r_vs_z_"+meas_type[i_meas]);
        print_th2_names.push_back("neutral_parent_generated_position_r_vs_z_"+meas_type[i_meas]);
        print_th2_names.push_back("neutral_grand_parent_generated_position_r_vs_z_"+meas_type[i_meas]);
        print_th2_names.push_back("neutral_2grand_parent_generated_position_r_vs_z_"+meas_type[i_meas]);
        print_th2_names.push_back("neutral_3grand_parent_generated_position_r_vs_z_"+meas_type[i_meas]);
        print_th2_names.push_back("neutral_4grand_parent_generated_position_r_vs_z_"+meas_type[i_meas]);
        // --
        print_th2_names.push_back("resolution_sigmam_momentum_"+meas_type[i_meas]);
        print_th2_names.push_back("resolution_proton1_momentum_"+meas_type[i_meas]);
        print_th2_names.push_back("resolution_proton2_momentum_"+meas_type[i_meas]);
        print_th2_names.push_back("resolution_pi_from_sigmam_momentum_"+meas_type[i_meas]);
        print_th2_names.push_back("resolution_nucleon_from_sigmam_momentum_"+meas_type[i_meas]);
        print_th2_names.push_back("");
        // --
        print_th2_names.push_back("resolution_smp1_mass_"+meas_type[i_meas]);
        print_th2_names.push_back("resolution_smp1_momtrans_"+meas_type[i_meas]);
        print_th2_names.push_back("");
        print_th2_names.push_back("resolution_smp2_mass_"+meas_type[i_meas]);
        print_th2_names.push_back("resolution_smp2_momtrans_"+meas_type[i_meas]);
        print_th2_names.push_back("");
        // --
        // 2D histograms drawn logarithmic
        log_th2_names.clear();
        // --
        log_th2_names.push_back("neutral_generated_position_r_vs_z_"+meas_type[i_meas]);
        log_th2_names.push_back("neutral_parent_generated_position_r_vs_z_"+meas_type[i_meas]);
        log_th2_names.push_back("neutral_grand_parent_generated_position_r_vs_z_"+meas_type[i_meas]);
        log_th2_names.push_back("neutral_2grand_parent_generated_position_r_vs_z_"+meas_type[i_meas]);
        log_th2_names.push_back("neutral_3grand_parent_generated_position_r_vs_z_"+meas_type[i_meas]);
        log_th2_names.push_back("neutral_4grand_parent_generated_position_r_vs_z_"+meas_type[i_meas]);
        // --
        Print(print_th2_names,log_th2_names,k2D);

        continue;

        // Slice of 2D histograms
        std::string th2_slice;
        //// --
        //th2_slice = "resolution_lambda_momentum_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,6);
        //// --
        //th2_slice = "resolution_proton_momentum_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,6);
        //// --
        //th2_slice = "resolution_neutron_momentum_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,6);
        //// --
        //th2_slice = "resolution_pi_from_lambda_momentum_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,6);
        //// --
        //th2_slice = "resolution_nucleon_from_lambda_momentum_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,6);
        //// --
        //th2_slice = "resolution_lp_mass_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,6);
        //// --
        //th2_slice = "resolution_lp_momtrans_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,6);
        //// --
        //th2_slice = "resolution_ln_mass_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,6);
        //// --
        //th2_slice = "resolution_ln_momtrans_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,6);
        //// --
        // covariance
        // --
        //// beam
        //th2_slice = "covariance_beam_px_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //th2_slice = "covariance_beam_py_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //th2_slice = "covariance_beam_pz_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //// --
        //// lambda
        //th2_slice = "covariance_lambda_px_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //th2_slice = "covariance_lambda_py_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //th2_slice = "covariance_lambda_pz_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //// --
        //// proton
        //th2_slice = "covariance_proton_px_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //th2_slice = "covariance_proton_py_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //th2_slice = "covariance_proton_pz_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //// --
        //// neutron
        //th2_slice = "covariance_neutron_px_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //th2_slice = "covariance_neutron_py_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //th2_slice = "covariance_neutron_pz_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //// --
        //// pi_from_lambda
        //th2_slice = "covariance_pi_from_lambda_px_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //th2_slice = "covariance_pi_from_lambda_py_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //th2_slice = "covariance_pi_from_lambda_pz_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //// --
        //// nucleon_from_lambda
        //th2_slice = "covariance_nucleon_from_lambda_px_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //th2_slice = "covariance_nucleon_from_lambda_py_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //th2_slice = "covariance_nucleon_from_lambda_pz_"+meas_type[i_meas];
        //Print2DSlice(th2_slice,kXSlice,0);
        //// --
    }


    // 2D histograms to be drawn
    print_th2_names.clear();
    // --
    print_th2_names.push_back("neutral_over_beta_vs_energy_deposit_meas");
    print_th2_names.push_back("");
    print_th2_names.push_back("");
    print_th2_names.push_back("");
    print_th2_names.push_back("");
    print_th2_names.push_back("");
    // --
    // 2D histograms drawn logarithmic
    log_th2_names.clear();
    // --
    log_th2_names.push_back("neutral_over_beta_vs_energy_deposit_meas");
    // --
    Print(print_th2_names,log_th2_names,k2D);


    // For same drawing TH1
    std::vector<std::string> th1_names;
    std::vector<Int_t> line_colors;
    std::vector<std::string> legend_names;
    // --
    th1_names.push_back("proton2_mass_meas_smp1");
    line_colors.push_back(kBlack);
    legend_names.push_back("all");
    th1_names.push_back("proton2_mass_meas_smp1_fake");
    line_colors.push_back(kBlue-4);
    legend_names.push_back("fake");
    PrintSame(th1_names,line_colors,legend_names);
    // --
    th1_names.clear();
    line_colors.clear();
    legend_names.clear();
    // --
    th1_names.push_back("sigmam_mass_meas_smp1");
    line_colors.push_back(kBlack);
    legend_names.push_back("all");
    th1_names.push_back("sigmam_mass_meas_smp1_fake");
    line_colors.push_back(kBlue-4);
    legend_names.push_back("fake");
    PrintSame(th1_names,line_colors,legend_names);
    // --
    th1_names.clear();
    line_colors.clear();
    legend_names.clear();
    // --
    th1_names.push_back("proton1_mass_meas_smp2");
    line_colors.push_back(kBlack);
    legend_names.push_back("all");
    th1_names.push_back("proton1_mass_meas_smp2_fake");
    line_colors.push_back(kBlue-4);
    legend_names.push_back("fake");
    PrintSame(th1_names,line_colors,legend_names);
    // --
    th1_names.clear();
    line_colors.clear();
    legend_names.clear();
    th1_names.push_back("sigmam_mass_meas_smp2");
    line_colors.push_back(kBlack);
    legend_names.push_back("all");
    th1_names.push_back("sigmam_mass_meas_smp2_fake");
    line_colors.push_back(kBlue-4);
    legend_names.push_back("fake");
    PrintSame(th1_names,line_colors,legend_names);
    // --

    // For acceptance
    // On the 2D plot of Lp system
    std::vector<std::string> gene_names;
    gene_names.push_back("smp1_mass_vs_momtrans_gene");
    gene_names.push_back("smp2_mass_vs_momtrans_gene");
    std::vector<std::string> acce_names;
    acce_names.push_back("smp1_mass_vs_momtrans_acce_smp1_true");
    acce_names.push_back("smp2_mass_vs_momtrans_acce_smp1_true");
    Double_t maximum = 1.5;
    PrintAcceptance(gene_names,acce_names,maximum);
    acce_names.clear();
    acce_names.push_back("smp1_mass_vs_momtrans_acce_smp2_true");
    acce_names.push_back("smp2_mass_vs_momtrans_acce_smp2_true");
    maximum = 1.5;
    PrintAcceptance(gene_names,acce_names,maximum);
    acce_names.clear();
    acce_names.push_back("smp1_mass_vs_momtrans_acce_smpp_true");
    acce_names.push_back("smp2_mass_vs_momtrans_acce_smpp_true");
    maximum = 1.5;
    PrintAcceptance(gene_names,acce_names,maximum);

    tmp_canvas->Print(std::string(_pdf_file_name+"]").data());
    delete tmp_canvas;

}
