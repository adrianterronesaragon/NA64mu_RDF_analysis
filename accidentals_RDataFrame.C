
#include "histogram_plot.h"
#include "ROOT/RVec.hxx"

void accidentals_RDataFrame() {

	time_t t0 = time(0);
	cout << "Time control: End of compiling" << endl;

	// Option for not showing plots after compiling
	gROOT->SetBatch(kTRUE);

	// To include headers from another folder
	//R__ADD_INCLUDE_PATH(<name of the path>);

	// Definition of the data frame
	//ROOT::EnableImplicitMT(); // Tell ROOT you want to go parallel
	ROOT::RDataFrame d("ana_tree", "../Reco_2305_160gev_V1.7.root"); // Interface to TTree and TChain

	//ROOT::RDataFrame d0("ana_tree", "Reco_2305_160gev_V1.7.root");
	//auto d = d0.Range(0, 1000000);

	// Count of the total entries
	auto totentries = d.Count();

	// General set up
	// Binning
	const int nbins = 100;
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
	// Calorimeter cells
	int n_ECALx = 5;
	int n_ECALy = 6;
	//
	int n_VHCALx = 4;
	int n_VHCALy = 4;
	//
	int n_HCALx = 6;
	int n_HCALy = 3;

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

	// Columns taken as vectors from the data frame
	//auto ECALtot_vec = *d.Take<double, ROOT::VecOps::RVec<double>>("ECALtot");
	//auto VHCALtot_vec = *d.Take<double, ROOT::VecOps::RVec<double>>("VHCALtot");
	auto HCAL0tot_vec = *d.Take<double, ROOT::VecOps::RVec<double>>("HCAL0tot");
	//auto HCAL1tot_vec = *d.Take<double, ROOT::VecOps::RVec<double>>("HCAL1tot");

	auto GEM1x_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM1x");
	//auto GEM1y_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM1y");
	//auto GEM2x_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM2x");
	//auto GEM2y_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM2y");
	//auto GEM3x_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM3x");
	//auto GEM3y_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM3y");
	//auto GEM4x_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM4x");
	//auto GEM4y_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM4y");
	//auto MM1x_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM1x");
	//auto MM1y_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM1y");
	//auto MM2x_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM2x");
	//auto MM2y_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM2y");
	//auto MM3x_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM3x");
	//auto MM3y_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM3y");
	//auto MM4x_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM4x");
	//auto MM4y_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM4y");
	//auto MM5x_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM5x");
	//auto MM5y_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM5y");
	//auto MM6x_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM6x");
	//auto MM6y_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM6y");
	//auto MM7x_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM7x");
	//auto MM7y_vec = *d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM7y");

	// Initial values
	double t_spill = 4.8e9; // ns
	double t_accept = 10; // ns
	unsigned int n_bins = (unsigned int)(t_spill / t_accept);
	auto n_events = d.Count();

	// test values
	n_bins = 10;
	*n_events = 10;

	time_t t1 = time(0);
	cout << "Time control: Columns taken as vectors \t \t \t \t " << t1 - t0 << " s" << endl;

	// Random object definition
	TRandom3* random = new TRandom3();

	// Generate random bin tags and sort them
	ROOT::VecOps::RVec<int> bins_t;
	for (int i = 0; i < *n_events; i++) {
		bins_t.push_back(random->Integer(n_bins));
	}
	auto bins_t_sorted = Take(bins_t, Argsort(bins_t));

	time_t t2 = time(0);
	cout << "Time control: bin tags generated and sorted \t \t \t " << t2 - t0 << " s" << endl;

	// Count and store the multiplicities of the bin tags
	ROOT::VecOps::RVec<int> bin_multiplicities_t{ 1 };
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
	auto bin_multiplicities_t_sorted = Take(bin_multiplicities_t, Argsort(bin_multiplicities_t));

	time_t t3 = time(0);
	cout << "Time control: multiplicities obtained and sorted \t \t " << t3 - t0 << " s" << endl;

	// New data frame
	int n_bin_multiplicities = bin_multiplicities_t.size();
	ROOT::RDataFrame d_accidentals0(n_bin_multiplicities);
	int i_notMerged = 0;
	ROOT::VecOps::RVec<double> HCAL0tot_vec_merged = {};
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> GEM1x_vec_merged;
	for (int i = 0; i < n_bin_multiplicities; i++) {
		if (bin_multiplicities_t.at(i) == 1) {
			HCAL0tot_vec_merged.push_back(HCAL0tot_vec.at(i_notMerged));
			//HCAL0tot_vec_merged.push_back(*d.Range(i_notMerged, i_notMerged + bin_multiplicities_t.at(i)).Sum("HCAL0tot"));

			GEM1x_vec_merged.push_back(GEM1x_vec.at(i_notMerged));
		}
		else {
			ROOT::VecOps::RVec<int> range_vec(bin_multiplicities_t.at(i));
			std::iota(range_vec.begin(), range_vec.end(), i_notMerged);

			HCAL0tot_vec_merged.push_back( Sum( Take( HCAL0tot_vec, range_vec ) ) );
			//HCAL0tot_vec_merged.push_back(*d.Range(i_notMerged, i_notMerged + bin_multiplicities_t.at(i)).Sum("HCAL0tot"));
			ROOT::VecOps::RVec<double> GEM1x_aux_vec = {};
			for (int j = 0; j < bin_multiplicities_t.at(i); j++) {
				GEM1x_aux_vec.insert(GEM1x_aux_vec.end(), GEM1x_vec.at(i_notMerged + j).begin(), GEM1x_vec.at(i_notMerged + j).end());
			}
			GEM1x_vec_merged.push_back(GEM1x_aux_vec);
		}
		i_notMerged = i_notMerged + bin_multiplicities_t.at(i);
	}

	time_t t4 = time(0);
	cout << "Time control: merged columns obtained \t \t \t \t " << t4 - t0 << " s" << endl;

	int i_eventloop = 0;
	auto d_accidentals = d_accidentals0
		.Define("HCAL0tot", [&i_eventloop, HCAL0tot_vec_merged]() { double foo = HCAL0tot_vec_merged.at(i_eventloop); i_eventloop++; return foo; })
		.Define("GEM1x", [&i_eventloop, GEM1x_vec_merged]() { ROOT::VecOps::RVec<double> foo = GEM1x_vec_merged.at(i_eventloop); i_eventloop++; return foo; });

	time_t t5 = time(0);
	cout << "Time control: columns stored in new data frame (end) \t \t " << t5 - t0 << " s" << endl << endl;

	cout << bins_t_sorted << endl;
	cout << bin_multiplicities_t << endl;
	//cout << bin_multiplicities_t_sorted << endl;
	cout << HCAL0tot_vec_merged << endl;
	cout << *d.Range(0, *n_events).Take<double, ROOT::VecOps::RVec<double>>("HCAL0tot") << endl;
	cout << GEM1x_vec_merged << endl;
	cout << *d.Range(0, *n_events).Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM1x") << endl;

	// Check that the data is correctly stored in data frame
	//auto a_test = *d_accidentals.Take<double, ROOT::VecOps::RVec<double>>("HCAL0tot");
	//cout << a_test << endl;

	//auto d_fulltrigger = d_accidentals.Filter(cut_S0, { "Triggers" }).Filter(cut_S1, { "Triggers" }).Filter(cut_S4, { "Triggers" }).Filter(cut_Smu, { "Triggers" }).Filter(cut_antiV0, { "Triggers" });

	//auto acci_hHCAL0tot_test_filtered = d_accidentals.Histo1D({ "Name_hHCAL0tot","Title_hHCAL0tot", nbins, -1e-6, 20 }, "HCAL0tot");
	//auto acci_hGEM1x_test_filtered = d_accidentals.Histo1D({ "Name_hGEM1x","Title_hGEM1x", nbins, -80, 80 }, "GEM1x");

	//histogram_plot(acci_hHCAL0tot_test_filtered, "acci_hHCAL0tot_test_filtered", "Energy [GeV]", "Events", 1);
	//histogram_plot(acci_hGEM1x_test_filtered, "acci_hGEM1x_test_filtered", "x [mm]", "Events", 1);


	/*
	// Show the properties of the data frame
	d_accidentals.Describe().Print();
	std::cout << std::endl;
	// Alternative way: std::cout << d.Describe().AsString() << std::endl;
	//*/


}