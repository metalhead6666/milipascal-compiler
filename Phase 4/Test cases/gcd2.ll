; Default Declarations
@.strNewLine = private unnamed_addr constant [2 x i8] c"\0A\00"
@.strInt = private unnamed_addr constant [3 x i8] c"%d\00"
@.strDouble = private unnamed_addr constant [6 x i8] c"%.12E\00"
@.str = private unnamed_addr constant [3 x i8] c"%s\00"
@.strTrue = private unnamed_addr constant [5 x i8] c"TRUE\00"
@.strFalse = private unnamed_addr constant [6 x i8] c"FALSE\00"

; Print Declaration
declare i32 @printf(i8*, ...)

@x = common global i32 0
@y = common global i32 0
@z = common global i32 0
@final = common global i32 0

define i32 @main() {
  store i32 1, i32* @x
  store i32 2, i32* @y
  store i32 3, i32* @z
  %1 = load i32* @x
  %2 = load i32* @y
  %3 = add nsw i32 %1, %2
  store i32 3, i32* @final
  %4 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.strInt, i32 0, i32 0), i32 3)
  %5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @.strNewLine, i32 0, i32 0))
  ret i32 0
}
