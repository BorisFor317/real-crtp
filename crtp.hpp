#include <cstddef>

template <typename Impl> class ICrtpCounter {
public:
  void Count(std::size_t value) {
    static_cast<Impl*>(this)->Count(value);
  }

  std::size_t GetValue() { return static_cast<Impl*>(this)->GetValue(); }
};

class CrtpCounter : public ICrtpCounter<CrtpCounter> {
public:
  CrtpCounter(std::size_t initial = 0) : counter_(initial) {}

  void Count(std::size_t value) { counter_ += value; }

  std::size_t GetValue() { return counter_; }

private:
  std::size_t counter_;
};
