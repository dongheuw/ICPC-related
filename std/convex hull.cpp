{
ID:hedongn1
PROB:fc
LANG:PASCAL
}
program usaco_fc;
type
   point = record
      x,y : double;
   end;
var
   a,stack : array[1..10000] of point;
   n,i,j,k,top : longint;
   ans : double;
procedure swap(var x,y:point);
var
   t : point;
begin
        t := x;
        x := y;
        y := t;
end;
function cross(a,b,c:point):double;
begin
        exit((a.x-c.x)*(b.y-c.y)-(a.y-c.y)*(b.x-c.x));
end;
function dist(a,b:point):double;
begin
        exit(sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)));
end;
procedure qsort(x,y:longint);
var
   xx,yy : longint;
   mid : point;
begin
        xx := x;
        yy := y;
        mid := a[(x+y) div 2];
        repeat
                while (cross(a[xx],mid,a[1]) > 0) or ((cross(a[xx],mid,a[1]) = 0) and (dist(a[xx],a[1]) > dist(mid,a[1]))) do inc(xx);
                while (cross(a[yy],mid,a[1]) < 0) or ((cross(a[yy],mid,a[1]) = 0) and (dist(a[yy],a[1]) < dist(mid,a[1]))) do dec(yy);
                if xx <= yy then
                begin
                        swap(a[xx],a[yy]);
                        inc(xx);
                        dec(yy);
                end;
        until xx > yy;
        if xx < y then qsort(xx,y);
        if x < yy then qsort(x,yy);
end;
procedure push(x:longint);
begin
        inc(top);
        stack[top] := a[x];
end;
begin
        assign(input,'fc.in'); reset(input);
        assign(output,'fc.out'); rewrite(output);
        readln(n);
        for i := 1 to n do readln(a[i].x,a[i].y);
        for i := 2 to n do
                if (a[i].y < a[1].y) or ((a[i].y = a[1].y) and (a[i].x < a[1].x)) then
                        swap(a[i],a[1]);
        qsort(2,n);
        top := 0;
        push(1);
        push(2);
        for i := 3 to n do
        begin
                while (top > 1) and (cross(a[i],stack[top],stack[top-1]) >= 0) do dec(top);
                push(i);
        end;
        ans := dist(stack[top],stack[1]);
        for i := 1 to top-1 do
                ans := ans + dist(stack[i],stack[i+1]);
        writeln(ans:0:2);
        close(input); close(output);
end.
