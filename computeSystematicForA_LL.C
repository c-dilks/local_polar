void computeSystematicForA_LL() {
  enum y_enum {k12,k13};
  Int_t year[2] = {12,13};

  TFile * infile[2];
  TString infileN;
  TTree * poltr[2];
  for(int y=0; y<2; y++) {
    infileN = Form("zdc_pol%dL/poltr.root",year[y]);
    infile[y] = new TFile(infileN.Data(),"READ");
    poltr[y] = (TTree*) infile[y]->Get("poltr");
  };

  enum b_enum {kBF,kYF,kBB,kYB}; // Blue/Yellow Forward/Backward
  TString beam[4] = {"B","Y","B[backward]","Y[backward]"}; // Blue/Yellow Forward/Backward
  TGraphErrors * epsT[2][4]; // [year] [beam]
  TGraphErrors * epsL[2][4]; // [year] [beam]
  TString title,xaxis,yaxis;
  Int_t epsTn[2][4];
  Int_t epsLn[2][4];
  for(int y=0; y<2; y++) for(int b=0; b<4; b++) {
    epsTn[y][b] = 0;
    epsLn[y][b] = 0;

    epsT[y][b] = new TGraphErrors();
    epsL[y][b] = new TGraphErrors();

    if(b==kYF || b==kYB) {
      epsT[y][b]->SetMarkerColor(kOrange+8);
      epsL[y][b]->SetMarkerColor(kOrange+8);
    } else {
      epsT[y][b]->SetMarkerColor(kBlue);
      epsL[y][b]->SetMarkerColor(kBlue);
    };
    epsT[y][b]->SetMarkerStyle(kFullCircle);
    epsL[y][b]->SetMarkerStyle(kFullCircle);
    epsT[y][b]->SetLineWidth(2);
    epsL[y][b]->SetLineWidth(2);

    title = Form("Run %d #varepsilon_{T}^{%s} vs. internal run index",year[y],beam[b].Data());
    epsT[y][b]->SetTitle(title.Data());
    title = Form("Run %d #varepsilon_{L}^{%s} vs. internal run index",year[y],beam[b].Data());
    epsL[y][b]->SetTitle(title.Data());
  };

  Int_t i[2];
  Int_t fill[2];
  Float_t epsilon[2][4];
  Float_t epsilon_err[2][4];
  for(int y=0; y<2; y++) {
    poltr[y]->SetBranchAddress("i",&i[y]);
    poltr[y]->SetBranchAddress("fill",&fill[y]);

    poltr[y]->SetBranchAddress("BF_epsilon",&epsilon[y][kBF]);
    poltr[y]->SetBranchAddress("YF_epsilon",&epsilon[y][kYF]);
    poltr[y]->SetBranchAddress("BB_epsilon",&epsilon[y][kBB]);
    poltr[y]->SetBranchAddress("YB_epsilon",&epsilon[y][kYB]);

    poltr[y]->SetBranchAddress("BF_epsilon_err",&epsilon_err[y][kBF]);
    poltr[y]->SetBranchAddress("YF_epsilon_err",&epsilon_err[y][kYF]);
    poltr[y]->SetBranchAddress("BB_epsilon_err",&epsilon_err[y][kBB]);
    poltr[y]->SetBranchAddress("YB_epsilon_err",&epsilon_err[y][kYB]);
  };

  for(int y=0; y<2; y++) {
    for(int x=0; x<poltr[y]->GetEntries(); x++) {
      poltr[y]->GetEntry(x);

      for(int b=0; b<4; b++) {

        // check if there was a valid measurement, some values of epsilon are 0+/-0
        if(!(epsilon_err[y][b]>0)) continue;

        if(fill[y]==16570 || fill[y]==16578) {
          epsT[y][b]->SetPoint( epsTn[y][b], i[y], epsilon[y][b] ); // transverse fills
          epsT[y][b]->SetPointError( epsTn[y][b], 0, epsilon_err[y][b] ); // transverse fills
          epsTn[y][b]++;
        } else if(fill[y]==16650) {
          continue; // this fill had flaky ZDC
        } else if(fill[y]<16582) {
          continue; // before longitudinal period
        } else {
          epsL[y][b]->SetPoint( epsLn[y][b], i[y], epsilon[y][b] );
          epsL[y][b]->SetPointError( epsLn[y][b], 0, epsilon_err[y][b] );
          epsLn[y][b]++;
        };
      };
    };
  };

  Float_t imin,imax;
  for(int y=0; y<2; y++) for(int b=0; b<4; b++) {
    if(epsTn[y][b]>0) {
      imin = epsT[y][b]->GetXaxis()->GetXmin();
      imax = epsT[y][b]->GetXaxis()->GetXmax();
      epsT[y][b]->Fit("pol0","","",imin-1,imax);
    }
    if(epsLn[y][b]>0) {
      imin = epsL[y][b]->GetXaxis()->GetXmin();
      imax = epsL[y][b]->GetXaxis()->GetXmax();
      epsL[y][b]->Fit("pol0","","",imin-1,imax);
    }
  };

  gStyle->SetOptFit(11);
  gStyle->SetFitFormat(".3g");

  TCanvas * canvT[2];
  for(int y=0; y<2; y++) for(int cc=0; cc<2; cc++) {
    if(y==k13) continue; // (no transverse runs in run13)
    canvT[cc] = new TCanvas();
    canvT[cc]->Divide(1,2);
    for(int pp=1; pp<=2; pp++) canvT[cc]->GetPad(pp)->SetGrid(1,1);
    canvT[cc]->cd(1);
    if(epsTn[y][2*cc]>0) epsT[y][2*cc]->Draw("APE");
    canvT[cc]->cd(2);
    if(epsTn[y][2*cc+1]>0) epsT[y][2*cc+1]->Draw("APE");
  };

  TCanvas * canvL[2];
  for(int y=0; y<2; y++) for(int cc=0; cc<2; cc++) {
    canvL[cc] = new TCanvas();
    canvL[cc]->Divide(1,2);
    for(int pp=1; pp<=2; pp++) canvL[cc]->GetPad(pp)->SetGrid(1,1);
    canvL[cc]->cd(1);
    if(epsLn[y][2*cc]>0) epsL[y][2*cc]->Draw("AP");
    canvL[cc]->cd(2);
    if(epsLn[y][2*cc+1]>0) epsL[y][2*cc+1]->Draw("AP");
  };

  for(int y=0; y<2; y++) for(int b=0; b<4; b++) {
    xaxis = "internal run index";
    yaxis = Form("#varepsilon_{T}^{%s}",beam[b].Data());
    epsT[y][b]->GetXaxis()->SetTitle(xaxis.Data());
    epsT[y][b]->GetYaxis()->SetTitle(yaxis.Data());
    yaxis = Form("#varepsilon_{L}^{%s}",beam[b].Data());
    epsL[y][b]->GetXaxis()->SetTitle(xaxis.Data());
    epsL[y][b]->GetYaxis()->SetTitle(yaxis.Data());
  };

  // compute systematic
  Float_t val_epsTB = epsT[k12][kBF]->GetFunction("pol0")->GetParameter(0);
  Float_t val_epsTY = epsT[k12][kYF]->GetFunction("pol0")->GetParameter(0);

  Float_t val_epsLB[2]; // [year]
  Float_t val_epsLY[2]; // [year]
  for(int y=0; y<2; y++) {
    val_epsLB[y] = epsL[y][kBF]->GetFunction("pol0")->GetParameter(0);
    val_epsLY[y] = epsL[y][kYF]->GetFunction("pol0")->GetParameter(0);
  };

  Float_t aSigma[2] = {0.008,0.008}; // redetermined 10.08.17

  for(int y=0; y<2; y++) {
    printf("\n  Run %d\n",year[y]);
    printf("    epsilon_L^B = %f\n",val_epsLB[y]);
    printf("    epsilon_L^Y = %f\n",val_epsLY[y]);
    printf("    epsilon_T^B = %f\n",val_epsTB);
    printf("    epsilon_T^Y = %f\n",val_epsTY);
    printf("    A_Sigma = %f\n",aSigma[y]);
    printf("    SYSTEMATIC on A_{LL} = %.10f\n\n",
      (val_epsLB[y] / val_epsTB) * (val_epsLY[y] / val_epsTY) * aSigma[y]);
  };
};
