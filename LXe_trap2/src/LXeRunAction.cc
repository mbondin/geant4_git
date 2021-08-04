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
//
/// \file optical/LXe/src/LXeRunAction.cc
/// \brief Implementation of the LXeRunAction class
//
//
#include "LXeRunAction.hh"
#include "LXeRun.hh"
#include "LXeAnalysis.hh"
#include "G4RunManager.hh"
//#include "LXeHistoManager.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeRunAction::LXeRunAction() //: fRun(nullptr)//, fHistoManager(nullptr)
{
  // Book predefined histograms
  //fHistoManager = new LXeHistoManager();
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B4Analysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();


  // Create directories
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  // Default settings
  analysisManager->SetNtupleMerging(true);
  analysisManager->SetFileName("LXe");
  // Creating histograms
  analysisManager->CreateH1("EScint","Edep in scintillator",200, 0., 2.0*MeV);
  analysisManager->CreateH1("HitCount1","Hit Count in SiPM 1",150,0.,1500);
  analysisManager->CreateH1("Photons","Photons created",150,0.,10000);
  
  //create Ntuple
  analysisManager->CreateNtuple("LXe", "Data");
  analysisManager->CreateNtupleDColumn("Energy_deposited");  // column Id = 0
  analysisManager->CreateNtupleDColumn("SiPm_hits");  // column Id = 1
  analysisManager->CreateNtupleDColumn("Photons_per_hit"); // column Id = 2
  analysisManager->FinishNtuple();
  // analysisManager->SetNtupleFileName(0, "LXeNtuple");



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LXeRunAction::~LXeRunAction()
{
  //delete fHistoManager;
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4Run* LXeRunAction::GenerateRun()
{
  fRun = new LXeRun();
  return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeRunAction::BeginOfRunAction(const G4Run*)
{
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  //if (analysisManager->IsActive()) {
  analysisManager->OpenFile();
  //}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LXeRunAction::EndOfRunAction(const G4Run*){
  if (isMaster) fRun->EndOfRun();

  // save histograms
  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->Write();
  analysisManager->CloseFile();

}
