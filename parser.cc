/*
File name: parser.cc
Description: parses code
Project: Compiler
Author: Krishan Madan
Email: krm219
Class: CSE109
Professor: James Femister
*/



#include "parser.h"
//#include "Token.h"
//#include "SymbolTable.h"
//#include "hashTable.cc"
#include <string>
#include <stdio.h>
#include <cstring>


const string Parser::ops[] =
  {"ADD", "SUB", "MULT", "DIV",

   "ISEQ", "ISNE", "ISLT", "ISLE", "ISGT", "ISGE",

   "AND", "OR",

   "PUSHL", "PUSHV", "STORE",

   "JUMP", "JUMPF", "JUMPT", "CALL", "RET",

   "PRINTF",

   "LABEL", "SEQ",

   "PARAM1", "PARAM2", "PARAM3", "PARAM4", "PARAM5", "FUNC" };




Parser::Parser(Lexer& lexerx, ostream& outx): lexer(lexerx), out(outx), lindex(1), tindex(1) {
    token = lexer.nextToken();
    tabofsymbols= SymbolTable();
    pushvandstore=new string[1000];//used to store strings output in
				   //bss section
    keepstrack=0; 
}


 



void Parser::error(string message) {
  cerr << message << " Found " << token.getlexeme() << " at line " << token.getline() << " position " << token.getposition() << endl;
  exit(1);
}

void Parser::check(int tokenType, string message) {
  if (token.gettype() != tokenType)
    error(message);
}

Parser::TreeNode* Parser::factor() {
  
  TreeNode* node;
  int toketype=token.gettype();
  
     if(toketype== Token::INTLIT)
      {
	node=new TreeNode(PUSHL, token.getlexeme());
      token=lexer.nextToken();
      
      }
     if(toketype== Token::IDENT)
      {
      string identlexeme=token.getlexeme();
      // identlexeme=tabofsymbols.getUniqueSymbol(identlexeme);
      // cout<<identlexeme.c_str()<<endl;
      // cout<<token.getlexeme()<<endl;
      //node=new TreeNode(PUSHV, token.getlexeme());
      token=lexer.nextToken();
      // tabofsymbols.addSymbol(identlexeme);
           if(token.gettype()==Token::LPAREN)
	    {
	     node=funcall(identlexeme);
             }
	      else if(token.gettype()==Token::ASSIGN)
	    {
	      // tabofsymbols.addSymbol(identlexeme);
	     identlexeme=tabofsymbols.getUniqueSymbol(identlexeme);
             if(identlexeme==" ")
	       {
		 error(identlexeme);
	       }
             node=assignStatement(identlexeme);
	     }
           else
	     {
	       // tabofsymbols.addSymbol(identlexeme);
	       identlexeme=tabofsymbols.getUniqueSymbol(identlexeme);
	       if(identlexeme==" ")
		 {
		   error(identlexeme);
		 }
	       // tabofsymbols.add(identlexeme);
	       node=new TreeNode(PUSHV, identlexeme);
	       // token=lexer.nextToken();
	     }
      }
     if(toketype== Token::LPAREN)
      {
       token=lexer.nextToken();
      node=expression();
      check(Token::RPAREN, "Expecting right parenth");
      token=lexer.nextToken();
      
      }
    
  
  return node;
 }

    Parser::TreeNode* Parser::term() {
    TreeNode* node=factor();
    
    
    
    int temp=token.gettype();
    while(temp==Token::TIMES || temp==Token::DIVIDE)
    {
      token=lexer.nextToken();
      
     //token=lexer.nextToken();
       
        if(temp==Token::TIMES)
        {
	  TreeNode* node2=factor();
          node=new TreeNode(MULT, node, node2);
        }
	else if(temp==Token::DIVIDE)
        {
	  TreeNode* node2=factor();
         node=new TreeNode(DIV, node, node2);
        }
	
	temp=token.gettype();
    }
  return node;
 }

Parser::TreeNode* Parser::expression() {
  TreeNode* node=term();
 
     int temp=token.gettype();  
     while(temp==Token::PLUS ||  temp==Token::MINUS)
     {
       token=lexer.nextToken();
        if(temp==Token::PLUS)
	  {
	    TreeNode* node2=term();
	    node=new TreeNode(ADD, node, node2);
	  }
	if(temp==Token::MINUS)
	  {
	    TreeNode* node2=term();
	    node=new TreeNode(SUB, node, node2);
	  }
	temp=token.gettype();
     }
     
  return node;
}

