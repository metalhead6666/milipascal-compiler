; Default Declarations
@.strNewLine = private unnamed_addr constant [2 x i8] c"\0A\00"
@.strInt = private unnamed_addr constant [3 x i8] c"%d\00"
@.strDouble = private unnamed_addr constant [6 x i8] c"%.12E\00"
@.str = private unnamed_addr constant [3 x i8] c"%s\00"
@.strTrue = private unnamed_addr constant [5 x i8] c"TRUE\00"
@.strFalse = private unnamed_addr constant [6 x i8] c"FALSE\00"

; Print Declaration
declare i32 @printf(i8*, ...)

@a = common global i32 0
@b = common global double 0.000000e+00
@c = common global i1 0

define i32 @main() {
  store i32 1, i32* @a
  store double 1.0, double* @b
  %1 = load double* @b
  %2 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([6 x i8]* @.strDouble, i32 0, i32 0), double %1)
  %3 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @.strNewLine, i32 0, i32 0))
  %4 = load double* @a
  %5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([6 x i8]* @.strDouble, i32 0, i32 0), double %4)
  %6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @.strNewLine, i32 0, i32 0))
  ret i32 0
}
