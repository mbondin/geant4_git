//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file optical/LXe/include/Run.hh
/// \brief Definition of the Run class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef LXeRun_h
#define LXeRun_h 1

#include "G4Run.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class LXeRun : public G4Run
{
  public:
    LXeRun();
    ~LXeRun();

    void IncPhotonCount_Scint(G4int count) {
      fPhotonCount_Scint  += count;
      fPhotonCount_Scint2 += count*count;
    }
    void IncPhotonCount_Ceren(G4int count) {
      fPhotonCount_Ceren  += count;
      fPhotonCount_Ceren2 += count*count;
    }
    void IncLCE(G4double count){
      fLCE += count;
    }
    void IncEDep(G4double dep) {
      fTotE  += dep;
      fTotE2 += dep*dep;
    }
    void IncEDepPM(G4double deppm){
      fTotEPM += deppm;
      fTotEPM2 += deppm*deppm;
    }
    /*void IncAbsorption(G4int count) {
      fAbsorptionCount  += count;
      fAbsorptionCount2 += count*count;
    }
    void IncBoundaryAbsorption(G4int count) {
      fBoundaryAbsorptionCount  += count;
      fBoundaryAbsorptionCount2 += count*count;
    }*/
    void IncHitCount(G4int count) {
      fHitCount  += count;
      fHitCount2 += count*count;
    }
    void IncHC1(G4int count){
      fHC1 += count;

    }
    void IncHC2(G4int count){
      fHC2 += count;

    }
    void Inchits(G4int count){
      fhits += count;
    }

    /*void IncHitsAboveThreshold(G4int count) {
      fPMTsAboveThreshold  += count;
      fPMTsAboveThreshold2 += count*count;
    }*/

    virtual void Merge(const G4Run* run);

    void EndOfRun();


  private:
    G4int fHitCount, fHitCount2;
    G4int fHC1, fHC2;
    G4int fhits;

    G4int fPhotonCount_Scint, fPhotonCount_Scint2;
    G4int fPhotonCount_Ceren, fPhotonCount_Ceren2;
    G4double fLCE;
    //G4int fAbsorptionCount, fAbsorptionCount2;
    //G4int fBoundaryAbsorptionCount, fBoundaryAbsorptionCount2;
    //G4int fPMTsAboveThreshold, fPMTsAboveThreshold2;

    G4double fTotE, fTotE2;
    G4double fTotEPM, fTotEPM2;
};

#endif // LXeRun_h