Parser::TreeNode* Parser::relationalExpression() {
  TreeNode* node=expression();
  
  TreeNode* node2;
  int toketype=token.gettype();
  Operation op;
      if(toketype==Token::EQ)
      {
        op=ISEQ;
	token=lexer.nextToken();
	node2=expression();
	node=new TreeNode(op, node, node2);
      }
      else if(toketype==Token::LT)
      {
        op=ISLT;
	token=lexer.nextToken();
	node2=expression();
	node=new TreeNode(op, node, node2);
       }
      else if(toketype==Token::LE)
      {
        op=ISLE;
	token=lexer.nextToken();
 	node2=expression();
	node=new TreeNode(op, node, node2);
      }
      else if(toketype==Token::GT)
        {
        op=ISGT;
	token=lexer.nextToken();
	node2=expression();
	node=new TreeNode(op, node, node2);
         }
      else if(toketype==Token::GE)
         {
        op=ISGE;
        token=lexer.nextToken();
	
	node2=expression();
	node=new TreeNode(op, node, node2);
         }
      else if(toketype==Token::NE)
         {
        op=ISNE;
	token=lexer.nextToken();
	node2=expression();
	node=new TreeNode(op, node, node2);
         }
      
   
    
  return node;
 }

Parser::TreeNode* Parser::logicalExpression() {
  
  TreeNode* node=relationalExpression();
  // token=lexer.nextToken();  
  int temp=token.gettype();
   
  Operation op;
  // cout<<token.getlexeme()<<endl;
  
  //TreeNode* node2=relationalExpression();
       // TreeNode* node2=relationalExpression();
  while(temp==Token::AND || temp==Token::OR)
    {
      token=lexer.nextToken();
      //TreeNode* node2;
        if(temp==Token::AND)
        {
	 TreeNode* node2=relationalExpression();
	 op=AND;
        //token=lexer.nextToken();
	  // node2=relationalExpression();
        node=new TreeNode(op, node, node2);
        }

        if(temp==Token::OR)
        {

	  TreeNode* node2=relationalExpression();
	  op=OR;
        //token=lexer.nextToken();
        //node2=relationalExpression();
        node=new TreeNode(op, node, node2);
        } 
	temp=token.gettype();	
    }
  
  return node;
}

Parser::TreeNode* Parser::block(){
  check(Token::LBRACE, "Expecting left brace");
  
  token=lexer.nextToken();
  TreeNode* node;
   TreeNode* node2;
       if(token.gettype()==Token::RBRACE)
	 {
	   node=new TreeNode(SEQ);
	 }
         else
	 {
               node=statement();
  
	       while(token.gettype()==Token::WHILE || token.gettype()==Token::VAR || token.gettype()==Token::RETURN || token.gettype()==Token::IDENT || token.gettype()==Token::IF || token.gettype()==Token::PRINTF)
             {
	        node2=statement();
	       node=new TreeNode(SEQ, node, node2);
	  
             }
             check(Token::RBRACE, "Expecting right brace");
	 }
       
  token=lexer.nextToken();
  return node;
  }



