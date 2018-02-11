/*************************************************************************
Implementation File : decasc85.c
Author - Date       : Efstathios Siatras - 05/12/2016
Purpose             : Decodes Ascii85
**************************************************************************/
#include <stdio.h>

int main (void) {

	unsigned long int total, cachetotal;
	int ch, n, ch1, ch2, ch3, ch4, inputcounter;

	ch = getchar ();  													   		   /* Get the first character */
	while (ch == ' ' || ch == '\t' || ch == '\n') 									      		      /* Ignore whitespace characters */
		ch = getchar();

	if (ch != '<') {							  		 /* Identify the delimiter that marks the start of the Ascii85-encoded string */
		fprintf(stderr, "Bad Start\n");

		return 1;
	}

	ch = getchar();
	if (ch != '~') {
		fprintf(stderr, "Bad Start\n");

		return 1;
	}

	ch = getchar(); 												       /* Get the first character after the delimiter */

	while (ch != EOF) {
		total = 0; 									  		 /* The unsigned integer needed for decoding every five bytes */
		cachetotal = 0;
		inputcounter = 0; 											        /* Counter of bytes in input every five bytes */

		for (n = 0 ; n < 5 ; n++) {

			if (ch == ' ' || ch == '\t' || ch == '\n') { 							       		      /* Ignore whitespace characters */
				ch = getchar();
				n--;

				continue;
			}

			else if (ch == 'z') { 					              					            /* Handle 'z' characters properly */
				if (ch == 'z' && n != 0) {		        /* Character 'z' must not be part of another 5-tuple, cause it represents the 5-tuple '!!!!!' */
					fprintf(stderr, "Bad input character\n");

					return 3;
				}

				total = 0;
				inputcounter += 5;

				ch = getchar(); 										    		    /* Get the next character */

				break;
			}

			else if (ch == EOF) {										 /* Check if input has ended without an end delimeter */
				fprintf(stderr, "Bad end\n");

				return 2;
			}

			else if (ch == '~') { 					   		   /* Identify the delimiter that marks the end of the Ascii85-encoded string */
				ch = getchar();

				if (ch == '>') {
					ch = getchar();
					while (ch == ' ' || ch == '\t' || ch == '\n') 					       		      /* Ignore whitespace characters */
						ch = getchar();

					if (ch != EOF) {     		    /* There must be no more input after the end delimeter, except from whitespace characters and EOF */
						fprintf(stderr, "Unnecessary input\n");

						return 4;
					}

					while (n < 5) { 										  /* Check if a 5-tuple is incomplete */
						if (total == 0)								    	   /* There is no other 5-tuple to be decoded */
							return 0;

						cachetotal = total; 										/* Cache the unsigned integer */
						total = (total * 85) + 'u' - '!';     /* Pad the incomplete 5-tuple with as many 'u' characters as the bytes that are missing */

						if (cachetotal != total/85) { 					    /* Find possible undefined behaviour, because of overflow */
							fprintf(stderr, "Overflow sequence\n");

							return 5;
						}

						n++;
					}

					break;
				}

				else { 						      /* '~' is generally a bad character and it's only allowed to be used in both delimiters */
					fprintf(stderr, "Bad input character\n");

					return 3;
				}
			}

			if ( (ch < '!' || ch > 'u') && (ch != '~' && ch != 'z') && (ch != EOF) ) { 						 /* Find bad input characters */
				fprintf(stderr, "Bad input character\n");  	  	     /* '~', 'z' and EOF are exceptions, because they will be (or have been) examined */

				return 3;
			}

			cachetotal = total; 													/* Cache the unsigned integer */
			total = (total * 85) + ch - '!';
			inputcounter++;

			if (cachetotal != ((total - ch + '!') / 85)) { 						    /* Find possible undefined behaviour, because of overflow */
				fprintf(stderr, "Overflow sequence\n");

				return 5;
			}

			ch = getchar();														    /* Get the next character */
		}

		ch4 = total % 256;									     /* Implemented algorithm to calculate the Ascii85-decoded output */
		total /= 256;

		ch3 = total % 256;
		total /= 256;

		ch2 = total % 256;
		total /= 256;

		ch1 = total % 256;
		total /= 256;

		switch (inputcounter) { 			    /* Print decoded output based on how many 'u' characters were used (or not) to pad the incomplete 5-tuple */
				case 5: 									 /* Five counted bytes of input ; No 'u' characters were used */
					putchar(ch1);
					putchar(ch2);
					putchar(ch3);
					putchar(ch4);

					break;

				case 4:										  /* Four counted bytes of input ; One 'u' character was used */
					putchar(ch1);
					putchar(ch2);
					putchar(ch3);

					break;

				case 3: 								       /* Three counted bytes of input ; Two 'u' characters were used */
					putchar(ch1);
					putchar(ch2);

					break;

				case 2: 									   /* Two counted bytes of input ; One 'u' character was used */
					putchar(ch1);

					break;

				case 1: 										 	     /* One counted byte of input ; Bad input */
					fprintf(stderr, "Bad Input\n");

					return 6;
			}
	}

	return 0;
}
