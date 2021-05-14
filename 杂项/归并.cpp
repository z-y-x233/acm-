const int N = 1e5 + 100;

int t[N];

void merge(int *a, int l, int r) {
	int mid = l + r >> 1;
	int i = l, j = mid + 1;
	int cnt = l;
	while (i <= mid && j <= r) {
		if (a[i] <= a[j]) t[cnt++] = a[i++];
		else t[cnt++] = a[j++];
	}
	while (i <= mid) t[cnt++] = a[i++];
	while (j <= r) t[cnt++] = a[j++];
	for (i = l; i <= r; ++i) a[i] = t[i];

}

void merge_sort(int *a, int l, int r) {
	if (l >= r) return;
	int mid = l + r >> 1;
	merge_sort(a, l, mid);
	merge_sort(a, mid + 1, r);
	merge(a, l, r);
}
