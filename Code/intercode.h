#ifndef __INTERCODE_H__
#define __INTERCODE_H__

#define WORD_LENGTH 4

struct Operand_ {
	enum { CONSTANT_INT, CONSTANT_FLOAT, VARIABLE, FUNC_NAME, ADDRESS} kind;
	union{
		int intValue;
		float floatValue;
		char* var;
		char* func_name;
		char* addr;
	};
};
typedef struct Operand_* Operand;

Operand new_operand(int kind, int intValue, float floatValue, char* name);

#define OP1_OFF 0
#define OP2_OFF 8
#define OP3_OFF 16

struct InterCode_ {
	enum { 
		iLABEL = OP1_OFF, iFUNC, iGOTO, iRETURN, iARG, iPARAM, iREAD, iWRITE,
		iASSIGN = OP2_OFF, iCALL, iADDRESS, iGET, iPOST, iDEC,
		iADD = OP3_OFF, iSUB, iMUL, iDIV, iREGOTO
	} kind;
	union {
		struct { Operand op; } operate1;
		struct { Operand op1, op2; } operate2;
		struct { Operand op1, op2, op3; } operate3;
	};
};
typedef struct InterCode_* InterCode;

InterCode new_intercode(int kind);

struct InterCodes_ {
	InterCode code;
	struct InterCodes_ *prev, *next;
};
typedef struct InterCodes_* InterCodes;

// codeField is the root empty node
// context is the position to generate
extern InterCodes codeField, context;

#define is_constant(kind) ((kind == CONSTANT_INT || kind == CONSTANT_FLOAT)?1:0)
void intercodeInit();
void addCode(InterCode code, InterCodes position/*=context*/);
int op_num(int kind);
void print_intercode();
char* new_temp();
char* new_label();
char* new_var();

#define INIT_3_OP \
	code->operate3.op1 = op1;\
	code->operate3.op2 = op2;\
	code->operate3.op3 = op3;

#define INIT_2_OP \
	code->operate2.op1 = op1;\
	code->operate2.op2 = op2;

#endif
