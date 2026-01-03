void SetStyle(Bool_t graypalette = kTRUE);

void sethisto(TH2D *r1__1) {
  r1__1->SetStats(0);
  // r1__1->GetXaxis()->SetTitle("p_{T}[GeV/c]");
  // r1__1->GetXaxis()->CenterTitle(true);
  r1__1->GetXaxis()->SetLabelFont(42);
  r1__1->GetXaxis()->SetNdivisions(510);
  r1__1->GetXaxis()->SetLabelOffset(0.01);
  r1__1->GetXaxis()->SetLabelSize(0.05);
  r1__1->GetXaxis()->SetTitleSize(0.05);
  r1__1->GetXaxis()->SetTickLength(0.04);
  r1__1->GetXaxis()->SetTitleOffset(1.2);
  r1__1->GetXaxis()->SetTitleFont(42);

  // r1__1->GetYaxis()->SetTitle("#frac{1}{2#piN_{eV}} #frac{d^{2}N}{dy dp_{T}}
  // [(GeV/c)^{-1}]");
  r1__1->GetYaxis()->SetNdivisions(510);
  r1__1->GetYaxis()->SetLabelFont(42);
  r1__1->GetYaxis()->SetLabelOffset(0.01);
  r1__1->GetYaxis()->SetLabelSize(0.075);
  r1__1->GetYaxis()->SetTitleSize(0.075);
  r1__1->GetYaxis()->SetTickLength(0.025);
  r1__1->GetYaxis()->SetTitleOffset(0.85);
  r1__1->GetYaxis()->SetTitleFont(42);

  // r1__1->GetYaxis()->SetMoreLogLabels(kTRUE);
  r1__1->Draw("");
}
void sethistodown(TH2D *r1__1) {
  r1__1->SetStats(0);
  // r1__1->GetXaxis()->SetTitle("Centrality (%)");
  // r1__1->GetXaxis()->CenterTitle(true);
  r1__1->GetXaxis()->SetLabelFont(42);
  r1__1->GetXaxis()->SetLabelOffset(0.01);
  r1__1->GetXaxis()->SetLabelSize(0.175);
  r1__1->GetXaxis()->SetTitleSize(0.18);
  r1__1->GetXaxis()->SetTickLength(0.09);
  r1__1->GetXaxis()->SetTitleOffset(0.90);
  r1__1->GetXaxis()->SetTitleFont(42);
  r1__1->GetXaxis()->SetNdivisions(510);

  // r1__1->GetYaxis()->SetTitle("#LT#epsilon_{n}#GT");
  r1__1->GetYaxis()->SetLabelFont(42);
  r1__1->GetYaxis()->SetLabelOffset(0.01);
  r1__1->GetYaxis()->SetLabelSize(0.175);
  r1__1->GetYaxis()->SetTitleSize(0.18);
  r1__1->GetYaxis()->SetTickLength(0.04);
  r1__1->GetYaxis()->SetTitleOffset(0.35);
  r1__1->GetYaxis()->SetTitleFont(42);
  r1__1->GetYaxis()->SetNdivisions(503);
  r1__1->Draw("");
}

void setpad(TPad *c_1) {
  c_1->Draw();
  c_1->cd();
  //   c_1->Range(-0.427002,-0.01611993,4.141898,0.06259125);
  c_1->SetFillColor(0);
  c_1->SetBorderMode(0);
  c_1->SetBorderSize(1);
  c_1->SetTickx(1);
  c_1->SetTicky(1);
  c_1->SetLeftMargin(0.1296791);
  c_1->SetBottomMargin(0.13);
  c_1->SetTopMargin(0.04);
  c_1->SetRightMargin(0.03);
  c_1->SetFrameBorderMode(0);
  c_1->SetFrameLineWidth(1);
  c_1->SetFrameBorderMode(0);
}

void setlegendstyle(TLegend *leg1) {
  leg1->SetBorderSize(1);
  leg1->SetLineColor(0);
  leg1->SetLineStyle(1);
  leg1->SetLineWidth(1);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(1001);
}

TString partname[4] = {"MPIp", "MPInp", "MPIp", "MPInp"};
Int_t color[4] = {kGreen + 1, kMagenta + 1, kGreen + 2, kMagenta + 2};
Int_t markerstyle[4] = {20, 21, 24, 25};
Double_t markersize[4] = {1.5, 1.5, 1.5, 1.5};

