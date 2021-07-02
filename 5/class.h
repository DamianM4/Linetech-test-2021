template <typename n>
class Example{
private:
    n x;

public:
    n& get_x() { return x; }

    Example() {}
    Example& operator=(Example const& ref) { return ref; }
    Example& operator=(Example&& ref) { return ref; }

};
