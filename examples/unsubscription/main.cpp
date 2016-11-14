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
 * \brief A callback associated with a subscription.
 */
static void callback(const event::event_t<std::string>& e) {
  dump(e);
}

/**
 * \brief Subscribes to 2 events `event.foo` and `event.qux` and
 * triggers these 2 subscriptions by emitting two messages.
 */
int main(void)
{
  event::emitter_t<std::string> emitter;

  // Subscribing to two events.
  auto foo = emitter.on("event.foo", [] (const event::event_t<std::string>& e) {
    dump(e);
  });

  auto bar = emitter.on("event.bar", callback);

  // Emitting these two events.
  emitter.emit("event.foo", "foo");
  emitter.emit("event.bar", "bar");

  // Unsubscribing from these two events.
  emitter.off(foo);
  emitter.off(bar);

  // Re-emitting these two events.
  emitter.emit("event.foo", "foo");
  emitter.emit("event.bar", "bar");
  return (0);
}
