
-- Assignment 4, CSCE-314
-- Section: PUT YOUR SECTION HERE
-- Student Name: PUT YOUR NAME HERE
-- UIN: PUT YOUR UIN HERE
-- (Acknowledge any help received here)

module Main where

import Prelude hiding (lookup)

import Test.HUnit
import System.Exit

-- AST definition for W
data WValue = VInt Int 
            | VBool Bool 
              deriving (Eq, Show)

data WExp = Val WValue
          | Var String

          | Plus WExp WExp
          | Minus WExp WExp
          | Multiplies WExp WExp
          | Divides WExp WExp

          | Equals WExp WExp
          | NotEqual WExp WExp
          | Less WExp WExp
          | Greater WExp WExp
          | LessOrEqual WExp WExp
          | GreaterOrEqual WExp WExp
		  | IsEven WExp
		  | Mod WExp WExp

          | And WExp WExp
          | Or WExp WExp
          | Not WExp

data WStmt = Empty
           | VarDecl String WExp
           | Assign String WExp
           | If WExp WStmt WStmt
           | While WExp WStmt
           | Block [WStmt]

type Memory = [(String, WValue)]
marker = ("|", undefined)
isMarker (x, _) = x == "|"

intEval :: (Int -> Int -> Int) -> WExp -> WExp -> Memory -> WValue 
--intEval _ _ _ [] = error $ "empty memory"
intEval f x y m = VInt(f ix iy) 
				where
					(VInt ix)= (eval x m)
					(VInt iy)= (eval y m)

boolEval :: (Int-> Int -> Bool) -> WExp -> WExp -> Memory -> WValue 
boolEval f a b m = VBool(f ia ib) 
				where (VInt ia) = (eval a m)
				      (VInt ib) = (eval b m)
					  
relationEval :: (Bool->Bool->Bool)->WExp->WExp->Memory->WValue
relationEval f x y m= VBool (f bx by) 
					where (VBool bx)= (eval x m)
					      (VBool by)= (eval y m)
-- eval function
eval :: WExp -> Memory -> WValue
eval (Val (VInt x)) m = (VInt x)
eval (Val (VBool x)) m = (VBool x)
eval (Var x) m = fromJust (lookup x m)
eval (Plus x y) m = intEval (+) x y m
eval (Minus x y) m = intEval (-) x y m
eval (Multiplies x y)m = intEval (*) x y m
eval (Divides x y) m = intEval div x y m
eval (Equals x y) m = boolEval (==) x y m
eval (NotEqual x y) m = VBool(not (ix==iy))
	  				where (VInt ix) = (eval x m)
	  				      (VInt iy) = (eval y m)
eval (Less x y) m = boolEval (<) x y m
eval (Greater x y) m = boolEval (>) x y m
eval (LessOrEqual x y) m = boolEval (<=) x y m
eval (GreaterOrEqual x y) m = boolEval (>=) x y m
eval (And x y) m= relationEval (&&) x y m
eval (Or x y) m= relationEval (||) x y m
eval (Not x) m= VBool (not(bx))
			  where (VBool bx) = eval x m
-- new function for hailstone sequence
eval (IsEven x) m = VBool (even (bx))
                 where (VInt bx)=eval x m
--new function for testing
eval (Mod x y)m = intEval mod x y m

-- exec function
exec :: WStmt -> Memory -> Memory

exec Empty m = m

exec (VarDecl s e) m
      | elem s (map fst m) = error $ s++": variable already in memory, please use assign"
	  | otherwise = (s, ve):m 
	  	where ve= eval e m
								

exec (Assign s e) m  = rFDF s (eval e m) m     --string var name and expression
	where rFDF _ _ [] = error $ "Undefined variable "++s   --memory is empty  
	      rFDF s v (x@(k,_):xs)
		     |s==k = if sameKind v x then (k, v):xs  --var name existed in memory, override
                     else error "Type error in assignment"
			 |otherwise = x: rFDF s v xs
			 where sameKind v@(VInt _) x@(_, VInt _)=True--x is pair with key and type
			       sameKind v@(VBool _) x@(_, VBool _)=True 
			       sameKind _ _=False
				  
