#include <iostream>
#include <string>
#include <memory>

class Notifier
{
 public:
    void notify(const std::string& msg) const
    {
        do_notify(msg);
    }

    std::unique_ptr<Notifier> clone() const
    {
        return do_clone();
    }

    virtual ~Notifier() = default;
 protected:
    Notifier& operator=(const Notifier&) = default;
 private:
    virtual void do_notify(const std::string&) const = 0;
    virtual std::unique_ptr<Notifier> do_clone() const = 0;
};

class ConsoleNotifier: public Notifier
{
 private:
    void do_notify(const std::string& msg) const override
    {
        std::cout << msg << std::endl;
    }

    std::unique_ptr<Notifier> do_clone() const override
    {
        return std::make_unique<ConsoleNotifier>(*this);
    }
};

class EmailNotifier: public Notifier
{
 public:
    EmailNotifier(const std::string& email) :
        m_email{email}
    {}
 private:
    std::string m_email;

    std::unique_ptr<Notifier> do_clone() const override
    {
        return std::make_unique<EmailNotifier>(*this);
    }

    void do_notify(const std::string& msg) const override
    {
        std::cout << "Sending " << msg << " to " << m_email << std::endl;
    }
};
