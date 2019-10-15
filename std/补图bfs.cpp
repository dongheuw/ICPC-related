void BFS()
{
    fo(i,0,n) dis[i] = INF;
    link.clear(), tmp.clear();
    fo(i,2,n) link.insert(i);
    queue<int> Q;
    while (!Q.empty()) Q.pop();
    Q.push(1); dis[1] = 0;
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        for (int i = head[u];i != -1;i = edge[i].next)
        {
            int v = edge[i].v;
            if (link.count(v) == 0) continue;
            link.erase(v), tmp.insert(v);
        }
        for (set<int>::iterator it = link.begin();it != link.end();it ++)
            Q.push(*it), dis[*it] = dis[u] + b;
        link.swap(tmp), tmp.clear();
    }
    printf("%lld\n",min(dis[n],a));
}
