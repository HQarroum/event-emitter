#include <iostream>
#include <event_emitter.hpp>

using namespace event;

class topic_t {

  std::string m_subject;

public:

  topic_t(const std::string& subject) : m_subject(subject) {}

  topic_t(const topic_t& t) = default;

  const std::string& subject() const {
    return (m_subject);
  }
};

void callback2(const event::event_t<>&)
{
  std::cout << "foo once called" << std::endl;
}

int main(void)
{
  /*event::emitter_t<std::string> emitter;

  auto c = [&] (const event::event_t<std::string>& e) {
    std::cout << "foo listener called with " << e.topic() << std::endl;
  };

  auto s1 = emitter.on("foo", c);
  auto s2 = emitter.on("foo", callback2);
  emitter.emit("foo", "Hello");
  emitter.off("foo", s1);
  emitter.off("foo", s2);
  emitter.emit("foo", "toto");

  emitter.on("event", [] (const event::event_t<std::string>& e) {
    std::cout << "Received event !!" << std::endl;
  }).on("event2", [] (const event::event_t<std::string>& e) {
    std::cout << "Received event2 !!" << std::endl;
  });
  emitter.emit("event", "foo")
  .emit("event2", "foo")
  .emit("event3", "foo");

  auto tc = [] (const topic_t& s) {
    std::cout << "Topic listener called " << s.subject() << std::endl;
  };

  auto tc1 = emitter.on<topic_t>(tc);
  emitter.emit(topic_t("toto"));
  emitter.off<topic_t>(tc1);
  emitter.emit(topic_t("titi"));
  */

  event::emitter_t<std::string> emitter;

    emitter
      .on<subscription_t<std::string>>([] (const subscription_t<std::string>& e) {
        std::cout << "A subscription to type " << e.topic() << " has been added." << std::endl;
      })
      .on<typed_subscription_t<std::string>>([] (const typed_subscription_t<std::string>& e) {
        //std::cout << "A subscription to a type has been added." << std::endl;
      })
      .on<event_t<std::string>>([] (const event_t<std::string>& e) {
        std::cout << "An event " << e.topic() << " has been emitted." << std::endl;
      })
      .on<typed_event_t<std::string>>([] (const typed_event_t<std::string>& e) {
        //std::cout << "A typed event has been emitted." << std::endl;
      })
      .on("foo", [] (const event_t<std::string>& e) {
        std::cout << "foo called with " << std::endl;
      })
      .on<topic_t>([] (const topic_t& topic) {
        //std::cout << "Topic called with value " << topic.subject() << std::endl;
      });

      emitter.emit("foo", "toto");

  for (size_t i = 0; i < 10000; ++i) {
      //emitter.emit("foo", "toto").emit(topic_t("foo"));
  }
  return (0);
}
