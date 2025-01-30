#include "lib/includes.h"

#define TRIALS 1e4

#define MEAN 0
#define VARI 1
#define SIG sqrt(VARI)

int main(void){
	int count_sig=0, count_2sig=0;
	for(int i=0; i<TRIALS; i++){
		double* temp = box_muller_gaussian(MEAN, VARI);
		for(int j=0; j<2; j++){
			if( temp[j] > MEAN-(SIG*2) && temp[j] < MEAN+(SIG*2) ){
				count_2sig++;
				if( temp[j] > MEAN-SIG && temp[j] > MEAN+SIG ){
					count_sig++;
				}
			}
		}
	}
	
	printf("rate between mean-sig*2 and mean+sig*2 : %lf\n", count_2sig / TRIALS);
	printf("rate between mean-sig and mean+sig     : %lf\n", count_sig / TRIALS);

	return 0;
}
