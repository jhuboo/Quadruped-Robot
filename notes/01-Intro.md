# Introdution

## Structure of Robot

Robot Definition
> A robot is a machine that combines electro-mechanical systems, computing, sensing, and actuation; its capabilities can fall along a large spectrum of intelligence and autonomy.

The above definition implies the following cycle: sensing -> computation -> actuation -> effect with environment -> sensing


### Components

1. Mechanical System
	- Comprises of the physical components of the robot and determines how the robot interacts with the environment (actuation). This is abrasted through a model, generally in the form of an ODE, or state machine, or combination of both.

2. Perception
	- Covers sensors and algorithms the robot can use of get a sense of the state of its environment. Ie, use an IR sensor to know how far it is from a barrier, or use a cameraand analyze it to perform a certain task.

3. Control & Decision Making
	- Algorithms that command the robot to move according to its high-level objectives and by reacting to its environment. Ie, use LIDAR to know when it reaches a target, then pick something off a table.

4. Mapping & Localization
	- Methods to model and represent the state of the environment from the perspectiv of the robot. Using sensor data & computations, or ML algorithms, the robot can build a map of the different obstacles in the environment.

5. Planning
	- Methods and algorithms to go FROM environment repr together with high-level objectives TO low-level plan for control of robot (ie. trajectory).


### Time Scales

1. Fast Time Scale
	- Typically associated with low-level perception and control, which allows to quickly react to noise and disturbances, but cannot reliably achieve objs with long-time horizons. Ie, microcontrollers like Arduino used to compute fast time scale control.

2. Slow Time Scale
	- Typically associated to mapping and high-level planning. Algorithms running at this time scale are not fast enough to cope with low latency, to environmental changes, but allow to consider long-term objectives. Ie, Single Board Computers (SBCs), like the Pi are good for slow time scale operations since it has an onboard OS.


## Hardware Organization (Computation, Sensors, Actuators)

### Computation

1. Embedded Systems
	- Computers dedicated to specific purposes in an electro-mechanical system

2. Microcontrollers
	- No OS, strigent real-time, low-level. Good for very low-level control (ie. motor speed) and interfacing (ie. get dat from an analog sensor). Ie. Arduino

3. Single Board Computers (SBCs)
	- OS (typically Linux variant), Non-Strigent real-time, High-level. Ie. Raspberry PI


### Sensors

1. Monocular & Stereo Cameras
	- *Monocular*: camera has only one lens and image sensor. Only 2D image capable.
	- *Stereo*: camera has 2 or more lenses with separate image sensor for each lens. This allows the camera to capture 3D images by correlating the two images and triangulating the points in space.

2.  Depth Cameras
	- *Structured Light Cameras*: structured light from IR emitter is emitted onto the object. Camera detects IR that bounces back. Camera takes picture of sturctured light distorted by the geometry of the object. By correlating the distorted pattern with the one orignally projected, it is possible to recover the depth information via triagulation method. The larger the distance, the more accurate the measurements, but self-occlusion become more pronounced.
	- *Time of Flight Cameras*: spatially uniform but time-modulated light is projected on the scene. The time difference between emission and reception at the sensor is proportional ot the distance.

3. Ultrasonic Sensors
	- Sensor measrues distance by recording time it takes for sound wave to return. However, if object is soft, porous or oriented in a certain way, it may be undetectable.

4. LIDAR
	- Combination of scanning laser & monocular camera. Functions similar to depth camera but instead of emitting flash of light rays, it scans the environment with a single light ray. Measures the reflected light pulses, and return time with a light sensor. Can be 2D or 3D.

5. GPS
	- Constellation of 35 satellites in LEO orbit Earth 2x per day. Every spot on Earth is in sight of four satellites at a time. Each satellite has an atomic clock. This system works by communicating with GPS receivers on land. The satellite sends a signal to the receiver tracking the exact time the signal was sent and the exact time it was received. The receiver is sent a signal from at least 3 satellites and uses triangulation to know their exact position in the sky (by calculating the time it takes to get signals from 3 GPS satellites, it can determine its position on Earth!). The 4th satellite is used to keep time because the GPS receiver is not armed with an atomic clock. The receiver will know its East, North, and altitude positions.

6. IMU (Inertial Measurement Units)
	- Device that measures an object's specific force, magnetic field, and angular rate with accelerometers, magnetometers, and gyroscopes. IMU works in the following way: An accelerator works by measuring changes in acceleration an object undergoes by first measuing the change in voltage. Say there is a spring and mass model. A known mass is contained in the box, and suspended by springs on all sides. When the box, and mass have a force applied to them, and move, the springs deform. Using circuitry, the deformation can be converted into a voltage. This voltage change is sent through an AC to DC converter, and turned into a number presenting acceleration. A comman way voltage into acceleration is incorporating capacitors into the mass-spring model. With a capacitor on th emass and on the walls of the box, any distance the mass moves will change the voltage going through the capacitors on the wall. Therefore, the change in voltage represents a change in accelerative forces, and be integrated into a distance.


### Actuators
> Typically represented by motors. Other options include piezoelectric actuators (for high-frequency operation such as RoboBee) and soft actuators

1. Brushed DC Motors
2. Brushless DC Motors



## Software Organization

### General Development Strategy

Rule to maintain sanity: use modularity. Start with low-level functionality, make a way to test it, build on top.

Software Stack for ROSBot
1. Linux
2. Robotic Operating System (ROS)

### ROS Fundamentals

