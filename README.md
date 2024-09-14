# Self Threadable class

*This is used to simplify the projects that need an asynchronous thread running on an object's method.*

*By standardizing the function to call and overriding it in a child's class, this will configure the thread for you with no configuration needed.*

### Example

```cpp
class MySensor : protected SelfThreadable {
  void async() {
    while(1) { /* do work */ }
    vTaskDelete(NULL);
  }
public:
  MySensor() : SelfThreadable("MyFancySensor") { async_start(); }
};
```
*This creates an object that will always start `async()` as a new thread, running indefinitely. Be sure the object exists while running it, or the code may break.*

*Deleting the object will kill the thread, so if you are sure that your object can be deleted (no raw pointers yet to be deleted and such), the thread deletion is done by SelfThreadable itself.*

*The string in `SelfThreadable`'s constructor is used to identify the thread in FreeRTOS task creation function. As simple as that.*

*`async_start()` is an option because maybe you want to configure something before effectively initializing the thread. This is the only thing you have to do to start it.*
