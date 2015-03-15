// draws some plots based on local polarimetry data in poltr.root

void DrawPlots(const char * filename="poltr.root")
{
  // get running period type information (for plot titles & max binning)
  TTree * rtr = new TTree("rtr","rtr");
  rtr->ReadFile("run_type","year/I:sqrts/I:type/C");
  Int_t year,sqrts;
  char type[16];
  rtr->SetBranchAddress("year",&year);
  rtr->SetBranchAddress("sqrts",&sqrts);
  rtr->SetBranchAddress("type",&type);
  rtr->GetEntry(0);
  printf("year=%d sqrt(s)=%d type=%s\n",2000+year,sqrts,type);


  // open poltr.root
  gStyle->SetOptStat(0);
  TFile * infile = new TFile(filename,"READ");
  TTree * tr = (TTree*) infile->Get("poltr");


  // set pi & number of bins
  const Float_t PI=3.1415;
  const Int_t NBINS=50;


  // set maximum binning
  Float_t pol_fac; // analysing power max = epsilon max / pol_fac
  Float_t epsilon_MAX_YF; // maxima defined separately for each running period
  Float_t epsilon_MAX_YB;
  Float_t epsilon_MAX_BF;
  Float_t epsilon_MAX_BB;
  if(!strcmp(type,"T") && year==11) 
  {
    epsilon_MAX_YF = 0.06;
    epsilon_MAX_YB = 0.006;
    epsilon_MAX_BF = 0.06;
    epsilon_MAX_BB = 0.006;
    pol_fac=0.3;
  }
  else if(!strcmp(type,"T") && year==12) 
  {
    epsilon_MAX_YF = 0.04;
    epsilon_MAX_YB = 0.04;
    epsilon_MAX_BF = 0.04;
    epsilon_MAX_BB = 0.04;
    pol_fac=0.3;
  }
  else if(!strcmp(type,"L"))
  {
    epsilon_MAX_YF = 0.006;
    epsilon_MAX_YB = 0.002;
    epsilon_MAX_BF = 0.006;
    epsilon_MAX_BB = 0.002;
    pol_fac=0.3;
  };
  Float_t AP_MAX_YF = epsilon_MAX_YF/pol_fac;
  Float_t AP_MAX_YB = epsilon_MAX_YB/pol_fac;
  Float_t AP_MAX_BF = epsilon_MAX_BF/pol_fac;
  Float_t AP_MAX_BB = epsilon_MAX_BB/pol_fac;


  // print list of runs which will be cutoff from plots
  printf("\n");
  Float_t YF_epsilon,YB_epsilon,BF_epsilon,BB_epsilon;
  Float_t YF_AP,YB_AP,BF_AP,BB_AP;
  Int_t runnum;
  tr->SetBranchAddress("YF_epsilon",&YF_epsilon);
  tr->SetBranchAddress("YB_epsilon",&YB_epsilon);
  tr->SetBranchAddress("BF_epsilon",&BF_epsilon);
  tr->SetBranchAddress("BB_epsilon",&BB_epsilon);
  tr->SetBranchAddress("YF_AP",&YF_AP);
  tr->SetBranchAddress("YB_AP",&YB_AP);
  tr->SetBranchAddress("BF_AP",&BF_AP);
  tr->SetBranchAddress("BB_AP",&BB_AP);
  tr->SetBranchAddress("runnum",&runnum);
  for(Int_t i=0; i<tr->GetEntries(); i++)
  {
    tr->GetEntry(i);
    if( YF_epsilon > epsilon_MAX_YF || 
        YB_epsilon > epsilon_MAX_YB || 
        BF_epsilon > epsilon_MAX_BF || 
        BB_epsilon > epsilon_MAX_BB)
      printf("run %d has epsilon larger than plot range\n",runnum);
    if( YF_AP > AP_MAX_YF || 
        YB_AP > AP_MAX_YB || 
        BF_AP > AP_MAX_BF || 
        BB_AP > AP_MAX_BB)
      printf("run %d has AP larger than plot range\n",runnum);
  };


  // define correlation 2d histograms
  TH2F * epsilon_corr_F;
  TH2F * epsilon_corr_B;
  TH2F * AP_corr_F;
  TH2F * AP_corr_B;
  char epsilon_corr_F_t[256];
  char epsilon_corr_B_t[256];
  char AP_corr_F_t[256];
  char AP_corr_B_t[256];
  char type_title[64];
  sprintf(type_title,"Run%d pp%d%s",year,sqrts,type);
  sprintf(epsilon_corr_F_t,"%s -- forward raw asymmetry correlation;Blue #epsilon;Yellow #epsilon",type_title);
  sprintf(epsilon_corr_B_t,"%s -- backward raw asymmetry correlation;Blue #epsilon;Yellow #epsilon",type_title);
  sprintf(AP_corr_F_t,"%s -- forward analysing power correlation;Blue A_{P};Yellow A_{P}",type_title);
  sprintf(AP_corr_B_t,"%s -- backward analysing power correlation;Blue A_{P};Yellow A_{P}",type_title);

  Int_t nn=0;
  nn += tr->GetEntries("YF_AP<0");
  nn += tr->GetEntries("YB_AP<0");
  nn += tr->GetEntries("BF_AP<0");
  nn += tr->GetEntries("BB_AP<0");
  if(nn>0)
  {
    printf("extending analysing power plots to +/- AP_MAX, since AP<0 in some cases\n");
    epsilon_corr_F = new TH2F("epsilon_corr_F",epsilon_corr_F_t,2*NBINS,-1*epsilon_MAX_BF,epsilon_MAX_BF,2*NBINS,-1*epsilon_MAX_YF,epsilon_MAX_YF);
    epsilon_corr_B = new TH2F("epsilon_corr_B",epsilon_corr_B_t,2*NBINS,-1*epsilon_MAX_BB,epsilon_MAX_BB,2*NBINS,-1*epsilon_MAX_YB,epsilon_MAX_YB);
    AP_corr_F = new TH2F("AP_corr_F",AP_corr_F_t,2*NBINS,-1*AP_MAX_BF,AP_MAX_BF,2*NBINS,-1*AP_MAX_YF,AP_MAX_YF);
    AP_corr_B = new TH2F("AP_corr_B",AP_corr_B_t,2*NBINS,-1*AP_MAX_BB,AP_MAX_BB,2*NBINS,-1*AP_MAX_YB,AP_MAX_YB);
  }
  else
  {
    epsilon_corr_F = new TH2F("epsilon_corr_F",epsilon_corr_F_t,NBINS,0,epsilon_MAX_BF,NBINS,0,epsilon_MAX_YF);
    epsilon_corr_B = new TH2F("epsilon_corr_B",epsilon_corr_B_t,NBINS,0,epsilon_MAX_BB,NBINS,0,epsilon_MAX_YB);
    AP_corr_F = new TH2F("AP_corr_F",AP_corr_F_t,NBINS,0,AP_MAX_BF,NBINS,0,AP_MAX_YF);
    AP_corr_B = new TH2F("AP_corr_B",AP_corr_B_t,NBINS,0,AP_MAX_BB,NBINS,0,AP_MAX_YB);
  };

  TH2F * phi_corr_F;
  TH2F * phi_corr_B;
  char phi_corr_F_t[256];
  char phi_corr_B_t[256];
  sprintf(phi_corr_F_t,"%s -- Forward Phase Correlation;Blue #phi;Yellow #phi",type_title);
  sprintf(phi_corr_B_t,"%s -- Backward Phase Correlation;Blue #phi;Yellow #phi",type_title);
  phi_corr_F = new TH2F("phi_corr_F",phi_corr_F_t,NBINS,-1*PI,PI,NBINS,-1*PI,PI);
  phi_corr_B = new TH2F("phi_corr_B",phi_corr_B_t,NBINS,-1*PI,PI,NBINS,-1*PI,PI);

  epsilon_corr_F->GetYaxis()->SetTitleOffset(1.5);
  epsilon_corr_B->GetYaxis()->SetTitleOffset(1.5);
  AP_corr_F->GetYaxis()->SetTitleOffset(1.5);
  AP_corr_B->GetYaxis()->SetTitleOffset(1.5);


  // cut for runs which have zero asymmetry and valid polarization measurements (sometimes P>1 ?????????????????)
  char clean_cut[256];
  sprintf(clean_cut,"abs(BF_AP)>0 && abs(BB_AP)>0 && abs(YF_AP)>0 && abs(YB_AP)>0 && BF_pol<1 && YF_pol<1 && BB_pol<1 && YB_pol<1");


  // project correlation plots
  tr->Project("epsilon_corr_F","YF_epsilon:BF_epsilon",clean_cut);
  tr->Project("epsilon_corr_B","YB_epsilon:BB_epsilon",clean_cut);
  tr->Project("AP_corr_F","YF_AP:BF_AP",clean_cut);
  tr->Project("AP_corr_B","YB_AP:BB_AP",clean_cut);
  tr->Project("phi_corr_F","YF_phi:BF_phi",clean_cut);
  tr->Project("phi_corr_B","YB_phi:BB_phi",clean_cut);

  
  // draw correlation plots
  TCanvas * cc = new TCanvas("cc","cc",1600,800);
  cc->Divide(3,2);
  for(Int_t i=1; i<=6; i++) 
  {
    cc->GetPad(i)->SetLogz();
    cc->GetPad(i)->SetGrid(1,1);
  };
  cc->cd(1); epsilon_corr_F->Draw("colz");
  cc->cd(4); epsilon_corr_B->Draw("colz");
  cc->cd(2); AP_corr_F->Draw("colz");
  cc->cd(5); AP_corr_B->Draw("colz");
  cc->cd(3); phi_corr_F->Draw("colz");
  cc->cd(6); phi_corr_B->Draw("colz");
};
