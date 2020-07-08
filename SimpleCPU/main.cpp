/* 
 * File:   main.cpp
 * Ebru Kardaş 141044049

	The program simulate a very simple CPU with 5 registers and 6 instructions
(move, addition, subtraction, jump, print and halt). To run, your command in 
terminal have to be like "$ program filename option". 

If option is 0, the program will run and finish by executing each instructions,
if option is 1, the program will execute each instruction after displaying the 
instruction first.
if option is 2, it is exactly the same as option 1 but it prints memory.

 *
 * Created on October 17, 2016, 10.27 PM
 */

#include <iostream>
#include <fstream>

using namespace std;
// main progress in program().
int* program(const string *file, int size, char* argv[2], int* reg, unsigned int* mem);
// validStr() is checking argumans of instruction, cleanStr() is erased spaces
// and tabs and lower cases will be upper.
string validStr(string temp);
string cleanStr(string k);
// kind of stoi function that I write
int strToInt(string ptr);
// for HALT instruction for finite program
int search(string* arr, int strSize, string target);
// arg pointer (0. index-1. register arguman , 1. index-2. register arguman, 
// 2. index-constant value , 3. index-first memory address, 4. index-second 
// memory address) will be returned.
int* argumans(string s, int *arg);
void printReg(int* reg);											// opt 1
void printMem(unsigned int* mem);								// opt 2

// INTRUCTIONS
int* move(int* arr, int* reg, unsigned int* mem);
int* addition(int* arr, int* reg, unsigned int* mem);
int* subtraction(int* arr, int* reg, unsigned int* mem);
int jump(int* arr, int* reg, int size, int i);
int jpn(int* arr, int* reg, int i);
void print(int* arr, int* reg, unsigned int* mem);
int halt(int* arr, int size);

int main(int argc, char** argv) {

	string file[200], line ;
	int size,  reg[5] = {0,0,0,0,0}; 
	unsigned int mem[50];
	ifstream myFile(argv[1]);

	for(int y=0; y<50; ++y)												// initialization memory (all 0)
		mem[y]=0;

	if( (*argv[2] != '1' || *argv[2] != '0' || *argv[2] != '2' ) && argc != 3){				// OPTION CONTROLL
		cerr << "Arguman Error!\n";
		return -1;
	}

	if(myFile.is_open()){												// OPENED_FILE CONTROLL
		for( size=0; getline (myFile, line); ++size )
			file[size]=cleanStr(line);
		myFile.close();
	}
	else{
		cerr << ".txt file cannot opened." << endl;
		return -1;
	}

	if( search(file,size,"HLT") == -1){								// HLT CONTROLL (for finite loop)
		cerr << "There is no HALT instruction! \n ";
		return -1;
	}

	program(file,size,argv,reg,mem);

	if(*argv[2] == '0')													// option 0
		printReg(reg);

	return 0;
}

int* program(const string *file, int size, char* argv[2], int* reg, unsigned int* mem){

	int flag=0;

	for(int lineNum=0; lineNum<size ; ++lineNum){

		int arr[5]={-1,-1,-1,-1,-1}, lin= lineNum;				// for jmp instruction
		string  s = file[lineNum].substr(3);
		argumans(s, arr);

		if(file[lineNum].rfind("MOV") != -1)
			move(arr, reg, mem);

		else if(file[lineNum].rfind("ADD") != -1)
			addition(arr, reg, mem);

		else if( file[lineNum].rfind("SUB")!=-1 )
			subtraction(arr,reg, mem);

		else if( file[lineNum].rfind("JMP")!=-1 )
			lineNum = jump(arr, reg, size, lin);

		else if( file[lineNum].rfind("PRN") != -1 )
			print(arr, reg, mem);

		else if( file[lineNum].rfind("JPN") != -1 )
			lineNum = jpn(arr, reg, lin);

		else if( file[lineNum].rfind("HLT") != -1 )
			lineNum = halt(arr, size);

		else if( file[lineNum] == "" ){
			cerr << "Empty line or invalid instruction!\n";
			return reg;
		}
		else
			cerr << lin+1 << ". line cannot be read in .txt file!\n";


		if(*argv[2] == '1'){
			cout << file[lin] << endl;
			printReg(reg);
		}
		else if(*argv[2] == '2'){
			cout << file[lin] << endl;
			printMem(mem);
		}
	}
}

