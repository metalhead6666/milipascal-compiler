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
    BEG = 258,
    DO = 259,
    IF = 260,
    THEN = 261,
    ELSE = 262,
    END = 263,
    FORWARD = 264,
    FUNCTION = 265,
    OUTPUT = 266,
    PARAMSTR = 267,
    REPEAT = 268,
    UNTIL = 269,
    VAR = 270,
    VAL = 271,
    WHILE = 272,
    WRITELN = 273,
    PROGRAM = 274,
    ASSIGN = 275,
    NOT = 276,
    OR = 277,
    MULTOP = 278,
    ADDOP = 279,
    RELATIONALOP = 280,
    ID = 281,
    STRING = 282,
    INTEGER = 283,
    REAL = 284,
    RESERVED = 285
  };
#endif
/* Tokens.  */
#define BEG 258
#define DO 259
#define IF 260
#define THEN 261
#define ELSE 262
#define END 263
#define FORWARD 264
#define FUNCTION 265
#define OUTPUT 266
#define PARAMSTR 267
#define REPEAT 268
#define UNTIL 269
#define VAR 270
#define VAL 271
#define WHILE 272
#define WRITELN 273
#define PROGRAM 274
#define ASSIGN 275
#define NOT 276
#define OR 277
#define MULTOP 278
#define ADDOP 279
#define RELATIONALOP 280
#define ID 281
#define STRING 282
#define INTEGER 283
#define REAL 284
#define RESERVED 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 105 "mpacompiler.y" /* yacc.c:1909  */

	struct Program* program;
	char *string;

#line 119 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */