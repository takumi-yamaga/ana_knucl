// AnaKnuclCommon.h

#ifndef AnaKnuclCommon_h
#define AnaKnuclCommon_h

#include "KinFitter/TKinFitter.h"
#include "KinFitter/TFitParticlePxPyPz.h"
#include "KinFitter/TFitConstraintM.h"
#include "KinFitter/TFitConstraintEp.h"

#include"TObject.h"
#include"TMatrixD.h"

const Int_t k1D = 1;
const Int_t k2D = 2;
const Int_t kXSlice = 1;
const Int_t kYSlice = 2;

const Double_t kPiMass = 0.13957;
const Double_t kPi0Mass= 0.1349766;
const Double_t kProtonMass= 0.938272;
const Double_t kNeutronMass = 0.939565;
const Double_t kDeutronMass = 1.87561;
const Double_t kLambdaMass = 1.115683;
const Double_t kSigma0Mass= 1.192642;
const Double_t kSigmaPlusMass= 1.18937;
const Double_t kSigmaMinusMass= 1.197449;
const Double_t kKaonMass = 0.4936;
const Double_t kKaon0Mass = 0.497614;
const Double_t kThreeHeMass = 2.80839;
const Double_t kLightVelocity = 29.97; // cm/ns

const Double_t kPlanckConstantReduced = 6.582119514e-22; // MeV s
const Double_t kNuclearMagneton = 3.1524512550e-14; // MeV/T
const Double_t kProtonMagneticMoment = 2.792847351;
const Double_t kLambdaMagneticMoment = -0.613;

const Double_t kVertexResolutionOfBeamXY = 1.0; // mm
const Double_t kVertexResolutionOfBeamZ  =10.0; // mm

const Int_t kNumberOfChamberHitsInBeamAtLeast = 8;
const Double_t kBeamMomentumResolution = 2.0; // %
const Double_t kBeamThetaResolution = 0.01; 

const Int_t kNumberOfChamberHitsInCDCAtLeast = 15;
const Int_t kNumberOfChamberHitsInCAPAtLeast = 7;
const Double_t kRadialResolutionOfCDC = 200.e-6; // m (200 um)
const Double_t kZResolutionOfCDC = 2.e-3; // m (2 mm)
const Double_t kMagneticField = 0.7; // T
const Double_t kRadiationLengthOfChamberGas = 500.; // m

const Double_t kTOFResolutionOfNC = 0.12; // ns
const Double_t kZPositionResolutionOfNC = 5.0; // cm
const Double_t kRPositionResolutionOfNC = 5.0; // cm
const Double_t kNeutralMomentumAtLeast = 10.; // MeV/c
const Double_t kNeutralEnergyDepositAtLeast = 5.0; // MeVee
const Double_t kNeutralOverBetaAtLeast = 1.2;

const Double_t kAnalysisEfficiency = 0.5;
const Double_t kSelectionEfficiency = 0.8;

