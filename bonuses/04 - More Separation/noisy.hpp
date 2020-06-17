#pragma once

#include <memory>

class Noisy
{
 public:
    Noisy();
    explicit Noisy(int);
    Noisy(const Noisy&);
    Noisy& operator=(const Noisy&);
    Noisy(Noisy&&) = default;
    Noisy& operator=(Noisy&&) = default;
    ~Noisy();

    void swap(Noisy&);

    bool should_shout() const { return true; }
    void shout() const;
 private:
    class Implementation;
    std::unique_ptr<Implementation> pimpl;
};
