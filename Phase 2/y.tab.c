/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "mpaparser.y" /* yacc.c:339  */

	#include <string.h>
	#include "functions.h"
	#include "print.h"

	void yyerror(char *s);

	/* values received from lex */
	extern char *yytext;
	extern int count_line, count_column;

	/* node root to print in the tree */
	Program* program;

	/* in case some syntax error appears, doesn't print the AST */
	int hasErrors = 0;

#line 84 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 83 "mpaparser.y" /* yacc.c:355  */

	struct ProgBlock* progBlock;
	struct VarPart* varPart;
	struct FuncPart* funcPart;
	struct IdStruct* idStruct;
	struct VarDecl* varDecl;
	struct FuncDeclaration* funcDeclaration;
	struct FuncHeading *funcHeading;
	struct FormalParamList *formalParamList;
	struct FormalParams *formalParams;
	struct StatList *statList;
	struct Stat *stat;
	struct Expr *expr;
	struct WriteInPList *writeInPList;
	struct Optional *optional;
	struct Term *term;
	struct SimpleExpr *simpleExpr;
	struct Factor *factor;
	struct ParamList *paramList;
	char *string;

#line 206 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 221 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   138

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  138

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      33,    34,     2,     2,    36,     2,    32,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    35,    31,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   106,   106,   109,   112,   115,   116,   119,   120,   123,
     126,   127,   130,   131,   134,   135,   136,   139,   142,   143,
     146,   147,   150,   151,   154,   157,   160,   161,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   175,   176,   179,
     180,   183,   184,   187,   188,   191,   192,   193,   194,   197,
     200,   201,   204,   205,   206,   207,   208,   209,   212,   215,
     216
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BEG", "DO", "IF", "THEN", "ELSE", "END",
  "FORWARD", "FUNCTION", "OUTPUT", "PARAMSTR", "REPEAT", "UNTIL", "VAR",
  "VAL", "WHILE", "WRITELN", "PROGRAM", "ASSIGN", "NOT", "OR", "MULTOP",
  "ADDOP", "RELATIONALOP", "ID", "STRING", "INTEGER", "REAL", "RESERVED",
  "';'", "'.'", "'('", "')'", "':'", "','", "$accept", "Prog",
  "ProgHeading", "ProgBlock", "varPart", "VarDeclarationRepeat",
  "VarDeclaration", "IDList", "funcPart", "FuncDeclaration", "FuncHeading",
  "FormalParamList", "FormalParamListRepeat", "FormalParams", "StatPart",
  "StatList", "StatListRepeat", "Stat", "WriteInPList",
  "WriteInPListOptional", "Optional", "Expr", "SimpleExpr", "Term",
  "TermRepeat", "Factor", "ParamList", "ParamListOptional", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    59,    46,    40,    41,    58,    44
};
# endif

