void u_f_npe_draw()
{
   //TString name = "u_npe_f_t15_2.5-12.5";    
   //TString name = "u_npe_f_t15_2.5-10";    
   //TString name = "u_npe_f_t45_2.5-12.5";    
   TString name = "u_npe_f_t45_2.5-10";    

   TString fin = "out/" + name + ".dat";
   TString fout = "out/" + name + ".png";

   float U[15], npe[15], err_npe[15], freq[15], err_freq[15];

   FILE *f = fopen(fin,"r");
   Int_t i=0;
   while (!feof(f)){
	fscanf(f,"%f %f %f %f %f\n",&U[i],&npe[i],&err_npe[i],&freq[i],&err_freq[i]);
	//freq[i] = freq[i];
        err_freq[i] = 0.2;
	//err_npe[i] = err_npe[i]/3.;
	cout<<i<<"\t"<<U[i]<<"\t"<<npe[i]<<"\t"<<freq[i]<<"\t"<<npe[i]/freq[i]<<endl;
	i++;
   }
 
   auto g1 = new TGraphErrors(i,U,npe,0,err_npe);
   auto g2 = new TGraphErrors(i,U,freq,0,err_freq);

   TMultiGraph* mg = new TMultiGraph();

   TCanvas *c1 = new TCanvas();
   c1->SetBorderSize(0);
   c1->SetFillColor(kWhite);
   c1->SetGrid();
   
   TPad *pad1 = new TPad("pad1","",0,0,1,1);
   pad1->SetFillStyle(4000);
   pad1->SetFillColor(kWhite);
   pad1->SetFrameBorderMode(0);
   pad1->Draw();
   pad1->cd();

   mg->Add(g1);
   mg->Add(g2);
   
   g1->Draw("ALP");
   g1->SetMarkerStyle(21);
   g1->SetTitle(" ; U, V; #mu_{ph.e.}");
   g1->GetYaxis()->SetRangeUser(0.5, 2.5);
   //g1->GetYaxis()->SetRangeUser(0, 5.0);
   
   c1->cd();	
   TPad *pad2 = new TPad("pad2","",0,0,1,1);
   pad2->SetFillStyle(4000); //will be transparent 
   pad2->SetFillColor(kWhite);
   pad2->SetFrameBorderMode(0);
   pad2->SetFrameFillStyle(0);
   pad2->Draw();
   pad2->cd();

   g2->Draw("Y+ALP,same");
   g2->SetMarkerStyle(22);
   g2->SetMarkerColor(kRed);
   g2->SetLineColor(kRed);
   g2->SetTitle(" ; U, V; Frequency, MHz");
   g2->GetYaxis()->SetTitleOffset(1.0);
   //g2->GetYaxis()->SetRangeUser(0, 2.0);
   g2->GetYaxis()->SetRangeUser(0, 6.5);
   g2->GetYaxis()->SetAxisColor(kRed);
   g2->GetYaxis()->SetLabelColor(kRed);
   g2->GetYaxis()->SetTitleColor(kRed);
   c1->cd();
   
   c1->SaveAs(fout);
} 
