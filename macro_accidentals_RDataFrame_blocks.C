
#include "histogram_plot.h"

#define str(s) (TString) #s

bool digit_check(int digit, int number) {
	// Checks if the digit "digit" is in the integer number "number"
	bool b = false;
	int d;
	while (number != 0) {
		d = number % 10;
		if (d == digit) { b = true; }
		number /= 10;
	}
	return b;
}

void macro_accidentals_RDataFrame_blocks() {

	// Selection of blocks to run
	cout << endl;
	cout << "Please, select which blocks you want to run. Type" << endl;
	cout << "\t 0 \t to run all" << endl;
	cout << "\t 1 \t to run unfiltered" << endl;
	cout << "\t 2 \t to run the cut on S0 and S1" << endl;
	cout << "\t 3 \t to run the cut on S0, S1 and antiV0" << endl;
	cout << "\t 4 \t to run the cut on anti( S0, S1 )" << endl;
	cout << "\t 5 \t to run the cut on S0, S1 and V0" << endl;
	cout << "\t 6 \t to run the cut on S0, S1, S4, Smu and antiV0" << endl;
	cout << "\t 7 \t to run the cut on S4 and anti(S0, S1)" << endl;
	cout << "\t 9 \t to run tests" << endl;
	//cout << "\t 34 \t to run the cuts on S0, S1 and antiV0 and on anti( S0, S1 )" << endl;
	cout << "Your selection: ";
	int blocks = 0;
	cin >> blocks;
	cout << "Blocks run: ";


	bool bool_unfiltered = blocks == 0 || digit_check(1, blocks);
	bool bool_S0S1 = blocks == 0 || digit_check(2, blocks);
	bool bool_S0S1antiV0 = blocks == 0 || digit_check(3, blocks);
	bool bool_antiS0S1 = blocks == 0 || digit_check(4, blocks);
	bool bool_S0S1V0 = blocks == 0 || digit_check(5, blocks);
	bool bool_S0S1S4SmuantiV0 = blocks == 0 || digit_check(6, blocks);
	bool bool_S4antiS0S1 = blocks == 0 || digit_check(7, blocks);
	bool bool_tests = blocks == 0 || digit_check(9, blocks);


	time_t t0 = time(0);



	// Option for not showing plots after compiling
	gROOT->SetBatch(kTRUE);

	// To include headers from another folder
	//R__ADD_INCLUDE_PATH(<name of the path>);

	// Definition of the data frame
	ROOT::EnableImplicitMT(); // Tell ROOT you want to go parallel
	ROOT::RDataFrame d0("accidentals_tree", "../Reco_2305_160gev_V1.7_accidentals.root"); // Interface to TTree and TChain

	//ROOT::RDataFrame d0("ana_tree", "Reco_2305_160gev_V1.7.root");
	//auto d = d0.Range(0, 1000000);






	// General set up
	// 
	//
	// Binning
	const int nbins = 120;
	//
	// Histogram limits
	double xlow_MM5 = -174 - 10;
	double xup_MM5 = 79 + 10;
	double ylow_MM5 = -1681 - 96;
	double yup_MM5 = -1600 + 96;
	//
	double xlow_MM6 = -184 - 10;
	double xup_MM6 = 69 + 10;
	double ylow_MM6 = -1686 - 96;
	double yup_MM6 = -1605 + 96;
	//
	double xlow_MM7 = -197 - 10;
	double xup_MM7 = 56 + 10;
	double ylow_MM7 = -1701 - 96;
	double yup_MM7 = -1620 + 96;
	//
	double low_cals = -1e-6;
	double up_cals = 20;
	// 
	// Calorimeter cells
	int n_ECALx = 5;
	int n_ECALy = 6;
	//
	int n_VHCALx = 4;
	int n_VHCALy = 4;
	//
	int n_HCALx = 6;
	int n_HCALy = 3;
	//
	// Definition of new columns in the dataframe
	auto d = d0.Define("S0", "Triggers[0]").Define("S1", "Triggers[1]").Define("S4", "Triggers[2]").Define("Smu", "Triggers[3]").Define("V0", "Triggers[4]");
	//
	for (int i = 0; i < n_ECALx; i++) {
		for (int j = 0; j < n_ECALy; j++) {
			int k = i + (j * n_ECALx);
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"ECALenergy_" + i_str + j_str;
			TString temp_str = (TString)"ECALenergy[" + k_str + "]";
			string_view col_str = (string_view)temp_str;
			d = d.Define(str, col_str);
		}
	}
	//
	for (int i = 0; i < n_VHCALx; i++) {
		for (int j = 0; j < n_VHCALy; j++) {
			int k = i + (j * n_VHCALx);
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"VHCALenergy_" + i_str + j_str;
			TString temp_str = (TString)"VHCALenergy[" + k_str + "]";
			string_view col_str = (string_view)temp_str;
			d = d.Define(str, col_str);
		};
	};
	//
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			int k = i + (j * n_HCALx);
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"HCAL0energy_" + i_str + j_str;
			TString temp_str = (TString)"HCALenergy[" + k_str + "]";
			string_view col_str = (string_view)temp_str;
			d = d.Define(str, col_str);
		};
	};
	//
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			int k = i + (j * n_HCALx) + n_HCALx * n_HCALy;
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"HCAL1energy_" + i_str + j_str;
			TString temp_str = (TString)"HCALenergy[" + k_str + "]";
			string_view col_str = (string_view)temp_str;
			d = d.Define(str, col_str);
		};
	};
	// 
	// Functions for the cut conditions
	auto cut_S0 = [](ROOT::VecOps::RVec<double>& col) { return col.at(0) > 0.15e-3; };
	auto cut_S1 = [](ROOT::VecOps::RVec<double>& col) { return col.at(1) > 0.15e-3; };
	// auto cutGEM = [](ROOT::VecOps::RVec<double>& col) { return !col.empty(); }; not necessary
	auto cut_S4 = [](ROOT::VecOps::RVec<double>& col) { return col.at(2) > 0.00135; };
	auto cut_Smu = [](ROOT::VecOps::RVec<double>& col) { return col.at(3) > 0.00135; };
	auto cut_V0 = [](ROOT::VecOps::RVec<double>& col) { return col.at(4) > 0; };
	//
	auto cut_antiS0 = [](ROOT::VecOps::RVec<double>& col) { return col.at(0) <= 0.15e-3; };
	auto cut_antiS1 = [](ROOT::VecOps::RVec<double>& col) { return col.at(1) <= 0.15e-3; };
	auto cut_antiV0 = [](ROOT::VecOps::RVec<double>& col) { return col.at(4) <= 1.3e-3; };
	//
	// Count of the total entries
	auto totentries = d.Count();
	





	// Set ups
	// 
	// 
	// Unfiltered
	//
	// Histogram definitions
	ROOT::RDF::RResultPtr<TH1D> hMM1x;
	ROOT::RDF::RResultPtr<TH1D> hMM1y;
	ROOT::RDF::RResultPtr<TH2D> hMM1xy;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM2x;
	ROOT::RDF::RResultPtr<TH1D> hMM2y;
	ROOT::RDF::RResultPtr<TH2D> hMM2xy;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM3x;
	ROOT::RDF::RResultPtr<TH1D> hMM3y;
	ROOT::RDF::RResultPtr<TH2D> hMM3xy;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM4x;
	ROOT::RDF::RResultPtr<TH1D> hMM4y;
	ROOT::RDF::RResultPtr<TH2D> hMM4xy;
	//
	ROOT::RDF::RResultPtr<TH1D> hGEM1x;
	ROOT::RDF::RResultPtr<TH1D> hGEM1y;
	ROOT::RDF::RResultPtr<TH2D> hGEM1xy;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM2xy;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM3xy;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM4xy;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM5xy;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM6xy;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM7xy;
	//
	ROOT::RDF::RResultPtr<TH1D> hV0;
	//
	//
	//ROOT::RDF::RResultPtr<TH1D> hBeamEnergy0;
	//
	ROOT::RDF::RResultPtr<TH1D> hECALtot;
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALtot;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0tot;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1tot;
	//
	//
	ROOT::RDF::RResultPtr<TH1D> hECALenergy[n_ECALx][n_ECALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALenergy[n_VHCALx][n_VHCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0energy[n_HCALx][n_HCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1energy[n_HCALx][n_HCALy];
	//
	// 
	ROOT::RDF::RResultPtr<TH1D> hS4;
	//
	// 
	//
	if (bool_unfiltered) {

		cout << "unfiltered ";

		// Histograms
		hMM1x = d.Histo1D({ "Name_hMM1x","Title_MM1x",nbins,-80,80 }, "MM1x");
		hMM1y = d.Histo1D({ "Name_hMM1y", "Title_MM1y", nbins, -80, 80 }, "MM1y");
		hMM1xy = d.Histo2D({ "MM1", "MM1 events", nbins, -80, 80, nbins, -80, 80 }, "MM1x", "MM1y");
		//
		hMM2x = d.Histo1D({ "Name_hMM2x","Title_MM2x",nbins,-80,80 }, "MM2x");
		hMM2y = d.Histo1D({ "Name_hMM2y", "Title_MM2y", nbins, -80, 80 }, "MM2y");
		hMM2xy = d.Histo2D({ "MM2", "MM2 events", nbins, -80, 80, nbins, -80, 80 }, "MM2x", "MM2y");
		//
		hMM3x = d.Histo1D({ "Name_hMM3x","Title_MM3x",nbins,-80,80 }, "MM3x");
		hMM3y = d.Histo1D({ "Name_hMM3y", "Title_MM3y", nbins, -830, -670 }, "MM3y");
		hMM3xy = d.Histo2D({ "MM3", "MM3 events", nbins, -80, 80, nbins, -830, -670 }, "MM3x", "MM3y");
		//
		hMM4x = d.Histo1D({ "Name_hMM4x","Title_MM4x",nbins,-80,80 }, "MM4x");
		hMM4y = d.Histo1D({ "Name_hMM4y", "Title_MM4y", nbins, -850, -690 }, "MM4y");
		hMM4xy = d.Histo2D({ "MM4", "MM4 events", nbins, -80, 80, nbins, -850, -690 }, "MM4x", "MM4y");
		//
		hGEM1x = d.Histo1D({ "Name_hGEM1x","Title_GEM1x",nbins,-80, 80 }, "GEM1x");
		hGEM1y = d.Histo1D({ "Name_hGEM1y", "Title_GEM1y", nbins, -1500, -1340 }, "GEM1y");
		hGEM1xy = d.Histo2D({ "GEM1", "GEM1 events", nbins, -80, 80, nbins, -1500, -1340 }, "GEM1x", "GEM1y");
		//
		hGEM2xy = d.Histo2D({ "GEM2", "GEM2 events", nbins, -80, 80, nbins, -1565, -1405 }, "GEM2x", "GEM2y");
		//
		hGEM3xy = d.Histo2D({ "GEM3", "GEM3 events", nbins, -80, 80, nbins, -1600, -1440 }, "GEM3x", "GEM3y");
		//
		hGEM4xy = d.Histo2D({ "GEM4", "GEM4 events", nbins, -80, 80, nbins, -1625, -1465 }, "GEM4x", "GEM4y");
		//
		hMM5xy = d.Histo2D({ "MM5", "MM5 events", nbins, xlow_MM5, xup_MM5, nbins, ylow_MM5, yup_MM5 }, "MM5x", "MM5y");
		//
		hMM6xy = d.Histo2D({ "MM6", "MM6 events", nbins, xlow_MM6, xup_MM6, nbins, ylow_MM6, yup_MM6 }, "MM6x", "MM6y");
		//
		hMM7xy = d.Histo2D({ "MM7", "MM7 events", nbins, xlow_MM7, xup_MM7, nbins, ylow_MM7, yup_MM7 }, "MM7x", "MM7y");
		//
		hV0 = d.Histo1D({ "Name_hV0","Title_V0", nbins, low_cals, 1e-2 }, "V0");
		//
		// 
		//hBeamEnergy0 = d.Histo1D({ "Name_hBeamEnergy0","Title_hBeamEnergy0", nbins, 0, 220 }, "BeamEnergy0");
		//
		hECALtot = d.Histo1D({ "Name_hECALtot","Title_hECALtot", nbins, low_cals, up_cals }, "ECALtot");
		//
		hVHCALtot = d.Histo1D({ "Name_hVHCALtot","Title_hVHCALtot", nbins, low_cals, up_cals }, "VHCALtot");
		//
		hHCAL0tot = d.Histo1D({ "Name_hHCAL0tot","Title_hHCAL0tot", nbins, low_cals, up_cals }, "HCAL0tot");
		//
		hHCAL1tot = d.Histo1D({ "Name_hHCAL1tot","Title_hHCAL1tot", nbins, low_cals, up_cals }, "HCAL1tot");
		//
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				int k = i + (j * n_ECALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"ECALenergy_" + i_str + j_str;
				TString col = (TString)"ECALenergy_" + i_str + j_str;
				hECALenergy[i][j] = d.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_VHCALx; i++) {
			for (int j = 0; j < n_VHCALy; j++) {
				int k = i + (j * n_VHCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"VHCALenergy_" + i_str + j_str;
				TString col = (TString)"VHCALenergy_" + i_str + j_str;
				hVHCALenergy[i][j] = d.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				int k = i + (j * n_HCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"HCAL0energy_" + i_str + j_str;
				TString col = (TString)"HCAL0energy_" + i_str + j_str;
				hHCAL0energy[i][j] = d.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				int k = i + (j * n_HCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				//cout << k_str + "\t" + i_str + "\t" + j_str << endl;
				TString str = (TString)"HCAL1energy_" + i_str + j_str;
				TString col = (TString)"HCAL1energy_" + i_str + j_str;
				hHCAL1energy[i][j] = d.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		//
		hS4 = d.Histo1D({ "S4", "S4 events", nbins, -1000, 1000 }, "S4");

	}
	//
	// 
	// 
	// 
	// 
	// 
	// Cut on S0 and S1
	//
	// Histogram definitions
	ROOT::RDF::RResultPtr<TH1D> hMM1x_cut_S0S1;
	ROOT::RDF::RResultPtr<TH1D> hMM1y_cut_S0S1;
	ROOT::RDF::RResultPtr<TH2D> hMM1xy_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM2x_cut_S0S1;
	ROOT::RDF::RResultPtr<TH1D> hMM2y_cut_S0S1;
	ROOT::RDF::RResultPtr<TH2D> hMM2xy_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM3x_cut_S0S1;
	ROOT::RDF::RResultPtr<TH1D> hMM3y_cut_S0S1;
	ROOT::RDF::RResultPtr<TH2D> hMM3xy_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM4x_cut_S0S1;
	ROOT::RDF::RResultPtr<TH1D> hMM4y_cut_S0S1;
	ROOT::RDF::RResultPtr<TH2D> hMM4xy_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hGEM1x_cut_S0S1;
	ROOT::RDF::RResultPtr<TH1D> hGEM1y_cut_S0S1;
	ROOT::RDF::RResultPtr<TH2D> hGEM1xy_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM2xy_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM3xy_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM4xy_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM5xy_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM6xy_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM7xy_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hV0_cut_S0S1;
	//
	//
	//ROOT::RDF::RResultPtr<TH1D> hBeamEnergy0_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hECALtot_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALtot_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0tot_cut_S0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1tot_cut_S0S1;
	//
	//
	ROOT::RDF::RResultPtr<TH1D> hECALenergy_cut_S0S1[n_ECALx][n_ECALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALenergy_cut_S0S1[n_VHCALx][n_VHCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0energy_cut_S0S1[n_HCALx][n_HCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1energy_cut_S0S1[n_HCALx][n_HCALy];
	//
	// 
	//ROOT::RDF::RResultPtr<TH2D> hS4_cut_S0S1;
	//
	// 
	// 
	// Count definition
	ROOT::RDF::RResultPtr<ULong64_t> c_S0S1;
	//
	// 
	//
	if (bool_S0S1) {

		cout << "S0S1 ";

		// Filter
		auto f_S0S1 = d.Filter(cut_S0, { "Triggers" }).Filter(cut_S1, { "Triggers" }); // auto f_S0S1_GEM1 = f_S0S1.Filter(cutGEM, { "GEM1x" }).Filter(cutGEM, { "GEM1y" }); not necessary

		// Counts
		c_S0S1 = f_S0S1.Count();

		// Histograms
		hMM1xy_cut_S0S1 = f_S0S1.Histo2D({ "MM1 after cuts in S0 & S1", "MM1 events after cuts in S0 & S1", nbins, -80, 80, nbins, -80, 80 }, "MM1x", "MM1y");
		//
		hMM2xy_cut_S0S1 = f_S0S1.Histo2D({ "MM2 after cuts in S0 & S1", "MM2 events after cuts in S0 & S1", nbins, -80, 80, nbins, -80, 80 }, "MM2x", "MM2y");
		//
		hMM3xy_cut_S0S1 = f_S0S1.Histo2D({ "MM3 after cuts in S0 & S1", "MM3 events after cuts in S0 & S1", nbins, -80, 80, nbins, -830, -670 }, "MM3x", "MM3y");
		//
		hMM4xy_cut_S0S1 = f_S0S1.Histo2D({ "MM4 after cuts in S0 & S1", "MM4 events after cuts in S0 & S1", nbins, -80, 80, nbins, -850, -690 }, "MM4x", "MM4y");
		//
		hGEM1x_cut_S0S1 = f_S0S1.Histo1D({ "Name_hGEM1x_cut_S0S1","Title_GEM1x_cut_S0S1",nbins,-80,80 }, "GEM1x");
		hGEM1y_cut_S0S1 = f_S0S1.Histo1D({ "Name_hGEM1y_cut_S0S1", "Title_GEM1y_cut_S0S1", nbins, -1500, -1340 }, "GEM1y");
		hGEM1xy_cut_S0S1 = f_S0S1.Histo2D({ "GEM1 after cuts in S0 & S1", "GEM1 events after cuts in S0 & S1", nbins, -80, 80, nbins, -1500, -1340 }, "GEM1x", "GEM1y");
		//
		hGEM2xy_cut_S0S1 = f_S0S1.Histo2D({ "GEM2 after cuts in S0 & S1", "GEM2 events after cuts in S0 & S1", nbins, -80, 80, nbins, -1565, -1405 }, "GEM2x", "GEM2y");
		//
		hGEM3xy_cut_S0S1 = f_S0S1.Histo2D({ "GEM3 after cuts in S0 & S1", "GEM3 events after cuts in S0 & S1", nbins, -80, 80, nbins, -1600, -1440 }, "GEM3x", "GEM3y");
		//
		hGEM4xy_cut_S0S1 = f_S0S1.Histo2D({ "GEM4 after cuts in S0 & S1", "GEM4 events after cuts in S0 & S1", nbins, -80, 80, nbins, -1625, -1465 }, "GEM4x", "GEM4y");
		//
		hMM5xy_cut_S0S1 = f_S0S1.Histo2D({ "MM5 after cuts in S0 & S1", "MM5 events after cuts in S0 & S1", nbins, xlow_MM5, xup_MM5, nbins, ylow_MM5, yup_MM5 }, "MM5x", "MM5y");
		//
		hMM6xy_cut_S0S1 = f_S0S1.Histo2D({ "MM6 after cuts in S0 & S1", "MM6 events after cuts in S0 & S1", nbins, xlow_MM6, xup_MM6, nbins, ylow_MM6, yup_MM6 }, "MM6x", "MM6y");
		//
		hMM7xy_cut_S0S1 = f_S0S1.Histo2D({ "MM7 after cuts in S0 & S1", "MM7 events after cuts in S0 & S1", nbins, xlow_MM7, xup_MM7, nbins, ylow_MM7, yup_MM7 }, "MM7x", "MM7y");
		//
		hV0_cut_S0S1 = f_S0S1.Histo1D({ "V0 after cuts in S0 & S1","V0 after cuts in S0 & S1",nbins,low_cals,1e-2 }, "V0");
		//
		// 
		hECALtot_cut_S0S1 = f_S0S1.Histo1D({ "Name_hECALtot_cut_S0S1","Title_hECALtot_cut_S0S1",nbins,low_cals,up_cals }, "ECALtot");
		//
		hVHCALtot_cut_S0S1 = f_S0S1.Histo1D({ "Name_hVHCALtot_cut_S0S1","Title_hVHCALtot_cut_S0S1",nbins,low_cals,up_cals }, "VHCALtot");
		//
		hHCAL0tot_cut_S0S1 = f_S0S1.Histo1D({ "Name_hHCAL0tot_cut_S0S1","Title_hHCAL0tot_cut_S0S1",nbins,low_cals,up_cals }, "HCAL0tot");
		//
		hHCAL1tot_cut_S0S1 = f_S0S1.Histo1D({ "Name_hHCAL1tot_cut_S0S1","Title_hHCAL1tot_cut_S0S1",nbins,low_cals,up_cals }, "HCAL1tot");
		
	}
	//
	// 
	// 
	// 
	// 
	//
	// Cut on S0, S1 and antiV0
	//
	// Histogram definitions
	ROOT::RDF::RResultPtr<TH1D> hMM1x_cut_S0S1antiV0;
	ROOT::RDF::RResultPtr<TH1D> hMM1y_cut_S0S1antiV0;
	ROOT::RDF::RResultPtr<TH2D> hMM1xy_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM2x_cut_S0S1antiV0;
	ROOT::RDF::RResultPtr<TH1D> hMM2y_cut_S0S1antiV0;
	ROOT::RDF::RResultPtr<TH2D> hMM2xy_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM3x_cut_S0S1antiV0;
	ROOT::RDF::RResultPtr<TH1D> hMM3y_cut_S0S1antiV0;
	ROOT::RDF::RResultPtr<TH2D> hMM3xy_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM4x_cut_S0S1antiV0;
	ROOT::RDF::RResultPtr<TH1D> hMM4y_cut_S0S1antiV0;
	ROOT::RDF::RResultPtr<TH2D> hMM4xy_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hGEM1x_cut_S0S1antiV0;
	ROOT::RDF::RResultPtr<TH1D> hGEM1y_cut_S0S1antiV0;
	ROOT::RDF::RResultPtr<TH2D> hGEM1xy_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM2xy_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM3xy_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM4xy_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM5xy_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM6xy_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM7xy_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hV0_cut_S0S1antiV0;
	//
	//
	//ROOT::RDF::RResultPtr<TH1D> hBeamEnergy0_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hECALtot_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALtot_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0tot_cut_S0S1antiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1tot_cut_S0S1antiV0;
	//
	//
	ROOT::RDF::RResultPtr<TH1D> hECALenergy_cut_S0S1antiV0[n_ECALx][n_ECALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALenergy_cut_S0S1antiV0[n_VHCALx][n_VHCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0energy_cut_S0S1antiV0[n_HCALx][n_HCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1energy_cut_S0S1antiV0[n_HCALx][n_HCALy];
	//
	// 
	ROOT::RDF::RResultPtr<TH2D> hS4_cut_S0S1antiV0;
	//
	// 
	// 
	// Count definition
	ROOT::RDF::RResultPtr<ULong64_t> c_S0S1antiV0;
	//
	// 
	//
	if (bool_S0S1antiV0) {

		cout << "S0S1antiV0 ";

		// Filter
		auto f_S0S1antiV0 = d.Filter(cut_S0, { "Triggers" }).Filter(cut_S1, { "Triggers" }).Filter(cut_antiV0, { "Triggers" });

		// Counts
		c_S0S1antiV0 = f_S0S1antiV0.Count();

		// Histograms
		hMM1xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM1 after cuts in S0, S1 & anti(V0)", "MM1 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -80, 80 }, "MM1x", "MM1y");
		//
		hMM2xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM2 after cuts in S0, S1 & anti(V0)", "MM2 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -80, 80 }, "MM2x", "MM2y");
		//
		hMM3xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM3 after cuts in S0, S1 & anti(V0)", "MM3 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -830, -670 }, "MM3x", "MM3y");
		//
		hMM4xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM4 after cuts in S0, S1 & anti(V0)", "MM4 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -850, -690 }, "MM4x", "MM4y");
		//
		hGEM1x_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "Name_hGEM1x_cut_S0S1antiV0","Title_GEM1x_cut_S0S1antiV0",nbins,-80,80 }, "GEM1x");
		hGEM1y_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "Name_hGEM1y_cut_S0S1antiV0", "Title_GEM1y_cut_S0S1antiV0", nbins, -1500, -1340 }, "GEM1y");
		hGEM1xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "GEM1 after cuts in S0, S1 & anti(V0)", "GEM1 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -1500, -1340 }, "GEM1x", "GEM1y");
		//
		hGEM2xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "GEM2 after cuts in S0, S1 & anti(V0)", "GEM2 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -1565, -1405 }, "GEM2x", "GEM2y");
		//
		hGEM3xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "GEM3 after cuts in S0, S1 & anti(V0)", "GEM3 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -1600, -1440 }, "GEM3x", "GEM3y");
		//
		hGEM4xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "GEM4 after cuts in S0, S1 & anti(V0)", "GEM4 events after cuts in S0, S1 & anti(V0)", nbins, -80, 80, nbins, -1625, -1465 }, "GEM4x", "GEM4y");
		//
		hMM5xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM5 after cuts in S0, S1 & anti(V0)", "MM5 events after cuts in S0, S1 & anti(V0)", nbins, xlow_MM5, xup_MM5, nbins, ylow_MM5, yup_MM5 }, "MM5x", "MM5y");
		//
		hMM6xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM6 after cuts in S0, S1 & anti(V0)", "MM6 events after cuts in S0, S1 & anti(V0)", nbins, xlow_MM6, xup_MM6, nbins, ylow_MM6, yup_MM6 }, "MM6x", "MM6y");
		//
		hMM7xy_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "MM7 after cuts in S0, S1 & anti(V0)", "MM7 events after cuts in S0, S1 & anti(V0)", nbins, xlow_MM7, xup_MM7, nbins, ylow_MM7, yup_MM7 }, "MM7x", "MM7y");
		//
		hV0_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "V0 after cuts in S0, S1 & anti(V0)","V0 after cuts in S0, S1 & anti(V0)",nbins,low_cals,1e-2 }, "V0");
		//
		// 
		hECALtot_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "Name_hECALtot_cut_S0S1antiV0","Title_hECALtot_cut_S0S1antiV0",nbins,low_cals,up_cals }, "ECALtot");
		//
		hVHCALtot_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "Name_hVHCALtot_cut_S0S1antiV0","Title_hVHCALtot_cut_S0S1antiV0",nbins,low_cals,up_cals }, "VHCALtot");
		//
		hHCAL0tot_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "Name_hHCAL0tot_cut_S0S1antiV0","Title_hHCAL0tot_cut_S0S1antiV0",nbins,low_cals,up_cals }, "HCAL0tot");
		//
		hHCAL1tot_cut_S0S1antiV0 = f_S0S1antiV0.Histo1D({ "Name_hHCAL1tot_cut_S0S1antiV0","Title_hHCAL1tot_cut_S0S1antiV0",nbins,low_cals,up_cals }, "HCAL1tot");
		//
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				int k = i + (j * n_ECALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"ECALenergy_cut_S0S1antiV0_" + i_str + j_str;
				TString col = (TString)"ECALenergy_" + i_str + j_str;
				hECALenergy_cut_S0S1antiV0[i][j] = f_S0S1antiV0.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_VHCALx; i++) {
			for (int j = 0; j < n_VHCALy; j++) {
				int k = i + (j * n_VHCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"VHCALenergy_cut_S0S1antiV0_" + i_str + j_str;
				TString col = (TString)"VHCALenergy_" + i_str + j_str;
				hVHCALenergy_cut_S0S1antiV0[i][j] = f_S0S1antiV0.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				int k = i + (j * n_HCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"HCAL0energy_cut_S0S1antiV0_" + i_str + j_str;
				TString col = (TString)"HCAL0energy_" + i_str + j_str;
				hHCAL0energy_cut_S0S1antiV0[i][j] = f_S0S1antiV0.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				int k = i + (j * n_HCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				//cout << k_str + "\t" + i_str + "\t" + j_str << endl;
				TString str = (TString)"HCAL1energy_cut_S0S1antiV0_" + i_str + j_str;
				TString col = (TString)"HCAL1energy_" + i_str + j_str;
				hHCAL1energy_cut_S0S1antiV0[i][j] = f_S0S1antiV0.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		//
		//hS4_cut_S0S1antiV0 = f_S0S1antiV0.Histo2D({ "S4_cut_S0S1antiV0", "S4 events_cut_S0S1antiV0", nbins, -1000, 1000, nbins, -1770, -1550 }, "s4x", "s4y");
		
	}
	//
	// 
	// 
	// 
	// 
	// 
	// Cut on anti( S0, S1 )
	//
	// Histogram definitions
	ROOT::RDF::RResultPtr<TH1D> hMM1x_cut_antiS0S1;
	ROOT::RDF::RResultPtr<TH1D> hMM1y_cut_antiS0S1;
	ROOT::RDF::RResultPtr<TH2D> hMM1xy_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM2x_cut_antiS0S1;
	ROOT::RDF::RResultPtr<TH1D> hMM2y_cut_antiS0S1;
	ROOT::RDF::RResultPtr<TH2D> hMM2xy_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM3x_cut_antiS0S1;
	ROOT::RDF::RResultPtr<TH1D> hMM3y_cut_antiS0S1;
	ROOT::RDF::RResultPtr<TH2D> hMM3xy_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM4x_cut_antiS0S1;
	ROOT::RDF::RResultPtr<TH1D> hMM4y_cut_antiS0S1;
	ROOT::RDF::RResultPtr<TH2D> hMM4xy_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hGEM1x_cut_antiS0S1;
	ROOT::RDF::RResultPtr<TH1D> hGEM1y_cut_antiS0S1;
	ROOT::RDF::RResultPtr<TH2D> hGEM1xy_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM2xy_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM3xy_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM4xy_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM5xy_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM6xy_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM7xy_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hV0_cut_antiS0S1;
	//
	//
	//ROOT::RDF::RResultPtr<TH1D> hBeamEnergy0_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hECALtot_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALtot_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0tot_cut_antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1tot_cut_antiS0S1;
	//
	//
	ROOT::RDF::RResultPtr<TH1D> hECALenergy_cut_antiS0S1[n_ECALx][n_ECALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALenergy_cut_antiS0S1[n_VHCALx][n_VHCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0energy_cut_antiS0S1[n_HCALx][n_HCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1energy_cut_antiS0S1[n_HCALx][n_HCALy];
	//
	// 
	ROOT::RDF::RResultPtr<TH2D> hS4_cut_antiS0S1;
	//
	// 
	// 
	// Count definition
	ROOT::RDF::RResultPtr<ULong64_t> c_antiS0S1;
	//
	// 
	//
	if (bool_antiS0S1) {

		cout << "anti(S0S1) ";

		// Filter
		auto f_antiS0S1 = d.Filter(cut_antiS0, { "Triggers" }).Filter(cut_antiS1, { "Triggers" });

		// Counts
		c_antiS0S1 = f_antiS0S1.Count();

		// Histograms
		hMM1xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM1 after cuts in anti(S0 & S1)", "MM1 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -80, 80 }, "MM1x", "MM1y");
		//
		hMM2xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM2 after cuts in anti(S0 & S1)", "MM2 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -80, 80 }, "MM2x", "MM2y");
		//
		hMM3xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM3 after cuts in anti(S0 & S1)", "MM3 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -830, -670 }, "MM3x", "MM3y");
		//
		hMM4xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM4 after cuts in anti(S0 & S1)", "MM4 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -850, -690 }, "MM4x", "MM4y");
		//
		hGEM1x_cut_antiS0S1 = f_antiS0S1.Histo1D({ "Name_hGEM1x_cut_antiS0S1", "Title_GEM1x_cut_antiS0S1",nbins,-80,80 }, "GEM1x");
		hGEM1y_cut_antiS0S1 = f_antiS0S1.Histo1D({ "Name_hGEM1y_cut_antiS0S1", "Title_GEM1y_cut_antiS0S1", nbins, -1500, -1340 }, "GEM1y");
		hGEM1xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "GEM1 after cuts in anti(S0 & S1)", "GEM1 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -1500, -1340 }, "GEM1x", "GEM1y");
		//
		hGEM2xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "GEM2 after cuts in anti(S0 & S1)", "GEM2 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -1565, -1405 }, "GEM2x", "GEM2y");
		//
		hGEM3xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "GEM3 after cuts in anti(S0 & S1)", "GEM3 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -1600, -1440 }, "GEM3x", "GEM3y");
		//
		hGEM4xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "GEM4 after cuts in anti(S0 & S1)", "GEM4 events after cuts in anti(S0 & S1)", nbins, -80, 80, nbins, -1625, -1465 }, "GEM4x", "GEM4y");
		//
		hMM5xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM5 after cuts in anti(S0 & S1)", "MM5 events after cuts in anti(S0 & S1)", nbins, xlow_MM5, xup_MM5, nbins, ylow_MM5, yup_MM5 }, "MM5x", "MM5y");
		//
		hMM6xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM6 after cuts in anti(S0 & S1)", "MM6 events after cuts in anti(S0 & S1)", nbins, xlow_MM6, xup_MM6, nbins, ylow_MM6, yup_MM6 }, "MM6x", "MM6y");
		//
		hMM7xy_cut_antiS0S1 = f_antiS0S1.Histo2D({ "MM7 after cuts in anti(S0 & S1)", "MM7 events after cuts in anti(S0 & S1)", nbins, xlow_MM7, xup_MM7, nbins, ylow_MM7, yup_MM7 }, "MM7x", "MM7y");
		//
		hV0_cut_antiS0S1 = f_antiS0S1.Histo1D({ "V0 after cuts in anti(S0 & S1)","V0 after cuts in anti(S0 & S1)",nbins,low_cals,1e-2 }, "V0");
		//
		// 
		hECALtot_cut_antiS0S1 = f_antiS0S1.Histo1D({ "Name_hECALtot_cut_antiS0S1","Title_hECALtot_cut_antiS0S1",nbins,low_cals,up_cals }, "ECALtot");
		//
		hVHCALtot_cut_antiS0S1 = f_antiS0S1.Histo1D({ "Name_hVHCALtot_cut_antiS0S1","Title_hVHCALtot_cut_antiS0S1",nbins,low_cals,up_cals }, "VHCALtot");
		//
		hHCAL0tot_cut_antiS0S1 = f_antiS0S1.Histo1D({ "Name_hHCAL0tot_cut_antiS0S1","Title_hHCAL0tot_cut_antiS0S1",nbins,low_cals,up_cals }, "HCAL0tot");
		//
		hHCAL1tot_cut_antiS0S1 = f_antiS0S1.Histo1D({ "Name_hHCAL1tot_cut_antiS0S1","Title_hHCAL1tot_cut_antiS0S1",nbins,low_cals,up_cals }, "HCAL1tot");
		//
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				int k = i + (j * n_ECALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"ECALenergy_cut_antiS0S1_" + i_str + j_str;
				TString col = (TString)"ECALenergy_" + i_str + j_str;
				hECALenergy_cut_antiS0S1[i][j] = f_antiS0S1.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_VHCALx; i++) {
			for (int j = 0; j < n_VHCALy; j++) {
				int k = i + (j * n_VHCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"VHCALenergy_cut_antiS0S1_" + i_str + j_str;
				TString col = (TString)"VHCALenergy_" + i_str + j_str;
				hVHCALenergy_cut_antiS0S1[i][j] = f_antiS0S1.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				int k = i + (j * n_HCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"HCAL0energy_cut_antiS0S1_" + i_str + j_str;
				TString col = (TString)"HCAL0energy_" + i_str + j_str;
				hHCAL0energy_cut_antiS0S1[i][j] = f_antiS0S1.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				int k = i + (j * n_HCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				//cout << k_str + "\t" + i_str + "\t" + j_str << endl;
				TString str = (TString)"HCAL1energy_cut_antiS0S1_" + i_str + j_str;
				TString col = (TString)"HCAL1energy_" + i_str + j_str;
				hHCAL1energy_cut_antiS0S1[i][j] = f_antiS0S1.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		//
		//hS4_cut_antiS0S1 = f_antiS0S1.Histo2D({ "S4_cut_antiS0S1", "S4 events_cut_antiS0S1", nbins, -1000, 1000, nbins, -1770, -1550 }, "s4x", "s4y");
		
	}
	//
	// 
	// 
	// 
	// 
	//
	// Cut on S0, S1 and V0
	//
	// Histogram definitions
	ROOT::RDF::RResultPtr<TH1D> hMM1x_cut_S0S1V0;
	ROOT::RDF::RResultPtr<TH1D> hMM1y_cut_S0S1V0;
	ROOT::RDF::RResultPtr<TH2D> hMM1xy_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM2x_cut_S0S1V0;
	ROOT::RDF::RResultPtr<TH1D> hMM2y_cut_S0S1V0;
	ROOT::RDF::RResultPtr<TH2D> hMM2xy_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM3x_cut_S0S1V0;
	ROOT::RDF::RResultPtr<TH1D> hMM3y_cut_S0S1V0;
	ROOT::RDF::RResultPtr<TH2D> hMM3xy_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM4x_cut_S0S1V0;
	ROOT::RDF::RResultPtr<TH1D> hMM4y_cut_S0S1V0;
	ROOT::RDF::RResultPtr<TH2D> hMM4xy_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH1D> hGEM1x_cut_S0S1V0;
	ROOT::RDF::RResultPtr<TH1D> hGEM1y_cut_S0S1V0;
	ROOT::RDF::RResultPtr<TH2D> hGEM1xy_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM2xy_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM3xy_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM4xy_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM5xy_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM6xy_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM7xy_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH1D> hV0_cut_S0S1V0;
	//
	//
	//ROOT::RDF::RResultPtr<TH1D> hBeamEnergy0_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH1D> hECALtot_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALtot_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0tot_cut_S0S1V0;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1tot_cut_S0S1V0;
	//
	//
	ROOT::RDF::RResultPtr<TH1D> hECALenergy_cut_S0S1V0[n_ECALx][n_ECALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALenergy_cut_S0S1V0[n_VHCALx][n_VHCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0energy_cut_S0S1V0[n_HCALx][n_HCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1energy_cut_S0S1V0[n_HCALx][n_HCALy];
	//
	// 
	// 
	// Count definition
	ROOT::RDF::RResultPtr<ULong64_t> c_S0S1V0;
	//
	// 
	//
	if (bool_S0S1V0) {

		cout << "S0S1V0 ";

		// Filter
		auto f_S0S1V0 = d.Filter(cut_S0, { "Triggers" }).Filter(cut_S1, { "Triggers" }).Filter(cut_V0, { "Triggers" });

		// Counts
		c_S0S1V0 = f_S0S1V0.Count();

		// Histograms
		hGEM1xy_cut_S0S1V0 = f_S0S1V0.Histo2D({ "GEM1 after cuts in S0, S1, V0", "GEM1 events after cuts in S0, S1, V0", nbins, -80, 80, nbins, -1500, -1340 }, "GEM1x", "GEM1y");
		//
		hV0_cut_S0S1V0 = f_S0S1V0.Histo1D({ "Name_hV0","Title_V0",nbins,low_cals,1e-2 }, "V0");

	}
	//
	// 
	// 
	// 
	// 
	// 
	// Cut on S0, S1, S4, Smu and antiV0
	//
	// Histogram definitions
	ROOT::RDF::RResultPtr<TH1D> hMM1x_cut_S0S1S4SmuantiV0;
	ROOT::RDF::RResultPtr<TH1D> hMM1y_cut_S0S1S4SmuantiV0;
	ROOT::RDF::RResultPtr<TH2D> hMM1xy_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM2x_cut_S0S1S4SmuantiV0;
	ROOT::RDF::RResultPtr<TH1D> hMM2y_cut_S0S1S4SmuantiV0;
	ROOT::RDF::RResultPtr<TH2D> hMM2xy_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM3x_cut_S0S1S4SmuantiV0;
	ROOT::RDF::RResultPtr<TH1D> hMM3y_cut_S0S1S4SmuantiV0;
	ROOT::RDF::RResultPtr<TH2D> hMM3xy_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM4x_cut_S0S1S4SmuantiV0;
	ROOT::RDF::RResultPtr<TH1D> hMM4y_cut_S0S1S4SmuantiV0;
	ROOT::RDF::RResultPtr<TH2D> hMM4xy_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hGEM1x_cut_S0S1S4SmuantiV0;
	ROOT::RDF::RResultPtr<TH1D> hGEM1y_cut_S0S1S4SmuantiV0;
	ROOT::RDF::RResultPtr<TH2D> hGEM1xy_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM2xy_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM3xy_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM4xy_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM5xy_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM6xy_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM7xy_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hV0_cut_S0S1S4SmuantiV0;
	//
	//
	//ROOT::RDF::RResultPtr<TH1D> hBeamEnergy0_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hECALtot_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALtot_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0tot_cut_S0S1S4SmuantiV0;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1tot_cut_S0S1S4SmuantiV0;
	//
	//
	ROOT::RDF::RResultPtr<TH1D> hECALenergy_cut_S0S1S4SmuantiV0[n_ECALx][n_ECALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALenergy_cut_S0S1S4SmuantiV0[n_VHCALx][n_VHCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0energy_cut_S0S1S4SmuantiV0[n_HCALx][n_HCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1energy_cut_S0S1S4SmuantiV0[n_HCALx][n_HCALy];
	//
	// 
	ROOT::RDF::RResultPtr<TH2D> hS4_cut_S0S1S4SmuantiV0;
	//
	// 
	// 
	// Count definition
	ROOT::RDF::RResultPtr<ULong64_t> c_S0S1S4SmuantiV0;
	//
	// 
	//
	if (bool_S0S1S4SmuantiV0) {

		cout << "S0S1S4SmuantiV0 ";

		// Filter
		auto f_S0S1S4SmuantiV0 = d.Filter(cut_S0, { "Triggers" }).Filter(cut_S1, { "Triggers" }).Filter(cut_S4, { "Triggers" }).Filter(cut_Smu, { "Triggers" }).Filter(cut_antiV0, { "Triggers" });

		// Counts
		c_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Count();

		// Histograms
		hMM1xy_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo2D({ "MM1 after cuts in S0, S1, anti(V0), S4, Smu", "MM1 events after cuts in S0, S1, anti(V0), S4, Smu", nbins, -80, 80, nbins, -80, 80 }, "MM1x", "MM1y");
		//
		hMM2xy_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo2D({ "MM2 after cuts in S0, S1, anti(V0), S4, Smu", "MM2 events after cuts in S0, S1, anti(V0), S4, Smu", nbins, -80, 80, nbins, -80, 80 }, "MM2x", "MM2y");
		//
		hMM3xy_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo2D({ "MM3 after cuts in S0, S1, anti(V0), S4, Smu", "MM3 events after cuts in S0, S1, anti(V0), S4, Smu", nbins, -80, 80, nbins, -830, -670 }, "MM3x", "MM3y");
		//
		hMM4xy_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo2D({ "MM4 after cuts in S0, S1, anti(V0), S4, Smu", "MM4 events after cuts in S0, S1, anti(V0), S4, Smu", nbins, -80, 80, nbins, -850, -690 }, "MM4x", "MM4y");
		//
		hGEM1x_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo1D({ "Name_hGEM1x_cut_S0S1S4SmuantiV0","Title_GEM1x_cut_S0S1S4SmuantiV0",nbins,-80,80 }, "GEM1x");
		hGEM1y_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo1D({ "Name_hGEM1y_cut_S0S1S4SmuantiV0", "Title_GEM1y_cut_S0S1S4SmuantiV0", nbins, -1500, -1340 }, "GEM1y");
		hGEM1xy_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo2D({ "GEM1 after cuts in S0, S1, anti(V0), S4, Smu", "GEM1 events after cuts in S0, S1, anti(V0), S4, Smu", nbins, -80, 80, nbins, -1500, -1340 }, "GEM1x", "GEM1y");
		//
		hGEM2xy_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo2D({ "GEM2 after cuts in S0, S1, anti(V0), S4, Smu", "GEM2 events after cuts in S0, S1, anti(V0), S4, Smu", nbins, -80, 80, nbins, -1565, -1405 }, "GEM2x", "GEM2y");
		//
		hGEM3xy_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo2D({ "GEM3 after cuts in S0, S1, anti(V0), S4, Smu", "GEM3 events after cuts in S0, S1, anti(V0), S4, Smu", nbins, -80, 80, nbins, -1600, -1440 }, "GEM3x", "GEM3y");
		//
		hGEM4xy_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo2D({ "GEM4 after cuts in S0, S1, anti(V0), S4, Smu", "GEM4 events after cuts in S0, S1, anti(V0), S4, Smu", nbins, -80, 80, nbins, -1625, -1465 }, "GEM4x", "GEM4y");
		//
		hMM5xy_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo2D({ "MM5 after cuts in S0, S1, anti(V0), S4, Smu", "MM5 events after cuts in S0, S1, anti(V0), S4, Smu", nbins, xlow_MM5, xup_MM5, nbins, ylow_MM5, yup_MM5 }, "MM5x", "MM5y");
		//
		hMM6xy_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo2D({ "MM6 after cuts in S0, S1, anti(V0), S4, Smu", "MM6 events after cuts in S0, S1, anti(V0), S4, Smu", nbins, xlow_MM6, xup_MM6, nbins, ylow_MM6, yup_MM6 }, "MM6x", "MM6y");
		//
		hMM7xy_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo2D({ "MM7 after cuts in S0, S1, anti(V0), S4, Smu", "MM7 events after cuts in S0, S1, anti(V0), S4, Smu", nbins, xlow_MM7, xup_MM7, nbins, ylow_MM7, yup_MM7 }, "MM7x", "MM7y");
		//
		hV0_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo1D({ "V0 after cuts in S0, S1, anti(V0), S4, Smu","V0 after cuts in S0, S1, anti(V0), S4, Smu",nbins,low_cals,1e-2 }, "V0");
		//
		// 
		hECALtot_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo1D({ "Name_hECALtot_cut_S0S1S4SmuantiV0","Title_hECALtot_cut_S0S1S4SmuantiV0",nbins,low_cals,up_cals }, "ECALtot");
		//
		hVHCALtot_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo1D({ "Name_hVHCALtot_cut_S0S1S4SmuantiV0","Title_hVHCALtot_cut_S0S1S4SmuantiV0",nbins,low_cals,up_cals }, "VHCALtot");
		//
		hHCAL0tot_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo1D({ "Name_hHCAL0tot_cut_S0S1S4SmuantiV0","Title_hHCAL0tot_cut_S0S1S4SmuantiV0",nbins,low_cals,up_cals }, "HCAL0tot");
		//
		hHCAL1tot_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo1D({ "Name_hHCAL1tot_cut_S0S1S4SmuantiV0","Title_hHCAL1tot_cut_S0S1S4SmuantiV0",nbins,low_cals,up_cals }, "HCAL1tot");
		//
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				int k = i + (j * n_ECALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"ECALenergy_cut_S0S1S4SmuantiV0_" + i_str + j_str;
				TString col = (TString)"ECALenergy_" + i_str + j_str;
				hECALenergy_cut_S0S1S4SmuantiV0[i][j] = f_S0S1S4SmuantiV0.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_VHCALx; i++) {
			for (int j = 0; j < n_VHCALy; j++) {
				int k = i + (j * n_VHCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"VHCALenergy_cut_S0S1S4SmuantiV0_" + i_str + j_str;
				TString col = (TString)"VHCALenergy_" + i_str + j_str;
				hVHCALenergy_cut_S0S1S4SmuantiV0[i][j] = f_S0S1S4SmuantiV0.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				int k = i + (j * n_HCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"HCAL0energy_cut_S0S1S4SmuantiV0_" + i_str + j_str;
				TString col = (TString)"HCAL0energy_" + i_str + j_str;
				hHCAL0energy_cut_S0S1S4SmuantiV0[i][j] = f_S0S1S4SmuantiV0.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				int k = i + (j * n_HCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				//cout << k_str + "\t" + i_str + "\t" + j_str << endl;
				TString str = (TString)"HCAL1energy_cut_S0S1S4SmuantiV0_" + i_str + j_str;
				TString col = (TString)"HCAL1energy_" + i_str + j_str;
				hHCAL1energy_cut_S0S1S4SmuantiV0[i][j] = f_S0S1S4SmuantiV0.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		//
		//hS4_cut_S0S1S4SmuantiV0 = f_S0S1S4SmuantiV0.Histo2D({ "S4_cut_S0S1S4SmuantiV0", "S4 events_cut_S0S1S4SmuantiV0", nbins, -1000, 1000, nbins, -1770, -1550 }, "s4x", "s4y");

	}
	//
	// 
	// 
	// 
	// 
	// 
	// Cut on S4, Smu and anti(S0, S1)
	//
	// Histogram definitions
	ROOT::RDF::RResultPtr<TH1D> hMM1x_cut_S4antiS0S1;
	ROOT::RDF::RResultPtr<TH1D> hMM1y_cut_S4antiS0S1;
	ROOT::RDF::RResultPtr<TH2D> hMM1xy_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM2x_cut_S4antiS0S1;
	ROOT::RDF::RResultPtr<TH1D> hMM2y_cut_S4antiS0S1;
	ROOT::RDF::RResultPtr<TH2D> hMM2xy_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM3x_cut_S4antiS0S1;
	ROOT::RDF::RResultPtr<TH1D> hMM3y_cut_S4antiS0S1;
	ROOT::RDF::RResultPtr<TH2D> hMM3xy_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hMM4x_cut_S4antiS0S1;
	ROOT::RDF::RResultPtr<TH1D> hMM4y_cut_S4antiS0S1;
	ROOT::RDF::RResultPtr<TH2D> hMM4xy_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hGEM1x_cut_S4antiS0S1;
	ROOT::RDF::RResultPtr<TH1D> hGEM1y_cut_S4antiS0S1;
	ROOT::RDF::RResultPtr<TH2D> hGEM1xy_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM2xy_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM3xy_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hGEM4xy_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM5xy_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM6xy_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH2D> hMM7xy_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hV0_cut_S4antiS0S1;
	//
	//
	//ROOT::RDF::RResultPtr<TH1D> hBeamEnergy0_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hECALtot_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALtot_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0tot_cut_S4antiS0S1;
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1tot_cut_S4antiS0S1;
	//
	//
	ROOT::RDF::RResultPtr<TH1D> hECALenergy_cut_S4antiS0S1[n_ECALx][n_ECALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hVHCALenergy_cut_S4antiS0S1[n_VHCALx][n_VHCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL0energy_cut_S4antiS0S1[n_HCALx][n_HCALy];
	//
	ROOT::RDF::RResultPtr<TH1D> hHCAL1energy_cut_S4antiS0S1[n_HCALx][n_HCALy];
	//
	// 
	ROOT::RDF::RResultPtr<TH2D> hS4_cut_S4antiS0S1;
	//
	// 
	// 
	// Count definition
	ROOT::RDF::RResultPtr<ULong64_t> c_S4antiS0S1;
	//
	// 
	//
	if (bool_S4antiS0S1) {

		cout << "S4antiS0S1 ";

		// Filter
		auto f_S4antiS0S1 = d.Filter(cut_S4, { "Triggers" }).Filter(cut_antiS0, { "Triggers" }).Filter(cut_antiS1, { "Triggers" });

		// Counts
		c_S4antiS0S1 = f_S4antiS0S1.Count();

		// Histograms
		hMM1xy_cut_S4antiS0S1 = f_S4antiS0S1.Histo2D({ "MM1 after cuts in S4, anti(S0, S1)", "MM1 events after cuts in S4, anti(S0, S1)", nbins, -80, 80, nbins, -80, 80 }, "MM1x", "MM1y");
		//
		hMM2xy_cut_S4antiS0S1 = f_S4antiS0S1.Histo2D({ "MM2 after cuts in S4, anti(S0, S1)", "MM2 events after cuts in S4, anti(S0, S1)", nbins, -80, 80, nbins, -80, 80 }, "MM2x", "MM2y");
		//
		hMM3xy_cut_S4antiS0S1 = f_S4antiS0S1.Histo2D({ "MM3 after cuts in S4, anti(S0, S1)", "MM3 events after cuts in S4, anti(S0, S1)", nbins, -80, 80, nbins, -830, -670 }, "MM3x", "MM3y");
		//
		hMM4xy_cut_S4antiS0S1 = f_S4antiS0S1.Histo2D({ "MM4 after cuts in S4, anti(S0, S1)", "MM4 events after cuts in S4, anti(S0, S1)", nbins, -80, 80, nbins, -850, -690 }, "MM4x", "MM4y");
		//
		hGEM1x_cut_S4antiS0S1 = f_S4antiS0S1.Histo1D({ "Name_hGEM1x_cut_S4antiS0S1","Title_GEM1x_cut_S4antiS0S1",nbins,-80,80 }, "GEM1x");
		hGEM1y_cut_S4antiS0S1 = f_S4antiS0S1.Histo1D({ "Name_hGEM1y_cut_S4antiS0S1", "Title_GEM1y_cut_S4antiS0S1", nbins, -1500, -1340 }, "GEM1y");
		hGEM1xy_cut_S4antiS0S1 = f_S4antiS0S1.Histo2D({ "GEM1 after cuts in S4, anti(S0, S1)", "GEM1 events after cuts in S4, anti(S0, S1)", nbins, -80, 80, nbins, -1500, -1340 }, "GEM1x", "GEM1y");
		//
		hGEM2xy_cut_S4antiS0S1 = f_S4antiS0S1.Histo2D({ "GEM2 after cuts in S4, anti(S0, S1)", "GEM2 events after cuts in S4, anti(S0, S1)", nbins, -80, 80, nbins, -1565, -1405 }, "GEM2x", "GEM2y");
		//
		hGEM3xy_cut_S4antiS0S1 = f_S4antiS0S1.Histo2D({ "GEM3 after cuts in S4, anti(S0, S1)", "GEM3 events after cuts in S4, anti(S0, S1)", nbins, -80, 80, nbins, -1600, -1440 }, "GEM3x", "GEM3y");
		//
		hGEM4xy_cut_S4antiS0S1 = f_S4antiS0S1.Histo2D({ "GEM4 after cuts in S4, anti(S0, S1)", "GEM4 events after cuts in S4, anti(S0, S1)", nbins, -80, 80, nbins, -1625, -1465 }, "GEM4x", "GEM4y");
		//
		hMM5xy_cut_S4antiS0S1 = f_S4antiS0S1.Histo2D({ "MM5 after cuts in S4, anti(S0, S1)", "MM5 events after cuts in S4, anti(S0, S1)", nbins, xlow_MM5, xup_MM5, nbins, ylow_MM5, yup_MM5 }, "MM5x", "MM5y");
		//
		hMM6xy_cut_S4antiS0S1 = f_S4antiS0S1.Histo2D({ "MM6 after cuts in S4, anti(S0, S1)", "MM6 events after cuts in S4, anti(S0, S1)", nbins, xlow_MM6, xup_MM6, nbins, ylow_MM6, yup_MM6 }, "MM6x", "MM6y");
		//
		hMM7xy_cut_S4antiS0S1 = f_S4antiS0S1.Histo2D({ "MM7 after cuts in S4, anti(S0, S1)", "MM7 events after cuts in S4, anti(S0, S1)", nbins, xlow_MM7, xup_MM7, nbins, ylow_MM7, yup_MM7 }, "MM7x", "MM7y");
		//
		hV0_cut_S4antiS0S1 = f_S4antiS0S1.Histo1D({ "V0 after cuts in S4, anti(S0, S1)","V0 after cuts in S4, anti(S0, S1)",nbins,low_cals,1e-2 }, "V0");
		//
		// 
		hECALtot_cut_S4antiS0S1 = f_S4antiS0S1.Histo1D({ "Name_hECALtot_cut_S4antiS0S1","Title_hECALtot_cut_S4antiS0S1",nbins,low_cals,up_cals }, "ECALtot");
		//
		hVHCALtot_cut_S4antiS0S1 = f_S4antiS0S1.Histo1D({ "Name_hVHCALtot_cut_S4antiS0S1","Title_hVHCALtot_cut_S4antiS0S1",nbins,low_cals,up_cals }, "VHCALtot");
		//
		hHCAL0tot_cut_S4antiS0S1 = f_S4antiS0S1.Histo1D({ "Name_hHCAL0tot_cut_S4antiS0S1","Title_hHCAL0tot_cut_S4antiS0S1",nbins,low_cals,up_cals }, "HCAL0tot");
		//
		hHCAL1tot_cut_S4antiS0S1 = f_S4antiS0S1.Histo1D({ "Name_hHCAL1tot_cut_S4antiS0S1","Title_hHCAL1tot_cut_S4antiS0S1",nbins,low_cals,up_cals }, "HCAL1tot");
		//
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				int k = i + (j * n_ECALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"ECALenergy_cut_S4antiS0S1_" + i_str + j_str;
				TString col = (TString)"ECALenergy_" + i_str + j_str;
				hECALenergy_cut_S4antiS0S1[i][j] = f_S4antiS0S1.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_VHCALx; i++) {
			for (int j = 0; j < n_VHCALy; j++) {
				int k = i + (j * n_VHCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"VHCALenergy_cut_S4antiS0S1_" + i_str + j_str;
				TString col = (TString)"VHCALenergy_" + i_str + j_str;
				hVHCALenergy_cut_S4antiS0S1[i][j] = f_S4antiS0S1.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				int k = i + (j * n_HCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"HCAL0energy_cut_S4antiS0S1_" + i_str + j_str;
				TString col = (TString)"HCAL0energy_" + i_str + j_str;
				hHCAL0energy_cut_S4antiS0S1[i][j] = f_S4antiS0S1.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				int k = i + (j * n_HCALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				//cout << k_str + "\t" + i_str + "\t" + j_str << endl;
				TString str = (TString)"HCAL1energy_cut_S4antiS0S1_" + i_str + j_str;
				TString col = (TString)"HCAL1energy_" + i_str + j_str;
				hHCAL1energy_cut_S4antiS0S1[i][j] = f_S4antiS0S1.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
			};
		};
		//
		//
		//hS4_cut_S4antiS0S1 = f_S4antiS0S1.Histo2D({ "S4_cut_S4antiS0S1", "S4 events_cut_S4antiS0S1", nbins, -1000, 1000, nbins, -1770, -1550 }, "s4x", "s4y");

	}
	//
	// 
	// 
	// 
	// 
	// 
	if (blocks == 8 || blocks == 0) {	}
	//
	// 
	// 
	// 
	// 
	// 
	// Tests
	//
	//Histogram definitions
	ROOT::RDF::RResultPtr<TH1D> hHCAL1tot_HighEnergy;
	//
	// 
	//
	if (bool_tests) {

		cout << "tests ";

		//hHCAL1tot_HighEnergy = d.Filter("BeamEnergy0 < 160 && BeamEnergy0 > 140 && HCAL1tot > 160")
		//						.Histo1D({ "HCAL1tot events with 140 GeV < BeamEnergy0 < 160 GeV ","HCAL1tot events with 140 GeV < BeamEnergy0 < 160 GeV",nbins,150,220 }, "HCAL1tot");
	}
	//
	cout << endl;






	// Event loop
	// 
	//
	// Unfiltered
	//
	if (bool_unfiltered) {

		// Plots
		//histogram_plot(hMM1x, "acc_RDF_hMM1x", "x[mm]", "Events");
		//histogram_plot(hMM1y, "acc_RDF_hMM1y", "y[mm]", "Events");
		histogram_plot(hMM1xy, "acc_RDF_hMM1xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		// 
		//histogram_plot(hMM2x, "acc_RDF_hMM2x", "x[mm]", "Events");
		//histogram_plot(hMM2y, "acc_RDF_hMM2y", "y[mm]", "Events");
		histogram_plot(hMM2xy, "acc_RDF_hMM2xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hMM3x, "acc_RDF_hMM3x", "x[mm]", "Events");
		//histogram_plot(hMM3y, "acc_RDF_hMM3y", "y[mm]", "Events");
		histogram_plot(hMM3xy, "acc_RDF_hMM3xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hMM4x, "acc_RDF_hMM4x", "x[mm]", "Events");
		//histogram_plot(hMM4y, "acc_RDF_hMM4y", "y[mm]", "Events");
		histogram_plot(hMM4xy, "acc_RDF_hMM4xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hGEM1x, "acc_RDF_hGEM1x", "x[mm]", "Events");
		//histogram_plot(hGEM1y, "acc_RDF_hGEM1y", "y[mm]", "Events");
		histogram_plot(hGEM1xy, "acc_RDF_hGEM1xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.025, "col", "", "");
		//
		histogram_plot(hGEM2xy, "acc_RDF_hGEM2xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hGEM3xy, "acc_RDF_hGEM3xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hGEM4xy, "acc_RDF_hGEM4xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM5xy, "acc_RDF_hMM5xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM6xy, "acc_RDF_hMM6xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM7xy, "acc_RDF_hMM7xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hV0, "acc_RDF_hV0", "Energy [GeV]", "Events", 1);
		//
		// 
		//histogram_plot(hBeamEnergy0, "acc_RDF_hBeamEnergy0", "Energy [GeV]", "Events", 0);
		//
		histogram_plot(hECALtot, "acc_RDF_hECALtot", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hVHCALtot, "acc_RDF_hVHCALtot", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hHCAL0tot, "acc_RDF_hHCAL0tot", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hHCAL1tot, "acc_RDF_hHCAL1tot", "Energy [GeV]", "Events", 1);
		//
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hECALenergy[i][j], (TString)"acc_RDF_hECALenergy_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_VHCALx; i++) {
			for (int j = 0; j < n_VHCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hVHCALenergy[i][j], (TString)"acc_RDF_hVHCALenergy_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hHCAL0energy[i][j], (TString)"acc_RDF_hHCAL0energy_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hHCAL1energy[i][j], (TString)"acc_RDF_hHCAL1energy_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		//
		//histogram_plot(hS4, "acc_RDF_hS4", "x [mm]", "y [mm]");

	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Cut on S0 and S1
	//
	if (bool_S0S1) {

		// Plots
		//histogram_plot(hMM1x_cut_S0S1, "acc_RDF_hMM1x_cut_S0S1", "x[mm]", "Events");
		//histogram_plot(hMM1y_cut_S0S1, "acc_RDF_hMM1y_cut_S0S1", "y[mm]", "Events");
		histogram_plot(hMM1xy_cut_S0S1, "acc_RDF_hMM1xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		// 
		//histogram_plot(hMM2x_cut_S0S1, "acc_RDF_hMM2x_cut_S0S1", "x[mm]", "Events");
		//histogram_plot(hMM2y_cut_S0S1, "acc_RDF_hMM2y_cut_S0S1", "y[mm]", "Events");
		histogram_plot(hMM2xy_cut_S0S1, "acc_RDF_hMM2xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hMM3x_cut_S0S1, "acc_RDF_hMM3x_cut_S0S1", "x[mm]", "Events");
		//histogram_plot(hMM3y_cut_S0S1, "acc_RDF_hMM3y_cut_S0S1", "y[mm]", "Events");
		histogram_plot(hMM3xy_cut_S0S1, "acc_RDF_hMM3xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hMM4x_cut_S0S1, "acc_RDF_hMM4x_cut_S0S1", "x[mm]", "Events");
		//histogram_plot(hMM4y_cut_S0S1, "acc_RDF_hMM4y_cut_S0S1", "y[mm]", "Events");
		histogram_plot(hMM4xy_cut_S0S1, "acc_RDF_hMM4xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hGEM1x_cut_S0S1, "acc_RDF_hGEM1x_cut_S0S1", "x[mm]", "Events");
		//histogram_plot(hGEM1y_cut_S0S1, "acc_RDF_hGEM1y_cut_S0S1", "y[mm]", "Events");
		histogram_plot(hGEM1xy_cut_S0S1, "acc_RDF_hGEM1xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.025, "col", "", "");
		//
		histogram_plot(hGEM2xy_cut_S0S1, "acc_RDF_hGEM2xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hGEM3xy_cut_S0S1, "acc_RDF_hGEM3xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hGEM4xy_cut_S0S1, "acc_RDF_hGEM4xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM5xy_cut_S0S1, "acc_RDF_hMM5xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM6xy_cut_S0S1, "acc_RDF_hMM6xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM7xy_cut_S0S1, "acc_RDF_hMM7xy_cut_S0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hV0_cut_S0S1, "acc_RDF_hV0_cut_S0S1", "Energy [GeV]", "Events", 1);

	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Cut on S0, S1 and antiV0
	//
	if (bool_S0S1antiV0) {

		// Plots
		//histogram_plot(hMM1x_cut_S0S1antiV0, "acc_RDF_hMM1x_cut_S0S1antiV0", "x[mm]", "Events");
		//histogram_plot(hMM1y_cut_S0S1antiV0, "acc_RDF_hMM1y_cut_S0S1antiV0", "y[mm]", "Events");
		histogram_plot(hMM1xy_cut_S0S1antiV0, "acc_RDF_hMM1xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		// 
		//histogram_plot(hMM2x_cut_S0S1antiV0, "acc_RDF_hMM2x_cut_S0S1antiV0", "x[mm]", "Events");
		//histogram_plot(hMM2y_cut_S0S1antiV0, "acc_RDF_hMM2y_cut_S0S1antiV0", "y[mm]", "Events");
		histogram_plot(hMM2xy_cut_S0S1antiV0, "acc_RDF_hMM2xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hMM3x_cut_S0S1antiV0, "acc_RDF_hMM3x_cut_S0S1antiV0", "x[mm]", "Events");
		//histogram_plot(hMM3y_cut_S0S1antiV0, "acc_RDF_hMM3y_cut_S0S1antiV0", "y[mm]", "Events");
		histogram_plot(hMM3xy_cut_S0S1antiV0, "acc_RDF_hMM3xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hMM4x_cut_S0S1antiV0, "acc_RDF_hMM4x_cut_S0S1antiV0", "x[mm]", "Events");
		//histogram_plot(hMM4y_cut_S0S1antiV0, "acc_RDF_hMM4y_cut_S0S1antiV0", "y[mm]", "Events");
		histogram_plot(hMM4xy_cut_S0S1antiV0, "acc_RDF_hMM4xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hGEM1x_cut_S0S1antiV0, "acc_RDF_hGEM1x_cut_S0S1antiV0", "x[mm]", "Events");
		//histogram_plot(hGEM1y_cut_S0S1antiV0, "acc_RDF_hGEM1y_cut_S0S1antiV0", "y[mm]", "Events");
		histogram_plot(hGEM1xy_cut_S0S1antiV0, "acc_RDF_hGEM1xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.025, "col", "", "");
		//
		histogram_plot(hGEM2xy_cut_S0S1antiV0, "acc_RDF_hGEM2xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hGEM3xy_cut_S0S1antiV0, "acc_RDF_hGEM3xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hGEM4xy_cut_S0S1antiV0, "acc_RDF_hGEM4xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM5xy_cut_S0S1antiV0, "acc_RDF_hMM5xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM6xy_cut_S0S1antiV0, "acc_RDF_hMM6xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM7xy_cut_S0S1antiV0, "acc_RDF_hMM7xy_cut_S0S1antiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hV0_cut_S0S1antiV0, "acc_RDF_hV0_cut_S0S1antiV0", "Energy [GeV]", "Events", 1);
		//
		//
		histogram_plot(hECALtot_cut_S0S1antiV0, "acc_RDF_hECALtot_cut_S0S1antiV0", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hVHCALtot_cut_S0S1antiV0, "acc_RDF_hVHCALtot_cut_S0S1antiV0", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hHCAL0tot_cut_S0S1antiV0, "acc_RDF_hHCAL0tot_cut_S0S1antiV0", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hHCAL1tot_cut_S0S1antiV0, "acc_RDF_hHCAL1tot_cut_S0S1antiV0", "Energy [GeV]", "Events", 1);
		//
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hECALenergy_cut_S0S1antiV0[i][j], (TString)"acc_RDF_hECALenergy_cut_S0S1antiV0_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_VHCALx; i++) {
			for (int j = 0; j < n_VHCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hVHCALenergy_cut_S0S1antiV0[i][j], (TString)"acc_RDF_hVHCALenergy_cut_S0S1antiV0_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hHCAL0energy_cut_S0S1antiV0[i][j], (TString)"acc_RDF_hHCAL0energy_cut_S0S1antiV0_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hHCAL1energy_cut_S0S1antiV0[i][j], (TString)"acc_RDF_hHCAL1energy_cut_S0S1antiV0_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};

	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Cut on anti( S0, S1)
	//
	if (bool_antiS0S1) {

		// Plots
		//histogram_plot(hMM1x_cut_antiS0S1, "acc_RDF_hMM1x_cut_antiS0S1", "x[mm]", "Events");
		//histogram_plot(hMM1y_cut_antiS0S1, "acc_RDF_hMM1y_cut_antiS0S1", "y[mm]", "Events");
		histogram_plot(hMM1xy_cut_antiS0S1, "acc_RDF_hMM1xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		// 
		//histogram_plot(hMM2x_cut_antiS0S1, "acc_RDF_hMM2x_cut_antiS0S1", "x[mm]", "Events");
		//histogram_plot(hMM2y_cut_antiS0S1, "acc_RDF_hMM2y_cut_antiS0S1", "y[mm]", "Events");
		histogram_plot(hMM2xy_cut_antiS0S1, "acc_RDF_hMM2xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hMM3x_cut_antiS0S1, "acc_RDF_hMM3x_cut_antiS0S1", "x[mm]", "Events");
		//histogram_plot(hMM3y_cut_antiS0S1, "acc_RDF_hMM3y_cut_antiS0S1", "y[mm]", "Events");
		histogram_plot(hMM3xy_cut_antiS0S1, "acc_RDF_hMM3xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hMM4x_cut_antiS0S1, "acc_RDF_hMM4x_cut_antiS0S1", "x[mm]", "Events");
		//histogram_plot(hMM4y_cut_antiS0S1, "acc_RDF_hMM4y_cut_antiS0S1", "y[mm]", "Events");
		histogram_plot(hMM4xy_cut_antiS0S1, "acc_RDF_hMM4xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hGEM1x_cut_antiS0S1, "acc_RDF_hGEM1x_cut_antiS0S1", "x[mm]", "Events");
		//histogram_plot(hGEM1y_cut_antiS0S1, "acc_RDF_hGEM1y_cut_antiS0S1", "y[mm]", "Events");
		histogram_plot(hGEM1xy_cut_antiS0S1, "acc_RDF_hGEM1xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.025, "col", "", "");
		//
		histogram_plot(hGEM2xy_cut_antiS0S1, "acc_RDF_hGEM2xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hGEM3xy_cut_antiS0S1, "acc_RDF_hGEM3xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hGEM4xy_cut_antiS0S1, "acc_RDF_hGEM4xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM5xy_cut_antiS0S1, "acc_RDF_hMM5xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM6xy_cut_antiS0S1, "acc_RDF_hMM6xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM7xy_cut_antiS0S1, "acc_RDF_hMM7xy_cut_antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hV0_cut_antiS0S1, "acc_RDF_hV0_cut_antiS0S1", "Energy [GeV]", "Events", 1);
		//
		//
		histogram_plot(hECALtot_cut_antiS0S1, "acc_RDF_hECALtot_cut_antiS0S1", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hVHCALtot_cut_antiS0S1, "acc_RDF_hVHCALtot_cut_antiS0S1", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hHCAL0tot_cut_antiS0S1, "acc_RDF_hHCAL0tot_cut_antiS0S1", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hHCAL1tot_cut_antiS0S1, "acc_RDF_hHCAL1tot_cut_antiS0S1", "Energy [GeV]", "Events", 1);
		//
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hECALenergy_cut_antiS0S1[i][j], (TString)"acc_RDF_hECALenergy_cut_antiS0S1_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_VHCALx; i++) {
			for (int j = 0; j < n_VHCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hVHCALenergy_cut_antiS0S1[i][j], (TString)"acc_RDF_hVHCALenergy_cut_antiS0S1_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hHCAL0energy_cut_antiS0S1[i][j], (TString)"acc_RDF_hHCAL0energy_cut_antiS0S1_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hHCAL1energy_cut_antiS0S1[i][j], (TString)"acc_RDF_hHCAL1energy_cut_antiS0S1_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};

	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Cut on S0, S1 and V0
	//
	if (bool_S0S1V0) {

		// Plots
		histogram_plot(hGEM1xy_cut_S0S1V0, "acc_RDF_hGEM1xy_cut_S0S1V0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.025, "col", "", "");
		//
		histogram_plot(hV0_cut_S0S1V0, "acc_RDF_hV0_cut_S0S1V0", "Energy [GeV]", "Events", 1);

	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Cut on S0, S1, S4, Smu and antiV0
	//
	if (bool_S0S1S4SmuantiV0) {

		// Plots
		//histogram_plot(hMM1x_cut_S0S1S4SmuantiV0, "acc_RDF_hMM1x_cut_S0S1S4SmuantiV0", "x[mm]", "Events");
		//histogram_plot(hMM1y_cut_S0S1S4SmuantiV0, "acc_RDF_hMM1y_cut_S0S1S4SmuantiV0", "y[mm]", "Events");
		histogram_plot(hMM1xy_cut_S0S1S4SmuantiV0, "acc_RDF_hMM1xy_cut_S0S1S4SmuantiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		// 
		//histogram_plot(hMM2x_cut_S0S1S4SmuantiV0, "acc_RDF_hMM2x_cut_S0S1S4SmuantiV0", "x[mm]", "Events");
		//histogram_plot(hMM2y_cut_S0S1S4SmuantiV0, "acc_RDF_hMM2y_cut_S0S1S4SmuantiV0", "y[mm]", "Events");
		histogram_plot(hMM2xy_cut_S0S1S4SmuantiV0, "acc_RDF_hMM2xy_cut_S0S1S4SmuantiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hMM3x_cut_S0S1S4SmuantiV0, "acc_RDF_hMM3x_cut_S0S1S4SmuantiV0", "x[mm]", "Events");
		//histogram_plot(hMM3y_cut_S0S1S4SmuantiV0, "acc_RDF_hMM3y_cut_S0S1S4SmuantiV0", "y[mm]", "Events");
		histogram_plot(hMM3xy_cut_S0S1S4SmuantiV0, "acc_RDF_hMM3xy_cut_S0S1S4SmuantiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hMM4x_cut_S0S1S4SmuantiV0, "acc_RDF_hMM4x_cut_S0S1S4SmuantiV0", "x[mm]", "Events");
		//histogram_plot(hMM4y_cut_S0S1S4SmuantiV0, "acc_RDF_hMM4y_cut_S0S1S4SmuantiV0", "y[mm]", "Events");
		histogram_plot(hMM4xy_cut_S0S1S4SmuantiV0, "acc_RDF_hMM4xy_cut_S0S1S4SmuantiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hGEM1x_cut_S0S1S4SmuantiV0, "acc_RDF_hGEM1x_cut_S0S1S4SmuantiV0", "x[mm]", "Events");
		//histogram_plot(hGEM1y_cut_S0S1S4SmuantiV0, "acc_RDF_hGEM1y_cut_S0S1S4SmuantiV0", "y[mm]", "Events");
		histogram_plot(hGEM1xy_cut_S0S1S4SmuantiV0, "acc_RDF_hGEM1xy_cut_S0S1S4SmuantiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.025, "col", "", "");
		//
		histogram_plot(hGEM2xy_cut_S0S1S4SmuantiV0, "acc_RDF_hGEM2xy_cut_S0S1S4SmuantiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hGEM3xy_cut_S0S1S4SmuantiV0, "acc_RDF_hGEM3xy_cut_S0S1S4SmuantiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hGEM4xy_cut_S0S1S4SmuantiV0, "acc_RDF_hGEM4xy_cut_S0S1S4SmuantiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM5xy_cut_S0S1S4SmuantiV0, "acc_RDF_hMM5xy_cut_S0S1S4SmuantiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM6xy_cut_S0S1S4SmuantiV0, "acc_RDF_hMM6xy_cut_S0S1S4SmuantiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM7xy_cut_S0S1S4SmuantiV0, "acc_RDF_hMM7xy_cut_S0S1S4SmuantiV0", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hV0_cut_S0S1S4SmuantiV0, "acc_RDF_hV0_cut_S0S1S4SmuantiV0", "Energy [GeV]", "Events", 1);
		//
		//
		histogram_plot(hECALtot_cut_S0S1S4SmuantiV0, "acc_RDF_hECALtot_cut_S0S1S4SmuantiV0", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hVHCALtot_cut_S0S1S4SmuantiV0, "acc_RDF_hVHCALtot_cut_S0S1S4SmuantiV0", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hHCAL0tot_cut_S0S1S4SmuantiV0, "acc_RDF_hHCAL0tot_cut_S0S1S4SmuantiV0", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hHCAL1tot_cut_S0S1S4SmuantiV0, "acc_RDF_hHCAL1tot_cut_S0S1S4SmuantiV0", "Energy [GeV]", "Events", 1);
		//
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hECALenergy_cut_S0S1S4SmuantiV0[i][j], (TString)"acc_RDF_hECALenergy_cut_S0S1S4SmuantiV0_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_VHCALx; i++) {
			for (int j = 0; j < n_VHCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hVHCALenergy_cut_S0S1S4SmuantiV0[i][j], (TString)"acc_RDF_hVHCALenergy_cut_S0S1S4SmuantiV0_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hHCAL0energy_cut_S0S1S4SmuantiV0[i][j], (TString)"acc_RDF_hHCAL0energy_cut_S0S1S4SmuantiV0_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hHCAL1energy_cut_S0S1S4SmuantiV0[i][j], (TString)"acc_RDF_hHCAL1energy_cut_S0S1S4SmuantiV0_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};

	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Cut on S4, and anti(S0, S1)
	//
	if (bool_S4antiS0S1) {

		// Plots
		//histogram_plot(hMM1x_cut_S4antiS0S1, "acc_RDF_hMM1x_cut_S4antiS0S1", "x[mm]", "Events");
		//histogram_plot(hMM1y_cut_S4antiS0S1, "acc_RDF_hMM1y_cut_S4antiS0S1", "y[mm]", "Events");
		histogram_plot(hMM1xy_cut_S4antiS0S1, "acc_RDF_hMM1xy_cut_S4antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		// 
		//histogram_plot(hMM2x_cut_S4antiS0S1, "acc_RDF_hMM2x_cut_S4antiS0S1", "x[mm]", "Events");
		//histogram_plot(hMM2y_cut_S4antiS0S1, "acc_RDF_hMM2y_cut_S4antiS0S1", "y[mm]", "Events");
		histogram_plot(hMM2xy_cut_S4antiS0S1, "acc_RDF_hMM2xy_cut_S4antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hMM3x_cut_S4antiS0S1, "acc_RDF_hMM3x_cut_S4antiS0S1", "x[mm]", "Events");
		//histogram_plot(hMM3y_cut_S4antiS0S1, "acc_RDF_hMM3y_cut_S4antiS0S1", "y[mm]", "Events");
		histogram_plot(hMM3xy_cut_S4antiS0S1, "acc_RDF_hMM3xy_cut_S4antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hMM4x_cut_S4antiS0S1, "acc_RDF_hMM4x_cut_S4antiS0S1", "x[mm]", "Events");
		//histogram_plot(hMM4y_cut_S4antiS0S1, "acc_RDF_hMM4y_cut_S4antiS0S1", "y[mm]", "Events");
		histogram_plot(hMM4xy_cut_S4antiS0S1, "acc_RDF_hMM4xy_cut_S4antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		//histogram_plot(hGEM1x_cut_S4antiS0S1, "acc_RDF_hGEM1x_cut_S4antiS0S1", "x[mm]", "Events");
		//histogram_plot(hGEM1y_cut_S4antiS0S1, "acc_RDF_hGEM1y_cut_S4antiS0S1", "y[mm]", "Events");
		histogram_plot(hGEM1xy_cut_S4antiS0S1, "acc_RDF_hGEM1xy_cut_S4antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.025, "col", "", "");
		//
		histogram_plot(hGEM2xy_cut_S4antiS0S1, "acc_RDF_hGEM2xy_cut_S4antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hGEM3xy_cut_S4antiS0S1, "acc_RDF_hGEM3xy_cut_S4antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hGEM4xy_cut_S4antiS0S1, "acc_RDF_hGEM4xy_cut_S4antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM5xy_cut_S4antiS0S1, "acc_RDF_hMM5xy_cut_S4antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM6xy_cut_S4antiS0S1, "acc_RDF_hMM6xy_cut_S4antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hMM7xy_cut_S4antiS0S1, "acc_RDF_hMM7xy_cut_S4antiS0S1", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		histogram_plot(hV0_cut_S4antiS0S1, "acc_RDF_hV0_cut_S4antiS0S1", "Energy [GeV]", "Events", 1);
		//
		//
		histogram_plot(hECALtot_cut_S4antiS0S1, "acc_RDF_hECALtot_cut_S4antiS0S1", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hVHCALtot_cut_S4antiS0S1, "acc_RDF_hVHCALtot_cut_S4antiS0S1", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hHCAL0tot_cut_S4antiS0S1, "acc_RDF_hHCAL0tot_cut_S4antiS0S1", "Energy [GeV]", "Events", 1);
		//
		histogram_plot(hHCAL1tot_cut_S4antiS0S1, "acc_RDF_hHCAL1tot_cut_S4antiS0S1", "Energy [GeV]", "Events", 1);
		//
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hECALenergy_cut_S4antiS0S1[i][j], (TString)"acc_RDF_hECALenergy_cut_S4antiS0S1_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_VHCALx; i++) {
			for (int j = 0; j < n_VHCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hVHCALenergy_cut_S4antiS0S1[i][j], (TString)"acc_RDF_hVHCALenergy_cut_S4antiS0S1_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hHCAL0energy_cut_S4antiS0S1[i][j], (TString)"acc_RDF_hHCAL0energy_cut_S4antiS0S1_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		//
		for (int i = 0; i < n_HCALx; i++) {
			for (int j = 0; j < n_HCALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hHCAL1energy_cut_S4antiS0S1[i][j], (TString)"acc_RDF_hHCAL1energy_cut_S4antiS0S1_" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};

	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	if (blocks == 8 || blocks == 0) {	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Tests
	//
	if (bool_tests) {

		// Plots
		//histogram_plot(hHCAL1tot_HighEnergy, "acc_RDF_hHCAL1tot_HighEnergy", "Energy [GeV]", "Events", 1);

	}






	// Displays
	//
	// 
	std::cout << *totentries << " total entries" << std::endl;
	//
	// 
	// 
	// 
	// 
	// 
	// Cut on S0 and S1
	//
	if (bool_S0S1) {
		std::cout << *c_S0S1 << " entries passed the cut on S0 and S1" << std::endl;
	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Cut on S0, S1 and antiV0
	//
	if (bool_S0S1antiV0) {
		std::cout << *c_S0S1antiV0 << " entries passed the cut on S0, S1 and anti(V0)" << std::endl;
	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Cut on anti( S0, S1)
	//
	if (bool_antiS0S1) {
		std::cout << *c_antiS0S1 << " entries did not pass the cut on S0 and S1" << std::endl;
	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Cut on S0, S1 and V0
	//
	if (bool_S0S1V0) {
		std::cout << *c_S0S1V0 << " entries passed the cut on S0 and S1 and had a hit on V0" << std::endl;
	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Cut on S0, S1, S4, Smu and antiV0
	//
	if (bool_S0S1S4SmuantiV0) {
		std::cout << *c_S0S1S4SmuantiV0 << " entries passed the cut on S0, S1, anti(V0), S4 and Smu" << std::endl;
	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Cut on S4, and anti(S0, S1)
	//
	if (bool_S4antiS0S1) {
		std::cout << *c_S4antiS0S1 << " entries passed the cut on S4 and anti(S0, S1)" << std::endl;
	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	if (blocks == 8 || blocks == 0) {	}
	//
	// 
	// 
	// 
	// 
	// 
	// 
	// Tests
	//
	if (bool_tests) {	}




	/*
	// Show the properties of the data frame
	d.Describe().Print();
	std::cout << std::endl;
	// Alternative way: std::cout << d.Describe().AsString() << std::endl;
	//*/



	time_t tend = time(0);

	cout << "Running time: " << tend - t0 << " seconds" << endl;

}