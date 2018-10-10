
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define alphalen 26; // the length of the English alphabet

// determines how far an input alphabet is from the letter 'A'
// preconditions: input must be upper-case alphabetic character
// postconditions: output = number of rightward shifts to reach input from 'A'
int shift(char input)
{
	int change = input - 'A';
	return change;
}

// preconditions: 
// cipherAlpha must be upper-case
// keyword must be a single alphabetic string
// keyword, message and cipherAlpha must not exceed 100 characters
// postconditions:
// output is an encrypted/decrypted array of characters	(a string)			  
int main()
{
	char keyword[101], message[101], caesar[101], cipher[101], cipherAlpha[101]; 
	char EngAlpha[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // standard english alphabet
	char option[3];
	int i, x = 0; 
	
	printf("For encryption enter A\nFor decryption enter B\n");
	fgets(option, sizeof(option), stdin);

	if (*option == 'A') // encryption
	{ // reading and assigning input data to variables
		printf("Enter Cipher Alphabet\n");
		fgets(cipherAlpha, 101, stdin);
		printf("Enter Message\n");
		fgets (message, 101, stdin);
		printf("Enter Keyword\n");
		fgets (keyword, 101, stdin);
		int keylen = strlen(keyword) - 1;
					
		/* step 1: performs "caesar cipher" on input string */
		// loop runs 'x' times, given that x is length of input message
		while  (i < strlen(message) - 1)  
		{		
			if (isalpha(message[i])) // if the character is an alphabet, it is shifted
			{
				caesar[i] = toupper(message[i]) + shift(toupper(keyword[i%keylen])); // shift
				if (caesar[i] > 'Z') // makes sure that shift loops over the alphabet
				{
					caesar[i] = caesar[i] - alphalen; // e.g. 'Y' + 4 = 'C'
				}
			}
			else // if character is non-alphabetic, it is copied as it is
			{
				caesar[i] = message[i]; 
			}
			i++;		
		}
		caesar[i] = '\0'; // adds null character at the end of string

		/* step 2: encrypts input string according to cipher alphabet */
		// loop runs 'x' times, given that x is length of input message
		while (x < (strlen(caesar))) 
		{
			if (isalpha(caesar[x])) // if character is an alphabet
			{ // alphabet at corresponding index is obtained
				cipher[x] = cipherAlpha[caesar[x] - 'A']; 
				x++;
			}
			else
			{
				cipher[x] = caesar[x]; // if character is non-alphabetic, it is copied as it is
				x++; 
			}
		}
		cipher[x] = '\0'; // adds null character at the end of string
		printf("Encrypted: %s\n", cipher); //resultant string is printed							
	}

	else if (*option == 'B') // decryption
	{ // reading and assigning input data to variables
		printf("Enter Cipher Alphabet\n");
		fgets(cipherAlpha, 101, stdin);
		printf("Enter Message\n");
		fgets(message, 101, stdin);
		printf("Enter Keyword\n");
		fgets (keyword, 101, stdin);
		int keylen = strlen(keyword) - 1;


		/* step 1: finds corresponding english alphabet */
		// loop runs 'x' times, given that x is length of input message
		while (x < (strlen(message))) 
		{
			message[x] = toupper(message[x]); // converts alphabet to uppercase 
			if (isalpha(message[x])) // if character is an alphabet
			{
				// cipher alphabet at corresponding index is obtained by subtracting addresses
				cipher[x] = EngAlpha[strchr(cipherAlpha, message[x]) - cipherAlpha]; 
				x++;
			}
			else // else if character is non-alphabetic, it is copied as it is
			{
				cipher[x] = message[x]; 
				x++; 
			}
		}
		cipher[x] = '\0'; // adds null character at the end of string

		/* step 2: performs inverse of caesar shift to get unencrypted message */
		while  (i < strlen(message) - 1)  
		{		
			if (isalpha(cipher[i])) // if the character is an alphabet, it is shifted
			{
				caesar[i] = toupper(cipher[i]) - shift(toupper(keyword[i%keylen])); // shift left
				if (caesar[i] < 'A') // makes sure that shift loops over the alphabet
				{
					caesar[i] = caesar[i] + alphalen; // e.g. 'B' - 4 = 'X'
				}
			}
			else // if character is non-alphabetic, it is copied as it is
			{
				caesar[i] = cipher[i]; 
			}
		i++;						
		}
		caesar[i] = '\0'; // adds null character at the end of string
		printf("Decrypted: %s\n", caesar);
	}			
return(0); // program ran without error
}
