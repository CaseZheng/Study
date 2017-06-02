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

template<typename T>
void print(T x)
{
    cout<<x<<endl;   
}

template<>
void print(pair<int, string> x)
{
    cout<<x.first<<" "<<x.second<<endl;
}

//assign
void TestAssign()
{
    using namespace boost::assign;
    //向容器中增加元素
    vector<int> v;
    v += 1, 2, 3, 4, 5, 6, 9*9; 
    for_each(v.begin(), v.end(), print<int>);

    set<string> s;
    s += "cpp", "md";
    for_each(s.begin(), s.end(), print<string>);

    map<int, string> m;
    m += make_pair(1, "one"), make_pair(2, "two");
    for_each(m.begin(), m.end(), print<pair<int, string>>);

    push_back(v)(7)(8)(9);
    for_each(v.begin(), v.end(), print<int>);

    list<string> l;
    push_front(l)("cpp")("java");
    for_each(l.begin(), l.end(), print<string>);

    set<double> sd;
    insert(sd)(1.1)(2.2)(3.3);
    for_each(sd.begin(), sd.end(), print<double>);

    insert(m)(3, "t")(4, "f");
    for_each(m.begin(), m.end(), print<pair<int, string>>);

    push_back(v), 1, 2, 3, 4, 5;
    push_back(v)(6), 7, 8, (9), 10;
    for_each(v.begin(), v.end(), print<int>);


    //初始化容器元素
    vector<int> vec = list_of(1)(2)(3)(4)(5);
    for_each(vec.begin(), vec.end(), print<int>);

    deque<string> deq = (list_of("one")("two"), "t", ("f"));
    for_each(deq.begin(), deq.end(), print<string>);

    map<int, string> mp = (list_of(make_pair(1, "one"))(make_pair(2, "two")), make_pair(3, "t"));
    for_each(mp.begin(), mp.end(), print<pair<int, string>>);

    map<int, string> mp2 = map_list_of(1, "cpp")(2, "java");
    for_each(mp2.begin(), mp2.end(), print<pair<int, string>>);

    //减少重复输入
    vector<int> v2 = list_of(1).repeat(3, 100).repeat(4, 1000);
    for_each(v2.begin(), v2.end(), print<int>);

    vector<int> v3;
    push_back(v3).range(v.begin(), v.begin()+5);
    for_each(v3.begin(), v3.end(), print<int>);

    stack<int> stk = (list_of(1), 2, 3).to_adapter();

    queue<string> q = (list_of("java")("md")("c")).to_adapter();

    vector<vector<int>> vv;
    vv += list_of(5)(6), list_of(7)(8);

    int a = 1, b = 2, c = 3;
    vector<int> v4 = ref_list_of<3>(a)(b)(c);
    for_each(v4.begin(), v4.end(), print<int>);

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
    //TestOptional();

    //assign
    TestAssign();

	return 0;
}
