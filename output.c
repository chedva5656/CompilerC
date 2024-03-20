#include "header.h"


long char_to_bin(char ch){

	long bin=dec_to_bin((int)ch);
	return bin;
}

int power(int num,int p){
	int result=1;
	int i;
	for(i=1;i<=p;i++)
		result=num*result;
	return result;		
}

long dec_to_bin(int dec){
	long bin=0;
	int counter=0;
	long musk=1;
	if(dec==0)
		return 0;
	while(dec!=0){
		if((dec & musk)==1 && counter==0)
			bin+=1;
		else if((dec & musk)==1)
			bin+=power(10,counter);
		counter++;
		dec=dec>>1;	
	}
  	return bin;
}

int bin_to_base64(int n)
{
    	int num = n;
    	int dec_value = 0;
  
    	// Initializing base value to 1, i.e 2^0
    	int base = 1;
  
    	int temp = num;
    	while (temp) {
        	int last_digit = temp % 10;
        	temp = temp / 10;
  
        	dec_value += last_digit * base;
  
        	base = base * 2;
    	}
  
    	return dec_value;
}
  