// covariance target
const Double_t kValCovarianceZero[9] = {
    0.0000e+00,0.0000e+00,0.0000e+00,
    0.0000e+00,0.0000e+00,0.0000e+00,
    0.0000e+00,0.0000e+00,0.0000e+00
};
// covariance beam
const Double_t kValCovarianceBeam[9] = {
    3.8852e-04,0.0000e+00,0.0000e+00,
    0.0000e+00,2.9573e-04,0.0000e+00,
    0.0000e+00,0.0000e+00,2.0400e-02
};
// covariance proton
inline void GetCovarianceProton(Double_t momentum, Double_t val_covariance[9]){
    val_covariance[0] = momentum * (1.4038e-02 + 1.7051e-02*momentum);
    val_covariance[1] = 0.;
    val_covariance[2] = 0.;

    val_covariance[3] = 0.;
    val_covariance[4] = momentum * (1.3766e-02 + 1.7358e-02*momentum);
    val_covariance[5] = 0.;

    val_covariance[6] = 0.;
    val_covariance[7] = 0.;
    val_covariance[8] = momentum * (6.1509e-03 + 2.3576e-02*momentum);

    return;
}
// covariance neutron
inline void GetCovarianceNeutron(Double_t momentum, Double_t val_covariance[9]){
    val_covariance[0] = momentum * (2.2299e-02 + 2.6878e-02*momentum);
    val_covariance[1] = 0.;
    val_covariance[2] = 0.;

    val_covariance[3] = 0.;
    val_covariance[4] = momentum * (2.2169e-02 + 2.7251e-02*momentum);
    val_covariance[5] = 0.;

    val_covariance[6] = 0.;
    val_covariance[7] = 0.;
    val_covariance[8] = momentum * (9.8380e-02 + 5.3162e-03*momentum);

    return;
}
// covariance pi
inline void GetCovariancePi(Double_t momentum, Double_t val_covariance[9]){
    val_covariance[0] = momentum * (1.0219e-02 - 9.0273e-03*momentum);
    val_covariance[1] = 0.;
    val_covariance[2] = 0.;

    val_covariance[3] = 0.;
    val_covariance[4] = momentum * (1.0809e-02 - 1.0592e-02*momentum);
    val_covariance[5] = 0.;

    val_covariance[6] = 0.;
    val_covariance[7] = 0.;
    val_covariance[8] = momentum * (8.9558e-03 + 1.4078e-02*momentum);

    return;
}

const Double_t kCovarianceLpn_LpDetection[7][4] = {
    {0.0000e+00,0.0000e+00,0.0000e+00,0.0000e+00}, // target
    {3.8852e-04,2.9573e-04,2.0400e-02,1.8371e-02}, // beam
    //{2.6103e-02,2.6007e-02,2.4774e-02,2.7949e-02}, // lambda
    {0.0000e+00,0.0000e+00,0.0000e+00,0.0000e+00}, // target
    {2.6355e-02,2.6347e-02,2.4634e-02,3.2425e-02}, // proton
    //{3.6823e-02,3.6820e-02,4.0240e-02,4.6315e-02}, // neutron
    {0.0000e+00,0.0000e+00,0.0000e+00,0.0000e+00}, // target
    {5.5298e-03,5.5954e-03,5.6179e-03,6.6288e-03}, // pi_from_lambda
    {2.3416e-02,2.3405e-02,2.1997e-02,2.6815e-02}  // nucleon_from_lambda
};

const Double_t kCovarianceLpn_LnDetection[7][4] = {
    {0.0000e+00,0.0000e+00,0.0000e+00,0.0000e+00}, // target
    {4.3944e-04,3.6557e-04,2.0329e-02,1.8290e-02}, // beam
    {2.5739e-02,2.5883e-02,2.5247e-02,2.8981e-02}, // lambda
    {4.7361e-02,4.7480e-02,8.9949e-02,6.8453e-02}, // proton
    {4.0525e-02,4.0565e-02,8.7110e-02,6.1729e-02}, // neutron
    {4.7987e-03,5.2967e-03,5.0944e-03,5.9320e-03}, // pi_from_lambda
    {2.3639e-02,2.3847e-02,2.3121e-02,2.7971e-02}  // nucleon_from_lambda
};

const Int_t kLineColor[10] = {
    kBlack,
    kRed-4,
    kBlue-4,
    kGreen+1,
    kBlack,
    kBlack,
    kBlack,
    kBlack,
    kBlack,
    kBlack
};

const Double_t kCDCLayerRadius[15] = { // cm
    19.05,
    20.40,
    21.75,
    24.85,
    26.20,
    29.30,
    30.65,
    33.75,
    35.10,
    38.20,
    39.55,
    42.65,
    44.00,
    47.10,
    48.45
};

inline double sign(double val){
    return (val>0)-(val<0);
}

#endif
