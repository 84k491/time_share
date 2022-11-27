Hello!

----------------------------------------------------------------------------------------------

Project consists of a client and a server:
Server:
    - Gets a time from the host system and sends it to the broadcast as a timestamp(ms) message every 100ms.
    - Can run without any client or with multiple instances.
Client:
    - Receives server's messages and prints: own timestamp, timestamp in a message, difference between those two.
    - Can run multiple instances on the same port.

Both client and server:
    - Pick a port from the arguments or choose the default one.
    - Able to stop gracefully on USR2 signal caught.
    - Have time logic (business layer) decoupled with transport layer.
    - Tested to work on a single host and across hosts in a home network.
    - Main functionality covered by GTest unit tests. Also have one end-to-end test.
    - Built with CMake.
    - Have 3 build types: Release, Debug and ASan

All projects can be built with "build.sh" script in a corresponding directory.
There is a one-for-all build script "build_all.sh" that compiles all projects and runs tests after.

Requires clang, cmake, gtests installed.

Compiled binaries are placed in "./bin"
