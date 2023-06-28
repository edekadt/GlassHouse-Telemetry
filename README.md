# Setup
### Clone the GlassHouse repository into your project root directory. We recommend adding the project as a git submodule using
```git submodule add https://github.com/edekadt/GlassHouse-Telemetry GlassHouse-Telemetry```

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

# Usage

## Initialization
GlassHouse works off of an internal single instance, so you don't need to worry about creating or deleting an object. Boot the tracker with GlassHouse::init(...) at the start of your program and close it at the end with GlassHouse::close(). 

There are two versions of GlassHouse::init(...). The first:
```cpp
GlassHouse::init(SerializerType sType, PersistorType pType, std::string destination)
```
allows you to specify from among the built-in options for serialization (json) and persistence (local file or server), as well as specifying a directory or url to persist in.

The second:
```cpp
GlassHouse::init(ISerializer serializer, IPersistor persistor)
```
allows you to make use of user-defined serialization and/or persistence systems.

## Configuration
By default, the tracker only writes its events at the end of the program, in GlassHouse::close(). There are two additional settings that can be adjusted to write more often, using the following functions: 
```cpp
void setEventLimit(size_t eventLimit)
void setTimeLimit(double timeLimit)
```
The event limit refers to a number of events that can be accumulated in the system; once the number exceeds this limit, the events are persisted. Note: due to the concurrent queue used internally, the number of events stored is only an estimate.

The time limit refers to the maximum amount of time that is allowed to pass between two flushes. Any time a flush occurs, the timer is reset. Once the timer exceeds the established limit, stored events are flushed and persisted.

## Tracking events
By default, the system only collects two events: SESSION_START and SESSION_END; the start and end of the session. The base library also includes the GAME_START, GAME_END, LEVEL_START and LEVEL_END events, but it is down to the user when each of these events is sent.

To track an event, call GlassHouse:enqueue(...) passing a new pointer to the desired event. The memory created is later deleted automatically. For example:
```c++
GlassHouse::enqueue(new LevelStart());
```

## Creating new event types 
You can add new types of events with unique attributes by inheriting from the Events class found in Events.h. A new event class requires an eventID, which is a string passed to the constructor of the base class, and used to discriminate different types of events.

There is no control to prevent the user from creating different event types with the same name. However, doing so won't cause any issues beyond potential confusion.

Any event can have additional data added to it via the Event.add(std::string key, Serializable value) method. The value added can be of any type that is implicitly castable to **size_t**, **int32_t**, **double**, **std::string** or **bool**. Each value is eventually serialized with its key.

## Creating a new serialization system
To serialize your data to a custom format, create a new object that inherits from ISerializer, then override the 
```cpp
void serialize(const Event& event, std::string& serializable)
```
method to serialize a single event, storing the result in the string argument.

### Additional options
There are four other string fields of the serializer that can be used to add formatting:

**fileFormat** is the extension that the resulting file will use, including the '.' (i.e.: ".json").

**openingString** is written once at the very beggining of the file.

**separator** is written in between every two events, but not before the first one or after the last one (useful for things like line jumps).

**closingString** is written once at the end of every file.

## Creating a new persistence system
To store the generated telemetry in a custom destination, create a new object that inherits from IPersistor and override the following methods:
 ```cpp
void persist(const std::string& s)
void open()
void close()
 ```
**persist(const std::string& s)** defines how a serialized string is stored in the destination.
**open()** is called at the start of the program, and should open the file, establish connection to server, etc.
**close()** is called at the end of the program, and should close the file, end connection to server, etc.

## Error Control
If an exception causes your game to close before the SESSION_END event can be sent, you can call GlassHouse::emergencyClose() to seal off the json file with the correct syntax for it to be readable.

# Output
Events captured by the telemetry system are stored in a json file located by default in the folder GlassHouse-data, within the same directory as your solution. Each session generates a uniquely ID'd file containing all the events.

To change the directory in which files are stored, pass the desired directory as an argument of GlassHouse::init().

We recommend excluding the folder you choose from your project's source code.

## Server
To store your data on a remote server instead of in a local file, use the GlassHouse::setWriteMode(...) function. To avoid splitting data between the two locations, this should be done immediately after initializing the library.

To launch the testing server , go to .\Utils\TestServer folder, unzip the node_modules.zip then  run powershell and type the command.
```bash
node .\server.js
#Or node .\Utils\TestServer\server.js if you are on solution dir
```
