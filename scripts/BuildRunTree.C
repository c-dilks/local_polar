// builds poltr.root, which contains a tree of the data in zdc_pol_table_formatted.txt

void BuildRunTree(const char * filename="zdc_pol_table_formatted.txt")
{
  TFile * poltr_file = new TFile("poltr.root","RECREATE");
  TTree * poltr = new TTree("poltr","poltr");
  char trstr[1024];
  strcpy(trstr,"");
  sprintf(trstr,"%s%s",trstr,"i/I:");               // run index
  sprintf(trstr,"%s%s",trstr,"fill/I:");            // fill number
  sprintf(trstr,"%s%s",trstr,"runnum/I:");          // run number

  sprintf(trstr,"%s%s",trstr,"YF_epsilon/F:");      // yellow forward raw asymmetry
  sprintf(trstr,"%s%s",trstr,"YF_epsilon_err/F:");  // yellow forward raw asymmetry error
  sprintf(trstr,"%s%s",trstr,"YF_pol/F:");          // yellow forward polarisation
  sprintf(trstr,"%s%s",trstr,"YF_pol_err/F:");      // yellow forward polarisation error
  sprintf(trstr,"%s%s",trstr,"YF_AP/F:");           // yellow forward analysing power
  sprintf(trstr,"%s%s",trstr,"YF_AP_err/F:");       // yellow forward analysing power error
  sprintf(trstr,"%s%s",trstr,"YF_phi/F:");          // yellow forward azimuth
  sprintf(trstr,"%s%s",trstr,"YF_phi_err/F:");      // yellow forward azimuth error

  sprintf(trstr,"%s%s",trstr,"YB_epsilon/F:");      // yellow backward raw asymmetry
  sprintf(trstr,"%s%s",trstr,"YB_epsilon_err/F:");  // yellow backward raw asymmetry error
  sprintf(trstr,"%s%s",trstr,"YB_pol/F:");          // yellow backward polarisation
  sprintf(trstr,"%s%s",trstr,"YB_pol_err/F:");      // yellow backward polarisation error
  sprintf(trstr,"%s%s",trstr,"YB_AP/F:");           // yellow backward analysing power
  sprintf(trstr,"%s%s",trstr,"YB_AP_err/F:");       // yellow backward analysing power error
  sprintf(trstr,"%s%s",trstr,"YB_phi/F:");          // yellow backward azimuth
  sprintf(trstr,"%s%s",trstr,"YB_phi_err/F:");      // yellow backward azimuth error

  sprintf(trstr,"%s%s",trstr,"BF_epsilon/F:");      // blue forward raw asymmetry
  sprintf(trstr,"%s%s",trstr,"BF_epsilon_err/F:");  // blue forward raw asymmetry error
  sprintf(trstr,"%s%s",trstr,"BF_pol/F:");          // blue forward polarisation
  sprintf(trstr,"%s%s",trstr,"BF_pol_err/F:");      // blue forward polarisation error
  sprintf(trstr,"%s%s",trstr,"BF_AP/F:");           // blue forward analysing power
  sprintf(trstr,"%s%s",trstr,"BF_AP_err/F:");       // blue forward analysing power error
  sprintf(trstr,"%s%s",trstr,"BF_phi/F:");          // blue forward azimuth
  sprintf(trstr,"%s%s",trstr,"BF_phi_err/F:");      // blue forward azimuth error

  sprintf(trstr,"%s%s",trstr,"BB_epsilon/F:");      // blue backward raw asymmetry
  sprintf(trstr,"%s%s",trstr,"BB_epsilon_err/F:");  // blue backward raw asymmetry error
  sprintf(trstr,"%s%s",trstr,"BB_pol/F:");          // blue backward polarisation
  sprintf(trstr,"%s%s",trstr,"BB_pol_err/F:");      // blue backward polarisation error
  sprintf(trstr,"%s%s",trstr,"BB_AP/F:");           // blue backward analysing power
  sprintf(trstr,"%s%s",trstr,"BB_AP_err/F:");       // blue backward analysing power error
  sprintf(trstr,"%s%s",trstr,"BB_phi/F:");          // blue backward azimuth
  sprintf(trstr,"%s%s",trstr,"BB_phi_err/F");      // blue backward azimuth error

  poltr->ReadFile(filename,trstr);
  poltr->Write();
};


