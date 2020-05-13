#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_fft_complex.h>

#define REAL(z,i) ((z)[2*(i)])							//funkcijas lai ierakstit datus alternejosa seciba
#define IMAG(z,i) ((z)[2*(i)+1])

int main()
{
  
   double float1=0.0;

	 FILE* stream2 = fopen("lor.txt", "r");				//Lasa lorentca profilu ar troksni 
	 FILE* stream3 = fopen("out2.txt", "w");			//ieraksta jaunus datus sheit
	{
		 int i; double data[2*128];

		for (i = 0; i < 128; i++)
		{
			fscanf(stream2, "%lg", &float1);			//dati ir envely-spaced
			REAL(data, i) = float1; IMAG(data, i) = 0.0;//ieraksta masiva alternejosi realas un imaginaras dalas
		}
		fclose(stream2);
		gsl_fft_complex_radix2_forward(data, 1, 128);	//Fourier transform
		int m;
		for (m = 0; m < 128; m++)
		{
			printf("%f\n", REAL(data, m));				//Nolasa parveidotus datus un ieraksta faila
			fprintf(stream3,"%f\n", REAL(data, m) * 1 / (sqrt(128)));
		}												//output ir normalizets lai but samerojams ar inputu
		fclose(stream3);
		return 0;
	}

}

