#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <linux/joystick.h>

#define JOY_DEV "/dev/input/js0" //device to read

int main(void)
{
    pid_t pid;	// process ID
    pid_t sid;	// session ID

    // create a fork of the parent process
    pid = fork();

    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    // change the file mode mask to have no permissions
    umask(0);

    // create the system ID for the child process
    sid = setsid();

    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    // change the working directory to one that is always known
    if ((chdir("/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    // close out the standard file descriptors since a daemon is not able
    // to use the termnial
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    int joy_fd;		// joystick file handle
    int *axis = NULL;
    int num_of_axis = 0;
    int axis_value_0;
    int axis_value_1;
    int axis_value_2;

    struct js_event js;

    if ((joy_fd = open( JOY_DEV , O_RDONLY)) == -1)
    {
        exit(EXIT_FAILURE); //return -1;
    }

    // get the number of availble axis
    ioctl(joy_fd, JSIOCGAXES, &num_of_axis);

    // create and fill a variable size array
    axis = (int *) calloc( num_of_axis, sizeof( int ) );

    // use the non blocking mode
    fcntl(joy_fd, F_SETFL, O_NONBLOCK);

    while (1)
    {
        //read the joystick state
        read(joy_fd, &js, sizeof(struct js_event));

        // update the axis value array with the new value
        if ((js.type & ~JS_EVENT_INIT) == JS_EVENT_AXIS)
	{
	   axis[js.number] = js.value;
	}

        axis_value_0 = axis[0];
        axis_value_1 = axis[1];
        axis_value_2 = axis[2];

      	if (axis_value_1 > 10000)
	{
	    // invert the display
	    system("xrandr -o inverted");

	    // disable the touchpad when inverted
	    system("synclient TouchpadOff=0");
	}
        else if (axis_value_0 > 10000)
	{
	    // rotate right
	    system("xrandr -o right");

	    // disable the touchpad
	    system("synclient TouchpadOff=0");
	}
      	else if (axis_value_0 < -10000)
	{
	    // rotate left
	    system("xrandr -o left");

	    // disable the touchpad
	    system("synclient TouchpadOff=0");
	}
        else
	{
	    // rotate the screen back to normal
	    system("xrandr -o normal");

            // enable the touchpad when in normal mode
	    system("synclient TouchpadOff=2");
	}

        // 1 millisecond delay
        usleep(1000);
    }

    close(joy_fd);
    free(axis);

    exit(EXIT_SUCCESS);
}
