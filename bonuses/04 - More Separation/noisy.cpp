#include <iostream>

#include "noisy.hpp"

class Noisy::Implementation
{
public:
    Implementation() = default;
    Implementation(int marker) : m_marker{marker} {}

    void shout(const Noisy&) const;

    int marker() const;
private:
    int m_marker{0};
};

void Noisy::Implementation::shout(const Noisy& self) const
{
    if (self.should_shout())
    {
        std::cout << "AAAAAAAAAAAAAAAAAAAA\n";
    }
}

int Noisy::Implementation::marker() const
{
    return m_marker;
}

Noisy::Noisy() :
    pimpl{std::make_unique<Implementation>(0)}
{
    std::cout << "CTOR 0\n";
}

Noisy::Noisy(int marker) :
    pimpl{std::make_unique<Implementation>(marker)}
{
    std::cout << "CTOR " << marker << "\n";
}

Noisy::~Noisy()
{
    std::cout << "DTOR " << pimpl->marker() << "\n";
}

Noisy::Noisy(const Noisy& other) :
    pimpl{std::make_unique<Implementation>(*other.pimpl)}
{
    std::cout << "COPY CTOR " << other.pimpl->marker() << "\n";
}

void Noisy::swap(Noisy& other)
{
    using std::swap;
    swap(pimpl, other.pimpl);
}

// Too noisy, also logs copy ctor and dtor but whatever
Noisy& Noisy::operator=(const Noisy& other)
{
    std::cout << "COPY ASSIGNMENT " << other.pimpl->marker() << "\n";
    Noisy tmp{other};
    swap(tmp);
    return *this;
}

void Noisy::shout() const
{
    pimpl->shout(*this);
}