exec (If cond stmta stmtb) m =
	if vcond then exec stmta m
		else exec stmtb m
		 where (VBool vcond) = eval cond m

exec (While cond stmt) m = if vcond then exec (While cond stmt) (exec stmt m)
						   else m
								where (VBool vcond)= eval cond m
				  

exec (Block ss) m = popMarker $              --pop after statements are done, clear memory
	foldr exec (marker:m)(reverse ss)   
	where popMarker [] = []
	      popMarker (x:xs) = if (isMarker x) then xs    --poped x
	                         else popMarker xs
	
fibonacci :: Int-> Int
fibonacci 0=0
fibonacci 1=1
fibonacci n= asInt(fromJust (lookup "result" (exec func [("result", VInt 0), ("n", VInt (n-1))]))) 
  where 
	 func= Block
	    [
	    VarDecl "i" (Val (VInt 0)),
	    VarDecl "n1" (Val (VInt 0)),
	    VarDecl "n2" (Val (VInt 1)),
	    While (Less (Var "i") (Var "n"))
	    (
	      Block
	 	 [
	 	 	Assign "result" (Plus (Var "n1") (Var "n2")),
	 		Assign "n1" (Var "n2"),
	 	    Assign "n2" (Var "result"),
	 		Assign "i" (Plus (Var "i") (Val (VInt 1)))
	 	 ]	   
	    )
	    ]
				

   
   
-- example programs
prog1 = Block
     [
       VarDecl "x" (Val (VInt 0)),
       VarDecl "b" (Greater (Var "x") (Val (VInt 0))),
       If (Or (Var "b") (Not (GreaterOrEqual (Var "x") (Val (VInt 0)))))
         ( Block [ Assign "x" (Val (VInt 1)) ] )
         ( Block [ Assign "x" (Val (VInt 2)) ] )
     ]

prog2 = Block [
    VarDecl "x" (Val (VInt 5)),
	Assign "x" (Val (VInt 1)), 
	If (NotEqual (Plus (Var "x") (Val (VInt 2))) (Val (VInt 3)))
    ( Block [ Assign "x" (Val (VInt 1)) ] )
    ( Block [ Assign "x" (Val (VInt 2)) ] ),
	Assign "result" (Var "x")
	]
	

	   
prog6= Block [
	    VarDecl "x" (Val (VInt 4)),
	    VarDecl "y" (Val (VInt 8)),
		Assign "result1" (Plus (Var "x") (Var "y")),
		Assign "result2" (Minus (Var "x") (Var "y")),
		Assign "result3" (Multiplies (Var "x") (Var "y")),
		If (Equals (Mod (Var "y") (Var "x")) (Val (VInt 0)))
	    ( Block [ Assign "factor" (Val (VBool True)) ] )
	    ( Block [ Assign "factor" (Val (VBool False)) ] )
       ]	
	      
prog7= Block [
	    VarDecl "x" (Val (VInt 23)),
	    VarDecl "y" (Val (VInt 25)),
	    VarDecl "z" (Val (VInt 33)),
		
        Assign "result" (Plus (Var "x") (Minus (Multiplies (Val (VInt 7)) (Divides (Var "z") (Var "y"))) (Var "z")))

       ]	
	      
prog8= Block [--nested if
	    
		If (NotEqual (Mod (Var "y") (Var "x")) (Val (VInt 0)))
	    ( Block [
			If (Or (IsEven (Var "x")) (Not (IsEven (Var "y")) ) )
			(Block [Assign "result" (Val (VInt 1))])
			(Block [Assign "result" (Val (VInt (-1)))])
		  ] )
	    ( Block [ Assign "result" (Val (VInt 0)) ] )

       ]	
	      
power= Block [ --power x^n
        If ( (Equals (Val (VInt 0)) (Var "n")) )
	    ( Block [ Assign "x" (Val (VInt 1)) ] )
	    ( Block [  
   	    	VarDecl "i" (Val (VInt 1)),
		    While (Less (Var "i") (Var "n"))(
			 Block[
			  Assign "x" (Multiplies (Var "x") (Var "x")),
  	 		  Assign "i" (Plus (Var "i") (Val (VInt 1)))
			 ]
			)
		  ] )
       ]	--2?
	      
