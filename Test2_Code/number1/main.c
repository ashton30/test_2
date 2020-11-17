/*a lexical analyzer for test 2 */
/*this is my answer to number 1 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
  global variables and function declarations provided by Robert W. Sebesta
  R. W. Sebesta, Concepts of Programming Languages. Boston, MA: Pearson, 2016
*/

/* Global declarations */
/* Variables */

int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
char idenEnd = ':';
FILE *in_fp;

/* Function declarations */
int lookup(char ch); //symbol table
void addChar(void); //adder
void getChar(void); //getter
void getNonBlank(void); //handle spaces
int lex(void); //lexical analyzer
void error(void); //print error statement

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define FLOAT 2
#define UNKNOWN 99

/* Token codes */
#define STR_LIT 7 //java-style string literal ""
#define INT_LIT 8 //c-style int literal
#define CHA_LIT 9 //c-style character lit ' '
#define FLO_LIT 10 //c-style floating point lit
#define IDENT 11 //identifier
#define ASSIGN_OP 20 //assignment operator
#define ADD_OP 21 //add operator
#define SUB_OP 22 //subtract operator
#define MULT_OP 23 //multiply operator
#define DIV_OP 24 //divide operator
#define LEFT_PAREN 25 //left parenthesis
#define RIGHT_PAREN 26 //right parenthesis
#define LEFT_CURLY 27 //LEFT OPEN CODE BLOCK
#define RIGHT_CURLY 28 //RIGHT CLOSE CODE BLOCK
#define INCR_OP 29 //INCREMENT OPERATOR
#define DEC_OP 30 //DECREMENT OPERATOR
#define MOD_OP 31 //MODULUS OPERATOR
#define AND_OP 32 // AND OPERATOR
#define OR_OP 33 // OR OPERATOR
#define NOT_OP 34 // NOT OPERATOR
#define IF_CODE 50 //CHECKS FOR "IF"
#define ELSE_CODE 51 //CHECKS FOR "ELSE"
#define WHILE_CODE 52 //CHECKS FOR "WHILE"
#define DOESNT_EXIST 77 //prints for invalid chars

/******************************************************/
/*
  this method provided by Robert W. Sebesta
  R. W. Sebesta, Concepts of Programming Languages. Boston, MA: Pearson, 2016
*/
/* main driver */
int main(void) {
	/* Open the input data file and process its contents */
  //states if file is null return error
	 if ((in_fp = fopen("front.in", "r")) == NULL)
	 	printf("ERROR - cannot open front.in \n");
	 else { //if there isnt an error get the next char
	 	getChar();
	 do { //then call lex as long as nexttoken isnt eof
	 	lex();
	 } while (nextToken != EOF);
	 }
	 return 0;
}
/******************************************************/
/* lookup - a function to look up unkown characters and return the token */

/*
  some parts of this method provided by Robert W. Sebesta
  R. W. Sebesta, Concepts of Programming Languages. Boston, MA: Pearson, 2016. Aspects coded by me (Ashton Sims) in this method are noted.
*/

 //symbol table
