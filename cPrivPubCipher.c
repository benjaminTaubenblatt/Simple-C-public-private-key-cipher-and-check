#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Benjamin Taubenblatt 
09/26/2016
*/

int GCD(int n1,int n2){ //this method determines if the GCD(pub,mod)=1, returns 0 if gcd = 1
	int i = 1;
	int gcd = 0;
	for(i = 1; i <= n1 && i <=n2; ++i){ 
		if(n1%i==0 && n2%i==0){ //check's if i is a factor of both integers
			gcd = i;
			break;
		}
	}
	
	if(gcd == 1){
		return(0); //then we can use the 2 numbers to encrypt
	}
	else{
		return(1); //gcd != 1
	}
}
 
//This method tests the gcd(pub,mod)=1 and gcd(priv,mod)=1, that pub and q are inverses, and that the equation works out
int testRun(int p,int q,int u){ 
	int g = GCD(p,u); //0 if gcd(pub, mod) = 1
	int h = GCD(q,u); 
	if((g == 0)&&(h == 0)){
		int invCheck = (p*q)%u; //will be 1 if p and q are inverses  
		int RHS = (p*2)%u; //checking cipher
	 	int LHS = (RHS*q)%u;
		if((2 == LHS)&&(invCheck == 1)){ //VALID KEYS
			return(0);
		} 
		else{
			return(1);
		}
	}
	else{
		return(1); 
	}
}

int checkMe(int pub,int priv,int mod){ 
	int c = testRun(pub, priv, mod);//0 if VALID KEYS 

	if(c != 0){ 
		return(1); 
	}
	else{
		return(0); //everything checks out
	}
}

int encrypt(int M, int W, int U){ //encrypt M is message W is key, U is mod
	int ciph = (W*M)%U;
	return(ciph); 
} 

int main(int argc, char *argv[]){
	char *flag = argv[1];
	char *check = "-CHECK"; //setting up our flag checking system 
	char *cipher = "-CIPHER";
	int checkResult = strcmp(flag,check); //0 if they are equal 
	int cipherResult = strcmp(flag,cipher); 

	if(checkResult == 0){ //Then the flag was -CHECK
	
		if(argv[2] == NULL||argv[3] == NULL || argv[4] == NULL){ //checking if no input at all
			printf("\nINVALID KEYS\n\n"); 
			exit(1); //exit failure
		}
		int publicKey = atoi(argv[2]); //getting user input and converting(when appropriate to int
		int privateKey = atoi(argv[3]); 
		int modulo = atoi(argv[4]);	
	
		int result = checkMe(publicKey, privateKey, modulo); //1 if INVALID 0 if VALID
		if(result == 1){
			printf("\nINVALID KEYS\n\n");
			exit(1);
		} 
		else if(result == 0){
			printf("\nVALID KEYS\n\n");
			exit(1); 
		}
	}

	if(cipherResult == 0){ //Then the flag was -CIPHER
		if(argv[2] == NULL||argv[3] == NULL){ //check user input
			printf("\nINVALID INPUT\n\n");
			exit(1);
		}
		//opens our file for reading
		FILE *input;
		input = fopen(argv[2],"r");
		int aKey = atoi(argv[3]);
		
		//getting the size of the file and making an array of that size. 
		fseek(input, 0L, SEEK_END); //places cursor at end
		int sz = ftell(input);
		fseek(input, 0L, SEEK_SET); //seek back to front of file
		char array[sz]; //array of correct size
  			
		//makes sure file is able to open
		if(input == NULL){
			fprintf(stderr, "\nCan't open input file \n\n");
			exit(1); 
		}
		
	
		int c;
		int k = 0;
		int result;
				 
		while((c = fgetc(input)) != EOF){ //while there is stuff to read
			result = encrypt(aKey,c,256); //encrypts character  
			array[k] = result; //creating our encrypted message
			k++;  
				
		}
			
		FILE *fp;
		char *fileName = argv[2]; //retrieving file name
		char *cat = ".CIPHER"; //making our file extension
		char *finally = strcat(fileName,cat); //concatenating strings to make our new file name
		fp = fopen(finally,"w"); //opens our file to write to

		fprintf(fp,"%s",array); //write to file fp

		fclose(fp);  
		fclose(input); //close file

	}
	else if(checkResult != 0 && cipherResult != 0){ //then incorrect input 
		printf("Please enter an appropriate option, %s is not valid input\n",flag);
		exit(1); 
	}
	
	return(0); 
}
