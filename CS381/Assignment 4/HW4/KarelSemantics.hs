module KarelSemantics where

import Prelude hiding (Either(..))
import Data.Function (fix)

import KarelSyntax
import KarelState

-- type World = Pos -> Maybe Int
-- type Pos = (Int,Int)
-- | Valuation function for Test.

test :: Test -> World -> Robot -> Bool
test (Not x) w r              = case (test x w r) of
								  True -> False
								  _    -> True 
test (Facing d) w (_,d1,_)    = (d == d1)
test (Clear d) w ((x,y),d1,_) =  case (cardTurn d d1) of
		                           North -> isClear((x,y+1)) w
		                           South -> isClear((x,y-1)) w
		                           East  -> isClear((x+1,y)) w
		                           West  -> isClear((x-1,y)) w
test (Beeper) w ((x,y),_,_)   = hasBeeper ((x,y)) w 
test (Empty) w r              = (test (Not Beeper) w r)

--data Result = OK    World Robot
--            | Done  Robot
--            | Error String

--type Robot = (Pos,Card,Int)

-- | Valuation function for Stmt.
stmt :: Stmt -> Defs -> World -> Robot -> Result
stmt Shutdown   _ _ r     = Done r
stmt PickBeeper _ w r     = let p = getPos r
                              in if hasBeeper p w
                                then OK (decBeeper p w) (incBag r)
                                else Error ("No beeper to pick at: " ++ show p)
stmt Move _ w ((x,y),c,i) = case (test (Clear Front) w ((x,y),c,i)) of
		                    True -> OK w (setPos(neighbor c (x,y))((x,y),c,i))
		                    	      
		                    _    -> Error ("Blocked at: "++ show (neighbor c (x,y)))
stmt PutBeeper _ w r      = let p = getPos r
                              in if isEmpty r
                              	then Error ("No beeper to put.")
                              	else OK (incBeeper p w) (decBag r)
stmt (Turn d) _ w (p,c,i) = OK w (p,(cardTurn d c),i)
stmt (Call m) ((m1,st):xs) w r  = case (m == m1) of
					                True -> (stmt (st) ((m1,st):xs) w r)
					                False -> case (xs == []) of
					                           True  -> Error ("Undefined macro: " ++ m) -- USE LOOKUP
					                           False -> (stmt (Call m) xs w r) -- Looses the first macro if called second macro
stmt (Iterate i s) a b c        = if (i == 0)
								    then OK b c
								    else let (result) = (stmt (s) a b c) 
								           in if (stmtResult result == 0)
								             then let (OK d f) = result
								               in (stmt (Iterate (i-1) s) a d f)
								             else result
stmt (If t s1 s2) a b c         = if ((test(t) b c) == True)
								    then (stmt (s1) a b c)
								    else (stmt (s2) a b c)							 
stmt (While t s) a b c          = if ((test(t) b c) == True)
	                                then let (result) = (stmt (s) a b c)
	                                  in if (stmtResult result) == 0
	                                  	then let (OK d f) = result
	                                  	  in (stmt (While t s) a d f)
	                                  	else result
	                                else OK b c	
stmt (Block (x:xs)) a b c       = if (xs == []) 
								    then (stmt (x) a b c)
                                    else let (result) = (stmt (x) a b c)
                                    	   in if (stmtResult result) == 0 
                                             then let (OK d f) = result 
                                               in (stmt (Block xs) a (d) (f))
                                             else
                                               result
-- | Run a Karel program.

stmtResult :: Result -> Int
stmtResult (OK _ _)  = 0 
stmtResult (Done _)  = 1
stmtResult (Error _) = 2

prog :: Prog -> World -> Robot -> Result
prog (m,s) w r = stmt s m w r
