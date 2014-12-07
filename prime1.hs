module Main where
import Data.List

main :: IO ()
main =
  do
    tests <- getLine
    contents <- getContents
    putStr $ intercalate "\n" $ mapPrimes $ makeLines tests contents
  where
    makeLines :: String -> String -> [String]
    makeLines n content = take (read n) (lines content)
    mapPrimes :: [String] -> [String]
    mapPrimes = map (showPrimesBetween . (map read) . words)

showPrimesBetween :: [Integer] -> String
showPrimesBetween [a, b] = concat $ map showLn $ primesBetween a b
  where
    showLn s = (show s) ++ "\n"

divisible :: Integer -> Integer -> Bool
divisible a b = a `mod` b == 0

isPrime 2 = True
isPrime n = not $ any (n`divisible`) $ takeWhile (<=limit) primes
  where limit = ceiling $ sqrt $ fromIntegral n

primesBetween :: Integer -> Integer -> [Integer]
primesBetween 1 b = primesBetween 2 b
primesBetween a b = filter isPrime [a..b]

primes :: [Integer]
primes = sieve [2..]

sieve :: [Integer] -> [Integer]
sieve [] = []
sieve (p:ps)
  | p > 1 = p:(sieve $ filter ((> 0) . (`mod` p)) ps)
