
void sethisto1(TH2D *r1__1)
{
  r1__1->SetStats(0);
  r1__1->GetXaxis()->CenterTitle(true);
  r1__1->GetXaxis()->SetLabelFont(42);
  r1__1->GetXaxis()->SetNdivisions(505);
  r1__1->GetXaxis()->SetLabelOffset(0.01);
  r1__1->GetXaxis()->SetLabelSize(0.05);
  r1__1->GetXaxis()->SetTitleSize(0.06);
  r1__1->GetXaxis()->SetTickLength(0.03);
  r1__1->GetXaxis()->SetTitleOffset(1.2);
  r1__1->GetXaxis()->SetTitleFont(42);

  r1__1->GetYaxis()->CenterTitle(true);
  r1__1->GetYaxis()->SetNdivisions(510);
  r1__1->GetYaxis()->SetLabelFont(42);
  r1__1->GetYaxis()->SetLabelOffset(0.01);
  r1__1->GetYaxis()->SetLabelSize(0.06);
  r1__1->GetYaxis()->SetTitleSize(0.08);
  r1__1->GetYaxis()->SetTickLength(0.02);
  r1__1->GetYaxis()->SetTitleOffset(0.9);
  r1__1->GetYaxis()->SetTitleFont(42);
  // r1__1->GetYaxis()->SetMoreLogLabels(kTRUE);

  r1__1->Draw("");
}

void sethisto2(TH2D *r1__1)
{
  r1__1->SetStats(0);
  r1__1->GetXaxis()->CenterTitle(true);
  r1__1->GetXaxis()->SetLabelFont(42);
  r1__1->GetXaxis()->SetNdivisions(505);
  r1__1->GetXaxis()->SetLabelOffset(0.01);
  r1__1->GetXaxis()->SetLabelSize(0.05);
  r1__1->GetXaxis()->SetTitleSize(0.06);
  r1__1->GetXaxis()->SetTickLength(0.03);
  r1__1->GetXaxis()->SetTitleOffset(1.2);
  r1__1->GetXaxis()->SetTitleFont(42);

  r1__1->GetYaxis()->CenterTitle(true);
  r1__1->GetYaxis()->SetNdivisions(510);
  r1__1->GetYaxis()->SetLabelFont(42);
  r1__1->GetYaxis()->SetLabelOffset(0.008);
  r1__1->GetYaxis()->SetLabelSize(0.05);
  r1__1->GetYaxis()->SetTitleSize(0.065);
  r1__1->GetYaxis()->SetTickLength(0.02);
  r1__1->GetYaxis()->SetTitleOffset(1.1);
  r1__1->GetYaxis()->SetTitleFont(42);
  // r1__1->GetYaxis()->SetMoreLogLabels(kTRUE);

  r1__1->Draw("");
}

