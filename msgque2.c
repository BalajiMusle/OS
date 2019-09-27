// include header files

// declare msg struct, msg size

// define msg queue key, msg type, ...

int main()
{
	int ret;

	// create msgque -- mqid

	ret = fork();
	if(ret == 0)
	{	// child process -- reader
		
		// receive message -- m2

		// print message

		_exit(0);
	}
	else
	{	// parent process -- writer
		
		// initialize msg struct m1

		// send message

		// wait for child completion

		// destroy message queue
	}
	return 0;
}

