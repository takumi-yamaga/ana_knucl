// AnalyzedData.cc

#include"AnalyzedData.hh"

AnalyzedData::AnalyzedData()
{
    random = new TRandom3(0); // 0 means generating a random seed

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


    Clear();
}

AnalyzedData::~AnalyzedData()
{
    Clear();
    if(random) delete random;
    if(is_pdg_created) delete pdg;
}

void AnalyzedData::Clear()
{
    std::vector<Track*>::iterator itr_tracks_begin;
    std::vector<Track*>::iterator itr_tracks_end;

    // delete std::vector<Track*> _measured_beam_tracks -----
    itr_tracks_begin = _measured_beam_tracks.begin();
    itr_tracks_end = _measured_beam_tracks.end();
    for(std::vector<Track*>::iterator itr_track=itr_tracks_begin; itr_track!=itr_tracks_end; ++itr_track){
        delete (*itr_track);
    }
    _measured_beam_tracks.clear();
    // -----------------------------------------------------

    // delete std::vector<Track*> _measured_charged_tracks --
    itr_tracks_begin = _measured_charged_tracks.begin();
    itr_tracks_end = _measured_charged_tracks.end();
    for(std::vector<Track*>::iterator itr_track=itr_tracks_begin; itr_track!=itr_tracks_end; ++itr_track){
        delete (*itr_track);
    }
    _measured_charged_tracks.clear();
    // -----------------------------------------------------

    // delete std::vector<Track*> _measured_charged_capb_tracks --
    itr_tracks_begin = _measured_charged_capb_tracks.begin();
    itr_tracks_end = _measured_charged_capb_tracks.end();
    for(std::vector<Track*>::iterator itr_track=itr_tracks_begin; itr_track!=itr_tracks_end; ++itr_track){
        delete (*itr_track);
    }
    _measured_charged_capb_tracks.clear();
    // -----------------------------------------------------

    // delete std::vector<Track*> _measured_charged_capf_tracks --
    itr_tracks_begin = _measured_charged_capf_tracks.begin();
    itr_tracks_end = _measured_charged_capf_tracks.end();
    for(std::vector<Track*>::iterator itr_track=itr_tracks_begin; itr_track!=itr_tracks_end; ++itr_track){
        delete (*itr_track);
    }
    _measured_charged_capf_tracks.clear();
    // -----------------------------------------------------

    // delete std::vector<Track*> _measured_neutral_tracks --
    itr_tracks_begin = _measured_neutral_tracks.begin();
    itr_tracks_end = _measured_neutral_tracks.end();
    for(std::vector<Track*>::iterator itr_track=itr_tracks_begin; itr_track!=itr_tracks_end; ++itr_track){
        delete (*itr_track);
    }
    _measured_neutral_tracks.clear();
    _measured_neutral_energy_deposits.clear();
    _measured_neutral_over_betas.clear();
    _measured_neutral_times.clear();
    // -----------------------------------------------------

    // delete std::vector<Track*> _measured_neutral_capb_tracks --
    itr_tracks_begin = _measured_neutral_capb_tracks.begin();
    itr_tracks_end = _measured_neutral_capb_tracks.end();
    for(std::vector<Track*>::iterator itr_track=itr_tracks_begin; itr_track!=itr_tracks_end; ++itr_track){
        delete (*itr_track);
    }
    _measured_neutral_capb_tracks.clear();
    _measured_neutral_capb_energy_deposits.clear();
    _measured_neutral_capb_over_betas.clear();
    _measured_neutral_capb_times.clear();
    // -----------------------------------------------------

    // delete std::vector<Track*> _measured_neutral_capf_tracks --
    itr_tracks_begin = _measured_neutral_capf_tracks.begin();
    itr_tracks_end = _measured_neutral_capf_tracks.end();
    for(std::vector<Track*>::iterator itr_track=itr_tracks_begin; itr_track!=itr_tracks_end; ++itr_track){
        delete (*itr_track);
    }
    _measured_neutral_capf_tracks.clear();
    _measured_neutral_capf_energy_deposits.clear();
    _measured_neutral_capf_over_betas.clear();
    _measured_neutral_capf_times.clear();
    // -----------------------------------------------------

    // clear std::vector<DetectorData*> _**_hits (counters)-
    _t0_hits.clear();
    _def_hits.clear();
    _chcbarrel_hits.clear();
    _chccapb_hits.clear();
    _chccapf_hits.clear();
    _ncbarrel_hits.clear();
    _nccapb_hits.clear();
    _nccapf_hits.clear();
    // -----------------------------------------------------

    // clear std::vector<DetectorData*> _**_hits (chambers)-
    for(Int_t i_layer=0; i_layer<15; ++i_layer){
        _cdc_hits[i_layer].clear();
    }
    for(Int_t i_layer=0; i_layer<8; ++i_layer){
        _bdc1_hits[i_layer].clear();
        _bdc2_hits[i_layer].clear();
        _bdc3_hits[i_layer].clear();
        _fdc1_hits[i_layer].clear();
        _fdc2_hits[i_layer].clear();
        _fdc3_hits[i_layer].clear();
    }
    // -----------------------------------------------------

}

