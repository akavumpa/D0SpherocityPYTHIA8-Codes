
void sethisto1(TH2D *r1__1) {
  r1__1->SetStats(0);
  // r1__1->GetXaxis()->SetTitle("p_{T}[GeV/c]");
  // r1__1->GetXaxis()->CenterTitle(true);
  r1__1->GetXaxis()->SetNdivisions(505);
  r1__1->GetXaxis()->SetLabelFont(42);
  r1__1->GetXaxis()->SetLabelOffset(0.01);
  r1__1->GetXaxis()->SetLabelSize(0.05);
  r1__1->GetXaxis()->SetTitleSize(0.05);
  r1__1->GetXaxis()->SetTitleOffset(1.2);
  r1__1->GetXaxis()->SetTitleFont(42);

  // r1__1->GetYaxis()->SetTitle("#frac{1}{2#piN_{eV}} #frac{d^{2}N}{dy dp_{T}}
  // [(GeV/c)^{-1}]");
  r1__1->GetXaxis()->SetNdivisions(505);
  r1__1->GetYaxis()->SetLabelFont(42);
  r1__1->GetYaxis()->SetLabelOffset(0.01);
  r1__1->GetYaxis()->SetLabelSize(0.05);
  r1__1->GetYaxis()->SetTitleSize(0.05);
  r1__1->GetYaxis()->SetTitleOffset(1);
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
  //   c_1->Draw();
  //   c_1->cd();
  c_1->SetFillColor(0);
  c_1->SetBorderMode(0);
  //   c_1->SetBorderSize(1);
  c_1->SetTickx(1);
  c_1->SetTicky(1);
  //   c_1->SetLeftMargin(0.14);
  //   c_1->SetBottomMargin(0.13);
  //   c_1->SetTopMargin(0.04);
  //   c_1->SetRightMargin(0.03);

  c_1->SetFrameBorderMode(0);
  //   c_1->SetFrameLineWidth(2);
}

void setlegendstyle(TLegend *leg1) {
  //   leg1->SetBorderSize(1);
  leg1->SetLineColor(0);
  leg1->SetLineStyle(1);
  //   leg1->SetLineWidth(1);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(1001);
}

void Rpp_nonprompt_plot() {

  TFile *file = new TFile("D0_Rpp.root");

  TCanvas *c = new TCanvas("c", "", 116, 119, 800, 600);
  c->Range(-1.996551, 0.08245242, 26.89655, 3.12685);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetTopMargin(0.04166667);
  c->SetBottomMargin(0.1371528);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);
  // c->SetLogx();

  TH2D *hframe1 =
      new TH2D("", ";p_{T} (GeV/c);Q_{pp}", 100, 0.9, 24.0, 100, 0.5, 2.0);

  sethisto1(hframe1);
  // sethisto2(hframe2);

  c->Draw();

  hframe1->Draw();

  TH1D *h1a[8];
  TH1D *h2a[8];
  // TString partname1[8] = {"prompt_J_mult_7", "prompt_I_mult_7"};
  TString partname2[8] = {"nonprompt_J_mult_7", "nonprompt_I_mult_7"};

  Int_t color[6] = {kGreen + 3, kMagenta,   kGreen + 3,
                    kMagenta,   kGreen + 3, kMagenta};
  Int_t markerstyle[6] = {20, 21, 25, 22, 26};
  Double_t markersize[6] = {1.2, 1.2, 1.2, 1.2, 1.2, 1.2};
  // Add histograms to ensure visible axes

  for (int i = 0; i < 2; i++) {
    h1a[i] = (TH1D *)file->Get(partname2[i]);
    //    if (h1a[i]) {
    //       cout << partname1[i] << " x-axis max: "
    //            << h1a[i]->GetXaxis()->GetXmax() << endl;
    //   }}
  }
  // h1a[1]->Scale(1.0/2);
  for (int i = 0; i < 2; i++) {

    h1a[i]->SetMarkerColorAlpha(color[i], 1.0);
    h1a[i]->SetLineColorAlpha(color[i], 1.0);
    h1a[i]->SetMarkerStyle(markerstyle[i]);
    h1a[i]->SetMarkerSize(markersize[i]);
    h1a[i]->SetFillColorAlpha(color[i], 0.3);
  }

  //   p1->Draw();
  for (int j = 0; j < 2; j++) {
    h1a[j]->Draw("E3, CPSAME");
  }
  TLine *line1 = new TLine(1, 1, 24, 1);
  line1->SetLineWidth(2);
  // line1->SetLineColor("kBlack");
  line1->SetLineStyle(2);
  line1->Draw("same");

  TLegend *pt1 =
      new TLegend(0.14411, 0.65625, 0.285714, 0.70833, NULL, "brNDC");
  setlegendstyle(pt1);
  //    pt->SetFillColor(0);
  pt1->SetTextSize(0.04);

  pt1->AddEntry("", "Non-prompt D^{0}", "");
  pt1->Draw("same");
  TLegend *legend2 =
      new TLegend(0.190476, 0.733507, 0.377193, 0.832465, NULL, "brNDC");
  setlegendstyle(legend2);
  legend2->AddEntry(h1a[0], " ", "lp");
  legend2->AddEntry(h1a[1], " ", "lp");
  legend2->SetTextSize(0.035);
  legend2->SetNColumns(3);
  legend2->SetBorderSize(0);

  legend2->Draw();

  TLegend *legend1 =
      new TLegend(0.139098, 0.810764, 0.359649, 0.892361, NULL, "brNDC");
  setlegendstyle(legend1);

  legend1->AddEntry((TObject *)0, "Jetty", "");
  legend1->AddEntry((TObject *)0, "Isotropic", "");
  legend1->SetTextSize(0.04);
  legend1->SetNColumns(2);
  legend1->SetBorderSize(0);

  legend1->Draw();
  c->Update();

  c->SaveAs("Rpp_nonprompt.pdf");
}
