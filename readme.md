# Build & Run unit tests using Docker
```
docker build -t docker_alm .
docker run --rm docker_alm:latest
mkdir coverage-html  && docker run --rm -v $(pwd)/coverage-html:/app/build/coverage-html docker_alm:latest
```

# Build & Run unit tests

Ensure you have gcc or any c++ compiler added into your system path. Then, run the following commands on Windows for example:

```
export CC=/c/TDM-GCC-64/bin/gcc
export CXX=/c/TDM-GCC-64/bin/g++

mkdir build
cd build
cmake .. -G "MinGW Makefiles"
make -j8
ctest
```

Or you can run directly from project root directory:
```
cmake -S . -B build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCODE_COVERAGE=ON
cmake --build build
```

# Build & Run application tests
This application allows playing manually with the alarm system.
It requires `sudo apt-get install sox` to play the audio beeps on Linux

```
./build/test/alarm_app
Press following keys :
  - 'h' for activating/deactivating high prio alarm 
  - 'm' for activating/deactivating medium prio alarm 
  - 'l' for activating/deactivating low prio alarm 
  - 'q' for quitting 
Output :
  - 'X' is equivalent to a 100ms beep window
  - '.' is equivalent to a 100ms no-beep window
...................XX...XX...XX.......XX...XX..........XX...XX...XX......
.XX...XX..........XX...XX...XX.......XX...XX........XXXXX.....XXXXX......
..............................XXXXX.....XXXXX............................
........XXXXX.....XXXXXXX...XX...XX.XXXXX...............XXXXXXXXXX.......
.........................................................................
...........XXXXXXXXXX....................................................
..............
```

# IEC 60601-1-8

### Sections

| **Category**                  | **Key Properties / Requirements**                                                                                                                                         |
|------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Alarm Signal Types**       | - **Auditory** and/or **visual** signals<br>- Alarms must be noticeable and distinguishable in various environments                                                      |
| **Alarm Prioritization**     | - Three priority levels: **High**, **Medium**, **Low**<br>- Priorities based on potential risk to patient if alarm is not addressed                                      |
| **Audible Alarm Sounds**     | - Standardized tones for each priority level<br>- Minimum and maximum sound pressure levels defined<br>- Sounds must be **distinct**, **recognizable**, and **non-melodic** |
| **Visual Indicators**        | - Colors linked to priority (e.g., Red for High, Yellow for Medium)<br>- Flashing rates and visibility requirements                                                       |
| **User Interface & Controls**| - Clear display of alarm cause, location, and priority<br>- Alarm **pause**, **reset**, and **silence** functions must be intuitive and documented                       |
| **Alarm Conditions**         | - Must be based on pre-set thresholds or system-detected conditions<br>- False alarms must be minimized                                                                  |
| **Human Factors**            | - Usability engineering considerations to reduce **alarm fatigue** and improve recognition and response                                                                  |
| **Alarm Logging**            | - Systems must log alarm events and responses for review, especially in critical systems                                                                                 |
| **Interoperability**         | - Alarm systems must not interfere with other equipment and should support integrated clinical environments                                                              |
| **Testing & Compliance**     | - Requires specific tests for sound pressure, light intensity, and user interface design                                                                                 |

### Alarm properties

Alars might have specific properties which are described in the table below:

| **Property**          | **Meaning / Description**                                                                                                                                       |
|-----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Audible Alarm Signal** | An alarm that produces a **sound** to alert the operator. Required for most high-priority conditions unless specifically exempted.                             |
| **Visible Alarm Signal** | A **visual indicator**, such as a flashing light or display message, associated with the alarm. Often color-coded (e.g., red = high priority).               |
| **Latchable**            | Once triggered, the alarm **remains active** (latched) even if the condition that caused it goes away. Requires **manual acknowledgement** to clear.         |
| **Non-latchable**        | The alarm automatically **resets or deactivates** when the condition that triggered it is no longer present.                                                |
| **Mutable**              | The **sound can be temporarily silenced** by the operator (typically for a defined period). Visual indicator remains active.                                 |
| **Non-mutable**          | The audible signal **cannot be silenced** until the alarm condition is resolved.                                                                             |
| **Pause Function**       | Temporarily **suspends alarm generation** during known, non-critical events (e.g., patient movement). Must automatically resume after a set time.           |
| **Resettable**           | Allows the user to **manually clear** the alarm once the condition has been resolved. Typically associated with latched alarms.                             |
| **Priority Level**       | Classifies alarms into **High**, **Medium**, or **Low** priority based on the potential risk if not addressed.                                              |
| **Alarm Signal Inhibit** | Feature allowing suppression of specific alarms during system start-up, testing, or maintenance, with safeguards to avoid misuse.                           |
| **Alarm Message**        | A **textual or graphical description** of the alarm cause displayed to the operator. Must be clear, concise, and meaningful.                               |
| **Indication of Alarm Source** | The system must clearly identify the **origin or location** of the alarm condition, especially in multi-parameter or networked systems.                 |
| **Alarm History / Log**  | Record of alarms and their statuses (triggered, acknowledged, cleared) must be maintained for analysis and traceability.                                    |
| **Alarm Signal Duration**| Defines how long an audible or visual signal continues. Must be sufficient for detection but avoid alarm fatigue.                                            |
| **Audibility Requirements** | Alarm sounds must meet specified **sound pressure levels**, frequencies, and repetition rates depending on priority level.                                |
| **Visual Signal Requirements** | Visual indicators must be **sufficiently bright, correctly colored**, and visible from the intended viewing direction and distance.                   |


