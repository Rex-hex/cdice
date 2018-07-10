void Rso(char* istr,bool Nl = true)
{
        //Rso: read string out, reads out a c like string to the terminal
        int i = 0;
        while (istr[i] != '\x00')
        {

                std::cout << istr[i];
                i++;
        }
        if (Nl == true) {std::cout << std::endl;}

}

int FindIndex(char *argv, char F,int Max=99999)
{       /*
	returns the position of a charicter in a c string,
        if the charicter is absent and will iterate for max until assuming that their is no null byte in the string
        BEWARE RETURNS -1 IF THE CHARICTER IS NOT PRESENT
	*/

        int i = 0;
        while (i < Max && argv[i] != F)
        {
                i++;
                if (argv[i] == '\x00') {return -1;}
        }
        return i;
}

int StrLen(char *istring,int MaxLength = 99999)
{
        //returns the string length, or -1 in the event that istring is greater than max length or lacking 0x00
	int i = 0;
        while (istring[i] != '\x00')
        {
		if (i > MaxLength) {return -1;}
                i++;
        }
        return i;
}


int SubStr(char* Istring,char* Ostring,int StartIndex,int EndIndex,int MaxLength = 9999)
{       //NOTE WHEN USING THIS FUNCTION MAKE ROOM FOR THE NULL BYTE IN THE OUTPUT ARRAY!!!!!

        /*
		Generates a substring between two indexes
        	and stores it in Ostring
        	returns -1 on error, 0 on success
	*/

        if (EndIndex < StartIndex)
        {       //returns an error if the start index is gretor than the end index
                return -1;
        }
        if (EndIndex == StartIndex) 
        {       //for if the indexes are the same
                Ostring[0] = Istring[StartIndex];
                Ostring[1] = '\x00';
                return 1;
        }

        //loops through each character of the array and returns an error if it exedes the given max length
        //or if it finds the null charicter of the main array
        for(int i = StartIndex; i <= EndIndex; i++)
        {
                if (i >= MaxLength ) {return -1;}
                if (Istring[i] == '\x00') {return -1;}
                Ostring[i - StartIndex] = Istring[i];
        }
        //append the null charicter to the output array
        Ostring[EndIndex] = '\x00';

        return 0;

}