int lookup(char ch) {
	 switch (ch) {
  /***************************************************************/
    //this case coded by me (Ashton Sims)
     case  '@':
      /*
        this test case states that if a letter or digit follows the at sign to store it as an identifier. otherwise it doesnt exist.
     */
			 addChar();
       getChar();
       if(!isspace(nextChar)){
         while((isalpha(nextChar) && !isspace(nextChar)) || (isdigit(nextChar) && !isspace(nextChar))){
           addChar();
           getChar();
          }
          if(!isalnum(nextChar)){
            nextToken = IDENT;
			      addChar();
            getChar();
            break;
          }  
        }else{ 
			    nextToken = DOESNT_EXIST;
			    break;
        }
       //break;
  /****************************************************************/
    //this case coded by me (Ashton Sims)
     case  '$':
      /*
        this test case states that if a letter or digit follows the dollar sign to store it as an identifier. otherwise
        it doenst exist.
     */
			 addChar();
       getChar();
       if(!isspace(nextChar)){
         while((isalpha(nextChar) && !isspace(nextChar)) || (isdigit(nextChar) && !isspace(nextChar))){
           addChar();
           getChar();
          }
          if(!isalnum(nextChar)){
            nextToken = IDENT;
			      addChar();
            getChar();
            break;
          }
        }else{  
			    nextToken = DOESNT_EXIST;
			    break;
        }
        //break;
    /**************************************************************/
		 case  '(':
			 addChar();
			 nextToken = LEFT_PAREN;
			 break;

		 case ')':
			 addChar();
			 nextToken = RIGHT_PAREN;
			 break;

     //this case coded by me (Ashton Sims)
		 case '+':
     /*
      this states that if its followed by another addition sign it means its an increment sign. otherwise its an addition sign.
     */
			 addChar();
       getChar();
       if(nextChar == '+'){
         addChar();
        nextToken = INCR_OP;
        break;
       }else{
			  nextToken = ADD_OP;
			  break;
       }
       //this case coded by me (Ashton Sims)
		 case '-':
     /*
      this states that if its followed by another minus sign it means
      its a decrement sign. otherwise its a subtraction sign.
     */
			 addChar();
       getChar();
       if(nextChar == '-'){
         addChar();
        nextToken = DEC_OP;
        break;
       }else{
			 nextToken = SUB_OP;
			 break;
       }

		 case '*':
			 addChar();
			 nextToken = MULT_OP;
			 break;

		 case '/':
			 addChar();
			 nextToken = DIV_OP;
			 break;

     case '{':
			 addChar();
			 nextToken = LEFT_CURLY;
			 break;

     case '}':
			 addChar();
			 nextToken = RIGHT_CURLY;
			 break;

     case '%':
			 addChar();
			 nextToken = MOD_OP;
			 break;

     //this case coded by me (Ashton Sims)
     case '!':
     /*
        this test case states that if a letter or digit follows the exclamation point to store it as an identifier
     */
			 addChar();
       getChar();
       if(!isspace(nextChar)){
         while((isalpha(nextChar) && !isspace(nextChar)) || (isdigit(nextChar) && !isspace(nextChar))){
           nextToken = IDENT;
           //charClass = LETTER;
           addChar();
           getChar();
           //charClass = LETTER;
           //break;
          }
          /*this states if nothing follows the exclamation point that its a not statement*/
        }else{  
			    nextToken = NOT_OP;
			    break;
        }
        break;
     //this case coded by me (Ashton Sims)
     case '|':
      /*
      this states that in order to be an or statement it must have another "|" following the first one. otherwise it doesnt exist.
      */
       addChar();
       getChar();
       if(nextChar == '|'){
         addChar();
        nextToken = OR_OP;
        break;
       }else{
          //getChar();
          nextToken = DOESNT_EXIST;
			    break;
       }
       //this case coded by me (Ashton Sims)
     case '\'':
        /*
          this states that if a single quote is detected to
          add all characters after it until the second one is detected
          and then classify it as a c character literal.
        */
        addChar();
        getChar();
        while(isalnum(nextChar)){
          addChar();
          getChar();
          if(nextChar == '\''){
            addChar();
            nextToken = CHA_LIT;
            break;
          }
        }
        break;
        //nextToken = CHA_LIT;
     //this case coded by me (Ashton Sims)
     case '\"':
        /*this states that if a double quote is detected to
          add all characters after it until the second one is detected
          and then classify it as a java string literal.
        */
        addChar();
        getChar();
        while(isalnum(nextChar)){
          addChar();
          getChar();
          if(nextChar == '\"'){
            addChar();
            nextToken = STR_LIT;
            break;
          }
        }
        break;

     case '=':
			 addChar();
			 nextToken = ASSIGN_OP;
			 break;
      
     //this case coded by me (Ashton Sims)
     case '&':
      /*
        this states that in order to be a logical AND statement
        it must be followed by a second &. otherwise it doesnt exist
      */
			 addChar();
       getChar();
       if(nextChar == '&'){
         addChar();
        nextToken = AND_OP;
        break;
       }else{
          //getChar();
          nextToken = DOESNT_EXIST;
			    break;
       }
     //this case coded by me (Ashton Sims)
     case '.':
       addChar();
       nextToken = FLO_LIT;
			 break;
		 default:
			 addChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
/*
  this method provided by Robert W. Sebesta
  R. W. Sebesta, Concepts of Programming Languages. Boston, MA: Pearson, 2016
*/
void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	} else
	printf("Error - lexeme is too long \n");
}


/******************************************************/
/*
  this method provided by Robert W. Sebesta
  R. W. Sebesta, Concepts of Programming Languages. Boston, MA: Pearson, 2016
*/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void) {
	 if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar))
		 	charClass = LETTER;
		
     else if(isdigit(nextChar))
      charClass = DIGIT;
   else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
}


/******************************************************/
/*
  this method provided by Robert W. Sebesta
  R. W. Sebesta, Concepts of Programming Languages. Boston, MA: Pearson, 2016
*/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
	while (isspace(nextChar))
	getChar();
}

/******************************************************/
//this method coded by me (Ashton Sims)
/*print error statement*/
void error(void){
  printf("ERROR\n");
}


/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex(void) {
	 lexLen = 0;
	 getNonBlank();
	 switch (charClass) {
		/* Identifiers */
    //this case coded by me (Ashton Sims)
		 case LETTER:
			 addChar();
			 getChar();
       if(!isspace(nextChar)){
         while((isalpha(nextChar) && !isspace(nextChar)) || (isdigit(nextChar) && !isspace(nextChar))){
           addChar();
           getChar();
          }
          if(!isalnum(nextChar)){
            nextToken = IDENT;
			      addChar();
            getChar();
            break;
          }  
        }else{ 
			    nextToken = DOESNT_EXIST;
			    break;
        }
       
       
		/* Integer literals */
    //this case altered by me (Ashton Sims)
		 case DIGIT:
			 addChar();
			 getChar();
			 while (charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
			  nextToken = INT_LIT;
		 	  break;

    /* floating point literals */
     /*case FLOAT:
			 addChar();
			 getChar();
			 while (charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
			 nextToken = FLO_LIT;
		 	 break;*/
		/* Parentheses and operators */

    /*
     this method provided by Robert W. Sebesta
      R. W. Sebesta, Concepts of Programming Languages. Boston, MA: Pearson, 2016
    */
		 case UNKNOWN:
			 lookup(nextChar);
			 getChar();
			 break;
			/* EOF */
		case EOF:
			 nextToken = EOF;
			 lexeme[0] = 'E';
			 lexeme[1] = 'O';
			 lexeme[2] = 'F';
			 lexeme[3] = '\0';
		 	break;
	 } /* End of switch */
	 printf("Next token is: %d, Next lexeme is %s\n",
	 nextToken, lexeme);
	 return nextToken;
} /* End of function lex */ 