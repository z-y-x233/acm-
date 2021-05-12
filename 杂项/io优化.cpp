#include <bits/stdc++.h>

using namespace std;


namespace io {
	const int L = 10000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}

	template <typename T>
	void read(T &x) {
		x = 0;int w = 1;
		char c = 0, la = ' ';
		while(c > '9' || c < '0') la = c, c = GetChar();
		while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = GetChar();
		if (la == '-') x = -x;
	}
	template <typename T>
	void write(T x) {
		int s[1000], top = 0;
		do {s[++top] = x % 10; x /= 10;} while(x);
		while(top) putchar(s[top--] + 48);
	}
}

int main() {
	int x;
	while(true) {
		io::read(x);
		io::write(x);
		putchar('\n');
	}

}