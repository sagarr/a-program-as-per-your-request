/** the given program found out the word enterd 
* by the user on command line in a given file..
* Prgram outputs the line no on whic it ocuurs..

  Author : Sagar Rohankar
**/

#include <stdio.h>
#include<string.h>

int exactFlag = 0;
int case_sen = 0;

// the following function returns an index of source
// string s1 on which we foinding out substring s2
// I implement it as a case insensitive.

int mystrstri(char s1[],char s2[])
{
	int l1,l2,i,j,k,m;
	l1=strlen(s1);
	l2=strlen(s2);
	if(l1 >= l2)
	{
		for(j=0;j<=(l1-l2);j++)
		{
			m=0;k=j;
			while((tolower(s1[k]) == tolower(s2[m])) && m<l2)
			{
				k++;m++;
			}
			if(m == l2)
				return m;
		}
	}
	return (-1);
}

int exactChkWord(char *base, char *word, int len)
{
	//'base' contains the address of the current line and 'word'
	//contains a pointer to the word to be searched
	//'len' contains the currline 's length

	char currword[100]="",tmp1[2],tmp2,*ptr=NULL;
	int i;

	for(i=0;i<len;i++)
	{
		tmp2=*(base+i);
		//<space> is the delimeter, if the current char is not a space format it using
		//sprintf and concatenate it to currword
		if(tmp2!=' ' )
		{
			sprintf(tmp1,"%c",tmp2);
			strcat(currword,tmp1);
		}
		//Now currword contains a word
		else if(tmp2==' ' )
		{
			if(exactFlag == 1) // check whether the exact word is  tobe searched.. or
			{
				//Check whether it's the word being searched
				if(case_sen ? (!strcmp(currword,word)) : (!stricmp(currword,word)))
				{
					//If it is, return 0, no point proceeding (searches only the first occurence)
					return 0;
				}
				else
				{
				//Current word is not the word searched, so blank out currword and proceed to the
				//next word
				strcpy(currword,"");
				}
			}
			else
			{    //check the given word is substring in given line or not.
				if(!case_sen)
				{
					if(mystrstri(currword,word) != -1)
						 return 0;
					 else
						 strcpy(currword,"");
				}
				else{
				       ptr =(char*) strstr(currword,word);
				       if(ptr != NULL)
						return 0;
				       else
						strcpy(currword,"");
				    }
			}



		}
	}
return -1;//word not found in file !!

}

int main(int argc, char *argv[])
 {
	FILE *fs;
	char tmp1,tmp2,currline[100]="",tmp3[2];
	int lineno=0;
	int flag=0;
	//Check the no.of args. if file name and word to searched are not found
	//Throw an error message and return
	if(argc!=5)
	{
		printf("Usage: WORDSRCH [filename] [word] [case sensitive(0/1)] [exact(0/1)]");
		exit(0);
	}
	//Attempt to open the file
	fs=fopen(argv[1],"r");
	//If accessing/opening fails, throw an error and return
	if(!fs)
	{
		printf("\n Error: Unable to Access/Read the file");
		fclose(fs);
		exit(0);
	}
	exactFlag = atoi(argv[4]); // sets whether exact match is to be found..
	case_sen = atoi(argv[3]); // sets whether search is case sensitive or not..

	printf("\n Searching for \"%s\" in \"%s\" \n",argv[2],argv[1]);
	//Repeat the process until EOF is encountered
	do
	{
	//Get the current char
		tmp1=fgetc(fs);
		//If its not a new line char, format it and append it to currline
		if (tmp1!='\n')
		{
			sprintf(tmp3,"%c",tmp1);
			strcat(currline,tmp3);
		}
		//It's a newline char
		else
		{
			//Increment the line no
			lineno++;
			//Check whether the line contains the word being searched
			//exactchkWord returns 0 if the word is found
			flag=exactChkWord(currline,argv[2],strlen(currline));
			//Word is found. Print to the console, write to the results file
			if(flag==0)
			{
				printf("\n\n Found: \"%s\" ==>> Line No.: \"%d\"",currline,lineno);
			 }
			//Blank out currline, we don't want this anymore
			strcpy(currline,"");
		}
	}while(tmp1!=EOF);
    //Close  the open files fs
	fclose(fs);
return 0;
}





