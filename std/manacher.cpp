void Manacher()
{
	int id = 0;
	fo(i,1,N)
	{
		if (id+r[id] > i) r[i] = min(id+r[id]-i,r[2*id-i]);
		else r[i] = 0;
		while (i+r[i]+1 <= N && i-r[i]-1 >= 1 && s[i+r[i]+1] == s[i-r[i]-1]) r[i] ++;
		if (i+r[i] > id+r[id]) id = i;
	}
}