Parser::TreeNode* Parser::ifStatement(){
  TreeNode* node;  
  
  
  //  TreeNode* l1=block()
  if(token.gettype()==Token::IF)
     {
      token=lexer.nextToken();
      check(Token::LPAREN, "expecting left parenthesis.");
      token=lexer.nextToken();
      // tabofsymbols.enterScope();
       node=logicalExpression();
      check(Token::RPAREN, "expecting right parenthesis.");
      token=lexer.nextToken();
       tabofsymbols.enterScope();
       TreeNode* thenBlock=block();
        tabofsymbols.exitScope();
       string JUMPF1Label=makeLabel();
       TreeNode* JumpF1=new TreeNode(JUMPF, JUMPF1Label);
       node=new TreeNode(SEQ, node, JumpF1);
      
      node=new TreeNode(SEQ, node, thenBlock);       
      if(token.gettype()==Token::ELSE)
	{
	  
	  string JumpLabel2=makeLabel();
	  TreeNode* JumpL2=new TreeNode(JUMP, JumpLabel2);
	  node=new TreeNode(SEQ, node, JumpL2);
	  string Label1=JUMPF1Label+":";
	  TreeNode* LabelL1=new TreeNode(LABEL, Label1);
	  node=new TreeNode(SEQ, node, LabelL1);
	  token=lexer.nextToken();
	   tabofsymbols.enterScope();
	  
	   TreeNode* elsenode=block();
	      tabofsymbols.exitScope();
	  node=new TreeNode(SEQ, node, elsenode);
	  // String JumpLabel2=makeLabel()+":";
	  string Label2=JumpLabel2+":";
	  TreeNode* LabelL2=new TreeNode(LABEL, Label2);
	  node=new TreeNode(SEQ, node, LabelL2);
          //token	  
	}
      
      else{
	string Label1=JUMPF1Label+":";
	TreeNode* LabelL1=new TreeNode(LABEL, Label1);
	//cout<<"here it is;";
	node=new TreeNode(SEQ, node, LabelL1);
	//token=lexer.nextToken();
      }

      
     }
  //   token=lexer.nextToken();
  return node;

}
Parser::TreeNode* Parser::statement(){
  TreeNode* thestatement;
     if(token.gettype()==Token::IF)
     {
       thestatement=ifStatement();
     }
     else if(token.gettype()==Token::WHILE)
     {
       thestatement=whileStatement();
     }
     else if(token.gettype()==Token::IDENT)
     {
       thestatement=factor();
     }
       else if(token.gettype()==Token::VAR)
     {
       thestatement= vardefStatement();
     }
     else if (token.gettype()==Token::RETURN)
       {
	 thestatement=returnStatement();
       }
     else if(token.gettype()==Token::PRINTF)
       {
         thestatement=printfStatement();
       }
     else{
       thestatement=NULL;
     }
     return thestatement;
}

/*Parser::TreeNode* Parser::block(){
  check(Token::LBRACE, "Expecting left brace");
  token=lexer.nextToken();
  TreeNode* node=statement();
  check(Token::RBRACE, "Expecting right brace");
  token=lexer.nextToken();
  return node;
  }*/

Parser::TreeNode* Parser::whileStatement(){
  
  check(Token::WHILE, "Expecting while");  
  token=lexer.nextToken();
  check(Token::LPAREN, "Expecting left parenthesis");
  token=lexer.nextToken();
  TreeNode* node=logicalExpression();
  check(Token::RPAREN, "Expecting right parenthesis");
  token=lexer.nextToken();
  // tabofsymbols.enterScope();
  tabofsymbols.enterScope();
  TreeNode* blocknode=block();
   tabofsymbols.exitScope();
  string Label1=makeLabel();
  TreeNode* L1=new TreeNode(LABEL, Label1+":");
  node=new TreeNode(SEQ, L1, node);
  string JUMPFL2=makeLabel();
  TreeNode* jumpFL2=new TreeNode(JUMPF, JUMPFL2);
   node=new TreeNode(SEQ, node, jumpFL2);
   node=new TreeNode(SEQ, node, blocknode);
   
  TreeNode* JUMPl1=new TreeNode(JUMP, Label1);
   node=new TreeNode(SEQ, node, JUMPl1);
   string L2=JUMPFL2+":";
   TreeNode* Label2=new TreeNode(LABEL, L2);
   node=new TreeNode(SEQ, node, Label2);
  return node;  
  }
  
Parser::TreeNode* Parser:: assignStatement(string identname){
  
  TreeNode* Identifier=new TreeNode(STORE, identname);
  // identlexeme=tabofsymbols.getUniqueSymbol(identlexeme);
   token=lexer.nextToken();
   // check(Token::ASSIGN, "Expecting assignment statement");*/
  // token=lexer.nextToken();
  TreeNode* node=logicalExpression();
  check(Token::SEMICOLON, "Expecting semicolon");
  token=lexer.nextToken();
  node=new TreeNode(SEQ, node, Identifier);  
  return node;  
}

Parser::TreeNode* Parser:: funcall(string funcname){
  TreeNode* callnode=new TreeNode(CALL, funcname);
 
  TreeNode* retnode=callnode;
  bool isotherexpres=false;
  TreeNode* otherside;
  check(Token::LPAREN, "Expecting left paren.");
  token=lexer.nextToken();
   if(token.gettype()==Token::LPAREN || token.gettype()==Token::INTLIT || token.gettype()==Token::IDENT)
     {
	  otherside=expression();
	 isotherexpres=true;
              while(token.gettype()==Token::COMMA)
	      {
		token=lexer.nextToken();
		TreeNode* currentexp=expression();
		otherside=new TreeNode(SEQ, otherside, currentexp);
	      }
       }
      check(Token::RPAREN, "Expecting right paren");
      
      if(isotherexpres)
	{
         retnode=new TreeNode(SEQ, otherside, callnode);
        }
      else
	{
	  retnode=callnode;
	}
      token=lexer.nextToken();
      return retnode;
   }


