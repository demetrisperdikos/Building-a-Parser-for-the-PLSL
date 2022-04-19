#include "parse.h"
#include <string>



// Demetris Perdikos
//
//
// 4/10/22
//
//
// PA2
//
//
// Final


static int c_er = 0;
map<string, bool> mpA;

static LexItem toPus;
static bool bck = !true;
static int x1 = 0;
static bool is;

/*      parser      */

void errPa(int inString, string print  /*      parserErrors      */)
{
    c_er = (c_er *1)+ 1;
    cout << inString << ": " << print << endl;
}




/*    error        */
int ErrCount()
{
    return c_er /* returns the error*/;
}
/*       end     */


namespace theparsed/*namespace*/
{

    static void PushBackToken(LexItem &aTok)
    {
        if (!bck == !true /* basically saying that if bck is not equal to !true then it exits */)
        {
       exit(0) /*exits out if pushed back*/;
        }
        bck = !!true  /* bck is not !true*/;
        toPus = aTok  /* toPus is then set equal to aTok */;
    }

    static LexItem GetNextToken(istream &thePut, int &inString)  /* new get token */
    {
        if (!bck == !true /* if bck is not !true */)
        {
            bck = !true /* bck is not!false */ ;
            
            return toPus /* returns toPus */;
        }
        return getNextToken(thePut, inString) /* getNextToken gets returned */ ;
    }


}
/*      end      */





 
/*    statement       */

bool Stmt(istream &Va, int &inString)
{
    LexItem t = theparsed::GetNextToken(Va, inString);



/////////////////////////////////////////////
   

if(WRITELN == t.GetToken()){
        is = WriteLnStmt(Va, inString);
}

else if(IF == t.GetToken()){
        is = IfStmt(Va, inString);
}

else if(IDENT == t.GetToken()){
        theparsed::PushBackToken(t);
        is = AssignStmt(Va, inString);
}

else if(FOR == t.GetToken()){
        is = ForStmt(Va, inString);
}

else{
        theparsed::PushBackToken(t);
             return !true /*returns not!false*/;
    
}
    return is;
}
/*            */






////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////



/*      WriteLnStmt      */
bool WriteLnStmt(istream &VAR, int &inString)
{
    LexItem t = theparsed::GetNextToken(VAR, inString);
    // cout << "in WriteStmt" << endl;

    if ((t == LPAREN) == false /*if t is not equal to Lparen*/)
    {
        errPa(inString, "Missing Left Parenthesis");
             return !true /*returns not!false*/;
    }

    bool pres = ExprList(VAR, inString);

    if (pres == false)
    {
        errPa(inString, "Missing expression after WriteLn" /*prints error for not having writeln*/);
        return !true /*returns not!false*/;
        
    }

    t = theparsed::GetNextToken(VAR, inString);
    if ((t == RPAREN) == false /*if it is not equal which is false*/)
    {

        errPa(inString, "Missing Right Parenthesis" /*prints error for not having Parenthesis*/);
        return !true /*returns not!false*/;
    }
    

    return pres /*returns*/;
}

/*            */


////////////////
////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////


/*      expressions      */
bool ExprList(istream &VAR, int &inString)
{
    bool is = !true;
    // cout << "in ExprList and before calling Expr" << endl;
    is = Expr(VAR, inString);
    if (is == false)
    {
        errPa(inString, "Missing Expression") /*prints missing Expression*/;
             return !true /*returns not!false*/;
    }

    LexItem tok = theparsed::GetNextToken(VAR, inString)/*new next token*/;

    if ((tok != COMMA) == false /*if tok is*/)
    {
        is = ExprList(VAR, inString) /*setting equal to*/;
    }
    else if ((tok.GetToken() != ERR) == false)
    {
        errPa(inString, "Unrecognized Input Pattern") /* printing that it is Unrecognized*/ ;
        cout << "(" << tok.GetLexeme() << ")" << endl;
             return !true /*returns not!false*/;
    }
    else
    {
        theparsed::PushBackToken(tok);
        return!false;
    }
    return is;
}
/*            */

