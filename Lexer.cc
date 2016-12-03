/*
  File name: Lexer.cc
  Project: Compiler
  Author: Krishan Madan
  Email: krm219
  Class: CSE109
  Professor: James Femister
  Description:creates tokens based on chars read from input stream
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
  tokepos=0;
  line=1;
}

char Lexer:: nextChar()
{
     
  // char currentchar=storedstream.get();
  
  
  // if(!storedstream.eof())
  //{
    /* if (storedstream.get()=='\n')
    {
    pos=0;
    line++;
    currentchar= ' ';
    }
   else
   {
   pos++;
   //currentchar= storedstream.get();
    }
  }  
  if(storedstream.eof())
    {
      currentchar='#';
    }
    return currentchar;*/
  // char currentchar=storedstream.get();
  //char  currentchar;
   while(!storedstream.eof())
   {
    char  currentchar=storedstream.get();
      if (currentchar== '\n' )
      {
	pos=0;
	line++;
	return ' ';
      }
      
         else 
	 {
	   pos++;
	   return currentchar;
	 }
      //return currentchar;
   }
       
       pos++;	      
       return 'a';
         
    // return currentchar;
    }
  /* else
    {
      currentchar= '#';
      }*/
 


Token Lexer::nextToken()
{
  // int tokepos=0;
  int lineholder=0;
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
      tokepos++;
	lineholder=line;
      bool match;
      while(isalpha(ch) || isdigit(ch))
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
      tokepos++;
      lineholder=line;
      type=Token::INTLIT;
      while(isdigit(ch))
      {
	lexeme+=ch;
        ch=nextChar();
       }
     }
     else if(ch=='"')
      {
	tokepos++;
	lineholder=line;
	type=Token::STRINGLIT;
	//lexeme+='"';
	ch=nextChar();
	while(ch!='"')
	  {
	    
	 lexeme+=ch;
	 ch=nextChar();	    
	  }
	//lexeme+='"';
	ch=nextChar();
       }
	else{
	  // if(ch!=EOF)
	  // {
            switch(ch)
            {
	    
	    case '+':
	      tokepos++;
	      lineholder=line;
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
	      tokepos++;
	      lineholder=line;
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
	   tokepos++;
	   lineholder=line;
	   lexeme+='-';
	   type=Token::MINUS;
	   ch=nextChar();
	   break;

	   case '*':
	   tokepos++;
	   lineholder=line;
	   lexeme+='*';
	   type=Token::TIMES;
	   ch=nextChar();
	   
	   break;

	   case '/':
	   tokepos++;
	   lineholder=line;
	   lexeme+='/';
	   type=Token::DIVIDE;
	   ch = nextChar();
	   break;

	    case '&':
	      {
	    char temp9=nextChar();
	    if(temp9=='&')
	      {
		tokepos++;
		lineholder=line;
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
	     tokepos++;
	     lineholder=line;
	   lexeme+='(';
	   type=Token::LPAREN;
	   ch=nextChar();
	   break;

	   case ')':
	     tokepos++;
	     lineholder=line;
	   lexeme+=')';
	   type=Token::RPAREN;

	   ch=nextChar();
	   break;

	   case '{':
	   tokepos++;
	   lineholder=line;
	   lexeme+='{';
	   type=Token::LBRACE;
	   ch=nextChar();
	   break;

	  case '}':
	  tokepos++;
	  lineholder=line;
	  lexeme+='}';
	  type=Token::RBRACE;
	   ch=nextChar();
	   break;

	   case ',':
	   tokepos++;
	   lineholder=line;
	   lexeme+=',';
	   type=Token::COMMA;
	   ch=nextChar();
	   break;

	   

	   case '>':
	     {
	    tokepos++;
	    lineholder=line;
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

	    case '!':
	      {
	    tokepos++;
	    lineholder=line;
	    lexeme+=ch;
	    ch=nextChar();
	    lexeme+=ch;
	    ch=nextChar();
	    type=Token::NE;
	    break;
               
            }
           case '<':
	   {
	       
	   tokepos++;
	   lineholder=line;
	   char temp5= '<';
	   ch=nextChar();
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
	   tokepos++;
	   lineholder=line;
	   lexeme+=';';
	   type=Token::SEMICOLON;
	   ch=nextChar();
	   break;

	     case 'a':
	    tokepos++;
	    lineholder=line;
	    type=Token::ENDOFFILE;
	    lexeme="You have reached end of file";
	    // ch=nextChar();
	    break;

	    case '|':
	      {
	      
	    char temp7='|';
	    ch=nextChar();
            if(ch==temp7)
	      {
	        tokepos++;
		lineholder=line;
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
	    tokepos++;
	    lineholder=line;
	   type=Token::ERROR;
	   lexeme+="ERROR";
	   ch=nextChar();
	   break;
	    }
	}
       

   /* else if(ch=='#')
	    {
	      tokepos++;
	      lineholder=line;
	      type=Token::ENDOFFILE;
	      lexeme="You have reached end of file";
	      // break;        
	    }
	}
    for(int i=0; i<(int)(sizeof(keywords)/sizeof(keywords[0]));i++)
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
  
   //ch=nextChar();
   /* if(pos==0)
     {
       tokepos=0;
     }*/
   if(line-lineholder==1)
     {
       tokepos=1;
     }
   
  return Token(type, lexeme, line, tokepos);

}


    


  
