## Setup
### Clone the GlassHouse repository into your project root directory.
### In your game's VS solution, open the Properties tab of your main project and follow these instructions: 
Place the following two commands in the COMMAND LINE field of Build Events -> Post-Build Event:
```
xcopy /y "$(SolutionDir)GlassHouse-Telemetry\GlassHouse\build\$(Configuration)\GlassHouse.dll" "$(OutDir)"

xcopy /y "$(SolutionDir)GlassHouse-Telemetry\GlassHouse\Utils\curl-8.0.1\lib\libcurl.dll" "$(OutDir)"
```
Under Linker -> General -> Additional Library Directories add the following line:
```
.\GlassHouse-Telemetry\GlassHouse\build\$(Configuration)
```

Under C/C++ -> General -> Additional Include Directories add the following 2 lines:
```
.\GlassHouse-Telemetry\GlassHouse\Utils\json-develop\include
.\GlassHouse-Telemetry\GlassHouse\src
```

## Usage
GlassHouse works off of an internal single instance, so you don't need to worry about creating or deleting an object. Simply boot the system with GlassHouse::init() at the start of your program and close it at the end with GlassHouse::close().

By default, the system only collects two events: SESSION_START and SESSION_END; the start and end of the session. The base library also includes the GAME_START, GAME_END, LEVEL_START and LEVEL_END events, but it is down to the user when each of these events is sent.

To send an event, call GlassHouse:enqueue(...) passing a new pointer to the desired event. For example:
```c++
GlassHouse::enqueue(new LevelStart());
```

You can add new types of events with unique attributes by inheriting from the Events class found in Events.h. However, you must first extend the enum that lists all of the event types. 
In the c++ file that defines your new event subclasees, define EXTEND_EVENT_DEFS in the following format:
```c++
#define EXTEND_EVENT_DEFS ,\
NEW_EVENT_1, \
NEW_EVENT_2, \
NEW_EVENT_3, \
NEW_EVENT_4, \
NEW_EVENT_5
```
Alternatively, in a single line:
```c++
#define EXTEND_EVENT_DEFS , NEW_EVENT_1, NEW_EVENT_2, NEW_EVENT_3, NEW_EVENT_4, NEW_EVENT_5
```
IMPORTANTLY, this redefinition should appear before you include Events.h

### Subclass Serialization
In order to correctly serialize the new attributes of a custom event, you must override the serializeToJSON() method, as so:
```c++
nlohmann::json WoundStart::serializeToJSON() const override
{
    nlohmann::json data = Events::serializeToJSON();

    data.push_back({ "AttributeName", attribute });

    return data;
}

```
## Error Control
If an exception causes your game to close before the SESSION_END event can be sent, you can call GlassHouse::emergencyClose() to seal off the json file with the correct syntax for it to be readable.

## Data

Events captured by the telemetry system are stored in a json file located by default in the folder GlassHouse-data, within the same directory as your solution. Each session generates a uniquely ID'd file containing all the events.

To change the directory in which files are stored, pass the desired directory as an argument of GlassHouse::init().

## Server
To store your data on a remote server instead of in a local file, use the GlassHouse::setWriteMode(...) function. To avoid splitting data between the two locations, this should be done immediately after initializing the library.

To launch the testing server , go to .\Utils\TestServer folder, unzip the node_modules.zip then  run powershell and type the command.
```bash
node .\server.js
#Or node .\Utils\TestServer\server.js if you are on solution dir
```
