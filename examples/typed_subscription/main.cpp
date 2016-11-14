#include <iostream>
#include <string>
#include <utility>
#include <event_emitter.hpp>

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
 * \struct topic_t
 * \brief Identifies a topic on the broker.
 */
struct topic_t
{
  /**
   * \constructor
   */
  topic_t(const std::string& topic)
    : m_topic(topic)
  {}

  /**
   * \return the topic name.
   */
  const std::string& name() const {
    return (m_topic);
  }

private:
  const std::string m_topic;
};

/**
 * \brief Subscribes to 2 typed events and triggers two events
 * associated with these subscriptions.
 */
int main(void)
{
  event::emitter_t<std::string> emitter;

  // Subscribing to two typed events.
  emitter.on<topic_t>([] (const topic_t& topic) {
    std::cout << "Received message from " << topic.name() << std::endl;
  })
  .on<foo_t>([] (const foo_t& foo) {
    std::cout << "Received foo_t with " << foo << std::endl;
  });

  // Emitting two typed events.
  emitter.emit(topic_t("topic.foo"));
  emitter.emit(foo_t({ "foo", "bar" }));
  return (0);
}