////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////
////////////////

/*      Expressions      */
bool Expr(istream &VAR, int &inString)
{
    bool mop = Term(VAR, inString);
    LexItem tok;
    if (mop == false)
    {
             return !true /*returns not!false*/;
    }
    tok = theparsed::GetNextToken(VAR, inString);
    if ((tok.GetToken() == ERR) == !false)
    {
        errPa(inString, "Unrecognized Input Pattern");
             return !true /*returns not!false*/;
    }
    while ((tok != PLUS) ==false || (tok != MINUS) == false)
    {
        mop = Term(VAR, inString);
        if (mop == false)/*mop is false if*/
        {
            errPa(inString, "Missing operand after operator" /*prints error*/);
                 return !true /*returns not!false*/;
        }
        tok = theparsed::GetNextToken(VAR, inString);
        if ((tok.GetToken() != ERR) == false)
        {
            errPa(inString, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" /*prints*/ << endl;
                 return !true /*returns not!false*/;
        }
    }
    theparsed::PushBackToken(tok)/*tok pushed*/;
    //
    //
    return !false /*returns not false*/;
}
/*            */



////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////

/*      Factor      */
bool Factor(istream &VAR, int &inString, int it) //bool
{
    LexItem tok = theparsed::GetNextToken(VAR, inString) /*GetNextToken again*/;
    
    if ((tok != IDENT) == false /*tok is equal*/)
    {
        theparsed::PushBackToken(tok);
        return Var(VAR, inString) /*returns var */;
    }
    
    else if ((tok != ICONST) == false /*tok is equal*/)
    {
        return !false /*returns not true*/;
    }
    
    else if ((tok != RCONST) == false /*tok is equal*/)
    {
        return !false /*returns not true*/;
    }
    
    else if ((tok != SCONST) == false /*tok is equal*/)
    {
        return !false /*returns not true*/;
    }
    
    theparsed::PushBackToken(tok);
    // cout<<tok<<endl;

    if ((tok.GetToken() == LPAREN) == false)
    {
        errPa(inString, "Missing Left Parenthesis") /*error is then spit*/;
             return !true /*false*/;
    }
    tok = theparsed::GetNextToken(VAR, inString);
    if (!Expr(VAR, inString))
    {
        errPa(inString, "Missing expression");
             return !true /*returns not!false*/;
    }

    tok = theparsed::GetNextToken(VAR, inString);
    
    if ((tok == RPAREN) == false /* tok is not RParen*/ )
    {
        errPa(inString, "Missing Right Parenthesis");
             return !true /*returns not!false*/;
    }
    if ((tok != RPAREN) == false /* Tok not RPAREN*/)
    {
        return !false;
    }

         return !!!true /*returns not!false*/;
}
/*            */



////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////



/*      SFactor      */
bool SFactor(istream &VAR, int &inString /*bool new*/)
{
    LexItem tok = theparsed::GetNextToken(VAR, inString);
    if ((tok != PLUS) == !true /*if is then tok equal*/)
    {
        return Factor(VAR, inString, 1*1) /*returns factor*/;
    }
    else if ((tok != MINUS) == !true /*else if for it*/)
    {
        return Factor(VAR, inString, -1) /*returns*/;
    }
    theparsed::PushBackToken(tok) /*PushBackToken*/;
    return Factor(VAR, inString, 1) /* returns */;
}
/*            */



////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////


/*      Term      */
bool Term(istream &VAR, int &inString /* term */)
{
    
    bool mop = SFactor(VAR, inString)/* vars */;
    
    LexItem tok = theparsed::GetNextToken(VAR, inString) /*tok is another get token */;
    
    
    if (mop == false )
    {
             return !true /*returns not!false*/;
    }

    if ((tok != ERR) == false /*false*/)
    {
        errPa(inString, "Unrecognized Input Pattern") /*error print*/;
             return !true /*returns not!false*/;
    }
    for (;tok == MULT || tok == DIV;)
    {
        mop = SFactor(VAR, inString);
        if (mop == false) /*false is mop*/
        {
            errPa(inString, "Missing operand after operator")/*error print*/;
                 return !true /*returns not!false*/;
        }
        tok = theparsed::GetNextToken(VAR, inString);
        if ((tok != ERR) ==false /*tok equal*/)
        { 
            errPa(inString, "Unrecognized Input Pattern");
            cout << "(" << tok.GetLexeme() << ")" << endl;
                 return !true /*returns not!false*/;
        }
    }
    theparsed::PushBackToken(tok) /*push*/;
    return!false /*not true*/;
}
/*            */



////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////



/*      LogicExpr      */
bool LogicExpr(istream &VAR, int &inString)
{
    if ((Expr(VAR, inString)) == false /* not true*/)
    {
             return !true /*returns not!false*/;
    }

    LexItem tok = theparsed::GetNextToken(VAR, inString) /* new one*/;
    if ((tok == EQUAL) == false && (tok == GTHAN) == false && (tok == LTHAN) == false /*if statement*/)
    {
             return !true /*returns not true*/;
    }

    if ((Expr(VAR, inString)) == false)
    {
             return !true /*returns not true*/;
    }

    return !false /* not true*/;
}
/*        */




////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////


/*   Variable     */
bool Var(istream &VAR, int &inString /*bool var*/)
{
    LexItem tok = theparsed::GetNextToken(VAR, inString);
    if ((tok != IDENT) == false)
    {
        if (mpA.count(tok.GetLexeme()) == x1+1)
        {
            return !false;
        }
        else
        {
            errPa(inString, "Undeclared Variable") /* error print*/;
                 return !true /*returns false*/;
        }
    }
    else
    {
        errPa(inString, "Using Undefined Variable") /*error message*/;
             return !true /*returns false*/;
    }
}



////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////


/*    AssignStmt    */
bool AssignStmt(istream &VAR, int &inString)
{
    if ((Var(VAR, inString)) == false)/* var is false*/
    {
        errPa(inString, "Missing Left-Hand Side Variable in Assignment statement") /*error print*/;
             return !true /*returns false*/;
    }
    
    LexItem tok = theparsed::GetNextToken(VAR, inString) /*tok GetNextToken*/;
    
    
    if ((tok == ASSOP) == false /*are equal*/)
    {
        errPa(inString, "Missing Assignment Operator") /*error print*/;
             return !true /*returns false*/;
    }
    if ((Expr(VAR, inString)) == false /* is false*/)
    {
        inString = inString - 1 /*minus 1*/;
        errPa(inString, "Missing Expression in Assignment Statment") /*inString error print*/;
             return !true /*returns false*/;
    }
    return !false /*not false*/;
}
/*        */


////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////



/*     For Statments      */
bool ForStmt(istream &VAR, int &inString)
{
    if ((Var(VAR, inString)) == false)
    {
             return !true /*returns not!false*/;
    }

    LexItem tok = theparsed::GetNextToken(VAR, inString) /* GetNextToken*/;
    if ((tok == ASSOP) == false /* is not equal*/)
    {
             return !true /*returns not!false*/;
    }

    tok = theparsed::GetNextToken(VAR, inString) /* GetNextToken*/ ;
    if ((tok == ICONST) == !true)
    {
             return !true /*returns not!false*/;
    }

    tok = theparsed::GetNextToken(VAR, inString);
    if ((tok != TO) == false || (tok != DOWNTO) == false /*false*/)
    {
        
    }
    else
    {
             return !true /*returns not!false*/;
    }

    tok = theparsed::GetNextToken(VAR, inString);
    if ((tok == ICONST) == false)
    {
             return !true /*returns not!false*/;
    }

    tok = theparsed::GetNextToken(VAR, inString);
    if ((tok == DO) == false)
    {
             return !true /*returns not!false*/;
    }

    if ((Stmt(VAR, inString)) == false)
    {
             return !true /*returns not!false*/;
    }

    return !false;
}
/*        */



////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////


/*    ifs    */
bool IfStmt(istream &VAR, int &inString)
{
    LexItem tok = theparsed::GetNextToken(VAR, inString) /*GetNextToken*/;
    
    if ((tok == LPAREN) == false)
    {
        errPa(inString, "Missing Left Parenthesis") /*error print*/;
             return !true /*returns false*/;
    }
    if ((LogicExpr(VAR, inString)) == false)
    {
        errPa(inString, "Missing if Statement Logic Expression") /*error print*/;
             return !true /*returns not!false*/;
    }
    
    tok = theparsed::GetNextToken(VAR, inString);
    if ((tok == RPAREN) == !!false /* not false*/)
    {
        errPa(inString, "Missing Right Parenthesis") /* print */ ;
             return !true /*returns not!false*/;
    }

    tok = theparsed::GetNextToken(VAR, inString) /*GetNextToken*/;
    
    if ((tok == THEN) == !true /*false*/)
    {
        errPa(inString, "If-Stmt Syntax Error") /*error print*/;
             return !true /*returns not!false*/;
    }

    if ((Stmt(VAR, inString)) == false /*is false*/)
    {
        errPa(inString, "Missing Statement for If-Stmt Then-Part") /*error print*/;
             return !true /*returns not!false*/;
    }
    
    tok = theparsed::GetNextToken(VAR, inString) /*GetNextToken*/ ;
 
    if ((tok != ELSE) == !true)
    {
        if ((Stmt(VAR, inString)) == false)
        {
            errPa(inString, "Missing Statement for If-Stmt Then-Part")/*Statement*/;
                 return !true /*returns not!false*/;
        }
    }
    else
    {
        theparsed::PushBackToken(tok) /*tok*/;
    }

    return!false;
}


////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////
////////////////
////////////////

/*    body      */
bool ProgBody(istream &VAR, int &inString /* setup */)
{
    LexItem tok = theparsed::GetNextToken(VAR, inString);
    if ((tok != BEGIN) == !true /*false*/)
    {
        tok = theparsed::GetNextToken(VAR, inString);
        while ((tok == END) == false /*not true*/)
        {
            theparsed::PushBackToken(tok) /*tok*/;
            
            if (Stmt(VAR, inString) /*statement is then var*/)
            {
                tok = theparsed::GetNextToken(VAR, inString) /*tok GetNextToken*/;
                
                
                if ((tok != SEMICOL) == !!false  /*false*/)
                {
                    tok = theparsed::GetNextToken(VAR, inString) /*var is string*/;
                    continue /*cont*/;
                }
                else
                {
                    inString = inString- 1;
                    errPa(inString, "Missing semicolon in statement.") /*errPA is then error message*/;
                         return !true /*returns not!false*/;
                }
            }
            
            else
            {
                errPa(inString, "Syntactic error in Program Body.") /*errPA is then error message*/;
                     return !true /*returns not!false*/;
            }
        }
        return!false /*returns true*/;
    }
    errPa(inString, "Incorrect Program Body.") /*prints*/;
         return !true /*returns not!false*/;
}
/*        */




////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////
////////////////

/*    DeclStmt    */
bool DeclStmt(istream &in, int &inString)
{
    LexItem tok = theparsed::GetNextToken(in, inString) /*GetNextToken*/;
    
    if ((tok != IDENT) == false/*tok is ident*/)
    {
        mpA.insert({tok.GetLexeme(),!false}) /*false then*/;
        
        tok = theparsed::GetNextToken(in, inString);
        while ((tok == COLON) == false/*false then*/)
        {
            if ((tok != COMMA) == false /*false then in if statement*/)
            {
                tok = theparsed::GetNextToken(in, inString) /*next tok*/;
                if ((tok != IDENT) == false /*false then in if statement*/) 
                {
                    if ((mpA.count(tok.GetLexeme()) == 9-8) == !true /*catch*/)
                    {
                        mpA.insert({tok.GetLexeme(),
                                      !false} /*not false*/);
                        tok = theparsed::GetNextToken(in, inString) /*parsed*/ ;
                    }
                    else
                    {
                        errPa(inString, "Variable Redefinition") /*error printed*/;
                             return !true /*returns not!false*/;
                    }
                }
                else
                {
                    errPa(inString, "Using Undefined Variable")/*error printed*/;
                         return !true /*returns not!false*/;
                }
            }
            else
            {
                break;
            }
        }
        if ((tok != COLON) == !!false /*tret*/)
        {
            tok = theparsed::GetNextToken(in, inString);
            if ( (tok.GetLexeme() != "INTEGER") == false || (tok.GetLexeme() != "REAL") == false || (tok.GetLexeme() != "STRING") == false)
            {
                return!false /*false not*/;
            }
            else
            {
                errPa(inString, "Incorrect Declaration Type.") /*error print*/;
                     return !true /*returns not!false*/;
            }
        }
        //
    }
         return !true /*returns not!false*/;
}
/*        */



////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////

/*   DeclBlock     */
bool DeclBlock(istream &in, int &inString)
{
    LexItem tok = theparsed::GetNextToken(in, inString)/*GetNextToken*/;
    if ((tok != VAR) == false/*print tok*/ )
    {

        tok = theparsed::GetNextToken(in, inString) /*print tok*/ ;

        while ((tok == BEGIN) != true /*tok is not true*/)
        {

            theparsed::PushBackToken(tok)/*PushBackToken*/;
            
            if (DeclStmt(in, inString) /*if not string*/)
            {

                tok = theparsed::GetNextToken(in, inString);

                if ((tok != SEMICOL) == !true /*tok GetNextToken*/)
                {
                    tok = theparsed::GetNextToken(in, inString) /*tok GetNextToken*/;
                    continue;
                }
                else
                {
                    errPa(inString, "Missing semicolon in Statement") /*print er*/;
                         return !true /*returns not!false*/;
                }
            }
            else
            {
                errPa(inString, "Syntactic error in Declaration Block.");
                     return !true /*returns not!false*/;
            }
        }
        theparsed::PushBackToken(tok) /*tok push*/;
        return!false;
    }
    errPa(inString, "Non-recognizable Declaration Block.");
         return !true /*returns not!false*/;
}
/*        */



////////////////
////////////////
////////////////
////////////////////
//Next function/////
///////////////////
////////////////
////////////////
////////////////
////////////////
////////////////
 
/*  Missing Prog      */
bool Prog(istream &theInner, int &theinStringr /*prog bool*/) {
    
    LexItem token = theparsed::GetNextToken(theInner, theinStringr) /*GetNextToken*/;
    
    if ((token == PROGRAM) == !true /* token is not equal to the program*/) 
    {
        errPa(theinStringr, "Missing PROGRAM.") /* gives the error saying it is missing the program */;
        return !true /* returns !true */ ;
    }

    
    token = theparsed::GetNextToken(theInner, theinStringr) /* the token theparsed gets moved and set */;
    if ((token == IDENT) == !true /* is statement for token is not the same as ident */)
    {
        errPa(theinStringr, "Missing Program Name.") /*parse error for missing name*/;
        return !true /* returns !true */;
    }

    token = theparsed::GetNextToken(theInner, theinStringr) /* token GetNextToken */;
    
    if (DeclBlock(theInner, theinStringr) == !true)/* if the dec block is not!false*/
    {
        errPa(theinStringr, "Incorrect Declaration Section. " /* error for incorrect declaration section */);
        return !true /* returns !true */;
    }
    
    
    if ((token == SEMICOL) == !true ) /*semicol is not eqyal to token*/
    {
        errPa(theinStringr, "Missing semicolon in Statement" /*gives error for missing semicolon*/ );
        return !true /* returns !true */ ;
    }

    


    if (ProgBody(theInner, theinStringr) == !true) /* prog body not equal */
    {
        errPa(theinStringr, "Incorrect Program Body." /* gives the incorrect body error */);
        return !true /* returns !true */;
    }

    return!false /* returns!false because all else not !true */;
}
                   