#define YYPACT_NINF -76

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-76)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -13,    -7,    27,    -2,     0,   -76,    21,    28,    16,    12,
      37,    14,    19,    22,   -76,    30,    60,    34,    39,   -76,
      42,    38,    16,    -3,     5,   -76,    37,    -4,    19,    48,
     -76,    44,    21,    -6,    45,    43,     5,    46,    43,    49,
      57,   -76,    73,    52,   -76,   -76,    60,   -76,   -76,    16,
      60,    58,    19,    54,    61,    17,    17,    55,   -76,   -76,
      43,    83,    65,    10,    68,    78,    81,    90,    33,   -76,
      43,   -76,     5,   -76,   -76,   -76,   -76,    19,    62,    -6,
      64,   -76,   -76,   -76,    43,   -76,    66,     5,    43,    43,
      43,    17,   -76,    43,    63,     5,   -76,    59,   -76,   -76,
      52,    67,    75,    54,   -76,    69,   -76,    92,   -76,   -76,
     -76,    68,   -76,    43,   -76,    33,    70,   -76,    77,   -76,
     -76,    43,    72,     5,   -76,    74,    59,   -76,   -76,    69,
     -76,   -76,    71,   -76,   -76,    84,    79,   -76
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     1,     6,     0,     0,     0,
      13,     0,    11,     0,     2,     0,     0,     0,     0,     3,
       0,     0,     8,    19,    36,     4,    13,     6,    11,     0,
       5,     0,     6,     0,     0,     0,    36,     0,     0,    38,
       0,    28,     0,    27,    12,    14,     0,    10,     9,     8,
       0,     0,    11,    21,     0,     0,     0,    56,    54,    55,
       0,     0,    43,    48,    51,     0,     0,     0,     0,    35,
       0,    24,    36,    25,    16,     7,    15,    11,     0,     0,
       0,    17,    53,    45,     0,    57,     0,    36,     0,     0,
       0,     0,    49,     0,     0,    36,    42,    40,    41,    34,
      27,     0,     0,    21,    18,    60,    52,    29,    44,    47,
      46,    51,    32,     0,    31,     0,     0,    26,     0,    22,
      20,     0,     0,    36,    50,     0,    40,    37,    23,    60,
      58,    30,     0,    39,    59,     0,     0,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -76,   -76,   -76,   -76,   -15,    76,   101,   -26,    85,   -76,
     -76,   -76,     9,    35,    -9,    80,    15,   -71,   -76,    -8,
       2,   -35,   -75,    82,     8,   -51,   -76,    -5
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     9,    10,    30,    31,    21,    16,    17,
      18,    34,    80,    53,    41,    42,    73,    43,    69,   116,
      97,    98,    62,    63,    92,    64,    85,   122
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      61,   100,    47,    67,    82,    45,     1,    25,    24,    51,
      35,     8,    46,   108,   109,   110,   107,    50,    36,     4,
      52,    37,    38,    39,   114,    86,    78,     5,    32,     6,
      33,    40,    89,     7,    90,    99,     8,    74,    55,    11,
     111,    76,    12,    57,    14,    58,    59,    15,    19,   105,
      60,   101,   131,    22,    55,    20,    23,    56,   112,    57,
      96,    58,    59,    24,    55,    26,    60,    56,    28,    57,
      27,    58,    59,    29,    48,    49,    60,    70,   125,    66,
      54,    71,    68,    72,    77,    79,   129,    81,    84,    87,
      88,    91,    93,    94,    95,   115,   113,   102,   104,   123,
     106,   119,   118,   128,   127,   121,   130,   135,   132,    13,
     136,    44,   120,   137,   103,   117,    65,   126,   133,   124,
       0,     0,     0,     0,   134,    75,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    83
};

