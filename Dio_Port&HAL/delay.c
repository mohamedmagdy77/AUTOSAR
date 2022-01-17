#include "delay.h"

/* delay for 1ms at 3MHz*/
void Delay_ms(uint16 milli_s){
	uint16 i=0, j=0;
	for(i=0; i<milli_s; i++){
		for(j=0; j<375; j++){}
	}
}
