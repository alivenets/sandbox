

int test_auto()
{
    auto i = 2;		// OK
    // auto int ii = 2; // ERROR!
}

int test_rvalue_reference()
{
    int a = 42;
    int &ra = a;
    // int &&rra = a; // ERROR!
    // int &&rra = ra; // ERROR!
}

int main(void)
{
}
