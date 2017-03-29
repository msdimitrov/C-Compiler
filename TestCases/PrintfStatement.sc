int foo()
{
	int new;
	new = 20*3+20/2-30;
	return new;
}

int main()
{
	int a;
	int b;
	int c;
	char ch;
	bool ok;
	ok = 1;

	printf(ok);

	ch = 9;
	printf(ch);

	a = 100;
	b = 20;
	printf(a);
	printf(b);
	
	c = a + b;
	printf(c);

	c = a - b;
	printf(c);

	c = a / b;
	printf(c);

	c = a * b;
	printf(c);

	c = 9 % 7;
	printf(c);

	printf(foo());

	nop;

	return 0;
}