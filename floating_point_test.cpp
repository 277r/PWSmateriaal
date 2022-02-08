// dit zorgt ervoor dat een struct geen padding bevat voor efficientie
// this makes sure that structs aren't padded, this can decrease efficiency
#pragma pack (1)

// IO 
#include <iostream>
// logarithmische functies, en meer
#include <cmath>

// define mantissa size of float 

#define CF_MANTISSA_GROOTTE 5
#define CF_EXPONENT_GROOTTE 3


struct customFloat {
	// door : achter de naam van het variabele te zetten, vertellen we de compiler dat het zoveel bits mag hebben
	// by putting : behind the variable name, we tell the compiler how much bits should be used
	unsigned int exp : CF_EXPONENT_GROOTTE;
	unsigned int mantissa : CF_MANTISSA_GROOTTE;
};

// turn number into customFloat
customFloat getalNaarFloat(float input){

	float bewerkteInput = input + 1;
	
	// door het log2 van het getal te krijgen, krijgen we de exponent die we nodig hebben voor de float
	unsigned int exponent = floor(log2(bewerkteInput));

	float mantissa = (bewerkteInput) / pow(2,exponent);
	
	mantissa -= 1;
	mantissa *= pow(2,CF_MANTISSA_GROOTTE);
	round(mantissa);

	// debug
	//std::cout << exponent << ", " << mantissa << "\n";

	if (mantissa >= pow(2,CF_MANTISSA_GROOTTE) || exponent >= pow(2,CF_EXPONENT_GROOTTE)){
		std::cout << "warning: out of bounds;";
		std::cout << "rounding to closest number";
	}

	return {exponent,(unsigned int)mantissa};

}


float customFloatNaarGetal(customFloat input){
	float mantissa = 1 + (input.mantissa *  (1.0F / pow(2,CF_MANTISSA_GROOTTE)));
	float exponent = pow(2,input.exp);
	return (mantissa * exponent) - 1;
	
}

// het programma begint hier
int main(){
	std::cout << "de grootte van de customFloat struct is: " << sizeof(customFloat) << " byte\n";
	
	std::cout << "\nalle waarden die de exponent kan aannemen\n";
	customFloat test_getal;


	test_getal.exp = 0;
	
	do {
		std::cout << test_getal.exp << "\n";
		test_getal.exp++;
	}
	while (test_getal.exp != 0);

	std::cout << "\nalle waarden die de mantisse kan aannemen\n";

	test_getal.mantissa = 0;


	do {

		std::cout << test_getal.mantissa << "\n";
		test_getal.mantissa++;
	}

	while (test_getal.mantissa != 0);

	std::cout << "\nalle mogelijke waarden die deze floating points aan kunnen nemen: (3e kolom)\n";


	// laat alle mogelijke combinaties zien van floating point getallen met deze standaard
	for (unsigned int i = 0; i < pow(2,3); i++){
		for (unsigned int ii = 0; ii < pow(2,5); ii++){
			std::cout << i << ", " << ii << ", " << customFloatNaarGetal({i,ii}) << "\n";
		}
	}



}