void setpad(TPad *c_1)
{
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

void setlegendstyle(TLegend *leg1)
{
  //   leg1->SetBorderSize(1);
  leg1->SetLineColor(0);
  leg1->SetLineStyle(1);
  //   leg1->SetLineWidth(1);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(1001);
}

void Hist2Graph_CRonMPIon(TH1D *hist, TGraphErrors *tgraph)
{
  const double MBdNchdeta = 4.3280;
  const double ErrorMBdNchdeta = 0.0003;
  double dNchdeta0p8[7] = {2.6348,2.9456,3.6674,5.6913,9.0967,15.8879,26.8715};
  double ErrordNchdeta0p8[7] = {0.0002,0.0003,0.0003,0.0007,0.0012,0.0021,0.0054};

  for (int i = 0; i < hist->GetNbinsX(); i++)
  {
    cout << i << "/" << hist->GetNbinsX() << "done" << endl;
    double x = 1.0 * dNchdeta0p8[i] / MBdNchdeta;
    double xerr = x * TMath::Sqrt(TMath::Power(1.0 * ErrordNchdeta0p8[i] / dNchdeta0p8[i], 2) + TMath::Power(1.0 * ErrorMBdNchdeta / MBdNchdeta, 2));
    tgraph->SetPoint(i, x, hist->GetBinContent(i + 1));
    tgraph->SetPointError(i, xerr, hist->GetBinError(i + 1));
  }
}
void Hist2Graph_CRoffMPIon(TH1D *hist, TGraphErrors *tgraph)
{
  const double MBdNchdeta = 5.0516;
  const double ErrorMBdNchdeta = 0.0004;
  double dNchdeta0p8[7] = {2.7440,3.1318,4.3060,7.0154,11.3114,19.7527,34.1083};
  double ErrordNchdeta0p8[7] = {0.0002,0.0003,0.0004,0.0008,0.0016,0.0026,0.0068};

  for (int i = 0; i < hist->GetNbinsX(); i++)
  {
    cout << i << "/" << hist->GetNbinsX() << "done" << endl;
    double x = 1.0 * dNchdeta0p8[i] / MBdNchdeta;
    double xerr = x * TMath::Sqrt(TMath::Power(1.0 * ErrordNchdeta0p8[i] / dNchdeta0p8[i], 2) + TMath::Power(1.0 * ErrorMBdNchdeta / MBdNchdeta, 2));
    tgraph->SetPoint(i, x, hist->GetBinContent(i + 1));
    tgraph->SetPointError(i, xerr, hist->GetBinError(i + 1));
  }
}

void Plot_SN_CRonandoff_3pTranges()
{
  TFile *f1 = TFile::Open("D0SNyaxis_CRon_.root"); // on on
  TFile *f1off = TFile::Open("D0SNyaxis_CRoff_.root");

  TCanvas *c = new TCanvas("c", "multipads", 1600, 800);

  // c->SetLogy();

  // Define x-axis divisions (2 sections)
  double x1_start = 0.0, x1_end = 0.36;
  double x2_start = 0.36, x2_end = 0.68;
  double x3_start = 0.68, x3_end = 1.0;

  // Define y-axis divisions (2 rows with 60:40 ratio)
  double y1_start = 0.55, y1_end = 1.0;
  double y2_start = 0.0, y2_end = 0.55;

  // Create TPads
  TPad *pad1a = new TPad("pad1a", "Pad 1A", x1_start, y1_start, x1_end, y1_end);
  TPad *pad1b = new TPad("pad1b", "Pad 1B", x1_start, y2_start, x1_end, y2_end);
  TPad *pad2a = new TPad("pad2a", "Pad 2A", x2_start, y1_start, x2_end, y1_end);
  TPad *pad2b = new TPad("pad2b", "Pad 2B", x2_start, y2_start, x2_end, y2_end);
  TPad *pad3a = new TPad("pad3a", "Pad 3A", x3_start, y1_start, x3_end, y1_end);
  TPad *pad3b = new TPad("pad3b", "Pad 3B", x3_start, y2_start, x3_end, y2_end);

  // Set margins (space left for y-axis labels and bottom for x-axis labels)
  pad1a->SetMargin(0.15, 0.0, 0.0, 0.05);
  pad1b->SetMargin(0.15, 0.0, 0.25, 0.0);
  pad2a->SetMargin(0.0, 0.00, 0.0, 0.05);
  pad2b->SetMargin(0.0, 0.00, 0.25, 0.0);
  pad3a->SetMargin(0.0, 0.01, 0.0, 0.05);
  pad3b->SetMargin(0.0, 0.01, 0.25, 0.0);

  // Draw TPads

  TH2D *hframe1 =
      new TH2D("", ";(dN_{ch}/d#eta)/#LTdN_{ch}/d#eta#GT|_{|#eta|<0.8};(d^{2}N/dydp_{T})/#LTd^{2}N/dydp_{T}#GT", 100,
               0.2,7.0, 100, 0.5, 28);
  TH2D *hframe2 =
      new TH2D("", ";(dN_{ch}/d#eta)/#LTdN_{ch}/d#eta#GT|_{|#eta|<0.8};(d^{2}N/dydp_{T})/#LTd^{2}N/dydp_{T}#GT", 100, 0.2,7.0, 100, 0.5, 28);

  sethisto1(hframe1);
  sethisto2(hframe2);
  TH1D *h1proH[2];
  TH1D *h2proH[2];
  TH1D *h3proH[2];
  TH1D *h1nonproH[2];
  TH1D *h2nonproH[2];
  TH1D *h3nonproH[2];
  TH1D *hOFF1proH[2];
  TH1D *hOFF2proH[2];
  TH1D *hOFF3proH[2];
  TH1D *hOFF1nonproH[2];
  TH1D *hOFF2nonproH[2];
  TH1D *hOFF3nonproH[2];

  TGraphErrors *h1pro[2];
  TGraphErrors *h2pro[2];
  TGraphErrors *h3pro[2];
  TGraphErrors *h1nonpro[2];
  TGraphErrors *h2nonpro[2];
  TGraphErrors *h3nonpro[2];
  TGraphErrors *hOFF1pro[2];
  TGraphErrors *hOFF2pro[2];
  TGraphErrors *hOFF3pro[2];
  TGraphErrors *hOFF1nonpro[2];
  TGraphErrors *hOFF2nonpro[2];
  TGraphErrors *hOFF3nonpro[2];

  c->cd();
  c->Draw();
  pad1a->Draw();
  pad2a->Draw();
  pad3a->Draw();
  pad1b->Draw();
  pad2b->Draw();
  pad3b->Draw();

  setpad(pad1a);
  setpad(pad2a);
  setpad(pad3a);
  setpad(pad1b);
  setpad(pad2b);
  setpad(pad3b);

  pad1a->cd();
  hframe1->Draw();

  c->cd();
  pad2a->cd();
  hframe1->Draw();
  c->cd();
  pad3a->cd();
  hframe1->Draw();

  c->cd();
  pad1b->cd();
  hframe2->Draw();

  c->cd();
  pad2b->cd();
  hframe2->Draw();
  c->cd();
  pad3b->cd();
  hframe2->Draw();


  Int_t color[4] = {kGreen + 2, kMagenta,kGreen + 3, kMagenta+1};
  Int_t markerstyle[4] = { 23,33,32,27};
  Double_t markersize[4] = {1.8, 1.8, 1.8, 1.8};
  TString partname_pt1p[2] = {"prompt_J_1", "prompt_I_1"};
  TString partname_pt1np[2] = {"nonprompt_J_1", "nonprompt_I_1"};
  TString partname_pt2p[2] = {"prompt_J_2", "prompt_I_2"};
  TString partname_pt2np[2] = {"nonprompt_J_2", "nonprompt_I_2"};
  TString partname_pt3p[2] = {"prompt_J_3", "prompt_I_3"};
  TString partname_pt3np[2] = {"nonprompt_J_3", "nonprompt_I_3"};

  // Add histograms to ensure visible axes

  for (int i = 0; i < 2; i++)
  {
    h1proH[i] = (TH1D *)f1->Get(partname_pt1p[i]);
    h1pro[i] = new TGraphErrors();
    Hist2Graph_CRonMPIon(h1proH[i], h1pro[i]);
    h1pro[i]->SetMarkerColor(color[i]);
    h1pro[i]->SetLineColor(color[i]);
    h1pro[i]->SetMarkerStyle(markerstyle[i]);
    h1pro[i]->SetMarkerSize(markersize[i]);

    hOFF1proH[i] = (TH1D *)f1off->Get(partname_pt1p[i]);
    hOFF1pro[i] = new TGraphErrors();
    Hist2Graph_CRoffMPIon(hOFF1proH[i], hOFF1pro[i]);
    hOFF1pro[i]->SetMarkerColor(color[i]);
    hOFF1pro[i]->SetLineColor(color[i]);
    hOFF1pro[i]->SetMarkerStyle(markerstyle[i + 2]);
    hOFF1pro[i]->SetMarkerSize(markersize[i]);

    h2proH[i] = (TH1D *)f1->Get(partname_pt2p[i]);
    h2pro[i] = new TGraphErrors();
    Hist2Graph_CRonMPIon(h2proH[i], h2pro[i]);
    h2pro[i]->SetMarkerColor(color[i]);
    h2pro[i]->SetLineColor(color[i]);
    h2pro[i]->SetMarkerStyle(markerstyle[i]);
    h2pro[i]->SetMarkerSize(markersize[i]);

    hOFF2proH[i] = (TH1D *)f1off->Get(partname_pt2p[i]);
    hOFF2pro[i] = new TGraphErrors();
    Hist2Graph_CRoffMPIon(hOFF2proH[i], hOFF2pro[i]);
    hOFF2pro[i]->SetMarkerColor(color[i]);
    hOFF2pro[i]->SetLineColor(color[i]);
    hOFF2pro[i]->SetMarkerStyle(markerstyle[i + 2]);
    hOFF2pro[i]->SetMarkerSize(markersize[i]);

    h3proH[i] = (TH1D *)f1->Get(partname_pt3p[i]);
    h3pro[i] = new TGraphErrors();
    Hist2Graph_CRonMPIon(h3proH[i], h3pro[i]);
    h3pro[i]->SetMarkerColor(color[i]);
    h3pro[i]->SetLineColor(color[i]);
    h3pro[i]->SetMarkerStyle(markerstyle[i]);
    h3pro[i]->SetMarkerSize(markersize[i]);

    hOFF3proH[i] = (TH1D *)f1off->Get(partname_pt3p[i]);
    hOFF3pro[i] = new TGraphErrors();
    Hist2Graph_CRoffMPIon(hOFF3proH[i], hOFF3pro[i]);
    hOFF3pro[i]->SetMarkerColor(color[i]);
    hOFF3pro[i]->SetLineColor(color[i]);
    hOFF3pro[i]->SetMarkerStyle(markerstyle[i + 2]);
    hOFF3pro[i]->SetMarkerSize(markersize[i]);

    h1nonproH[i] = (TH1D *)f1->Get(partname_pt1np[i]);
    h1nonpro[i] = new TGraphErrors();
    Hist2Graph_CRonMPIon(h1nonproH[i], h1nonpro[i]);
    h1nonpro[i]->SetMarkerColor(color[i]);
    h1nonpro[i]->SetLineColor(color[i]);
    h1nonpro[i]->SetMarkerStyle(markerstyle[i]);
    h1nonpro[i]->SetMarkerSize(markersize[i]);

    hOFF1nonproH[i] = (TH1D *)f1off->Get(partname_pt1np[i]);
    hOFF1nonpro[i] = new TGraphErrors();
    Hist2Graph_CRoffMPIon(hOFF1nonproH[i], hOFF1nonpro[i]);
    hOFF1nonpro[i]->SetMarkerColor(color[i]);
    hOFF1nonpro[i]->SetLineColor(color[i]);
    hOFF1nonpro[i]->SetMarkerStyle(markerstyle[i + 2]);
    hOFF1nonpro[i]->SetMarkerSize(markersize[i]);

    h2nonproH[i] = (TH1D *)f1->Get(partname_pt2np[i]);
    h2nonpro[i] = new TGraphErrors();
    Hist2Graph_CRonMPIon(h2nonproH[i], h2nonpro[i]);
    h2nonpro[i]->SetMarkerColor(color[i]);
    h2nonpro[i]->SetLineColor(color[i]);
    h2nonpro[i]->SetMarkerStyle(markerstyle[i]);
    h2nonpro[i]->SetMarkerSize(markersize[i]);

    hOFF2nonproH[i] = (TH1D *)f1off->Get(partname_pt2np[i]);
    hOFF2nonpro[i] = new TGraphErrors();
    Hist2Graph_CRoffMPIon(hOFF2nonproH[i], hOFF2nonpro[i]);
    hOFF2nonpro[i]->SetMarkerColor(color[i]);
    hOFF2nonpro[i]->SetLineColor(color[i]);
    hOFF2nonpro[i]->SetMarkerStyle(markerstyle[i + 2]);
    hOFF2nonpro[i]->SetMarkerSize(markersize[i]);

    h3nonproH[i] = (TH1D *)f1->Get(partname_pt3np[i]);
    h3nonpro[i] = new TGraphErrors();
    Hist2Graph_CRonMPIon(h3nonproH[i], h3nonpro[i]);
    h3nonpro[i]->SetMarkerColor(color[i]);
    h3nonpro[i]->SetLineColor(color[i]);
    h3nonpro[i]->SetMarkerStyle(markerstyle[i]);
    h3nonpro[i]->SetMarkerSize(markersize[i]);

    hOFF3nonproH[i] = (TH1D *)f1off->Get(partname_pt3np[i]);
    hOFF3nonpro[i] = new TGraphErrors();
    Hist2Graph_CRoffMPIon(hOFF3nonproH[i], hOFF3nonpro[i]);
    hOFF3nonpro[i]->SetMarkerColor(color[i]);
    hOFF3nonpro[i]->SetLineColor(color[i]);
    hOFF3nonpro[i]->SetMarkerStyle(markerstyle[i + 2]);
    hOFF3nonpro[i]->SetMarkerSize(markersize[i]);
  }

  TLine *line1 = new TLine(0.2, 0.5,7.0,7.0);
  line1->SetLineWidth(2);
  // line1->SetLineColor("kBlack");
  line1->SetLineStyle(2);

  TLegend *pt1 =
      new TLegend(0.2068558, 0.5389462, 0.5267, 0.5962199, NULL, "brNDC");
  pt1->SetHeader("1 < p_{T} < 2 GeV/c ");
  pt1->SetTextSize(0.07);
  pt1->SetBorderSize(0);
  TLegend *pt3 =
      new TLegend(0.04638611, 0.5103093, 0.3690551, 0.6563574, NULL, "brNDC");
  pt3->SetHeader("2 < p_{T} <5 GeV/c ");
  pt3->SetTextSize(0.075);
  pt3->SetBorderSize(0);
  TLegend *pt7 =
      new TLegend(0.05545995, 0.5389462, 0.3781289, 0.6849943, NULL, "brNDC");
  pt7->SetHeader("p_{T} > 5 GeV/c ");
  pt7->SetTextSize(0.075);
  pt7->SetBorderSize(0);

  TLegend *pt =
      new TLegend(0.0985, 0.691, 0.43, 0.93, NULL, "brNDC");
  pt->SetHeader("pp, #sqrt{s} = 13.6 TeV (PYTHIA8)");
  // pt->AddEntry("", " Prompt", "");
  pt->SetTextSize(0.075);
  pt->SetBorderSize(0);

  TLegend *pt0 =
      new TLegend(0.2016409, 0.742268, 0.5319149, 0.7995418, NULL, "brNDC");

  pt0->SetHeader(" Prompt D^{0}");
  pt0->SetTextSize(0.07);
  pt0->SetBorderSize(0);

  TLegend *legS = new TLegend(0.15, 0.72, 0.60, 0.94, NULL, "brNDC");
  setlegendstyle(legS);
  legS->SetTextSize(0.06);
  legS->SetHeader("CR-off");

  TLegend *legSS = new TLegend(0.1787, 0.73, 0.60, 0.944, NULL, "brNDC");
  setlegendstyle(legSS);
  legSS->SetTextSize(0.06);
  legSS->SetHeader("CR-on");

  pad1a->cd();
  for (int i = 0; i < 2; i++)
  {
    h1pro[i]->Draw("E1, cpsame");
    hOFF1pro[i]->Draw("E1, cpsame");
  }
  line1->Draw("same");
  pt0->Draw("same");
  pt1->Draw("same");

  pad2a->cd();
  for (int i = 0; i < 2; i++)
  {
    h2pro[i]->Draw("E1, cpsame");
    hOFF2pro[i]->Draw("E1, cpsame");
  }
  line1->Draw("same");
  pt3->Draw("same");

  pad3a->cd();
  for (int i = 0; i < 2; i++)
  {
    h3pro[i]->Draw("E1, cpsame");
    hOFF3pro[i]->Draw("E1, cpsame");
  }
  line1->Draw("same");
  pt->Draw("same");
  pt7->Draw("same");

  TLegend *pt2 =
      new TLegend(0.1763, 0.77949, 0.506315, 0.925544, NULL, "brNDC");
  pt2->SetHeader(" Non-prompt D^{0}");
  pt2->SetTextSize(0.065);
  //   pt->SetFillColor(0);
  // pt->AddText("|y|<0.5");
  pt2->SetBorderSize(0);

  pad1b->cd();
  for (int i = 0; i < 2; i++)
  {
    h1nonpro[i]->Draw("E1, cpsame");
    hOFF1nonpro[i]->Draw("E1, cpsame");
  }
  line1->Draw("same");
  pt2->Draw("same");

  pad2b->cd();
  for (int i = 0; i < 2; i++)
  {
    h2nonpro[i]->Draw("E1, cpsame");
    hOFF2nonpro[i]->Draw("E1, cpsame");
  }
  legS->AddEntry(hOFF2nonpro[0], "Jetty", "lp");
  legS->AddEntry(hOFF2nonpro[1], "Isotropic", "lp");
  legS->Draw();
  line1->Draw("same");

  pad3b->cd();
  for (int i = 0; i < 2; i++)
  {
    h3nonpro[i]->Draw("E1, cpsame");
    hOFF3nonpro[i]->Draw("E1, cpsame");
  }
  legSS->AddEntry(h3nonpro[0], "Jetty", "lp");
  legSS->AddEntry(h3nonpro[1], "Isotropic", "lp");
  legSS->Draw();
  line1->Draw("same");

  c->Update();

  c->SaveAs("selfnormalised_offon.pdf");
}
