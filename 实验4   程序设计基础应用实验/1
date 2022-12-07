/*1、掷骰子游戏
编写程序模拟掷骰子游戏。已知掷骰子游戏的游戏规则为：每个骰子有6面，这些面包含1、2、3、4、5、6个点，
投两枚骰子之后，计算点数之和。如果第一次投的点数和为7或11，则游戏者获胜；
如果第一次投的点数和为2、3或12，则游戏者输；如果第一次投的点数和为4、5、6、8、9或10，
则将这个和作为游戏者获胜需要掷出的点数，继续投骰子，直到赚到该点数时算是游戏者获胜。
如果投掷7次仍未赚到该点数，则游戏者输。
*/
#include <iostream>
#include <time.h>
using namespace std;


int main()
{
	int diceResult[3],i;
	cout << "Dice Game" << "\n------------------------\n" << "Rules:\n每个骰子有6面，这些面包含1、2、3、4、5、6个点，投两枚骰子之后，计算点数之和。\n如果第一次投的点数和为7或11，则游戏者获胜；如果第一次投的点数和为2、3或12，则游戏者输；\n如果第一次投的点数和为4、5、6、8、9或10，则将这个和作为游戏者获胜需要掷出的点数，继续投骰子，直到赚到该点数时算是游戏者获胜。\n如果投掷7次仍未赚到该点数，则游戏者输。\n------------------------\n";
	for (i = 7; i >= 1;)
	{
		diceResult[0] = diceResult[1] + diceResult[2];
		srand(time(0)+i);
		diceResult[1] = rand() % 6 + 1;
		srand(time(0)+2*i);
		diceResult[2] = rand() % 6 + 1;
		cout << i<<" chance left\n[" << diceResult[1] << "] + [" << diceResult[2] << "] = " << diceResult[1] + diceResult[2]<<endl;
		i--;
		switch (i)
		{case 6:
			switch (diceResult[1] + diceResult[2])
			{
			case 2:
			case 3:
			case 12:
				i = 0;
				break;
			case 7:
			case 11:
				i = -1;
				break;
			}
		default:
			if ( diceResult[0] == (diceResult[2] + diceResult[1]) )
				i = -1;
			break;
		}
	}
	i ? cout << "You Won!": cout << "You Loose.";
}
