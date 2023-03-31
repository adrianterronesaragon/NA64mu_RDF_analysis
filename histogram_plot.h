

void histogram_plot(ROOT::RDF::RResultPtr<TH1D> histo, TString name, const char* xlabel = "", const char* ylabel = "", int setlog = 0, int canvasform = 1, float xlabeloffset = 1, float ylabeloffset = 1, float xlabelsize = 0.04, float ylabelsize = 0.04, const char* drawoption = "", const char* canvasname = "", const char* canvastitle = "") {

	// Axis labels
	histo->GetXaxis()->SetTitle(xlabel);
	histo->GetYaxis()->SetTitle(ylabel);

	// Labels offset and size
	histo->GetXaxis()->SetTitleOffset(xlabeloffset);
	histo->GetXaxis()->SetLabelSize(xlabelsize);
	histo->GetYaxis()->SetTitleOffset(ylabeloffset);
	histo->GetYaxis()->SetLabelSize(ylabelsize);

	// Create canvas
	TCanvas* canvas = new TCanvas(canvasname, canvastitle, canvasform);

	// Draw the histogram into the canvas
	canvas->cd();
	histo->DrawCopy(drawoption);
	gPad->SetLogy(setlog);
	canvas->Update();

	canvas->SaveAs("../" + (TString)name + ".png");
}

void histogram_plot(ROOT::RDF::RResultPtr<TH2D> histo, TString name, const char* xlabel = "", const char* ylabel = "", int setlog = 0, int canvasform = 1, float xlabeloffset = 0.005, float ylabeloffset = 0.005, float xlabelsize = 0.04, float ylabelsize = 0.04, const char* drawoption = "", const char* canvasname = "", const char* canvastitle = "") {

	// Axis labels
	histo->GetXaxis()->SetTitle(xlabel);
	histo->GetYaxis()->SetTitle(ylabel);

	// Labels offset and size
	histo->GetXaxis()->SetTitleOffset(xlabeloffset);
	histo->GetXaxis()->SetLabelSize(xlabelsize);
	histo->GetYaxis()->SetTitleOffset(ylabeloffset);
	histo->GetYaxis()->SetLabelSize(ylabelsize);

	// Create canvas
	TCanvas* canvas = new TCanvas(canvasname, canvastitle, canvasform);

	// Draw the histogram into the canvas
	canvas->cd();
	histo->DrawCopy(drawoption);
	gPad->SetLogz(setlog);
	canvas->Update();

	canvas->SaveAs("../" + (TString) name + ".png");
}