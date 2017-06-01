#include "public.h"

//timer
void TestTimer()
{
	timer t;
	cout << "max timespac:" << t.elapsed_max()/3600/24/30 << "m" << endl;
	cout << "min timespac:" << t.elapsed_min() << "s" << endl;
	cout << "now timespac:" << t.elapsed() << "s" << endl;

	return ;
}

class do_not_copy: boost::noncopyable
{
};

//noncopyable
void TestNoncopyable()
{
    do_not_copy d1;
    //下面两句代码会导致编译错误
    //do_not_copy d2 = d1;
    //do_not_copy d3(d1);

    return ;
}

//typeof
void TestTypeof()
{
    //typeof(1) tint = 1;
    //typeof(1>0) tbool = 1>0;

    auto tint1 = 1;
    auto tbool1 = 1>0;
    cout<<tint1<<endl;
    cout<<tbool1<<endl;

    BOOST_TYPEOF(1) tint2 = 1;
    BOOST_TYPEOF(3.14) tdouble2 = 3.14;
    cout<<tint2<<endl;
    cout<<tdouble2<<endl;

    BOOST_AUTO(tdp, new double[20]);
    BOOST_AUTO(tpair, make_pair(1, "string"));
    cout<<tpair.second<<endl;

    return ;
}

optional<double> calc(int x)
{
    return optional<double>(x!=0, 1.0/x);
}

//optional
void TestOptional()
{
    optional<int> op0;
    optional<int> op1(op0);
    assert(!op0);
    assert(op0==op1);
    assert(op1.get_value_or(253) == 253);
    
    optional<string> ops("test");
    cout<<*ops<<endl;

    vector<int> v(10);
    optional<vector<int> &> opv(v);
    assert(opv);

    opv->push_back(5);
    assert(opv->size() == 11);

    opv = none;
    assert(!opv);

    optional<double> d = calc(10);
    if(d)
    {
        cout<<*d<<endl;
    }

    BOOST_AUTO(x, make_optional(5));    //工厂函数
    cout<<*x<<endl;

    return ;
}

int main()
{
    //timer
    //TestTimer();

    //noncopyable
    //TestNoncopyable();

    //typeof
    //TestTypeof();
    
    //optional
    TestOptional();
	return 0;
}