void MPI_plotting_pndnp() {
  TFile *f1 = new TFile("pThatMPI_CRon_on_plot.root");
  TFile *f2 = new TFile("pThatMPI_CRoff_on_plot.root");

  TCanvas *c = new TCanvas("c", "2pads", 850, 600);
  setpad(c);

  // c->SetLogy();
  // c->Draw();

  double y1_start = 0.0, y1_end = 0.31;
  double y2_start = 0.31, y2_end = 1.0;
  // Define y-axis divisions (2 rows with 60:40 ratio)
  double x1_start = 0.0, x1_end = 1.0;

  // Create TPads
  TPad *pad1a = new TPad("pad1a", "Pad 1A", x1_start, y2_start, x1_end, y2_end);
  TPad *pad2a = new TPad("pad2a", "Pad 2A", x1_start, y1_start, x1_end, y1_end);

  // gStyle->SetOptStat(0);
  // // gPad->SetTicks();
  // gStyle->SetPadTickX(1);
  // gStyle->SetPadTickY(1);
  // // gStyle->SetPalette(kRainBow);

  // c->SetLogy();
  c->Draw();

  TH2D *hframe1 = new TH2D(
      "", ";p_{T}^{D^{0}-lead} (GeV/#it{c});#LTN_{mpi}#GT ", 100,
      0.1, 24.0, 100, 0.5, 10.0);
  TH2D *hframe2 = new TH2D("", ";p_{T}^{D^{0}-lead} (GeV/#it{c});CR-off/on",
                           100, 0.1, 24.0, 100, 0.9, 1.12);
  sethisto(hframe1);
  sethistodown(hframe2);

  setpad(pad1a);
  setpad(pad2a);

  pad1a->SetMargin(0.13, 0.12, 0.0, 0.05);
  pad2a->SetMargin(0.13, 0.12, 0.4, 0.0);

  c->cd();
  pad1a->Draw();
  pad2a->Draw();

  pad2a->cd();
  hframe2->Draw();

  TLine *line = new TLine(0.0, 1.0, 24, 1.0);
  line->SetLineStyle(2);      // Dashed
  line->SetLineColor(kBlack); // Black line
  line->SetLineWidth(2);      // Thickness
  line->Draw("same");

  pad1a->cd();
  hframe1->Draw();

 
  TProfile *h1[4];
  TH1D *h2[2];


  for (int i = 0; i < 4; i++) {
    if (i < 2) {
      h1[i] = (TProfile *)f1->Get(partname[i]); // CR on: pro and npro
    } else {
      h1[i] = (TProfile *)f2->Get(partname[i]); // CR off: pro and npro
    }

    h1[i]->SetMarkerColor(color[i]);
    h1[i]->SetLineColor(color[i]);
    h1[i]->SetMarkerStyle(markerstyle[i]);
    h1[i]->SetMarkerSize(markersize[i]);
  }

  for (int i = 0; i < 4; i++) {
    h1[i]->Draw("pesame");
  }

  h2[0] = (TH1D *)h1[2]->ProjectionX("");
  h2[0]->Divide(h1[2]->ProjectionX(""), h1[0]->ProjectionX(""));
  h2[0]->SetMarkerColor(color[0]);
  h2[0]->SetLineColor(color[0]);
  h2[0]->SetMarkerStyle(markerstyle[2]);
  h2[0]->SetMarkerSize(markersize[0]);

  h2[1] = (TH1D *)h1[3]->ProjectionX("");
  h2[1]->Divide(h1[3]->ProjectionX(""), h1[1]->ProjectionX(""));
  h2[1]->SetMarkerColor(color[1]);
  h2[1]->SetLineColor(color[1]);
  h2[1]->SetMarkerStyle(markerstyle[3]);
  h2[1]->SetMarkerSize(markersize[1]);

  pad1a->cd();

  TLegend *legend1 =
      new TLegend(0.293632, 0.228671, 0.48467, 0.327877, NULL, "brNDC");
  // legend->SetHeader("Multiplicity, "+partID1[j],"C");
  setlegendstyle(legend1);
  legend1->AddEntry((TObject *)0, "CR on", "");
  legend1->AddEntry((TObject *)0, "CR off", "");

  legend1->SetTextSize(0.065);
  legend1->SetNColumns(2);
  legend1->SetBorderSize(0);
  legend1->Draw();

  TLegend *legend =
      new TLegend(0.357311, 0.0897817, 0.804245, 0.21875, NULL, "brNDC");
  // legend->SetHeader("Multiplicity, "+partID1[j],"C");
  setlegendstyle(legend);

  legend->AddEntry(h1[0], " ", "lp");
  legend->AddEntry(h1[2], " ", "lp");
  legend->AddEntry((TObject *)0, "Prompt", "");

  legend->AddEntry(h1[1], " ", "lp");
  legend->AddEntry(h1[3], " ", "lp");
  legend->AddEntry((TObject *)0, "Non-prompt", "");

  legend->SetTextSize(0.065);
  legend->SetNColumns(3);
  legend->SetBorderSize(0);

  legend->Draw();

 
  pad2a->cd();

  for (int i = 0; i < 2; i++) {
    h2[i]->Draw("pesame");
  }
  // cout << "reached here 1" << endl;

  c->SaveAs("D0_MPI.pdf");
}

void SetStyle(Bool_t graypalette) {
  // cout << "Setting style!" << endl;

  gStyle->Reset("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  if (graypalette)
    gStyle->SetPalette(8, 0);
  else
    gStyle->SetPalette(1);
  gStyle->SetCanvasColor(10);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameLineWidth(1);

  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetPadColor(10);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.09);
  gStyle->SetPadBottomMargin(0.18);
  gStyle->SetPadLeftMargin(0.17);
  gStyle->SetNdivisions(505, "y");
  gStyle->SetNdivisions(510, "x");

  gStyle->SetHistLineWidth(1);
  // gStyle->SetHistLineColor(kRed);
  gStyle->SetFuncWidth(2);
  // gStyle->SetFuncColor(kBlack);
  gStyle->SetLineWidth(2);
  gStyle->SetLabelSize(0.04, "xyz");
  gStyle->SetLabelOffset(0.01, "y");
  gStyle->SetLabelOffset(0.01, "x");
  gStyle->SetLabelColor(kBlack, "xyz");
  gStyle->SetTitleSize(0.05, "xyz");
  gStyle->SetTitleOffset(1.0, "y");
  gStyle->SetTitleOffset(1.1, "x");
  gStyle->SetTitleFillColor(kWhite);
  gStyle->SetTextSizePixels(26);
  gStyle->SetTextFont(42);
  gStyle->SetTickLength(0.04, "X");
  gStyle->SetTickLength(0.02, "Y");
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);
  gStyle->SetLegendFont(42);
}