1. Package
	- A "module" of the ROS system, which provides a set of nodes, message defs (topics), and a dir with at least the files `package.xml` and `CMakeLists.txt`
	- "package.xml" contains general info about the package, such as a description, the contact info of the maintainer, the dependencies of this pkg on other pkgs.
	- "CMakeLists.txt" contains info about compiling the code for scripts, nodes, and messages/services. This is mainly required for C/C++ code and messages/services. If you only have Python code, this is not required.
	- Packages commonly contain the subdirs:
		- `/src`: with source code for the nodes
		- `/script`: with programs that are typically commands that do not create nodes
		- `/launch`: with launch files

2. Workspaces
	- A special dir contiaining all the pkgs that are under development (that are not system pkgs)
	- The ROS workspace is in dir `ros_ws`
	- "Making" a workspace means to compile all the code and message definitions in the pkgs in that workspace. This is done with the command "catkin make"

3. Nodes
	- A node is a process that is intended to run continously on your robot, and communicates with other nodes typically using ROS messages exchanged on ROS topics. Each node has a name. The command "rosnode list" gives the names of nodes that are running.
	- Typically the name of the node is the same as one of the executable, although it could be different. As a consequence, the same executable can be launded multiple times under different names, creating different nodes.
	- Nodes can be started manually using the command "rosrun \<pkgname\> \<nodename\>"
	- NOTE: Since each node is supposed to run continously, each one occupies a terminal. The master node needs to be run first.

4. Master Node
	- Special node that is started with the command "roscore"
	- The output of the master node to the console provides info on which nodes are being run, and which have stopped running
	- It is possible to configure a machine to use a roscore running on another machine on the same network. In this way, topics can be sent.


### Topics and Message Definitions

> The most way to communicate between nodes is through messages exchanged over topics.

Topics are "channels" on which nodes can either publish (send msgs) or subscribe (receive msgs). A list of topics can be see using the command "rostopic list". Each topic is assigned a message type at its definition. These types are defined in ROS packages (either system or user-defined), and are essentially structures whwere the fields can be some primitive types or other msg types. Topics can transfer msgs only of the type with which they have been defined. The info about the msg type of a topic can be found using:

	 `rostopic info \<topicname\>`

While topics are "channels", messages are the "packets" exchanged on these "channels". Youcan see what message are exchanged over topics. Loosely speaking, you will have:
- "input" nodes, that only publish information
- "processing" nodes, that subscribe to a topic and publish the data on another after transforming it
- "output" nodes, that simply visualize the results


### Header Message Structure

> A structure containing meta-information about a package.

***NOTE 1***: The field `seq` is automatically populated when a msg is published. However, the fields `frame_id` and `stamp` need to be manually populated if they are used

***NOTE 2***: The field `stamp` is a time struct where seconds and nanoseconds are separated. The Python implementation has the method `.to_sec()` to obtain the combination of the two fields in a single number expressed in seconds.


### roslaunch & launch files

> Instead of launching every node (including master) manually, you can embed them in a launch file.

Since the system is likely to have a lot of nodes that perform interrelated functions as it grows, it is easier to use a launch file to semi-automate the launching of those nodes. For instance, it might be that one node published image from a camera, another performs image processing, and the other two show the original and processed images.

launch files are launched as follows using the `roslaunch` command (NOTE: roslaunch will launch a master, ie `roscore`):

	```
	roslaunch <pkg_name> <file_name>.launch
	```

launch files are usually stored in the `/launch` directory of a ROS package. A sample launch file is shown below:

```
<?xml version="1.0"?>

<?ignore
	Script streams camera to a screen and loads the keyboard motor controls
?>

<launch>
	<include file="$(find myROS_pkg)/launch/camera.launch"/>
	<node pkg="myROS_pkg" name="motor_command" type="motor_command.py"/>
	<node pkg="myROS_pkg" name="key_op" type="key_op.py" output="screen"/>
</launch>
```


##### Breakdown of the launch file

- Header (mandatory)
	```
	<?xml version="1.0"?>
	```
	

- Optional Description
	```
	<?ignore
		content of description
	?>
	```

- Main tags (mandatory)
	```
	<launch>
		[...]
	</launch>
	```

- Nodes
	To ask to start a node, you can use the command:
	```
	<node pkg="package_name" name="node_name" type="node_file_name"/>
	```

- Inclusion of other launch files
	Other launch files can be launched by including them:
	```
	<include file="$(find pkg_name)/launch/file-name.launch"/>
	```


#### rosbag

> ROS bags are achives of msgs and topics.

You can record/replay all topics, or only specific topics, and you can also "filter" bags (change topic names, remove topics, ...). The Ros bags also record the timing of each msg.

Use the command `rosbag` to manage ROS bags.

To record ALL msgs and their timings from ALL the topics (even for nodes not started in the same terminal), use:

	```
	rosbag record --all
	```

If specific topics are needed instead, they can be specified (ie, for topic chatter):

	```
	rosbag record chatter
	```

The rosbag record command will store all the info captured in `.bag` file in the current dir. The only way to stop the recording is to use the `CTRL+C` key combo.

The command `rosbag play filename.bag` will replay the contents of the specified ROS bag file. All the msgs from all the topics recorded are published again with the same relative timing as they were recorded. You can run the same or additional nodes while replaying a ROS bag; these nodes can subscribe or publish on the same topics from the bag.

	```
	rosbag play filename.bag
	--start=TIME  		- Start playing from TIME seconds into the file
	--duration=TIME 	- Play for a duration of TIME seconds
	```

### Summary

The ROS architecture makes it easy to be modular. For prototyping, it is best to keep each node as simple as possible, so that they can be reused. If possible, use nodes that are already available and tested. The only downside is that publishing/suscribing on nodes is slower that doing everything in the same program.

NOTE: Nodelets can be used to increase performance.


