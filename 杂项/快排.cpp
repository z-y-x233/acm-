void q_sort(int *a, int l, int r) {

	if (l >= r) return;

	int i = l - 1, j = r + 1;
	int x = a[l + r >> 1];
	while (i < j) {
		do i++; while (a[i] < x);
		do j--; while (a[j] > x);
		if (i < j) swap(a[i], a[j]);
	}
	q_sort(a, l, j);
	q_sort(a, j + 1, r);
}

