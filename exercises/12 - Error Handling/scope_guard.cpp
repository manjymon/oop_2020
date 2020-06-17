#include <iostream>
#include <exception>

template<typename F>
class ScopeGuard
{
 public:
    ScopeGuard(F f) :
        m_f{std::move(f)},
        m_exceptions_count{std::uncaught_exceptions()}
    {}

    ~ScopeGuard()
    {
        if (std::uncaught_exceptions() > m_exceptions_count)
        {
            m_f();
        }
    }

    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
 private:
    F m_f;
    int m_exceptions_count{0};
};

template<typename F>
ScopeGuard<F> on_error(F f)
{
    return ScopeGuard<F>(f);
}

void step1()
{
    std::cout << "do 1\n";
}
void step2()
{
    std::cout << "do 2\n";
    throw "error in step 2\n";
}
void step3()
{
    std::cout << "do 3\n";
}
void step4()
{
    std::cout << "do 4\n";
    throw "error in step 4\n";
}

int main()
{
    try
    {
        auto sg1 = on_error([](){
            std::cout << "rollback 1" << std::endl;
        });
        step1();


        auto sg2 = on_error([](){
            std::cout << "rollback 2" << std::endl;
        });
        step2();
// -------------------------------------

        auto sg3 = on_error([](){
            std::cout << "rollback 3" << std::endl;
        });
        step3();


        auto sg4 = on_error([](){
            std::cout << "rollback 4" << std::endl;
        });
        step4();
    } // dtors
    catch(const char* msg)
    {
        std::cout << msg << std::endl;;
    }
    return 0;
}
