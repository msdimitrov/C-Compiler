
int func1()
{
	int variable1_;
	int variable2_;

	variable1_ = 30;
	variable2_ = 90;

	return variable1_ + variable2_;
}

int func2()
{
	int a;
	int var_;
	var_ = 9;
	a = func1();

	return a + var_;
}

int main()
{
	int x;

	x = func2();

	printf(x);

	return 0;
}