string validStr(string temp){

	string r, inst;
	int h= temp.find_first_not_of(" 	");
	if( h!=-1 )
		inst = temp.erase(0, h);							// tabs or spaces are gone

	h = temp.find_first_of(" 	");
	if( h != -1 ){
		inst = temp.substr(0, h);
		r = temp.substr(h+1);
		if( ( h= r.find_first_not_of(" 	") ) != -1 ){
			cerr << "Not valid instruction!\n";
			return "";
		}
	}
	return inst;
}

int strToInt(string ptr){

	int i, digit, num=0;
	char dig;

	if(ptr=="")													// for empty string
		return -1;
// loop looks from units digit(end of the ptr) to beginning of the ptr
	for( i=ptr.size()-1, digit=1;		i>=0;		--i, digit*=10 ){
		dig = ptr[i]-'0';										// to control if it is a number
		if(dig>=0 && dig<=9 )
			num += dig*digit;									// addition with its digit
		else if(i==0){											// for negative numbers
			if(ptr[0]=='-')
				num = 0-num;
		}
		else
			return -1;
	}
	return num;
}

int search(string* arr, int strSize, string target){	// FOR FINITE LOOP (HALT EXIST?)

	for(int i=0; i<strSize; ++i){
		if(arr[i]==target)
			return i;
	}
	return -1;
}

string cleanStr(string k){

	string inst, temp=k, s,p;
	int h, m;

	if( ( m= temp.find_first_of(';') ) != -1 )			// comment erased
		temp.erase( m );
	if( ( m = temp.find_first_not_of(" 	") ) != -1 )	// first space&tab erased
		temp.erase( 0, m );

	h= temp.find_first_of(" 	");
	m= temp.size();

	if( m==3 ){													// the instruction like hlt (with no param)
		for(int i=0 ; i<temp.size(); ++i ){
			if( temp[i] >= 'a' && temp[i] <= 'z' )
				temp[i] += ('A'-'a');
		}
		return temp;
	}
	if(h!=3 ){													// instruction controll
		cerr << "Instruction is not valid\n";			// m, mo is not valid, just mov
		return "";
	}
	else{
		inst = temp.substr(0,3);							//instruction taken (will returned)
		temp.erase(0,h);										// and erased to find parameter(s)

		h = temp.find_first_of(",");
		if( h != -1){											// if it has 2 parameters
			string f = temp.substr(0,h);					// first parameter
			if( ( p = validStr(f) ) == "")				// if it is valid or not
				return "";
			inst += p;											// valid param taken
			inst +=",";
		}

		s = temp.substr(h+1);								// second param
		if( ( p = validStr(s) ) == "")
			return "";
		inst += p;												// valid param taken
	}
		
	for(int i=0 ; i<inst.size(); ++i ){					// Lower letters -> upper letters
		if( inst[i] >= 'a' && inst[i] <= 'z' )
			inst[i] += ('A'-'a');
	}
	return inst;
}

int* argumans(string s, int *arg){
// arg is my variable set.
// arr[5] = {1. param-register, 2. param-register, constant, 1. param-memory, 2. param-memory }
		int i = s.find_first_of(','), temp;
		string ptr1, ptr2;

		if(i>0)
			ptr1 = s.substr(0, i), ptr2 = s.substr(i+1);
		else
			ptr1 = s, ptr2 = "";

		if(ptr1[0]=='R'){										// 1. param- reg
			temp = strToInt(ptr1.erase(0,1))-1;			// 'R' erased, string conversed to int and for index (-1)
			if( temp >=0 && temp <=5 )						// If it is valid for register 
				arg[0] = temp;									// assignment
			else													// otherwise, error
				cerr << "First register is not valid\n";
		}
		else if(ptr1[0]=='#'){								// 1. param- mem
			temp = strToInt(ptr1.erase(0,1));			// '#' erased, string conversed to int 
			if( temp >=0 && temp <50 )						// If it is valid for memory
				arg[3] = temp;									// assignment
			else													// otherwise, error
				cerr << "First memory address is not valid\n";
		}
		else
			arg[2] = strToInt(ptr1);

// SAME THİNG LIKE FIRST ARGUMAN
		if(ptr2[0]=='R'){
			temp = strToInt(ptr2.erase(0,1)) -1;
			if( temp >=0 && temp <=5 )
				arg[1] = temp;
			else
				cerr << "Second register is not valid\n";
		}
		else if(ptr2[0]=='#'){
			temp = strToInt(ptr2.erase(0,1));
			if( temp >=0 && temp <=50 )
				arg[4] = temp;
			else
				cerr << "Second register is not valid\n";
		}
		else if(ptr2.size() !=0)
			arg[2] = strToInt(ptr2);

	return arg;
}