pythagorean= Block [ 
	    Assign "result" (Equals (Multiplies (Var "z") (Var "z")) (Plus (Multiplies (Var "x") (Var "x")) (Multiplies (Var "y") (Var "y")) ))
		
       ]	
	   
	   	   	   
hailstone= Block [ 
		While( NotEqual (Var "x") (Val (VInt 1)))
		(
			Block [
			If (IsEven (Var "x"))
		    ( Block [ Assign "x" (Divides (Var "x") (Val (VInt 2)))])
		    ( Block [ Assign "x" (Plus (Val (VInt 1)) (Multiplies (Var "x") (Val (VInt 3))))]),
			Assign "result" (Plus (Var "result") (Val (VInt 1)))
			] 
		)
       ]
	 
	      
prog11= Block [
	    VarDecl "x" (Val (VInt 2)),
	    VarDecl "y" (Val (VInt 4)),
		Assign "result"  (Multiplies (Minus (Var "x") (Var "y")) (Val (VInt (-1))))
       ]	  
	   
prog3 = Block [ 
    VarDecl "x" (Val (VInt 4)),
    VarDecl "y" (Val (VInt 8)),
	If (LessOrEqual (Plus (Var "x") (Val (VInt 2))) (Var "y"))
    ( Block [ Assign "result" (Val (VBool True)) ] )
    ( Block [ Assign "result" (Val (VBool False)) ] )
	]
	    
mux= Block [
        If (Equals (Val (VInt 0)) (Var "selection") )
		(Block [Assign "result" (Var "a") ])
		(Block [Assign "result" (Var "b") ])

       ]	 
	   
prog4= Block [
	    VarDecl "x" (Val (VInt 5)),
	    VarDecl "y" (Val (VInt 4)),
		Assign "result1" (Less (Var "x") (Var "y")), --False
		Assign "result2" (GreaterOrEqual (Var "x")(Var "y")),--True
		Assign "result3" (Not (And (Less (Var "x")(Var "y")) (GreaterOrEqual (Var "x") (Var "y")))), --True
		Assign "result4" ((Or (Less (Var "x") (Var "y")) (GreaterOrEqual (Var "x") (Var "y")) ) ) --T

       ]
	  	       
prog15= Block [
	    VarDecl "x" (Val (VInt 4)),
	    VarDecl "y" (Val (VInt 5)),
		Assign "result" (Mod (Multiplies (Var "x") (Var "y")) (Val (VInt 6)))

       ]	
    
