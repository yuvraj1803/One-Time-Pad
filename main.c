#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
/* Note Section:

1. if the password is not the same length of the string, then a modified version of the password is generated, which is then used to 
 encrypt the file. This new password is then reported to the user.
2. The file must be executed in the form ./main string password

3. Integer mask is the mask of the given string mapped to their alphabetical indices. For example, A->0 and B->1 etc..

*/



char * PC(char *, char *); // password changing function
int * F(int*, char*); // encrypting/decrypting function
int largest_factor(int, int); // this function gives the largest factor of a number which is in-turn used in password changing function
int * makeMask(char *); // makes the integer mask
void printMask(int *, int); // prints the string from integer mask
int max(int,int); // returns the maximum of the two inputs


signed main(){



	char * data = (char*)malloc(1000*sizeof(char)); // data to be encrypted/decrypted
	char * pass = (char*)malloc(1000*sizeof(char)); // password
	printf("Enter Data to be Encrypted/Decrypted: ");
	gets(data);
	printf("Enter Password: ");
	gets(pass);

	int data_size = strlen(data); // length of data
	int pass_size = strlen(pass); // length of password
	int CHANGE_OF_PASS = data_size != pass_size; // if the length of the password is not the same as the length of data, CHANGE_OF_PASS is true otherwise its false
	pass = (CHANGE_OF_PASS ? PC(data, pass) : pass); // iff CHANGE_OF_PASS is true, function PC is called.
	int *maskedData = makeMask(data);

	int * cipher = F(maskedData, pass); // cipher is the string mask which holds the cipher message
	printMask(cipher, strlen(data));
	return 0;
}

int * makeMask(char * data){ // makes the integer mask for a given string
	
	int dataSize = strlen(data);
	int *Mask = (int*) malloc(sizeof(int)*dataSize);
	for(int i=0;i<dataSize; i++){
		*(Mask + i) = *(data + i) - 'A';
	}

	return Mask;

}

void printMask(int * Mask, int maskSize){ // for a given integer mask, prints the string
	for(int i=0;i<maskSize;i++){
		printf("%c", *(Mask + i) + 'A');
	}
	printf("\n");
}

char * PC(char * data, char * pass){ // modifies the password such that it is of the length of the given string



	int data_size = strlen(data);
	int pass_size = strlen(pass);
	char* dummy_ret_val; // dummy return value as the function doesnt return in all control paths
	if(pass_size < data_size){ // when the length of the password is less than length of data
		int lf = largest_factor(data_size, pass_size); // largest_factor(x,y) returns the largest factor of x <= y;
		char * new_pass = (char*)malloc(lf*sizeof(char)); // new password that has to be generated which has the length of the largest factor
		for(int i=0;i<lf;i++){

			*(new_pass + i) = *(pass + i);
		}
		int times = data_size/lf; // number of times the new passwords needs the be put end to end to generate the final password
		char *final_pass = (char*) malloc(lf*times*sizeof(char)); // final password that will be returned 
		for(int i=0;i<times;i++) final_pass = strcat(final_pass, new_pass); // joining the password end to end.
		return final_pass;

	}else if(pass_size > data_size){ // when the length of the password is greater than the length of the data
		char * new_pass = (char*)malloc(data_size * sizeof(char));
		for(int i=0;i<data_size;i++) *(new_pass + i) = *(pass + i); //  taking the first x letters of the passwordw where x is the length of the data.

		return new_pass;
	}

	return dummy_ret_val;// we have defined a dummy_ret_val because we dont have anything to return in this scope.
}

int largest_factor(int x, int y){ // returns the largest factor of length of data less than the size of the password.
	int lf = 1;
	int s = (int)sqrt(x);
	for(int i=1;i<=s;i++){

		if(x%i == 0){

			int f1 = x/i;
			int f2 = i;

			if(f1 > y && f2 > y){
				return lf;
			}else if(f1 > y) lf = f2;
			 else if(f2 > y) lf = f1;
			 else{

			 	lf = max(f1,f2);
			 }
		}
	}

	return lf;


}

int max(int x, int y){ // return the maximum of two input numbers
	if(x > y) return x;
	return y;

}

int * F(int * data, char  *pass){ // encrypting/decrypting function.

	
	int passSize = strlen(pass); // length of the password
	int dataSize = sizeof(data)/sizeof(data[0]); // length of the data

	int *cipherInt = (int*) malloc(sizeof(int) * dataSize); // integer mask created to store the data 
	int i = 0;
	while(i<passSize){
		int intPass = *(pass + i%passSize) - 'A'; // integer value of the char
		int intData = *(data + i); 
		int encryptedInt = intData ^ intPass; //   encrypted data
		cipherInt[i] = encryptedInt;
		i++;
	
	}


	return cipherInt;
	
}
