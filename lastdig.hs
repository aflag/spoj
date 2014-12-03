--import Test.QuickCheck

--prop_equiv (Positive x) (Positive y) = f x y == g x y

f x y = (x^y) `mod` 10

g _ 0 = 1
g 1 _ = 1
g x y = (map (f x) [4..]) !! (y `mod` 4)

numbers n rest = map transform $ take (read n) $ lines rest
transform line = let list = map read $ words line in (list !! 0, list !! 1)

main = do
    n <- getLine
    rest <- getContents
    mapM_ putStrLn $ map (show . uncurry g) $ numbers n rest 
    return ()