void printReg(int* reg){

	cout << "\nRegisters : ";

	for(int index=0; index<5; ++index)
		cout << "| " << reg[index] << " |" ;
	cout << "\n\n";

	return;
}

void printMem(unsigned int* mem){

	cout << "Memory content is : \n";

	for(int index=0; index<50; ++index){
		cout << "| " << mem[index] << "|";
		if((index+1)%10==0)									// to look better
			cout << endl;
	}
	cout << "\n\n";

	return;
}

int* move(int* arr, int* reg, unsigned int* mem){

	if(arr[0] !=-1){											// 1. param-register
		if(arr[1] != -1 )										// reg-reg
			reg[arr[1]]=reg[arr[0]];						// as in the pdf
		else if(arr[2] != -1 )								// reg-const			
			reg[arr[0]]=arr[2];
		else if( arr[4] != -1 )								// reg-mem
			mem[arr[4]] = reg[arr[0]];
	}
	else if(arr[3] !=-1){									// 1. param-memory
		if(arr[1] != -1 )										// mem-reg
			reg[arr[1]] = mem[arr[3]];						// as in the pdf
		else if(arr[2] != -1 )								// mem-constant
			mem[arr[3]] = arr[2];
	}
	else															// anything else, error
		cerr << "An error occured in MOV register\n";

	return reg;
}

int* addition(int* arr, int* reg, unsigned int* mem){

	if(arr[0] !=-1){											// 1. param-register
		if(arr[1] !=-1)										// reg-reg
			reg[arr[0]] += reg[arr[1]];
		else if(arr[2] != -1)								// reg-const
			reg[arr[0]] += arr[2];
		else if( arr[4] != -1 )								//reg-mem
			reg[arr[0]] += mem[arr[4]] ;
	}
	else															// anything else, error
		cerr << "An error occured in ADD register\n";

	return reg;
}

int* subtraction(int* arr, int* reg, unsigned int* mem){

	if(arr[0] !=-1){											// 1. param-register
		if(arr[1] !=-1)										// reg-reg
			reg[arr[0]] = reg[arr[0]] - reg[arr[1]];
		else if(arr[2] != -1)								// reg-const
			reg[arr[0]] = reg[arr[0]] - arr[2];
		else if( arr[4] != -1 )								//reg-mem
			reg[arr[0]] = reg[arr[0]] - mem[arr[4]] ;
	}
	else															// anything else, error
		cerr << "An error occured in SUB register\n";

	return reg;
}

int jump(int* arr, int* reg, int size, int i){

	if(arr[0] !=-1){											// 1. param-reg
		if(reg[arr[0]] == 0)									// jump condition
			return arr[2]-2;									// (-1) for index, other (-1) for updating counter
		return i;												// to keep going if the condition is not executed
	}
	else if( arr[2] >=0 && arr[2]<= size )				// 1. param-const
		return arr[2]-2;										// (-1) for index, other (-1) for updating counter
	else{															// anything else, error
		cerr << "An error occured in JMP register\n";
		return -2;												// to not keep going in the loop of program() 
	}
}

int jpn(int* arr, int* reg, int i){

	if(arr[0] != -1){											// 1. param-reg
		if(reg[arr[0]] <= 0)									// jump condition
			return arr[2]-2;									// (-1) for index, other (-1) for updating counter
		return i;												// to keep going if the condition is not executed
	}
	else{															// anything else, error
		cerr << "An error occured in JPN register\n";
		return -2;												// to not keep going in the loop of program() 
	}
}

void print(int* arr, int* reg, unsigned int* mem){

	if( arr[1] == -1 && arr[4] == -1){					// just in case, register control
		if(arr[0] !=-1)										// 1. param-reg
			cout << reg[arr[0]] << endl;					// print to screen
		else if(arr[2] != -1)								// 1. param-const				
			cout << arr[2] << endl;
		else if(arr[3] != -1)								// 1. param-mem
			cout << mem[arr[3]] << endl;
	}
	else															// anything else, error
		cerr << "An error occured in PRN register\n";

	return;
}

int halt(int* arr, int size){

	if(arr[0] != -1 && arr[1] != -1 && arr[2] != -1){	// arguman control
		cerr << "HALT instruction cannot take arguments! \n";
		return -1;
	}
	return size;												// to finish loop
}
