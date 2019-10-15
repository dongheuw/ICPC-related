P[1]:=0;
j:=0;
for i:=2 to m do
begin
   while (j>0) and (B[j+1]<>B[i]) do j:=P[j];
   if B[j+1]=B[i] then j:=j+1;
   P[i]:=j;
end;

j:=0;
for i:=1 to n do
begin
   while (j>0) and (B[j+1]<>A[i]) do j:=P[j];
   if B[j+1]=A[i] then j:=j+1;
   if j=m then
   begin
      writeln('Pattern occurs with shift ',i-m);
      j:=P[j];
   end;
end;
