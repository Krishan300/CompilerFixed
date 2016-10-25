#include "parser.h"
#include "Token.h"
#include <string>
#include <cstring>


Parser::Parser(Lexer& lexerx, ostream& outx): lexer(lexerx), out(outx), lindex(1), tindex(1) {
  token = lexer.nextToken();
}

Parser::~Parser() {
}

const string Parser::ops[] =
  {"ADD", "SUB", "MULT", "DIV",
               
  "ISEQ", "ISNE", "ISLT", "ISLE", "ISGT", "ISGE",
                                                
  "AND", "OR",

  "PUSHL", "PUSHV", "STORE",

  "JUMP", "JUMPF", "JUMPT", "CALL", "RET",

  "PRINTF",

  "LABEL", "SEQ" };

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
      node=new TreeNode(PUSHV, token.getlexeme());
      token=lexer.nextToken();
     
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
    // TreeNode* node2;
    //node=factor();
    //Token temp=token;
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
  TreeNode* node;
  TreeNode* node2;
  node=expression();
  // cout<<token.getlexeme()<<endl;
  int toketype=token.gettype();
  Operation op;
      if(toketype==Token::EQ)
      {
        op=ISEQ;
	token=lexer.nextToken();
	node2=expression();
	node=new TreeNode(op, node, node2);
      }
     if(toketype==Token::LT)
      {
        op=ISLT;
	token=lexer.nextToken();
	node2=expression();
	node=new TreeNode(op, node, node2);
       }
     if(toketype==Token::LE)
      {
        op=ISLE;
	token=lexer.nextToken();
	node2=expression();
	node=new TreeNode(op, node, node2);
      }
     if(toketype==Token::GT)
        {
        op=ISGT;
	token=lexer.nextToken();
	node2=expression();
	node=new TreeNode(op, node, node2);
         }
     if(toketype==Token::GE)
         {
        op=ISGE;
        token=lexer.nextToken();
	
	node2=expression();
	node=new TreeNode(op, node, node2);
         }
     if(toketype==Token::NE)
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
  //token=lexer.nextToken();  
  int temp=token.gettype();
  //cout<<token.getlexeme()<<endl;
  Operation op;
  //TreeNode* node2=relationalExpression();
       // TreeNode* node2=relationalExpression();
    while(temp==AND || temp==OR)
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
  TreeNode* node=statement();
  check(Token::RBRACE, "Expecting right brace");
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
       node=logicalExpression();
      check(Token::RPAREN, "expecting right parenthesis.");
      token=lexer.nextToken();
       string JUMPF1Label=makeLabel();
       TreeNode* JumpF1=new TreeNode(JUMPF, JUMPF1Label);
       node=new TreeNode(SEQ, node, JumpF1);
       TreeNode* thenBlock=block();
      node=new TreeNode(SEQ, node, thenBlock);       
      if(token.gettype()==Token::ELSE)
	{
	  //String Label2=makeLabel()+":";
	  string JumpLabel2=makeLabel();
	  TreeNode* JumpL2=new TreeNode(JUMP, JumpLabel2);
	  node=new TreeNode(SEQ, node, JumpL2);
	  string Label1=makeLabel()+":";
	  TreeNode* LabelL1=new TreeNode(LABEL, Label1);
	  node=new TreeNode(SEQ, node, LabelL1);
	  TreeNode* elsenode=block();
	  node=new TreeNode(SEQ, node, elsenode);
	  // String JumpLabel2=makeLabel()+":";
	  string Label2=makeLabel()+":";
	  TreeNode* LabelL2=new TreeNode(LABEL, Label2);
	  node=new TreeNode(SEQ, node, LabelL2);
	  token=lexer.nextToken();
	}
      
      else{
	string Label1=makeLabel()+":";
	TreeNode* LabelL1=new TreeNode(LABEL, Label1);
	node=new TreeNode(SEQ, node, LabelL1);
      }

      
     }

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
       thestatement=assignStatement();
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
  check(Token::LBRACE, "Expecting left parenthesis");
  token=lexer.nextToken();
  TreeNode* node=logicalExpression();
  check(Token::RBRACE, "Expecting right parenthesis");
  token=lexer.nextToken();
  TreeNode* blocknode=block();
  string Label1=makeLabel()+":";
  TreeNode* L1=new TreeNode(LABEL, Label1);
  node=new TreeNode(SEQ, L1, node);
  string JUMPFL2=makeLabel();
  TreeNode* jumpFL2=new TreeNode(JUMPF, JUMPFL2);
   node=new TreeNode(SEQ, node, jumpFL2);
   node=new TreeNode(SEQ, node, blocknode);
   string jumpl1=makeLabel();
  TreeNode* JUMPl1=new TreeNode(JUMP, jumpl1);
   node=new TreeNode(SEQ, node, JUMPl1);
  return node;  
  }
  
Parser::TreeNode* Parser:: assignStatement(){
  check(Token::IDENT, "Expecting ident");
  TreeNode* Identifier=new TreeNode(STORE, token.getlexeme());
  token=lexer.nextToken();
  check(Token::ASSIGN, "Expecting assignment statement");
  token=lexer.nextToken();
  TreeNode* node=logicalExpression();
  check(Token::SEMICOLON, "Expecting right parenthesis");
  token=lexer.nextToken();
  node=new TreeNode(SEQ, node, Identifier);  
  return node;  
}
