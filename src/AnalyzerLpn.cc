// AnalyzerLpn.cc
#include"AnalyzerLpn.hh"

//#define USE_CAP

AnalyzerLpn::AnalyzerLpn()
{
    _is_created = false;
    _root_file_name = "tmp.root";
    _pdf_file_name = _root_file_name.substr(_root_file_name.find_last_of("/"),_root_file_name.find_first_of("."));
    _pdf_file_name.append(".pdf");
    _pdf_file_name.insert(0,"./fig/tmp");
    CreateRootFile("recreate");
    random = new TRandom3(0);

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

AnalyzerLpn::AnalyzerLpn(std::string file_name, std::string option)
{
    _is_created = false;
    _root_file_name = file_name;
    _pdf_file_name = _root_file_name.substr(_root_file_name.find_last_of("/"),_root_file_name.find_last_of(".")-_root_file_name.find_last_of("/"));
    _pdf_file_name.append(".pdf");
    _pdf_file_name.insert(0,"./fig/tmp");
    CreateRootFile(option);
    random = new TRandom3(0);

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

AnalyzerLpn::~AnalyzerLpn()
{
    if(_root_file){
        if(_is_created){
            _root_file->Write();
        }
        _root_file->Close();
    }
    delete random;
    delete pdg;
}
void AnalyzerLpn::CreateRootFile(std::string option)
{
    _meas_type.push_back("gene");
    _meas_type.push_back("acce_lp");
    _meas_type.push_back("meas_lp");
    _meas_type.push_back("acce_ln");
    _meas_type.push_back("meas_ln");
    _meas_type.push_back("acce_ln_true");
    _meas_type.push_back("meas_ln_true");
    _meas_type.push_back("acce_ln_fake");
    _meas_type.push_back("meas_ln_fake");
    _meas_type.push_back("acce_lpn");
    _meas_type.push_back("meas_lpn");
    _meas_type.push_back("acce_lpn_true");
    _meas_type.push_back("meas_lpn_true");
    _meas_type.push_back("acce_lpn_fake");
    _meas_type.push_back("meas_lpn_fake");

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
        // 1D histograms ------------------------------------------------------------------------------


        // 2D histograms ------------------------------------------------------------------------------
        new TH2F(Form("beam_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of K^{-}-beam (lab. frame);cos#theta_{K^{-}}^{lab};#phi_{K^{-}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("lambda_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of #Lambda (lab. frame);cos#theta_{#Lambda}^{lab};#phi_{#Lambda}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("proton_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of proton (lab. frame);cos#theta_{#font[12]{p}}^{lab};#phi_{#font[12]{p}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("neutron_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of neutron (lab. frame);cos#theta_{#font[12]{n}}^{lab};#phi_{#font[12]{n}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("pi_from_lambda_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of pi_from_lambda (lab. frame);cos#theta_{#pi from #Lambda}^{lab};#phi_{#font[12]{n}}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());
        new TH2F(Form("nucleon_from_lambda_cos_theta_vs_phi_lab_%s",_meas_type[i_type].data()),"cos#theta vs. phi of nucleon_from_lambda (lab. frame);cos#theta_{#font[12]{N} from #Lambda}^{lab};#phi_{#font[12]{N} from #Lambda}^{lab}", 50,-1.,1.,50,-TMath::Pi(),TMath::Pi());

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
        // 2D histograms ------------------------------------------------------------------------------

    }

    // for neutral detection
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
        }
        else if(pdg_id==2212){ // proton
            lv_proton_mc.SetVectM(track->momentum()*0.001,kProtonMass);
        }
        else if(pdg_id==2112){ // neutron
            lv_neutron_mc.SetVectM(track->momentum()*0.001,kNeutronMass);
        }
    }

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

    //if(measured_neutral_generation!=1){
    //    is_accepted_ln_true = false;
    //    if(is_accepted_ln){
    //        is_accepted_ln_fake = true;
    //    }
    //    is_accepted_lpn_true = false;
    //    if(is_accepted_lpn){
    //        is_accepted_lpn_fake = true;
    //    }
    //}
    // ============================================================================================
    // ============================================================================================
    // ============================================================================================


    // ============================================================================================
    // FILLING HISTOGRAMS =========================================================================
    // ============================================================================================
    Fill("beam_momentum_lab_gene",lv_beam_mc.Vect().Mag());
    Fill("lambda_momentum_lab_gene",lv_lambda_mc.Vect().Mag());
    Fill("proton_momentum_lab_gene",lv_proton_mc.Vect().Mag());
    Fill("neutron_momentum_lab_gene",lv_neutron_mc.Vect().Mag());
    Fill("pi_from_lambda_momentum_lab_gene",lv_pi_from_lambda_mc.Vect().Mag());
    Fill("nucleon_from_lambda_momentum_lab_gene",lv_nucleon_from_lambda_mc.Vect().Mag());
    Fill("lambda_mass_gene",lv_lambda_mc.M());
    Fill("proton_mass_gene",lv_proton_mc.M());
    Fill("neutron_mass_gene",lv_neutron_mc.M());
    Fill("lp_mass_gene",(lv_lambda_mc+lv_proton_mc).M());
    Fill("lp_momtrans_gene",(lv_lambda_mc+lv_proton_mc).Vect().Mag());
    Fill("ln_mass_gene",(lv_lambda_mc+lv_neutron_mc).M());
    Fill("ln_momtrans_gene",(lv_lambda_mc+lv_neutron_mc).Vect().Mag());

    Fill("beam_cos_theta_vs_phi_lab_gene",lv_beam_mc.Vect().CosTheta(),lv_beam_mc.Vect().Phi());
    Fill("lambda_cos_theta_vs_phi_lab_gene",lv_lambda_mc.Vect().CosTheta(),lv_lambda_mc.Vect().Phi());
    Fill("proton_cos_theta_vs_phi_lab_gene",lv_proton_mc.Vect().CosTheta(),lv_proton_mc.Vect().Phi());
    Fill("neutron_cos_theta_vs_phi_lab_gene",lv_neutron_mc.Vect().CosTheta(),lv_neutron_mc.Vect().Phi());
    Fill("pi_from_lambda_cos_theta_vs_phi_lab_gene",lv_pi_from_lambda_mc.Vect().CosTheta(),lv_pi_from_lambda_mc.Vect().Phi());
    Fill("nucleon_from_lambda_cos_theta_vs_phi_lab_gene",lv_nucleon_from_lambda_mc.Vect().CosTheta(),lv_nucleon_from_lambda_mc.Vect().Phi());

    Fill("lp_mass_vs_momtrans_gene",(lv_lambda_mc+lv_proton_mc).M(),(lv_lambda_mc+lv_proton_mc).Vect().Mag());
    Fill("ln_mass_vs_momtrans_gene",(lv_lambda_mc+lv_proton_mc).M(),(lv_lambda_mc+lv_proton_mc).Vect().Mag());

    Fill("neutron_momentum_lab_vs_lambda_momentum_lab_gene",lv_neutron_mc.Vect().Mag(),lv_lambda_mc.Vect().Mag());
    Fill("neutron_cos_theta_lab_vs_lambda_cos_theta_lab_gene",lv_neutron_mc.Vect().CosTheta(),lv_lambda_mc.Vect().CosTheta());

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
                break;
            case 1: // Ln detection
                lv_proton_meas = lv_missing_proton_meas;
                lv_neutron_meas = lv_detected_neutron_meas;
                break;
            case 2: // Ln detection (TRUE)
                lv_proton_meas = lv_missing_proton_meas;
                lv_neutron_meas = lv_detected_neutron_meas;
                break;
            case 3: // Ln detection (FAKE)
                lv_proton_meas = lv_missing_proton_meas;
                lv_neutron_meas = lv_detected_neutron_meas;
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
            Fill(Form("beam_momentum_lab_acce_%s",meas[i_meas].data()),lv_beam_mc.Vect().Mag());
            Fill(Form("lambda_momentum_lab_acce_%s",meas[i_meas].data()),lv_lambda_mc.Vect().Mag());
            Fill(Form("proton_momentum_lab_acce_%s",meas[i_meas].data()),lv_proton_mc.Vect().Mag());
            Fill(Form("neutron_momentum_lab_acce_%s",meas[i_meas].data()),lv_neutron_mc.Vect().Mag());
            Fill(Form("pi_from_lambda_momentum_lab_acce_%s",meas[i_meas].data()),lv_pi_from_lambda_mc.Vect().Mag());
            Fill(Form("nucleon_from_lambda_momentum_lab_acce_%s",meas[i_meas].data()),lv_nucleon_from_lambda_mc.Vect().Mag());
            Fill(Form("lambda_mass_acce_%s",meas[i_meas].data()),lv_lambda_mc.M());
            Fill(Form("proton_mass_acce_%s",meas[i_meas].data()),lv_proton_mc.M());
            Fill(Form("neutron_mass_acce_%s",meas[i_meas].data()),lv_neutron_mc.M());
            Fill(Form("lp_mass_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_proton_mc).M());
            Fill(Form("lp_momtrans_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_proton_mc).Vect().Mag());
            Fill(Form("ln_mass_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_neutron_mc).M());
            Fill(Form("ln_momtrans_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_neutron_mc).Vect().Mag());

            Fill(Form("beam_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_beam_mc.Vect().CosTheta(),lv_beam_mc.Vect().Phi());
            Fill(Form("lambda_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_lambda_mc.Vect().CosTheta(),lv_lambda_mc.Vect().Phi());
            Fill(Form("proton_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_proton_mc.Vect().CosTheta(),lv_proton_mc.Vect().Phi());
            Fill(Form("neutron_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_neutron_mc.Vect().CosTheta(),lv_neutron_mc.Vect().Phi());
            Fill(Form("pi_from_lambda_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_pi_from_lambda_mc.Vect().CosTheta(),lv_pi_from_lambda_mc.Vect().Phi());
            Fill(Form("nucleon_from_lambda_cos_theta_vs_phi_lab_acce_%s",meas[i_meas].data()),lv_nucleon_from_lambda_mc.Vect().CosTheta(),lv_nucleon_from_lambda_mc.Vect().Phi());
            Fill(Form("beam_momentum_lab_acce_%s",meas[i_meas].data()),lv_beam_mc.Vect().Mag());

            Fill(Form("lp_mass_vs_momtrans_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_proton_mc).M(),(lv_lambda_mc+lv_proton_mc).Vect().Mag());
            Fill(Form("ln_mass_vs_momtrans_acce_%s",meas[i_meas].data()),(lv_lambda_mc+lv_neutron_mc).M(),(lv_lambda_mc+lv_neutron_mc).Vect().Mag());

            Fill(Form("neutron_momentum_lab_vs_lambda_momentum_lab_acce_%s",meas[i_meas].data()),lv_neutron_mc.Vect().Mag(),lv_lambda_mc.Vect().Mag());
            Fill(Form("neutron_cos_theta_lab_vs_lambda_cos_theta_lab_acce_%s",meas[i_meas].data()),lv_neutron_mc.Vect().CosTheta(),lv_lambda_mc.Vect().CosTheta());

            Fill(Form("beam_momentum_lab_meas_%s",meas[i_meas].data()),lv_beam_meas.Vect().Mag());
            Fill(Form("lambda_momentum_lab_meas_%s",meas[i_meas].data()),lv_lambda_meas.Vect().Mag());
            Fill(Form("proton_momentum_lab_meas_%s",meas[i_meas].data()),lv_proton_meas.Vect().Mag());
            Fill(Form("neutron_momentum_lab_meas_%s",meas[i_meas].data()),lv_neutron_meas.Vect().Mag());
            Fill(Form("pi_from_lambda_momentum_lab_meas_%s",meas[i_meas].data()),lv_pi_from_lambda_meas.Vect().Mag());
            Fill(Form("nucleon_from_lambda_momentum_lab_meas_%s",meas[i_meas].data()),lv_nucleon_from_lambda_meas.Vect().Mag());
            Fill(Form("lambda_mass_meas_%s",meas[i_meas].data()),lv_lambda_meas.M());
            Fill(Form("proton_mass_meas_%s",meas[i_meas].data()),lv_proton_meas.M());
            Fill(Form("neutron_mass_meas_%s",meas[i_meas].data()),lv_neutron_meas.M());
            Fill(Form("lp_mass_meas_%s",meas[i_meas].data()),(lv_lambda_meas+lv_proton_meas).M());
            Fill(Form("lp_momtrans_meas_%s",meas[i_meas].data()),(lv_lambda_meas+lv_proton_meas).Vect().Mag());
            Fill(Form("ln_mass_meas_%s",meas[i_meas].data()),(lv_lambda_meas+lv_neutron_meas).M());
            Fill(Form("ln_momtrans_meas_%s",meas[i_meas].data()),(lv_lambda_meas+lv_neutron_meas).Vect().Mag());
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

            Fill(Form("beam_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_beam_meas.Vect().CosTheta(),lv_beam_meas.Vect().Phi());
            Fill(Form("lambda_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_lambda_meas.Vect().CosTheta(),lv_lambda_meas.Vect().Phi());
            Fill(Form("proton_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_proton_meas.Vect().CosTheta(),lv_proton_meas.Vect().Phi());
            Fill(Form("neutron_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_neutron_meas.Vect().CosTheta(),lv_neutron_meas.Vect().Phi());
            Fill(Form("pi_from_lambda_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_pi_from_lambda_meas.Vect().CosTheta(),lv_pi_from_lambda_meas.Vect().Phi());
            Fill(Form("nucleon_from_lambda_cos_theta_vs_phi_lab_meas_%s",meas[i_meas].data()),lv_nucleon_from_lambda_meas.Vect().CosTheta(),lv_nucleon_from_lambda_meas.Vect().Phi());

            Fill(Form("lp_mass_vs_momtrans_meas_%s",meas[i_meas].data()),(lv_lambda_meas+lv_proton_meas).M(),(lv_lambda_meas+lv_proton_meas).Vect().Mag());
            Fill(Form("ln_mass_vs_momtrans_meas_%s",meas[i_meas].data()),(lv_lambda_meas+lv_neutron_meas).M(),(lv_lambda_meas+lv_neutron_meas).Vect().Mag());

            Fill(Form("neutron_momentum_lab_vs_lambda_momentum_lab_meas_%s",meas[i_meas].data()),lv_neutron_meas.Vect().Mag(),lv_lambda_meas.Vect().Mag());
            Fill(Form("neutron_cos_theta_lab_vs_lambda_cos_theta_lab_meas_%s",meas[i_meas].data()),lv_neutron_meas.Vect().CosTheta(),lv_lambda_meas.Vect().CosTheta());

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


    Int_t total_meas_type = _meas_type.size();
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
        text->DrawLatex(0.5,0.5,_meas_type[i_meas].data());
        tmp_canvas->Print(std::string(_pdf_file_name).data());
        // 1D histograms to be drawn
        print_th1_names.clear();
        // --
        print_th1_names.push_back("beam_momentum_lab_"+_meas_type[i_meas]);
        print_th1_names.push_back("lambda_momentum_lab_"+_meas_type[i_meas]);
        print_th1_names.push_back("proton_momentum_lab_"+_meas_type[i_meas]);
        print_th1_names.push_back("neutron_momentum_lab_"+_meas_type[i_meas]);
        print_th1_names.push_back("pi_from_lambda_momentum_lab_"+_meas_type[i_meas]);
        print_th1_names.push_back("nucleon_from_lambda_momentum_lab_"+_meas_type[i_meas]);
        // --
        print_th1_names.push_back("lambda_mass_"+_meas_type[i_meas]);
        print_th1_names.push_back("proton_mass_"+_meas_type[i_meas]);
        print_th1_names.push_back("neutron_mass_"+_meas_type[i_meas]);
        print_th1_names.push_back("");
        print_th1_names.push_back("");
        print_th1_names.push_back("");
        // --
        print_th1_names.push_back("lp_mass_"+_meas_type[i_meas]);
        print_th1_names.push_back("lp_momtrans_"+_meas_type[i_meas]);
        print_th1_names.push_back("");
        print_th1_names.push_back("ln_mass_"+_meas_type[i_meas]);
        print_th1_names.push_back("ln_momtrans_"+_meas_type[i_meas]);
        print_th1_names.push_back("");
        // --
        print_th1_names.push_back("neutral_energy_deposit_"+_meas_type[i_meas]);
        print_th1_names.push_back("neutral_over_beta_"+_meas_type[i_meas]);
        print_th1_names.push_back("neutral_time_"+_meas_type[i_meas]);
        print_th1_names.push_back("neutral_generation_"+_meas_type[i_meas]);
        print_th1_names.push_back("");
        print_th1_names.push_back("");
        // --
        print_th1_names.push_back("neutral_charge_"+_meas_type[i_meas]);
        print_th1_names.push_back("neutral_parent_charge_"+_meas_type[i_meas]);
        print_th1_names.push_back("neutral_grand_parent_charge_"+_meas_type[i_meas]);
        print_th1_names.push_back("neutral_2grand_parent_charge_"+_meas_type[i_meas]);
        print_th1_names.push_back("neutral_3grand_parent_charge_"+_meas_type[i_meas]);
        print_th1_names.push_back("neutral_4grand_parent_charge_"+_meas_type[i_meas]);
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
        print_th2_names.push_back("beam_cos_theta_vs_phi_lab_"+_meas_type[i_meas]);
        print_th2_names.push_back("lambda_cos_theta_vs_phi_lab_"+_meas_type[i_meas]);
        print_th2_names.push_back("proton_cos_theta_vs_phi_lab_"+_meas_type[i_meas]);
        print_th2_names.push_back("neutron_cos_theta_vs_phi_lab_"+_meas_type[i_meas]);
        print_th2_names.push_back("pi_from_lambda_cos_theta_vs_phi_lab_"+_meas_type[i_meas]);
        print_th2_names.push_back("nucleon_from_lambda_cos_theta_vs_phi_lab_"+_meas_type[i_meas]);
        // --
        print_th2_names.push_back("lp_mass_vs_momtrans_"+_meas_type[i_meas]);
        print_th2_names.push_back("ln_mass_vs_momtrans_"+_meas_type[i_meas]);
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        // --
        print_th2_names.push_back("neutron_momentum_lab_vs_lambda_momentum_lab_"+_meas_type[i_meas]);
        print_th2_names.push_back("neutron_cos_theta_lab_vs_lambda_cos_theta_lab_"+_meas_type[i_meas]);
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        print_th2_names.push_back("");
        // --
        print_th2_names.push_back("neutral_generated_position_r_vs_z_"+_meas_type[i_meas]);
        print_th2_names.push_back("neutral_parent_generated_position_r_vs_z_"+_meas_type[i_meas]);
        print_th2_names.push_back("neutral_grand_parent_generated_position_r_vs_z_"+_meas_type[i_meas]);
        print_th2_names.push_back("neutral_2grand_parent_generated_position_r_vs_z_"+_meas_type[i_meas]);
        print_th2_names.push_back("neutral_3grand_parent_generated_position_r_vs_z_"+_meas_type[i_meas]);
        print_th2_names.push_back("neutral_4grand_parent_generated_position_r_vs_z_"+_meas_type[i_meas]);
        // --
        // 2D histograms drawn logarithmic
        log_th2_names.clear();
        // --
        log_th2_names.push_back("neutral_generated_position_r_vs_z_"+_meas_type[i_meas]);
        log_th2_names.push_back("neutral_parent_generated_position_r_vs_z_"+_meas_type[i_meas]);
        log_th2_names.push_back("neutral_grand_parent_generated_position_r_vs_z_"+_meas_type[i_meas]);
        log_th2_names.push_back("neutral_2grand_parent_generated_position_r_vs_z_"+_meas_type[i_meas]);
        log_th2_names.push_back("neutral_3grand_parent_generated_position_r_vs_z_"+_meas_type[i_meas]);
        log_th2_names.push_back("neutral_4grand_parent_generated_position_r_vs_z_"+_meas_type[i_meas]);
        // --
        Print(print_th2_names,log_th2_names,k2D);
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
