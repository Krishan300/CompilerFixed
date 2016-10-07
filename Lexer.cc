/*
  CSE 109
  Krishan Madan
  krm219
  Breaks up input stream into tokens
  Program #4
*/
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "Token.h"
#include <string>
#include "Lexer.h"
using namespace std;
Lexer::Lexer(istream& streamread): storedstream(streamread)
{
  ch=nextChar();
  pos=0;
  line=1;
}

char Lexer:: nextChar()
{
  
  char currentchar;
  if(!storedstream.eof())
  {
   currentchar=storedstream.get();
   
  if(currentchar=='\n')
	{
	  pos=0;
	  line++;
	  currentchar=' ';
	}
      else
	{
	  pos++;
	}
  }
    if(storedstream.eof())
    {
      currentchar='#';
    }
   return currentchar;

}
  
Token Lexer::nextToken()
{
  
  string lexeme;
  int type;
  string keywords[]={"if","else","while", "function", "var","printf","return"};
  int position[]={Token::IF, Token::ELSE, Token::WHILE,  Token::FUNCTION, Token::VAR, Token:: PRINTF, Token::RETURN};
  if(ch==' ')
  {
  while (ch==' ')
    {
      ch=nextChar();
    }
  }
  /*switch (ch)
    {
    case(' '):
    
    case(isalpha(ch)):
      while(isalpha(ch))
     {
       lexeme+=ch;
       ch=nextChar();
     }
     break;*/
  /*  if(ch==' ')
  {
    ch=nextChar();
    } */
   if(isalpha(ch))
    {
      bool match;
      while(isalpha(ch))
	{
	  // cout<<ch<<endl;  
	  lexeme+=ch;
	  ch=nextChar();
	}
       for(int i=0; i<(int)(sizeof(keywords)/sizeof(keywords[0]));i++)
	{
	   match=true;
	  if(lexeme==keywords[i])
	    {
	      type=position[i];
	      match=false;
	      break;
	    }
	}
       if(match==true){
	 type=Token::IDENT;
	  }
    }

    else if(isdigit(ch))
    {
      type=Token::INTLIT;
      while(isdigit(ch))
      {
	lexeme+=ch;
        ch=nextChar();
       }
     }
     else if(ch=='"')
      {
	type=Token::STRINGLIT;
	while(ch!='"')
	  {
	    
	    lexeme+=ch;
            ch=nextChar();	    
           }
       }
	else{

            switch(ch)
            {
	    
	    case '+':
	    lexeme+='+';
	    type=Token::PLUS;
	    ch=nextChar();
	    break;
	    
	    /* case '-':
	    lexeme+='-';
	    type=5;
	    nextChar();
	    break;*/

	    case '=':
	    {
	    char temp='=';
	    ch=nextChar();
	    if(ch!=temp)
	    {
	      type=Token::ASSIGN;
	     lexeme+=temp;
	     break;
	    }
	    else
	    {
	      type=Token::EQ;
	    lexeme=temp+ch;
	    ch=nextChar();
	    break;
	    }
           break;
	      }

	   case '-':
	   lexeme+='-';
	   type=Token::MINUS;
	   ch=nextChar();
	   break;

	   case '*':
	   lexeme+='*';
	   type=Token::TIMES;
	   ch=nextChar();
	   break;

	   case '/':
	   lexeme+='/';
	   type=Token::DIVIDE;
	   ch = nextChar();
	   break;

	    case '&':
	      {
	    char temp9=nextChar();
	    if(temp9=='&')
	      {
		lexeme+=temp9+'&';
		type=Token::AND;
		ch=nextChar();
		break;
	      }
	    else{
	      break;
	    }
            break;
	      }
            
	   case '(':
	   lexeme+='(';
	   type=Token::LPAREN;
	   ch=nextChar();
	   break;

	   case ')':
	   lexeme+=')';
	   type=Token::RPAREN;
	   ch=nextChar();
	   break;

	   case '{':
	   lexeme+='{';
	   type=Token::LBRACE;
	   ch=nextChar();
	   break;

	  case '}':
	  lexeme+='}';
	  type=Token::RBRACE;
	 ch=nextChar();
	   break;

	   case ',':
	   lexeme+=',';
	   type=Token::COMMA;
	   ch=nextChar();
	   break;

	   

	   case '>':
	     {
	   char temp3='>';
	   ch=nextChar();
	   if(ch=='=')
	   {
	     lexeme=temp3+ch;
	     type=Token::GE;
	     ch=nextChar();
	     break;
	   }
	   else{
           lexeme+=temp3;
	   type=Token::GT;
	   break;
	   }
	   break;
	   }

	     
           case '<':
	     {
	   char temp5= '<';
	   char ch=nextChar();
	   if(ch=='=')
	   {
	     lexeme=temp5+ch;
             type=Token::LE;
	     ch = nextChar();
	     break;
	   }
	   else
	   {
	     lexeme+=temp5;
             type=Token::LT;
	     break;
	   }
	   break;
	     }

	   case ';':
	   lexeme+=';';
	   type=Token::SEMICOLON;
	   ch=nextChar();
	   break;

	    case '#':
	    type=Token::ENDOFFILE;
	    lexeme="You have reached end of file";
	    break;

	    case '|':
	      {
	    char temp7='|';
	    ch=nextChar();
            if(ch==temp7)
	      {
		type=Token::OR;
		lexeme+=temp7+ch;
		ch=nextChar();
		break;
	      }
	    else
	      {
                break;
	      }
	    break;
	      }

	    default:
	     type=Token::ERROR;
	   lexeme+="ERROR";
	   ch=nextChar();
	   break;
	}
	
	}
   /* for(int i=0; i<(int)(sizeof(keywords)/sizeof(keywords[0]));i++)
    {
      if(lexeme==keywords[i])
	{
	  type=position[i];
	}
      else
	{
	  type=Token::IDENT;
 	}
	}*/
  
  ch=nextChar();
  return Token(type, lexeme, line, pos);
}
    


  
