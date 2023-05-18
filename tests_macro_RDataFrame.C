
#include "histogram_plot.h"
#include "ROOT/RVec.hxx"

#define str(s) (TString) #s

bool digit_check(int digit, int number) {
	bool b = false;
	int d;
	while (number != 0) {
		cout << number << endl << b << endl;
		d = number % 10;
		if (d == digit) { b = true; }
		number /= 10;
	}
	return b;
}

void tests_macro_RDataFrame() {

	/*
	// Selection of blocks to run
	cout << endl;
	cout << "Please, select which blocks you want to run. Type" << endl;
	cout << "\t 0 \t to quit" << endl;
	cout << "\t 1 \t to run unfiltered" << endl;
	cout << "\t 2 \t to run the cut on S0 and S1" << endl;
	cout << "\t 3 \t to run the cut on S0, S1 and antiV0" << endl;
	cout << "\t 4 \t to run the cut on anti( S0, S1 )" << endl;
	cout << "\t 5 \t to run the cut on S0, S1 and V0" << endl;
	cout << "\t 8 \t to run tests" << endl;
	cout << "\t 9 \t to run all" << endl;
	cout << "Your selection: ";
	int blocks;
	cin >> blocks;
	*/

	// Option for not showing plots after compiling
	gROOT->SetBatch(kTRUE);

	// To include headers from another folder
	//R__ADD_INCLUDE_PATH(<name of the path>);

	// Definition of the data frame
	ROOT::EnableImplicitMT(); // Tell ROOT you want to go parallel
	ROOT::RDataFrame d0("accidentals_tree", "../Reco_2305_160gev_V1.7_accidentals.root"); // Interface to TTree and TChain
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

	// Count of the total entries
	auto totentries = d.Count();


	auto f_S0S1S4SmuantiV0 = d.Filter(cut_S0, { "Triggers" }).Filter(cut_S1, { "Triggers" }).Filter(cut_S4, { "Triggers" }).Filter(cut_Smu, { "Triggers" }).Filter(cut_antiV0, { "Triggers" });

	auto hHCAL0tot_acc_trigger3_test = f_S0S1S4SmuantiV0.Histo1D({ "Name_hHCAL0tot_acc_trigger3_test","Title_hHCAL0tot_acc_trigger3_test",nbins,-1e-6,20 }, "HCAL0tot");
	ROOT::RDF::RResultPtr<TH1D> hHCAL0energy[n_HCALx][n_HCALy];
	ROOT::RDF::RResultPtr<TH1D> hHCAL1energy[n_HCALx][n_HCALy];
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			int k = i + (j * n_HCALx);
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"HCAL0energy_" + i_str + j_str;
			TString col = (TString)"HCAL0energy_" + i_str + j_str;
			hHCAL0energy[i][j] = f_S0S1S4SmuantiV0.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
		};
	};
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			int k = i + (j * n_HCALx);
			TString k_str = (TString)to_string(k);
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"HCAL1energy_" + i_str + j_str;
			TString col = (TString)"HCAL1energy_" + i_str + j_str;
			hHCAL1energy[i][j] = f_S0S1S4SmuantiV0.Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, low_cals, up_cals }, col);
		};
	};

	histogram_plot(hHCAL0tot_acc_trigger3_test, "acc_hHCAL0tot_trigger3_test", "Energy [GeV]", "Events", 1);
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			histogram_plot(hHCAL0energy[i][j], (TString)"acc_hHCAL0energy_trigger3_test_" + i_str + j_str, "Energy [GeV]", "Events", 1);
		};
	};
	//
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			histogram_plot(hHCAL1energy[i][j], (TString)"acc_hHCAL1energy_trigger3_test_" + i_str + j_str, "Energy [GeV]", "Events", 1);
		};
	};




	//auto a = std::iota(0, 3, 1);
	//cout << a << "\n";



	/*
	// Initial values
	double t_spill = 4.8e9; // ns
	double t_accept = 10; // ns
	unsigned int n_bins = (unsigned int)(t_spill / t_accept);
	auto n_events = d.Count();

	// test values
	n_bins = 50;
	*n_events = 100;

	// Random object definition
	TRandom3* random = new TRandom3();

	// Generate random bin tags and sort them
	ROOT::VecOps::RVec<int> bins_t;
	for (int i = 0; i < *n_events; i++) {
		bins_t.push_back(random->Integer(n_bins));
	}
	auto bins_t_sorted = Take(bins_t, Argsort(bins_t));

	// Count and store the multiplicities of the bin tags
	ROOT::VecOps::RVec<int> bin_multiplicities_t {1};
	int c = 0;
	for (int i = 0; i < bins_t_sorted.size() - 1; i++) {
		if (bins_t_sorted.at(i) == bins_t_sorted.at(i + 1)) {
			bin_multiplicities_t.at(c)++;
		}
		else {
			bin_multiplicities_t.push_back(1);
			c++;
		}
	}

	// New data frame
	int n_bins_multiplicities = bin_multiplicities_t.size();
	ROOT::RDataFrame d_accidentals0(n_bins_multiplicities);
	int b = 0;
	ROOT::VecOps::RVec<double> a;
	for (int i = 0; i < n_bins_multiplicities; i++) {
		a.push_back(*d.Range(b, b + bin_multiplicities_t.at(i)).Sum("ECALtot"));
		b = b + bin_multiplicities_t.at(i);
	}
	int i_eventloop = 0;
	auto d_accidentals = d_accidentals0.Define("ECALtot", [&i_eventloop, a]() { double foo = a.at(i_eventloop); i_eventloop++; return foo; });

	cout << bins_t_sorted << endl;
	cout << bin_multiplicities_t << endl;
	cout << a << endl;
	cout << *d.Range(0, *n_events).Take<double, ROOT::VecOps::RVec<double>>("ECALtot") << endl;

	// Check that the data is correctly stored in data frame
	//auto a_test = *d_accidentals.Take<double, ROOT::VecOps::RVec<double>>("ECALtot");
	//cout << a_test << endl;
	*/
	

	/*
	// Show the properties of the data frame
	d_accidentals.Describe().Print();
	std::cout << std::endl;
	// Alternative way: std::cout << d.Describe().AsString() << std::endl;
	//*/








	/*
	// Set ups
	// 
	// 
	// Unfiltered
	//
	ROOT::RDF::RResultPtr<TH2D> hMM1xy_test;
	//
	ROOT::RDF::RResultPtr<TH1D> hECALenergy_test[n_ECALx][n_ECALy];
	//
	if (blocks == 1 || blocks == 0) {
		// Histograms
		//hMM1xy_test = d.Histo2D({ "MM1", "MM1 events", nbins, -80, 80, nbins, -80, 80 }, "MM1x", "MM1y");
		//
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				int k = i + (j * n_ECALx);
				TString k_str = (TString)to_string(k);
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				TString str = (TString)"ECALenergy" + i_str + j_str;
				TString temp_str = (TString)"ECALenergy[" + k_str + "]";
				string_view col_str = (string_view)temp_str;
				hECALenergy_test[i][j] = d.Define(str, col_str).Histo1D({ (TString)"Name_h" + str ,"Title_h" + str , nbins, -1e-6, 10 }, str);
				hECALenergy_test[i][j]->SetAxisRange(0, 2, "x");
			};
		};
	
	}
	*/

	// Event loop
	// 
	//
	// Unfiltered
	//
	//if (blocks == 1 || blocks == 0) {

		// Plots
		//histogram_plot(hMM1xy_test, "RDF_hMM1xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		/*
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hECALenergy_test[i][j], (TString)"RDF_hECALenergy" + i_str + j_str, "Energy [GeV]", "Events", 1);
			};
		};
		*/
		

		// Axis labels
		//histo->GetXaxis()->SetTitle(xlabel);
		//histo->GetYaxis()->SetTitle(ylabel);

		// Labels offset and size
		//histo->GetXaxis()->SetTitleOffset(xlabeloffset);
		//histo->GetXaxis()->SetLabelSize(xlabelsize);
		//histo->GetYaxis()->SetTitleOffset(ylabeloffset);
		//histo->GetYaxis()->SetLabelSize(ylabelsize);
		
		/*
		// Create canvas
		TCanvas* canvas_test = new TCanvas("","", 5*700, 6*500);
		canvas_test->Divide(5, 6);
		for (int i = 0; i < n_ECALx; i++) {
			int j_dummy = 0;
			for (int j = n_ECALy - 1; j >= 0; j--) {
				int k = 1 + i + (j_dummy * n_ECALx);
				canvas_test->cd(k);
				hECALenergy_test[i][j]->SetAxisRange(0, 2, "x"); // why does this not work??
				hECALenergy_test[i][j]->DrawCopy();
				gPad->SetLogy(1);
				canvas_test->Update();
				j_dummy++;
			};
		};
		//canvas_test->Update();
		canvas_test->SaveAs("../test.png");
		canvas_test->SaveAs("../test.pdf");
		*/


		/*
		TCanvas* canvas_test2 = new TCanvas("", "", 5 * 700, 6 * 500);
		canvas_test2->Divide(5, 6);
		canvas_test2->cd(13);
		hECALenergy_test[2][3]->SetAxisRange(0, 2, "x");
		hECALenergy_test[2][3]->DrawCopy();
		gPad->SetLogy(1);
		canvas_test2->Update();
		canvas_test2->SaveAs("../test2.png");
		*/

	//}

	// Displays
	//
	// 
	//std::cout << *totentries << " total entries" << std::endl;


	/*
	auto HCALm = d.Range(0, 1).Take<ROOT::VecOps::RVec<double>>("HCALm")->at(0);
	cout << HCALm << endl;
	auto HCALx = d.Range(0, 1).Take<ROOT::VecOps::RVec<double>>("HCALx")->at(0);
	cout << HCALx << endl;
	auto HCALy = d.Range(0, 1).Take<ROOT::VecOps::RVec<double>>("HCALy")->at(0);
	cout << HCALy << endl;
	*/

	/*
	// Show the properties of the data frame
	d.Describe().Print();
	std::cout << std::endl;
	// Alternative way: std::cout << d.Describe().AsString() << std::endl;
	//*/

}