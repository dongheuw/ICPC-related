for ((i = 1; i <= 10;++i)) do
	echo test case # `$i`
	./d <test$i.in >my.out
	diff my.out test$i.out -w
done
