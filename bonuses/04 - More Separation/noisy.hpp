#pragma once

class Noisy
{
 public:
    Noisy();
    explicit Noisy(int);
    Noisy(const Noisy&);
    Noisy& operator=(const Noisy&);
    ~Noisy();
    void swap(Noisy&);

    bool should_shout() const { return true; }
    void shout() const;
 private:
    class Implementation;
    // Declare here
};
