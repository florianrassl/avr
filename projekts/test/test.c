#include "../../lib/UART/uart.h"

int main(){
	uart0Init();

	while(1){
		uart0PutString("hallo welt \n\r");
	}
	return 0;
}
