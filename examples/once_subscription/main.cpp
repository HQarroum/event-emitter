#include <iostream>
#include <string>
#include <event_emitter.hpp>

/**
 * \brief Prints the description of the given event
 * on the standard output.
 */
static void dump(const event::event_t<std::string>& e) {
  std::cout << "Event of topic " << e.topic() << " received with value '" << e.value() << "'" << std::endl;
}

/**
 * \brief Subscribes to 2 events `event.foo` and `event.qux` and
 * triggers these 2 subscriptions by emitting two messages.
 */
int main(void)
{
  event::emitter_t<std::string> emitter;

  // Subscribing to two events.
  emitter.on("event.foo", [] (const event::event_t<std::string>& e) {
    dump(e);
  })
  .once("event.foo", [] (const event::event_t<std::string>& e) {
    dump(e);
  });

  // Emitting the same event multiple times.
  emitter.emit("event.foo", "foo");
  emitter.emit("event.foo", "bar");
  emitter.emit("event.foo", "baz");
  emitter.emit("event.foo", "qux");
  return (0);
}
