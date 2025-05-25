I am doing a project with 3 parts:
 1. Secure OS for RISC-V World Guard extension.
 2. Linux driver for communication with Secure OS.
 3. OpenSBI modification to support World Guard extension.

Secure OS always works on first cpu core, other cores are left for Linux. Communication between Linux and Secure OS is provided using two shared pages. One page for requests (to secure OS) queue, second page for responses queue. Communication interface:
 1. Linux creates session for selected Trusted Application with `open` request and sends IPI to secure CPU.
 2. Secure OS gets IPI and creates corresponding TA process and immediately yields it
 3. Linux places `invoke` command and arguments to requests queue and sends IPI.
 4. Secure OS gets IPI, send request and arguments to TA
 5. TA does all computations and then calls Secure OS to send back response to response queue
 6. Linux gets response from response queue
 7. Linux closes session with `close` request

I need to write paper abort part with Secure OS.
It should have 4 chapters.
 - 1st chapter is an introduction. It is about background, brief introduction to TEE, problem statement, relevance of the work, possible applications of TEE, and comparison with other architectures, related work. Chapter should also focus on fact that RISC-V is open and free aritecture unlike others and not yet havei opensource interfaces and implementations for TEE.
 - 2nd chapter describes in detail Trusted Execution Enviroment, what is TEE in general, threat model (about attacks and protection), isolation mechanism (also add here section about hardware separation: CPU cores, RAM, ROM, peripherals separated to normal and secure parts), describes World Guard extension in detail, TEE interface, Trusted User Interface (TUI), boot sequence, chain of trust.
 - 3rd is about implementation. Project architecutre: WorldGuard integration, boot process, cross-world communication design and protocol, linux driver. Secure userspace: TA framework and api, standard library, SDK. Secure kernel: microkernel, tasks, scheduling, syscalls, access control for syscalls, communication control for trusted applications. Secure OS uses capability based approach, kernel just exposes a set of objects: tasks, threads,
pes, virtual memory objects, and so on. Objects wrapped with handles. Each task has a manifest, which declares what kernel interfaces and with which permissions this task needs. By design - root task owns all handles and gives them to newly creates tasks. Permissions to create new objects are also done using capabilities for factory-like objects. Capabilities are implemented in a way, methods of handles are handles themselves, so to call a method on an object - you first need to get handle for this method, and then if you have handle of object and handle of method, no more capability checks required to call it.
 - 4th is demonstration and launching trusted application. Software stack: QEMU, Linux, OpenSBI. Showing communication between normal and secure worlds. Security analysis, attempts to attack secure world, conclusion and future work.

Create structure of paper: detailed table of contents with chapters and sub-chapters. You can extend chapter plan when it be appropriate.
