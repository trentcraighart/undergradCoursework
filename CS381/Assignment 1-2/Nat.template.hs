-- Trent Vasquez 932-295-132
-- Scott Merrill 931-936-368

module Nat where

import Prelude hiding (Enum(..), sum)


--
-- * Part 2: Natural numbers
--

-- | The natural numbers.
data Nat = Zero
         | Succ Nat
         deriving (Eq,Show)

-- | The number 1.
one :: Nat
one = Succ Zero

-- | The number 2.
two :: Nat
two = Succ one

-- | The number 3.
three :: Nat
three = Succ two

-- | The number 4.
four :: Nat
four = Succ three


-- | The predecessor of a natural number.
--   
--   >>> pred Zero
--   Zero
--   
--   >>> pred three
--   Succ (Succ Zero)
--   
pred :: Nat -> Nat
pred (Zero)   = Zero
pred (Succ a) = a

-- | True if the given value is zero.
--
--   >>> isZero Zero
--   True
--
--   >>> isZero two
--   False
--
isZero :: Nat -> Bool
isZero (Zero)    = True
isZero (Succ a)  = False


-- | Convert a natural number to an integer.
--
--   >>> toInt Zero
--   0
--
--   >>> toInt three
--   3
--
toInt :: Nat -> Int
toInt (Zero)   = 0
toInt (Succ a) = 1 + (toInt(a))


-- | Add two natural numbers.
--
--   >>> add one two
--   Succ (Succ (Succ Zero))
--
--   >>> add Zero one == one
--   True
--
--   >>> add two two == four
--   True
--
--   >>> add two three == add three two
--   True
--   
add :: Nat -> Nat -> Nat
add (Zero) (a)   = a
add (a) (Zero)   = a
add (a) (b)      = add(Succ a) (pred b)

-- | Subtract the second natural number from the first. Return zero
--   if the second number is bigger.
--
--   >>> sub two one
--   Succ Zero
--   
--   >>> sub three one
--   Succ (Succ Zero)
--
--   >>> sub one one
--   Zero
--
--   >>> sub one three
--   Zero
--
-- **NOTE** Assuming this will always be a natural resualt

sub :: Nat -> Nat -> Nat
sub (a) (Zero) = a
sub (a) (b)    = sub(pred a) (pred b) 


-- | Is the left value greater than the right?
--
--   >>> gt one two
--   False
--
--   >>> gt two one
--   True
--
--   >>> gt two two
--   False
--
gt :: Nat -> Nat -> Bool
gt (Zero) (b) = False
gt (a) (Zero) = True
gt (a) (b)    = gt(pred a) (pred b)


-- | Multiply two natural numbers.
--
--   >>> mult two Zero
--   Zero
--
--   >>> mult Zero three
--   Zero
--
--   >>> toInt (mult two three)
--   6
--
--   >>> toInt (mult three three)
--   9
--
mult :: Nat -> Nat -> Nat
mult (Zero) (b)  = Zero
mult (a) (Zero)  = Zero
mult (a) (b)     = add a (mult a (pred b))


-- | Compute the sum of a list of natural numbers.
--
--   >>> sum []
--   Zero
--   
--   >>> sum [one,Zero,two]
--   Succ (Succ (Succ Zero))
--
--   >>> toInt (sum [one,two,three])
--   6
--
sum :: [Nat] -> Nat
sum [] = Zero
sum (x:xs) = add x (sum xs)

-- | An infinite list of all of the *odd* natural numbers, in order.
--
--   >>> map toInt (take 5 odds)
--   [1,3,5,7,9]
--
--   >>> toInt (sum (take 100 odds))
--   10000
--
odds :: [Nat]
odds  = infodds [one]

infodds :: [Nat] -> [Nat]
infodds xs = xs ++ infodds [(add two (last xs))]
