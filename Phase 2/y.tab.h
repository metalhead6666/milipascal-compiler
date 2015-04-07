/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    RESERVED = 258,
    REAL = 259,
    INTEGER = 260,
    BEG = 261,
    DO = 262,
    IF = 263,
    THEN = 264,
    ELSE = 265,
    END = 266,
    FORWARD = 267,
    FUNCTION = 268,
    OUTPUT = 269,
    PARAMSTR = 270,
    REPEAT = 271,
    UNTIL = 272,
    VAR = 273,
    VAL = 274,
    WHILE = 275,
    WRITELN = 276,
    PROGRAM = 277,
    ASSIGN = 278,
    NOT = 279,
    OP2 = 280,
    OP3 = 281,
    OP4 = 282,
    ID = 283,
    STRING = 284,
    IFX = 285
  };
#endif
/* Tokens.  */
#define RESERVED 258
#define REAL 259
#define INTEGER 260
#define BEG 261
#define DO 262
#define IF 263
#define THEN 264
#define ELSE 265
#define END 266
#define FORWARD 267
#define FUNCTION 268
#define OUTPUT 269
#define PARAMSTR 270
#define REPEAT 271
#define UNTIL 272
#define VAR 273
#define VAL 274
#define WHILE 275
#define WRITELN 276
#define PROGRAM 277
#define ASSIGN 278
#define NOT 279
#define OP2 280
#define OP3 281
#define OP4 282
#define ID 283
#define STRING 284
#define IFX 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 12 "mpaparser.y" /* yacc.c:1909  */

	struct _Program* program;
	struct _VarPart* varPart;
	struct _VarDecl* varDecl;
	struct _IdStruct* ids;
	struct _FuncPart* funcPart;
	struct _FuncDecl* funcDecl;
	struct _FuncDef* funcDef;
	struct _FuncDef2* funcDef2;
	struct _FuncParams* funcParams;
	struct _Params* params;
	struct _VarParams* varParams;
	Terminals type;
	Operators ops;

	char *string;
	int value;

#line 133 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
