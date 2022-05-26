#include <cstddef>

class INormalCounter {
public:
  virtual void Count(std::size_t value) = 0;
  virtual std::size_t GetValue() = 0;
};

class NormalCounter : public INormalCounter {
public:
  NormalCounter(std::size_t initial = 0) : counter_(initial) {}
  void Count(std::size_t value) override { counter_ += value; }
  std::size_t GetValue() override { return counter_; }

private:
  std::size_t counter_;
};
