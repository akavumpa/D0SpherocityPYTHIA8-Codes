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
  r1__1->GetYaxis()->SetTitleOffset(1.2);
  r1__1->GetYaxis()->SetTitleFont(42);
  r1__1->GetZaxis()->SetLabelFont(42);
  r1__1->GetZaxis()->SetLabelSize(0.06);
  r1__1->GetZaxis()->SetTitleSize(0.06);
  r1__1->GetZaxis()->SetTitleOffset(0.9);
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

void AvgD0NchVspThat_plotting() {
  gStyle->SetOptStat(0);
  // gPad->SetTicks();
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  // gStyle->SetPalette(kRainBow);
  TFile *f1 = new TFile("AvgD0VspthatCRon_on_plot.root");
  TFile *f2 = new TFile("AvgD0VspthatCRoff_on_plot.root");
  TCanvas *c = new TCanvas("c", "c", 750, 600);
  setpad(c);
  // c->SetLogy();
  c->Draw();
  TLegend *legend;
  TLegend *legend1;
  TLegend *legend2;

    TH2D *h2 = new TH2D("h2", "", 2, 2.0, 24.0, 400, 0.1, 50.0);  //fig1
    //   sethisto(h2);
  h2->GetYaxis()->SetTitle("dN/dy/#LTdN/dy#GT ");
    h2->GetXaxis()->SetTitle("#hatp_{T} (GeV/c)");
  TGraphErrors *h[6];
    TString partname[6] = {"pThat-D0p",  "pThat-D0p", "pThat-D0np",
                           "pThat-D0np", "pThat-Nch", "pThat-Nch"};

  Int_t color[6] = {kGreen + 1,   kGreen + 2, kMagenta + 1,
                    kMagenta + 2, kCyan + 1,  kCyan + 2};
  Int_t markerstyle[6] = {20, 24, 21, 25, 22, 26};
  Double_t markersize[6] = {1.8, 1.8, 1.8, 1.8, 1.8, 1.8};

  h2->Draw();
  h[0] = (TGraphErrors *)f1->Get(partname[0]);
  h[1] = (TGraphErrors *)f2->Get(partname[1]);
  h[2] = (TGraphErrors *)f1->Get(partname[2]);
  h[3] = (TGraphErrors *)f2->Get(partname[3]);
  h[4] = (TGraphErrors *)f1->Get(partname[4]);
  h[5] = (TGraphErrors *)f2->Get(partname[5]);

  for (int i = 0; i < 6; i++) {
    h[i]->SetMarkerColor(color[i]);
    h[i]->SetLineColor(color[i]);
    h[i]->SetMarkerStyle(markerstyle[i]);
    h[i]->SetMarkerSize(markersize[i]);
  }

  h[0]->Draw("pesame");
  h[1]->Draw("pesame");
  h[2]->Draw("pesame");
  h[3]->Draw("pesame");
  h[4]->Draw("pesame");
  h[5]->Draw("pesame");

  legend = new TLegend(0.167112, 0.647569, 0.393048, 0.873264, NULL, "brNDC");
  // legend->SetHeader("Multiplicity, "+partID1[j],"C");
  setlegendstyle(legend);

  legend->AddEntry((TObject *)0, "CR on", "");
  legend->AddEntry((TObject *)0, "CR off", "");
  legend->AddEntry((TObject *)0, "", "");
  legend->SetTextSize(0.04);
  legend->SetNColumns(2);
  legend->SetBorderSize(0);

  legend->Draw();
  
  legend1 = new TLegend(0.407754, 0.644097, 0.434492, 0.796875, NULL, "brNDC");
  // legend->SetHeader("Multiplicity, "+partID1[j],"C");
  setlegendstyle(legend1);

  legend1->AddEntry((TObject *)0, "Prompt D^{0}", "");

  legend1->AddEntry((TObject *)0, "Non-prompt D^{0}", "");

  legend1->AddEntry((TObject *)0, "h^{+}+h^{-}", "");
  legend1->SetTextSize(0.04);
  legend1->SetNColumns(1);
  legend1->SetBorderSize(0);

  legend1->Draw();
  legend2 = new TLegend(0.22861, 0.652778, 0.406417, 0.788194, NULL, "brNDC");
  setlegendstyle(legend2);

  legend2->AddEntry(h[0], " ", "lp");
  legend2->AddEntry(h[1], " ", "lp");
  legend2->AddEntry(h[2], " ", "lp");
  legend2->AddEntry(h[3], " ", "lp");
  legend2->AddEntry(h[4], " ", "lp");

  legend2->AddEntry(h[5], " ", "lp");

  legend2->SetTextSize(0.04);
  legend2->SetNColumns(2);
  legend2->SetBorderSize(0);

  legend2->Draw();

  TLegend *pt = new TLegend(0.15107, 0.8316, 0.294118, 0.930556, NULL, "brNDC");
  setlegendstyle(pt);
  //    pt->SetFillColor(0);
  pt->SetTextSize(0.05);

  pt->AddEntry("", "pp, #sqrt{s} = 13.6 TeV, PYTHIA8, |y|<0.5", "");
  //    pt->AddEntry("","Minimum Bias","");
  //    pt->SetBorderSize(0);
  pt->Draw("same");
  c->SaveAs("D0NchCRoffndonpThat.pdf");
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