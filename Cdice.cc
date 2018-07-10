#include <iostream>
#include "Rng.h"
#include "CharPtr.h"
#include "MathParser.h"

/*
The global dice that the program uses, declared globaly so that it incriments globaly
and thus every time its functions are called within the program it will be a different random sequence
as aposed to the computer outrunning the system timer used for the starting seed of the dice
*/
Rng dice;

int Roll(int RollNumb,int DieType)
{
	/*
	Roll given the number of times to roll, and the die type
	requires a global Rng object called dice declared
	*/

	int retVal = 0;
        while (RollNumb > 0)
        {
		retVal += (int)dice.Range(1,DieType);
           	RollNumb--;
    	}
      	return retVal;
}

int Parse(int argc, char *argv[],int arg,char * operands = Operands,int(**use)(int,int) = Use,bool fromMain=false)
{
	/*
		this is the recursive function that allows us to use the for loop operators inside of the program
	*/

	//this is the last argument that the recursive chain parsed, to be returned to the original caller of the Parse function
	//for further parsing
	static int lastarg;
	if (argv[arg][0] == '-')
	{
		//the argument given to us is a for loop instruction

//the bellow effectivly sets up variables for a for loop to be run based on certain conditions
		int Dindex = FindIndex(argv[arg],'D');
		float ForNum;
		char Delimit;
		if (Dindex != -1)
		{
			//the delimiter is specified
			ForNum = ParseMath(argv[arg],1,Dindex - 1,operands,use);
			Delimit = argv[arg][Dindex + 1];
			if (Delimit == '\x00'){Delimit = '\n';}

		}
		else
		{
			//the delimiter is not specified
			ForNum = ParseMath(argv[arg],1,StrLen(argv[arg]) - 1,operands,use);
			Delimit = ' ';
		}
//the above sets up arguments for a for loop to use based on the inputed information
		for(int i = ForNum; i > 0; i--)
		{
			//run whatever operation is specified next ForNum number of times
			Parse(argc,argv,arg + 1,operands,use);
			std::cout << Delimit;
		}
	}
	else if (fromMain == true)
	{
		/*
	this is here so the program will cout when called from main 
	(as it is normaly the caller function in the recursive "chain" that writes stuff to the screen)
		*/

		//set the return value for the main function to use
		lastarg = arg;
		std::cout << ParseMath(argv[arg],0,StrLen(argv[arg]) - 1,operands,use);
	}
	else
	{
		//this is the exit point of the recursive "chain"
		//it is the point where we actualy "role" the dice
		lastarg = arg;
		std::cout << ParseMath(argv[arg],0,StrLen(argv[arg]) - 1,operands,use);
	}
	return lastarg;
}

int main(int argc, char *argv[])
{
	/*
		the main function where the recursive rolling functions are called
		to do in the future: make a "shell mode" and allow for reursive rolling of parenthisised dice (-6 [3d6 1d4])
	*/

	if (argc == 1)
	{
		//roll 1d6 if called with no arguments
		std::cout << Roll(1,6) << std::endl;
		return 1;
	}
	//set up the custom math operands to be used in parsing, using d for rolling
	char Operands[6] = {'+','-','*','/','d','\x00'};
	int (*Using[5])(int,int)  = {&add,&sub,&mul,&divi,&Roll};

	//using the return value from parse loop over the arguments and run the program for all -loop# rollval combinations
	int args_parsed = Parse(argc,argv,1,Operands,Using,true);
	while(args_parsed < argc - 1)
	{
		args_parsed = Parse(argc,argv,args_parsed + 1,Operands,Using,true);
	}

	//cout an endline to make it purty and return
	std::cout << std::endl;
	return 1;
}
