/*
 * ArithmaticVal.cpp
 *
 *  Created on: Sep 21, 2018
 *      Author: Besho
 */


#include <iostream>
#include <assert.h>
#include <string>

using std::string;
using std::cin;
using std::cout;

//#define DEBUGMODE

#define ARITHMATICOPERATIONNUMS 15
#define MIN_INT64_T 			-9000000000000000000
#define MAX_INT64_T				 9000000000000000000

typedef struct
{
	int64_t MinVal;
	int64_t MaxVal;
}MinAndMax;

MinAndMax MapConstruction[ARITHMATICOPERATIONNUMS][ARITHMATICOPERATIONNUMS];
int64_t Numbers [ARITHMATICOPERATIONNUMS];
char Operations [ARITHMATICOPERATIONNUMS - 1];

/*!
 * Evaluation of arithmetic operation consists of two input values and operation
 */
int64_t Eval(int64_t a, int64_t b, char op)
{
	int64_t Temp;
	if (op == '*')
	{
		Temp = a * b;
	}
	else if (op == '+')
	{
		Temp = a + b;
	}
	else if (op == '-')
	{
		Temp = a - b;
	}
	else
	{
		assert(0);
	}

	return Temp;
}

/*!
 * Get Max value of three numbers A,B,C
 */
int64_t Maximum (int64_t A , int64_t B , int64_t C)
{
	if ( A >= B && A >= C)
		return A;
	else if ( B >= A && B >= C)
		return B;
	else
		return C;
}

/*!
 * Get Min value of three numbers A,B,C
 */
int64_t Minimum (int64_t A , int64_t B , int64_t C)
{
	if ( A <= B && A <= C)
		return A;
	else if ( B <= A && B <= C)
		return B;
	else
		return C;
}

/*!
 * return the Min and Max values between two sub operations based on the previous values on the map.
 */
MinAndMax MinAndMaxVal(uint64_t StartAdd, uint64_t EndAdd)
{
	MinAndMax ReturnedVal = {MAX_INT64_T , MIN_INT64_T};
	int64_t TempA, TempB, TempC, TempD;

	for (uint64_t MidAdd = StartAdd; MidAdd < EndAdd ; MidAdd++)
	{
		TempA = Eval(MapConstruction[StartAdd][MidAdd].MaxVal ,
				MapConstruction[MidAdd + 1][EndAdd].MaxVal , Operations [MidAdd]);

		TempB = Eval(MapConstruction[StartAdd][MidAdd].MaxVal ,
						MapConstruction[MidAdd + 1][EndAdd].MinVal , Operations [MidAdd]);

		TempC = Eval(MapConstruction[StartAdd][MidAdd].MinVal ,
						MapConstruction[MidAdd + 1][EndAdd].MaxVal , Operations [MidAdd]);

		TempD = Eval(MapConstruction[StartAdd][MidAdd].MinVal ,
						MapConstruction[MidAdd + 1][EndAdd].MinVal , Operations [MidAdd]);


		ReturnedVal.MaxVal = Maximum( ReturnedVal.MaxVal , TempA
													, Maximum( TempB , TempC , TempD));

		ReturnedVal.MinVal = Minimum( ReturnedVal.MinVal , TempA
															, Minimum( TempB , TempC , TempD));
	}

	return ReturnedVal;
}

int64_t GetMaximumValue(uint64_t NumLen)
{
	uint64_t EndAdd;
	/*! initializing the diagonal values of MapConstruction */
	for (uint64_t i =0 ; i < NumLen ; i++)
		MapConstruction[i][i] = {Numbers[i] , Numbers[i]};

	/*! constructing the whole map*/
	for(uint64_t Diff = 1 ; Diff < NumLen ; Diff++ )
		for(uint64_t StartAdd = 0 ; StartAdd < NumLen - Diff ; StartAdd++)
		{
			EndAdd = StartAdd + Diff;
			MapConstruction[StartAdd][EndAdd] = MinAndMaxVal(StartAdd , EndAdd );
		}

#ifdef DEBUGMODE
	for(uint64_t i =0 ; i < NumLen ; i++)
	{
		for(uint64_t j =0 ; j < NumLen ; j++)
		{
			cout << MapConstruction[i][j].MaxVal << "\t";
		}
		cout << "\n";
	}

	for(uint64_t i =0 ; i < NumLen ; i++)
	{
		for(uint64_t j =0 ; j < NumLen ; j++)
		{
			cout << MapConstruction[i][j].MinVal << "\t";
		}
		cout << "\n";
	}

#endif

	return MapConstruction[0][NumLen - 1].MaxVal;
}

int main()
{
	string Exp = "5-8+7*4-8+9";
	//cin >> Exp;

	Numbers[0] = (uint64_t)Exp[0] - 48 ;
	for( uint64_t i = 1; i < (uint64_t)Exp.size() ; i = i+2)
	{
		Operations[i/2] = Exp[i] ;
		Numbers[(i/2)+1] = (uint64_t)Exp[i+1] - 48;
	}

#ifdef DEBUGMODE
	for ( uint64_t i = 0; i < ( Exp.size() + 1 ) / 2 ;  i++)
		cout << i << " " << Numbers[i] << " ";
	cout << "\n";

	for ( uint64_t i = 0; i < ( Exp.size() - 1 ) / 2 ;  i++)
		cout << i << " " <<Operations[i] << " ";
	cout << "\n";
#endif

	cout << GetMaximumValue( ( Exp.size() + 1 ) / 2 ) << '\n';

	return 0;
}


