# event-emitter
> An event emitter implementation in C++, inspired by Node.js.

[![Build Status](https://travis-ci.org/HQarroum/event-emitter.svg?branch=master)](https://travis-ci.org/HQarroum/event-emitter)
![Production ready](https://img.shields.io/badge/production-ready-brightgreen.svg)

This module makes it possible to publish and subscribe to events in your application using C++11 semantics.

Current version: **1.0.0**

Lead Maintainer: [Halim Qarroum](mailto:hqm.post@gmail.com)

## Description

[Inversion of control (IoC)](https://en.wikipedia.org/wiki/Inversion_of_control) is a programming pattern commonly used in today's applications design, especially when building asynchronous apps. This emitter implementation aims at providing an expressive and simple interface for developers who would like to build event-based software components in their C++ applications using modern semantics.

The interface is compatible with both synchronous and asynchronous use-cases, and takes its inspiration from C++11 functional interfaces as well as [Node's EventEmitter](https://nodejs.org/api/events.html).

## Usage

This module is comprised of header-only modules, you simply need to include `event_emitter.hpp` in the units in which you would like to use the emitter.

### Instantiation

You call the `event::emitter_t` constructor by specifying a template parameter which will represent the type you would like to pass as a parameter to your listeners when emitting a message :

```c++
event::emitter_t<std::string> emitter;
```

> If you do not specifically want to transmit arguments across emitters and subscribers, you can omit the template parameter :

```c++
event::emitter_t<> emitter;
```

### Subscription

This implementation makes it possible to subscribe to events represented by a string as it is the case for most event emitters, but also to *types* which is another way of subscribing to a topic using compile-time constraints.

#### Event subscriptions

To subscribe to an event, you use the `.on` interface by passing as a first argument the name of the event you would like to subscribe to, and as a second a *callable* object.

All event listeners take a single parameter as an argument of type `const event::event_t<T>&` where `T` is the type you specify as a template argument when instantiating an `event::emitter_t` :

```c++
event::emitter_t<std::string> emitter;

emitter
  .on("event.foo", [] (const event::event_t<std::string>& e) {
    // Lambda called for every `event.foo`.
  })
  .on("event.bar", [] (const event::event_t<std::string>& e) {
    // Lambda called for every `event.bar`.
  }))
  .emit("event.foo", "foo")
  .emit("event.bar", "bar");
```

> Callable objects in C++11 includes lambda expressions, functors, free-functions and pointers to methods. Also note that it is possible to chain the calls to the methods exposed by the `emitter_t` instance.

#### Typed subscriptions

Sometimes it can be handy to bind an event to a type, especially when you want to add semantics to an event. Subscriptions to types as topics have several differences when compared to subscriptions to events represented by a string :

 - Events of any type can be published and listened to.
 - Events are evaluated at compile-time.
 - It is possible to add semantics to an event. For instance, when you want to subscribe to all events on an emitter instance. Most emitters use custom globbing characters (such as `'*'`) to express this wish. This lack of semantic requires the user to be aware of this particularity or edge-case, and his subscription cannot be checked at compile-time.
 - This method requires [Runtime type information (RTTI)](https://en.wikipedia.org/wiki/Run-time_type_information) to be enabled on your compiler.

You can subscribe to a type using an `emitter_t` instance as follows :

```c++
/**
 * \brief We assume a topic of type `topic_t` which we
 * define as a pair between a name and a value.
 */
using topic_t = std::pair<std::string, std::string>;

emitter.on<topic_t>([] (const topic_t& topic) {
  // Received a topic_t event.
})
.emit(topic_t({ "foo", "bar" });
```

#### Semantic subscriptions

Semantic subscriptions are typed subscriptions, but with types already defined by the library. The goal is to provide the ability to subscribe to lifecycle events pre-defined by the library.

> In the following examples, `T` is the type you have specified as a first template parameter of the `emitter_t`.

##### Listen to subscriptions

To be notified when someone has subscribed to a particular event on the emitter instance, you can do the following.

```c++
emitter.on<subscription_t<T>>([] (const subscription_t<T>& s) {
  // This is the callback associated with the subscription.
  auto& callable = s.function();
  // This is the topic associated with the subscription.
  auto& topic = s.topic();
});
```

##### Listen to typed subscriptions

To be notified when someone has subscribed to a typed event on the emitter instance, you can do the following :

```c++
emitter.on<typed_subscription_t<T>>([] (const typed_subscription_t<T>& s) {
  // This is the callback associated with the subscription.
  auto& callable = s.function();
  // This is the type index associated with the subscription.
  auto type = s.type_index();
});
```

##### Listen to emitted events

To be notified when someone has published an event on the emitter instance, whatever the event, you can do the following :

```c++
emitter.on<event_t<T>>([] (const event_t<T>& e) {
  // This is the topic associated with the event.
  auto& topic = e.topic();
  // This is the value associated with the event.
  T& value = e.value();
});
```

#### Removing a subscription

Each subscription made using the `.on` interface returns an object of type  `subscription<T>` for regular events, and `typed_subscription<T>` for typed events. To remove a subscription, you simply have to pass the subscription object to the `.off` interface :

##### For regular events

```c++
// Subscribing a lambda function to the event `foo`.
auto s = emitter.on("foo", [] (const event_t<T> e) {});
// Removing the subscription to `foo` for the previous lambda only.
emitter.off(s);
```

##### For typed events

```c++
// Subscribing a lambda function to the events of type `topic_t`.
auto s = emitter.on<topic_t>([] (const topic_t& t) {});
// Removing the subscription to the type `topic_t` for the previous lambda only.
emitter.off(s);
```
