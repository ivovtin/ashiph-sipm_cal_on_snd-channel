void u_npe_draw()
{
   //double U[4] = {53, 54, 55, 56};
   //t=15C, 2.5-12.5
   //double npe[4] = {0.897, 1.334, 2.26183, 2.587};
   //double err_npe[4] = {0.15, 0.15, 0.15, 0.15};
   //t=15C, 2.5-10
   //double npe[4] = {1.549, 2.258, 3.650, 4.167};
   //double err_npe[4] = {0.20, 0.20, 0.20, 0.20};
   //
   double U[4] = {54, 55, 56, 57};
   //t=25C, 2.5-12.5
   //double npe[4] = {1.089, 1.880, 2.200, 2.446};
   //double err_npe[4] = {0.15, 0.15, 0.15, 0.15};
   //t=25C, 2.5-10
   double npe[4] = {1.845, 2.840, 3.572, 3.967};
   double err_npe[4] = {0.20, 0.20, 0.20, 0.20};
   
   /*
   double U[4] = {55, 56, 57, 58};
   //t=45C, 2.5-12.5
   //double npe[4] = {1.092, 1.193, 1.338, 1.685};
   //double err_npe[4] = {0.15, 0.15, 0.15, 0.15};
   //t=45C, 2.5-10
   double npe[4] = {1.698, 1.822, 1.947, 2.396};
   double err_npe[4] = {0.20, 0.20, 0.20, 0.20};
   */
   
   TCanvas *c1 = new TCanvas();
   c1->cd();	
   auto g = new TGraphErrors(4,U,npe,0,err_npe);

   g->SetTitle("; U, V; N_{ph.e.}");

   g->SetMarkerStyle(21);
   //g->SetMarkerColor(4);
   g->Draw();
   //c1->SaveAs("out/U-Nphe_t15_2.5-12.5.png");
   //c1->SaveAs("out/U-Nphe_t15_2.5-10.png");
   //c1->SaveAs("out/U-Nphe_t25_2.5-12.5.png");
   c1->SaveAs("out/U-Nphe_t25_2.5-10.png");
   //c1->SaveAs("out/U-Nphe_t45_2.5-12.5.png");
   //c1->SaveAs("out/U-Nphe_t45_2.5-10.png");
} 
