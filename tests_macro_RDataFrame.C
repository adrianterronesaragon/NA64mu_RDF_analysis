
#include "histogram_plot.h"

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
	ROOT::RDataFrame d("ana_tree", "../Reco_2305_160gev_V1.7.root"); // Interface to TTree and TChain

	//ROOT::RDataFrame d0("ana_tree", "Reco_2305_160gev_V1.7.root");
	//auto d = d0.Range(0, 1000000);

	// Count of the total entries
	auto totentries = d.Count();



	// Binning
	const int nbins = 400;

	// Calorimeter cells
	int n_ECALx = 5;
	int n_ECALy = 6;




	// Initial values
	double t_spill = 4.8e9; // ns
	double t_accept = 10; // ns
	unsigned int n_bins = (unsigned int)(t_spill / t_accept);
	auto n_events = d.Count();

	// test values
	n_bins = 30;
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
	ROOT::RDataFrame d_accidentals(bin_multiplicities_t.size());
	int b = 0;
	ROOT::VecOps::RVec<int> a;
	for (int i = 0; i < bin_multiplicities_t.size(); i++) {
		a.push_back(*d.Range(b, b + bin_multiplicities_t.at(i)).Sum("ECALtot"));
		b = b + bin_multiplicities_t.at(i);
	}
	//d_accidentals.Define("ECALtot", );


	cout << bins_t_sorted << endl;
	cout << bin_multiplicities_t << endl;

	//*
	// Show the properties of the data frame
	d_accidentals.Describe().Print();
	std::cout << std::endl;
	// Alternative way: std::cout << d.Describe().AsString() << std::endl;
	//*/










	// Set ups
	// 
	// 
	// Unfiltered
	//
	ROOT::RDF::RResultPtr<TH2D> hMM1xy_test;
	//
	ROOT::RDF::RResultPtr<TH1D> hECALenergy_test[n_ECALx][n_ECALy];
	//
	//if (blocks == 1 || blocks == 0) {
	/*
		// Histograms
		hMM1xy_test = d.Histo2D({ "MM1", "MM1 events", nbins, -80, 80, nbins, -80, 80 }, "MM1x", "MM1y");
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
	*/
	//}

	// Event loop
	// 
	//
	// Unfiltered
	//
	//if (blocks == 1 || blocks == 0) {

		// Plots
		/*
		histogram_plot(hMM1xy, "RDF_hMM1xy", "x [mm]", "y [mm]", 0, 2, 1, 1.47, 0.04, 0.04, "col", "", "");
		//
		for (int i = 0; i < n_ECALx; i++) {
			for (int j = 0; j < n_ECALy; j++) {
				TString i_str = (TString)to_string(i);
				TString j_str = (TString)to_string(j);
				histogram_plot(hECALenergy[i][j], (TString)"RDF_hECALenergy" + i_str + j_str, "Energy [GeV]", "Events", 1);
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
			for (int j = 0; j < n_ECALy; j++) {
				int k = 1 + i + (j * n_ECALx);
				canvas_test->cd(k);
				hECALenergy_test[i][j]->SetAxisRange(0, 2, "x"); // why does this not work??
				hECALenergy_test[i][j]->DrawCopy();
				gPad->SetLogy(1);
				canvas_test->Update();
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

	//*
	// Show the properties of the data frame
	d.Describe().Print();
	std::cout << std::endl;
	// Alternative way: std::cout << d.Describe().AsString() << std::endl;
	//*/

}