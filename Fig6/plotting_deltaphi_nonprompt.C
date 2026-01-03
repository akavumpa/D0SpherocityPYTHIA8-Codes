void SetStyle(Bool_t graypalette = kTRUE);

void sethisto(TH2D *r1__1) {
  r1__1->SetStats(0);
  // r1__1->GetXaxis()->SetTitle("p_{T}[GeV/c]");
  // r1__1->GetXaxis()->CenterTitle(true);
  r1__1->GetXaxis()->SetLabelFont(42);
  r1__1->GetXaxis()->SetNdivisions(510);
  r1__1->GetXaxis()->SetLabelOffset(0.01);
  r1__1->GetXaxis()->SetLabelSize(0.05);
  r1__1->GetXaxis()->SetTitleSize(0.06);
  r1__1->GetXaxis()->SetTickLength(0.03);
  r1__1->GetXaxis()->SetTitleOffset(1.);
  r1__1->GetXaxis()->SetTitleFont(42);

  // r1__1->GetYaxis()->SetTitle("#frac{1}{2#piN_{eV}} #frac{d^{2}N}{dy dp_{T}}
  // [(GeV/c)^{-1}]");
  r1__1->GetYaxis()->SetNdivisions(510);
  r1__1->GetYaxis()->SetLabelFont(42);
  r1__1->GetYaxis()->SetLabelOffset(0.01);
  r1__1->GetYaxis()->SetLabelSize(0.05);
  r1__1->GetYaxis()->SetTitleSize(0.05);
  r1__1->GetYaxis()->SetTickLength(0.03);
  r1__1->GetYaxis()->SetTitleOffset(1.17);
  r1__1->GetYaxis()->SetTitleFont(42);
  r1__1->GetZaxis()->SetLabelFont(42);
  r1__1->GetZaxis()->SetLabelSize(0.06);
  r1__1->GetZaxis()->SetTitleSize(0.06);
  r1__1->GetZaxis()->SetTitleOffset(1.);
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

void plotting_deltaphi_nonprompt() {
  gStyle->SetOptStat(0);
  // gPad->SetTicks();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  // gStyle->SetPalette(kRainBow);
  TFile *f1 = new TFile("deltaphispectra_plot_CRon_MPIon.root");
  TFile *f2 = new TFile("deltaphispectra_plot_CRon_MPIoff.root");
  TFile *f3 = new TFile("deltaphispectra_plot_CRoff_MPIon.root");
  TCanvas *c = new TCanvas("", "", 750, 600);
  setpad(c);
  // c->SetLogy();
  c->Draw();

  TH2D *h2 = new TH2D("", "", 10, -0.5 * TMath::Pi(), 1.5 * TMath::Pi(), 10,
                      0.1, 0.45);
  sethisto(h2);
  h2->GetYaxis()->SetTitle("1/N_{pairs}(dN_{pairs}/d#Delta#phi)");
  h2->GetXaxis()->SetTitle("#Delta#phi");

  TH1F *h_1[3];

  TString partname1 = {"Delphi-dist-nonprompt"};
  Int_t color[3] = {kCyan + 1, kBlue + 1, kMagenta + 1};
  Int_t markerstyle1[3] = {20, 21, 23};
  Int_t markerstyle2[3] = {24, 25, 27};
  Double_t markersize[3] = {1.3, 1.3, 1.3};

  h2->Draw();
  h_1[0] = (TH1F *)f1->Get(partname1);
  h_1[1] = (TH1F *)f2->Get(partname1);
  h_1[2] = (TH1F *)f3->Get(partname1);

  for (int i = 0; i < 3; i++)
  // h[i] = (TH1D *)file->Get(Form("%s", partname[i]));
  {
    h_1[i]->SetMarkerColor(color[i]);
    h_1[i]->SetLineColor(color[i]);
    h_1[i]->SetMarkerStyle(markerstyle1[i]);
    h_1[i]->SetMarkerSize(1.5);
    h_1[i]->Draw("pesame");
  }

  // legend->Draw();

  TLegend *pt =
      new TLegend(0.164, 0.842, 0.295, 0.9496, NULL, "brNDC");
  setlegendstyle(pt);
  pt->SetTextSize(0.05);
  pt->AddEntry("", "", "");
  // pt->AddEntry("", "pp, #sqrt{s} = 13.6 TeV, PYTHIA 8, |y|<0.5", "");
  // pt->AddEntry("","Prompt D^{0}","");
  pt->AddEntry("", "Non-prompt D^{0}", "");

  pt->Draw("same");
  TLegend *legend =
      new TLegend(0.606952, 0.519097, 0.86631, 0.793403, NULL, "brNDC");
  setlegendstyle(legend);
  legend->AddEntry((TObject *)0, " ", "");
  legend->AddEntry((TObject *)0, " CR", "");
  legend->AddEntry((TObject *)0, " MPI", "");
  legend->AddEntry(h_1[0], " ", "lp");
  legend->AddEntry((TObject *)0, " on", "");
  legend->AddEntry((TObject *)0, " on", "");

  // legend->AddEntry(h1b[1], " ", "lp");
  legend->AddEntry(h_1[1], " ", "lp");
  legend->AddEntry((TObject *)0, " on", "");
  legend->AddEntry((TObject *)0, " off", "");

  legend->AddEntry(h_1[2], " ", "lp");
  legend->AddEntry((TObject *)0, " off", "");
  legend->AddEntry((TObject *)0, " on", "");

  legend->SetTextSize(0.05);
  legend->SetNColumns(3);
  legend->SetBorderSize(0);

  legend->Draw();

  c->SaveAs("D0_yieldVSphi_nonprompt.pdf");
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