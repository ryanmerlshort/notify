# notify

Notify is a lightweight subscription-notification wrapper for data consumers ("users") to subscribe to a data producer's ("data source") notification of data arrival.

This supports multiple subscriptions by multiple users to a single notification. Any number of notifications can be used.

### Notes
- when the data source notifies the subscriber that the data is ready, the subscriber's callback function is called directly from the notifier's thread, so make sure that the subscriber does not block or perform any other non-thread-safe opearations
- the notifier's list must be initialized before the subscriber registers itself with it
- this implementation is heap based, but it only allocates, it doesn't ever free, instead it reuses discarded objects when a new object is requested:
  - a new subscription into an empty list gets a subscription object malloc'd and inserted into the list
  - a new subscription into a list with only active objects in it also gets a malloc'd subscription object
  - an unsubscription request gets its object's contents set to null, but the empty object remains in the list, to be used by another subscriber later
  - a new subscription that comes in when there's an empty object in the list (from a previous unsubscription) uses the null'd object instead of malloc'ing a new one

github.com/ryanmerlshort/notify

# Example
The entirety of the wrapper is in ``notify.c`` and ``notify.h``.
The examples folder contains three users and one data source. ``main.c`` controls these to show how the code is used. The ``.vscode`` folder contains ``tasks.json`` so it can be built from vscode by pressing ``ctrl+shift+B``, then running the ``main`` file generated at the command line with ``$./main``.


## License

MIT
