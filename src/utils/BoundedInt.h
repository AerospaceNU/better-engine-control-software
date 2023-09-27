#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDED_INT
#define BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDED_INT

/**
 * Class for representing ints that are limited by certain bounds
 * 
 * These bounds are inclusive,
 * 
 * For example, BoundedInt<0,100> will accept 0 and 100, but truncate to 0 if 
 * passed -1 and truncate to 100 if passed 101
 * 
 * This type will fail to compile if given an upperBound less than lowerBound
 * 
 * This type implicitly converts to int, so
 * int foo = BoundedInt<0,100>(10); will compile
 * 
*/
template <int lowerBound, int upperBound>
class BoundedInt {
    static_assert(lowerBound <= upperBound, "BoundedInt cannot be instantiated with an upper bound lower than its lower bound!");
public:
    BoundedInt() = default;

    explicit BoundedInt(int val) noexcept {
        if (val > upperBound) {
            val = upperBound;
        }
        if (val < lowerBound) {
            val = lowerBound;
        }

        this->value = val;
    }

    operator int() const noexcept {
        return this->value;
    }

private:
    int value;
};



#endif //BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDED_INT
