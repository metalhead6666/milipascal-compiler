; Default Declarations
@.strNewLine = private unnamed_addr constant [2 x i8] c"\0A\00"
@.strInt = private unnamed_addr constant [3 x i8] c"%d\00"
@.strDouble = private unnamed_addr constant [6 x i8] c"%.12E\00"
@.str = private unnamed_addr constant [3 x i8] c"%s\00"
@.strTrue = private unnamed_addr constant [5 x i8] c"TRUE\00"
@.strFalse = private unnamed_addr constant [6 x i8] c"FALSE\00"

; Print Declaration
declare i32 @printf(i8*, ...)

@x = common global double 0.000000e+00
@y = common global double 0.000000e+00
@z = common global double 0.000000e+00
@final = common global double 0.000000e+00

define i32 @main() {
  store double 1.0, double* @x
  store double 2.0, double* @y
  store double 3.0, double* @z
  %1 = load double* @x
  %2 = load double* @y
  %3 = fadd double %1, %2
  %4 = load double* @z
  %5 = fsub double %%3, %4
  %6 = load double* @x
  %7 = load double* @y
  %8 = fadd double %6, %7
  %9 = load double* @x
  %10 = fadd double %%8, %9
  store double 10, double* @final
  %11 = load double* @final
  %12 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([6 x i8]* @.strDouble, i32 0, i32 0), double %11)
  %13 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @.strNewLine, i32 0, i32 0))
  ret i32 0
}
