-- Home Work 2 
-- CS 381 Programming Language Fundamentals 

module HW2 where

import Prelude hiding (Num)

--num	::=	(any natural number)	
--var	::=	(any variable name)	
--macro	::=	(any macro name)	
-- 			
--prog	::=	ε | cmd ; prog	                    sequence of commands
-- 			
--mode	::=	down | up	                        pen status
-- 			
--expr	::=	var	                                variable reference
--        |	num	                                literal number
--        |	expr + expr	                        addition expression
-- 			
--cmd	::=	pen mode	                        change pen mode
--        |	move ( expr , expr )	            move pen to a new position
--        |	define macro ( var* ) { prog }  	define a macro
--        |	call macro ( expr* )	            invoke a macro


-- 1.) Define an abstract sytax of MiniLogo as a set of Haskell data types using built in types for num, var, and macro

type Num = Int

type Var = [Char]

type Macro = [Char]

data Mode = Up 
          | Down 

data Expr = V Var 
          | N Num
          | Add Expr Expr 
   deriving (Eq,Show) 

data Cmd = Pen    Mode
	 | Move   Expr  Expr 
         | Define Macro [Var] Prog 
         | Call   Macro [Expr]

type Prog = [Cmd]



-- 2.) Define a MiniLogo macro line (x1,y1,x2,y2) that draws a line segment from (x1,y1) to (x2,y2).

line :: Prog      
line = [Define "line" ["x1", "x2", "y1", "y2"] 
       [Pen Up, Move (V "x1") (V "y1"), Pen Down, Move (V "x2") (V "y2")]]

-- 3.) Use the line macro you just defined to define a new MiniLogo macro nix (x,y,w,h) that draws a big “X” of width w and height h, starting from position (x,y).

nix :: Prog
nix = [Define "nix" ["x", "y", "w", "h"]
      [Call "line" [V "x", V "y", Add (V "x") (V "w"), Add (V "y") (V "h")],
      Call "line" [Add (V "x") (V "w"), V "y", V "x", Add (V "y") (V "h")]]]

-- 4.) 

steps :: Int -> Prog
steps 0 = [Pen Up, Move (N 0)(N 0), Pen Down]
steps x = steps (x-1) ++ [Move (N x) (N (x+1))] ++ [Move (N (x+1)) (N (x+1))]


-- 5.) 

macros :: Prog -> [Macro]
macros [] = []
macros (x:xs) = case x of
                Define m _ _ -> m:macros xs
                _            -> macros xs

-- 6.)

print_mode :: Mode -> String
print_mode Up   = "up "
print_mode Down = "down " 

pretty :: Prog -> String
pretty [] = ""
pretty (x:xs) = case x of
                Pen a           -> " pen " ++ print_mode a ++ pretty xs
                Move a b        -> " moving to the coordinate (" ++ show a ++ ", " ++ show b ++ ") " ++ pretty xs
                Define a b c    -> " defining " ++ show a ++ " as " ++ pretty c ++ pretty xs
                Call a b        -> " calling " ++ show a ++ pretty xs
		_               -> "NULL " ++ pretty xs