bool AnalyzedData::CheckTrackAlreadyMeasured(std::vector<Track*> measured_tracks, DetectorHit* hit){
    bool is_track_already_measured = false;
    std::vector<Track*>::iterator itr_tracks_begin = measured_tracks.begin();
    std::vector<Track*>::iterator itr_tracks_end = measured_tracks.end();
    for(std::vector<Track*>::iterator itr_track=itr_tracks_begin; itr_track!=itr_tracks_end; ++itr_track){
        Track* track = *itr_track;
        if(track->trackID()==hit->trackID()){
            track->setDetectorHitLink(hit->hitID());
            is_track_already_measured = true;
            break;
        }
    }
    return is_track_already_measured;
}

Track* AnalyzedData::CreateTrack(DetectorHit* hit){
    Track* track = new Track();
    track->init();
    track->setTrackID(hit->trackID());
    track->setMomentum(TVector3(0.,0.,0.));
    track->setParentTrackID(hit->parentID());
    track->setDetectorHitLink(hit->hitID());
    return track;
}

void AnalyzedData::DoAnalysis(MCData* mcData, DetectorData* detectorData)
{
    Clear();

    // ============================================================================================
    // For MCData =================================================================================
    // ============================================================================================
    Int_t total_tracks_in_mcdata = mcData->trackSize();
    TVector3 vec_original_reaction_vertex(0.,0.,0.);
    // check reaction vertex (starting position of Kaon beam)
    for(Int_t i_track = 0; i_track<total_tracks_in_mcdata; i_track++){
        Track* track = mcData->track(i_track);
        if(track->parentTrackID()!=0) continue;
        Int_t pdg_id = track->pdgID();
        if(pdg_id==321){ // K-beam
            vec_original_reaction_vertex = track->vertex()*0.1; // cm
        }
    }
    Double_t sigma_reaction_vertex_xy = kVertexResolutionOfBeamXY;
    Double_t sigma_reaction_vertex_z  = kVertexResolutionOfBeamZ;
    Double_t reaction_vertex_x = vec_original_reaction_vertex.X();
    Double_t reaction_vertex_y = vec_original_reaction_vertex.Y();
    Double_t reaction_vertex_z = vec_original_reaction_vertex.Z();
    reaction_vertex_x = random->Gaus(reaction_vertex_x,sigma_reaction_vertex_xy);
    reaction_vertex_y = random->Gaus(reaction_vertex_y,sigma_reaction_vertex_xy);
    reaction_vertex_z = random->Gaus(reaction_vertex_z,sigma_reaction_vertex_z);
    _vec_reaction_vertex.SetXYZ(reaction_vertex_x,reaction_vertex_y,reaction_vertex_z);
    // ============================================================================================
    // For MCData =================================================================================
    // ============================================================================================



    std::vector<DetectorHit*>::iterator itr_hits_begin;
    std::vector<DetectorHit*>::iterator itr_hits_end;

    std::vector<Track*>::iterator itr_tracks_begin;
    std::vector<Track*>::iterator itr_tracks_end;



    // --------------------------------------------------------------------------------------------
    // Detector hit collection --------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    Int_t total_hits = detectorData->detectorHitSize();   
    for(Int_t i_hit=0; i_hit<total_hits; i_hit++){
        DetectorHit* hit = detectorData->detectorHit(i_hit); 
        Int_t cid = hit->detectorID();
        if(cid==CID_T0){
            _t0_hits.push_back(hit);
        }
        else if(cid==CID_DEF){
            _def_hits.push_back(hit);
        }
        else if(cid==CID_CHCbarrel){
            _chcbarrel_hits.push_back(hit);
        }
        else if(cid==CID_CHCcapB){
            _chccapb_hits.push_back(hit);
        }
        else if(cid==CID_CHCcapF){
            _chccapf_hits.push_back(hit);
        }
        else if(cid==CID_NCbarrel){
            _ncbarrel_hits.push_back(hit);
        }
        else if(cid==CID_NCcapB){
            _nccapb_hits.push_back(hit);
        }
        else if(cid==CID_NCcapF){
            _nccapf_hits.push_back(hit);
        }
        else if(cid==CID_BDC1){
            _bdc1_hits[hit->layerID()].push_back(hit);
        }
        else if(cid==CID_BDC2){
            _bdc2_hits[hit->layerID()].push_back(hit);
        }
        else if(cid==CID_BDC3){
            _bdc3_hits[hit->layerID()].push_back(hit);
        }
        else if(cid==CID_FDC1){
            _fdc1_hits[hit->layerID()].push_back(hit);
        }
        else if(cid==CID_FDC2){
            _fdc2_hits[hit->layerID()].push_back(hit);
        }
        else if(cid==CID_FDC3){
            _fdc3_hits[hit->layerID()].push_back(hit);
        }
        else if(cid==CID_CDC){
            _cdc_hits[hit->layerID()].push_back(hit);
        }
    }
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------
    // beam particle ------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // T0 -----------------------------------------------------------------------------------------
    itr_hits_begin = _t0_hits.begin();
    itr_hits_end = _t0_hits.end();
    for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
        DetectorHit* hit = *itr_hit;
        if(!CheckTrackAlreadyMeasured(_measured_beam_tracks,hit)){
            _measured_beam_tracks.push_back(CreateTrack(hit));
        }
    }
    // T0 -----------------------------------------------------------------------------------------
    // DEF ----------------------------------------------------------------------------------------
    itr_hits_begin = _def_hits.begin();
    itr_hits_end = _def_hits.end();
    for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
        DetectorHit* hit = *itr_hit;
        CheckTrackAlreadyMeasured(_measured_beam_tracks,hit);
    }
    // DEF ----------------------------------------------------------------------------------------
    // BDC1 ---------------------------------------------------------------------------------------
    for(int i_layer=0; i_layer<8; ++i_layer){
        itr_hits_begin = _bdc1_hits[i_layer].begin();
        itr_hits_end = _bdc1_hits[i_layer].end();
        for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
            DetectorHit* hit = *itr_hit;
            CheckTrackAlreadyMeasured(_measured_beam_tracks,hit);
        }
    }
    // BDC1 ---------------------------------------------------------------------------------------
    // BDC2 ---------------------------------------------------------------------------------------
    for(int i_layer=0; i_layer<8; ++i_layer){
        itr_hits_begin = _bdc2_hits[i_layer].begin();
        itr_hits_end = _bdc2_hits[i_layer].end();
        for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
            DetectorHit* hit = *itr_hit;
            CheckTrackAlreadyMeasured(_measured_beam_tracks,hit);
        }
    }
    // BDC2 ---------------------------------------------------------------------------------------
    // BDC3 ---------------------------------------------------------------------------------------
    for(int i_layer=0; i_layer<8; ++i_layer){
        itr_hits_begin = _bdc3_hits[i_layer].begin();
        itr_hits_end = _bdc3_hits[i_layer].end();
        for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
            DetectorHit* hit = *itr_hit;
            CheckTrackAlreadyMeasured(_measured_beam_tracks,hit);
        }
    }
    // BDC3 ---------------------------------------------------------------------------------------
    // Set PID & Momentum -------------------------------------------------------------------------
    for(std::vector<Track*>::iterator itr_track=_measured_beam_tracks.begin(); itr_track!=_measured_beam_tracks.end();){
        Track* track = *itr_track;
        bool is_tracked_by_chamber = false;
        Int_t number_of_hit_in_chamber = 0;
        bool is_detected_by_hodoscope = false;
        bool is_detected_by_t0 = false;
        bool is_detected_by_def = false;
        for(Int_t i_hit=0; i_hit<track->detectorHitLinkSize(); ++i_hit){
            DetectorHit* hit = detectorData->detectorHit(track->detectorHitLink(i_hit));
            if(hit->detectorID()==CID_T0){
                is_detected_by_t0 = true;
            }
            else if(hit->detectorID()==CID_DEF){
                is_detected_by_def = true;
            }
            else if(hit->detectorID()==CID_BDC1||hit->detectorID()==CID_BDC2||hit->detectorID()==CID_BDC3){
                number_of_hit_in_chamber++;
            }
        }
        if(number_of_hit_in_chamber>=kNumberOfChamberHitsInBeamAtLeast){
            is_tracked_by_chamber = true;
        }
        is_detected_by_hodoscope = is_detected_by_t0 & is_detected_by_def;

        if(is_tracked_by_chamber&&is_detected_by_hodoscope){
            for(Int_t i_track = 0; i_track<total_tracks_in_mcdata; ++i_track){
                Track* track_from_mcdata = mcData->track(i_track);
                if(track_from_mcdata->trackID()==track->trackID()){
                    track->setPdgID(-321); // K-
                    TVector3 vec_momentum = -track_from_mcdata->momentum()*0.001; // GeV/c
                    double momentum = vec_momentum.Mag();
                    double sigma_momentum = momentum * kBeamMomentumResolution*0.01; // %
                    momentum = random->Gaus(momentum,sigma_momentum);
                    double theta = vec_momentum.Theta();
                    double sigma_theta = pow(sin(theta),2.)*kBeamThetaResolution;
                    theta = random->Gaus(theta,sigma_theta);
                    vec_momentum.SetMag(momentum);
                    vec_momentum.SetTheta(theta);
                    track->setMomentum(vec_momentum);
                    break;
                }
            }
            ++itr_track;
        }
        else{
            delete (*itr_track);
            itr_track = _measured_beam_tracks.erase(itr_track);
        }
    }
    // Set PID & Momentum -------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------




    // --------------------------------------------------------------------------------------------
    // charged particles (barrel) -----------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // CDC ----------------------------------------------------------------------------------------
    for(int i_layer=0; i_layer<15; i_layer++){
        itr_hits_begin = _cdc_hits[i_layer].begin();
        itr_hits_end = _cdc_hits[i_layer].end();
        for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
            DetectorHit* hit = *itr_hit;
            if(!CheckTrackAlreadyMeasured(_measured_charged_tracks,hit)){
                _measured_charged_tracks.push_back(CreateTrack(hit));
            }
        }
    }
    // CDC ----------------------------------------------------------------------------------------
    // CHCbarrel ----------------------------------------------------------------------------------
    itr_hits_begin = _chcbarrel_hits.begin();
    itr_hits_end = _chcbarrel_hits.end();
    for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
        DetectorHit* hit = *itr_hit;
        CheckTrackAlreadyMeasured(_measured_charged_tracks,hit);
    }
    // CHCbarrel ----------------------------------------------------------------------------------
    // Set PID & Momentum -------------------------------------------------------------------------
    for(std::vector<Track*>::iterator itr_track=_measured_charged_tracks.begin(); itr_track!=_measured_charged_tracks.end();){
        Track* track = *itr_track;
        bool is_tracked_by_chamber = false;
        Int_t number_of_hit_in_chamber = 0;
        bool is_detected_by_hodoscope = false;
        Int_t first_hit_layer = 99;
        Int_t last_hit_layer = -99;
        bool is_layer_fired[15] = {false};
        for(Int_t i_hit=0; i_hit<track->detectorHitLinkSize(); i_hit++){
            DetectorHit* hit = detectorData->detectorHit(track->detectorHitLink(i_hit));
            if(hit->detectorID()==CID_CDC){
                if(hit->layerID()<first_hit_layer){
                    first_hit_layer = hit->layerID();
                }
                if(hit->layerID()>last_hit_layer){
                    last_hit_layer = hit->layerID();
                }
                if(!is_layer_fired[hit->layerID()]){
                    is_layer_fired[hit->layerID()] = true;
                    number_of_hit_in_chamber++;
                }
            }
            else if(hit->detectorID()==CID_CHCbarrel){
                is_detected_by_hodoscope = true;
            }
        }
        if(number_of_hit_in_chamber>=kNumberOfChamberHitsInCDCAtLeast){
            is_tracked_by_chamber = true;
        }

        if(is_tracked_by_chamber&&is_detected_by_hodoscope){
            for(Int_t i_track = 0; i_track<total_tracks_in_mcdata; i_track++){
                Track* track_from_mcdata = mcData->track(i_track);
                if(track_from_mcdata->trackID()==track->trackID()){
                    track->setPdgID(track_from_mcdata->pdgID());
                    TVector3 vec_momentum = track_from_mcdata->momentum()*0.001; // GeV/c

                    // transverse momentum
                    Double_t transverse_momentum = vec_momentum.Perp();
                    Double_t beta = 0.;
                    TParticlePDG* particle = pdg->GetParticle(track->pdgID());
                    if(particle){
                        Double_t mass = particle->Mass();
                        beta = vec_momentum.Mag() / sqrt(vec_momentum.Mag2()+mass*mass);
                    }

                    Double_t lever_arm_length = fabs(kCDCLayerRadius[last_hit_layer]-kCDCLayerRadius[first_hit_layer])*0.01; // m
                    Double_t arm_length = lever_arm_length / sin(vec_momentum.Theta());

                    Double_t transverse_momentum_resolution_meas_error = transverse_momentum * kRadialResolutionOfCDC / (0.3*pow(lever_arm_length,2.)*kMagneticField) * sqrt(720./(Double_t)(number_of_hit_in_chamber+5));
                    Double_t transverse_momentum_resolution_mult_scat = 0.05 / (beta*kMagneticField) * sqrt( 1.43/(lever_arm_length*kRadiationLengthOfChamberGas) );
                    Double_t transverse_momentum_resolution = transverse_momentum * sqrt( pow(transverse_momentum_resolution_meas_error,2.) + pow(transverse_momentum_resolution_mult_scat,2.) );
                    Double_t transverse_momentum_smeared = random->Gaus(transverse_momentum,transverse_momentum_resolution);

                    // theta
                    Double_t theta = vec_momentum.Theta();
                    Double_t momentum = vec_momentum.Mag();

                    Double_t theta_resolution_meas_error = pow(sin(theta),2.) / arm_length * kZResolutionOfCDC;
                    Double_t theta_resolution_mult_scat = 0.015 / (momentum*beta) * sqrt(arm_length/kRadiationLengthOfChamberGas);
                    Double_t theta_resolution = sqrt( pow(theta_resolution_meas_error,2.) + pow(theta_resolution_mult_scat,2.) );
                    Double_t theta_smeared = random->Gaus(theta,theta_resolution);

                    // set smeared momentum
                    TVector3 vec_momentum_smeared = vec_momentum;
                    vec_momentum_smeared.SetMag(transverse_momentum_smeared/sin(theta_smeared));
                    vec_momentum_smeared.SetTheta(theta_smeared);
                    track->setMomentum(vec_momentum_smeared);
                    break;
                }
            }
            itr_track++;
        }
        else{
            delete (*itr_track);
            itr_track = _measured_charged_tracks.erase(itr_track);
        }
    }
    // Set PID & Momentum -------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------
    // charged particles (capb)  --------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // CDC ----------------------------------------------------------------------------------------
    for(int i_layer=0; i_layer<15; i_layer++){
        itr_hits_begin = _cdc_hits[i_layer].begin();
        itr_hits_end = _cdc_hits[i_layer].end();
        for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
            DetectorHit* hit = *itr_hit;
            if(!CheckTrackAlreadyMeasured(_measured_charged_capb_tracks,hit)){
                _measured_charged_capb_tracks.push_back(CreateTrack(hit));
            }
        }
    }
    // CDC ----------------------------------------------------------------------------------------
    // CHCCapB ------------------------------------------------------------------------------------
    itr_hits_begin = _chccapb_hits.begin();
    itr_hits_end = _chccapb_hits.end();
    for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
        DetectorHit* hit = *itr_hit;
        CheckTrackAlreadyMeasured(_measured_charged_capb_tracks,hit);
    }
    // CHCcapB ------------------------------------------------------------------------------------
    // Set PID & Momentum -------------------------------------------------------------------------
    for(std::vector<Track*>::iterator itr_track=_measured_charged_capb_tracks.begin(); itr_track!=_measured_charged_capb_tracks.end();){
        Track* track = *itr_track;
        bool is_tracked_by_chamber = false;
        Int_t number_of_hit_in_chamber = 0;
        bool is_detected_by_hodoscope = false;
        Int_t first_hit_layer = 99;
        Int_t last_hit_layer = -99;
        bool is_layer_fired[15] = {false};
        for(Int_t i_hit=0; i_hit<track->detectorHitLinkSize(); i_hit++){
            DetectorHit* hit = detectorData->detectorHit(track->detectorHitLink(i_hit));
            if(hit->detectorID()==CID_CDC){
                if(hit->layerID()<first_hit_layer){
                    first_hit_layer = hit->layerID();
                }
                if(hit->layerID()>last_hit_layer){
                    last_hit_layer = hit->layerID();
                }
                if(!is_layer_fired[hit->layerID()]){
                    is_layer_fired[hit->layerID()] = true;
                    number_of_hit_in_chamber++;
                }
            }
            else if(hit->detectorID()==CID_CHCcapB){
                is_detected_by_hodoscope = true;
            }
        }
        if(number_of_hit_in_chamber>=kNumberOfChamberHitsInCAPAtLeast){
            is_tracked_by_chamber = true;
        }

        if(is_tracked_by_chamber&&is_detected_by_hodoscope){
            for(Int_t i_track = 0; i_track<total_tracks_in_mcdata; i_track++){
                Track* track_from_mcdata = mcData->track(i_track);
                if(track_from_mcdata->trackID()==track->trackID()){
                    track->setPdgID(track_from_mcdata->pdgID());
                    TVector3 vec_momentum = track_from_mcdata->momentum()*0.001; // GeV/c

                    // transverse momentum
                    Double_t transverse_momentum = vec_momentum.Perp();
                    Double_t beta = 0.;
                    TParticlePDG* particle = pdg->GetParticle(track->pdgID());
                    if(particle){
                        Double_t mass = particle->Mass();
                        beta = vec_momentum.Mag() / sqrt(vec_momentum.Mag2()+mass*mass);
                    }

                    Double_t lever_arm_length = fabs(kCDCLayerRadius[last_hit_layer]-kCDCLayerRadius[first_hit_layer])*0.01; // m
                    Double_t arm_length = lever_arm_length / sin(vec_momentum.Theta());

                    Double_t transverse_momentum_resolution_meas_error = transverse_momentum * kRadialResolutionOfCDC / (0.3*pow(lever_arm_length,2.)*kMagneticField) * sqrt(720./(Double_t)(number_of_hit_in_chamber+5));
                    Double_t transverse_momentum_resolution_mult_scat = 0.05 / (beta*kMagneticField) * sqrt( 1.43/(lever_arm_length*kRadiationLengthOfChamberGas) );
                    Double_t transverse_momentum_resolution = transverse_momentum * sqrt( pow(transverse_momentum_resolution_meas_error,2.) + pow(transverse_momentum_resolution_mult_scat,2.) );
                    Double_t transverse_momentum_smeared = random->Gaus(transverse_momentum,transverse_momentum_resolution);

                    // theta
                    Double_t theta = vec_momentum.Theta();
                    Double_t momentum = vec_momentum.Mag();

                    Double_t theta_resolution_meas_error = pow(sin(theta),2.) / arm_length * kZResolutionOfCDC;
                    Double_t theta_resolution_mult_scat = 0.015 / (momentum*beta) * sqrt(arm_length/kRadiationLengthOfChamberGas);
                    Double_t theta_resolution = sqrt( pow(theta_resolution_meas_error,2.) + pow(theta_resolution_mult_scat,2.) );
                    Double_t theta_smeared = random->Gaus(theta,theta_resolution);

                    // set smeared momentum
                    TVector3 vec_momentum_smeared = vec_momentum;
                    vec_momentum_smeared.SetMag(transverse_momentum_smeared/sin(theta_smeared));
                    vec_momentum_smeared.SetTheta(theta_smeared);
                    track->setMomentum(vec_momentum_smeared);
                    break;
                }
            }
            itr_track++;
        }
        else{
            delete (*itr_track);
            itr_track = _measured_charged_capb_tracks.erase(itr_track);
        }
    }
    // Set PID & Momentum -------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------
    // charged particles (capf)  --------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // CDC ----------------------------------------------------------------------------------------
    for(int i_layer=0; i_layer<15; i_layer++){
        itr_hits_begin = _cdc_hits[i_layer].begin();
        itr_hits_end = _cdc_hits[i_layer].end();
        for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
            DetectorHit* hit = *itr_hit;
            if(!CheckTrackAlreadyMeasured(_measured_charged_capf_tracks,hit)){
                _measured_charged_capf_tracks.push_back(CreateTrack(hit));
            }
        }
    }
    // CDC ----------------------------------------------------------------------------------------
    // CHCCapF ------------------------------------------------------------------------------------
    itr_hits_begin = _chccapf_hits.begin();
    itr_hits_end = _chccapf_hits.end();
    for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
        DetectorHit* hit = *itr_hit;
        CheckTrackAlreadyMeasured(_measured_charged_capf_tracks,hit);
    }
    // CHCcapF ------------------------------------------------------------------------------------
    // Set PID & Momentum -------------------------------------------------------------------------
    for(std::vector<Track*>::iterator itr_track=_measured_charged_capf_tracks.begin(); itr_track!=_measured_charged_capf_tracks.end();){
        Track* track = *itr_track;
        bool is_tracked_by_chamber = false;
        Int_t number_of_hit_in_chamber = 0;
        bool is_detected_by_hodoscope = false;
        Int_t first_hit_layer = 99;
        Int_t last_hit_layer = -99;
        bool is_layer_fired[15] = {false};
        for(Int_t i_hit=0; i_hit<track->detectorHitLinkSize(); i_hit++){
            DetectorHit* hit = detectorData->detectorHit(track->detectorHitLink(i_hit));
            if(hit->detectorID()==CID_CDC){
                if(hit->layerID()<first_hit_layer){
                    first_hit_layer = hit->layerID();
                }
                if(hit->layerID()>last_hit_layer){
                    last_hit_layer = hit->layerID();
                }
                if(!is_layer_fired[hit->layerID()]){
                    is_layer_fired[hit->layerID()] = true;
                    number_of_hit_in_chamber++;
                }
            }
            else if(hit->detectorID()==CID_CHCcapF){
                is_detected_by_hodoscope = true;
            }
        }
        if(number_of_hit_in_chamber>=kNumberOfChamberHitsInCAPAtLeast){
            is_tracked_by_chamber = true;
        }

        if(is_tracked_by_chamber&&is_detected_by_hodoscope){
            for(Int_t i_track = 0; i_track<total_tracks_in_mcdata; i_track++){
                Track* track_from_mcdata = mcData->track(i_track);
                if(track_from_mcdata->trackID()==track->trackID()){
                    track->setPdgID(track_from_mcdata->pdgID());
                    TVector3 vec_momentum = track_from_mcdata->momentum()*0.001; // GeV/c

                    // transverse momentum
                    Double_t transverse_momentum = vec_momentum.Perp();
                    Double_t beta = 0.;
                    TParticlePDG* particle = pdg->GetParticle(track->pdgID());
                    if(particle){
                        Double_t mass = particle->Mass();
                        beta = vec_momentum.Mag() / sqrt(vec_momentum.Mag2()+mass*mass);
                    }

                    Double_t lever_arm_length = fabs(kCDCLayerRadius[last_hit_layer]-kCDCLayerRadius[first_hit_layer])*0.01; // m
                    Double_t arm_length = lever_arm_length / sin(vec_momentum.Theta());

                    Double_t transverse_momentum_resolution_meas_error = transverse_momentum * kRadialResolutionOfCDC / (0.3*pow(lever_arm_length,2.)*kMagneticField) * sqrt(720./(Double_t)(number_of_hit_in_chamber+5));
                    Double_t transverse_momentum_resolution_mult_scat = 0.05 / (beta*kMagneticField) * sqrt( 1.43/(lever_arm_length*kRadiationLengthOfChamberGas) );
                    Double_t transverse_momentum_resolution = transverse_momentum * sqrt( pow(transverse_momentum_resolution_meas_error,2.) + pow(transverse_momentum_resolution_mult_scat,2.) );
                    Double_t transverse_momentum_smeared = random->Gaus(transverse_momentum,transverse_momentum_resolution);

                    //std::cout << "------" << std::endl;
                    //std::cout << "L : " << lever_arm_length << std::endl;
                    //std::cout << "L_arm : " << arm_length << std::endl;
                    //std::cout << "pt_meas / pt : " << transverse_momentum_resolution_meas_error/transverse_momentum << std::endl;
                    //std::cout << "pt_ms * beta : " << transverse_momentum_resolution_mult_scat*beta << std::endl;

                    // theta
                    Double_t theta = vec_momentum.Theta();
                    Double_t momentum = vec_momentum.Mag();

                    Double_t theta_resolution_meas_error = pow(sin(theta),2.) / arm_length * kZResolutionOfCDC;
                    Double_t theta_resolution_mult_scat = 0.015 / (momentum*beta) * sqrt(arm_length/kRadiationLengthOfChamberGas);
                    Double_t theta_resolution = sqrt( pow(theta_resolution_meas_error,2.) + pow(theta_resolution_mult_scat,2.) );
                    Double_t theta_smeared = random->Gaus(theta,theta_resolution);

                    // set smeared momentum
                    TVector3 vec_momentum_smeared = vec_momentum;
                    vec_momentum_smeared.SetMag(transverse_momentum_smeared/sin(theta_smeared));
                    vec_momentum_smeared.SetTheta(theta_smeared);
                    track->setMomentum(vec_momentum_smeared);
                    break;
                }
            }
            itr_track++;
        }
        else{
            delete (*itr_track);
            itr_track = _measured_charged_capf_tracks.erase(itr_track);
        }
    }
    // Set PID & Momentum -------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------



    // --------------------------------------------------------------------------------------------
    // neutral particles (barrel) -----------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // CHCbarrel ----------------------------------------------------------------------------------
    itr_hits_begin = _chcbarrel_hits.begin();
    itr_hits_end = _chcbarrel_hits.end();
    for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
        DetectorHit* hit = *itr_hit;
        if(!CheckTrackAlreadyMeasured(_measured_neutral_tracks,hit)){
            _measured_neutral_tracks.push_back(CreateTrack(hit));
        }
    }
    // CHCbarrel ----------------------------------------------------------------------------------
    // NCbarrel ----------------------------------------------------------------------------------
    itr_hits_begin = _ncbarrel_hits.begin();
    itr_hits_end = _ncbarrel_hits.end();
    for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
        DetectorHit* hit = *itr_hit;
        if(!CheckTrackAlreadyMeasured(_measured_neutral_tracks,hit)){
            _measured_neutral_tracks.push_back(CreateTrack(hit));
        }
    }
    // NCbarrel ----------------------------------------------------------------------------------
    // Set PID & Momentum -------------------------------------------------------------------------
    for(std::vector<Track*>::iterator itr_track=_measured_neutral_tracks.begin(); itr_track!=_measured_neutral_tracks.end();){
        Track* track = *itr_track;
        DetectorHit* nc_hit = 0;
        bool is_detected_by_veto = false;
        bool is_detected_by_hodoscope = false;
        for(Int_t i_hit=0; i_hit<track->detectorHitLinkSize(); i_hit++){
            DetectorHit* hit = detectorData->detectorHit(track->detectorHitLink(i_hit));
            if(hit->detectorID()==CID_CHCbarrel){
                is_detected_by_veto = true;
            }
            else if(hit->detectorID()==CID_NCbarrel){
                is_detected_by_hodoscope = true;
                if(!nc_hit){
                    nc_hit = hit;
                }
                else{
                    if(nc_hit->time()>hit->time()){
                        nc_hit = hit;
                    }
                }
            }
        }

        if(!is_detected_by_veto&&is_detected_by_hodoscope){
            double energy_deposit = nc_hit->de(); // MeVee
            double time = nc_hit->time(); // ns
            double sigma_time = kTOFResolutionOfNC; // ns
            time = random->Gaus(time,sigma_time);
            TVector3 vec_position = nc_hit->pos()*0.1; // cm
            double sigma_z_position = kZPositionResolutionOfNC; // cm
            vec_position.SetZ(random->Gaus(vec_position.Z(),sigma_z_position));
            TVector3 vec_momentum = vec_position - _vec_reaction_vertex;
            double over_beta = (time * kLightVelocity) / vec_momentum.Mag();
            double momentum = kNeutronMass / sqrt(pow(over_beta,2.)-1.); // GeV/c
            vec_momentum.SetMag(momentum);
            track->setPdgID(2112);
            track->setMomentum(vec_momentum);

            if(momentum>kNeutralMomentumAtLeast/1000.&&energy_deposit>kNeutralEnergyDepositAtLeast&&over_beta>kNeutralOverBetaAtLeast){
                _measured_neutral_energy_deposits.push_back(energy_deposit);
                _measured_neutral_over_betas.push_back(over_beta);
                _measured_neutral_times.push_back(time);
                itr_track++;
            }
            else{
                delete (*itr_track);
                itr_track = _measured_neutral_tracks.erase(itr_track);
            }
        }
        else{
            delete (*itr_track);
            itr_track = _measured_neutral_tracks.erase(itr_track);
        }
    }
    // Set PID & Momentum -------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------
    // neutral particles (capb) -------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // CHCcapB ------------------------------------------------------------------------------------
    itr_hits_begin = _chccapb_hits.begin();
    itr_hits_end = _chccapb_hits.end();
    for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
        DetectorHit* hit = *itr_hit;
        if(!CheckTrackAlreadyMeasured(_measured_neutral_capb_tracks,hit)){
            _measured_neutral_capb_tracks.push_back(CreateTrack(hit));
        }
    }
    // CHCcapB ------------------------------------------------------------------------------------
    // NCcapB ------------------------------------------------------------------------------------
    itr_hits_begin = _nccapb_hits.begin();
    itr_hits_end = _nccapb_hits.end();
    for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
        DetectorHit* hit = *itr_hit;
        if(!CheckTrackAlreadyMeasured(_measured_neutral_capb_tracks,hit)){
            _measured_neutral_capb_tracks.push_back(CreateTrack(hit));
        }
    }
    // NCcapB ------------------------------------------------------------------------------------
    // Set PID & Momentum -------------------------------------------------------------------------
    for(std::vector<Track*>::iterator itr_track=_measured_neutral_capb_tracks.begin(); itr_track!=_measured_neutral_capb_tracks.end();){
        Track* track = *itr_track;
        DetectorHit* nc_hit = 0;
        bool is_detected_by_veto = false;
        bool is_detected_by_hodoscope = false;
        for(Int_t i_hit=0; i_hit<track->detectorHitLinkSize(); i_hit++){
            DetectorHit* hit = detectorData->detectorHit(track->detectorHitLink(i_hit));
            if(hit->detectorID()==CID_CHCcapB){
                is_detected_by_veto = true;
            }
            else if(hit->detectorID()==CID_NCcapB){
                is_detected_by_hodoscope = true;
                if(!nc_hit){
                    nc_hit = hit;
                }
                else{
                    if(nc_hit->time()>hit->time()){
                        nc_hit = hit;
                    }
                }
            }
        }

        if(!is_detected_by_veto&&is_detected_by_hodoscope){
            double energy_deposit = nc_hit->de(); // MeVee
            double time = nc_hit->time(); // ns
            double sigma_time = kTOFResolutionOfNC; // ns
            time = random->Gaus(time,sigma_time);
            TVector3 vec_position = nc_hit->pos()*0.1; // cm
            double r_position = sqrt( pow(vec_position.X(),2.) + pow(vec_position.Y(),2.) );
            double sigma_r_position = kRPositionResolutionOfNC; // cm
            r_position = random->Gaus(r_position,sigma_r_position); 
            double phi = vec_position.Phi();
            double x_position = r_position * cos(phi);
            double y_position = r_position * sin(phi);
            vec_position.SetX(x_position);
            vec_position.SetY(y_position);
            TVector3 vec_momentum = vec_position - _vec_reaction_vertex;
            double over_beta = (time * kLightVelocity) / vec_momentum.Mag();
            double momentum = kNeutronMass / sqrt(pow(over_beta,2.)-1.); // GeV/c
            vec_momentum.SetMag(momentum);
            track->setPdgID(2112);
            track->setMomentum(vec_momentum);
            _measured_neutral_capb_energy_deposits.push_back(energy_deposit);
            _measured_neutral_capb_over_betas.push_back(over_beta);
            _measured_neutral_capb_times.push_back(time);

            if(momentum>kNeutralMomentumAtLeast/1000.&&energy_deposit>kNeutralEnergyDepositAtLeast&&over_beta>kNeutralOverBetaAtLeast){
                itr_track++;
            }
            else{
                delete (*itr_track);
                itr_track = _measured_neutral_capb_tracks.erase(itr_track);
            }
        }
        else{
            delete (*itr_track);
            itr_track = _measured_neutral_capb_tracks.erase(itr_track);
        }
    }
    // Set PID & Momentum -------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------

    // --------------------------------------------------------------------------------------------
    // neutral particles (capf) -------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // CHCcapF ------------------------------------------------------------------------------------
    itr_hits_begin = _chccapf_hits.begin();
    itr_hits_end = _chccapf_hits.end();
    for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
        DetectorHit* hit = *itr_hit;
        if(!CheckTrackAlreadyMeasured(_measured_neutral_capf_tracks,hit)){
            _measured_neutral_capf_tracks.push_back(CreateTrack(hit));
        }
    }
    // CHCcapF ------------------------------------------------------------------------------------
    // NCcapF ------------------------------------------------------------------------------------
    itr_hits_begin = _nccapf_hits.begin();
    itr_hits_end = _nccapf_hits.end();
    for(std::vector<DetectorHit*>::iterator itr_hit=itr_hits_begin; itr_hit!=itr_hits_end; ++itr_hit){
        DetectorHit* hit = *itr_hit;
        if(!CheckTrackAlreadyMeasured(_measured_neutral_capf_tracks,hit)){
            _measured_neutral_capf_tracks.push_back(CreateTrack(hit));
        }
    }
    // NCcapF ------------------------------------------------------------------------------------
    // Set PID & Momentum -------------------------------------------------------------------------
    for(std::vector<Track*>::iterator itr_track=_measured_neutral_capf_tracks.begin(); itr_track!=_measured_neutral_capf_tracks.end();){
        Track* track = *itr_track;
        DetectorHit* nc_hit = 0;
        bool is_detected_by_veto = false;
        bool is_detected_by_hodoscope = false;
        for(Int_t i_hit=0; i_hit<track->detectorHitLinkSize(); i_hit++){
            DetectorHit* hit = detectorData->detectorHit(track->detectorHitLink(i_hit));
            if(hit->detectorID()==CID_CHCcapF){
                is_detected_by_veto = true;
            }
            else if(hit->detectorID()==CID_NCcapF){
                is_detected_by_hodoscope = true;
                if(!nc_hit){
                    nc_hit = hit;
                }
                else{
                    if(nc_hit->time()>hit->time()){
                        nc_hit = hit;
                    }
                }
            }
        }

        if(!is_detected_by_veto&&is_detected_by_hodoscope){
            double energy_deposit = nc_hit->de(); // MeVee
            double time = nc_hit->time(); // ns
            double sigma_time = kTOFResolutionOfNC; // ns
            time = random->Gaus(time,sigma_time);
            TVector3 vec_position = nc_hit->pos()*0.1; // cm
            double r_position = sqrt( pow(vec_position.X(),2.) + pow(vec_position.Y(),2.) );
            double sigma_r_position = kRPositionResolutionOfNC; // cm
            r_position = random->Gaus(r_position,sigma_r_position); 
            double phi = vec_position.Phi();
            double x_position = r_position * cos(phi);
            double y_position = r_position * sin(phi);
            vec_position.SetX(x_position);
            vec_position.SetY(y_position);
            TVector3 vec_momentum = vec_position - _vec_reaction_vertex;
            double over_beta = (time * kLightVelocity) / vec_momentum.Mag();
            double momentum = kNeutronMass / sqrt(pow(over_beta,2.)-1.); // GeV/c
            vec_momentum.SetMag(momentum);
            track->setPdgID(2112);
            track->setMomentum(vec_momentum);
            _measured_neutral_capf_energy_deposits.push_back(energy_deposit);
            _measured_neutral_capf_over_betas.push_back(over_beta);
            _measured_neutral_capf_times.push_back(time);

            if(momentum>kNeutralMomentumAtLeast/1000.&&energy_deposit>kNeutralEnergyDepositAtLeast&&over_beta>kNeutralOverBetaAtLeast){
                itr_track++;
            }
            else{
                delete (*itr_track);
                itr_track = _measured_neutral_capf_tracks.erase(itr_track);
            }
        }
        else{
            delete (*itr_track);
            itr_track = _measured_neutral_capf_tracks.erase(itr_track);
        }
    }
    // Set PID & Momentum -------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------
    // --------------------------------------------------------------------------------------------


    return;
}


