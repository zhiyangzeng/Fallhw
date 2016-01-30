
-- Assignment 3, CSCE-314
-- Section: 501
-- Student Name: Zhiyang Zeng
-- UIN: 720005338
-- Haskell.org, stackoverflow.com, textbook, lecture slide, learn yourself a little haskell, a friend from 312

module Main where

import Test.HUnit
import System.Exit
import Data.List
import Data.Char

triads :: Int -> [(Int, Int, Int)]
triads 0 = []
triads n = [(x, y, z) | x<-[1..n], y<-[1..n], z<-[1..n], x^2+y^2==z^2] 

perfect :: [Int]
perfect= filter isperfect [x | x<- [1..]]
--perfect= filter ((sum(filter (\x -> (mod n x ==0)) [1..n-1]))==n) [n | n <- [1..]]  --not in scope n

isperfect :: Int-> Bool
isperfect n = (sum(filter (\x -> (mod n x ==0)) [1..n-1]))==n


mergeBy :: (a -> a -> Bool) -> [a] -> [a] -> [a]
mergeBy f a [] = a
mergeBy f [] a = a
mergeBy f (x:xs) (y:ys) = 
	if f x y 
		then x: mergeBy f xs (y:ys) 
		else y: mergeBy f (x:xs) ys

mergeSortBy :: (a -> a -> Bool) -> [a] -> [a]
mergeSortBy f []= []
mergeSortBy f [a]=[a]
mergeSortBy f ls = mergeBy f (mergeSortBy f xs)(mergeSortBy f ys) where
	(xs, ys)=splitAt (div (length ls) 2) ls

mergeSort :: Ord a => [a] -> [a]
mergeSort []= []
mergeSort [a]=[a]
mergeSort ls =mergeSort ls = mergeSortBy (<) ls 
--mergeSort ls = mergeBy (<) (mergeSort xs)(mergeSort ys) where
	--(xs, ys)= splitAt (div (length ls) 2) ls


multiply :: [Int] -> Int
multiply = foldr (*) 1

concatenate :: [String] -> String     
concatenate = foldl (++) ""

concatenateAndUpcaseOddLengthStrings :: [String] -> String
concatenateAndUpcaseOddLengthStrings a = concatenate[(map toUpper (oddstr)) | oddstr <- a, odd (length oddstr)]

inserts :: Ord a => a->[a] ->[a]
inserts a [] = [a]
inserts a (x:xs) = 
	case a<=x of 
	True->(a:x:xs)
	False->x:(inserts a xs) 


insertionSort :: Ord a => [a] -> [a]
insertionSort = foldr inserts [] 
--insertionSort ls= [foldr inserts [] x | x<- ls]


maxElementOfAList :: Ord a => [a] -> a 
maxElementOfAList a  = foldr (max) (head a) a
-- foldr works, foldl doesn't?

keepInBetween :: Int -> Int -> [Int] -> [Int]
keepInBetween a b []= []
keepInBetween a b ls= [x | x<-ls, x>=a, x<=b]

--filter (x>=a || x<=b) [x| x<-ls] not in scope

data Tree a b = Branch b (Tree a b) (Tree a b)
              | Leaf a

instance (Show a, Show b) => Show (Tree a b) 
    where 
        show (Leaf a)="leaf "++(show a)
        show (Branch b l r) = "branch " ++ (show b)++"   \n"++ (show r)++"   \n"  ++ (show l) 

preorder :: (a -> c) -> (b -> c) -> Tree a b -> [c]
preorder x y (Leaf a) = [x a]
preorder x y (Branch b l r) = (y b) : (preorder x y l) ++ (preorder x y r) 
			
inorder :: (a -> c) -> (b -> c) -> Tree a b -> [c]
postorder x y (Leaf a) = [x a]
postorder x y (Branch b l r) = (postorder x y l) ++ (postorder x y r) ++ [y b] 

postorder :: (a -> c) -> (b -> c) -> Tree a b -> [c]
inorder x y (Leaf a) = [x a]
inorder x y (Branch b l r) = (inorder x y l) ++ [y b] ++ (inorder x y r) 
			
data E = IntLit Int
       | BoolLit Bool
       | Plus E E
       | Minus E E
       | Multiplies E E
       | Divides E E
       | Equals E E
         deriving (Eq, Show)


intEval :: (Int -> Int -> Int) -> E -> E -> E
intEval f x y = IntLit (f intx inty) 
	where (IntLit intx) = eval x
	      (IntLit inty) = eval y

eqEval :: E -> E -> Bool
eqEval (IntLit intx) (IntLit inty) = intx == inty
eqEval (BoolLit boolx) (BoolLit booly) = boolx == booly

eval :: E -> E
eval (BoolLit x) = (BoolLit x)
eval (IntLit x) = (IntLit x) 
eval (Plus x y) = intEval (+) x y 
eval (Minus x y) = intEval (-) x y 
eval (Multiplies x y) = intEval (*) x y 
eval (Divides x y) = intEval div x y 
eval (Equals x y) = BoolLit (eqEval (eval x) (eval y))

mytree = Branch "A" 
           (Branch "B" 
              (Leaf 1) 
              (Leaf 2)) 
           (Leaf 3)

program = Equals 
            (Plus (IntLit 1) (IntLit 2))
            (Minus
             (IntLit 5)
             (Minus (IntLit 3) (IntLit 1)))
    
myTestList =

  let te s e a = test $ assertEqual s e a
      tb s b = test $ assertBool s b

  in
    TestList [ 
        tb "triads 1" $ [(3, 4, 5)] == triads 5
      , tb "triads 2" $ [(3, 4, 5), (6, 8, 10)] == ( sort $ triads 10)

      , tb "perfect" $ take 3 perfect == [6, 28, 496]
        
      , te "mergeSort 1" " adhllowy" (mergeSort "howdy all") 
      , te "mergeSort 2" "" (mergeSort "") 
      , te "mergeSort 3" "x" (mergeSort "x") 
        
      , te "mergeSortBy 1" " 'eggim" (mergeSortBy (<) "gig 'em") 
      , te "mergeSortBy 2" "nmlkieecbbaJ  " (mergeSortBy (>) "Jack be nimble")
      , te "mergeSortBy 3" "" (mergeSortBy (<) "")

      , te "multiply" 10 (multiply [-2, -1, 5])
      , te "concatenate" "ABCD" (concatenate ["AB", "", "", "C", "D", ""])

      , te "concatenateAndUpcaseOddLengthStrings"
          "HERE'S AN EXAMPLE" (concatenateAndUpcaseOddLengthStrings ["here's ", "an ", "a ", "example"])

      , te "insertionSort" "  Jabcceikkqu" (insertionSort "Jack be quick")
      , te "max in a list" 100 (maxElementOfAList [3, 100, 0])
      , te "keepInBetween" [3,0,20,2] (keepInBetween 0 20 [77, 3, -1, 0, 21, 20, -9, 2])

      , te "preorder" "AB123" (concatenate (preorder show id mytree))
      , te "postrder" "12B3A" (concatenate (postorder show id mytree))
      , te "inorder" "1B2A3" (concatenate (inorder show id mytree))

      , te "eval" (BoolLit True) (eval program)
      ]

main = do c <- runTestTT myTestList
          putStrLn $ show c
          let errs = errors c
              fails = failures c
          exitWith (codeGet errs fails)
          
codeGet errs fails
 | fails > 0       = ExitFailure 2
 | errs > 0        = ExitFailure 1
 | otherwise       = ExitSuccess
