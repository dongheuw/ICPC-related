bool SPFA()
{
	int l = 0, r = 1;
	fo(i,0,T) dist[i] = INF;
	memset(flag,0,(T+1));
	q[1] = S; flag[S] = 1;
	dist[S] = 0; MinD[S] = INF;
	while (l < r)
	{
		int x = q[++l];
		for (int i = a[x];i;i = c[i])
			if (d[i] && dist[x]+cost[i] < dist[b[i]])
			{
				dist[b[i]] = dist[x] + cost[i];
				MinD[b[i]] = min(MinD[x],d[i]);
				pre[b[i]] = i;
				if (!flag[b[i]])
				{
					q[++r] = b[i];
					flag[b[i]] = 1;
				}
			}
		flag[x] = 0;
	}
	return dist[T] < INF;
}

void Work()
{
	int ans = 0;
	while (SPFA())
	{
		for (int x = T,i = pre[T];i;x = b[i^1],i = pre[x])
		{
			d[i] -= MinD[T];
			d[i^1] += MinD[T];
		}
		ans += MinD[T] * dist[T];
	}
	printf("%d\n",ans);
}