static const yytype_int16 yycheck[] =
{
      35,    72,    28,    38,    55,     9,    19,    16,     3,    15,
       5,    15,    27,    88,    89,    90,    87,    32,    13,    26,
      26,    16,    17,    18,    95,    60,    52,     0,    31,    31,
      33,    26,    22,    33,    24,    70,    15,    46,    21,    11,
      91,    50,    26,    26,    32,    28,    29,    10,    34,    84,
      33,    77,   123,    31,    21,    36,    26,    24,    93,    26,
      27,    28,    29,     3,    21,    31,    33,    24,    26,    26,
      31,    28,    29,    35,    26,    31,    33,    20,   113,    33,
      35,     8,    33,    31,    26,    31,   121,    26,    33,     6,
      25,    23,    14,    12,     4,    36,    33,    35,    34,     7,
      34,    26,    35,    26,    34,    36,    34,    36,    34,     8,
      26,    26,   103,    34,    79,   100,    36,   115,   126,   111,
      -1,    -1,    -1,    -1,   129,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    38,    39,    26,     0,    31,    33,    15,    40,
      41,    11,    26,    43,    32,    10,    45,    46,    47,    34,
      36,    44,    31,    26,     3,    51,    31,    31,    26,    35,
      42,    43,    31,    33,    48,     5,    13,    16,    17,    18,
      26,    51,    52,    54,    45,     9,    41,    44,    26,    31,
      41,    15,    26,    50,    35,    21,    24,    26,    28,    29,
      33,    58,    59,    60,    62,    52,    33,    58,    33,    55,
      20,     8,    31,    53,    51,    42,    51,    26,    44,    31,
      49,    26,    62,    60,    33,    63,    58,     6,    25,    22,
      24,    23,    61,    14,    12,     4,    27,    57,    58,    58,
      54,    44,    35,    50,    34,    58,    34,    54,    59,    59,
      59,    62,    58,    33,    54,    36,    56,    53,    35,    26,
      49,    36,    64,     7,    61,    58,    57,    34,    26,    58,
      34,    54,    34,    56,    64,    36,    26,    34
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    39,    40,    41,    41,    42,    42,    43,
      44,    44,    45,    45,    46,    46,    46,    47,    48,    48,
      49,    49,    50,    50,    51,    52,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    59,    59,    59,    60,
      61,    61,    62,    62,    62,    62,    62,    62,    63,    64,
      64
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     5,     3,     4,     0,     3,     0,     4,
       3,     0,     3,     0,     3,     5,     4,     5,     4,     0,
       3,     0,     4,     5,     3,     2,     3,     0,     1,     4,
       6,     4,     4,     9,     3,     2,     0,     4,     0,     3,
       0,     1,     1,     1,     3,     2,     3,     3,     1,     2,
       3,     0,     3,     2,     1,     1,     1,     2,     4,     3,
       0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 106 "mpaparser.y" /* yacc.c:1646  */
    {program = makeNode((yyvsp[-3].string), (yyvsp[-1].progBlock));}
#line 1388 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 109 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.string) = (yyvsp[-3].string);}
#line 1394 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 112 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.progBlock) = addProgBlock((yyvsp[-2].varPart), (yyvsp[-1].funcPart), (yyvsp[0].statList));}
#line 1400 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 115 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.varPart) = addVarPart((yyvsp[0].varPart), (yyvsp[-2].varDecl));}
#line 1406 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 116 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.varPart) = NULL;}
#line 1412 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 119 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.varPart) = addVarPart((yyvsp[0].varPart), (yyvsp[-2].varDecl));}
#line 1418 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 120 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.varPart) = NULL;}
#line 1424 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 123 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.varDecl) = addVarDecl((yyvsp[-3].string), (yyvsp[0].string), (yyvsp[-2].idStruct));}
#line 1430 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 126 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.idStruct) = addIdStruct((yyvsp[0].idStruct), (yyvsp[-1].string));}
#line 1436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 127 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.idStruct) = NULL;}
#line 1442 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 130 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.funcPart) = addFuncPart((yyvsp[0].funcPart), (yyvsp[-2].funcDeclaration));}
#line 1448 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 131 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.funcPart) = NULL;}
#line 1454 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 134 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.funcDeclaration) = addFuncDeclaration(NULL,NULL,(yyvsp[-2].funcHeading), 1, NULL);}
#line 1460 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 135 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.funcDeclaration) = addFuncDeclaration((yyvsp[-1].varPart),(yyvsp[-3].string),NULL, 2, (yyvsp[0].statList));}
#line 1466 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 136 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.funcDeclaration) = addFuncDeclaration((yyvsp[-1].varPart),NULL,(yyvsp[-3].funcHeading), 1, (yyvsp[0].statList));}
#line 1472 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 139 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.funcHeading) = addFuncHeading((yyvsp[-3].string), (yyvsp[-2].formalParamList), (yyvsp[0].string));}
#line 1478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 142 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.formalParamList) = addFormalParamList((yyvsp[-2].formalParams),(yyvsp[-1].formalParamList));}
#line 1484 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 143 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.formalParamList) = NULL;}
#line 1490 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 146 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.formalParamList) = addFormalParamList((yyvsp[-1].formalParams),(yyvsp[0].formalParamList));}
#line 1496 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 147 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.formalParamList) = NULL;}
#line 1502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 150 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.formalParams) = addFormalParams((yyvsp[-3].string),(yyvsp[-2].idStruct),(yyvsp[0].string));}
#line 1508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 151 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.formalParams) = addFormalParams((yyvsp[-3].string),(yyvsp[-2].idStruct),(yyvsp[0].string));}
#line 1514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 154 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.statList) = (yyvsp[-1].statList);}
#line 1520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 157 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.statList) = addStatList((yyvsp[-1].stat),(yyvsp[0].statList));}
#line 1526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 160 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.statList) = addStatList((yyvsp[-1].stat),(yyvsp[0].statList));}
#line 1532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 161 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.statList) = NULL;}
#line 1538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 164 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.stat) = addStat(NULL,NULL,NULL,NULL,(yyvsp[0].statList),2, StatList1);}
#line 1544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 165 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.stat) = addStat((yyvsp[-2].expr),(yyvsp[0].stat),NULL,NULL,NULL,3, IfElse);}
#line 1550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 166 "mpaparser.y" /* yacc.c:1646  */
    {if((yyvsp[-2].stat) != NULL) (yyvsp[-2].stat)->next = (yyvsp[0].stat); else (yyvsp[-2].stat) = (yyvsp[0].stat); (yyval.stat) = addStat((yyvsp[-4].expr),(yyvsp[-2].stat),NULL,NULL,NULL,3, IfElse);}
#line 1556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 167 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.stat) = addStat((yyvsp[-2].expr),(yyvsp[0].stat),NULL,NULL,NULL,3, While);}
#line 1562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 168 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.stat) = addStat((yyvsp[0].expr),NULL,NULL,NULL,(yyvsp[-2].statList),2, Repeat);}
#line 1568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 169 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.stat) = addStat((yyvsp[-4].expr),NULL,NULL,(yyvsp[-1].string),NULL,1, ValParam);}
#line 1574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 170 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.stat) = addStat((yyvsp[0].expr),NULL,NULL,(yyvsp[-2].string),NULL,1, Assign);}
#line 1580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 171 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.stat) = addStat(NULL,NULL,(yyvsp[0].writeInPList),NULL,NULL,3, WriteLn);}
#line 1586 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 172 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.stat) = NULL;}
#line 1592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 175 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.writeInPList) = addWriteInPList((yyvsp[-2].optional),(yyvsp[-1].writeInPList));}
#line 1598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 176 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.writeInPList) = NULL;}
#line 1604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 179 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.writeInPList) = addWriteInPList((yyvsp[-1].optional),(yyvsp[0].writeInPList));}
#line 1610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 180 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.writeInPList) = NULL;}
#line 1616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 183 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.optional) = addOptional((yyvsp[0].expr),NULL,1);}
#line 1622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 184 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.optional) = addOptional(NULL,(yyvsp[0].string),2);}
#line 1628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 187 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.expr) = addExpr((yyvsp[0].simpleExpr),NULL,NULL);}
#line 1634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 188 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.expr) = addExpr((yyvsp[-2].simpleExpr),(yyvsp[0].simpleExpr),(yyvsp[-1].string));}
#line 1640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 191 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.simpleExpr) = addSimpleExpr((yyvsp[0].term),(yyvsp[-1].string),NULL, 1);}
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 192 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.simpleExpr) = addSimpleExpr((yyvsp[-2].term),(yyvsp[-1].string),(yyvsp[0].simpleExpr), 2);}
#line 1652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 193 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.simpleExpr) = addSimpleExpr((yyvsp[-2].term),(yyvsp[-1].string),(yyvsp[0].simpleExpr), 2);}
#line 1658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 194 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.simpleExpr) = addSimpleExpr((yyvsp[0].term),NULL,NULL, 0);}
#line 1664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 197 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.term) = addTerm((yyvsp[-1].factor), (yyvsp[0].term), NULL);}
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 200 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.term) = addTerm((yyvsp[-1].factor), (yyvsp[0].term), (yyvsp[-2].string));}
#line 1676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 201 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.term) = NULL;}
#line 1682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 204 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.factor) = addFactor((yyvsp[-1].expr), NULL, NULL, NULL, Nothing);}
#line 1688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 205 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.factor) = addFactor(NULL, NULL, NULL, (yyvsp[0].factor), Not);}
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 206 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.factor) = addFactor(NULL, (yyvsp[0].string), NULL, NULL, IntLit);}
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 207 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.factor) = addFactor(NULL, (yyvsp[0].string), NULL, NULL, RealLit);}
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 208 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.factor) = addFactor(NULL, (yyvsp[0].string), NULL, NULL, Id);}
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 209 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.factor) = addFactor(NULL, (yyvsp[-1].string), (yyvsp[0].paramList), NULL, Id);}
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 212 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.paramList) = addParamList((yyvsp[-2].expr),(yyvsp[-1].paramList));}
#line 1724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 215 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.paramList) = addParamList((yyvsp[-1].expr),(yyvsp[0].paramList));}
#line 1730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 216 "mpaparser.y" /* yacc.c:1646  */
    {(yyval.paramList) = NULL;}
#line 1736 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1740 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 219 "mpaparser.y" /* yacc.c:1906  */

int main(int argc, char **argv){
	yyparse();

	if(argc > 1){
		if(strcmp(argv[1], "-t") == 0 && !hasErrors){
			print_tree(program);
		}
	}

	return 0;
}

void yyerror(char *s){
	hasErrors = 1;
	printf("Line %d, col %d: %s: %s\n", count_line, (int)(count_column - strlen(yytext)), s, yytext);
}

