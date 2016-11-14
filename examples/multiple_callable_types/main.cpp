#include <iostream>
#include <string>
#include <event_emitter.hpp>

using namespace std::placeholders;

/**
 * \brief Prints the description of the given event
 * on the standard output.
 */
static void dump(const event::event_t<std::string>& e) {
  std::cout << "Event of topic " << e.topic() << " received with value '" << e.value() << "'" << std::endl;
}

/**
 * \brief A functor associated with a subscription.
 */
struct functor
{
    void operator()(const event::event_t<std::string>& e) const {
      dump(e);
    }
};

/**
 * \brief A sample structure containing a method associated
 * with a subscription.
 */
struct structure
{
  void method(const event::event_t<std::string>& e) const {
    dump(e);
  }
};

/**
 * \brief Definition of a method pointer to `method` member of `stucture`.
 */
void (structure::*method_ptr)(const event::event_t<std::string>& e) const = &structure::method;

/**
 * \brief A callback associated with a subscription.
 */
static void callback(const event::event_t<std::string>& e) {
  dump(e);
}

/**
 * \brief Registers a subscription with 4 different types
 * of callable objects.
 */
int main(void)
{
  event::emitter_t<std::string> emitter;
  functor                       f;
  structure                     s;

  emitter.on("event.foo", [&] (const event::event_t<std::string>& e) {
    dump(e);
  })
  .on("event.bar", callback)
  .on("event.baz", f)
  .on("event.qux", std::bind(method_ptr, &s, _1))
  .emit("event.foo", "foo")
  .emit("event.bar", "bar")
  .emit("event.baz", "baz")
  .emit("event.qux", "qux");
  return (0);
}
