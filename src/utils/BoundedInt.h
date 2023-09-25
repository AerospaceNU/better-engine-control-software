#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDED_INT
#define BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDED_INT

template <int lowerBound, int upperBound>
class BoundedInt {
    static_assert(lowerBound < upperBound, "BoundedInt must be instantiated with an upper bound greater than its lower bound!");
public:
    BoundedInt() = default;

    explicit BoundedInt(int val) {
        if (val > upperBound) {
            val = upperBound;
        }
        if (val < lowerBound) {
            val = lowerBound;
        }

        this->value = val;
    }

    operator int() const {
        return this->value;
    }

private:
    int value;
};



#endif //BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDED_INT
