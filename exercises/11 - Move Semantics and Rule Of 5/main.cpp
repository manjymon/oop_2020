#include "notifier.h"
#include <vector>

#include <memory>
#include "pointer.h"
int main()
{
    std::vector<std::unique_ptr<Notifier>> arr;

    arr.emplace_back(std::make_unique<ConsoleNotifier>());
    arr.emplace_back(std::make_unique<EmailNotifier>("email@email.com"));

    for (const auto& x : arr)
    {
        x->notify("Message");
    }

    std::unique_ptr<Notifier> cpy{arr[1]->clone()};
    cpy->notify("message");

    pointer<int> x(10);
    return 0;
}
