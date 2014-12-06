program samer08f;
var n : Integer;
    x : integer;
    acc : integer;
begin
  while true do
  begin
    readln(n);
    if n = 0 then
    begin
      break;
    end;
    acc := 0;
    for x:=1 to n do
    begin
      acc := acc + x*x;
    end;
    writeln(acc);
  end;
end.
