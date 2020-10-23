// AnalyzerLpn.cc
#include"AnalyzerLpn.hh"

#define USE_CAP

AnalyzerLpn::AnalyzerLpn()
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

AnalyzerLpn::AnalyzerLpn(std::string file_name, std::string option)
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

AnalyzerLpn::~AnalyzerLpn()
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
void AnalyzerLpn::CreateRootFile(std::string option)
{
    _meas_type.push_back("gene");
    _meas_type.push_back("acce_lp");
    _meas_type.push_back("meas_lp");
    _meas_type.push_back("kfit_lp");
    _meas_type.push_back("acce_ln");
    _meas_type.push_back("meas_ln");
    _meas_type.push_back("kfit_ln");
    _meas_type.push_back("acce_ln_true");
    _meas_type.push_back("meas_ln_true");
    _meas_type.push_back("kfit_ln_true");
    _meas_type.push_back("acce_ln_fake");
    _meas_type.push_back("meas_ln_fake");
    _meas_type.push_back("kfit_ln_fake");
    _meas_type.push_back("acce_lpn");
    _meas_type.push_back("meas_lpn");
    _meas_type.push_back("kfit_lpn");
    _meas_type.push_back("acce_lpn_true");
    _meas_type.push_back("meas_lpn_true");
    _meas_type.push_back("kfit_lpn_true");
    _meas_type.push_back("acce_lpn_fake");
    _meas_type.push_back("meas_lpn_fake");
    _meas_type.push_back("kfit_lpn_fake");

    _root_file = new TFile(_root_file_name.data(),option.data());
    if(option=="read"||option=="READ"){
        return;
    }
    _root_file->cd();

    for(UInt_t i_type=0; i_type<_meas_type.size(); ++i_type){

        // 1D histograms ------------------------------------------------------------------------------
        new TH1F(Form("beam_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of K^{-}-beam;#font[12]{p}_{K^{-}}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("lambda_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of #Lambda;#font[12]{p}_{#Lambda}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("proton_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of proton;#font[12]{p}_{#font[12]{p}}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("neutron_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of neutron;#font[12]{p}_{#font[12]{n}}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("pi_from_lambda_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of #pi from #Lambda;#font[12]{p}_{#pi from #Lambda}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("nucleon_from_lambda_momentum_lab_%s",_meas_type[i_type].data()),"Momentum of nucleon from #Lambda;#font[12]{p}_{#font[12]{N} from #Lambda}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("lambda_mass_%s",_meas_type[i_type].data()),"Mass of #Lambda;#font[12]{m}_{#Lambda}^{lab} (GeV/#font[12]{c}^{2});Counts", 150, 1.05, 1.20);
        new TH1F(Form("proton_mass_%s",_meas_type[i_type].data()),"Mass of proton;#font[12]{m}_{#font[12]{p}}^{lab} (GeV/#font[12]{c}^{2});Counts", 150, 0.3, 1.8);
        new TH1F(Form("neutron_mass_%s",_meas_type[i_type].data()),"Mass of neutron;#font[12]{m}_{#font[12]{n}}^{lab} (GeV/#font[12]{c}^{2});Counts", 150, 0.3, 1.8);
        new TH1F(Form("lp_mass_%s",_meas_type[i_type].data()),"Mass of #Lambdap;#font[12]{m}_{#Lambda#font[12]{p}}^{lab} (GeV/#font[12]{c}^{2});Counts", 100, 2.0, 3.0);
        new TH1F(Form("lp_momtrans_%s",_meas_type[i_type].data()),"Momentum transfer of #Lambdap;#font[12]{q}_{#Lambda#font[12]{p}}^{lab} (GeV/#font[12]{c});Counts", 200, 0.0, 2.0);
        new TH1F(Form("ln_mass_%s",_meas_type[i_type].data()),"Mass of #Lambdan;#font[12]{m}_{#Lambda#font[12]{n}}^{lab} (GeV/#font[12]{c}^{2});Counts", 100, 2.0, 3.0);
        new TH1F(Form("ln_momtrans_%s",_meas_type[i_type].data()),"Momentum transfer of #Lambdan;#font[12]{q}_{#Lambda#font[12]{n}}^{lab} (GeV/#font[12]{c});Counts", 200, 0.0, 2.0);

        new TH1F(Form("lambda_flight_time_%s",_meas_type[i_type].data()),"Flight time of #Lambda;#font[12]{t}_{#Lambda}^{flight} (ns);Counts", 200, 0.0, 2.0);
        new TH1F(Form("proton_flight_time_%s",_meas_type[i_type].data()),"Flight time of proton;#font[12]{t}_{#font[12]{p}}^{flight} (ns);Counts", 200, 0.0, 20.0);
        new TH1F(Form("reference_axis_sin_theta_%s",_meas_type[i_type].data()),"sin#theta of reference axis;sin#theta^{ref};Counts", 100, 0.0, 1.0);
        new TH1F(Form("reference_axis_sin_phi_%s",_meas_type[i_type].data()),"sin#phi of reference axis;sin#phi^{ref};Counts", 100, 0.0, 1.0);

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

        // reference_axis_selected
        new TH1F(Form("lambda_momentum_lab_reference_axis_selected_%s",_meas_type[i_type].data()),"Momentum of #Lambda;#font[12]{p}_{#Lambda}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("proton_momentum_lab_reference_axis_selected_%s",_meas_type[i_type].data()),"Momentum of proton;#font[12]{p}_{#font[12]{p}}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("neutron_momentum_lab_reference_axis_selected_%s",_meas_type[i_type].data()),"Momentum of neutron;#font[12]{p}_{#font[12]{n}}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("pi_from_lambda_momentum_lab_reference_axis_selected_%s",_meas_type[i_type].data()),"Momentum of #pi from #Lambda;#font[12]{p}_{#pi from #Lambda}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        new TH1F(Form("nucleon_from_lambda_momentum_lab_reference_axis_selected_%s",_meas_type[i_type].data()),"Momentum of nucleon from #Lambda;#font[12]{p}_{#font[12]{N} from #Lambda}^{lab} (GeV/#font[12]{c});Counts", 150, 0., 1.5);
        // 1D histograms ------------------------------------------------------------------------------


        // 2D histograms ------------------------------------------------------------------------------
        new TH2F(Form("beam_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of K^{-}-beam (lab. frame);cos#theta_{K^{-}}^{lab};#phi_{K^{-}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("lambda_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of #Lambda (lab. frame);cos#theta_{#Lambda}^{lab};#phi_{#Lambda}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("proton_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of proton (lab. frame);cos#theta_{#font[12]{p}}^{lab};#phi_{#font[12]{p}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("neutron_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of neutron (lab. frame);cos#theta_{#font[12]{n}}^{lab};#phi_{#font[12]{n}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("pi_from_lambda_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of pi_from_lambda (lab. frame);cos#theta_{#pi from #Lambda}^{lab};#phi_{#font[12]{n}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("nucleon_from_lambda_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of nucleon_from_lambda (lab. frame);cos#theta_{#font[12]{N} from #Lambda}^{lab};#phi_{#font[12]{N} from #Lambda}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());

        new TH2F(Form("nucleon_from_lambda_cos_theta_vs_phi_lambda_rest_%s",_meas_type[i_type].data()),"cos#theta vs. phi of nucleon_from_lambda (#Lambda-rest frame);cos#theta_{#font[12]{N} from #Lambda}^{#Lambda-rest};#phi_{#font[12]{N} from #Lambda}^{#Lambda-rest}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("proton_theta_vs_phi_against_to_chc_%s",_meas_type[i_type].data()),"#theta vs. #phi of proton (against to CHC surface);#theta_{#font[12]{p}}^{CHC} (rad.);#phi_{#font[12]{p}}^{CHC} (rad.)", 50,0.,TMath::Pi(),50,0.,TMath::Pi());
        new TH2F(Form("proton_theta_vs_phi_against_to_chc_in_deg_%s",_meas_type[i_type].data()),"#theta vs. #phi of proton (against to CHC surface);#theta_{#font[12]{p}}^{CHC} (deg.);#phi_{#font[12]{p}}^{CHC} (deg.)", 60,0.,180.,60,0.,180.);
        new TH2F(Form("reference_axis_sin_theta_vs_phi_%s",_meas_type[i_type].data()),"sin#theta vs. #phi of reference axis;sin#theta_{#font[12]{p}}^{ref};#phi_{#font[12]{p}}^{ref} (rad.)", 50,0.,1.,50,0.,TMath::Pi());
        new TH2F(Form("reference_axis_sin_theta_vs_sin_phi_%s",_meas_type[i_type].data()),"sin#theta vs. sin#phi of reference axis;sin#theta_{#font[12]{p}}^{ref};sin#phi_{#font[12]{p}}^{ref}", 50,0.,1.,50,0.,1.);

        new TH2F(Form("lp_mass_vs_momtrans_%s",_meas_type[i_type].data()),"Mass vs. momentum transfer of #Lambdap;#font[12]{m}_{#Lambda#font[12]{p}} (GeV/#font[12]{c}^{2});#font[12]{q}_{#Lambda#font[12]{p}} (GeV/#font[12]{c})", 50,2.,3.,100,0.,2.);
        new TH2F(Form("ln_mass_vs_momtrans_%s",_meas_type[i_type].data()),"Mass vs. momentum transfer of #Lambdan;#font[12]{m}_{#Lambda#font[12]{n}} (GeV/#font[12]{c}^{2});#font[12]{q}_{#Lambda#font[12]{n}} (GeV/#font[12]{c})", 50,2.,3.,100,0.,2.);

        new TH2F(Form("neutral_generated_position_r_vs_z_%s",_meas_type[i_type].data()),"R vs. Z of neutral generated position;#font[12]{z} (cm);#font[12]{r} (cm);Counts", 100,-200.,200.,40,0.,160.);
        new TH2F(Form("neutral_parent_generated_position_r_vs_z_%s",_meas_type[i_type].data()),"R vs. Z of neutral parent generated position;#font[12]{z} (cm);#font[12]{r} (cm);Counts", 100,-200.,200.,40,0.,160.);
        new TH2F(Form("neutral_grand_parent_generated_position_r_vs_z_%s",_meas_type[i_type].data()),"R vs. Z of neutral grand parent generated position;#font[12]{z} (cm);#font[12]{r} (cm);Counts", 100,-200.,200.,40,0.,160.);
        new TH2F(Form("neutral_2grand_parent_generated_position_r_vs_z_%s",_meas_type[i_type].data()),"R vs. Z of neutral 2grand parent generated position;#font[12]{z} (cm);#font[12]{r} (cm);Counts", 100,-200.,200.,40,0.,160.);
        new TH2F(Form("neutral_3grand_parent_generated_position_r_vs_z_%s",_meas_type[i_type].data()),"R vs. Z of neutral 3grand parent generated position;#font[12]{z} (cm);#font[12]{r} (cm);Counts", 100,-200.,200.,40,0.,160.);
        new TH2F(Form("neutral_4grand_parent_generated_position_r_vs_z_%s",_meas_type[i_type].data()),"R vs. Z of neutral 4grand parent generated position;#font[12]{z} (cm);#font[12]{r} (cm);Counts", 100,-200.,200.,40,0.,160.);

        new TH2F(Form("neutron_momentum_lab_vs_lambda_momentum_lab_%s",_meas_type[i_type].data()),"Neutron momentum vs. Lambda momentum;#font[12]{p}_{#font[12]{n}} (GeV/#font[12]{c});#font[12]{p}_{#Lambda} (GeV/#font[12]{c});Counts", 100,0.,2.,100,0.,2.);
        new TH2F(Form("neutron_cos_theta_lab_vs_lambda_cos_theta_lab_%s",_meas_type[i_type].data()),"Neutron cos#theta vs. Lambda cos#theta;cos#theta_{#font[12]{n}}^{lab};cos#theta_{#Lambda}^{lab};Counts", 50,-1.,1.,50,-1.,1.);

        // reference_axis_selected
        new TH2F(Form("lambda_cos_theta_vs_phi_lab_reference_axis_selected_%s",_meas_type[i_type].data()),"cos#theta vs. phi of #Lambda (lab. frame);cos#theta_{#Lambda}^{lab};#phi_{#Lambda}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("proton_cos_theta_vs_phi_lab_reference_axis_selected_%s",_meas_type[i_type].data()),"cos#theta vs. phi of proton (lab. frame);cos#theta_{#font[12]{p}}^{lab};#phi_{#font[12]{p}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("neutron_cos_theta_vs_phi_lab_reference_axis_selected_%s",_meas_type[i_type].data()),"cos#theta vs. phi of neutron (lab. frame);cos#theta_{#font[12]{n}}^{lab};#phi_{#font[12]{n}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("pi_from_lambda_cos_theta_vs_phi_lab_reference_axis_selected_%s",_meas_type[i_type].data()),"cos#theta vs. phi of pi_from_lambda (lab. frame);cos#theta_{#pi from #Lambda}^{lab};#phi_{#font[12]{n}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("nucleon_from_lambda_cos_theta_vs_phi_lab_reference_axis_selected_%s",_meas_type[i_type].data()),"cos#theta vs. phi of nucleon_from_lambda (lab. frame);cos#theta_{#font[12]{N} from #Lambda}^{lab};#phi_{#font[12]{N} from #Lambda}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());

        new TH2F(Form("nucleon_from_lambda_cos_theta_vs_phi_lambda_rest_reference_axis_selected_%s",_meas_type[i_type].data()),"cos#theta vs. phi of nucleon_from_lambda (#Lambda-rest frame);cos#theta_{#font[12]{N} from #Lambda}^{#Lambda-rest};#phi_{#font[12]{N} from #Lambda}^{#Lambda-rest}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("proton_theta_vs_phi_against_to_chc_reference_axis_selected_%s",_meas_type[i_type].data()),"#theta vs. #phi of proton (against to CHC surface);#theta_{#font[12]{p}}^{CHC} (rad.);#phi_{#font[12]{p}}^{CHC} (rad.)", 50,0.,TMath::Pi(),50,0.,TMath::Pi());
        new TH2F(Form("proton_theta_vs_phi_against_to_chc_in_deg_reference_axis_selected_%s",_meas_type[i_type].data()),"#theta vs. #phi of proton (against to CHC surface);#theta_{#font[12]{p}}^{CHC} (deg.);#phi_{#font[12]{p}}^{CHC} (deg.)", 60,0.,180.,60,0.,180.);
        new TH2F(Form("reference_axis_sin_theta_vs_phi_reference_axis_selected_%s",_meas_type[i_type].data()),"sin#theta vs. #phi of reference axis;sin#theta_{#font[12]{p}}^{ref};#phi_{#font[12]{p}}^{ref} (rad.)", 50,0.,1.,50,0.,TMath::Pi());
        new TH2F(Form("reference_axis_sin_theta_vs_sin_phi_reference_axis_selected_%s",_meas_type[i_type].data()),"sin#theta vs. sin#phi of reference axis;sin#theta_{#font[12]{p}}^{ref};sin#phi_{#font[12]{p}}^{ref}", 50,0.,1.,50,0.,1.);
        new TH2F(Form("lp_mass_vs_momtrans_reference_axis_selected_%s",_meas_type[i_type].data()),"Mass vs. momentum transfer of #Lambdap;#font[12]{m}_{#Lambda#font[12]{p}} (GeV/#font[12]{c}^{2});#font[12]{q}_{#Lambda#font[12]{p}} (GeV/#font[12]{c})", 50,2.,3.,100,0.,2.);

        // resolution plots
        new TH2F(Form("resolution_beam_momentum_%s",_meas_type[i_type].data()),"Resolution of beam momentum;#font[12]{p}_{K^{-}} (GeV/#font[12]{c});#Delta#font[12]{p}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("resolution_lambda_momentum_%s",_meas_type[i_type].data()),"Resolution of #Lambda momentum;#font[12]{p}_{#Lambda} (GeV/#font[12]{c});#Delta#font[12]{p}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("resolution_proton_momentum_%s",_meas_type[i_type].data()),"Resolution of proton momentum;#font[12]{p}_{#font[12]{p}} (GeV/#font[12]{c});#Delta#font[12]{p}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("resolution_neutron_momentum_%s",_meas_type[i_type].data()),"Resolution of neutron momentum;#font[12]{p}_{#font[12]{n}} (GeV/#font[12]{c});#Delta#font[12]{p}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("resolution_pi_from_lambda_momentum_%s",_meas_type[i_type].data()),"Resolution of #pi from #Lambda momentum;#font[12]{p}_{#pi from #Lambda} (GeV/#font[12]{c});#Delta#font[12]{p}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("resolution_nucleon_from_lambda_momentum_%s",_meas_type[i_type].data()),"Resolution of nucleon from #Lambda momentum;#font[12]{p}_{#font[12]{N} from #Lambda} (GeV/#font[12]{c});#Delta#font[12]{p}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);

        new TH2F(Form("resolution_lp_mass_%s",_meas_type[i_type].data()),"Resolution of #Lambdap mass;#font[12]{m}_{#Lambda#font[12]{p}} (GeV/#font[12]{c}^{2});#Delta#font[12]{m}/#font[12]{m};Counts", 50,2.,3.,80,-0.02,0.02);
        new TH2F(Form("resolution_lp_momtrans_%s",_meas_type[i_type].data()),"Resolution of #Lambdap momentum transfer;#font[12]{q}_{#Lambda#font[12]{p}} (GeV/#font[12]{c});#Delta#font[12]{q}/#font[12]{q};Counts", 100,0.,2.,80,-0.1,0.1);
        new TH2F(Form("resolution_ln_mass_%s",_meas_type[i_type].data()),"Resolution of #Lambdan mass;#font[12]{m}_{#Lambda#font[12]{n}} (GeV/#font[12]{c}^{2});#Delta#font[12]{m}/#font[12]{m};Counts", 50,2.,3.,80,-0.02,0.02);
        new TH2F(Form("resolution_ln_momtrans_%s",_meas_type[i_type].data()),"Resolution of #Lambdan momentum transfer;#font[12]{q}_{#Lambda#font[12]{n}} (GeV/#font[12]{c});#Delta#font[12]{q}/#font[12]{q};Counts", 100,0.,2.,80,-0.1,0.1);

        // covariance for kinematical fitting
        new TH2F(Form("covariance_beam_px_%s",_meas_type[i_type].data()),"Covariance of beam p_{x};#font[12]{p}_{K^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{x}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_lambda_px_%s",_meas_type[i_type].data()),"Covariance of #Lambda p_{x};#font[12]{p}_{#Lambda} (GeV/#font[12]{c});#Delta#font[12]{p_{x}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_proton_px_%s",_meas_type[i_type].data()),"Covariance of proton p_{x};#font[12]{p}_{#font[12]{p}} (GeV/#font[12]{c});#Delta#font[12]{p_{x}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_neutron_px_%s",_meas_type[i_type].data()),"Covariance of neutron p_{x};#font[12]{p}_{#font[12]{n}} (GeV/#font[12]{c});#Delta#font[12]{p_{x}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_pi_from_lambda_px_%s",_meas_type[i_type].data()),"Covariance of #pi from #Lambda p_{x};#font[12]{p}_{#pi from #Lambda} (GeV/#font[12]{c});#Delta#font[12]{p_{x}}/#font[12]{p};Counts", 75,0.,0.5,80,-0.1,0.1);
        new TH2F(Form("covariance_nucleon_from_lambda_px_%s",_meas_type[i_type].data()),"Covariance of nucleon from #Lambda p_{x};#font[12]{p}_{#font[12]{N} from #Lambda} (GeV/#font[12]{c});#Delta#font[12]{p_{x}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);

        new TH2F(Form("covariance_beam_py_%s",_meas_type[i_type].data()),"Covariance of beam p_{y};#font[12]{p}_{K^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{y}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_lambda_py_%s",_meas_type[i_type].data()),"Covariance of #Lambda p_{y};#font[12]{p}_{#Lambda} (GeV/#font[12]{c});#Delta#font[12]{p_{y}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_proton_py_%s",_meas_type[i_type].data()),"Covariance of proton p_{y};#font[12]{p}_{#font[12]{p}} (GeV/#font[12]{c});#Delta#font[12]{p_{y}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_neutron_py_%s",_meas_type[i_type].data()),"Covariance of neutron p_{y};#font[12]{p}_{#font[12]{n}} (GeV/#font[12]{c});#Delta#font[12]{p_{y}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_pi_from_lambda_py_%s",_meas_type[i_type].data()),"Covariance of #pi from #Lambda p_{y};#font[12]{p}_{#pi from #Lambda} (GeV/#font[12]{c});#Delta#font[12]{p_{y}}/#font[12]{p};Counts", 75,0.,0.5,80,-0.1,0.1);
        new TH2F(Form("covariance_nucleon_from_lambda_py_%s",_meas_type[i_type].data()),"Covariance of nucleon from #Lambda p_{y};#font[12]{p}_{#font[12]{N} from #Lambda} (GeV/#font[12]{c});#Delta#font[12]{p_{y}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);

        new TH2F(Form("covariance_beam_pz_%s",_meas_type[i_type].data()),"Covariance of beam p_{z};#font[12]{p}_{K^{-}} (GeV/#font[12]{c});#Delta#font[12]{p_{z}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_lambda_pz_%s",_meas_type[i_type].data()),"Covariance of #Lambda p_{z};#font[12]{p}_{#Lambda} (GeV/#font[12]{c});#Delta#font[12]{p_{z}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_proton_pz_%s",_meas_type[i_type].data()),"Covariance of proton p_{z};#font[12]{p}_{#font[12]{p}} (GeV/#font[12]{c});#Delta#font[12]{p_{z}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_neutron_pz_%s",_meas_type[i_type].data()),"Covariance of neutron p_{z};#font[12]{p}_{#font[12]{n}} (GeV/#font[12]{c});#Delta#font[12]{p_{z}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        new TH2F(Form("covariance_pi_from_lambda_pz_%s",_meas_type[i_type].data()),"Covariance of #pi from #Lambda p_{z};#font[12]{p}_{#pi from #Lambda} (GeV/#font[12]{c});#Delta#font[12]{p_{z}}/#font[12]{p};Counts", 75,0.,0.5,80,-0.1,0.1);
        new TH2F(Form("covariance_nucleon_from_lambda_pz_%s",_meas_type[i_type].data()),"Covariance of nucleon from #Lambda p_{z};#font[12]{p}_{#font[12]{N} from #Lambda} (GeV/#font[12]{c});#Delta#font[12]{p_{z}}/#font[12]{p};Counts", 75,0.,1.5,80,-0.2,0.2);
        // 2D histograms ------------------------------------------------------------------------------
    }


    // for neutral detection
    new TH1F("neutral_number_of_hits","Number of hits of neutral particle;# of neutral;Counts", 11, -0.5, 10.5);
    new TH2F("neutral_over_beta_vs_energy_deposit_meas","1/#beta vs. dE of neutral particle;1/#beta;dE (MeVee)", 100, 0.0, 10.0, 100, 0.0, 100.0);

    _is_created = true;
}

void AnalyzerLpn::DoAnalysis(MCData* mcData, DetectorData* detectorData, AnalyzedData* analyzedData)
{

    // ============================================================================================
    // For MCData =================================================================================
    // ============================================================================================
    Int_t total_tracks = mcData->trackSize();   

    TVector3 vec_vertex_reaction(0.,0.,0.);
    TLorentzVector lv_beam_mc(0.,0.,0.,0.);
    TLorentzVector lv_lambda_mc(0.,0.,0.,0.);
    TLorentzVector lv_proton_mc(0.,0.,0.,0.);
    TLorentzVector lv_neutron_mc(0.,0.,0.,0.);
    Double_t lambda_flight_time_mc = 999.;
    Double_t proton_flight_time_mc = 999.;
    TVector3 vec_proton_momentum_at_chc_mc(0.,0.,0.);
    TVector3 vec_proton_position_at_chc_mc(0.,0.,0.);
    Int_t track_id_lambda = 0;
    // check generated particle (parentTrackID==0)
    for(Int_t i_track = 0; i_track<total_tracks; i_track++){
        Track* track = mcData->track(i_track);
        if(track->parentTrackID()!=0) continue;
        Int_t pdg_id = track->pdgID();
        if(pdg_id==321){ // K-beam
            vec_vertex_reaction = track->vertex()*0.1; // cm
            lv_beam_mc.SetVectM(-track->momentum()*0.001,kKaonMass);
        }
        else if(pdg_id==3122){ // Lambda
            track_id_lambda = track->trackID();
            lv_lambda_mc.SetVectM(track->momentum()*0.001,kLambdaMass);
            lambda_flight_time_mc = track->FlightTime();
        }
        else if(pdg_id==2212){ // proton
            lv_proton_mc.SetVectM(track->momentum()*0.001,kProtonMass);
            // check proton flight time to CHCbarrel or CHC cap
            for(Int_t i_hit=0; i_hit<track->detectorHitLinkSize(); ++i_hit){
                DetectorHit* hit = detectorData->detectorHit(track->detectorHitLink(i_hit));
                if(hit->detectorID()==CID_CHCbarrel||hit->detectorID()==CID_CHCcapF||hit->detectorID()==CID_CHCcapB){
                    if(proton_flight_time_mc>hit->time()){
                        proton_flight_time_mc=hit->time();
                    }
                }
                if(hit->detectorID()==CID_CHCbarrel){
                    vec_proton_momentum_at_chc_mc = hit->momentum()*0.001; // GeV/c
                    vec_proton_position_at_chc_mc = hit->pos()*0.1; // cm
                }
            }
        }
        else if(pdg_id==2112){ // neutron
            lv_neutron_mc.SetVectM(track->momentum()*0.001,kNeutronMass);
        }
    }

    TVector3 vec_k_to_chc_mc = vec_proton_momentum_at_chc_mc;
    if(vec_k_to_chc_mc.Mag()) vec_k_to_chc_mc.SetMag(1.);
    TVector3 vec_normal_to_chc_mc = vec_proton_position_at_chc_mc;
    vec_normal_to_chc_mc.SetZ(0.);
    if(vec_normal_to_chc_mc.Mag()) vec_normal_to_chc_mc.SetMag(1.);
    TVector3 vec_parallel_to_chc_mc(vec_normal_to_chc_mc.Y(),-vec_normal_to_chc_mc.X(),0.);
    if(vec_parallel_to_chc_mc.Mag()) vec_parallel_to_chc_mc.SetMag(1.);
    Double_t proton_theta_against_to_chc_mc = TMath::ACos(vec_k_to_chc_mc.Dot(vec_normal_to_chc_mc) /vec_k_to_chc_mc.Mag()/vec_normal_to_chc_mc.Mag());
    Double_t proton_phi_against_to_chc_mc = sign(vec_k_to_chc_mc.Dot(vec_parallel_to_chc_mc)) * TMath::ACos(vec_k_to_chc_mc.Z()/sqrt(pow(vec_k_to_chc_mc.Z(),2.)+pow(vec_k_to_chc_mc.Dot(vec_parallel_to_chc_mc),2.)));

    TVector3 vec_vertex_lambda_decay(0.,0.,0.);
    TLorentzVector lv_pi_from_lambda_mc(0.,0.,0.,0.);
    TLorentzVector lv_nucleon_from_lambda_mc(0.,0.,0.,0.);
    bool is_lambda_decay_charged = false;
    bool is_lambda_decay_neutral = false;
    // check decay product (parentTrackID == track_id_lambda)
    for(Int_t i_track = 0; i_track<total_tracks; i_track++){
        Track* track = mcData->track(i_track);
        if(track->parentTrackID()!=track_id_lambda) continue;
        Int_t pdg_id = track->pdgID();
        if(pdg_id==-211){ // pi-
            is_lambda_decay_charged = true;
            vec_vertex_lambda_decay = track->vertex()*0.1; // cm
            lv_pi_from_lambda_mc.SetVectM(track->momentum()*0.001,kPiMass);
        }
        else if(pdg_id==111){
            is_lambda_decay_neutral = true;
            vec_vertex_lambda_decay = track->vertex()*0.1; // cm
            lv_pi_from_lambda_mc.SetVectM(track->momentum()*0.001,kPi0Mass);
        }
        else if(pdg_id==2212){ // proton
            lv_nucleon_from_lambda_mc.SetVectM(track->momentum()*0.001,kProtonMass);
        }
        else if(pdg_id==2112){ // neutron
            lv_nucleon_from_lambda_mc.SetVectM(track->momentum()*0.001,kNeutronMass);
        }
    }
    TVector3 boost_lambda_rest_mc = lv_lambda_mc.BoostVector();
    TLorentzVector lv_pi_from_lambda_lambda_rest_mc = lv_pi_from_lambda_mc;
    lv_pi_from_lambda_lambda_rest_mc.Boost(-boost_lambda_rest_mc);
    TLorentzVector lv_nucleon_from_lambda_lambda_rest_mc = lv_nucleon_from_lambda_mc;
    lv_nucleon_from_lambda_lambda_rest_mc.Boost(-boost_lambda_rest_mc);

    TVector3 vec_reference_proton_mc = lv_nucleon_from_lambda_lambda_rest_mc.Vect();
    if(vec_reference_proton_mc.Mag()) vec_reference_proton_mc.SetMag(1.);
    Double_t omega_lambda = -2.*kLambdaMagneticMoment*kNuclearMagneton/kPlanckConstantReduced * kMagneticField * pow(10.,-9.); // rad/ns
    Double_t omega_proton = -2.*kProtonMagneticMoment*kNuclearMagneton/kPlanckConstantReduced * kMagneticField * pow(10.,-9.); // rad/ns
    Double_t lambda_delta_phi_mc = omega_lambda * lambda_flight_time_mc; // rad
    Double_t proton_delta_phi_mc = omega_proton * proton_flight_time_mc; // rad
    Double_t total_delta_phi_mc = -lambda_delta_phi_mc + proton_delta_phi_mc;
    vec_reference_proton_mc.RotateZ(total_delta_phi_mc);
    Double_t reference_axis_sin_theta_mc = sin( TMath::ACos( vec_k_to_chc_mc.Dot(vec_reference_proton_mc)/vec_k_to_chc_mc.Mag()/vec_reference_proton_mc.Mag() ) );

    Double_t factor_b_mc = - ( vec_normal_to_chc_mc.X()*vec_k_to_chc_mc.X() + vec_normal_to_chc_mc.Y()*vec_k_to_chc_mc.Y() ) / vec_k_to_chc_mc.Z();
    TVector3 vec_yprime_mc = vec_normal_to_chc_mc;
    vec_yprime_mc.SetZ(factor_b_mc);
    if(vec_yprime_mc.Mag()) vec_yprime_mc.SetMag(1.);
    TVector3 vec_xprime_mc = vec_yprime_mc.Cross(vec_k_to_chc_mc);
    Double_t reference_axis_proton_xprime_mc = vec_reference_proton_mc.Dot(vec_xprime_mc);
    Double_t reference_axis_proton_yprime_mc = vec_reference_proton_mc.Dot(vec_yprime_mc);
    Double_t reference_axis_phi_mc = sign(reference_axis_proton_yprime_mc) * TMath::ACos(reference_axis_proton_xprime_mc/sqrt(pow(reference_axis_proton_xprime_mc,2.)+pow(reference_axis_proton_yprime_mc,2.)));

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
    TLorentzVector lv_proton_meas(0.,0.,0.,0.);
    TLorentzVector lv_nucleon_from_lambda_meas(0.,0.,0.,0.);
    TLorentzVector lv_pi_from_lambda_meas(0.,0.,0.,0.);
    TLorentzVector lv_target_meas(0.,0.,0.,kThreeHeMass);
    TLorentzVector lv_lambda_meas(0.,0.,0.,0.);
    TLorentzVector lv_neutron_meas(0.,0.,0.,0.);
    TLorentzVector lv_detected_proton_meas(0.,0.,0.,0.);
    TLorentzVector lv_detected_neutron_meas(0.,0.,0.,0.);
    TLorentzVector lv_missing_proton_meas(0.,0.,0.,0.);
    TLorentzVector lv_missing_neutron_meas(0.,0.,0.,0.);
    Int_t measured_neutral_generation = -999;
    TVector3 vec_neutral_generated_position(999.,999.,999.);
    Double_t measured_neutral_charge = -999.;
    std::vector<TVector3> vec_neutral_parent_generated_positions;
    std::vector<Double_t> measured_parent_neutral_charges;
    Double_t measured_neutral_energy_deposit = -999.;
    Double_t measured_neutral_over_beta = -999.;
    Double_t measured_neutral_time = -999.;

    bool is_beam_detected = false;
    bool is_proton_detected = false;
    bool is_neutron_detected = false;
    bool is_true_neutron_detected = false;
    bool is_fake_neutron_detected = false;
    bool is_proton_from_lambda_detected = false;
    bool is_pim_from_lambda_detected = false;

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
            if(track->parentTrackID()==0){
                is_proton_detected = true;
                lv_detected_proton_meas.SetVectM(track->momentum(),kProtonMass);
            }
            else{
                is_proton_from_lambda_detected = true;
                lv_nucleon_from_lambda_meas.SetVectM(track->momentum(),kProtonMass);
            }
        }
        else if(track->pdgID()==-211&&track->parentTrackID()!=0){
            is_pim_from_lambda_detected = true;
            lv_pi_from_lambda_meas.SetVectM(track->momentum(),kPiMass);
        }
    }
    // neutron
    Fill("neutral_number_of_hits",measured_neutral_tracks.size());
    if(measured_neutral_tracks.size()==1){
        is_neutron_detected = true;
        Int_t parent_id = measured_neutral_tracks[0]->parentTrackID();
        lv_detected_neutron_meas.SetVectM(measured_neutral_tracks[0]->momentum(),kNeutronMass);
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
                if(track->parentTrackID()!=0){
                    parent_id = track->parentTrackID();
                    i_track=-1;
                }
                else{
                    parent_id = 0;
                    if(track->pdgID()==2112){
                        is_true_neutron_detected = true;
                    }
                    else{
                        is_fake_neutron_detected = true;
                    }
                }
            }
        }
        if(parent_id!=0){
            is_fake_neutron_detected = true;
        }
    }
    measured_neutral_generation = vec_neutral_parent_generated_positions.size();

    if(measured_neutral_generation!=1){
        is_true_neutron_detected = false;
        is_fake_neutron_detected = is_neutron_detected;
    }

    lv_lambda_meas = lv_nucleon_from_lambda_meas + lv_pi_from_lambda_meas;
    lv_missing_proton_meas = (lv_beam_meas+lv_target_meas) - (lv_lambda_meas+lv_detected_neutron_meas);
    lv_missing_neutron_meas = (lv_beam_meas+lv_target_meas) - (lv_lambda_meas+lv_detected_proton_meas);

    bool is_accepted_lp = is_beam_detected & is_proton_detected & is_proton_from_lambda_detected & is_pim_from_lambda_detected;
    bool is_accepted_ln = is_beam_detected & is_neutron_detected & is_proton_from_lambda_detected & is_pim_from_lambda_detected;
    bool is_accepted_ln_true = is_beam_detected & is_true_neutron_detected & is_proton_from_lambda_detected & is_pim_from_lambda_detected;
    bool is_accepted_ln_fake = is_beam_detected & is_fake_neutron_detected & is_proton_from_lambda_detected & is_pim_from_lambda_detected;
    bool is_accepted_lpn = is_accepted_lp & is_accepted_ln;
    bool is_accepted_lpn_true = is_accepted_lp & is_accepted_ln_true;
    bool is_accepted_lpn_fake = is_accepted_lp & is_accepted_ln_fake;
    // ============================================================================================
    // ============================================================================================
    // ============================================================================================


    // ============================================================================================
    // Kinematical fitting ========================================================================
    // ============================================================================================
    TLorentzVector lv_beam_kfit;
    TLorentzVector lv_lambda_kfit;
    TLorentzVector lv_proton_kfit;
    TLorentzVector lv_neutron_kfit;
    TLorentzVector lv_pi_from_lambda_kfit;
    TLorentzVector lv_nucleon_from_lambda_kfit;
    Double_t reduced_chisquare_kfit;

    // for lp detection -----------------------------------
    Double_t reduced_chisquare_lp = -999.;
    const Int_t total_particles_lp = 7;
    TLorentzVector lv_kfit_lp[total_particles_lp];
    if(is_accepted_lp){
        // [0] : target
        // [1] : beam
        // [2] : lambda
        // [3] : proton
        // [4] : neutron (missing)
        // [5] : pi- from lambda
        // [6] : proton from lambda
        Double_t val_covariance_proton[9];
        GetCovarianceProton(lv_detected_proton_meas.P(),val_covariance_proton);
        Double_t val_covariance_pi_from_lambda[9];
        GetCovariancePi(lv_pi_from_lambda_meas.P(),val_covariance_pi_from_lambda);
        Double_t val_covariance_nucleon_from_lambda[9];
        GetCovarianceProton(lv_nucleon_from_lambda_meas.P(),val_covariance_nucleon_from_lambda);

        TLorentzVector* lv_meas[total_particles_lp] = {&lv_target_meas,&lv_beam_meas,&lv_lambda_meas,&lv_detected_proton_meas,&lv_missing_neutron_meas,&lv_pi_from_lambda_meas,&lv_nucleon_from_lambda_meas};
        Double_t masses[total_particles_lp] = {kThreeHeMass,kKaonMass,kLambdaMass,kProtonMass,kNeutronMass,kPiMass,kProtonMass};
        TMatrixD* covariances[total_particles_lp];
        covariances[0] = new TMatrixD(3,3,kValCovarianceZero);                  // : target
        covariances[1] = new TMatrixD(3,3,kValCovarianceBeam);                  // : beam
        covariances[2] = new TMatrixD(3,3,kValCovarianceZero);                  // : lambda
        covariances[3] = new TMatrixD(3,3,val_covariance_proton);               // : proton
        covariances[4] = new TMatrixD(3,3,kValCovarianceZero);                  // : neutron (missing)
        covariances[5] = new TMatrixD(3,3,val_covariance_pi_from_lambda);       // : pim from lambda
        covariances[6] = new TMatrixD(3,3,val_covariance_nucleon_from_lambda);  // : proton from lambda
        TFitParticlePxPyPz particles[total_particles_lp];
        for(Int_t i_particle=0; i_particle<total_particles_lp; ++i_particle){
            TVector3 vec_momentum = lv_meas[i_particle]->Vect();
            particles[i_particle] = TFitParticlePxPyPz(Form("particle_%d",i_particle), Form("particle_%d",i_particle), &vec_momentum, masses[i_particle], covariances[i_particle]);
        }

        // constraint :: mass of lambda
        TFitConstraintM constraint_lambda_mass = TFitConstraintM("lambda_mass", "lambda_mass", 0, 0, kLambdaMass);
        constraint_lambda_mass.addParticles1(&particles[5], &particles[6]);
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
        kinfitter.addConstraint(&constraint_lambda_mass);
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
        reduced_chisquare_lp = kinfitter.getS()/kinfitter.getNDF();
        for(Int_t i_particle=0; i_particle<total_particles_lp; ++i_particle){
            lv_kfit_lp[i_particle] = (*particles[i_particle].getCurr4Vec());
            delete covariances[i_particle];
        }
    }
    // for lp detection -----------------------------------

    // for ln detection -----------------------------------
    Double_t reduced_chisquare_ln = -999.;
    const Int_t total_particles_ln = 7;
    TLorentzVector lv_kfit_ln[total_particles_ln];
    if(is_accepted_ln){
        // [0] : target
        // [1] : beam
        // [2] : lambda
        // [3] : proton
        // [4] : neutron (missing)
        // [5] : pi- from lambda
        // [6] : proton from lambda
        Double_t val_covariance_neutron[9];
        GetCovarianceNeutron(lv_detected_neutron_meas.P(),val_covariance_neutron);
        Double_t val_covariance_pi_from_lambda[9];
        GetCovariancePi(lv_pi_from_lambda_meas.P(),val_covariance_pi_from_lambda);
        Double_t val_covariance_nucleon_from_lambda[9];
        GetCovarianceProton(lv_nucleon_from_lambda_meas.P(),val_covariance_nucleon_from_lambda);

        TLorentzVector* lv_meas[total_particles_ln] = {&lv_target_meas,&lv_beam_meas,&lv_lambda_meas,&lv_missing_proton_meas,&lv_detected_neutron_meas,&lv_pi_from_lambda_meas,&lv_nucleon_from_lambda_meas};
        Double_t masses[total_particles_ln] = {kThreeHeMass,kKaonMass,kLambdaMass,kProtonMass,kNeutronMass,kPiMass,kProtonMass};
        TMatrixD* covariances[total_particles_ln];
        covariances[0] = new TMatrixD(3,3,kValCovarianceZero);                  // : target
        covariances[1] = new TMatrixD(3,3,kValCovarianceBeam);                  // : beam
        covariances[2] = new TMatrixD(3,3,kValCovarianceZero);                  // : lambda
        covariances[3] = new TMatrixD(3,3,kValCovarianceZero);                  // : proton (missing)
        covariances[4] = new TMatrixD(3,3,val_covariance_neutron);              // : neutron
        covariances[5] = new TMatrixD(3,3,val_covariance_pi_from_lambda);       // : pim from lambda
        covariances[6] = new TMatrixD(3,3,val_covariance_nucleon_from_lambda);  // : proton from lambda
        TFitParticlePxPyPz particles[total_particles_ln];
        for(Int_t i_particle=0; i_particle<total_particles_ln; ++i_particle){
            TVector3 vec_momentum = lv_meas[i_particle]->Vect();
            particles[i_particle] = TFitParticlePxPyPz(Form("particle_%d",i_particle), Form("particle_%d",i_particle), &vec_momentum, masses[i_particle], covariances[i_particle]);
        }

        // constraint :: mass of lambda
        TFitConstraintM constraint_lambda_mass = TFitConstraintM("lambda_mass", "lambda_mass", 0, 0, kLambdaMass);
        constraint_lambda_mass.addParticles1(&particles[5], &particles[6]);
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
        kinfitter.addConstraint(&constraint_lambda_mass);
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
        reduced_chisquare_ln = kinfitter.getS()/kinfitter.getNDF();
        for(Int_t i_particle=0; i_particle<total_particles_ln; ++i_particle){
            lv_kfit_ln[i_particle] = (*particles[i_particle].getCurr4Vec());
            delete covariances[i_particle];
        }
    }
    // for ln detection -----------------------------------

    // ============================================================================================
    // ============================================================================================
    // ============================================================================================

    // ============================================================================================
    // FILLING HISTOGRAMS =========================================================================
    // ============================================================================================
    Fill("beam_momentum_lab_gene",lv_beam_mc.P());
    Fill("lambda_momentum_lab_gene",lv_lambda_mc.P());
    Fill("proton_momentum_lab_gene",lv_proton_mc.P());
    Fill("neutron_momentum_lab_gene",lv_neutron_mc.P());
    Fill("pi_from_lambda_momentum_lab_gene",lv_pi_from_lambda_mc.P());
    Fill("nucleon_from_lambda_momentum_lab_gene",lv_nucleon_from_lambda_mc.P());
    Fill("lambda_mass_gene",lv_lambda_mc.M());
    Fill("proton_mass_gene",lv_proton_mc.M());
    Fill("neutron_mass_gene",lv_neutron_mc.M());
    Fill("lp_mass_gene",(lv_lambda_mc+lv_proton_mc).M());
    Fill("lp_momtrans_gene",(lv_lambda_mc+lv_proton_mc).P());
    Fill("ln_mass_gene",(lv_lambda_mc+lv_neutron_mc).M());
    Fill("ln_momtrans_gene",(lv_lambda_mc+lv_neutron_mc).P());

    Fill("proton_flight_time_gene",proton_flight_time_mc);
    Fill("lambda_flight_time_gene",lambda_flight_time_mc);
    Fill("reference_axis_sin_theta_gene",reference_axis_sin_theta_mc);
    Fill("reference_axis_sin_phi_gene",sin(reference_axis_phi_mc));

    Fill("beam_cos_theta_vs_phi_lab_gene",lv_beam_mc.CosTheta(),lv_beam_mc.Phi());
    Fill("lambda_cos_theta_vs_phi_lab_gene",lv_lambda_mc.CosTheta(),lv_lambda_mc.Phi());
    Fill("proton_cos_theta_vs_phi_lab_gene",lv_proton_mc.CosTheta(),lv_proton_mc.Phi());
    Fill("neutron_cos_theta_vs_phi_lab_gene",lv_neutron_mc.CosTheta(),lv_neutron_mc.Phi());
    Fill("pi_from_lambda_cos_theta_vs_phi_lab_gene",lv_pi_from_lambda_mc.CosTheta(),lv_pi_from_lambda_mc.Phi());
    Fill("nucleon_from_lambda_cos_theta_vs_phi_lab_gene",lv_nucleon_from_lambda_mc.CosTheta(),lv_nucleon_from_lambda_mc.Phi());

    Fill("nucleon_from_lambda_cos_theta_vs_phi_lambda_rest_gene",lv_nucleon_from_lambda_lambda_rest_mc.CosTheta(),lv_nucleon_from_lambda_lambda_rest_mc.Phi());
    Fill("proton_theta_vs_phi_against_to_chc_gene",proton_theta_against_to_chc_mc,proton_phi_against_to_chc_mc);
    Fill("proton_theta_vs_phi_against_to_chc_in_deg_gene",proton_theta_against_to_chc_mc/TMath::Pi()*180.,proton_phi_against_to_chc_mc/TMath::Pi()*180.);
    Fill("reference_axis_sin_theta_vs_phi_gene",reference_axis_sin_theta_mc,reference_axis_phi_mc);
    Fill("reference_axis_sin_theta_vs_sin_phi_gene",reference_axis_sin_theta_mc,sin(reference_axis_phi_mc));

    Fill("lp_mass_vs_momtrans_gene",(lv_lambda_mc+lv_proton_mc).M(),(lv_lambda_mc+lv_proton_mc).P());
    Fill("ln_mass_vs_momtrans_gene",(lv_lambda_mc+lv_proton_mc).M(),(lv_lambda_mc+lv_proton_mc).P());

    Fill("neutron_momentum_lab_vs_lambda_momentum_lab_gene",lv_neutron_mc.P(),lv_lambda_mc.P());
    Fill("neutron_cos_theta_lab_vs_lambda_cos_theta_lab_gene",lv_neutron_mc.CosTheta(),lv_lambda_mc.CosTheta());

    if(reference_axis_sin_theta_mc>0.98&&sin(reference_axis_phi_mc)>0.98){
        Fill("lambda_momentum_lab_reference_axis_selected_gene",lv_lambda_mc.P());
        Fill("proton_momentum_lab_reference_axis_selected_gene",lv_proton_mc.P());
        Fill("neutron_momentum_lab_reference_axis_selected_gene",lv_neutron_mc.P());
        Fill("pi_from_lambda_momentum_lab_reference_axis_selected_gene",lv_pi_from_lambda_mc.P());
        Fill("nucleon_from_lambda_momentum_lab_reference_axis_selected_gene",lv_nucleon_from_lambda_mc.P());

        Fill("lambda_cos_theta_vs_phi_lab_reference_axis_selected_gene",lv_lambda_mc.CosTheta(),lv_lambda_mc.Phi());
        Fill("proton_cos_theta_vs_phi_lab_reference_axis_selected_gene",lv_proton_mc.CosTheta(),lv_proton_mc.Phi());
        Fill("neutron_cos_theta_vs_phi_lab_reference_axis_selected_gene",lv_neutron_mc.CosTheta(),lv_neutron_mc.Phi());
        Fill("pi_from_lambda_cos_theta_vs_phi_lab_reference_axis_selected_gene",lv_pi_from_lambda_mc.CosTheta(),lv_pi_from_lambda_mc.Phi());
        Fill("nucleon_from_lambda_cos_theta_vs_phi_lab_reference_axis_selected_gene",lv_nucleon_from_lambda_mc.CosTheta(),lv_nucleon_from_lambda_mc.Phi());

        Fill("nucleon_from_lambda_cos_theta_vs_phi_lambda_rest_reference_axis_selected_gene",lv_nucleon_from_lambda_lambda_rest_mc.CosTheta(),lv_nucleon_from_lambda_lambda_rest_mc.Phi());
        Fill("proton_theta_vs_phi_against_to_chc_reference_axis_selected_gene",proton_theta_against_to_chc_mc,proton_phi_against_to_chc_mc);
        Fill("proton_theta_vs_phi_against_to_chc_in_deg_reference_axis_selected_gene",proton_theta_against_to_chc_mc/TMath::Pi()*180.,proton_phi_against_to_chc_mc/TMath::Pi()*180.);
        Fill("reference_axis_sin_theta_vs_phi_reference_axis_selected_gene",reference_axis_sin_theta_mc,reference_axis_phi_mc);
        Fill("reference_axis_sin_theta_vs_sin_phi_reference_axis_selected_gene",reference_axis_sin_theta_mc,sin(reference_axis_phi_mc));

        Fill("lp_mass_vs_momtrans_reference_axis_selected_reference_axis_selected_gene",(lv_lambda_mc+lv_proton_mc).M(),(lv_lambda_mc+lv_proton_mc).P());
    }

    for(UInt_t i_meas=0; i_meas<measured_neutral_energy_deposits.size(); i_meas++){
        Fill("neutral_over_beta_vs_energy_deposit_meas",measured_neutral_over_betas[i_meas],measured_neutral_energy_deposits[i_meas]);
    }

    bool fill_flag[7] = {is_accepted_lp, is_accepted_ln, is_accepted_ln_true, is_accepted_ln_fake,
        is_accepted_lpn, is_accepted_lpn_true, is_accepted_lpn_fake};
    std::string meas[7] = {"lp","ln","ln_true","ln_fake","lpn","lpn_true","lpn_fake"};
    for(Int_t i_meas=0; i_meas<7; i_meas++){
        switch(i_meas){
            case 0: // Lp detection
                lv_proton_meas = lv_detected_proton_meas;
                lv_neutron_meas = lv_missing_neutron_meas;
                lv_beam_kfit = lv_kfit_lp[1];
                lv_proton_kfit = lv_kfit_lp[3];
                lv_neutron_kfit = lv_kfit_lp[4];
                lv_pi_from_lambda_kfit = lv_kfit_lp[5];
                lv_nucleon_from_lambda_kfit = lv_kfit_lp[6];
                lv_lambda_kfit = lv_pi_from_lambda_kfit + lv_nucleon_from_lambda_kfit;
                reduced_chisquare_kfit = reduced_chisquare_lp;
                break;
            case 1: // Ln detection
                lv_proton_meas = lv_missing_proton_meas;
                lv_neutron_meas = lv_detected_neutron_meas;
                lv_beam_kfit = lv_kfit_ln[1];
                lv_proton_kfit = lv_kfit_ln[3];
                lv_neutron_kfit = lv_kfit_ln[4];
                lv_pi_from_lambda_kfit = lv_kfit_ln[5];
                lv_nucleon_from_lambda_kfit = lv_kfit_ln[6];
                lv_lambda_kfit = lv_pi_from_lambda_kfit + lv_nucleon_from_lambda_kfit;
                reduced_chisquare_kfit = reduced_chisquare_ln;
                break;
            case 2: // Ln detection (TRUE)
                lv_proton_meas = lv_missing_proton_meas;
                lv_neutron_meas = lv_detected_neutron_meas;
                lv_beam_kfit = lv_kfit_ln[1];
                lv_proton_kfit = lv_kfit_ln[3];
                lv_neutron_kfit = lv_kfit_ln[4];
                lv_pi_from_lambda_kfit = lv_kfit_ln[5];
                lv_nucleon_from_lambda_kfit = lv_kfit_ln[6];
                lv_lambda_kfit = lv_pi_from_lambda_kfit + lv_nucleon_from_lambda_kfit;
                reduced_chisquare_kfit = reduced_chisquare_ln;
                break;
            case 3: // Ln detection (FAKE)
                lv_proton_meas = lv_missing_proton_meas;
                lv_neutron_meas = lv_detected_neutron_meas;
                lv_beam_kfit = lv_kfit_ln[1];
                lv_proton_kfit = lv_kfit_ln[3];
                lv_neutron_kfit = lv_kfit_ln[4];
                lv_pi_from_lambda_kfit = lv_kfit_ln[5];
                lv_nucleon_from_lambda_kfit = lv_kfit_ln[6];
                lv_lambda_kfit = lv_pi_from_lambda_kfit + lv_nucleon_from_lambda_kfit;
                reduced_chisquare_kfit = reduced_chisquare_ln;
                break;
            case 4: // Lpn detection
                lv_proton_meas = lv_detected_proton_meas;
                lv_neutron_meas = lv_detected_neutron_meas;
                break;
            case 5: // Lpn detection (TRUE)
                lv_proton_meas = lv_detected_proton_meas;
                lv_neutron_meas = lv_detected_neutron_meas;
                break;
            case 6: // Lpn detection (FAKE)
                lv_proton_meas = lv_detected_proton_meas;
                lv_neutron_meas = lv_detected_neutron_meas;
                break;
            default:
                break;
        }


        if(fill_flag[i_meas]){
            // acce -----
            Fill(Form("beam_momentum_lab_acce_%s",meas[i_meas].data()),lv_beam_mc.P());
            Fill(Form("lambda_momentum_lab_acce_%s",meas[i_meas].data()),lv_lambda_mc.P());
            Fill(Form("proton_momentum_lab_acce_%s",meas[i_meas].data()),lv_proton_mc.P());
            Fill(Form("neutron_momentum_lab_acce_%s",meas[i_meas].data()),lv_neutron_mc.P());
            Fill(Form("pi_from_lambda_momentum_lab_acce_%s",meas[i_meas].data()),lv_pi_from_lambda_mc.P());
            Fill(Form("nucleon_from_lambda_momentum_lab_acce_%s",meas[i_meas].data()),lv_nucleon_from_lambda_mc.P());
            Fill(Form("lambda_mass_acce_%s",meas[i_meas].data()),lv_lambda_mc.M());
            Fill(Form("proton_mass_acce_%s",meas[i_meas].data()),lv_proton_mc.M());
            Fill(Form("neutron_mass_acce_%s",meas[i_meas].data()),lv_neutron_mc.M());
            Fill(Form("lp_mass_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_proton_mc).M());
            Fill(Form("lp_momtrans_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_proton_mc).P());
            Fill(Form("ln_mass_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_neutron_mc).M());
            Fill(Form("ln_momtrans_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_neutron_mc).P());

            Fill(Form("proton_flight_time_acce_%s",meas[i_meas].data()),proton_flight_time_mc);
            Fill(Form("lambda_flight_time_acce_%s",meas[i_meas].data()),lambda_flight_time_mc);
            Fill(Form("reference_axis_sin_theta_acce_%s",meas[i_meas].data()),reference_axis_sin_theta_mc);
            Fill(Form("reference_axis_sin_phi_acce_%s",meas[i_meas].data()),sin(reference_axis_phi_mc));

            Fill(Form("beam_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_beam_mc.CosTheta(),lv_beam_mc.Phi());
            Fill(Form("lambda_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_lambda_mc.CosTheta(),lv_lambda_mc.Phi());
            Fill(Form("proton_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_proton_mc.CosTheta(),lv_proton_mc.Phi());
            Fill(Form("neutron_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_neutron_mc.CosTheta(),lv_neutron_mc.Phi());
            Fill(Form("pi_from_lambda_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_pi_from_lambda_mc.CosTheta(),lv_pi_from_lambda_mc.Phi());
            Fill(Form("nucleon_from_lambda_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_nucleon_from_lambda_mc.CosTheta(),lv_nucleon_from_lambda_mc.Phi());

            Fill(Form("nucleon_from_lambda_cos_theta_vs_phi_lambda_rest_acce_%s",meas[i_meas].data()),lv_nucleon_from_lambda_lambda_rest_mc.CosTheta(),lv_nucleon_from_lambda_lambda_rest_mc.Phi());
            Fill(Form("proton_theta_vs_phi_against_to_chc_acce_%s",meas[i_meas].data()),proton_theta_against_to_chc_mc,proton_phi_against_to_chc_mc);
            Fill(Form("proton_theta_vs_phi_against_to_chc_in_deg_acce_%s",meas[i_meas].data()),proton_theta_against_to_chc_mc/TMath::Pi()*180.,proton_phi_against_to_chc_mc/TMath::Pi()*180.);
            Fill(Form("reference_axis_sin_theta_vs_phi_acce_%s",meas[i_meas].data()),reference_axis_sin_theta_mc,reference_axis_phi_mc);
            Fill(Form("reference_axis_sin_theta_vs_sin_phi_acce_%s",meas[i_meas].data()),reference_axis_sin_theta_mc,sin(reference_axis_phi_mc));

            Fill(Form("lp_mass_vs_momtrans_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_proton_mc).M(),(lv_lambda_mc+lv_proton_mc).P());
            Fill(Form("ln_mass_vs_momtrans_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_neutron_mc).M(),(lv_lambda_mc+lv_neutron_mc).P());

            Fill(Form("neutron_momentum_lab_vs_lambda_momentum_lab_acce_%s",meas[i_meas].data()),lv_neutron_mc.P(),lv_lambda_mc.P());
            Fill(Form("neutron_cos_theta_lab_vs_lambda_cos_theta_lab_acce_%s",meas[i_meas].data()),lv_neutron_mc.CosTheta(),lv_lambda_mc.CosTheta());

            if(reference_axis_sin_theta_mc>0.98&&sin(reference_axis_phi_mc)>0.98){
                Fill(Form("lambda_momentum_lab_reference_axis_selected_acce_%s",meas[i_meas].data()),lv_lambda_mc.P());
                Fill(Form("proton_momentum_lab_reference_axis_selected_acce_%s",meas[i_meas].data()),lv_proton_mc.P());
                Fill(Form("neutron_momentum_lab_reference_axis_selected_acce_%s",meas[i_meas].data()),lv_neutron_mc.P());
                Fill(Form("pi_from_lambda_momentum_lab_reference_axis_selected_acce_%s",meas[i_meas].data()),lv_pi_from_lambda_mc.P());
                Fill(Form("nucleon_from_lambda_momentum_lab_reference_axis_selected_acce_%s",meas[i_meas].data()),lv_nucleon_from_lambda_mc.P());

                Fill(Form("lambda_cos_theta_vs_phi_lab_reference_axis_selected_acce_%s",meas[i_meas].data()),lv_lambda_mc.CosTheta(),lv_lambda_mc.Phi());
                Fill(Form("proton_cos_theta_vs_phi_lab_reference_axis_selected_acce_%s",meas[i_meas].data()),lv_proton_mc.CosTheta(),lv_proton_mc.Phi());
                Fill(Form("neutron_cos_theta_vs_phi_lab_reference_axis_selected_acce_%s",meas[i_meas].data()),lv_neutron_mc.CosTheta(),lv_neutron_mc.Phi());
                Fill(Form("pi_from_lambda_cos_theta_vs_phi_lab_reference_axis_selected_acce_%s",meas[i_meas].data()),lv_pi_from_lambda_mc.CosTheta(),lv_pi_from_lambda_mc.Phi());
                Fill(Form("nucleon_from_lambda_cos_theta_vs_phi_lab_reference_axis_selected_acce_%s",meas[i_meas].data()),lv_nucleon_from_lambda_mc.CosTheta(),lv_nucleon_from_lambda_mc.Phi());

                Fill(Form("nucleon_from_lambda_cos_theta_vs_phi_lambda_rest_reference_axis_selected_acce_%s",meas[i_meas].data()),lv_nucleon_from_lambda_lambda_rest_mc.CosTheta(),lv_nucleon_from_lambda_lambda_rest_mc.Phi());
                Fill(Form("proton_theta_vs_phi_against_to_chc_reference_axis_selected_acce_%s",meas[i_meas].data()),proton_theta_against_to_chc_mc,proton_phi_against_to_chc_mc);
                Fill(Form("proton_theta_vs_phi_against_to_chc_in_deg_reference_axis_selected_acce_%s",meas[i_meas].data()),proton_theta_against_to_chc_mc/TMath::Pi()*180.,proton_phi_against_to_chc_mc/TMath::Pi()*180.);
                Fill(Form("reference_axis_sin_theta_vs_phi_reference_axis_selected_acce_%s",meas[i_meas].data()),reference_axis_sin_theta_mc,reference_axis_phi_mc);
                Fill(Form("reference_axis_sin_theta_vs_sin_phi_reference_axis_selected_acce_%s",meas[i_meas].data()),reference_axis_sin_theta_mc,sin(reference_axis_phi_mc));

                Fill(Form("lp_mass_vs_momtrans_reference_axis_selected_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_proton_mc).M(),(lv_lambda_mc+lv_proton_mc).P());
            }

            // meas -----
            Fill(Form("beam_momentum_lab_meas_%s",meas[i_meas].data()),lv_beam_meas.P());
            Fill(Form("lambda_momentum_lab_meas_%s",meas[i_meas].data()),lv_lambda_meas.P());
            Fill(Form("proton_momentum_lab_meas_%s",meas[i_meas].data()),lv_proton_meas.P());
            Fill(Form("neutron_momentum_lab_meas_%s",meas[i_meas].data()),lv_neutron_meas.P());
            Fill(Form("pi_from_lambda_momentum_lab_meas_%s",meas[i_meas].data()),lv_pi_from_lambda_meas.P());
            Fill(Form("nucleon_from_lambda_momentum_lab_meas_%s",meas[i_meas].data()),lv_nucleon_from_lambda_meas.P());
            Fill(Form("lambda_mass_meas_%s",meas[i_meas].data()),lv_lambda_meas.M());
            Fill(Form("proton_mass_meas_%s",meas[i_meas].data()),lv_proton_meas.M());
            Fill(Form("neutron_mass_meas_%s",meas[i_meas].data()),lv_neutron_meas.M());
            Fill(Form("lp_mass_meas_%s",meas[i_meas].data()),(lv_lambda_meas+lv_proton_meas).M());
            Fill(Form("lp_momtrans_meas_%s",meas[i_meas].data()),(lv_lambda_meas+lv_proton_meas).P());
            Fill(Form("ln_mass_meas_%s",meas[i_meas].data()),(lv_lambda_meas+lv_neutron_meas).M());
            Fill(Form("ln_momtrans_meas_%s",meas[i_meas].data()),(lv_lambda_meas+lv_neutron_meas).P());
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
            Fill(Form("lambda_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_lambda_meas.CosTheta(),lv_lambda_meas.Phi());
            Fill(Form("proton_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_proton_meas.CosTheta(),lv_proton_meas.Phi());
            Fill(Form("neutron_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_neutron_meas.CosTheta(),lv_neutron_meas.Phi());
            Fill(Form("pi_from_lambda_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_pi_from_lambda_meas.CosTheta(),lv_pi_from_lambda_meas.Phi());
            Fill(Form("nucleon_from_lambda_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_nucleon_from_lambda_meas.CosTheta(),lv_nucleon_from_lambda_meas.Phi());

            Fill(Form("lp_mass_vs_momtrans_meas_%s",meas[i_meas].data()),(lv_lambda_meas+lv_proton_meas).M(),(lv_lambda_meas+lv_proton_meas).P());
            Fill(Form("ln_mass_vs_momtrans_meas_%s",meas[i_meas].data()),(lv_lambda_meas+lv_neutron_meas).M(),(lv_lambda_meas+lv_neutron_meas).P());

            Fill(Form("neutron_momentum_lab_vs_lambda_momentum_lab_meas_%s",meas[i_meas].data()),lv_neutron_meas.P(),lv_lambda_meas.P());
            Fill(Form("neutron_cos_theta_lab_vs_lambda_cos_theta_lab_meas_%s",meas[i_meas].data()),lv_neutron_meas.CosTheta(),lv_lambda_meas.CosTheta());

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
            Fill(Form("resolution_lambda_momentum_meas_%s",meas[i_meas].data()),lv_lambda_mc.P(),(lv_lambda_mc.P()-lv_lambda_meas.P())/lv_lambda_mc.P());
            Fill(Form("resolution_proton_momentum_meas_%s",meas[i_meas].data()),lv_proton_mc.P(),(lv_proton_mc.P()-lv_proton_meas.P())/lv_proton_mc.P());
            Fill(Form("resolution_neutron_momentum_meas_%s",meas[i_meas].data()),lv_neutron_mc.P(),(lv_neutron_mc.P()-lv_neutron_meas.P())/lv_neutron_mc.P());
            Fill(Form("resolution_pi_from_lambda_momentum_meas_%s",meas[i_meas].data()),lv_pi_from_lambda_mc.P(),(lv_pi_from_lambda_mc.P()-lv_pi_from_lambda_meas.P())/lv_pi_from_lambda_mc.P());
            Fill(Form("resolution_nucleon_from_lambda_momentum_meas_%s",meas[i_meas].data()),lv_nucleon_from_lambda_mc.P(),(lv_nucleon_from_lambda_mc.P()-lv_nucleon_from_lambda_meas.P())/lv_nucleon_from_lambda_mc.P());

            Fill(Form("resolution_lp_mass_meas_%s",meas[i_meas].data()),(lv_lambda_mc+lv_proton_mc).M(),( (lv_lambda_mc+lv_proton_mc).M()-(lv_lambda_meas+lv_proton_meas).M() )/(lv_lambda_mc+lv_proton_mc).M());
            Fill(Form("resolution_lp_momtrans_meas_%s",meas[i_meas].data()),(lv_lambda_mc+lv_proton_mc).P(),( (lv_lambda_mc+lv_proton_mc).P()-(lv_lambda_meas+lv_proton_meas).P() )/(lv_lambda_mc+lv_proton_mc).P());
            Fill(Form("resolution_ln_mass_meas_%s",meas[i_meas].data()),(lv_lambda_mc+lv_neutron_mc).M(),( (lv_lambda_mc+lv_neutron_mc).M()-(lv_lambda_meas+lv_neutron_meas).M() )/(lv_lambda_mc+lv_neutron_mc).M());
            Fill(Form("resolution_ln_momtrans_meas_%s",meas[i_meas].data()),(lv_lambda_mc+lv_neutron_mc).P(),( (lv_lambda_mc+lv_neutron_mc).P()-(lv_lambda_meas+lv_neutron_meas).P() )/(lv_lambda_mc+lv_neutron_mc).P());

            // covariance
            Fill(Form("covariance_beam_px_meas_%s",meas[i_meas].data()),lv_beam_meas.P(),(lv_beam_mc.Px()-lv_beam_meas.Px())/lv_beam_meas.P());
            Fill(Form("covariance_lambda_px_meas_%s",meas[i_meas].data()),lv_lambda_meas.P(),(lv_lambda_mc.Px()-lv_lambda_meas.Px())/lv_lambda_meas.P());
            Fill(Form("covariance_proton_px_meas_%s",meas[i_meas].data()),lv_proton_meas.P(),(lv_proton_mc.Px()-lv_proton_meas.Px())/lv_proton_meas.P());
            Fill(Form("covariance_neutron_px_meas_%s",meas[i_meas].data()),lv_neutron_meas.P(),(lv_neutron_mc.Px()-lv_neutron_meas.Px())/lv_neutron_meas.P());
            Fill(Form("covariance_pi_from_lambda_px_meas_%s",meas[i_meas].data()),lv_pi_from_lambda_meas.P(),(lv_pi_from_lambda_mc.Px()-lv_pi_from_lambda_meas.Px())/lv_pi_from_lambda_meas.P());
            Fill(Form("covariance_nucleon_from_lambda_px_meas_%s",meas[i_meas].data()),lv_nucleon_from_lambda_meas.P(),(lv_nucleon_from_lambda_mc.Px()-lv_nucleon_from_lambda_meas.Px())/lv_nucleon_from_lambda_meas.P());

            Fill(Form("covariance_beam_py_meas_%s",meas[i_meas].data()),lv_beam_meas.P(),(lv_beam_mc.Py()-lv_beam_meas.Py())/lv_beam_meas.P());
            Fill(Form("covariance_lambda_py_meas_%s",meas[i_meas].data()),lv_lambda_meas.P(),(lv_lambda_mc.Py()-lv_lambda_meas.Py())/lv_lambda_meas.P());
            Fill(Form("covariance_proton_py_meas_%s",meas[i_meas].data()),lv_proton_meas.P(),(lv_proton_mc.Py()-lv_proton_meas.Py())/lv_proton_meas.P());
            Fill(Form("covariance_neutron_py_meas_%s",meas[i_meas].data()),lv_neutron_meas.P(),(lv_neutron_mc.Py()-lv_neutron_meas.Py())/lv_neutron_meas.P());
            Fill(Form("covariance_pi_from_lambda_py_meas_%s",meas[i_meas].data()),lv_pi_from_lambda_meas.P(),(lv_pi_from_lambda_mc.Py()-lv_pi_from_lambda_meas.Py())/lv_pi_from_lambda_meas.P());
            Fill(Form("covariance_nucleon_from_lambda_py_meas_%s",meas[i_meas].data()),lv_nucleon_from_lambda_meas.P(),(lv_nucleon_from_lambda_mc.Py()-lv_nucleon_from_lambda_meas.Py())/lv_nucleon_from_lambda_meas.P());

            Fill(Form("covariance_beam_pz_meas_%s",meas[i_meas].data()),lv_beam_meas.P(),(lv_beam_mc.Pz()-lv_beam_meas.Pz())/lv_beam_meas.P());
            Fill(Form("covariance_lambda_pz_meas_%s",meas[i_meas].data()),lv_lambda_meas.P(),(lv_lambda_mc.Pz()-lv_lambda_meas.Pz())/lv_lambda_meas.P());
            Fill(Form("covariance_proton_pz_meas_%s",meas[i_meas].data()),lv_proton_meas.P(),(lv_proton_mc.Pz()-lv_proton_meas.Pz())/lv_proton_meas.P());
            Fill(Form("covariance_neutron_pz_meas_%s",meas[i_meas].data()),lv_neutron_meas.P(),(lv_neutron_mc.Pz()-lv_neutron_meas.Pz())/lv_neutron_meas.P());
            Fill(Form("covariance_pi_from_lambda_pz_meas_%s",meas[i_meas].data()),lv_pi_from_lambda_meas.P(),(lv_pi_from_lambda_mc.Pz()-lv_pi_from_lambda_meas.Pz())/lv_pi_from_lambda_meas.P());
            Fill(Form("covariance_nucleon_from_lambda_pz_meas_%s",meas[i_meas].data()),lv_nucleon_from_lambda_meas.P(),(lv_nucleon_from_lambda_mc.Pz()-lv_nucleon_from_lambda_meas.Pz())/lv_nucleon_from_lambda_meas.P());

            // kfit -----
            Fill(Form("beam_momentum_lab_kfit_%s",meas[i_meas].data()),lv_beam_kfit.P());
            Fill(Form("lambda_momentum_lab_kfit_%s",meas[i_meas].data()),lv_lambda_kfit.P());
            Fill(Form("proton_momentum_lab_kfit_%s",meas[i_meas].data()),lv_proton_kfit.P());
            Fill(Form("neutron_momentum_lab_kfit_%s",meas[i_meas].data()),lv_neutron_kfit.P());
            Fill(Form("pi_from_lambda_momentum_lab_kfit_%s",meas[i_meas].data()),lv_pi_from_lambda_kfit.P());
            Fill(Form("nucleon_from_lambda_momentum_lab_kfit_%s",meas[i_meas].data()),lv_nucleon_from_lambda_kfit.P());
            Fill(Form("lambda_mass_kfit_%s",meas[i_meas].data()),lv_lambda_kfit.M());
            Fill(Form("proton_mass_kfit_%s",meas[i_meas].data()),lv_proton_kfit.M());
            Fill(Form("neutron_mass_kfit_%s",meas[i_meas].data()),lv_neutron_kfit.M());
            Fill(Form("lp_mass_kfit_%s",meas[i_meas].data()),(lv_lambda_kfit+lv_proton_kfit).M());
            Fill(Form("lp_momtrans_kfit_%s",meas[i_meas].data()),(lv_lambda_kfit+lv_proton_kfit).P());
            Fill(Form("ln_mass_kfit_%s",meas[i_meas].data()),(lv_lambda_kfit+lv_neutron_kfit).M());
            Fill(Form("ln_momtrans_kfit_%s",meas[i_meas].data()),(lv_lambda_kfit+lv_neutron_kfit).P());

            Fill(Form("beam_cos_theta_vs_phi_lab_kfit_%s",meas[i_meas].data()),lv_beam_kfit.CosTheta(),lv_beam_kfit.Phi());
            Fill(Form("lambda_cos_theta_vs_phi_lab_kfit_%s",meas[i_meas].data()),lv_lambda_kfit.CosTheta(),lv_lambda_kfit.Phi());
            Fill(Form("proton_cos_theta_vs_phi_lab_kfit_%s",meas[i_meas].data()),lv_proton_kfit.CosTheta(),lv_proton_kfit.Phi());
            Fill(Form("neutron_cos_theta_vs_phi_lab_kfit_%s",meas[i_meas].data()),lv_neutron_kfit.CosTheta(),lv_neutron_kfit.Phi());
            Fill(Form("pi_from_lambda_cos_theta_vs_phi_lab_kfit_%s",meas[i_meas].data()),lv_pi_from_lambda_kfit.CosTheta(),lv_pi_from_lambda_kfit.Phi());
            Fill(Form("nucleon_from_lambda_cos_theta_vs_phi_lab_kfit_%s",meas[i_meas].data()),lv_nucleon_from_lambda_kfit.CosTheta(),lv_nucleon_from_lambda_kfit.Phi());
            Fill(Form("reduced_chisquare_kfit_%s",meas[i_meas].data()),reduced_chisquare_kfit);

            Fill(Form("lp_mass_vs_momtrans_kfit_%s",meas[i_meas].data()),(lv_lambda_kfit+lv_proton_kfit).M(),(lv_lambda_kfit+lv_proton_kfit).P());
            Fill(Form("ln_mass_vs_momtrans_kfit_%s",meas[i_meas].data()),(lv_lambda_kfit+lv_neutron_kfit).M(),(lv_lambda_kfit+lv_neutron_kfit).P());

            Fill(Form("neutron_momentum_lab_vs_lambda_momentum_lab_kfit_%s",meas[i_meas].data()),lv_neutron_kfit.P(),lv_lambda_kfit.P());
            Fill(Form("neutron_cos_theta_lab_vs_lambda_cos_theta_lab_kfit_%s",meas[i_meas].data()),lv_neutron_kfit.CosTheta(),lv_lambda_kfit.CosTheta());

            // resolutions
            Fill(Form("resolution_beam_momentum_kfit_%s",meas[i_meas].data()),lv_beam_mc.P(),(lv_beam_mc.P()-lv_beam_kfit.P())/lv_beam_mc.P());
            Fill(Form("resolution_lambda_momentum_kfit_%s",meas[i_meas].data()),lv_lambda_mc.P(),(lv_lambda_mc.P()-lv_lambda_kfit.P())/lv_lambda_mc.P());
            Fill(Form("resolution_proton_momentum_kfit_%s",meas[i_meas].data()),lv_proton_mc.P(),(lv_proton_mc.P()-lv_proton_kfit.P())/lv_proton_mc.P());
            Fill(Form("resolution_neutron_momentum_kfit_%s",meas[i_meas].data()),lv_neutron_mc.P(),(lv_neutron_mc.P()-lv_neutron_kfit.P())/lv_neutron_mc.P());
            Fill(Form("resolution_pi_from_lambda_momentum_kfit_%s",meas[i_meas].data()),lv_pi_from_lambda_mc.P(),(lv_pi_from_lambda_mc.P()-lv_pi_from_lambda_kfit.P())/lv_pi_from_lambda_mc.P());
            Fill(Form("resolution_nucleon_from_lambda_momentum_kfit_%s",meas[i_meas].data()),lv_nucleon_from_lambda_mc.P(),(lv_nucleon_from_lambda_mc.P()-lv_nucleon_from_lambda_kfit.P())/lv_nucleon_from_lambda_mc.P());

            Fill(Form("resolution_lp_mass_kfit_%s",meas[i_meas].data()),(lv_lambda_mc+lv_proton_mc).M(),( (lv_lambda_mc+lv_proton_mc).M()-(lv_lambda_kfit+lv_proton_kfit).M() )/(lv_lambda_mc+lv_proton_mc).M());
            Fill(Form("resolution_lp_momtrans_kfit_%s",meas[i_meas].data()),(lv_lambda_mc+lv_proton_mc).P(),( (lv_lambda_mc+lv_proton_mc).P()-(lv_lambda_kfit+lv_proton_kfit).P() )/(lv_lambda_mc+lv_proton_mc).P());
            Fill(Form("resolution_ln_mass_kfit_%s",meas[i_meas].data()),(lv_lambda_mc+lv_neutron_mc).M(),( (lv_lambda_mc+lv_neutron_mc).M()-(lv_lambda_kfit+lv_neutron_kfit).M() )/(lv_lambda_mc+lv_neutron_mc).M());
            Fill(Form("resolution_ln_momtrans_kfit_%s",meas[i_meas].data()),(lv_lambda_mc+lv_neutron_mc).P(),( (lv_lambda_mc+lv_neutron_mc).P()-(lv_lambda_kfit+lv_neutron_kfit).P() )/(lv_lambda_mc+lv_neutron_mc).P());

            // covariance
            Fill(Form("covariance_beam_px_kfit_%s",meas[i_meas].data()),lv_beam_kfit.P(),(lv_beam_mc.Px()-lv_beam_kfit.Px())/lv_beam_kfit.P());
            Fill(Form("covariance_lambda_px_kfit_%s",meas[i_meas].data()),lv_lambda_kfit.P(),(lv_lambda_mc.Px()-lv_lambda_kfit.Px())/lv_lambda_kfit.P());
            Fill(Form("covariance_proton_px_kfit_%s",meas[i_meas].data()),lv_proton_kfit.P(),(lv_proton_mc.Px()-lv_proton_kfit.Px())/lv_proton_kfit.P());
            Fill(Form("covariance_neutron_px_kfit_%s",meas[i_meas].data()),lv_neutron_kfit.P(),(lv_neutron_mc.Px()-lv_neutron_kfit.Px())/lv_neutron_kfit.P());
            Fill(Form("covariance_pi_from_lambda_px_kfit_%s",meas[i_meas].data()),lv_pi_from_lambda_kfit.P(),(lv_pi_from_lambda_mc.Px()-lv_pi_from_lambda_kfit.Px())/lv_pi_from_lambda_kfit.P());
            Fill(Form("covariance_nucleon_from_lambda_px_kfit_%s",meas[i_meas].data()),lv_nucleon_from_lambda_kfit.P(),(lv_nucleon_from_lambda_mc.Px()-lv_nucleon_from_lambda_kfit.Px())/lv_nucleon_from_lambda_kfit.P());

            Fill(Form("covariance_beam_py_kfit_%s",meas[i_meas].data()),lv_beam_kfit.P(),(lv_beam_mc.Py()-lv_beam_kfit.Py())/lv_beam_kfit.P());
            Fill(Form("covariance_lambda_py_kfit_%s",meas[i_meas].data()),lv_lambda_kfit.P(),(lv_lambda_mc.Py()-lv_lambda_kfit.Py())/lv_lambda_kfit.P());
            Fill(Form("covariance_proton_py_kfit_%s",meas[i_meas].data()),lv_proton_kfit.P(),(lv_proton_mc.Py()-lv_proton_kfit.Py())/lv_proton_kfit.P());
            Fill(Form("covariance_neutron_py_kfit_%s",meas[i_meas].data()),lv_neutron_kfit.P(),(lv_neutron_mc.Py()-lv_neutron_kfit.Py())/lv_neutron_kfit.P());
            Fill(Form("covariance_pi_from_lambda_py_kfit_%s",meas[i_meas].data()),lv_pi_from_lambda_kfit.P(),(lv_pi_from_lambda_mc.Py()-lv_pi_from_lambda_kfit.Py())/lv_pi_from_lambda_kfit.P());
            Fill(Form("covariance_nucleon_from_lambda_py_kfit_%s",meas[i_meas].data()),lv_nucleon_from_lambda_kfit.P(),(lv_nucleon_from_lambda_mc.Py()-lv_nucleon_from_lambda_kfit.Py())/lv_nucleon_from_lambda_kfit.P());

            Fill(Form("covariance_beam_pz_kfit_%s",meas[i_meas].data()),lv_beam_kfit.P(),(lv_beam_mc.Pz()-lv_beam_kfit.Pz())/lv_beam_kfit.P());
            Fill(Form("covariance_lambda_pz_kfit_%s",meas[i_meas].data()),lv_lambda_kfit.P(),(lv_lambda_mc.Pz()-lv_lambda_kfit.Pz())/lv_lambda_kfit.P());
            Fill(Form("covariance_proton_pz_kfit_%s",meas[i_meas].data()),lv_proton_kfit.P(),(lv_proton_mc.Pz()-lv_proton_kfit.Pz())/lv_proton_kfit.P());
            Fill(Form("covariance_neutron_pz_kfit_%s",meas[i_meas].data()),lv_neutron_kfit.P(),(lv_neutron_mc.Pz()-lv_neutron_kfit.Pz())/lv_neutron_kfit.P());
            Fill(Form("covariance_pi_from_lambda_pz_kfit_%s",meas[i_meas].data()),lv_pi_from_lambda_kfit.P(),(lv_pi_from_lambda_mc.Pz()-lv_pi_from_lambda_kfit.Pz())/lv_pi_from_lambda_kfit.P());
            Fill(Form("covariance_nucleon_from_lambda_pz_kfit_%s",meas[i_meas].data()),lv_nucleon_from_lambda_kfit.P(),(lv_nucleon_from_lambda_mc.Pz()-lv_nucleon_from_lambda_kfit.Pz())/lv_nucleon_from_lambda_kfit.P());

        }
    }

    // ============================================================================================
    // FILLING HISTOGRAMS =========================================================================
    // ============================================================================================

    return;
}

void AnalyzerLpn::PrintHistogram(std::string file_name){
    if(file_name!=""){
        _pdf_file_name = file_name;
        _pdf_file_name = _pdf_file_name.substr(0,_pdf_file_name.find_last_of("."));
        _pdf_file_name.append("_lpn.pdf");
    }
    TCanvas* tmp_canvas = new TCanvas("tmp_canvas","canvas",3200,1800);
    tmp_canvas->Draw();
    tmp_canvas->Print(std::string(_pdf_file_name+"[").data());


    std::vector<std::string> meas_type;
    meas_type.push_back("gene");
    meas_type.push_back("acce_lp");
    meas_type.push_back("meas_lp");
    meas_type.push_back("kfit_lp");
    //meas_type.push_back("acce_ln");
    //meas_type.push_back("meas_ln");
    //meas_type.push_back("kfit_ln");
    meas_type.push_back("acce_ln_true");
    meas_type.push_back("meas_ln_true");
    meas_type.push_back("kfit_ln_true");
    //meas_type.push_back("acce_ln_fake");
    //meas_type.push_back("meas_ln_fake");
    //meas_type.push_back("kfit_ln_fake");
    //meas_type.push_back("acce_lpn");
    //meas_type.push_back("meas_lpn");
    //meas_type.push_back("kfit_lpn");
    //meas_type.push_back("acce_lpn_true");
    //meas_type.push_back("meas_lpn_true");
    //meas_type.push_back("kfit_lpn_true");
    //meas_type.push_back("acce_lpn_fake");
    //meas_type.push_back("meas_lpn_fake");
    //meas_type.push_back("kfit_lpn_fake");


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
        print_th1_names.push_back("lambda_momentum_lab_"+meas_type[i_meas]);
        print_th1_names.push_back("proton_momentum_lab_"+meas_type[i_meas]);
        print_th1_names.push_back("neutron_momentum_lab_"+meas_type[i_meas]);
        print_th1_names.push_back("pi_from_lambda_momentum_lab_"+meas_type[i_meas]);
        print_th1_names.push_back("nucleon_from_lambda_momentum_lab_"+meas_type[i_meas]);
        // --
        print_th1_names.push_back("lambda_mass_"+meas_type[i_meas]);
        print_th1_names.push_back("proton_mass_"+meas_type[i_meas]);
        print_th1_names.push_back("neutron_mass_"+meas_type[i_meas]);
        print_th1_names.push_back("");
        print_th1_names.push_back("");
        print_th1_names.push_back("");
        // --
        print_th1_names.push_back("lp_mass_"+meas_type[i_meas]);
        print_th1_names.push_back("lp_momtrans_"+meas_type[i_meas]);
        print_th1_names.push_back("");
        print_th1_names.push_back("ln_mass_"+meas_type[i_meas]);
        print_th1_names.push_back("ln_momtrans_"+meas_type[i_meas]);
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
        print_th1_names.push_back("proton_flight_time_"+meas_type[i_meas]);
        print_th1_names.push_back("lambda_flight_time_"+meas_type[i_meas]);
        print_th1_names.push_back("");
        print_th1_names.push_back("reference_axis_sin_theta_"+meas_type[i_meas]);
        print_th1_names.push_back("reference_axis_sin_phi_"+meas_type[i_meas]);
        print_th1_names.push_back("");
        // --
        print_th2_names.push_back("");
        print_th1_names.push_back("lambda_momentum_lab_reference_axis_selected_"+meas_type[i_meas]);
        print_th1_names.push_back("proton_momentum_lab_reference_axis_selected_"+meas_type[i_meas]);
        print_th1_names.push_back("neutron_momentum_lab_reference_axis_selected_"+meas_type[i_meas]);
        print_th1_names.push_back("pi_from_lambda_momentum_lab_reference_axis_selected_"+meas_type[i_meas]);
        print_th1_names.push_back("nucleon_from_lambda_momentum_lab_reference_axis_selected_"+meas_type[i_meas]);
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
        print_th2_names.push_back("lambda_cos_theta_vs_phi_lab_"+meas_type[i_meas]);
        print_th2_names.push_back("proton_cos_theta_vs_phi_lab_"+meas_type[i_meas]);
        print_th2_names.push_back("neutron_cos_theta_vs_phi_lab_"+meas_type[i_meas]);
        print_th2_names.push_back("pi_from_lambda_cos_theta_vs_phi_lab_"+meas_type[i_meas]);
        print_th2_names.push_back("nucleon_from_lambda_cos_theta_vs_phi_lab_"+meas_type[i_meas]);
        // --
        print_th2_names.push_back("nucleon_from_lambda_cos_theta_vs_phi_lambda_rest_"+meas_type[i_meas]);
        print_th2_names.push_back("proton_theta_vs_phi_against_to_chc_"+meas_type[i_meas]);
        print_th2_names.push_back("proton_theta_vs_phi_against_to_chc_in_deg_"+meas_type[i_meas]);
        print_th2_names.push_back("reference_axis_sin_theta_vs_phi_"+meas_type[i_meas]);
        print_th2_names.push_back("reference_axis_sin_theta_vs_sin_phi_"+meas_type[i_meas]);
        print_th2_names.push_back("");
        // --
        print_th2_names.push_back("nucleon_from_lambda_cos_theta_vs_phi_lambda_rest_reference_axis_selected_"+meas_type[i_meas]);
        print_th2_names.push_back("proton_theta_vs_phi_against_to_chc_reference_axis_selected_"+meas_type[i_meas]);
        print_th2_names.push_back("proton_theta_vs_phi_against_to_chc_in_deg_reference_axis_selected_"+meas_type[i_meas]);
        print_th2_names.push_back("reference_axis_sin_theta_vs_phi_reference_axis_selected_"+meas_type[i_meas]);
        print_th2_names.push_back("reference_axis_sin_theta_vs_sin_phi_reference_axis_selected_"+meas_type[i_meas]);
        print_th2_names.push_back("");
        // --
        print_th2_names.push_back("");
        print_th2_names.push_back("lambda_cos_theta_vs_phi_lab_reference_axis_selected_"+meas_type[i_meas]);
        print_th2_names.push_back("proton_cos_theta_vs_phi_lab_reference_axis_selected_"+meas_type[i_meas]);
        print_th2_names.push_back("neutron_cos_theta_vs_phi_lab_reference_axis_selected_"+meas_type[i_meas]);
        print_th2_names.push_back("pi_from_lambda_cos_theta_vs_phi_lab_reference_axis_selected_"+meas_type[i_meas]);
        print_th2_names.push_back("nucleon_from_lambda_cos_theta_vs_phi_lab_reference_axis_selected_"+meas_type[i_meas]);
        // --
        print_th2_names.push_back("lp_mass_vs_momtrans_"+meas_type[i_meas]);
        print_th2_names.push_back("ln_mass_vs_momtrans_"+meas_type[i_meas]);
        print_th2_names.push_back("");
        print_th2_names.push_back("lp_mass_vs_momtrans_reference_axis_selected_"+meas_type[i_meas]);
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        // --
        print_th2_names.push_back("neutron_momentum_lab_vs_lambda_momentum_lab_"+meas_type[i_meas]);
        print_th2_names.push_back("neutron_cos_theta_lab_vs_lambda_cos_theta_lab_"+meas_type[i_meas]);
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
        // --
        th2_slice = "resolution_lp_mass_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        // --
        th2_slice = "resolution_lp_momtrans_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        // --
        th2_slice = "resolution_ln_mass_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        // --
        th2_slice = "resolution_ln_momtrans_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        // --
        continue;
        // covariance
        // --
        // beam
        th2_slice = "covariance_beam_px_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        th2_slice = "covariance_beam_py_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        th2_slice = "covariance_beam_pz_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        // --
        // lambda
        th2_slice = "covariance_lambda_px_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        th2_slice = "covariance_lambda_py_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        th2_slice = "covariance_lambda_pz_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        // --
        // proton
        th2_slice = "covariance_proton_px_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        th2_slice = "covariance_proton_py_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        th2_slice = "covariance_proton_pz_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        // --
        // neutron
        th2_slice = "covariance_neutron_px_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        th2_slice = "covariance_neutron_py_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        th2_slice = "covariance_neutron_pz_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        // --
        // pi_from_lambda
        th2_slice = "covariance_pi_from_lambda_px_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        th2_slice = "covariance_pi_from_lambda_py_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        th2_slice = "covariance_pi_from_lambda_pz_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        // --
        // nucleon_from_lambda
        th2_slice = "covariance_nucleon_from_lambda_px_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        th2_slice = "covariance_nucleon_from_lambda_py_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        th2_slice = "covariance_nucleon_from_lambda_pz_"+meas_type[i_meas];
        Print2DSlice(th2_slice,kXSlice,0);
        // --
    }


    // 1D histograms to be drawn
    print_th1_names.clear();
    // --
    print_th1_names.push_back("neutral_number_of_hits");
    print_th1_names.push_back("");
    print_th1_names.push_back("");
    print_th1_names.push_back("");
    print_th1_names.push_back("");
    print_th1_names.push_back("");
    // --
    // 1D histograms drawn logarithmic
    log_th1_names.clear();
    // --
    log_th1_names.push_back("neutral_over_beta_vs_energy_deposit_meas");
    // --
    Print(print_th1_names,log_th1_names,k2D);

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
    th1_names.push_back("proton_mass_meas_ln");
    line_colors.push_back(kBlack);
    legend_names.push_back("all");
    th1_names.push_back("proton_mass_meas_ln_fake");
    line_colors.push_back(kBlue-4);
    legend_names.push_back("fake");
    PrintSame(th1_names,line_colors,legend_names);

    // For acceptance
    // On the 2D plot of Lp system
    std::vector<std::string> gene_names;
    gene_names.push_back("lp_mass_vs_momtrans_gene");
    gene_names.push_back("ln_mass_vs_momtrans_gene");
    std::vector<std::string> acce_names;
    acce_names.push_back("lp_mass_vs_momtrans_acce_lp");
    acce_names.push_back("ln_mass_vs_momtrans_acce_lp");
    Double_t maximum = 15.;
    PrintAcceptance(gene_names,acce_names,maximum);
    acce_names.clear();
    acce_names.push_back("lp_mass_vs_momtrans_acce_ln_true");
    acce_names.push_back("ln_mass_vs_momtrans_acce_ln_true");
    maximum = 1.5;
    PrintAcceptance(gene_names,acce_names,maximum);
    acce_names.clear();
    acce_names.push_back("lp_mass_vs_momtrans_acce_lpn_true");
    acce_names.push_back("ln_mass_vs_momtrans_acce_lpn_true");
    maximum = 1.5;
    PrintAcceptance(gene_names,acce_names,maximum);

    tmp_canvas->Print(std::string(_pdf_file_name+"]").data());
    delete tmp_canvas;

}
