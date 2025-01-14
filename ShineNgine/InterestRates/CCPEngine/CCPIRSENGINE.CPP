#include "utils.hpp"
#include "vanillaCCP.hpp"

#include <ql/quantlib.hpp>
#include <iostream>

using namespace std;
using namespace ext;
using namespace QuantLib;

int main()
{
	try
	{
		std::vector<double> tempTenors;
		tempTenors.push_back(0);
		tempTenors.push_back(3); tempTenors.push_back(6); tempTenors.push_back(9);
		tempTenors.push_back(12); tempTenors.push_back(18); tempTenors.push_back(24);
		tempTenors.push_back(36); tempTenors.push_back(48); tempTenors.push_back(60);
		tempTenors.push_back(72); tempTenors.push_back(84); tempTenors.push_back(96);
		tempTenors.push_back(108); tempTenors.push_back(120); tempTenors.push_back(144);
		tempTenors.push_back(180); tempTenors.push_back(240);
		//Date today = Date(14, Oct, 2021);
		std::string IRfilePath = "C:\\IRSData\\20211014_LQ\\YieldCurve_IRS.txt";
		std::string IRVolfilePath = "C:\\IRSData\\20211014_LQ\\NormalSwaption.csv";
		std::string fixingPath = "C:\\Program Files\\Numerix\\Leading Hedge 2.4\\client\\Hanwha\\Database\\Market-Data\\Fixings\\MktFixings.Ir.txt";
		VanillaSwap::Type position = VanillaSwap::Receiver;

		Reader dataReader;
		std::vector<double> krwirsrate= dataReader.readRateCSV(IRfilePath);
		Matrix krwswaptionVol= dataReader.readVolCSV(IRVolfilePath);
		IRSPricer IRSPricer1(Date(14,Oct,2021), IRfilePath, fixingPath, IRVolfilePath);



		IRSPricer IRSPricer2(Date(14, Oct, 2021), IRfilePath, fixingPath, IRVolfilePath);
		Real price2 = IRSPricer1.Calculate(Date(14, Oct, 2021), "210719IRS20Y016300R");
		cout << setprecision(15);
		cout << "price2 " << price2 << endl;
		cout << endl;

		Real price3 = IRSPricer1.Calculate(Date(14, Oct, 2021), "211008IRS10Y019960R");
		cout << setprecision(15);
		cout << "price3 " << price3 << endl;
		cout << endl;

		Real price0 = IRSPricer1.Calculate(Date(14, Oct, 2021), 0.01935, 20, position, 20000000000, 0.0);
		cout << setprecision(15);
		cout << price0 << endl;
		cout << "Test Overloading and trade date " << endl;
		cout << endl;


		/*
		Real price4 = IRSPricer1.Calculate(Date(14, Oct, 2021), Date(8, Oct, 2021),
			0.0193, 20, position, 45000000000.0, 0.0);
		cout << setprecision(15);
		cout << "price3 " << price4 << endl;
		cout << endl;
		*/
		//


		IRSPricer1.GreeksMatrix();
		std::vector<Real> Duration(17, 0);
		std::vector<double> Tenors = IRSPricer1.setTenors();
		for (int i = 0; i < 17; i++)
		{
			Real tempRho = 0;
			for (int j = 0; j < 17; j++)
			{
				cout << setprecision(10);
				cout << IRSPricer1.DurationMatrix[i][j] << " ";
				tempRho += IRSPricer1.DurationMatrix[i][j];
			}
			Duration[i] = tempRho;
			cout << endl;
			cout << "Duration " << Tenors[i + 1] << "Months = " << Duration[i] << endl;
			cout << endl;
		}
		//
		std::vector<Real> greeksExample;
		greeksExample = IRSPricer1.GreeksKeyRate("211008IRS20Y019300R");
		Real totalRho;
		for (int i = 0; i < 18; i++)
		{
			cout << setprecision(15);
			cout << greeksExample[i] << " ";
			std::cout << std::endl;
		}



		pair<std::string, Real> greeksTotalExmaple = IRSPricer1.greeksTotalRho("211008IRS20Y019300R");
		std::cout << greeksTotalExmaple.first << "'s Rho = " << greeksTotalExmaple.second << std::endl;
	

		return 0;
	}
	catch (exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unknown Error ! " << std::endl;
		return 1;
	}
}