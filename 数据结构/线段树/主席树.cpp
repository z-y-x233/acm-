//主席树板子
namespace zxt {
	const int N = 2e5 + 100;
	//主席树维护的是当前权值[l, r]中出现的数的数量
	struct node
	{
		//树的结点存储的为左孩子和右孩子信息
		//值域不需要存储, 两孩子值域一定为[l, mid]和[mid + 1, r]
		int ls, rs;
		int size;
	}t[N << 5];
	//root[i]存储第前i颗线段树的根结点, cnt用来动态开点
	int root[N], cnt = 0;
	//建立一颗空树方便插入
	int build(int l, int r) {
		int rt = ++cnt;
		t[rt].size = 0;
		if (l < r) {
			int mid = l + r >> 1;
			t[rt].ls = build(l, mid);
			t[rt].rs = build(mid + 1, r);
		}
		return rt;
	}
	//pre为前一颗表示值域为[l, r]的线段树的根节点
	//x为需要插入的数
	int insert(int pre, int l, int r, int x) {
		int rt = ++cnt;
		t[rt].size = t[pre].size + 1;
		t[rt].ls = t[pre].ls;
		t[rt].rs = t[pre].rs;
		if (l < r) {
			int mid = l + r >> 1;
			//若l < r且x <= mid值域中点, 则对左子树递归建树
			//并把返回的新的根节点赋给新树的左儿子, 反之
			if (x <= mid) t[rt].ls = insert(t[pre].ls, l, mid, x);
			else t[rt].rs = insert(t[pre].rs, mid + 1, r, x);
		}
		return rt;
	}
	//查询区间为[pre, now]的第k大的数, 当前值域为[l, r]
	//返回值p为离散化后的下标, 获取原值需要使用d[p - 1]
	// L = pre, R = now
	int query(int pre, int now, int l, int r, int k) {
		if (l >= r) return l;
		int x = t[t[now].ls].size - t[t[pre].ls].size;
		//x为前R个数和前L个数中值域在[l, mid]中的数量的差值
		//若k <= x, 则[l, mid]中有超过k个数, 第k大的数一定
		//在左子树中
		int mid = l + r >> 1;
		if (k <= x) return query(t[pre].ls, t[now].ls, l, mid, k);
		else return query(t[pre].rs, t[now].rs, mid + 1, r, k - x);
	}

}

int a[N];
vector<int> d;
//对值域离散化处理
//二分返回值为x在d中的下标 + 1
int pos(int x) {
	return lower_bound(d.begin(), d.end(), x) - d.begin() + 1;
}