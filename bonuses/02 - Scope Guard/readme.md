# Bonus 02- Scope Guard

## Scope Guard

Design a way to delay the invocation of void(\*)() procedures to the end of the scope. Also implement a way to dismiss the invocation at will. Make sure that one delayed invocation will NEVER be done twice.

## Example + Notes

- Don't worry about the new syntax (try / catch / throw) for now, it's just part of the example (to make sure it works without UB).
- Comments surrounded by <> are where you have to call your functions (Feel free to choose any interface that makes sense to you)
- Generally you want 2 versions for this that behave slightly different, one for finalizing and one for undoing errors but this is a simple toy example

```c++
int main()
{
    try
    {
        // You can use it to finalize some operation at the end of the scope

        // <Somehow delay the invocation of []() { std::cout << "Finalize Operation 1\n"; }>
        std::cout << "Operation 1\n";

        // Or undo an operation that failed
        // <Somehow delay the invocation of []() { std::cout << "Rollback Operation 2\n"; }>
        std::cout << "Operation 2\n";
        // <Somehow dismiss the the invocation>
        // ^ This one didn't fail so we don't undo it

        // <Somehow delay the invocation of []() { std::cout << "Rollback Operation 3\n"; }>
        std::cout << "Operation 3\n";
        throw "Error with Operation 3"; // Error
        // <Somehow dismiss the the invocation> // This won't get called because of the error above
    }
    catch (const char * error)
    {
        std::cout << error << '\n';
    }

    return 0;
}
```

Output

```
Operation 1
Operation 2
Operation 3
Rollback Operation 3
Finalize Operation 1
Error with Operation 3
```
