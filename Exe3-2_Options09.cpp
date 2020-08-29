#include "Exe3-2_Options09.h"
#include "Exe3-2_BinModel02.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

double EurOption::PriceByCRR(BinModel Model)
{
   double q = Model.RiskNeutProb();
   int N = GetN();

   //*******************
   //replication strategy

   vector<double> Price1(N + 1);
   double p1, p0;

   for (int i = 0; i <= N; i++)
   {
      Price1[i] = Payoff(Model.S(N, i));
   }
   for (int n = N - 1; n >= 1; n--)
   {
      for (int i = 0; i <= n; i++)
      {
         Price1[i] = (q * Price1[i + 1] + (1 - q) * Price1[i]) / (1 + Model.GetR());
      }
   }
   p1 = Price1[1];
   p0 = Price1[0];

   double x = (p1 - p0) / (Model.S(1, 1) - Model.S(1, 0));
   double y = Price1[0] - x * Model.S(0, 0);
   cout << "x= " << x << endl;
   cout << "y= " << y << endl;

   // ***************************

   vector<double> Price(N + 1);

   for (int i = 0; i <= N; i++)
   {
      Price[i] = Payoff(Model.S(N, i));
   }

   for (int n = N - 1; n >= 0; n--)
   {
      for (int i = 0; i <= n; i++)
      {
         Price[i] = (q * Price[i + 1] + (1 - q) * Price[i]) / (1 + Model.GetR());
      }
   }
   return Price[0];
}

double AmOption::PriceByAmCRR(BinModel Model)
{
   double q = Model.RiskNeutProb();
   int N = GetN();
   double ContVal1;

   //*******************
   //replication strategy

   vector<double> Price1(N + 1);
   double p1, p0;

   for (int i = 0; i <= N; i++)
   {
      Price1[i] = Payoff(Model.S(N, i));
   }
   for (int n = N - 1; n >= 1; n--)
   {
      for (int i = 0; i <= n; i++)
      {
         ContVal1 = (q * Price1[i + 1] + (1 - q) * Price1[i]) / (1 + Model.GetR());
         Price1[i] = Payoff(Model.S(n, i));
         if (ContVal1 > Price1[i])
            Price1[i] = ContVal1;
      }
   }
   p1 = Price1[1];
   p0 = Price1[0];

   double x = (p1 - p0) / (Model.S(1, 1) - Model.S(1, 0));
   double y = Price1[0] - x * Model.S(0, 0);
   cout << "x= " << x << endl;
   cout << "y= " << y << endl;

   //**********************

   vector<double> Price(N + 1);
   double ContVal;
   for (int i = 0; i <= N; i++)
   {
      Price[i] = Payoff(Model.S(N, i));
   }

   for (int n = N - 1; n >= 0; n--)
   {
      for (int i = 0; i <= n; i++)
      {
         ContVal = (q * Price[i + 1] + (1 - q) * Price[i]) / (1 + Model.GetR());
         Price[i] = Payoff(Model.S(n, i));
         if (ContVal > Price[i])
            Price[i] = ContVal;
      }
   }

   return Price[0];
}

double Call::Payoff(double z)
{
   if (z > K)
      return z - K;
   return 0.0;
}

double Put::Payoff(double z)
{
   if (z < K)
      return K - z;
   return 0.0;
}
