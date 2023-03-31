
#include "histogram_plot.h"

#define str(s) (TString) #s

void tests_macro_RDataFrame() {

	// Option for not showing plots after compiling
	gROOT->SetBatch(kTRUE);

	// To include headers from another folder
	//R__ADD_INCLUDE_PATH(<name of the path>);

	// Definition of the data frame
	//ROOT::EnableImplicitMT(); // Tell ROOT you want to go parallel
	ROOT::RDataFrame d("ana_tree", "Reco_2305_160gev_V1.1.root"); // Interface to TTree and TChain

	//ROOT::RDataFrame d0("ana_tree", "Reco_2305_160gev_V1.1.root");
	//auto d = d0.Range(0, 1000000);

	// Count of the total entries
	auto totentries = d.Count();



	auto HCALm = d.Range(0, 1).Take<ROOT::VecOps::RVec<double>>("HCALm")->at(0);
	cout << HCALm << endl;
	auto HCALx = d.Range(0, 1).Take<ROOT::VecOps::RVec<double>>("HCALx")->at(0);
	cout << HCALx << endl;
	auto HCALy = d.Range(0, 1).Take<ROOT::VecOps::RVec<double>>("HCALy")->at(0);
	cout << HCALy << endl;
	


	// Show the properties of the data frame
	d.Describe().Print();
	std::cout << std::endl;
	// Alternative way: std::cout << d.Describe().AsString() << std::endl;

}