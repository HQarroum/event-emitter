#include <iostream>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <utility>
#include <event_emitter.hpp>

using namespace event;

/**
 * \brief Defining the type `foo_t` as a simple
 * pair of strings.
 */
using foo_t = std::pair<std::string, std::string>;

/**
 * \brief Helper for dumping a pair on an output stream.
 */
std::ostream& operator<<(std::ostream& os, const foo_t& foo) {
  os << foo.first << " - " << foo.second;
  return (os);
}

/**
 * \brief A mapping between types and their human-readable
 * representation.
 */
static std::unordered_map<std::type_index, std::string> types = {
  { typeid(subscription_t<std::string>), "subscription_t<std::string>" },
  { typeid(typed_subscription_t<std::string>), "typed_subscription_t<std::string>" },
  { typeid(event_t<std::string>), "event_t<std::string>" },
  { typeid(foo_t), "foo_t" }
};

/**
 * \brief Subscribes to 2 typed events and triggers two events
 * associated with these subscriptions.
 */
int main(void)
{
  event::emitter_t<std::string> emitter;

  // Subscribing to semantical events.
  emitter
    .on<typed_subscription_t<std::string>>([] (const typed_subscription_t<std::string>& s) {
      auto type = types[s.type_index()];
      std::cout << "A subscription to " << type << " has been added." << std::endl;
    })
    .on<subscription_t<std::string>>([] (const subscription_t<std::string>& s) {
      std::cout << "A subscription to topic " << s.topic() << " has been added." << std::endl;
    })
    .on<event_t<std::string>>([] (const event_t<std::string>& e) {
      std::cout << "An event " << e.topic() << " has been emitted." << std::endl;
    });

  // Subscribing to regular events and typed events.
  emitter
    .on("event.foo", [] (const event_t<std::string> e) {
      std::cout << "Topic " << e.topic() << " received value " << e.value() << std::endl;
    })
    .on<foo_t>([] (const foo_t& foo) {
      std::cout << "Received foo_t with " << foo << std::endl;
    });

  // Emitting two typed events.
  emitter.emit("event.foo", "foo");
  emitter.emit(foo_t({ "foo", "bar" }));
  return (0);
}
