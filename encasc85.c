/*************************************************************************
Implementation File : encasc85.c
Author - Date       : Efstathios Siatras - 03/12/2016
Purpose             : Encodes Ascii85
**************************************************************************/
#include <stdio.h>

int charprint (int ch, int printbytecounter);										   /* Function to print the encoded output properly */


int main (void) {

	unsigned long int total;
	int ch, n, ch1, ch2, ch3, ch4, ch5, inputcounter, printbytecounter = 0;

	ch = getchar (); 															 /* Get the first character */

	putchar ('<');										  /* Print the delimiter that marks the start of the Ascii85-encoded string */
	putchar ('~');
	putchar ('\n');

	while (ch != EOF) {
		total = 0;										       /* The unsigned integer needed for encoding every four bytes */
		inputcounter = 0; 											      /* Counter of bytes in input every four bytes */

		for (n = 0 ; n < 4 ; n++) {
			if (ch == EOF) { 												/* Check if a 4-tuple is incomplete */
				while (n < 4) {
					total *= 256; 					/* Pad the incomplete 4-tuple with as many zero bytes as the bytes that are missing */
					n++;
				}

				break;
			}

			total = (total * 256) + ch;
			inputcounter++;

			ch = getchar(); 													  /* Get the next character */
		}

		ch5 = total % 85 + '!';									   /* Implemented algorithm to calculate the Ascii85-encoded output */
		total /= 85;

		ch4 = total % 85 + '!';
		total /= 85;

		ch3 = total % 85 + '!';
		total /= 85;

		ch2 = total % 85 + '!';
		total /= 85;

		ch1 = total % 85 + '!';
		total /= 85;

		if ((ch1 == '!' && ch2 == '!') && (ch3 == '!' && ch4 == '!') && ch5 == '!') {						    /* Data Compress '!!!!!' to 'z' */
			putchar ('z');
			printbytecounter++;

			if (printbytecounter == 50) { 				   /* Change line after fifty bytes of printed output in cases of continuous last 'z' chars */
				putchar('\n');
				printbytecounter = 0;
			}
		}

		else {
			switch (inputcounter) { 			/* Print encoded output based on how many zero bytes were used (or not) to pad an incomplete 4-tuple*/
				case 4: 									   /* Four counted bytes of input ; No zero bytes were used */
					printbytecounter = charprint (ch1, printbytecounter);
					printbytecounter = charprint (ch2, printbytecounter);
					printbytecounter = charprint (ch3, printbytecounter);
					printbytecounter = charprint (ch4, printbytecounter);
					printbytecounter = charprint (ch5, printbytecounter);

					break;

				case 3: 									   /* Three counted bytes of input ; One zero byte was used */
					printbytecounter = charprint (ch1, printbytecounter);
					printbytecounter = charprint (ch2, printbytecounter);
					printbytecounter = charprint (ch3, printbytecounter);
					printbytecounter = charprint (ch4, printbytecounter);

					break;

				case 2: 									   /* Two counted bytes of input ; Two zero bytes were used */
					printbytecounter = charprint (ch1, printbytecounter);
					printbytecounter = charprint (ch2, printbytecounter);
					printbytecounter = charprint (ch3, printbytecounter);

					break;

				case 1: 									  /* One counted byte of input ; Three zero bytes were used */
					printbytecounter = charprint (ch1, printbytecounter);
					printbytecounter = charprint (ch2, printbytecounter);

					break;
			}
		}
	}

	putchar ('\n');
	putchar ('~'); 										    /* Print the delimiter that marks the end of the Ascii85-encoded string */
	putchar ('>');
	putchar ('\n');

	return 0;
}


int charprint (int ch, int printbytecounter) {
	putchar(ch);
	printbytecounter++; 							       /* Increase the counter by one each time one byte of encoded output is being printed */

	if (printbytecounter == 50) { 									     /* Change line after fifty bytes of encoded and printed output */
		putchar('\n');
		printbytecounter = 0; 														       /* Reset the counter */
	}

	return printbytecounter; 														      /* Return the counter */
}
