
//distance of one hit from a given point in plane
double dist(double x, double y, double x0, double y0){
    return std::sqrt(std::pow(x - x0, 2) + std::pow(y - y0, 2));
}

//vector of distances for each hit in one tracker in one event
template<typename T>
T hit_distances_from_point(T xhits, T yhits, double x0, double y0) {
    T the_hit_distances_from_point;
    for(int i = 0; i<xhits.size(); i++){
        the_hit_distances_from_point.push_back(dist(xhits[i],yhits[i],x0,y0));
    }
    return the_hit_distances_from_point;
}

template<typename T>
bool inCircle(T r, double r0){
    bool isInCircle = true;
    for(int i = 0; i < r.size(); i++){
        if(r[i]>r0) {
            isInCircle=false;
            break;
        }
    }
    return isInCircle;
}

// map to call columns needed for a define/filter loop
std::vector<std::string> getColumns (TString theCol) {
    
    std::map<TString, std::vector<std::string>> theCols;
    theCols["no_cols"] = {};
    theCols["Triggers"] = {"Triggers"};
    theCols["singletrack_downstream"] = { "GEM1x", "GEM2x", "GEM3x", "GEM4x", "MM5x", "MM6x", "MM7x" };
    theCols["MM5"] = {"MM5x", "MM5y"};
    theCols["MM6"] = {"MM6x", "MM6y"};
    theCols["MM7"] = {"MM7x", "MM7y"};
    theCols["mmlarge_distances"] = {"r_mm5","r_mm6","r_mm7"};
    
    return theCols[theCol];
}

//get trigger configuration
template<typename T>
std::function<bool(T)> getTrig(TString trigname) {
    
    std::map<TString, std::function<bool(T)>> filters;
    filters["none"]      = [](T v) {return true;};
    filters["s0s1"]      = [](T v) {return v[0] > 0.0001 && v[1] > 0.0001; };
    filters["s4smu"]     = [](T v) {return v[2] > 0.0011 && v[3] > 0.0011; };
    filters["s0s1s4smu"] = [](T v) {return v[0] > 0.0001 && v[1] > 0.0001 && v[2] > 0.0011 && v[3] > 0.0011; };

    return filters[trigname];

}

// function list for new columns
// currently only works for two arguments
template<typename T>
std::function<T(T,T)> defineColumnExpression(TString colname) {
    
    std::map<TString, std::function<T(T,T)>> expressions;
    expressions["r_gem1"] = [](T v1, T v2){return hit_distances_from_point<T>(v1, v2,    0., -1428.6);};
    expressions["r_gem4"] = [](T v1, T v2){return hit_distances_from_point<T>(v1, v2,    0., -1540.4);}; 
    expressions["r_mm5"]  = [](T v1, T v2){return hit_distances_from_point<T>(v1, v2,  -7.5, -1633.0);};
    expressions["r_mm6"]  = [](T v1, T v2){return hit_distances_from_point<T>(v1, v2, -10.7, -1643.6);};
    expressions["r_mm7"]  = [](T v1, T v2){return hit_distances_from_point<T>(v1, v2, -12.4, -1654.5);};

    return expressions[colname];

}

// get list of cuts for filter loop
template<typename T>
std::function<bool(T)> getCut(TString cutname) {
    
    std::map<TString, std::function<bool(T)>> filters;
    filters["no_cuts"] = [](T v){return true;};
    filters["1_hit"]  = [](T v) {return v.size()==1; };
    filters["gem4inCore"] = [](T r) { return inCircle<T>(r,20); };

    return filters[cutname];

}


void rdf_general(){
    gROOT->SetBatch(kTRUE);
    TString filename = "../Reco_2305_160gev_V1.7.root"; // user input
    ROOT::EnableImplicitMT(); // Tell ROOT you want to go parallel
    ROOT::RDataFrame d("ana_tree", filename.Data()); // Interface to TTree and TChain
    
    ////////////////////////////// FLAGS //////////////////////////////////////
    // trigger tag
    TString the_df_trigger = "none";
    //TString the_df_trigger = "s0s1s4smu";

    // columns for define
    //std::vector<std::string> cols_as_args = {getColumns("no_cols")};
    std::vector< std::vector<std::string> > cols_as_args = {getColumns("MM5"), getColumns("MM6"), getColumns("MM7")};
    std::vector<std::string> new_col_names = getColumns("mmlarge_distances");

    // list of column names to which the corresponding cut from below is applied
    TString the_df_cut = "singletrack_downstream";
    std::vector<std::string> cols_for_cut = getColumns(the_df_cut);
    std::size_t N_cols_for_cut = cols_for_cut.size();

    // list of cut tags
    std::vector<TString> cut_labels(N_cols_for_cut,"1_hit"); 
    //////////////////////////// FLAGS END ////////////////////////////////////
    


    // filter procedure
    auto latestDF = std::make_unique<ROOT::RDF::RNode>(d); //it can only overwrite itself
    
    // trigger filter
    latestDF = std::make_unique<ROOT::RDF::RNode>(latestDF
        ->Filter(
            getTrig<ROOT::VecOps::RVec<double>>(the_df_trigger), 
            getColumns("Triggers")));
    
    // define columns
    for( auto i = 0u; i < new_col_names.size(); i++) {
        latestDF = std::make_unique<ROOT::RDF::RNode>(latestDF
            ->Define(
                new_col_names[i],
                defineColumnExpression<ROOT::VecOps::RVec<double>>(new_col_names[i]),
                cols_as_args[i]));
    }

    // cut filters
    for( auto i = 0u; i < cols_for_cut.size(); i++) {
        latestDF = std::make_unique<ROOT::RDF::RNode>(latestDF
            ->Filter(
                getCut<ROOT::VecOps::RVec<double>>(cut_labels[i]),
                {cols_for_cut[i]}));
    }

    TH1D myHisto = (TH1D)*latestDF->Histo1D("MM7x");
    TCanvas * ctest = new TCanvas();
    ctest->cd();
    myHisto.Draw();
    ctest->SaveAs("test.png");

    TH2D myHisto2 = (TH2D)*latestDF->Histo2D({"h_mm7", "MM 7", 200, -200., 60., 200, -1654.5-40, -1654.5+40},"MM7x","MM7y");
    TCanvas * ctest2 = new TCanvas();
    ctest2->cd();
    gPad->SetLogz();
    myHisto2.Draw("colz");
    ctest2->SaveAs("test2.png");
    //d.Describe().Print(); std::cout << std::endl;
}