# module-6-fonts-Brutus314
module-6-fonts-Brutus314 created by GitHub Classroom

This module will require 2 instances of it running at the same time.
In the aftr.conf file, one instance must have NetServerListenPort=12683.
The other must have NetServerListenPort=12682.
When launching the instances, one may be very slow at first. This is because
it sends a message on every world update, and sending a message is slow when
it fails. The same is true for closing down.

One extra command line argument is required in each instance. This argument is just
a username. It can be really anything, but it must be exactly 1 command line argument.
Each instance should see their respective username in the top-left corner of the screen.

When both instances are running, they should be able to see each other by a cube
tracking the location of the other instance. Moving in one instance moves the cube
in the other. The cube will also rotate with camera looking. Above this cube is
the username the other instance entered in. Make the usernames not matching to see this
easily.

Additionally, pressing '1' will stack a cube near the start in both instances.
