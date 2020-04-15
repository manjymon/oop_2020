#include <iostream>
#include <string>

class Notifier
{
 public:
    // NVI (non-virtual interface)
    // Interface for notify
    void notify(const std::string& msg) const
    {
        // precondition
        // other customization points e.g. do_establish_connection();
        do_notify(msg);
        // postcondition
    }

    Notifier* clone() const
    {
        return do_clone();
    }

    // Virtual dtor to prevent bugs
    virtual ~Notifier() = default;
    // Alternative: protected non-virtual dtor
 protected:
    // Protected assignment operator in non-leaf classes to prevent some slicing
    Notifier& operator=(const Notifier&) = default;
    // Alternative: delete copy assignment operator and copy constructor and only copy with clone
 private:
    // Implementation / Customization point for notify
    virtual void do_notify(const std::string&) const = 0;
    virtual Notifier* do_clone() const = 0;
};

class ConsoleNotifier: public Notifier
{
 private:
    // Actual implementation of notify
    void do_notify(const std::string& msg) const override
    {
        std::cout << msg << std::endl;
    }

    ConsoleNotifier* do_clone() const override
    {
        return new ConsoleNotifier{*this};
    }
};

class EmailNotifier: public Notifier
{
 public:
    EmailNotifier(const std::string& email) :
        m_email{email}
    {}

    bool check_connection() const
    {
        std::cout << "CHECKING CONNECTION TO " << m_email << std::endl;
        return true;
    }
 private:
    std::string m_email;

    EmailNotifier* do_clone() const override
    {
        return new EmailNotifier{*this};
    }

    void do_notify(const std::string& msg) const override
    {
        std::cout << "Sending " << msg << " to " << m_email << std::endl;
    }
};

int main()
{
    Notifier* arr[2];
    arr[0] = new ConsoleNotifier;
    arr[1] = new EmailNotifier{"email@email.com"};

    for (auto x : arr)
    {
        x->notify("Message");
    }

    for (auto x: arr)
    {
        delete x;
    }

    return 0;
}
