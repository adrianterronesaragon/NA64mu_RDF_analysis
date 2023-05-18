
#include "histogram_plot.h"
#include "ROOT/RVec.hxx"

void accidentals_RDataFrame() {

	time_t t0 = time(0);
	cout << "Time control: End of compiling" << endl;



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



	// Option for not showing plots after compiling
	gROOT->SetBatch(kTRUE);

	// To include headers from another folder
	//R__ADD_INCLUDE_PATH(<name of the path>);

	// Definition of the data frame
	ROOT::EnableImplicitMT(); // Tell ROOT you want to go parallel
	ROOT::RDataFrame d0("ana_tree", "../Reco_2305_160gev_V1.7.root"); // Interface to TTree and TChain
	
	// For Range
	//ROOT::RDataFrame d0Range("ana_tree", "../Reco_2305_160gev_V1.7.root");
	//auto d0 = d0Range.Range(0, 800000);

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

	// Count of the total entries
	auto totentries = d.Count();

	time_t t_initDataFrame = time(0);
	cout << "Time control: Dataframe initialised \t \t \t \t " << t_initDataFrame - t0 << " s" << endl;




	// Columns taken as vectors from the data frame
	auto ECALtot_vec = d.Take<double, ROOT::VecOps::RVec<double>>("ECALtot");
	auto VHCALtot_vec = d.Take<double, ROOT::VecOps::RVec<double>>("VHCALtot");
	auto HCAL0tot_vec = d.Take<double, ROOT::VecOps::RVec<double>>("HCAL0tot");
	auto HCAL1tot_vec = d.Take<double, ROOT::VecOps::RVec<double>>("HCAL1tot");

	ROOT::RDF::RResultPtr<ROOT::VecOps::RVec<double>> ECALenergy_vec[n_ECALx][n_ECALy];
	for (int i = 0; i < n_ECALx; i++) {
		for (int j = 0; j < n_ECALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"ECALenergy_" + i_str + j_str;
			ECALenergy_vec[i][j] = d.Take<double, ROOT::VecOps::RVec<double>>(str);
		}
	}
	ROOT::RDF::RResultPtr<ROOT::VecOps::RVec<double>> VHCALenergy_vec[n_VHCALx][n_VHCALy];
	for (int i = 0; i < n_VHCALx; i++) {
		for (int j = 0; j < n_VHCALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"VHCALenergy_" + i_str + j_str;
			VHCALenergy_vec[i][j] = d.Take<double, ROOT::VecOps::RVec<double>>(str);
		}
	}
	ROOT::RDF::RResultPtr<ROOT::VecOps::RVec<double>> HCAL0energy_vec[n_HCALx][n_HCALy];
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"HCAL0energy_" + i_str + j_str;
			HCAL0energy_vec[i][j] = d.Take<double, ROOT::VecOps::RVec<double>>(str);
		}
	}
	ROOT::RDF::RResultPtr<ROOT::VecOps::RVec<double>> HCAL1energy_vec[n_HCALx][n_HCALy];
	for (int i = 0; i < n_HCALx; i++) {
		for (int j = 0; j < n_HCALy; j++) {
			TString i_str = (TString)to_string(i);
			TString j_str = (TString)to_string(j);
			TString str = (TString)"HCAL1energy_" + i_str + j_str;
			HCAL1energy_vec[i][j] = d.Take<double, ROOT::VecOps::RVec<double>>(str);
		}
	}

	auto S0_vec = d.Take<double, ROOT::VecOps::RVec<double>>("S0");
	auto S1_vec = d.Take<double, ROOT::VecOps::RVec<double>>("S1");
	auto S4_vec = d.Take<double, ROOT::VecOps::RVec<double>>("S4");
	auto Smu_vec = d.Take<double, ROOT::VecOps::RVec<double>>("Smu");
	auto V0_vec = d.Take<double, ROOT::VecOps::RVec<double>>("V0");

	auto GEM1x_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM1x");
	auto GEM1y_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM1y");
	auto GEM2x_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM2x");
	auto GEM2y_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM2y");
	auto GEM3x_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM3x");
	auto GEM3y_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM3y");
	auto GEM4x_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM4x");
	auto GEM4y_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM4y");
	auto MM1x_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM1x");
	auto MM1y_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM1y");
	auto MM2x_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM2x");
	auto MM2y_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM2y");
	auto MM3x_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM3x");
	auto MM3y_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM3y");
	auto MM4x_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM4x");
	auto MM4y_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM4y");
	auto MM5x_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM5x");
	auto MM5y_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM5y");
	auto MM6x_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM6x");
	auto MM6y_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM6y");
	auto MM7x_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM7x");
	auto MM7y_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("MM7y");

	// Initial values
	double t_spill = 4.8e9; // ns
	double t_accept = 10; // ns
	unsigned int n_bins = (unsigned int)(t_spill / t_accept);
	auto n_events = d.Count();

	// test values
	//n_bins = 6;
	//*n_events = 10;

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
	//auto bin_multiplicities_t_sorted = Take(bin_multiplicities_t, Argsort(bin_multiplicities_t));

	time_t t3 = time(0);
	cout << "Time control: multiplicities obtained and sorted \t \t " << t3 - t0 << " s" << endl;

	// New data frame
	int n_bin_multiplicities = bin_multiplicities_t.size();
	int i_notMerged = 0;

	ROOT::VecOps::RVec<double> ECALtot_vec_merged;
	ROOT::VecOps::RVec<double> VHCALtot_vec_merged;
	ROOT::VecOps::RVec<double> HCAL0tot_vec_merged;
	ROOT::VecOps::RVec<double> HCAL1tot_vec_merged;

	ROOT::VecOps::RVec<double> ECALenergy_vec_merged[n_ECALx][n_ECALy];
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> ECALenergies_vec_merged;
	ROOT::VecOps::RVec<double> VHCALenergy_vec_merged[n_VHCALx][n_VHCALy];
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> VHCALenergies_vec_merged;
	ROOT::VecOps::RVec<double> HCAL0energy_vec_merged[n_HCALx][n_HCALy];
	ROOT::VecOps::RVec<double> HCAL1energy_vec_merged[n_HCALx][n_HCALy];
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> HCALenergy_vec_merged;

	ROOT::VecOps::RVec<double> S0_vec_merged;
	ROOT::VecOps::RVec<double> S1_vec_merged;
	ROOT::VecOps::RVec<double> S4_vec_merged;
	ROOT::VecOps::RVec<double> Smu_vec_merged;
	ROOT::VecOps::RVec<double> V0_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> Triggers_vec_merged;

	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> GEM1x_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> GEM1y_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> GEM2x_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> GEM2y_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> GEM3x_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> GEM3y_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> GEM4x_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> GEM4y_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM1x_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM1y_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM2x_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM2y_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM3x_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM3y_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM4x_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM4y_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM5x_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM5y_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM6x_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM6y_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM7x_vec_merged;
	ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>> MM7y_vec_merged;

	ROOT::VecOps::RVec<bool> isMerged_vec;

	for (int i = 0; i < n_bin_multiplicities; i++) {
		if (bin_multiplicities_t.at(i) == 1) {
			// double type columns (calorimeters & triggers)
			ECALtot_vec_merged.push_back(ECALtot_vec->at(i_notMerged));
			VHCALtot_vec_merged.push_back(VHCALtot_vec->at(i_notMerged));
			HCAL0tot_vec_merged.push_back(HCAL0tot_vec->at(i_notMerged));
			HCAL1tot_vec_merged.push_back(HCAL1tot_vec->at(i_notMerged));

			for (int k = 0; k < n_ECALx; k++) {
				for (int j = 0; j < n_ECALy; j++) {
					ECALenergy_vec_merged[k][j].push_back(ECALenergy_vec[k][j]->at(i_notMerged));
				}
			}
			for (int k = 0; k < n_VHCALx; k++) {
				for (int j = 0; j < n_VHCALy; j++) {
					VHCALenergy_vec_merged[k][j].push_back(VHCALenergy_vec[k][j]->at(i_notMerged));
				}
			}
			for (int k = 0; k < n_HCALx; k++) {
				for (int j = 0; j < n_HCALy; j++) {
					HCAL0energy_vec_merged[k][j].push_back(HCAL0energy_vec[k][j]->at(i_notMerged));
					HCAL1energy_vec_merged[k][j].push_back(HCAL1energy_vec[k][j]->at(i_notMerged));
				}
			}

			S0_vec_merged.push_back(S0_vec->at(i_notMerged));
			S1_vec_merged.push_back(S1_vec->at(i_notMerged));
			S4_vec_merged.push_back(S4_vec->at(i_notMerged));
			Smu_vec_merged.push_back(Smu_vec->at(i_notMerged));
			V0_vec_merged.push_back(V0_vec->at(i_notMerged));

			// RVec<double> type columns (trackers)
			GEM1x_vec_merged.push_back(GEM1x_vec->at(i_notMerged));
			GEM1y_vec_merged.push_back(GEM1y_vec->at(i_notMerged));
			GEM2x_vec_merged.push_back(GEM2x_vec->at(i_notMerged));
			GEM2y_vec_merged.push_back(GEM2y_vec->at(i_notMerged));
			GEM3x_vec_merged.push_back(GEM3x_vec->at(i_notMerged));
			GEM3y_vec_merged.push_back(GEM3y_vec->at(i_notMerged));
			GEM4x_vec_merged.push_back(GEM4x_vec->at(i_notMerged));
			GEM4y_vec_merged.push_back(GEM4y_vec->at(i_notMerged));
			MM1x_vec_merged.push_back(MM1x_vec->at(i_notMerged));
			MM1y_vec_merged.push_back(MM1y_vec->at(i_notMerged));
			MM2x_vec_merged.push_back(MM2x_vec->at(i_notMerged));
			MM2y_vec_merged.push_back(MM2y_vec->at(i_notMerged));
			MM3x_vec_merged.push_back(MM3x_vec->at(i_notMerged));
			MM3y_vec_merged.push_back(MM3y_vec->at(i_notMerged));
			MM4x_vec_merged.push_back(MM4x_vec->at(i_notMerged));
			MM4y_vec_merged.push_back(MM4y_vec->at(i_notMerged));
			MM5x_vec_merged.push_back(MM5x_vec->at(i_notMerged));
			MM5y_vec_merged.push_back(MM5y_vec->at(i_notMerged));
			MM6x_vec_merged.push_back(MM6x_vec->at(i_notMerged));
			MM6y_vec_merged.push_back(MM6y_vec->at(i_notMerged));
			MM7x_vec_merged.push_back(MM7x_vec->at(i_notMerged));
			MM7y_vec_merged.push_back(MM7y_vec->at(i_notMerged));

			isMerged_vec.push_back(0);
		}
		else {
			ROOT::VecOps::RVec<int> range_vec(bin_multiplicities_t.at(i));
			std::iota(range_vec.begin(), range_vec.end(), i_notMerged);

			// double type columns (calorimeters & triggers)
			ECALtot_vec_merged.push_back(Sum(Take(*ECALtot_vec, range_vec)));
			VHCALtot_vec_merged.push_back(Sum(Take(*VHCALtot_vec, range_vec)));
			HCAL0tot_vec_merged.push_back(Sum(Take(*HCAL0tot_vec, range_vec)));
			HCAL1tot_vec_merged.push_back(Sum(Take(*HCAL1tot_vec, range_vec)));

			for (int k = 0; k < n_ECALx; k++) {
				for (int j = 0; j < n_ECALy; j++) {
					ECALenergy_vec_merged[k][j].push_back(Sum(Take(*ECALenergy_vec[k][j], range_vec)));
				}
			}
			for (int k = 0; k < n_VHCALx; k++) {
				for (int j = 0; j < n_VHCALy; j++) {
					VHCALenergy_vec_merged[k][j].push_back(Sum(Take(*VHCALenergy_vec[k][j], range_vec)));
				}
			}
			for (int k = 0; k < n_HCALx; k++) {
				for (int j = 0; j < n_HCALy; j++) {
					HCAL0energy_vec_merged[k][j].push_back(Sum(Take(*HCAL0energy_vec[k][j], range_vec)));
					HCAL1energy_vec_merged[k][j].push_back(Sum(Take(*HCAL1energy_vec[k][j], range_vec)));
				}
			}

			S0_vec_merged.push_back(Sum(Take(*S0_vec, range_vec)));
			S1_vec_merged.push_back(Sum(Take(*S1_vec, range_vec)));
			S4_vec_merged.push_back(Sum(Take(*S4_vec, range_vec)));
			Smu_vec_merged.push_back(Sum(Take(*Smu_vec, range_vec)));
			V0_vec_merged.push_back(Sum(Take(*V0_vec, range_vec)));

			// RVec<double> type columns (trackers)
			ROOT::VecOps::RVec<double> GEM1x_aux_vec = {};
			ROOT::VecOps::RVec<double> GEM1y_aux_vec = {};
			ROOT::VecOps::RVec<double> GEM2x_aux_vec = {};
			ROOT::VecOps::RVec<double> GEM2y_aux_vec = {};
			ROOT::VecOps::RVec<double> GEM3x_aux_vec = {};
			ROOT::VecOps::RVec<double> GEM3y_aux_vec = {};
			ROOT::VecOps::RVec<double> GEM4x_aux_vec = {};
			ROOT::VecOps::RVec<double> GEM4y_aux_vec = {};
			ROOT::VecOps::RVec<double> MM1x_aux_vec = {};
			ROOT::VecOps::RVec<double> MM1y_aux_vec = {};
			ROOT::VecOps::RVec<double> MM2x_aux_vec = {};
			ROOT::VecOps::RVec<double> MM2y_aux_vec = {};
			ROOT::VecOps::RVec<double> MM3x_aux_vec = {};
			ROOT::VecOps::RVec<double> MM3y_aux_vec = {};
			ROOT::VecOps::RVec<double> MM4x_aux_vec = {};
			ROOT::VecOps::RVec<double> MM4y_aux_vec = {};
			ROOT::VecOps::RVec<double> MM5x_aux_vec = {};
			ROOT::VecOps::RVec<double> MM5y_aux_vec = {};
			ROOT::VecOps::RVec<double> MM6x_aux_vec = {};
			ROOT::VecOps::RVec<double> MM6y_aux_vec = {};
			ROOT::VecOps::RVec<double> MM7x_aux_vec = {};
			ROOT::VecOps::RVec<double> MM7y_aux_vec = {};
			//
			for (int j = 0; j < bin_multiplicities_t.at(i); j++) {
				GEM1x_aux_vec.insert(GEM1x_aux_vec.end(), GEM1x_vec->at(i_notMerged + j).begin(), GEM1x_vec->at(i_notMerged + j).end());
				GEM1y_aux_vec.insert(GEM1y_aux_vec.end(), GEM1y_vec->at(i_notMerged + j).begin(), GEM1y_vec->at(i_notMerged + j).end());
				GEM2x_aux_vec.insert(GEM2x_aux_vec.end(), GEM2x_vec->at(i_notMerged + j).begin(), GEM2x_vec->at(i_notMerged + j).end());
				GEM2y_aux_vec.insert(GEM2y_aux_vec.end(), GEM2y_vec->at(i_notMerged + j).begin(), GEM2y_vec->at(i_notMerged + j).end());
				GEM3x_aux_vec.insert(GEM3x_aux_vec.end(), GEM3x_vec->at(i_notMerged + j).begin(), GEM3x_vec->at(i_notMerged + j).end());
				GEM3y_aux_vec.insert(GEM3y_aux_vec.end(), GEM3y_vec->at(i_notMerged + j).begin(), GEM3y_vec->at(i_notMerged + j).end());
				GEM4x_aux_vec.insert(GEM4x_aux_vec.end(), GEM4x_vec->at(i_notMerged + j).begin(), GEM4x_vec->at(i_notMerged + j).end());
				GEM4y_aux_vec.insert(GEM4y_aux_vec.end(), GEM4y_vec->at(i_notMerged + j).begin(), GEM4y_vec->at(i_notMerged + j).end());
				MM1x_aux_vec.insert(MM1x_aux_vec.end(), MM1x_vec->at(i_notMerged + j).begin(), MM1x_vec->at(i_notMerged + j).end());
				MM1y_aux_vec.insert(MM1y_aux_vec.end(), MM1y_vec->at(i_notMerged + j).begin(), MM1y_vec->at(i_notMerged + j).end());
				MM2x_aux_vec.insert(MM2x_aux_vec.end(), MM2x_vec->at(i_notMerged + j).begin(), MM2x_vec->at(i_notMerged + j).end());
				MM2y_aux_vec.insert(MM2y_aux_vec.end(), MM2y_vec->at(i_notMerged + j).begin(), MM2y_vec->at(i_notMerged + j).end());
				MM3x_aux_vec.insert(MM3x_aux_vec.end(), MM3x_vec->at(i_notMerged + j).begin(), MM3x_vec->at(i_notMerged + j).end());
				MM3y_aux_vec.insert(MM3y_aux_vec.end(), MM3y_vec->at(i_notMerged + j).begin(), MM3y_vec->at(i_notMerged + j).end());
				MM4x_aux_vec.insert(MM4x_aux_vec.end(), MM4x_vec->at(i_notMerged + j).begin(), MM4x_vec->at(i_notMerged + j).end());
				MM4y_aux_vec.insert(MM4y_aux_vec.end(), MM4y_vec->at(i_notMerged + j).begin(), MM4y_vec->at(i_notMerged + j).end());
				MM5x_aux_vec.insert(MM5x_aux_vec.end(), MM5x_vec->at(i_notMerged + j).begin(), MM5x_vec->at(i_notMerged + j).end());
				MM5y_aux_vec.insert(MM5y_aux_vec.end(), MM5y_vec->at(i_notMerged + j).begin(), MM5y_vec->at(i_notMerged + j).end());
				MM6x_aux_vec.insert(MM6x_aux_vec.end(), MM6x_vec->at(i_notMerged + j).begin(), MM6x_vec->at(i_notMerged + j).end());
				MM6y_aux_vec.insert(MM6y_aux_vec.end(), MM6y_vec->at(i_notMerged + j).begin(), MM6y_vec->at(i_notMerged + j).end());
				MM7x_aux_vec.insert(MM7x_aux_vec.end(), MM7x_vec->at(i_notMerged + j).begin(), MM7x_vec->at(i_notMerged + j).end());
				MM7y_aux_vec.insert(MM7y_aux_vec.end(), MM7y_vec->at(i_notMerged + j).begin(), MM7y_vec->at(i_notMerged + j).end());
			}
			//
			GEM1x_vec_merged.push_back(GEM1x_aux_vec);
			GEM1y_vec_merged.push_back(GEM1y_aux_vec);
			GEM2x_vec_merged.push_back(GEM2x_aux_vec);
			GEM2y_vec_merged.push_back(GEM2y_aux_vec);
			GEM3x_vec_merged.push_back(GEM3x_aux_vec);
			GEM3y_vec_merged.push_back(GEM3y_aux_vec);
			GEM4x_vec_merged.push_back(GEM4x_aux_vec);
			GEM4y_vec_merged.push_back(GEM4y_aux_vec);
			MM1x_vec_merged.push_back(MM1x_aux_vec);
			MM1y_vec_merged.push_back(MM1y_aux_vec);
			MM2x_vec_merged.push_back(MM2x_aux_vec);
			MM2y_vec_merged.push_back(MM2y_aux_vec);
			MM3x_vec_merged.push_back(MM3x_aux_vec);
			MM3y_vec_merged.push_back(MM3y_aux_vec);
			MM4x_vec_merged.push_back(MM4x_aux_vec);
			MM4y_vec_merged.push_back(MM4y_aux_vec);
			MM5x_vec_merged.push_back(MM5x_aux_vec);
			MM5y_vec_merged.push_back(MM5y_aux_vec);
			MM6x_vec_merged.push_back(MM6x_aux_vec);
			MM6y_vec_merged.push_back(MM6y_aux_vec);
			MM7x_vec_merged.push_back(MM7x_aux_vec);
			MM7y_vec_merged.push_back(MM7y_aux_vec);

			isMerged_vec.push_back(1);
		}

		// Reconstruct the shape of Triggers column
		ROOT::VecOps::RVec<double> Triggers_aux_vec_merged;
		Triggers_aux_vec_merged.push_back(S0_vec_merged.at(i));
		Triggers_aux_vec_merged.push_back(S1_vec_merged.at(i));
		Triggers_aux_vec_merged.push_back(S4_vec_merged.at(i));
		Triggers_aux_vec_merged.push_back(Smu_vec_merged.at(i));
		Triggers_aux_vec_merged.push_back(V0_vec_merged.at(i));
		//
		Triggers_vec_merged.push_back(Triggers_aux_vec_merged);

		// Reconstruct the shape of calorimeter cells columns
		ROOT::VecOps::RVec<double> ECALenergy_aux_vec_merged;
		ROOT::VecOps::RVec<double> VHCALenergy_aux_vec_merged;
		ROOT::VecOps::RVec<double> HCALenergy_aux_vec_merged;
		//
		for (int j = 0; j < n_ECALy; j++) {
			for (int k = 0; k < n_ECALx; k++) {
				ECALenergy_aux_vec_merged.push_back(ECALenergy_vec_merged[k][j].at(i));
			}
		}
		for (int j = 0; j < n_VHCALy; j++) {
			for (int k = 0; k < n_VHCALx; k++) {
				VHCALenergy_aux_vec_merged.push_back(VHCALenergy_vec_merged[k][j].at(i));
			}
		}
		for (int j = 0; j < n_HCALy; j++) {
			for (int k = 0; k < n_HCALx; k++) {
				HCALenergy_aux_vec_merged.push_back(HCAL0energy_vec_merged[k][j].at(i));
			}
		}
		for (int j = 0; j < n_HCALy; j++) {
			for (int k = 0; k < n_HCALx; k++) {
				HCALenergy_aux_vec_merged.push_back(HCAL1energy_vec_merged[k][j].at(i));
			}
		}
		//
		ECALenergies_vec_merged.push_back(ECALenergy_aux_vec_merged);
		VHCALenergies_vec_merged.push_back(VHCALenergy_aux_vec_merged);
		HCALenergy_vec_merged.push_back(HCALenergy_aux_vec_merged);

		i_notMerged = i_notMerged + bin_multiplicities_t.at(i);
	}

	time_t t4 = time(0);
	cout << "Time control: merged columns obtained \t \t \t \t " << t4 - t0 << " s" << endl;

	ROOT::RDataFrame d_accidentals0(n_bin_multiplicities);
	int i_eventloop = 0;
	auto d_accidentals = d_accidentals0
		.Define("Triggers", [&i_eventloop, Triggers_vec_merged]() { ROOT::VecOps::RVec<double> foo = Triggers_vec_merged.at(i_eventloop); return foo; })
		.Define("ECALtot", [&i_eventloop, ECALtot_vec_merged]() { double foo = ECALtot_vec_merged.at(i_eventloop); return foo; })
		.Define("VHCALtot", [&i_eventloop, VHCALtot_vec_merged]() { double foo = VHCALtot_vec_merged.at(i_eventloop); return foo; })
		.Define("HCAL0tot", [&i_eventloop, HCAL0tot_vec_merged]() { double foo = HCAL0tot_vec_merged.at(i_eventloop); return foo; })
		.Define("HCAL1tot", [&i_eventloop, HCAL1tot_vec_merged]() { double foo = HCAL1tot_vec_merged.at(i_eventloop); return foo; })
		.Define("ECALenergy", [&i_eventloop, ECALenergies_vec_merged]() { ROOT::VecOps::RVec<double> foo = ECALenergies_vec_merged.at(i_eventloop); return foo; })
		.Define("VHCALenergy", [&i_eventloop, VHCALenergies_vec_merged]() { ROOT::VecOps::RVec<double> foo = VHCALenergies_vec_merged.at(i_eventloop); return foo; })
		.Define("HCALenergy", [&i_eventloop, HCALenergy_vec_merged]() { ROOT::VecOps::RVec<double> foo = HCALenergy_vec_merged.at(i_eventloop); return foo; })
		.Define("GEM1x", [&i_eventloop, GEM1x_vec_merged]() { ROOT::VecOps::RVec<double> foo = GEM1x_vec_merged.at(i_eventloop); return foo; })
		.Define("GEM1y", [&i_eventloop, GEM1y_vec_merged]() { ROOT::VecOps::RVec<double> foo = GEM1y_vec_merged.at(i_eventloop); return foo; })
		.Define("GEM2x", [&i_eventloop, GEM2x_vec_merged]() { ROOT::VecOps::RVec<double> foo = GEM2x_vec_merged.at(i_eventloop); return foo; })
		.Define("GEM2y", [&i_eventloop, GEM2y_vec_merged]() { ROOT::VecOps::RVec<double> foo = GEM2y_vec_merged.at(i_eventloop); return foo; })
		.Define("GEM3x", [&i_eventloop, GEM3x_vec_merged]() { ROOT::VecOps::RVec<double> foo = GEM3x_vec_merged.at(i_eventloop); return foo; })
		.Define("GEM3y", [&i_eventloop, GEM3y_vec_merged]() { ROOT::VecOps::RVec<double> foo = GEM3y_vec_merged.at(i_eventloop); return foo; })
		.Define("GEM4x", [&i_eventloop, GEM4x_vec_merged]() { ROOT::VecOps::RVec<double> foo = GEM4x_vec_merged.at(i_eventloop); return foo; })
		.Define("GEM4y", [&i_eventloop, GEM4y_vec_merged]() { ROOT::VecOps::RVec<double> foo = GEM4y_vec_merged.at(i_eventloop); return foo; })
		.Define("MM1x", [&i_eventloop, MM1x_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM1x_vec_merged.at(i_eventloop); return foo; })
		.Define("MM1y", [&i_eventloop, MM1y_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM1y_vec_merged.at(i_eventloop); return foo; })
		.Define("MM2x", [&i_eventloop, MM2x_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM2x_vec_merged.at(i_eventloop); return foo; })
		.Define("MM2y", [&i_eventloop, MM2y_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM2y_vec_merged.at(i_eventloop); return foo; })
		.Define("MM3x", [&i_eventloop, MM3x_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM3x_vec_merged.at(i_eventloop); return foo; })
		.Define("MM3y", [&i_eventloop, MM3y_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM3y_vec_merged.at(i_eventloop); return foo; })
		.Define("MM4x", [&i_eventloop, MM4x_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM4x_vec_merged.at(i_eventloop); return foo; })
		.Define("MM4y", [&i_eventloop, MM4y_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM4y_vec_merged.at(i_eventloop); return foo; })
		.Define("MM5x", [&i_eventloop, MM5x_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM5x_vec_merged.at(i_eventloop); return foo; })
		.Define("MM5y", [&i_eventloop, MM5y_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM5y_vec_merged.at(i_eventloop); return foo; })
		.Define("MM6x", [&i_eventloop, MM6x_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM6x_vec_merged.at(i_eventloop); return foo; })
		.Define("MM6y", [&i_eventloop, MM6y_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM6y_vec_merged.at(i_eventloop); return foo; })
		.Define("MM7x", [&i_eventloop, MM7x_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM7x_vec_merged.at(i_eventloop); return foo; })
		.Define("MM7y", [&i_eventloop, MM7y_vec_merged]() { ROOT::VecOps::RVec<double> foo = MM7y_vec_merged.at(i_eventloop); return foo; })
		.Define("isMerged", [&i_eventloop, isMerged_vec]() { bool foo = isMerged_vec.at(i_eventloop); i_eventloop++; return foo; })
		;

	time_t t5 = time(0);
	cout << "Time control: columns stored in new data frame \t \t \t " << t5 - t0 << " s" << endl;

	// Write out the new dataframe as a ROOT file
	d_accidentals.Snapshot("accidentals_tree", "../Reco_2305_160gev_V1.7_accidentals.root", {"Triggers"
		, "ECALtot"
		, "VHCALtot"
		, "HCAL0tot"
		, "HCAL1tot"
		, "ECALenergy"
		, "VHCALenergy"
		, "HCALenergy"
		, "GEM1x"
		, "GEM1y"
		, "GEM2x"
		, "GEM2y"
		, "GEM3x"
		, "GEM3y"
		, "GEM4x"
		, "GEM4y"
		, "MM1x"
		, "MM1y"
		, "MM2x"
		, "MM2y"
		, "MM3x"
		, "MM3y"
		, "MM4x"
		, "MM4y"
		, "MM5x"
		, "MM5y"
		, "MM6x"
		, "MM6y"
		, "MM7x"
		, "MM7y"
		, "isMerged"
		});

	time_t t6 = time(0);
	cout << "Time control: data frame stored in new ROOT file (end) \t \t " << t6 - t0 << " s" << endl << endl;

	/*
	// Checks that the data is correctly stored in data frame
	cout << "Bins (sorted): \t \t" << bins_t_sorted << endl;
	cout << "Bin multiplicities: \t" << bin_multiplicities_t << endl;
	//cout << "Bin multiplicities (sorted): " << bin_multiplicities_t_sorted << endl;
	cout << "HCALtot: \t \t" << *d.Range(0, *n_events).Take<double, ROOT::VecOps::RVec<double>>("HCAL0tot") << endl;
	cout << "HCALtot (merged): \t" << HCAL0tot_vec_merged << endl;
	cout << "GEM1x: \t \t \t" << *d.Range(0, *n_events).Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("GEM1x") << endl;
	cout << "GEM1x (merged): \t" << GEM1x_vec_merged << endl;
	//cout << "S0 (merged): \t \t" << S0_vec_merged << endl;
	//cout << "S1 (merged): \t \t" << S1_vec_merged << endl;
	//cout << "S4 (merged): \t \t" << S4_vec_merged << endl;
	//cout << "Smu (merged): \t \t" << Smu_vec_merged << endl;
	//cout << "V0 (merged): \t \t" << V0_vec_merged << endl;
	//cout << "Triggers (merged): \t" << Triggers_vec_merged << endl;
	std::cout << "isMerged: \t \t" << isMerged_vec << std::endl;
	//auto a_test = *d_accidentals.Take<double, ROOT::VecOps::RVec<double>>("HCAL0tot");
	//cout << a_test << endl;
	//*/
	//auto Triggers_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("Triggers");
	//cout << "Triggers: \t" << *Triggers_vec << endl;
	//auto HCAL1energy_vec = d.Take<vector<double>, ROOT::VecOps::RVec<ROOT::VecOps::RVec<double>>>("HCAL1energy");
	//cout << "HCAL1energy: \t" << *HCAL1energy_vec << endl;


	/*
	auto d_accidentals_trigger3 = d_accidentals.Filter(cut_S0, { "Triggers" }).Filter(cut_S1, { "Triggers" }).Filter(cut_S4, { "Triggers" }).Filter(cut_Smu, { "Triggers" }).Filter(cut_antiV0, { "Triggers" });

	auto acci_hHCAL0tot_test_unfiltered = d_accidentals.Histo1D({ "Name_hHCAL0tot","Title_hHCAL0tot", nbins, -1e-6, 20 }, "HCAL0tot");
	//auto acci_hGEM1x_test_unfiltered = d_accidentals.Histo1D({ "Name_hGEM1x","Title_hGEM1x", nbins, -80, 80 }, "GEM1x"); => Why is this making trouble with event loop??

	auto acci_hHCAL0tot_test_filtered = d_accidentals_trigger3.Histo1D({ "Name_hHCAL0tot","Title_hHCAL0tot", nbins, -1e-6, 20 }, "HCAL0tot");
	auto acci_hGEM1x_test_filtered = d_accidentals_trigger3.Histo1D({ "Name_hGEM1x","Title_hGEM1x", nbins, -80, 80 }, "GEM1x");

	histogram_plot(acci_hHCAL0tot_test_unfiltered, "acci_hHCAL0tot_test_unfiltered", "Energy [GeV]", "Events", 1);
	//histogram_plot(acci_hGEM1x_test_unfiltered, "acci_hGEM1x_test_unfiltered", "x [mm]", "Events", 1);

	histogram_plot(acci_hHCAL0tot_test_filtered, "acci_hHCAL0tot_test_filtered", "Energy [GeV]", "Events", 1);
	histogram_plot(acci_hGEM1x_test_filtered, "acci_hGEM1x_test_filtered", "x [mm]", "Events", 1);
	*/


	/*
	// Show the properties of the data frame
	cout << endl;
	d.Describe().Print();
	std::cout << std::endl;
	// Alternative way: std::cout << d.Describe().AsString() << std::endl;
	//*/

	/*
	std::cout << std::endl;
	std::cout << d.GetNRuns();
	std::cout << std::endl;
	//*/

	//*
	// Show the properties of the data frame
	cout << endl;
	d_accidentals.Describe().Print();
	std::cout << std::endl;
	// Alternative way: std::cout << d.Describe().AsString() << std::endl;
	//*/


}