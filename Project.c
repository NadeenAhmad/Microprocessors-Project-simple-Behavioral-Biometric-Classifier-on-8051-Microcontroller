#include <REG52.H>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//unsigned char xdata serial_input_buffer [] =
//"This is a test to see if this data gets "
//"injected into the serial port.\r\n"
//"Have fun.\r\n"
//"\r\n\r\n";
unsigned char i=0;
unsigned char j;
unsigned char l ;
unsigned char q;
unsigned char r;
unsigned char count =0;
//unsigned char key[11] = {'1','2','3','4','5','6','7','8','9','0','\0'};
unsigned char key[11] = {'.','t','i','e','5','R','o','n','a','l','\0'};
unsigned char flag = 0;
unsigned char T0_ISR_count = 0;
unsigned char timekey[10];
unsigned char differenceA[9];
unsigned char differenceB[9];
unsigned char differenceT[9];
unsigned char w =0 ;
unsigned char t = 0;
unsigned char Da=0;
unsigned char Db = 0;
unsigned char empty = ' '; 
//A timer function that we use to calculate time between each keystroke 
void T0_ISR(void) interrupt 1 {
T0_ISR_count++;
//TF0 = 0; // Reset the interrupt request
TH0 = 0x63;//rechek these numbers
TL0 = 0xC0;
}
//LED Delay 
//A function that induces delay between the values given 
// to the output ports to simulate the behavior of LEDs
void delay(){
int tt;
for(tt=0;tt<32000;tt++);
}
void main (void) {
//Setup the serial port for 2400 baud at 12MHz.
// SCON: mode 1, 8-bit UART, enable reciever
SCON = 0x50; 
// TMOD: timer 1, mode 2, 8-bit reload	
TMOD |= 0x20;
// TH1: reload value for 2400 baud @ 12MHz	
TH1 = 0xF3;
// TR1: timer 1 run	
TR1 = 1;
// TI: set TI to send first char of UART	
TI = 1; 
//Set Timer0 for 16-bit interval timer mode.
TMOD |= 0x01;
T0_ISR_count = 0;
// Value saved in register for delay 
TH0 = 0x63;
TL0 = 0xC0;
TR0 = 1;
//Enable timer zero interrupts
ET0 = 1;
//Enable interrupts in the whole system
EA = 1;
while (1) {
//Receive keystrokes from the user through the UART
char x = _getkey();
printf("%c",x);
//Identify the key and compare it with the training password 	
if(x != key[i] && i != 10 && x != empty){
//If the user enters an incorrect character print a warning message	
	printf("Incorrect Password !!");
	}
if (x == key[i] ) {
     i++;
//We keep track of the interrupt flag give use an insight of the flight time  
	  timekey[i] += abs(T0_ISR_count); 
    T0_ISR_count =0;
} 
//if the counter i reaches 10 thus the user used one 
//of his five trials therefore reset the counter i.
//If the counter count is less than 5 means 
//that the user has more iterations to go.
if(count <5 && i == 10){
	printf("\n");
  i = 0;
	count ++;
}
//Training phase user A 
//If the input port reads a value A indicates that 
//we are in the training phase and the current user is A.
	if (P0 == 0x0A){
	flag = 0;}
//Now user A used all his 5 trials
//therefore we need to calculate the
//flight time and save it in user's A profile.
//We discard the time before the first keystroke 
//to end up with 9 features.
else if(count == 5 && flag == 0 ){
	for(j =0; j<9;j++){
//Average of 5 trials 
	  differenceA[j] = abs(timekey[j + 1])/ 5;
	}
//To reuse the same array to save user's B feature profile
// we need to reset it's values 
	for(q = 0; q <=9; q++ ){
		timekey[q] = 0;
	}
//Training phase user B
//If the input port reads a value B indicates that 
//we are in the training phase and the current user is B.
	if (P0 == 0x0B){
	flag = 1;
	}
  flag = 1;
	i = 0;
	count = 0;
	}
//Now user B used all his 5 trials
//therefore we need to calculate the
//flight time and save it in user's B profile.
//We discard the time before the first keystroke 
//to end up with 9 features.
	else if (count == 5 && flag == 1){
		for(r =0; r<9;r++){
//Divide by five to get the average of each feature
		differenceB[r] = abs(timekey[r + 1]) / 5;
//We will use this array to save the timings of the 
//test user , so we reset all the values.			
	}for(q = 0; q <= 9; q++ ){
		timekey[q] = 0;
	}
//Test phase unknown user
//If the input port reads a value C indicates that we are 
//in the test phase and the user is unknown.
if (P0 == 0x0C){
	flag=2;}
		flag = 2;
	i = 0;
	count++;
	}
//Save the flight time of each feature of the test user
	else if (count == 6 && flag == 2 && i == 10){
		for(l =0; l<9;l++){
		differenceT[l] = abs(timekey[l + 1]) ;
	}
//Euclidean
//We simplified the equation since it is a comparison
// the square roots will cancel each other.
//Comparing each feature of test user to profile A & B	
		for(t = 0; t <8;t++){
		Da += (differenceT[t] - differenceA[t]) * (differenceT[t] - differenceA[t]);
		Db += (differenceT[t] - differenceB[t]) * (differenceT[t] - differenceB[t]);			
		}
//If condition is satisfied this means features of 
//user A were closer to test user the features of user B.
		if(Da < Db){
//User A detected
//P3=0x0A;  
//flash LED once
    	int z2;
			for (z2=0 ;z2<10;z2++)
			{
				P1 = 0x00;
      delay();
      P1 = 0xFF;
			delay();
			}
			while(1);
      }
		else{
//User B detected 
//P3=0x0B;
//flash LED twice
      int z;
			for (z=0 ;z<30;z++)
			{
			P2 = 0x00;
      delay();
      P2 = 0xFF;
			delay();
   	}
			while(1);
	}
	}
}
}

