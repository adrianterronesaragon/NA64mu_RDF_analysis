
#include "histogram_plot.h"

#define str(s) (TString) #s

void macro_RDataFrame() {

	// Option for not showing plots after compiling
	gROOT->SetBatch(kTRUE);

	// To include headers from another folder
	//R__ADD_INCLUDE_PATH(<name of the path>);

	// Definition of the data frame
	ROOT::EnableImplicitMT(); // Tell ROOT you want to go parallel
	ROOT::RDataFrame d("ana_tree", "../Reco_2305_160gev_V1.1.root"); // Interface to TTree and TChain

	//ROOT::RDataFrame d0("ana_tree", "Reco_2305_160gev_V1.1.root");
	//auto d = d0.Range(0, 1000000);

	// Count of the total entries
	auto totentries = d.Count();





	
	// Filters
	//
	// Functions for the cut conditions
	auto cut_S0 = [](ROOT::VecOps::RVec<double>& col) { return col.at(0) > 0.15e-3; };
	auto cut_S1 = [](ROOT::VecOps::RVec<double>& col) { return col.at(1) > 0.15e-3; }; // auto cutGEM = [](ROOT::VecOps::RVec<double>& col) { return !col.empty(); }; not necessary
	auto cut_V0 = [](ROOT::VecOps::RVec<double>& col) { return col.at(4) > 0; };
	//
	auto cut_antiS0 = [](ROOT::VecOps::RVec<double>& col) { return col.at(0) <= 0.15e-3; };
	auto cut_antiS1 = [](ROOT::VecOps::RVec<double>& col) { return col.at(1) <= 0.15e-3; };
	auto cut_antiV0 = [](ROOT::VecOps::RVec<double>& col) { return col.at(4) <= 1.3e-3; };
	//
	// Apply the filters
	auto f_S0S1 = d.Filter(cut_S0, { "Triggers" }).Filter(cut_S1, { "Triggers" }); // auto f_S0S1_GEM1 = f_S0S1.Filter(cutGEM, { "GEM1x" }).Filter(cutGEM, { "GEM1y" }); not necessary
	auto f_S0S1antiV0 = d.Filter(cut_S0, { "Triggers" }).Filter(cut_S1, { "Triggers" }).Filter(cut_antiV0, { "Triggers" });
	auto f_antiS0S1 = d.Filter(cut_antiS0, { "Triggers" }).Filter(cut_antiS1, { "Triggers" });
	auto f_S0S1V0 = d.Filter(cut_S0, { "Triggers" }).Filter(cut_S1, { "Triggers" }).Filter(cut_V0, { "Triggers" });
	//
	// Count events
	auto c_S0S1 = f_S0S1.Count(); // auto c_S_GEM1 = f_S0S1_GEM1.Count(); not necessary
	auto c_S0S1antiV0 = f_S0S1antiV0.Count();
	auto c_antiS0S1 = f_antiS0S1.Count();
	auto c_S0S1V0 = f_S0S1V0.Count();






	// Create histograms
	//
	const int nbins = 400;
	//
	// Unfiltered
	auto hMM1x = d.Histo1D({ "Name_hMM1x","Title_MM1x",nbins,-80,80 }, "MM1x");
	auto hMM1y = d.Histo1D({ "Name_hMM1y", "Title_MM1y", nbins, -80, 80 }, "MM1y");
	auto hMM1xy = d.Histo2D({ "MM1", "MM1 events", nbins, -80, 80, nbins, -80, 80 }, "MM1x", "MM1y");
	//
	auto hMM2x = d.Histo1D({ "Name_hMM2x","Title_MM2x",nbins,-80,80 }, "MM2x");
	auto hMM2y = d.Histo1D({ "Name_hMM2y", "Title_MM2y", nbins, -80, 80 }, "MM2y");
	auto hMM2xy = d.Histo2D({ "MM2", "MM2 events", nbins, -80, 80, nbins, -80, 80 }, "MM2x", "MM2y");
	//
	auto hMM3x = d.Histo1D({ "Name_hMM3x","Title_MM3x",nbins,-80,80 }, "MM3x");
	auto hMM3y = d.Histo1D({ "Name_hMM3y", "Title_MM3y", nbins, -830, -670 }, "MM3y");
	auto hMM3xy = d.Histo2D({ "MM3", "MM3 events", nbins, -80, 80, nbins, -830, -670 }, "MM3x", "MM3y");
	//
	auto hMM4x = d.Histo1D({ "Name_hMM4x","Title_MM4x",nbins,-80,80 }, "MM4x");
	auto hMM4y = d.Histo1D({ "Name_hMM4y", "Title_MM4y", nbins, -850, -690 }, "MM4y");
	auto hMM4xy = d.Histo2D({ "MM4", "MM4 events", nbins, -80, 80, nbins, -850, -690 }, "MM4x", "MM4y");
	//
	auto hGEM1x = d.Histo1D({ "Name_hGEM1x","Title_GEM1x",nbins,-80, 80 }, "GEM1x");
	auto hGEM1y = d.Histo1D({ "Name_hGEM1y", "Title_GEM1y", nbins, -1500, -1340 }, "GEM1y");
	auto hGEM1xy = d.Histo2D({ "GEM1", "GEM1 events", nbins, -80, 80, nbins, -1500, -1340 }, "GEM1x", "GEM1y");
	//
	auto hGEM2xy = d.Histo2D({ "GEM2", "GEM2 events", nbins, -80, 80, nbins, -1565, -1405 }, "GEM2x", "GEM2y");
	//
	auto hGEM3xy = d.Histo2D({ "GEM3", "GEM3 events", nbins, -80, 80, nbins, -1600, -1440 }, "GEM3x", "GEM3y");
	//
	auto hGEM4xy = d.Histo2D({ "GEM4", "GEM4 events", nbins, -80, 80, nbins, -1625, -1465 }, "GEM4x", "GEM4y");
	//
	auto hMM5xy = d.Histo2D({ "MM5", "MM5 events", nbins, -130, 130, nbins, -1770, -1510 }, "MM5x", "MM5y");
	//
	auto hMM6xy = d.Histo2D({ "MM6", "MM6 events", nbins, -130, 130, nbins, -1780, -1520 }, "MM6x", "MM6y");
	//
	auto hMM7xy = d.Histo2D({ "MM7", "MM7 events", nbins, -130, 130, nbins, -1790, -1530 }, "MM7x", "MM7y");
	//
	auto hV0 = d.Define("V0", "Triggers[4]").Histo1D({ "Name_hV0","Title_V0", nbins, -1e-6, 1e-2 }, "V0");
	//
	// 
	auto hBeamEnergy0 = d.Histo1D({ "Name_hBeamEnergy0","Title_hBeamEnergy0", nbins, 0, 220 }, "BeamEnergy0");
	//
	auto hECALtot = d.Histo1D({ "Name_hECALtot","Title_hECALtot", nbins, -1e-6, 190 }, "ECALtot");
	//
	auto hVHCALtot = d.Histo1D({ "Name_hVHCALtot","Title_hVHCALtot", nbins, -1e-6, 190 }, "VHCALtot");
	//
	auto hHCAL0tot = d.Histo1D({ "Name_hHCAL0tot","Title_hHCAL0tot", nbins, -1e-6, 190 }, "HCAL0tot");
	//
	auto hHCAL1tot = d.Histo1D({ "Name_hHCAL1tot","Title_hHCAL1tot", nbins, -1e-6, 190 }, "HCAL1tot");
	//
	int n_ECALx = 5;
	int n_ECALy = 6;
	ROOT::RDF::RResultPtr<TH1D> hECALenergy[n_ECALx][n_ECALy];
	for (int i = 0; i < n_ECALx; i++) {
		for (int j = 0; j < n_ECALy; j++) {
			int k = i + (j * n_ECALx);
			TString k_str = (TString) to_string(k);
			TString i_str = (TString) to_string(i);
			TString j_str = (TString) to_string(j);
			TString str = (TString)"ECALenergy" + i_str + j_str;
			TString temp_str = (TString)"ECALenergy[" + k_str + "]";
			string_view col_str = (string_view)temp_str;
			hECALenergy[i][j] = d.Define(str, col_str).Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, -1e-6, 10 }, str);
		};
	};
	//
	int n_VHCALx = 4;
	int n_VHCALy = 4;
	ROOT::RDF::RResultPtr<TH1D> hVHCALenergy[n_VHCALx][n_VHCALy];
	for (int i = 0; i < n_VHCALx; i++) {
		for (int j = 0; j < n_VHCALy; j++) {
			int k = i + (j * n_VHCALx);
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"VHCALenergy" + i_str + j_str;
			TString temp_str = (TString)"VHCALenergy[" + k_str + "]";
			string_view col_str = (string_view) temp_str;
			hVHCALenergy[i][j] = d.Define(str, col_str).Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, -1e-6, 10 }, str);
		};
	};
	//
	int n_HCALx = 6;
	int n_HCALy = 3;
	ROOT::RDF::RResultPtr<TH1D> hHCAL0energy[n_HCALx][n_HCALy];
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			int k = i + (j * n_HCALx);
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"HCAL0energy" + i_str + j_str;
			TString temp_str = (TString)"HCALenergy[" + k_str + "]";
			string_view col_str = (string_view)temp_str;
			hHCAL0energy[i][j] = d.Define(str, col_str).Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, -1e-6, 10 }, str);
		};
	};
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1energy[n_HCALx][n_HCALy];
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			int k = i + (j * n_HCALx);
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			//cout << k_str + "\t" + i_str + "\t" + j_str << endl;
			TString str = (TString)"HCAL1energy" + i_str + j_str;
			TString temp_str = (TString)"HCALenergy[" + k_str + "]";
			string_view col_str = (string_view)temp_str;
			hHCAL1energy[i][j] = d.Define(str, col_str).Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, -1e-6, 10 }, str);
		};
	};
	// 
	// 
	// 
	// 
	// 
	//
	// Cut on S0 and S1
	auto hMM1xy_cut_S0S1 = f_S0S1.Histo2D({ "MM1 after cuts in S0 & S1", "MM1 events after cuts in S0 & S1", nbins, -80, 80, nbins, -80, 80 }, "MM1x", "MM1y");
	//
	auto hMM2xy_cut_S0S1 = f_S0S1.Histo2D({ "MM2 after cuts in S0 & S1", "MM2 events after cuts in S0 & S1", nbins, -80, 80, nbins, -80, 80 }, "MM2x", "MM2y");
	//
	auto hMM3xy_cut_S0S1 = f_S0S1.Histo2D({ "MM3 after cuts in S0 & S1", "MM3 events after cuts in S0 & S1", nbins, -80, 80, nbins, -830, -670 }, "MM3x", "MM3y");
	//
	auto hMM4xy_cut_S0S1 = f_S0S1.Histo2D({ "MM4 after cuts in S0 & S1", "MM4 events after cuts in S0 & S1", nbins, -80, 80, nbins, -850, -690 }, "MM4x", "MM4y");
	//
	auto hGEM1x_cut_S0S1 = f_S0S1.Histo1D({ "Name_hGEM1x_cut_S0S1","Title_GEM1x_cut_S0S1",nbins,-80,80 }, "GEM1x");
	auto hGEM1y_cut_S0S1 = f_S0S1.Histo1D({ "Name_hGEM1y_cut_S0S1", "Title_GEM1y_cut_S0S1", nbins, -1500, -1340 }, "GEM1y");
	auto hGEM1xy_cut_S0S1 = f_S0S1.Histo2D({ "GEM1 after cuts in S0 & S1", "GEM1 events after cuts in S0 & S1", nbins, -80, 80, nbins, -1500, -1340 }, "GEM1x", "GEM1y");
	//
	auto hGEM2xy_cut_S0S1 = f_S0S1.Histo2D({ "GEM2 after cuts in S0 & S1", "GEM2 events after cuts in S0 & S1", nbins, -80, 80, nbins, -1565, -1405 }, "GEM2x", "GEM2y");
	//
	auto hGEM3xy_cut_S0S1 = f_S0S1.Histo2D({ "GEM3 after cuts in S0 & S1", "GEM3 events after cuts in S0 & S1", nbins, -80, 80, nbins, -1600, -1440 }, "GEM3x", "GEM3y");
	//
	auto hGEM4xy_cut_S0S1 = f_S0S1.Histo2D({ "GEM4 after cuts in S0 & S1", "GEM4 events after cuts in S0 & S1", nbins, -80, 80, nbins, -1625, -1465 }, "GEM4x", "GEM4y");
	//
	auto hMM5xy_cut_S0S1 = f_S0S1.Histo2D({ "MM5 after cuts in S0 & S1", "MM5 events after cuts in S0 & S1", nbins, -130, 130, nbins, -1770, -1510 }, "MM5x", "MM5y");
	//
	auto hMM6xy_cut_S0S1 = f_S0S1.Histo2D({ "MM6 after cuts in S0 & S1", "MM6 events after cuts in S0 & S1", nbins, -130, 130, nbins, -1780, -1520 }, "MM6x", "MM6y");
	//
	auto hMM7xy_cut_S0S1 = f_S0S1.Histo2D({ "MM7 after cuts in S0 & S1", "MM7 events after cuts in S0 & S1", nbins, -130, 130, nbins, -1790, -1530 }, "MM7x", "MM7y");
	//
	auto hV0_cut_S0S1 = f_S0S1.Define("V0", "Triggers[4]").Histo1D({ "V0 after cuts in S0 & S1","V0 after cuts in S0 & S1",nbins,-1e-6,1e-2 }, "V0");
	//
	// 
	auto hECALtot_cut_S0S1 = f_S0S1.Histo1D({ "Name_hECALtot_cut_S0S1","Title_hECALtot_cut_S0S1",nbins,-1e-6,190 }, "ECALtot");
	//
	auto hVHCALtot_cut_S0S1 = f_S0S1.Histo1D({ "Name_hVHCALtot_cut_S0S1","Title_hVHCALtot_cut_S0S1",nbins,-1e-6,190 }, "VHCALtot");
	//
	auto hHCAL0tot_cut_S0S1 = f_S0S1.Histo1D({ "Name_hHCAL0tot_cut_S0S1","Title_hHCAL0tot_cut_S0S1",nbins,-1e-6,190 }, "HCAL0tot");
	//
	auto hHCAL1tot_cut_S0S1 = f_S0S1.Histo1D({ "Name_hHCAL1tot_cut_S0S1","Title_hHCAL1tot_cut_S0S1",nbins,-1e-6,190 }, "HCAL1tot");
	//
	// 
	// 
	// 
	// 
	// 
	// Cut on S0, S1 and antiV0
	auto hMM1xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM1 after cuts in S0, S1 & anti(V0)", "MM1 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -80, 80 }, "MM1x", "MM1y");
	//
	auto hMM2xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM2 after cuts in S0, S1 & anti(V0)", "MM2 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -80, 80 }, "MM2x", "MM2y");
	//
	auto hMM3xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM3 after cuts in S0, S1 & anti(V0)", "MM3 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -830, -670 }, "MM3x", "MM3y");
	//
	auto hMM4xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM4 after cuts in S0, S1 & anti(V0)", "MM4 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -850, -690 }, "MM4x", "MM4y");
	//
	auto hGEM1x_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "Name_hGEM1x_cut_S0S1antiV0","Title_GEM1x_cut_S0S1antiV0",nbins,-80,80 }, "GEM1x");
	auto hGEM1y_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "Name_hGEM1y_cut_S0S1antiV0", "Title_GEM1y_cut_S0S1antiV0", nbins, -1500, -1340 }, "GEM1y");
	auto hGEM1xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "GEM1 after cuts in S0, S1 & anti(V0)", "GEM1 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -1500, -1340 }, "GEM1x", "GEM1y");
	//
	auto hGEM2xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "GEM2 after cuts in S0, S1 & anti(V0)", "GEM2 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -1565, -1405 }, "GEM2x", "GEM2y");
	//
	auto hGEM3xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "GEM3 after cuts in S0, S1 & anti(V0)", "GEM3 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -1600, -1440 }, "GEM3x", "GEM3y");
	//
	auto hGEM4xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "GEM4 after cuts in S0, S1 & anti(V0)", "GEM4 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -1625, -1465 }, "GEM4x", "GEM4y");
	//
	auto hMM5xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM5 after cuts in S0, S1 & anti(V0)", "MM5 events after cuts in S0, S1 & anti(V0)", nbins, -130, 130, nbins, -1770, -1510 }, "MM5x", "MM5y");
	//
	auto hMM6xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM6 after cuts in S0, S1 & anti(V0)", "MM6 events after cuts in S0, S1 & anti(V0)", nbins, -130, 130, nbins, -1780, -1520 }, "MM6x", "MM6y");
	//
	auto hMM7xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM7 after cuts in S0, S1 & anti(V0)", "MM7 events after cuts in S0, S1 & anti(V0)", nbins, -130, 130, nbins, -1790, -1530 }, "MM7x", "MM7y");
	//
	auto hV0_cut_S0S1antiV0 = f_S0S1antiV0.Define("V0", "Triggers[4]").Histo1D({ "V0 after cuts in S0, S1 & anti(V0)","V0 after cuts in S0, S1 & anti(V0)",nbins,-1e-6,1e-2 }, "V0");
	//
	// 
	auto hECALtot_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "Name_hECALtot_cut_S0S1antiV0","Title_hECALtot_cut_S0S1antiV0",nbins,-1e-6,190 }, "ECALtot");
	//
	auto hVHCALtot_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "Name_hVHCALtot_cut_S0S1antiV0","Title_hVHCALtot_cut_S0S1antiV0",nbins,-1e-6,190 }, "VHCALtot");
	//
	auto hHCAL0tot_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "Name_hHCAL0tot_cut_S0S1antiV0","Title_hHCAL0tot_cut_S0S1antiV0",nbins,-1e-6,190 }, "HCAL0tot");
	//
	auto hHCAL1tot_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "Name_hHCAL1tot_cut_S0S1antiV0","Title_hHCAL1tot_cut_S0S1antiV0",nbins,-1e-6,190 }, "HCAL1tot");
	//
	ROOT::RDF::RResultPtr<TH1D> hECALenergy_cut_S0S1antiV0[n_ECALx][n_ECALy];
	for (int i = 0; i < n_ECALx; i++) {
		for (int j = 0; j < n_ECALy; j++) {
			int k = i + (j * n_ECALx);
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"ECALenergy_cut_S0S1antiV0" + i_str + j_str;
			TString temp_str = (TString)"ECALenergy[" + k_str + "]";
			string_view col_str = (string_view)temp_str;
			hECALenergy_cut_S0S1antiV0[i][j] = f_S0S1antiV0.Define(str, col_str).Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, -1e-6, 10 }, str);
		};
	};
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALenergy_cut_S0S1antiV0[n_VHCALx][n_VHCALy];
	for (int i = 0; i < n_VHCALx; i++) {
		for (int j = 0; j < n_VHCALy; j++) {
			int k = i + (j * n_VHCALx);
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"VHCALenergy_cut_S0S1antiV0" + i_str + j_str;
			TString temp_str = (TString)"VHCALenergy[" + k_str + "]";
			string_view col_str = (string_view)temp_str;
			hVHCALenergy_cut_S0S1antiV0[i][j] = f_S0S1antiV0.Define(str, col_str).Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, -1e-6, 10 }, str);
		};
	};
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0energy_cut_S0S1antiV0[n_HCALx][n_HCALy];
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			int k = i + (j * n_HCALx);
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"HCAL0energy_cut_S0S1antiV0" + i_str + j_str;
			TString temp_str = (TString)"HCALenergy[" + k_str + "]";
			string_view col_str = (string_view)temp_str;
			hHCAL0energy_cut_S0S1antiV0[i][j] = f_S0S1antiV0.Define(str, col_str).Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, -1e-6, 10 }, str);
		};
	};
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1energy_cut_S0S1antiV0[n_HCALx][n_HCALy];
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			int k = i + (j * n_HCALx);
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			//cout << k_str + "\t" + i_str + "\t" + j_str << endl;
			TString str = (TString)"HCAL1energy_cut_S0S1antiV0" + i_str + j_str;
			TString temp_str = (TString)"HCALenergy[" + k_str + "]";
			string_view col_str = (string_view)temp_str;
			hHCAL1energy_cut_S0S1antiV0[i][j] = f_S0S1antiV0.Define(str, col_str).Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, -1e-6, 10 }, str);
		};
	};
	//
	//
	//
	// 
	// 
	//
	// Cut on anti (S0, S1)
	auto hMM1xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM1 after cuts in anti(S0 & S1)", "MM1 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -80, 80 }, "MM1x", "MM1y");
	//
	auto hMM2xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM2 after cuts in anti(S0 & S1)", "MM2 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -80, 80 }, "MM2x", "MM2y");
	//
	auto hMM3xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM3 after cuts in anti(S0 & S1)", "MM3 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -830, -670 }, "MM3x", "MM3y");
	//
	auto hMM4xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM4 after cuts in anti(S0 & S1)", "MM4 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -850, -690 }, "MM4x", "MM4y");
	//
	auto hGEM1x_cut_antiS0S1 = f_antiS0S1.Histo1D({ "Name_hGEM1x_cut_antiS0S1", "Title_GEM1x_cut_antiS0S1",nbins,-80,80 }, "GEM1x");
	auto hGEM1y_cut_antiS0S1 = f_antiS0S1.Histo1D({ "Name_hGEM1y_cut_antiS0S1", "Title_GEM1y_cut_antiS0S1", nbins, -1500, -1340 }, "GEM1y");
	auto hGEM1xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "GEM1 after cuts in anti(S0 & S1)", "GEM1 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -1500, -1340 }, "GEM1x", "GEM1y");
	//
	auto hGEM2xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "GEM2 after cuts in anti(S0 & S1)", "GEM2 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -1565, -1405 }, "GEM2x", "GEM2y");
	//
	auto hGEM3xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "GEM3 after cuts in anti(S0 & S1)", "GEM3 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -1600, -1440 }, "GEM3x", "GEM3y");
	//
	auto hGEM4xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "GEM4 after cuts in anti(S0 & S1)", "GEM4 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -1625, -1465 }, "GEM4x", "GEM4y");
	//
	auto hMM5xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM5 after cuts in anti(S0 & S1)", "MM5 events after cuts in anti(S0 & S1)", nbins, -130, 130, nbins, -1770, -1510 }, "MM5x", "MM5y");
	//
	auto hMM6xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM6 after cuts in anti(S0 & S1)", "MM6 events after cuts in anti(S0 & S1)", nbins, -130, 130, nbins, -1780, -1520 }, "MM6x", "MM6y");
	//
	auto hMM7xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM7 after cuts in anti(S0 & S1)", "MM7 events after cuts in anti(S0 & S1)", nbins, -130, 130, nbins, -1790, -1530 }, "MM7x", "MM7y");
	//
	auto hV0_cut_antiS0S1 = f_antiS0S1.Define("V0", "Triggers[4]").Histo1D({ "V0 after cuts in anti(S0 & S1)","V0 after cuts in anti(S0 & S1)",nbins,-1e-6,1e-2 }, "V0");
	//
	// 
	auto hECALtot_cut_antiS0S1 = f_antiS0S1.Histo1D({ "Name_hECALtot_cut_antiS0S1","Title_hECALtot_cut_antiS0S1",nbins,-1e-6,190 }, "ECALtot");
	//
	auto hVHCALtot_cut_antiS0S1 = f_antiS0S1.Histo1D({ "Name_hVHCALtot_cut_antiS0S1","Title_hVHCALtot_cut_antiS0S1",nbins,-1e-6,190 }, "VHCALtot");
	//
	auto hHCAL0tot_cut_antiS0S1 = f_antiS0S1.Histo1D({ "Name_hHCAL0tot_cut_antiS0S1","Title_hHCAL0tot_cut_antiS0S1",nbins,-1e-6,190 }, "HCAL0tot");
	//
	auto hHCAL1tot_cut_antiS0S1 = f_antiS0S1.Histo1D({ "Name_hHCAL1tot_cut_antiS0S1","Title_hHCAL1tot_cut_antiS0S1",nbins,-1e-6,190 }, "HCAL1tot");
	//
	// 
	// 
	// 
	// 
	//
	// Cut on S0, S1 and V0
	auto hGEM1xy_cut_S0S1V0 = f_S0S1V0.Histo2D({ "GEM1 after cuts in S0, S1, V0", "GEM1 events after cuts in S0, S1, V0", nbins, -80, 80, nbins, -1500, -1340 }, "GEM1x", "GEM1y");
	//
	auto hV0_cut_S0S1V0 = f_S0S1V0.Define("V0", "Triggers[4]").Histo1D({ "Name_hV0","Title_V0",nbins,-1e-6,1e-2 }, "V0");
	//
	// 
	// 
	// 
	// 
	//
	// Other tests
	auto hHCAL1tot_HighEnergy = d.Filter("BeamEnergy0 < 160 && BeamEnergy0 > 140 && HCAL1tot > 160")
						.Histo1D({"HCAL1tot events with 140 GeV < BeamEnergy0 < 160 GeV ","HCAL1tot events with 140 GeV < BeamEnergy0 < 160 GeV",nbins,150,220}, "HCAL1tot");
	




	
	// Plots
	// 
	//histogram_plot(hMM1x, "RDF_hMM1x", "x[mm]", "Events");
	//histogram_plot(hMM1y, "RDF_hMM1y", "y[mm]", "Events");
	histogram_plot(hMM1xy, "RDF_hMM1xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	// 
	//histogram_plot(hMM2x, "RDF_hMM2x", "x[mm]", "Events");
	//histogram_plot(hMM2y, "RDF_hMM2y", "y[mm]", "Events");
	histogram_plot(hMM2xy, "RDF_hMM2xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	//histogram_plot(hMM3x, "RDF_hMM3x", "x[mm]", "Events");
	//histogram_plot(hMM3y, "RDF_hMM3y", "y[mm]", "Events");
	histogram_plot(hMM3xy, "RDF_hMM3xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	//histogram_plot(hMM4x, "RDF_hMM4x", "x[mm]", "Events");
	//histogram_plot(hMM4y, "RDF_hMM4y", "y[mm]", "Events");
	histogram_plot(hMM4xy, "RDF_hMM4xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	//histogram_plot(hGEM1x, "RDF_hGEM1x", "x[mm]", "Events");
	//histogram_plot(hGEM1y, "RDF_hGEM1y", "y[mm]", "Events");
	histogram_plot(hGEM1xy, "RDF_hGEM1xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.025, "col", "", "");
	//
	histogram_plot(hGEM2xy, "RDF_hGEM2xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hGEM3xy, "RDF_hGEM3xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hGEM4xy, "RDF_hGEM4xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hMM5xy, "RDF_hMM5xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hMM6xy, "RDF_hMM6xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hMM7xy, "RDF_hMM7xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hV0, "RDF_hV0", "Energy [GeV]", "Events", 1);
	//
	// 
	histogram_plot(hBeamEnergy0, "RDF_hBeamEnergy0", "Energy [GeV]", "Events", 0);
	//
	histogram_plot(hECALtot, "RDF_hECALtot", "Energy [GeV]", "Events", 1);
	//
	histogram_plot(hVHCALtot, "RDF_hVHCALtot", "Energy [GeV]", "Events", 1);
	//
	histogram_plot(hHCAL0tot, "RDF_hHCAL0tot", "Energy [GeV]", "Events", 1);
	//
	histogram_plot(hHCAL1tot, "RDF_hHCAL1tot", "Energy [GeV]", "Events", 1);
	//
	for (int i = 0; i < n_ECALx; i++) {
		for (int j = 0; j < n_ECALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			histogram_plot(hECALenergy[i][j], (TString)"RDF_hECALenergy" + i_str + j_str, "Energy [GeV]", "Events", 1);
		};
	};
	//
	for (int i = 0; i < n_VHCALx; i++) {
		for (int j = 0; j < n_VHCALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			histogram_plot(hVHCALenergy[i][j], (TString)"RDF_hVHCALenergy" + i_str + j_str, "Energy [GeV]", "Events", 1);
		};
	};
	//
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			histogram_plot(hHCAL0energy[i][j], (TString)"RDF_hHCAL0energy" + i_str + j_str, "Energy [GeV]", "Events", 1);
		};
	};
	//
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			histogram_plot(hHCAL1energy[i][j], (TString)"RDF_hHCAL1energy" + i_str + j_str, "Energy [GeV]", "Events", 1);
		};
	};
	//
	//
	// 
	// 
	// 
	//
	//histogram_plot(hMM1x_cut_S0S1, "RDF_hMM1x_cut_S0S1", "x[mm]", "Events");
	//histogram_plot(hMM1y_cut_S0S1, "RDF_hMM1y_cut_S0S1", "y[mm]", "Events");
	histogram_plot(hMM1xy_cut_S0S1, "RDF_hMM1xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	// 
	//histogram_plot(hMM2x_cut_S0S1, "RDF_hMM2x_cut_S0S1", "x[mm]", "Events");
	//histogram_plot(hMM2y_cut_S0S1, "RDF_hMM2y_cut_S0S1", "y[mm]", "Events");
	histogram_plot(hMM2xy_cut_S0S1, "RDF_hMM2xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	//histogram_plot(hMM3x_cut_S0S1, "RDF_hMM3x_cut_S0S1", "x[mm]", "Events");
	//histogram_plot(hMM3y_cut_S0S1, "RDF_hMM3y_cut_S0S1", "y[mm]", "Events");
	histogram_plot(hMM3xy_cut_S0S1, "RDF_hMM3xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	//histogram_plot(hMM4x_cut_S0S1, "RDF_hMM4x_cut_S0S1", "x[mm]", "Events");
	//histogram_plot(hMM4y_cut_S0S1, "RDF_hMM4y_cut_S0S1", "y[mm]", "Events");
	histogram_plot(hMM4xy_cut_S0S1, "RDF_hMM4xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	//histogram_plot(hGEM1x_cut_S0S1, "RDF_hGEM1x_cut_S0S1", "x[mm]", "Events");
	//histogram_plot(hGEM1y_cut_S0S1, "RDF_hGEM1y_cut_S0S1", "y[mm]", "Events");
	histogram_plot(hGEM1xy_cut_S0S1, "RDF_hGEM1xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.025, "col", "", "");
	//
	histogram_plot(hGEM2xy_cut_S0S1, "RDF_hGEM2xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hGEM3xy_cut_S0S1, "RDF_hGEM3xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hGEM4xy_cut_S0S1, "RDF_hGEM4xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hMM5xy_cut_S0S1, "RDF_hMM5xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hMM6xy_cut_S0S1, "RDF_hMM6xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hMM7xy_cut_S0S1, "RDF_hMM7xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hV0_cut_S0S1, "RDF_hV0_cut_S0S1", "Energy [GeV]", "Events", 1);
	//
	// 
	// 
	// 
	// 
	// 
	//histogram_plot(hMM1x_cut_S0S1antiV0, "RDF_hMM1x_cut_S0S1antiV0", "x[mm]", "Events");
	//histogram_plot(hMM1y_cut_S0S1antiV0, "RDF_hMM1y_cut_S0S1antiV0", "y[mm]", "Events");
	histogram_plot(hMM1xy_cut_S0S1antiV0, "RDF_hMM1xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	// 
	//histogram_plot(hMM2x_cut_S0S1antiV0, "RDF_hMM2x_cut_S0S1antiV0", "x[mm]", "Events");
	//histogram_plot(hMM2y_cut_S0S1antiV0, "RDF_hMM2y_cut_S0S1antiV0", "y[mm]", "Events");
	histogram_plot(hMM2xy_cut_S0S1antiV0, "RDF_hMM2xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	//histogram_plot(hMM3x_cut_S0S1antiV0, "RDF_hMM3x_cut_S0S1antiV0", "x[mm]", "Events");
	//histogram_plot(hMM3y_cut_S0S1antiV0, "RDF_hMM3y_cut_S0S1antiV0", "y[mm]", "Events");
	histogram_plot(hMM3xy_cut_S0S1antiV0, "RDF_hMM3xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	//histogram_plot(hMM4x_cut_S0S1antiV0, "RDF_hMM4x_cut_S0S1antiV0", "x[mm]", "Events");
	//histogram_plot(hMM4y_cut_S0S1antiV0, "RDF_hMM4y_cut_S0S1antiV0", "y[mm]", "Events");
	histogram_plot(hMM4xy_cut_S0S1antiV0, "RDF_hMM4xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	//histogram_plot(hGEM1x_cut_S0S1antiV0, "RDF_hGEM1x_cut_S0S1antiV0", "x[mm]", "Events");
	//histogram_plot(hGEM1y_cut_S0S1antiV0, "RDF_hGEM1y_cut_S0S1antiV0", "y[mm]", "Events");
	histogram_plot(hGEM1xy_cut_S0S1antiV0, "RDF_hGEM1xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.025, "col", "", "");
	//
	histogram_plot(hGEM2xy_cut_S0S1antiV0, "RDF_hGEM2xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hGEM3xy_cut_S0S1antiV0, "RDF_hGEM3xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hGEM4xy_cut_S0S1antiV0, "RDF_hGEM4xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hMM5xy_cut_S0S1antiV0, "RDF_hMM5xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hMM6xy_cut_S0S1antiV0, "RDF_hMM6xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hMM7xy_cut_S0S1antiV0, "RDF_hMM7xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hV0_cut_S0S1antiV0, "RDF_hV0_cut_S0S1antiV0", "Energy [GeV]", "Events", 1);
	//
	//
	histogram_plot(hECALtot_cut_S0S1antiV0, "RDF_hECALtot_cut_S0S1antiV0", "Energy [GeV]", "Events", 1);
	//
	histogram_plot(hVHCALtot_cut_S0S1antiV0, "RDF_hVHCALtot_cut_S0S1antiV0", "Energy [GeV]", "Events", 1);
	//
	histogram_plot(hHCAL0tot_cut_S0S1antiV0, "RDF_hHCAL0tot_cut_S0S1antiV0", "Energy [GeV]", "Events", 1);
	//
	histogram_plot(hHCAL1tot_cut_S0S1antiV0, "RDF_hHCAL1tot_cut_S0S1antiV0", "Energy [GeV]", "Events", 1);
	//
	for (int i = 0; i < n_ECALx; i++) {
		for (int j = 0; j < n_ECALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			histogram_plot(hECALenergy_cut_S0S1antiV0[i][j], (TString)"RDF_hECALenergy_cut_S0S1antiV0" + i_str + j_str, "Energy [GeV]", "Events", 1);
		};
	};
	//
	for (int i = 0; i < n_VHCALx; i++) {
		for (int j = 0; j < n_VHCALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			histogram_plot(hVHCALenergy_cut_S0S1antiV0[i][j], (TString)"RDF_hVHCALenergy_cut_S0S1antiV0" + i_str + j_str, "Energy [GeV]", "Events", 1);
		};
	};
	//
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			histogram_plot(hHCAL0energy_cut_S0S1antiV0[i][j], (TString)"RDF_hHCAL0energy_cut_S0S1antiV0" + i_str + j_str, "Energy [GeV]", "Events", 1);
		};
	};
	//
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			histogram_plot(hHCAL1energy_cut_S0S1antiV0[i][j], (TString)"RDF_hHCAL1energy_cut_S0S1antiV0" + i_str + j_str, "Energy [GeV]", "Events", 1);
		};
	};
	// 
	// 
	// 
	// 
	// 
	// 
	//histogram_plot(hMM1x_cut_antiS0S1, "RDF_hMM1x_cut_antiS0S1", "x[mm]", "Events");
	//histogram_plot(hMM1y_cut_antiS0S1, "RDF_hMM1y_cut_antiS0S1", "y[mm]", "Events");
	histogram_plot(hMM1xy_cut_antiS0S1, "RDF_hMM1xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	// 
	//histogram_plot(hMM2x_cut_antiS0S1, "RDF_hMM2x_cut_antiS0S1", "x[mm]", "Events");
	//histogram_plot(hMM2y_cut_antiS0S1, "RDF_hMM2y_cut_antiS0S1", "y[mm]", "Events");
	histogram_plot(hMM2xy_cut_antiS0S1, "RDF_hMM2xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	//histogram_plot(hMM3x_cut_antiS0S1, "RDF_hMM3x_cut_antiS0S1", "x[mm]", "Events");
	//histogram_plot(hMM3y_cut_antiS0S1, "RDF_hMM3y_cut_antiS0S1", "y[mm]", "Events");
	histogram_plot(hMM3xy_cut_antiS0S1, "RDF_hMM3xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	//histogram_plot(hMM4x_cut_antiS0S1, "RDF_hMM4x_cut_antiS0S1", "x[mm]", "Events");
	//histogram_plot(hMM4y_cut_antiS0S1, "RDF_hMM4y_cut_antiS0S1", "y[mm]", "Events");
	histogram_plot(hMM4xy_cut_antiS0S1, "RDF_hMM4xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	//histogram_plot(hGEM1x_cut_antiS0S1, "RDF_hGEM1x_cut_antiS0S1", "x[mm]", "Events");
	//histogram_plot(hGEM1y_cut_antiS0S1, "RDF_hGEM1y_cut_antiS0S1", "y[mm]", "Events");
	histogram_plot(hGEM1xy_cut_antiS0S1, "RDF_hGEM1xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.025, "col", "", "");
	//
	histogram_plot(hGEM2xy_cut_antiS0S1, "RDF_hGEM2xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hGEM3xy_cut_antiS0S1, "RDF_hGEM3xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hGEM4xy_cut_antiS0S1, "RDF_hGEM4xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hMM5xy_cut_antiS0S1, "RDF_hMM5xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hMM6xy_cut_antiS0S1, "RDF_hMM6xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hMM7xy_cut_antiS0S1, "RDF_hMM7xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
	//
	histogram_plot(hV0_cut_antiS0S1, "RDF_hV0_cut_antiS0S1", "Energy [GeV]", "Events", 1);
	//
	// 
	// 
	// 
	// 
	//
	histogram_plot(hGEM1xy_cut_S0S1V0, "RDF_hGEM1xy_cut_S0S1V0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.025, "col", "", "");
	//
	histogram_plot(hV0_cut_S0S1V0, "RDF_hV0_cut_S0S1V0", "Energy [GeV]", "Events", 1);
	//
	// 
	// 
	// 
	// 
	//
	histogram_plot(hHCAL1tot_HighEnergy, "RDF_hHCAL1tot_HighEnergy", "Energy [GeV]", "Events", 1);
	





	// Display number of events after every cut
	//
	std::cout << *totentries << " total entries" << std::endl;
	std::cout << *c_S0S1 << " entries passed the cut on S0 and S1" << std::endl; // std::cout << *c_S_GEM1 << " entries passed the cut on S0 and S1 and had a hit on GEM1" << std::endl; not necessary
	std::cout << *c_S0S1antiV0 << " entries passed the cut on S0, S1 and anti(V0)" << std::endl;
	std::cout << *c_antiS0S1 << " entries did not pass the cut on S0 and S1" << std::endl;
	std::cout << *c_S0S1 << " entries passed the cut on S0 and S1 and had a hit on V0" << std::endl;
	

	/*
	// Show the properties of the data frame
	d.Describe().Print();
	std::cout << std::endl;
	// Alternative way: std::cout << d.Describe().AsString() << std::endl;
	//*/

}