void thrnpe_eff()
{
	//TString infile = "onelz200_240905_131608_76025_res"; //T=15 U=53V - 8.50096 - 6.73469 - p2,n=1.05	
	//TString infile = "onelz200_240905_131647_76025_res"; //T=15 U=53V - 4.08572 - 3.65567 - p9,n=1.05	
	//TString infile = "onelz200_240905_125310_76025_res"; //T=15 U=54V - 8.05748 - 7.00863 - p2,n=1.05	
	//TString infile = "onelz200_240905_125233_76025_res"; //T=15 U=54V - 6.26868 - 5.17476 - p9,n=1.05	
	
	//TString infile = "onelz200_240905_135117_76025_res"; //T=45 U=57V - 5.74336 - p2,n=1.05	
	//TString infile = "onelz200_240905_135155_76025_res"; //T=45 U=57V - 5.27964 - 4.15208 - p9,n=1.05	

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//TString infile = "onelz200_240905_131532_76025_res"; //T=15 U=53V - 12.6185 - p2,n=1.13	
	//TString infile = "onelz200_240905_131608_76025_res"; //T=15 U=53V - 8.50096 - 6.73469 - p9,n=1.13	
	//TString infile = "onelz200_240905_125409_76025_res"; //T=15 U=54V - 9.24601 - p2,n=1.13	
	//TString infile = "onelz200_240905_125310_76025_res"; //T=15 U=54V - 8.05748 - 7.00863  - p9,n=1.13	

	//TString infile = "onelz200_240905_135004_76025_res"; //T=45 U=57V - 12.8865 - p2,n=1.13  -	
	//TString infile = "onelz200_240905_135040_76025_res"; //T=45 U=57V - 7.51046 - p2,n=1.13	
	//TString infile = "onelz200_240905_135117_76025_res"; //T=45 U=57V - 5.74336 - p9,n=1.13	

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//TString infile = "onelz200_240905_115451_76025_res"; //T=25 U=55V - 	5.17603 -  4.34206 ph.e.  2.5-7.5%
	//TString infile = "onelz200_240905_115552_76025_res"; //T=25 U=55V - 7.23574 - 6.14482 ph.e.  2.5-5% 
	//TString infile = "onelz200_240905_115702_76025_res"; //T=25 U=55V - 8.26413 ph.e.            2.5-2.5%
	TString infile = "onelz200_240905_115811_76025_res"; //T=25 U=55V - 10.8504 ph.e.   2.5-0%

        //**********************************************
        //float A1phe = 3.05944; //T=15 U=53V    
        //float A1phe = 3.71949; //T=15 U=54V
	//***********************    
        //float A1phe = 6.74038; //T=45 U=57V    
        //**********************************************
        float A1phe = 4.3029; //T=25 U=55V,   run-115158
        //**********************************************

        TString infileroot = infile + ".root"; 
	TString outDir="out/";
	TString outfile = "underther_eff_" + infileroot;

	TFile *f=new TFile(outDir + infileroot);

	auto fout = TFile::Open(outDir + outfile,"RECREATE");
        TH1F *hped=(TH1F*)f->Get("hAmpPed");

	TF1* fitG = new TF1("fitG","gaus",-10.,50.);
        hped->Fit("fitG","LQ","",-10.,1.7);
        Double_t g1 = fitG->GetParameter(1);

        TH1F *hsig=(TH1F*)f->Get("hAmpSig");
	//hped->Draw();	
	
	hped->SetAxisRange(-10., 100.,"X");

	int binBorder1, firstbin, lastbin;
	float integral_before, integral_after, integral_all;
	float underthr_eff, underthr_effErr, underthr_Npe, underthr_NpeErr;
	
	int binBorder2, firstbin2, lastbin2;
	float integral_before2, integral_after2, integral_all2;
	float eff, effErr, Npe, NpeErr;
	float Ksigma, errKsigma, errKsigma1, errKsigma2;

	float border1;
	
	vector< float > vec_ch, vec_npe, vec_underthr_eff, vec_underthr_effErr, vec_eff, vec_effErr, vec_Ksigma, vec_errKsigma;

	for(int i=3; i<=20; i++ ){   //t15, u54v - 7phe 
	//for(int i=2; i<=20; i++ ){   //t15, u54v - 5phe 
	//for(int i=6; i<=40; i++ ){    //t45, u57v - 5.7phe
	//for(int i=3; i<=40; i++ ){    //t45, u57v - 4phe
	//////////////////////////////////////////////////
	//for(int i=2; i<=25; i++ ){    //t15, u54v - 9phe
	//for(int i=2; i<=25; i++ ){    //t15, u54v - 7phe
	//for(int i=2; i<=50; i++ ){    //t45, u57v - 7.5phe
	//for(int i=2; i<=40; i++ ){    //t45, u57v - 5.7phe
		cout<<"===================================================="<<endl;
		border1 = i;
		cout<<"border1 = "<<border1<<endl;
        	binBorder1 = hped->GetXaxis()->FindBin(border1);
        	//firstbin = hped->GetXaxis()->FindBin(-100);
        	//lastbin = hped->GetXaxis()->FindBin(1900);
        	firstbin = hped->GetXaxis()->FindBin(-10);
        	lastbin = hped->GetXaxis()->FindBin(140);

        	integral_before = hped->Integral(firstbin,binBorder1);
        	integral_after = hped->Integral(binBorder1,lastbin);
        	integral_all = hped->Integral(firstbin,lastbin);
        	cout<<"integral_after:"<<integral_after<<endl;
        	cout<<"integral_all:"<<integral_all<<endl;

		
		if( integral_after<=1 ) 
		{
			integral_after = 2;
			integral_all = integral_all - 2;
		}
                 
		
		underthr_eff = (integral_after/integral_all);
		underthr_effErr = sqrt(integral_after*(integral_all-integral_after)/pow(integral_all,3));
        	underthr_Npe = -log(1-underthr_eff);
        	underthr_NpeErr = underthr_effErr/(1-underthr_eff);

        	binBorder2 = hsig->GetXaxis()->FindBin(border1);
        	//firstbin2 = hsig->GetXaxis()->FindBin(-100);
        	//lastbin2 = hsig->GetXaxis()->FindBin(1900);
        	firstbin2 = hsig->GetXaxis()->FindBin(-10);
        	lastbin2 = hsig->GetXaxis()->FindBin(140);

        	integral_before2 = hsig->Integral(firstbin2,binBorder2);
        	integral_after2 = hsig->Integral(binBorder2,lastbin2);
        	integral_all2 = hsig->Integral(firstbin2,lastbin2);
        	cout<<"integral_after2:"<<integral_after2<<endl;
        	cout<<"integral_all2:"<<integral_all2<<endl;

		if( integral_after2>=(integral_all2-1) )
		{
			integral_after2 = integral_after2 - 2;
		}

		eff = (integral_after2/integral_all2);
		effErr = sqrt(integral_after2*(integral_all2-integral_after2)/pow(integral_all2,3));
        	Npe = -log(1-eff);
       	 	NpeErr = effErr/(1-eff);

		vec_ch.push_back(border1);
		//vec_npe.push_back(border1/A1phe);
		//vec_npe.push_back((border1 - hped->GetMean())/A1phe);
		vec_npe.push_back((border1 - g1)/A1phe);
		vec_underthr_eff.push_back(underthr_eff);
		vec_underthr_effErr.push_back(underthr_NpeErr);
		//vec_eff.push_back(eff);
		vec_eff.push_back(1.-eff);
		vec_effErr.push_back(effErr);

		Ksigma = abs(sqrt(2.)*(TMath::ErfInverse(1-2*underthr_eff)+TMath::ErfInverse(1-2*(1-eff))));
		cout<<"underthr_eff-underthr_effErr = "<<underthr_eff-underthr_effErr<<endl;
		cout<<"eff-effErr = "<<eff-effErr<<endl;
		cout<<"underthr_eff+underthr_effErr = "<<underthr_eff+underthr_effErr<<endl;
		cout<<"eff+effErr = "<<eff+effErr<<endl;
		errKsigma1 = Ksigma - abs(sqrt(2.)*(TMath::ErfInverse(1-2*(underthr_eff-underthr_effErr))+TMath::ErfInverse(1-2*(1-(eff+effErr)))));
		errKsigma2 = Ksigma - abs(sqrt(2.)*(TMath::ErfInverse(1-2*(underthr_eff+underthr_effErr))+TMath::ErfInverse(1-2*(1-(eff-effErr)))));
		cout<<"Ksigma = "<<Ksigma<<endl;
		cout<<"errKsigma1 = "<<errKsigma1<<endl;
		cout<<"errKsigma2 = "<<errKsigma2<<endl;
		errKsigma = abs(errKsigma1);
		if( abs(errKsigma2)>abs(errKsigma) ) errKsigma = abs(errKsigma2);
		vec_Ksigma.push_back(Ksigma);
		vec_errKsigma.push_back(errKsigma);

        	cout<<"*************************************************"<<endl;
        	cout<<"underthr_eff = " << underthr_eff * 100 <<" +/- "<< underthr_effErr*100 <<"%"<<endl;
        	cout<<"underthr_Nph.e. = " << underthr_Npe <<" +/- "<< underthr_NpeErr <<endl;
        	cout<<"*************************************************"<<endl;
		cout<<"eff = " << eff * 100 <<" +/- "<< effErr*100 <<"%"<<endl;
        	cout<<"Nph.e. = " << Npe <<" +/- "<<NpeErr<<endl;
        	cout<<"*************************************************"<<endl;
	}

	TGraphErrors* gr1 = new TGraphErrors(vec_ch.size(), &vec_ch[0], &vec_underthr_eff[0], 0, &vec_underthr_effErr[0]);
	//TGraphErrors* gr1 = new TGraphErrors(vec_ch.size(), &vec_ch[0], &vec_underthr_eff[0], 0, 0);
	gr1->SetMarkerStyle(21);
  	gr1->SetMarkerSize(0.8);
  	gr1->SetMarkerColor(4);
  	gr1->SetLineWidth(2);
  	gr1->SetLineColor(4);

	TGraphErrors* gr2 = new TGraphErrors(vec_ch.size(), &vec_ch[0], &vec_eff[0], 0, &vec_effErr[0]);
	//TGraphErrors* gr2 = new TGraphErrors(vec_ch.size(), &vec_ch[0], &vec_eff[0], 0, 0);
	gr2->SetMarkerStyle(24);
  	gr2->SetMarkerSize(0.8);
  	gr2->SetMarkerColor(2);
  	gr2->SetLineWidth(2);
  	gr2->SetLineColor(2);

	TMultiGraph *mg = new TMultiGraph();
   	mg->Add(gr1);
   	mg->Add(gr2);
	mg->SetTitle("; Threshold, Channels; Misidentification");
	mg->GetYaxis()->SetRangeUser(0, 1);

	TGraphErrors* gr3 = new TGraphErrors(vec_ch.size(), &vec_ch[0], &vec_Ksigma[0], 0, &vec_errKsigma[0]);
	gr3->SetMarkerStyle(24);
  	gr3->SetMarkerSize(0.8);
  	gr3->SetMarkerColor(6);
  	gr3->SetLineWidth(2);
  	gr3->SetLineColor(6);
	gr3->SetTitle("; Threshold, Channels; #sigma");
	gr3->GetYaxis()->SetRangeUser(0, 8);

	//***********************************************
	
	TGraphErrors* gr4 = new TGraphErrors(vec_npe.size(), &vec_npe[0], &vec_underthr_eff[0], 0, &vec_underthr_effErr[0]);
	gr4->SetMarkerStyle(21);
  	gr4->SetMarkerSize(0.8);
  	gr4->SetMarkerColor(4);
  	gr4->SetLineWidth(2);
  	gr4->SetLineColor(4);

	TGraphErrors* gr5 = new TGraphErrors(vec_npe.size(), &vec_npe[0], &vec_eff[0], 0, &vec_effErr[0]);
	gr5->SetMarkerStyle(24);
  	gr5->SetMarkerSize(0.8);
  	gr5->SetMarkerColor(2);
  	gr5->SetLineWidth(2);
  	gr5->SetLineColor(2);

	TMultiGraph *mg2 = new TMultiGraph();
   	mg2->Add(gr4);
   	mg2->Add(gr5);
	mg2->SetTitle("; Threshold, npe; Misidentification");
	mg2->GetYaxis()->SetRangeUser(0, 1);

	TCanvas *c1 = new TCanvas("c1","c1",600,400);
	TGraphErrors* gr6 = new TGraphErrors(vec_npe.size(), &vec_npe[0], &vec_Ksigma[0], 0, &vec_errKsigma[0]);
	gr6->SetMarkerStyle(24);
  	gr6->SetMarkerSize(0.8);
  	gr6->SetMarkerColor(6);
  	gr6->SetLineWidth(2);
  	gr6->SetLineColor(6);
	gr6->SetTitle("; Threshold, npe; #sigma");
	gr6->GetYaxis()->SetRangeUser(0, 8);
	gr6->Draw();
	c1->SaveAs("out/" + infile + "sigma_NpeTrh.png");

	mg->Write("misident");
	mg2->Write("misident_npe");
	gr3->Write("sigma");
	gr6->Write("sigma_npe");
	hped->SetLineColor(4);
        hped->SetTitle(" ");
	hped->Write();
	hsig->SetLineColor(2);
        hsig->SetTitle(" ");
	hsig->Write();
	fout->Close();
}	