Parser:: TreeNode* Parser:: vardefStatement(){
  check(Token::VAR, "expecting var");
  token=lexer.nextToken();
  check(Token::IDENT, "expecting ident");
   tabofsymbols.addSymbol(token.getlexeme());   
  token=lexer.nextToken();
  while(token.gettype()==Token::COMMA)
    {
      token=lexer.nextToken();
      check(Token::IDENT, "expecting ident");
      tabofsymbols.addSymbol(token.getlexeme());
      token=lexer.nextToken();
    }
  check(Token::SEMICOLON, "expecting semicolon");
  // TreeNode* ret= new TreeNode(SEQ,"this is placeholder");
  //return ret;
  token=lexer.nextToken();
   TreeNode* placeholder=new TreeNode(SEQ);
     
	
         
	
  return placeholder;
}



Parser:: TreeNode* Parser::returnStatement(){
  check(Token::RETURN, "expecting return");
  token=lexer.nextToken();
  TreeNode* le=logicalExpression();
  check(Token::SEMICOLON, "expecting semicolon");
  TreeNode* re=new TreeNode(RET);//?-confused
  le=new TreeNode(SEQ, le, re);
  token=lexer.nextToken();
  return le;
}

Parser:: TreeNode* Parser::parameterdef(string paramname, int count){
  
  TreeNode* individualparam;
  Operation possibleparams[]={PARAM1, PARAM2, PARAM3, PARAM4, PARAM5};
  individualparam=new TreeNode(possibleparams[count-1], paramname);
  token=lexer.nextToken();
  return individualparam;
  }





Parser:: TreeNode* Parser::Function(){
  check(Token::FUNCTION, "expecting function");
  TreeNode* retNode;
  string passtoparam;
   int identcounter=0;
  token=lexer.nextToken();
  TreeNode* leftnode=new TreeNode(FUNC, token.getlexeme()+":");
  check(Token::IDENT, "expecting ident");
  token=lexer.nextToken();
  check(Token::LPAREN, "expecting left paren");
  // tabofsymbols.enterScope();
  token=lexer.nextToken();

    if(token.gettype()==Token::IDENT)
	 {
	   tabofsymbols.enterScope();
	   tabofsymbols.addSymbol(token.getlexeme());
	    identcounter=identcounter+1;
	   passtoparam=tabofsymbols.getUniqueSymbol(token.getlexeme());
	   
	   TreeNode* otherleft=new TreeNode(STORE,passtoparam);
	   token=lexer.nextToken();
           leftnode=new TreeNode(SEQ, leftnode, otherleft);
	   while(identcounter>0)
	      {
		if(token.gettype()==Token::COMMA)
		  {
		  token=lexer.nextToken();
		  
		  }
		  else if (token.gettype()==Token::IDENT)
		  {
		      identcounter=identcounter+1;
		      tabofsymbols.addSymbol(token.getlexeme());
		       passtoparam=tabofsymbols.getUniqueSymbol(token.getlexeme());
		       otherleft=new TreeNode(STORE, passtoparam);
		       token=lexer.nextToken();
		       leftnode=new TreeNode(SEQ, leftnode, otherleft);
		  }
		    // check(Token::COMMA, "expecting comma");
		       else if(token.gettype()==Token::RPAREN)
		       {
			 // tabofsymbols.exitScope();
			break;
		       }
		       /* else if(token.gettype()==Token::COMMA)
		      {
		      token=lexer.nextToken();
		      }*/
		    // check(Token::COMMA, "expecting comma");
		    // // identcounter=identcounter+1;
		    // otherleft=parameterdef(token.getlexeme(), identcounter);
		    // leftnode=new TreeNode(SEQ, leftnode, otherleft);
		    // token=lexer.nextToken();
		  }
	 }
	 
	 /*check(Token::IDENT, "expecting ident");
	identcounter=identcounter+1;
	TreeNode* lastparam=parameterdef(token.getlexeme(), identcounter);
	leftnode=new TreeNode(SEQ, leftnode, lastparam);*/
	token=lexer.nextToken();
	tabofsymbols.enterScope(); 
       TreeNode* rightnode=block();
       tabofsymbols.exitScope();
       retNode=new TreeNode(SEQ, leftnode, rightnode);
       if(identcounter>0)
	 {
       tabofsymbols.exitScope();
	 }
       return retNode; 


       }