xor= Block [ --xor the hard way
--Not ( Or (Not(ORab) Andab) 
        Assign "result1" (Not( (Or (And (Var "x1")  (Var "x2")) (Not ( Or (Var "x1") (Var "x2")  ))) )),
        Assign "result2" (Not( (Or (And (Var "y1")  (Var "y2")) (Not ( Or (Var "y1") (Var "y2")  ))) ))
		
       ]
	        
prog16= Block [
	    VarDecl "x" (Val (VInt 131)),
	    VarDecl "y" (Val (VInt 54)),
		Assign "result" (Divides (Mod (Var "x") (Var "y")) (Val (VInt 3)) )
       ] 
	   	     
perfect= Block [--perfect
	     VarDecl "sum" (Val (VInt 0)),	
	     VarDecl "i" (Val (VInt 1)),		
	
	     While (Less (Var "i") (Var "x"))(
		 Block[
          If ( (Equals (Val (VInt 0)) (Mod (Var "x") (Var "i"))) )
          ( Block [ Assign "sum" (Plus (Var "sum") (Var "i") ) ] )
          ( Block [Empty] ),
		  
		  Assign "i" (Plus (Var "i") (Val (VInt 1)))
		 ]
		),
		If (Equals (Var "x") (Var "sum"))
	    ( Block [ Assign "result" (Val (VBool True)) ] )
	    ( Block [ Assign "result" (Val (VBool False)) ] )
       ]
	   
factorial = 
  Block
  [
    VarDecl "acc" (Val (VInt 1)),
    While (Greater (Var "arg") (Val (VInt 1)))
    (
      Block
      [
        Assign "acc" (Multiplies (Var "acc") (Var "arg")),
        Assign "arg" (Minus (Var "arg") (Val (VInt 1)))         
      ]
    ),
    Assign "result" (Var "acc")
  ]
-- some useful helper functions
lookup s [] = Nothing
lookup s ((k,v):xs) | s == k = Just v
                    | otherwise = lookup s xs

asInt (VInt v) = v
asInt x = error $ "Expected a number, got " ++ show x

asBool (VBool v) = v
asBool x = error $ "Expected a boolean, got " ++ show x

fromJust (Just v) = v
fromJust Nothing = error "Expected a value in Maybe, but got Nothing"

-- unit tests
myTestList =
  TestList [
    test $ assertEqual "prog1 test" [] (exec prog1 []),
    test $ assertEqual "prog2 test" [("result", VInt (2))] (exec prog2 [("result", VInt (0))]),
    test $ assertEqual "prog3 test" [("result", VBool True)] (exec prog3 [("result", VBool True)]),
    test $ assertEqual "prog4 test" [("result1", VBool False),("result2", VBool True),("result3", VBool True),("result4", VBool True)] (exec prog4 [("result1", VBool True),("result2", VBool True),("result3", VBool True),("result4", VBool True)]),
    test $ assertEqual "hailstone test" [("x", VInt (1)),("result", VInt (25))] (exec hailstone [("x", VInt (100)),("result", VInt (0))]),
    test $ assertEqual "prog6 test" [("result1", VInt (12)),("result2", VInt (-4)),("result3", VInt (32)),("factor", VBool True)] (exec prog6 [("result1", VInt (0)),("result2", VInt (0)),("result3", VInt (0)),("factor", VBool False)]),
    test $ assertEqual "prog7 test" [("result", VInt (-3))] (exec prog7 [("result", VInt (0))]),
    test $ assertEqual "prog8 test" [("result", VInt (1)),("x", VInt 10),("y", VInt 14)] (exec prog8 [("result", VInt (0)),("x", VInt 10),("y", VInt 14)]),
    test $ assertEqual "power test" [("x", VInt (3014151301029068801)), ("n", VInt (14))] (exec power [("x", VInt 3), ("n", VInt (14))]),
    test $ assertEqual "pythagorean test" [("result", VBool True),("x", VInt 29),("y", VInt 420),("z", VInt 421)] (exec pythagorean [("result", VBool False),("x", VInt 29),("y", VInt 420),("z", VInt 421)]),
    test $ assertEqual "prog11 test" [("result", VInt (2))] (exec prog11 [("result", VInt (0))]),
    test $ assertEqual "mux test" [("result", VInt (-99)),("selection", VInt (1)),("a", VInt (99)),("b", VInt (-99))] (exec mux [("result", VInt (0)),("selection", VInt (1)),("a", VInt (99)),("b", VInt (-99))]),
    test $ assertEqual "xor test" [("result1", VBool False),("x1", VBool True),("x2", VBool True),("result2", VBool True),("y1", VBool True),("y2", VBool False)] (exec xor [("result1", VBool True),("x1", VBool True),("x2", VBool True),("result2", VBool False),("y1", VBool True),("y2", VBool False)]),
    test $ assertEqual "perfect test" [("result", VBool True),("x", VInt 28)] (exec perfect [("result", VBool False),("x", VInt 28)]),
    test $ assertEqual "prog15 test" [("result", VInt (2))] (exec prog15 [("result", VInt (0))]),
    test $ assertEqual "prog16 test" [("result", VInt (7))] (exec prog16 [("result", VInt (0))]),
	
    let res = lookup "result" (exec factorial [("result", VInt (-1)), ("arg", VInt 10)])
    in test $ assertBool "factorial of 10" (3628800 == asInt (fromJust res))
    ]    

-- main: run the unit tests  
main = do c <- runTestTT myTestList
          putStrLn $ show c
          let errs = errors c
              fails = failures c
          if (errs + fails /= 0) then exitFailure else return ()

