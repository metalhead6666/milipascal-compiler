; Default Declarations
@.strNewLine = private unnamed_addr constant [2 x i8] c"\0A\00"
@.strInt = private unnamed_addr constant [3 x i8] c"%d\00"
@.strDouble = private unnamed_addr constant [6 x i8] c"%.12E\00"
@.str = private unnamed_addr constant [3 x i8] c"%s\00"
@.strTrue = private unnamed_addr constant [5 x i8] c"TRUE\00"
@.strFalse = private unnamed_addr constant [6 x i8] c"FALSE\00"

; Print Declaration
declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

@paramcount = common global i32 0
@paramstr = common global i8** null

@merda = common global double 0.0
@coco = common global double 0.0
@cona = common global double 0.0
@pilaw5 = common global double 0.0
@sdf = common global i1 0
@sdf1 = common global i1 0
@a = common global i32 0

define i32 @pila(i32* %b, double %a) {
  store double 4.0, double* @coco
  ret i32 0
}

define i32 @pila2(i32* %b, double %a) {
  store double 5.0, double* @coco
  ret i32 0
}

define i32 @pila3(i32* %b, double %a) {
  store double 6.0, double* @coco
  ret i32 0
}

define i32 @pila4(i32* %b, double %a) {
  ret i32 0
}

define i32 @main(i32 %argc, i8** %argv) {
  store i32 %argc, i32* @paramcount
  %1 = load i32* @paramcount
  %2 = sub i32 %1, 1
  store i32 %2, i32* @paramcount
  store i8** %argv, i8*** @paramstr
  store double 4.0, double* @coco
  store double 5.0, double* @coco
  store double 6.0, double* @coco
  %3 = load i1* @sdf1
  store i1 0, i1* @sdf1
  %4 = load i1* @sdf
  store i1 1, i1* @sdf
  %5 = load i1* @sdf1
  store i1 %5, i1* @sdf
  store double 1.0e+0, double* @coco
  store double 1.0, double* @merda
  %6 = load double* @merda
  store double %6, double* @coco
  store double 3.0, double* @pilaw5
  %7 = load i8*** @paramstr
  %8 = getelementptr inbounds i8** %7, i32 1
  %9 = load i8** %8
  %10 = call i32 @atoi(i8* %9)
  store i32 %10, i32* @a
  %11 = load i32* @a
  %12 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.strInt, i32 0, i32 0), i32 %11)
  %13 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @.strNewLine, i32 0, i32 0))
  ret i32 0
}
