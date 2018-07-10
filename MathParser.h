//the global char pointer required for the default ParseMath function, these are the delimiters that will be used
char Operands[5] = {'+','-','*','/','\x00'};

//the basic global functions required by the ParseMath function
int add(int A, int B) {return A + B;}
int sub(int A, int B) {return A - B;}
int mul(int A, int B) {return A * B;}
int divi(int A, int B) {return A / B;}

//the global Use pointer that is used to locate each of the functions to be passed to the program defining the operands use
int (*Use[4])(int,int)  = {&add,&sub,&mul,&divi};

//default definitions for what the program uses as parenthasis
char Parenth[2] = {'[',']'};

int char2int (char c)
{
	/*
		this function is at the heart of the string to int function,
		the reason why this could be desireable to regular stoi is the fact
		that it doesnt error on non number charicters, instead assuming them to be zero

		in the future I would like to also make it parse negetive numbers, but for now stoi is
		probly superior for most other tasks
	*/

	switch(c) 
	{
	case '1':
		return 1.00;
	case '2':
		return 2.00;
	case '3':
		return 3.00;
	case '4':
		return 4.00;
	case '5':
		return 5.00;
	case '6':
		return 6.00;
	case '7':
		return 7.00;
	case '8':
		return 8.00;
	case '9':
		return 9.00;

	default:
		return 0.00;
	}
}
int pow(int A,int B)
{
	/*
		takes A^B
	*/
	int Ret = 1;
	if (B == 0) {return Ret;}
	while (B != 0)
	{
		Ret *= A;
		B--;
	}
	return Ret;
}

int better_stoi(char * str,int start,int end)
{
	/*
		translates a string into a base 10 intager
	*/

	int Ret = 0;
	int Power = 0;
	for (int i = end; i>=start; i--)
	{
		Ret += pow(10,Power) * char2int(str[i]);
		Power += 1;
	}
	return Ret;
}
bool InParenthasis(char* str,int start,int end,char* parenth = Parenth)
{
	//returns true if the given string is completly insise of parenthasis

	int Parenthasis = 0;
	for (int i = start; i <= end; i++)
	{
		if(str[i] == Parenth[0]) {Parenthasis += 1;}
		if (Parenthasis == 0) {return false;}
		else if(str[i] == Parenth[1]) {Parenthasis -= 1;}
	}
	if(Parenthasis == 0)
	{
		return true;
	}
	else {return false;}
}

void StripOuter(char* equation,int *start,int * end,char* parenth = Parenth)
{
	/*
		a simple function that makes sure that the inputed math to be parsed is not encapsilated with pointless
		parenthasys
	*/
	while(InParenthasis(equation,start[0],end[0],parenth))
	{
		start[0] += 1;
		end[0] -= 1;
	}
}

int ParseMath(char* equation,int start,int end,char * operands = Operands, int(**use)(int,int) = Use,char* parenth = Parenth)
{
	/*
		this is a recursive function that parses string math operations into intagers
		it can be thought of as a "simplification machine" for operations that return single intagers
	*/
	int Parenthasis = 0;

	//make sure we are not given a string completly in parenthasis
	StripOuter(equation,&start,&end,parenth);

	for (int i = 0; operands[i] != '\x00';i++)
	{
		//scan the given string range for any of our defined operands

		for(int i2=start;i2<=end;i2++)
		{
			//increment the parenthasis if we find an open parenth [
			if (equation[i2] == Parenth[0]){Parenthasis += 1;}

			//if we find an operand that is not in parenthasis then prepare to perform the specified
			//operation on the two halfs of the given string
			if (equation[i2] == operands[i] && Parenthasis == 0)
			{
				int A,B;
				A = ParseMath(equation,start,(i2 - 1),operands,use,parenth);
				B = ParseMath(equation,i2+1,end,operands,use,parenth);

				//return the specified operation on the resault of the parsed data
				return use[i](A,B);
			}

			//close the parenthasis if we find a closing parenthasis ]
			if (equation[i2] == Parenth[1]) {Parenthasis -= 1;}
		}
	}

	//there are no operands inside of the string to be parsed so it has to be a constant
	return better_stoi(equation,start,end);
}

