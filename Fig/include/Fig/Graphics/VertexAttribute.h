



// Marker base
struct itest { };

// Concept: must inherit itest and have static member 'items'
template<typename T>
concept IsITest = std::is_base_of_v<itest, T> && requires { T::items; };

template<typename DerivedClass>
struct ITest : itest {
    template<IsITest T>
    static constexpr int ItemCount() {
        return T::items;
    }

    constexpr int ItemCount()
    {
        return DerivedClass::items;
    }
};

struct Test : ITest<Test> {
    int a = 0;
    static constexpr int items = 2;
    static constexpr int data[] = {1,2};
};


void SomeMethod()
{
    Test tst{};
    tst.ItemCount<Test>;
    Test::ItemCount<Test>;
    tst.ItemCount();
}
