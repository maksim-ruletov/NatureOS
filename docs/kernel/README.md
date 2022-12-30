Kernel is a namespace with a one basic function `E_EnterKernel()`. This function recive 1 argument - bool S_Debug. If you set true you can see all changes in OS.

The first thing the kernel does is prepare the entire space. It connects the necessary modules and creates its own workspace at the `mpoint` point, where in the future I will store all the data for the OS.

After preparation is complete, you will see welcome messages in the console and (if debug mode is enabled) notifications about the initialization of the workspace.

## Basics kernel futures.

At the moment, the kernel has a package manager (not networked) virtual memory, a file subsystem and one of the most important BridgeAPI mechanisms, which can be read about in the `docs/other` directory.

After all the above operations, you will see the kernel prompt for a command. More about them will be written later, and there will also be a command by which you will find out everything!
