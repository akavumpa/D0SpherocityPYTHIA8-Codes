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
  r1__1->GetXaxis()->SetTickLength(0.03);
  r1__1->GetXaxis()->SetTitleOffset(1.2);
  r1__1->GetXaxis()->SetTitleFont(42);

  // r1__1->GetYaxis()->SetTitle("#frac{1}{2#piN_{eV}} #frac{d^{2}N}{dy dp_{T}}
  // [(GeV/c)^{-1}]");
  r1__1->GetYaxis()->SetNdivisions(510);
  r1__1->GetYaxis()->SetLabelFont(42);
  r1__1->GetYaxis()->SetLabelOffset(0.01);
  r1__1->GetYaxis()->SetLabelSize(0.05);
  r1__1->GetYaxis()->SetTitleSize(0.05);
  r1__1->GetYaxis()->SetTickLength(0.03);
  r1__1->GetYaxis()->SetTitleOffset(1.);
  r1__1->GetYaxis()->SetTitleFont(42);
  r1__1->GetZaxis()->SetLabelFont(42);
  r1__1->GetZaxis()->SetLabelSize(0.06);
  r1__1->GetZaxis()->SetTitleSize(0.06);
  r1__1->GetZaxis()->SetTitleOffset(1);
  r1__1->GetZaxis()->SetTitleFont(42);
  // r1__1->GetYaxis()->SetMoreLogLabels(kTRUE);
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

// void profileToGraph(TProfile *pf, TGraphErrors *gr)
// {
//     Double_t xval[1000] = {};
//     Double_t xerr[1000] = {};

//     int nBins = pf->GetNbinsX();

//     for (int i = 0; i < nBins; i++)
//     {
//         double x = pf->GetBinCenter(i + 1);
//         double y = pf->GetBinContent(i + 1);
//         double ex = pf->GetBinWidth(i + 1) / 2.0;   // or 0 if you want
//         double ey = pf->GetBinError(i + 1);

//         gr->SetPoint(i, x, y);
//         gr->SetPointError(i, ex, ey);
//     }
// }

// void Hist2Graph_CRonMPIon(TH1D *hist, TGraphErrors *tgraph) {
//   const double MBdNchdeta = 4.3280;
//   const double ErrorMBdNchdeta = 0.0003;
//   double dNchdeta0p8[7] = {2.6348, 2.9456,  3.6674, 5.6913,
//                            9.0967, 15.8879, 26.8715};
//   double ErrordNchdeta0p8[7] = {0.0002, 0.0003, 0.0003, 0.0007,
//                                 0.0012, 0.0021, 0.0054};

//   for (int i = 0; i < hist->GetNbinsX(); i++) {
//     cout << i << "/" << hist->GetNbinsX() << "done" << endl;
//     double x = 1.0 * dNchdeta0p8[i] / MBdNchdeta;
//     double xerr =
//         x * TMath::Sqrt(
//                 TMath::Power(1.0 * ErrordNchdeta0p8[i] / dNchdeta0p8[i], 2) +
//                 TMath::Power(1.0 * ErrorMBdNchdeta / MBdNchdeta, 2));
//     tgraph->SetPoint(i, x, hist->GetBinContent(i + 1));
//     tgraph->SetPointError(i, xerr, hist->GetBinError(i + 1));
//   }
// }

void Prof2Graph(TProfile *prof, TGraphErrors *tgraph) {
  const double MBdNchdeta = 4.3280;
  const double ErrorMBdNchdeta = 0.0003;
  double dNchdeta0p8[7] = {2.6348, 2.9456,  3.6674, 5.6913,
                           9.0967, 15.8879, 26.8715};
  double ErrordNchdeta0p8[7] = {0.0002, 0.0003, 0.0003, 0.0007,
                                0.0012, 0.0021, 0.0054};

  for (int i = 0; i < prof->GetNbinsX(); i++) {
    cout << i << "/" << prof->GetNbinsX() << "done" << endl;
    double x = 1.0 * dNchdeta0p8[i] / MBdNchdeta;
    double xerr =
        x * TMath::Sqrt(
                TMath::Power(1.0 * ErrordNchdeta0p8[i] / dNchdeta0p8[i], 2) +
                TMath::Power(1.0 * ErrorMBdNchdeta / MBdNchdeta, 2));
    tgraph->SetPoint(i, x, prof->GetBinContent(i + 1));
    tgraph->SetPointError(i, xerr, prof->GetBinError(i + 1));
  }
}

