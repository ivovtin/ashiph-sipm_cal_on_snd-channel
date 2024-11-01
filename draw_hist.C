void draw_hist(TString listfile = "115811")
{
    cout << "Reprocessing file with Run number: " << listfile << endl;

    TString inDir = "data";	
    //TString infile = "onelz200_240905_114343_76025";    //T=25C, U=55V, 2.5V-12.5%
    //TString infile = "onelz200_240905_135337_76025";    //T=45C, U=57V, 2.5V-12.5%
    
    TString infile = "onelz200_240905_" + listfile + "_76025";

    TString inName = inDir + "/" + infile + ".dat";	

    vector<std::vector<int> > allData;

    ifstream fin(inName);
    string line;
    while (getline(fin, line)) 
    {
	vector<int> lineData;
    	int val;
	istringstream lineStream(line);
	while (lineStream >> val) 
	{
		lineData.push_back(val);
	}
	allData.push_back(lineData);
    }
    cout << "Events: " << allData.size() << "\n";
    cout << "row 0 contains " << allData[0].size() << " columns\n";
    cout << "row 0, column 0 is " << allData[0][0] << '\n';
    cout << "row 0, column 1 is " << allData[0][1] << '\n';

    TString outName = "out/" + infile + "_res.root"; 	

    auto f = TFile::Open(outName,"RECREATE");    
    
    char name0[allData.size()];
    char name1[allData.size()];
    //TH2F* timeAmp[allData.size()];
    TProfile* timeAmp[allData.size()];
    TProfile* timeAmpCor[allData.size()];

    //Double_t bHist1 = -10.;
    //Double_t bHist2 = 100.;
    //TH1F* hAmpPed = new TH1F("hAmpPed", "Counter amplitude", 1000, bHist1, bHist2);
    //TH1F* hAmpSig = new TH1F("hAmpSig", "Counter amplitude", 1000, bHist1, bHist2);
    //Double_t bHist1 = -100.;
    //Double_t bHist2 = 1900.;
    //TH1F* hAmpPed = new TH1F("hAmpPed", "Counter amplitude", 2000, bHist1, bHist2);
    //TH1F* hAmpSig = new TH1F("hAmpSig", "Counter amplitude", 2000, bHist1, bHist2);
    Double_t bHist1 = -10.;
    Double_t bHist2 = 140.;
    TH1F* hAmpPed = new TH1F("hAmpPed", "Counter amplitude", 1000, bHist1, bHist2);
    TH1F* hAmpSig = new TH1F("hAmpSig", "Counter amplitude", 1000, bHist1, bHist2);

    Double_t bHistInt1 = -500.;
    Double_t bHistInt2 = 10000.;
    TH1F* hAmpPedInt = new TH1F("hAmpPedInt", "Counter amplitude", 1000, bHistInt1, bHistInt2);
    TH1F* hAmpSigInt = new TH1F("hAmpSigInt", "Counter amplitude", 1000, bHistInt1, bHistInt2);

    TH2F *hosc = new TH2F("hosc",";Time, ticks; Amplitude, channels",200,0,200,200,0,500);

    Double_t binFit1 = 20.;	 
    Double_t binFit2 = 65.;	 

    Double_t binPed1 = 110.;	 
    Double_t binPed2 = 140.;	 

    Double_t binSig1 = 140.;
    Double_t binSig2 = 170.;

    for (int j=0; j<allData.size(); j++)
    //for (int j=0; j<50; j++)
    {
    	if( allData[j][0] == 1 )
    	{
	  sprintf(name0,"Ev%d",j);
	  timeAmp[j] = new TProfile(name0, "a(t) for Cnt",200,0,200);
	  timeAmp[j]->SetMarkerStyle(20);
	  timeAmp[j]->SetMarkerSize(0.5);
	  timeAmp[j]->SetMarkerColor(1); 
	  sprintf(name1,"EvCor%d",j);
	  timeAmpCor[j] = new TProfile(name1, "a(t) for Cnt",200,0,200);
	  
          for(int bin=1; bin<allData[j].size(); bin++)
          {
    	    timeAmp[j]->Fill(bin-1,allData[j][bin]);
    	    timeAmpCor[j]->Fill(bin-1,1000.-allData[j][bin]);
	    hosc->Fill(bin-1,allData[j][bin]);
    	  }
    	  		
	  auto h = new TH1F("h","osc",199,0,199);
          for (int k = 0; k < timeAmpCor[j]->GetNbinsX(); k++ )
          {
              h->SetBinContent(k, timeAmpCor[j]->GetBinContent(k));
	      //cout<<k<<"\t"<<timeAmpCor[j]->GetBinContent(k)<<endl;
          }
	  h->Draw("");
	   	
          //auto s = new TSpectrum();
          //auto hb = s->Background(h,40,"same");
            
	  const Int_t nbins = 199;
	  Double_t source[nbins];
	  for (int i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);
	  TSpectrum *s = new TSpectrum();
	  //s->Background(source, nbins, 40, TSpectrum::kBackDecreasingWindow, TSpectrum::kBackOrder2, kFALSE, TSpectrum::kBackSmoothing3, kFALSE); //-
	  //s->Background(source, nbins, 6, TSpectrum::kBackDecreasingWindow, TSpectrum::kBackOrder2, kTRUE, TSpectrum::kBackSmoothing3, kFALSE);     //++
	  s->Background(source, nbins, 8, TSpectrum::kBackDecreasingWindow, TSpectrum::kBackOrder2, kTRUE, TSpectrum::kBackSmoothing3, kFALSE);     //++
	  //s->Background(source, nbins, 40, TSpectrum::kBackDecreasingWindow, TSpectrum::kBackOrder2, kTRUE, TSpectrum::kBackSmoothing3, kFALSE);     //+
	  //s->Background(source, nbins, 6, TSpectrum::kBackDecreasingWindow, TSpectrum::kBackOrder2, kTRUE, TSpectrum::kBackSmoothing5, kFALSE);     //++
	  //s->Background(source, nbins, 6, TSpectrum::kBackIncreasingWindow, TSpectrum::kBackOrder2, kFALSE, TSpectrum::kBackSmoothing3, kFALSE);  //-
	  //s->Background(source, nbins, 10, TSpectrum::kBackDecreasingWindow, TSpectrum::kBackOrder8, kTRUE, TSpectrum::kBackSmoothing5, kTRUE);    //-	
	  //s->Background(source, nbins, 40, TSpectrum::kBackDecreasingWindow, TSpectrum::kBackOrder8, kFALSE, TSpectrum::kBackSmoothing3, kFALSE);  //-

	  TH1F *d1 = new TH1F("d1","",nbins,0,199);
	  for (int i = 0; i < nbins; i++) d1->SetBinContent(i + 1,source[i]);
   	  d1->SetLineColor(kRed);
          d1->Draw("SAME L");
	   
          TProfile* amp = new TProfile("amp", "a(t) for Cnt", 200, 0. , 200);
          for(int k=0; k<=h->GetNbinsX(); k++)
          {
             //amp->Fill( k, h->GetBinContent(k) - hb->GetBinContent(k) );
             amp->Fill( k, h->GetBinContent(k) - d1->GetBinContent(k) );
             //amp->Fill( k, h->GetBinContent(k) );
             //cout<<k<<"\t"<<h->GetBinContent(k)<<"\t"<<hb->GetBinContent(k)<<endl;
          }
   	  
	  /*
	  TF1* fitl = new TF1("fitl","pol0",binPed1, binPed2);
          amp->Fit("fitl","LQ","",binPed1, binPed2);
          Double_t p0 = fitl->GetParameter(0);
	  */
	  //ped area
          amp->GetXaxis()->SetRangeUser(binPed1, binPed2);

          float meanPed = amp->GetMean(2);
          float maxped1 = amp->GetMaximum();
          float maxbinped1 = amp->GetMaximumBin();
          float maxped2 = amp->GetBinContent(maxbinped1+1);
          float maxped3 = amp->GetBinContent(maxbinped1+2);
          float maxped4 = amp->GetBinContent(maxbinped1-1);
          float ped = (maxped1 + maxped2 + maxped3 + maxped4)/4.;
          //float ped = (maxped1 + maxped2 + maxped3)/3.;
          //float ped = (maxped1 + maxped2 + maxped3)/3. - p0;

	  float intPed = 0.;
          for(int k=binPed1; k<=binPed2; k++)
          {
             Double_t binContPed = amp->GetBinContent(k);
             intPed += binContPed;
          }

	  amp->GetXaxis()->SetRangeUser(binSig1, binSig2);

          float max1 = amp->GetMaximum();
          float maxbin1 = amp->GetMaximumBin();
          float max2 = amp->GetBinContent(maxbin1+1);
          float max3 = amp->GetBinContent(maxbin1+2);
          float max4 = amp->GetBinContent(maxbin1-1);
          float sig = (max1 + max2 + max3 + max4)/4.;
          //float sig = (max1 + max2 + max3)/3.;
          //float sig = (max1 + max2 + max3)/3. - p0;

	  float intSig = 0.;
          for(int y=binSig1; y<=binSig2; y++)
          {
             Double_t binContSig = amp->GetBinContent(y);
             intSig += binContSig;
          }

	  //cout<<i<<"\t"<<sig<<endl;
	  amp->GetXaxis()->SetRangeUser(0, 199);
	  //amp->GetXaxis()->SetRangeUser(0, 200);

	  hAmpPed->Fill(ped);
	  hAmpSig->Fill(sig);

	  hAmpPedInt->Fill(intPed);
          hAmpSigInt->Fill(intSig);

	  if( j<100 )
          {
            TString ii;
            ii.Form("%d", j);
            amp->Write("amp_"+ii);
            h->Write("h_"+ii);
            //d1->Write("d1_"+ii);
            //hb->Write("hb_"+ii);
          }
          
          amp->Delete();
    	  h->Delete();    	     	  	 
    	  d1->Delete();    	     	  	 
       }
    }
    
    cout<<"***************** 1 method: ============== Nphe calculation =====>> from pulse amplitude ============================"<<endl;
    TF1* fitG = new TF1("fitG","gaus",-30.,100.);
    hAmpPed->Fit("fitG","Q","",-30.,1.7);
    Double_t g1 = fitG->GetParameter(1);
    Double_t g2 = fitG->GetParameter(2);
    float border1 = g1 + 3.0*g2;
    //float border1 = 1.7;
    fitG = hAmpPed->GetFunction("fitG");
    fitG->SetLineColor(7);

    //Calculation from Puasson
    int binBorder1 = hAmpSig->GetXaxis()->FindBin(border1);
    int firstbin = hAmpSig->GetXaxis()->FindBin(bHist1);
    int lastbin = hAmpSig->GetXaxis()->FindBin(bHist2);

    float integral_before = hAmpSig->Integral(firstbin,binBorder1);
    float integral_after = hAmpSig->Integral(binBorder1,lastbin);
    float integral_all = hAmpSig->Integral(firstbin,lastbin);

    int firstbinPed = hAmpPed->GetXaxis()->FindBin(bHist1);
    int lastbinPed = hAmpPed->GetXaxis()->FindBin(bHist2);

    float integral_beforePed = hAmpPed->Integral(firstbinPed,binBorder1);
    float integral_afterPed = hAmpPed->Integral(binBorder1,lastbinPed);
    float integral_allPed = hAmpPed->Integral(firstbinPed,lastbinPed);

    float prob = (integral_before/integral_all)*(integral_allPed/integral_beforePed);
    float probErr = sqrt(integral_before*(integral_all-integral_before)/pow(integral_before,3)) + sqrt(integral_allPed*(integral_allPed-integral_beforePed)/pow(integral_allPed,3));

    cout<<prob<<"\t"<<probErr<<endl;

    float Npe = -log(prob);
    float NpeErr = probErr/prob;
    //float NpeErr1 = -log(prob+probErr);
    //float NpeErr2 = -log(prob-probErr);
    //float NpeErr = NpeErr1 - (NpeErr1+NpeErr2)/2.;

    cout<<"border1:"<<border1<<endl;
    cout<<"integral_after:"<<integral_after<<endl;
    cout<<"integral_all:"<<integral_all<<endl;
    cout<<"Aped = " << g1 <<endl;
    cout<<"Ch_Ampl. = " << hAmpSig->GetMean() <<" +/- "<<hAmpSig->GetRMS()<<endl;
    cout<<"Ch_Ampl.-Aped = " << hAmpSig->GetMean() - g1 <<endl;

    cout<<"Nph.e. = " << Npe <<" +/- "<< NpeErr <<endl;
    cout<<"Amp 1ph.e. = " << (hAmpSig->GetMean() - g1)/Npe <<" +/- "<<NpeErr<<endl;

    float Freq = (integral_afterPed/integral_allPed)/(binPed2-binPed1)*pow(10,9)/5.;
    float err_Freq = sqrt(integral_afterPed*(integral_allPed-integral_afterPed)/pow(integral_afterPed,3))/(binPed2-binPed1)*pow(10,9)/5.;
    cout<<"Freq = "<< Freq <<" +/- "<< err_Freq <<endl;

    cout<<"S/N = "<< Npe/Freq <<endl;

    
    //Calculation from normalization to A1phe
    //float A1phe = 3.05944;     //131722 - runs/list_t15_u53.dat +
    //float A1phe = 3.71949;     //124924 - runs/list_t15_u54.dat +
    //float A1phe = 4.15636;     //130325 - runs/list_t15_u55.dat +
    //float A1phe = 4.642;       //131130 - runs/list_t15_u56.dat +
    ///////////////////////////////////////////////////////////// 
    //float A1phe = 3.69211;     //122338 - runs/list_t25_u54.dat +
    float A1phe = 4.3029;      //115158 - runs/list_t25_u55.dat +
    //float A1phe = 4.61824;     //120511 - runs/list_t25_u56.dat +
    //float A1phe = 5.37618;     //122052 - runs/list_t25_u57.dat +
    ///////////////////////////////////////////////////////////// 
    //float A1phe = 4.55618;     //133639 - runs/list_t45_u55.dat +
    //float A1phe = 5.1241;      //134443 - runs/list_t45_u56.dat +
    //float A1phe = 6.74038;     //135337 - runs/list_t45_u57.dat +
    //float A1phe = 7.60752;     //140137 - runs/list_t45_u58.dat +

    float resNpe = ( hAmpSig->GetMean() - g1 )/A1phe;
    float errresNpe = ( hAmpSig->GetRMS()/sqrt(hAmpSig->GetEntries()) + hAmpPed->GetRMS()/sqrt(hAmpPed->GetEntries()) )/A1phe;
    cout<<"Normalized Npe="<<resNpe<<"+-"<<errresNpe<<endl;

    //TString SoutF = "out/res_" + infile + ".dat";
    TString SoutF = "out/results.dat";
    ofstream SfileOut;
    SfileOut.open(SoutF,ios_base::app | ios_base::ate);
    SfileOut << listfile << "\t" << Npe << "\t" << NpeErr << "\t" << (hAmpSig->GetMean() - g1)/Npe << "\t" << A1phe << "\t" << resNpe << "\t" << errresNpe << "\t" << Freq << "\t"<< err_Freq << "\n";
    SfileOut.close();


    TCanvas *c2 = new TCanvas("c2","c2",600,400);
    //hAmpPed->SetAxisRange(bHist1+5, bHist2-60.,"X");
    hAmpPed->SetAxisRange(bHist1+5, hAmpSig->GetMean()+5*hAmpSig->GetRMS(),"X");
    hAmpPed->SetLineColor(kBlue);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.9);
    gStyle->SetStatTextColor(kBlue);
    hAmpPed->Draw();
    hAmpPed->GetXaxis()->SetTitle("Pulse amplitude, channels");
    hAmpPed->GetYaxis()->SetTitle("Number of events");  
    c2->Update();
    //hAmpSig->SetAxisRange(bHist1+5, bHist2-60.,"X");
    hAmpSig->SetAxisRange(bHist1+5, hAmpSig->GetMean()+5*hAmpSig->GetRMS(),"X");
    hAmpSig->SetLineColor(kRed);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.74);
    gStyle->SetStatTextColor(kRed);
    hAmpSig->Draw("sames");
    hAmpSig->GetXaxis()->SetTitle("Pulse amplitude, channels");
    hAmpSig->GetYaxis()->SetTitle("Number of events");
    c2->SaveAs("out/" + infile + ".png");

    /* 
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"***************** 2 method:"<<endl;
    float border1_int = 15490.;
    
    //TF1* fitGint = new TF1("fitGint","gaus",0.,20000.);
    //hAmpPedInt->Fit("fitGint","LQ","",15000.,20000.);
    //Double_t g1int = fitGint->GetParameter(1);
    //Double_t g2int = fitGint->GetParameter(2);	
    //float border1_int = g1int - 2.0*g2int;

    int binBorder1_int = hAmpSigInt->GetXaxis()->FindBin(border1_int);
    int firstbin_int = hAmpSigInt->GetXaxis()->FindBin(bHistInt1);
    int lastbin_int = hAmpSigInt->GetXaxis()->FindBin(bHistInt2);

    float integral_before_int = hAmpSigInt->Integral(binBorder1_int,lastbin_int);
    float integral_after_int = hAmpSigInt->Integral(firstbin_int,binBorder1_int);
    float integral_all_int = hAmpSigInt->Integral(firstbin_int,lastbin_int);

    float effitiency_int = (integral_after_int/integral_all_int);
    float effitiencyErr_int = sqrt(integral_after_int*(integral_all_int-integral_after_int)/pow(integral_after_int,3));

    float Npe_int = -log(1-effitiency_int);
    float NpeErr_int = effitiencyErr_int/(1-effitiency_int);

    cout<<"border1_int:"<<border1_int<<endl;
    cout<<"hAmpPedInt->GetMean() = "<<hAmpPedInt->GetMean()<<endl;
    cout<<"hAmpSigInt->GetMean() = "<<hAmpSigInt->GetMean()<<endl;
    cout<<"Int_Sig - Int_Ped = " << hAmpPedInt->GetMean() - hAmpSigInt->GetMean() <<endl;
    cout<<"Nph.e. = " << Npe_int <<" +/- "<<NpeErr_int<<endl;
    cout<<"Int Amp 1ph.e. = " << (hAmpPedInt->GetMean() - hAmpSigInt->GetMean())/Npe_int <<" +/- "<<NpeErr_int<<endl;
    */

    TCanvas *c3 = new TCanvas("c3","c3",600,400); 
    hAmpPedInt->SetAxisRange(bHistInt1+500, bHistInt2,"X");
    hAmpPedInt->SetLineColor(kBlue);
    //gStyle->SetStatX(0.9);
    gStyle->SetStatX(0.3);
    gStyle->SetStatY(0.9);
    gStyle->SetStatTextColor(kBlue);
    hAmpPedInt->Draw();
    c3->Update();
    hAmpSigInt->SetAxisRange(bHistInt1+500, bHistInt2,"X");
    hAmpSigInt->SetLineColor(kRed);
    //gStyle->SetStatX(0.9);
    gStyle->SetStatX(0.3);
    gStyle->SetStatY(0.74);
    gStyle->SetStatTextColor(kRed);
    hAmpSigInt->Draw("sames");
    c3->SaveAs("out/" + infile + "_int.png");

    TCanvas *c4 = new TCanvas("c4","c4",600,400); 
    gStyle->SetStatX(0.3);
    gStyle->SetStatY(0.5);
    hosc->Draw("colz");
    /*    
    TLine *lines1 = new TLine(binSig1+0.5,0,binSig1+0.5,500);
    TLine *lines2 = new TLine(binSig2,0,binSig2,500);
    TLine *linep1 = new TLine(binPed1,0,binPed1,500);
    TLine *linep2 = new TLine(binPed2-0.5,0,binPed2-0.5,500);
    lines1->SetLineColor(kRed);
    lines1->SetLineStyle(4);
    lines1->Draw();
    lines2->SetLineColor(kRed);
    lines2->SetLineStyle(4);
    lines2->Draw();
    linep1->SetLineColor(kBlue);
    linep1->SetLineStyle(4);
    linep1->Draw();
    linep2->SetLineColor(kBlue);
    linep2->SetLineStyle(4);
    linep2->Draw();
    */
    c4->SaveAs("out/" + infile + "_hosc.png");

    f->Write();
    f->Close();
}
