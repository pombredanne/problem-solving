// n : �l��
// k : �X�L�b�v����
// m : �J�n�ʒu
int joseph(int n, int k, int m)
{
	int j = 0, d;
	for (int i=2; i <= n; ++i) {
		d = (k-1) % i;
		j=(j+d)%(i-1);
		if (j>=d) ++j;
	}
	return (j-(k-m)%n+n)%n + 1;
}
