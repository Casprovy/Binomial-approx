#include "Exe3-2_BinModel02.h"
#include "Exe3-2_BSModel.h"
#include "Exe3-2_Options09.h"
#include <iostream>
using namespace std;

int main()
{
   double S0 = 100.0;
   double r = 0.05;
   double sigma = 0.2;
   double T = 1.0;
   double K = 100.0;
   int N = 500;
   cout << "S0 =    " << S0 << endl;
   cout << "r  =    " << r << endl;
   cout << "sigma = " << sigma << endl;
   cout << "T =     " << T << endl;
   cout << "K =     " << K << endl;
   cout << "N =     " << N << endl;
   cout << endl;

   BSModel Model(S0, r, sigma);
   double h = T / N;
   BinModel ApproxModel = Model.ApproxBinModel(h);

   Put Option(N, K);
   cout << "American put option price = " << Option.PriceByAmCRR(ApproxModel) << endl
        << endl;
   cout << "Euro put option price= " << Option.PriceByCRR(ApproxModel) << endl
        << endl;

   Call Option2(N, K);
   cout << "Euro and Amer call option price= " << Option2.PriceByCRR(ApproxModel) << endl;

   return 0;
}