void fig9_MeanpTplot() {
  gStyle->SetOptStat(0);
  // gPad->SetTicks();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  // gStyle->SetPalette(kRainBow);

  TFile *file = new TFile("MeanpT_Yaxis.root");
  TCanvas *c = new TCanvas("c", "c", 750, 600);
  setpad(c);
  // c->SetLogy();
  c->Draw();

  TH2D *h2 = new TH2D("h2", "", 100, 0, 7, 100, 1.8, 3.0);
  sethisto(h2);
  h2->GetYaxis()->SetTitle("#LTp_{T}#GT");
  h2->GetXaxis()->SetTitle("(dN_{ch}/d#eta)/#LTdN_{ch}/d#eta#GT|_{|#eta|<0.8}");

  TProfile *prof1[4];
  TGraphErrors *g1[4];

  TString partname[4] = {"prompt_jetty", "prompt_isotropic", "nonprompt_jetty",
                         "nonprompt_isotropic"};
  // TString partID[4] = {"prompt_jetty", "prompt_isotropic", "nonprompt_jetty",
  // "nonprompt_isotropic"};
  Int_t color[4] = {kRed, kGreen + 3, kRed, kGreen + 3};
  Int_t markerstyle[4] = {20, 21, 24, 25};
  Double_t markersize[4] = {1.5, 1.5, 1.5, 1.5};

  h2->Draw();

  for (int i = 0; i < 4; i++) {
    // h[i] = (TH1D *)file->Get(Form("%s", partname[i]));
    prof1[i] = (TProfile *)file->Get(partname[i]);
    g1[i] = new TGraphErrors();
    Prof2Graph(prof1[i], g1[i]);
    g1[i]->SetMarkerColor(color[i]);
    g1[i]->SetLineColor(color[i]);
    g1[i]->SetMarkerStyle(markerstyle[i]);
    g1[i]->SetMarkerSize(markersize[i]);
    g1[i]->Draw("elpsame");
  }

  TLegend *legHeader = new TLegend(0.29, 0.82, 0.43, 0.82, NULL, "brNDC");
  setlegendstyle(legHeader);
  legHeader->SetTextSize(0.05);
  legHeader->AddEntry("", "pp, #sqrt{s} = 13.6 TeV, PYTHIA8, |y|<0.5", "");
  legHeader->Draw("same");

  TLegend *legend2 = new TLegend(
      0.6, 0.244, 0.871, 0.36, NULL,
      "brNDC"); // the dimension specified within the bracket specifies the
                // position of the following names in canvas
  legend2->SetTextSize(0.04);
  legend2->AddEntry(g1[0], " ", "lp");
  legend2->AddEntry(g1[1], " ", "lp");
  legend2->AddEntry(g1[2], " ", "lp");
  legend2->AddEntry(g1[3], " ", "lp");
  // legend2->AddEntry((TObject *)0, "Prompt", "");

  // legend2->AddEntry(graph[2], " ", "lp");
  // legend2->AddEntry(graph[3], " ", "lp");
  // legend2->AddEntry((TObject *)0, "Non-prompt", "");

  legend2->SetNColumns(2);
  legend2->SetTextSize(0.035);
  legend2->SetTextFont(42);
  legend2->SetBorderSize(0);
  legend2->Draw("same");

  TLegend *legS0 = new TLegend(0.537, 0.38, 0.88, 0.415, NULL, "brNDC");

  legS0->AddEntry((TObject *)0, "Jetty", "");
  legS0->AddEntry((TObject *)0, "Isotropic", "");
  legS0->SetTextSize(0.04);
  legS0->SetNColumns(2);
  legS0->SetBorderSize(0);
  legS0->Draw("same");

  TLegend *legPID = new TLegend(0.37, 0.244, 0.559, 0.359, NULL, "brNDC");

  legPID->AddEntry((TObject *)0, "Prompt", "");
  legPID->AddEntry((TObject *)0, "Non-prompt", "");
  legPID->SetTextSize(0.04);
  legPID->SetNColumns(1);
  legPID->SetBorderSize(0);
  legPID->Draw("same");

  // legend->Draw();

  c->SaveAs("MeanpTD0_NormNch.pdf");
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
  gStyle->SetPadRightMargin(0.3);
  gStyle->SetPadBottomMargin(0.35);
  gStyle->SetPadLeftMargin(0.2);
  gStyle->SetNdivisions(505, "y");
  gStyle->SetNdivisions(510, "x");

  gStyle->SetHistLineWidth(1);
  // gStyle->SetHistLineColor(kRed);
  gStyle->SetFuncWidth(2);
  // gStyle->SetFuncColor(kBlack);
  gStyle->SetLineWidth(2);
  gStyle->SetLabelSize(0.06, "xyz");
  gStyle->SetLabelOffset(0.01, "y");
  gStyle->SetLabelOffset(0.01, "x");
  gStyle->SetLabelColor(kBlack, "xyz");
  gStyle->SetTitleSize(0.06, "xyz");
  gStyle->SetTitleOffset(1.1, "y");
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