N = gets.to_i
(1..N).each do
  x, y = gets.split
  x.reverse!
  y.reverse!
  z = (x.to_i + y.to_i).to_s
  z.reverse!
  puts z.to_i
end
