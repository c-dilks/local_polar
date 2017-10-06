void computeSystematic() {
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
  TGraph * epsT[2][4]; // [year] [beam]
  TGraph * epsL[2][4]; // [year] [beam]
  TString title;
  Int_t epsTn[2][4];
  Int_t epsLn[2][4];
  for(int y=0; y<2; y++) for(int b=0; b<4; b++) {
    epsTn[y][b] = 0;
    epsLn[y][b] = 0;

    epsT[y][b] = new TGraph();
    epsL[y][b] = new TGraph();

    if(b==kYF || b==kYB) {
      epsT[y][b]->SetMarkerColor(kOrange);
      epsL[y][b]->SetMarkerColor(kOrange);
    } else {
      epsT[y][b]->SetMarkerColor(kBlue);
      epsL[y][b]->SetMarkerColor(kBlue);
    };
    epsT[y][b]->SetMarkerStyle(kFullCircle);
    epsL[y][b]->SetMarkerStyle(kFullCircle);

    title = Form("Run %d #varepsilon_{T}^{%s} vs. internal run index",year[y],beam[b].Data());
    epsT[y][b]->SetTitle(title.Data());
    title = Form("Run %d #varepsilon_{L}^{%s} vs. internal run index",year[y],beam[b].Data());
    epsL[y][b]->SetTitle(title.Data());
  };

  Int_t i[2];
  Int_t fill[2];
  Float_t epsilon[2][4];
  for(int y=0; y<2; y++) {
    poltr[y]->SetBranchAddress("i",&i[y]);
    poltr[y]->SetBranchAddress("fill",&fill[y]);
    poltr[y]->SetBranchAddress("BF_epsilon",&epsilon[y][kBF]);
    poltr[y]->SetBranchAddress("YF_epsilon",&epsilon[y][kYF]);
    poltr[y]->SetBranchAddress("BB_epsilon",&epsilon[y][kBB]);
    poltr[y]->SetBranchAddress("YB_epsilon",&epsilon[y][kYB]);
  };

  for(int y=0; y<2; y++) {
    for(int x=0; x<poltr[y]->GetEntries(); x++) {
      poltr[y]->GetEntry(x);

      for(int b=0; b<4; b++) {
        if(fill[y]==16570 || fill[y]==16578) {
          epsT[y][b]->SetPoint( epsTn[y][b]++, i[y], epsilon[y][b] );
        } else {
          epsL[y][b]->SetPoint( epsLn[y][b]++, i[y], epsilon[y][b] );
        };
      };
    };
  };


  TCanvas * canvT[2];
  for(int y=0; y<2; y++) for(int cc=0; cc<2; cc++) {
    canvT[cc] = new TCanvas();
    canvT[cc]->Divide(1,2);
    canvT[cc]->cd(1);
    if(epsTn[y][2*cc]>0) epsT[y][2*cc]->Draw("AP");
    canvT[cc]->cd(2);
    if(epsTn[y][2*cc+1]>0) epsT[y][2*cc+1]->Draw("AP");
  };

  TCanvas * canvL[2];
  for(int y=0; y<2; y++) for(int cc=0; cc<2; cc++) {
    canvL[cc] = new TCanvas();
    canvL[cc]->Divide(1,2);
    canvL[cc]->cd(1);
    if(epsLn[y][2*cc]>0) epsL[y][2*cc]->Draw("AP");
    canvL[cc]->cd(2);
    if(epsLn[y][2*cc+1]>0) epsL[y][2*cc+1]->Draw("AP");
  };
};
