/*
 * 奇妙旅行
 * @描述
 *  小熊住在由n个城镇(城镇编号from 1 to n)组成的国家里,n-1条双向联通的路将这n个城镇相互连接。
 *  所以从一个城镇旅行到其他任意一个城镇都是可行的。小熊想要进行一次旅行，它选择一对城镇(u,v)(u ≠ v)，
 *  然后选择从u到v的最短路径完成旅行。(注意：(u,v)和(v,u)被认为是不同旅行。)
 *  然而，在小熊的国家里，有2个特殊的城镇，一个叫伦敦(编号x)，一个叫巴黎(编号y)。
 *  伦敦是一个被花香萦绕的小镇，巴黎是一个到处都是蜜蜂的小镇。
 *  因此，小熊在旅行过程中，如果先经过伦敦，再经过巴黎，他就会遭到蜜蜂的疯狂攻击。
 *  请你帮帮小熊计算出有多少对(u,v)可供选择来完成旅行计划。
 *
 * @输入描述
 *  第一行包含3个整数，n,x,y(1 ≤n≤3000, 1≤x,y≤n , x ≠ y) ，n表示城镇数量，x表示伦敦的编号,y表示巴黎的编号。
 *  接下来n-1行，每行包括两个整数a,b(1≤a,b≤n1≤a,b≤n, a≠b),描述了城镇a和城镇b之间存在一条道路。
 *  输入保证，任意两点都彼此联通（所给的城镇和道路组成了一棵树）。
 * 
 * @输出描述
 *  输出有多少对(u,v)可供小熊选择来完成旅行。
 * 
 * @样例输入 1 
 *  3 1 3
 *  1 2
 *  2 3
 * 
 * @样例输出 1
 *  5
 * 
 * @样例输入 2 
 *  3 1 3
 *  1 2
 *  1 3
 * 
 * @样例输出 2
 *  4
 * 
 * @提示
 *  第一个example中,小熊有5种选择
 *  (1,2): 他的路线是 1→2
 *  (2,3): 他的路线是 2→3
 *  (3,2): 他的路线是 3→2
 *  (2,1): 他的路线是 2→1
 *  (3,1): 他的路线是 3→2→1
 *  小熊不能选择(1,3)。因为如果它选择这个路线，他会先访问城镇1(伦敦)再访问城镇3(巴黎)，它会遭到蜜蜂的攻击，这会让小熊受伤。
 */

#include <iostream>

// city index.
// NOTE: 0 is invalid
typedef int cidx_t;
// path index.
// NOTE: 0 is invalid
typedef int pidx_t;

typedef struct path {
	cidx_t t1;	// terminal city 1
	cidx_t t2;	// terminal city 2
	pidx_t t1n;	// path index connected to t1
	pidx_t t2n;	// path index connected to t2
} path_t;

constexpr int maxcity = 3000;

// path array
// NOTE: the pa[0] is invalid, i.e. the t1n/t2n represent NULL with 0.
path_t pa[maxcity];
int n = 0;
cidx_t x = 0;	// london index
cidx_t y = 0;	// paris index
// path header (the first path index connected to specific city)
pidx_t ph[maxcity+1];

/*
 * @flg: store connection state
 * @cityidx: the city index to process
 * @maskcity: the city index to mask
 * @ncity: the connected city number
 */
void prcconn(bool * flg, cidx_t cityidx, cidx_t maskcity, int & ncity)
{
	if (cityidx == maskcity || flg[cityidx]) {
		return;
	}

	flg[cityidx] = true;
	++ncity;
	pidx_t pidx = ph[cityidx];
	while (pidx != 0) {
		const path_t & p = pa[pidx];
		if (cityidx == p.t1) {
			prcconn(flg, p.t2, maskcity, ncity);
			pidx = p.t1n;
		}
		else {
			prcconn(flg, p.t1, maskcity, ncity);
			pidx = p.t2n;
		}
	}
}

int main()
{
	std::cin >> n >> x >> y;

	for (int i = 1; i < n; ++i) {
		int u = 0;
		int v = 0;
		std::cin >> u >> v;
		pa[i].t1 = u;
		pa[i].t2 = v;
		pa[i].t1n = ph[u];
		pa[i].t2n = ph[v];
		ph[u] = i;
		ph[v] = i;
	}

	/// 与 y 连通的城市
	bool flgy[maxcity+1] = {};
	/// 不经过 x 可到达 y 的城镇数量
	int  ny = 0;
	prcconn(flgy, y, x, ny);

	/// 与 x 连通的城市
	bool flgx[maxcity+1] = {};
	/// 不经过 y 可到达 x 的城镇数量
	int  nx = 0;
	prcconn(flgx, x, y, nx);

	const int ret = n * (n-1) - (n - ny) * (n - nx);

	// std::cout << "ny: " << ny << "   nx: " << nx << std::endl;
	std::cout << ret << std::endl;

	return 0;
}
