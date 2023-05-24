#include <cstdint>
#include <string>


class ShapeType
{
private:
 std::string color_;
 int32_t x_ = 0;
 int32_t y_ = 0;
 int32_t shapesize_ = 0;

public:
  ShapeType() = default;

  explicit ShapeType(
    const std::string& color,
    int32_t x,
    int32_t y,
    int32_t shapesize) :
    color_(color),
    x_(x),
    y_(y),
    shapesize_(shapesize) { }

  const std::string& color() const { return this->color_; }
  std::string& color() { return this->color_; }
  void color(const std::string& _val_) { this->color_ = _val_; }
  void color(std::string&& _val_) { this->color_ = _val_; }
  int32_t x() const { return this->x_; }
  int32_t& x() { return this->x_; }
  void x(int32_t _val_) { this->x_ = _val_; }
  int32_t y() const { return this->y_; }
  int32_t& y() { return this->y_; }
  void y(int32_t _val_) { this->y_ = _val_; }
  int32_t shapesize() const { return this->shapesize_; }
  int32_t& shapesize() { return this->shapesize_; }
  void shapesize(int32_t _val_) { this->shapesize_ = _val_; }

  bool operator==(const ShapeType& _other) const
  {
    (void) _other;
    return color_ == _other.color_ &&
      x_ == _other.x_ &&
      y_ == _other.y_ &&
      shapesize_ == _other.shapesize_;
  }

  bool operator!=(const ShapeType& _other) const
  {
    return !(*this == _other);
  }

};