/*Parser:: TreeNode* Parser::parameterdef(string paramname, int count){

  TreeNode* individualparam;
  Operation possibleparams[]={PARAM1, PARAM2, PARAM3, PARAM4, PARAM5};
  individualparam=new TreeNode(possibleparams[count-1], paramname);
  token=lexer.nextToken();
  return individualparam;
  }*/

string currentFunc;
int nfmts = 0;
string fmts[100];
void Parser:: genasm(TreeNode* node){
  cout<< "    global main\n    extern printf\n" ;
  // genist(node);
  vardefs(node);
  cout<<"\n    segment .bss\n";
  int i;
  for(i=0; i<keepstrack; i++)
    {
      cout<<"    "+ pushvandstore[i]+" resq 1\n";

    }
  cout<<"\n    section .text\n";
  genist(node);
  cout<<"\n    section .data\n";
  for (int i=0; i < nfmts; ++i) {

  cout << "    fmt" << i+1 << ": db " << fmts[i] << ", 0" << endl;

  }
  
}
Parser::TreeNode* Parser:: compilationUnit(){
  // TreeNode* retnode;
  TreeNode* topnode=Function();
  // bool isotherfunc=false;
  //retnode=topnode;
        if(token.gettype()==Token::FUNCTION)
	  {
	    TreeNode* nextfunction=Function();
	    // isotherfunc=true;
	    topnode=new TreeNode(SEQ, topnode, nextfunction);
	        while(token.gettype()==Token::FUNCTION)
		  {
		    TreeNode* currfunction=Function();
                    topnode=new TreeNode(SEQ, topnode, currfunction);
                  }
	  }
	return topnode;
}

   

void Parser::genist(TreeNode *node){
    if(node!=NULL){
  genist(node->leftChild);
  genist(node->rightChild);
  emit(node->op, node->val);
    }
  }

void Parser:: vardefs(TreeNode *node){
  if(node!=NULL)
  {
    vardefs(node->leftChild);
    vardefs(node->rightChild);
    bssection(node);
    }
}

void Parser:: bssection(TreeNode *node)
{
  int keepstrack2;
  int tellsbefore=0;
  if(node->op==PUSHV || node->op==STORE)
    {
      for(keepstrack2=0;keepstrack2<1000;keepstrack2++)
	{
          if(pushvandstore[keepstrack2]==node->val)
	    {
              tellsbefore+=1;
	      break;
	    }
	     
	}
      if(tellsbefore==0)
	{
	  pushvandstore[keepstrack]=node->val;
	  keepstrack++;
	}
    }
  /* if(tellsbefore==0)
    {
  pushvandstore[keepstrack]=node->val;
  keepstrack++;
  }*/
}
void Parser:: emit(Operation op, string val){
  /* string currentFunc;
  int nfmts = 0;
  string fmts[100];*/
  string funcval;
  switch(op){
  case ADD:
    {
      cout<<"    pop rbx\n    pop rax\n    add rax,rbx\n    push rax\n";
      break;
    }
  case SUB:
     {
       cout<<"    pop rbx\n    pop rax\n    sub rax,rbx\n    push rax\n";
       break;
     }
  case AND:
     {
       cout<<"    pop rbx\n    pop rax\n    and rax,rbx\n    push rax\n";
      break;
     }
  case OR:
     {
       cout<<"    pop rbx\n    pop rax\n    or rax,rbx\n    push rax\n";
      break;
     }
  case MULT:
     {
       cout<<"    pop rbx\n    pop rax\n    imul rbx\n    push rax\n";
      break;
     }
  case DIV:
     {
       cout<<"    mov rdx,0\n    pop rbx\n    pop rax\n    idiv rbx\n    push rax\n";
       break;
     }
  case LABEL:
     {
       cout<<val<<"\n";
       break;
     }
  case SEQ:
    {
      cout<<"";
      break;
      

    }
  case PARAM1:
    {
      cout<<"";
      break;

    }
  case PARAM2:
    {
      cout<<"";
      break;

    }
  case PARAM3:
    {
      cout<<"";
      break;

    }
  case PARAM4:
    {
      cout<<"";
      break;

    }
  case PARAM5:
    {
      cout<<"";
      break;

    }
  case JUMP:
     {
       cout<<"    jmp "+val+"\n";
       break;
     }
  case JUMPF:
     {
       cout<<"    pop rax\n    cmp rax,0\n    je "+val+"\n";
       break;
     }
  case JUMPT:
    {
      cout<<"    pop rax\n    cmp rax,0\n    jne "+val+"\n";
      break;
    }
  case CALL:
    {
      cout<<"    call "+val+"\n    push rax\n";
      break;

    }
  case PRINTF:
    {
      string fmt = val;
      int nparams = fmt.at(0) - '0';
      fmt = "`" + fmt.substr(1) + "`";
      fmts[nfmts++] = fmt;
      cout<<"    mov rdi,fmt" + itos(nfmts)+"\n";
      if (nparams == 5) {
	cout<<"    pop r9\n";
	--nparams;
      }
      if (nparams == 4) {
	cout<<"    pop r8\n";
	--nparams;
      }
      if (nparams == 3) {
	cout<<"    pop rcx\n";
	--nparams;
      }
      if (nparams == 2) {
	cout<<"    pop rdx\n";
	--nparams;
      }
      if (nparams == 1) {
	cout<<"    pop rsi\n";
      }
      cout<<"    mov rax,0\n";
      cout<<"    push rbp\n";
      cout<<"    call printf\n";
      cout<<"    pop rbp\n";
      
      break;
 


    }

    case STORE:
      {
        cout<<"    pop qword["+val+"]\n";
	break;
      }
  case PUSHL:
    {
      cout<<"    mov rax,"+val+"\n    push rax\n";
      break;
 
    }
  case PUSHV:
    {
      cout<<"    push qword["+val+"]\n";
      break;
    }

  case FUNC:
    {
      currentFunc=val;
      cout<<val+ "\n";
      if(val!="main:")
	{
	  cout<<"    pop r15\n";
	}
      break;
      
    }
  case RET:
    {
      cout<<"    pop rax\n";
      if(currentFunc!="main:")//modified//wrong val
	{
	  cout<<"    push r15\n";
	}
      cout<<"    ret\n";
      break;

    }
   
  default:
    {
      relationalexprestaker(op,val);

    }
  }
  
     }


  
