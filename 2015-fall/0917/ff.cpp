#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std ;

typedef long long LL ;

#define Log( i , a , b ) for ( int i = a ; ( 1 << i ) <= b ; ++ i )
#define rep( i , a , b ) for ( int i = a ; i < b ; ++ i )
#define For( i , a , b ) for ( int i = a ; i <= b ; ++ i )
#define rev( i , a , b ) for ( int i = ( a ) ; i >= ( b ) ; -- i )
#define travel( e , H , u ) for ( Edge* e = H[u] ; e ; e = e -> next )
#define clr( a , x ) memset ( a , x , sizeof a )
#define cpy( a , x ) memcpy ( a , x , sizeof a )

const int MAXN = 100005 ;
const int MAXE = 200005 ;
const int INF = 0x3f3f3f3f ;

struct Edge {
	int v , c ;
	Edge* next ;
} E[MAXE] , *H[MAXN] , *edge ;

struct Node {
	int dis ;
	int idx ;
	Node () {}
	Node ( int dis , int idx ) : dis ( dis ) , idx ( idx ) {}
	bool operator < ( const Node& a ) const {
		if ( dis != a.dis ) return dis < a.dis ;
		return idx < a.idx ;
	}
	bool operator > ( const Node& a ) const {
		return a < *this ;
	}
	bool operator <= ( const Node& a ) const {
		return !( a < *this ) ;
	}
	bool operator >= ( const Node& a ) const {
		return !( *this < a ) ;
	}
	Node operator + ( const int& val ) const {
		return Node ( dis + val , idx ) ;
	}
	Node operator - ( const int& val ) const {
		return Node ( dis - val , idx ) ;
	}
} node[MAXN] , S[MAXN] ;

int Q[MAXN] , head , tail ;
int vis[MAXN] ;
int Time ;
int siz[MAXN] ;
int num[MAXN] ;
int mart[MAXN] ;
int ans[MAXN] ;
int dis[MAXN] ;
int size ;
int root ;
int cnt ;
int n ;

void clear () {
	edge = E ;
	num[0] = n ;
	clr ( H , 0 ) ;
	head = tail = 0 ;
	clr ( ans , 0 ) ;
}

void addedge ( int u , int v , int c ) {
	edge->v = v ;
	edge->c = c ;
	edge->next = H[u] ;
	H[u] = edge ++ ;
}

void spfa () {
	while ( head != tail ) {
		int u = Q[head ++] ;
		if ( head == MAXN ) head = 0 ;
		vis[u] = Time - 1 ;
		travel ( e , H , u ) {
			int v = e->v ;
			Node tmp = node[u] + e->c ;
			if ( node[v] > tmp ) {
				node[v] = tmp ;
				if ( vis[v] != Time ) {
					vis[v] = Time ;
					Q[tail ++] = v ;
					if ( tail == MAXN ) tail = 0 ;
				}
			}
		}
	}
}

void get_siz ( int u , int fa = 0 ) {
	siz[u] = 1 ;
	travel ( e , H , u ) {
		int v = e->v ;
		if ( v != fa && vis[v] != Time ) {
			get_siz ( v , u ) ;
			siz[u] += siz[v] ;
		}
	}
}

void get_root ( int u , int fa = 0 ) {
	num[u] = 0 ;
	travel ( e , H , u ) {
		int v = e->v ;
		if ( v != fa && vis[v] != Time ) {
			get_root ( v , u ) ;
			num[u] = max ( num[u] , siz[v] ) ;
		}
	}
	num[u] = max ( num[u] , size - siz[u] ) ;
	if ( num[u] < num[root] ) root = u ;
}

void get_dis ( int u , int val , int fa = 0 ) {
	dis[u] = val ;
	S[++ cnt] = node[u] - val ;//丢进S数组
	travel ( e , H , u ) {
		int v = e->v ;
		if ( v != fa && vis[v] != Time ) {
			get_dis ( v , dis[u] + e->c , u ) ;
		}
	}
}

int search ( const Node& x ) {//二分查找，如果没有找到目标，则返回小于x的最大的数的下标
	int l = 0 , r = cnt ;
	while ( l < r ) {
		int m = ( l + r + 1 ) >> 1 ;
		if ( S[m] <= x ) l = m ;
		else r = m - 1 ;
	}
	return r ;
}

void get_ans ( int u , int sign , int fa = 0 ) {
	if ( !mart[u] ) {//为不是mart的点计算能被其占领的点的个数
		int tmp = search ( Node ( dis[u] , u ) ) ;
		ans[u] += ( cnt - tmp ) * sign ;
	}
	travel ( e , H , u ) {
		int v = e->v ;
		if ( v != fa && vis[v] != Time ) {
			get_ans ( v , sign , u ) ;
		}
	}
}

void deal ( int u , int val , int sign ) {
	cnt = 0 ;
	get_dis ( u , val ) ;//得到dist
	sort ( S + 1 , S + cnt + 1 ) ;
	get_ans ( u , sign ) ;//计算贡献
}

void divide ( int u ) {//分治
	get_siz ( u ) ;//得到子树规模
	size = siz[u] ;
	root = 0 ;
	get_root ( u ) ;//寻找u所在的子树的重心
	vis[root] = Time ;
	deal ( root , 0 , 1 ) ;//得到该子树内所有的贡献，不管是不是同一棵子树的
	travel ( e , H , root ) if ( vis[e->v] != Time ) deal ( e->v , e->c , -1 ) ;//去重，排除同一棵子树的贡献
	travel ( e , H , root ) if ( vis[e->v] != Time ) divide ( e->v ) ;//递归处理
}

void solve () {
	int x , y , c ;
	clear () ;
	rep ( i , 1 , n ) {
		scanf ( "%d%d%d" , &x , &y , &c ) ;
		addedge ( x , y , c ) ;
		addedge ( y , x , c ) ;
	}
	For ( i , 1 , n ) {
		scanf ( "%d" , &mart[i] ) ;
		if ( mart[i] ) {
			node[i] = Node ( 0 , i ) ;
			Q[tail ++] = i ;
		} else node[i] = Node ( INF , 0 ) ;
	}
	++ Time ;
	spfa () ;
	++ Time ;
	divide ( 1 ) ;
	int res = 0 ;
	For ( i , 1 , n ) if ( ans[i] > res ) res = ans[i] ;
	printf ( "%d\n" , res ) ;
}

int main () {
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
	Time = 0 ;
	clr ( vis , 0 ) ;//优化
	while ( ~scanf ( "%d" , &n ) ) solve () ;
	return 0 ;
}
