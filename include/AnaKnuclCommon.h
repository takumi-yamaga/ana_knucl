// AnaKnuclCommon.h

#ifndef AnaKnuclCommon_h
#define AnaKnuclCommon_h

#include"TObject.h"

const Int_t k1D = 1;
const Int_t k2D = 2;

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

const Double_t kRadialResolutionOfCDC = 200.e-6; // m (200 um)
const Double_t kZResolutionOfCDC = 2.e-3; // m (2 mm)
const Double_t kMagneticField = 0.7; // T
const Double_t kRadiationLengthOfChamberGas = 500.; // m

const Double_t kAnalysisEfficiency = 0.5;
const Double_t kSelectionEfficiency = 0.8;

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



#endif