void Parser:: relationalexprestaker(Operation op, string val){
   int count=0;
    string Label1=makeLabel();
    string Label2=makeLabel();
    string optostring;
    switch(op)
      {
      case ISEQ:
	{
	  optostring="     je";
	  break;
	}
      case ISNE:
	{
	  optostring="     jne";
	  break;
	}
      case ISLT:
	 {
	   optostring="    jl";
	   break;
	 }
      case ISLE:
	 {
           optostring="    jle";
	   break;
	 }
      case ISGT:
	 {
           optostring="    jg";
	   break;
	 }
      case ISGE:
	 {
           optostring="    jge";
	   break;
	 }
	 default:
	{
	  count++;
          cout<<"   "+val+"not a sequence or others \n";
	  break;
	  }
      }
    if(count==0)
      {
	cout<<std::string("    pop rbx\n    pop rax\n    cmp rax,rbx\n")+optostring+" "+Label1+"\n"+"    mov rax,0\n"+"    jmp "+Label2+"\n"+Label1+":\n"+"    mov rax,1\n"+Label2+":\n"+"    push rax\n";
      }
  }


/*Parser::void Parser:: genasm(TreeNode* node){
  printf("     global main\n","     extern printf\n","     segment .bss\n");
  }*/


Parser::TreeNode* Parser::printfStatement() {
  TreeNode* paramList = NULL;
  int nparams = 0;
  check(Token::PRINTF, "Expecting printf");
  token = lexer.nextToken();
  check(Token::LPAREN, "Expecting (");
  token = lexer.nextToken();
  check(Token::STRINGLIT, "Expecting string literal");
  string formatString = token.getlexeme();
  token = lexer.nextToken();
  if (token.gettype() == Token::COMMA) {
    token = lexer.nextToken();
    paramList = expression();
    ++nparams;
    while (token.gettype() == Token::COMMA) {
      token = lexer.nextToken();
      paramList = new TreeNode(SEQ, paramList, expression());
      ++nparams;
    }
  }
  check(Token::RPAREN, "Expecting )");
  token = lexer.nextToken();
  check(Token::SEMICOLON, "Expecting ;");
  token = lexer.nextToken();
   TreeNode* printStatement =
     new TreeNode(SEQ, paramList, new TreeNode(PRINTF, itos(nparams) + formatString));
   return printStatement;
}
