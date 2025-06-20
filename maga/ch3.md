
# Chapter 3: Design and Implementation of the Secure Operating System
 ## 3.1 Interface Considerations
 The choice of an interface for communication between the Normal World (running Linux) and the Secure World (hosting the Secure OS and Trusted Applications) is a critical design decision. It directly impacts usability, security, and the effort required for integration and development of Trusted Applications. This section explores various approaches considered for the TEE Client API, which facilitates inter-world communication, culminating in the rationale for the selected strategy.

  ### 3.1.1 TEE Client API: Inter-World Communication Interface
  The TEE Client API defines the functions that Normal World clients use to interact with Trusted Applications running within the Secure OS. This interface must provide mechanisms for establishing a connection, sharing data, invoking secure functions, and managing the lifecycle of secure sessions.

   #### 3.1.1.1 OP-TEE on RISC-V
   OP-TEE (Open Portable TEE) is a prominent open-source Trusted Execution Environment designed primarily for Arm TrustZone. Efforts have been made to port OP-TEE to the RISC-V architecture, leveraging existing security mechanisms or extensions like Physical Memory Protection (PMP) or, more recently, experimental support for WorldGuard-like mechanisms. OP-TEE implements a substantial portion of the GlobalPlatform TEE specifications, providing a rich feature set including a TEE Internal Core API for TA development and a comprehensive TEE Client API.

   While OP-TEE offers a mature and widely adopted TEE solution, its architecture presents different considerations. OP-TEE itself is a small, secure operating system typically running alongside a rich OS. For this project, which focuses on a custom-designed monolithic Secure OS with a specific capability-based model and tight integration with the RISC-V World Guard extension, adopting OP-TEE directly would involve either a significant porting and adaptation effort or would dictate architectural choices less aligned with the project's goal of a minimal, deeply understood TCB tailored to World Guard. Furthermore, OP-TEE's internal complexity, while offering extensive features, might be excessive for the project's initial scope focused on fundamental secure services and the unique aspects of the WorldGuard extension.

   #### 3.1.1.2 Develop own minimal GlobalPlatform TEE interface
   An alternative approach considered was the development of a bespoke, minimal TEE interface derived from the GlobalPlatform TEE Client API specifications. This path involves implementing only the essential API functions required for basic Trusted Application interaction: context management, session management, shared memory handling, and command invocation.

   Developing a custom, minimal interface offered several advantages:
   - Reduced Complexity: A smaller API surface simplifies the implementation within the Secure OS, potentially leading to a smaller Trusted Computing Base (TCB) and fewer an attack vectors.
   - Tailored to World Guard: The interface could be specifically designed to leverage the World Guard extension's two-world model and its inter-world communication primitives efficiently. For instance, the shared memory communication paradigm dictated by the project (two shared pages) can be directly mapped to the API design.
   - Alignment with Secure OS Architecture: The interface could be closely integrated with the Secure OS's monolithic design and capability-based security model.
   - Controlled Scope: For a research-oriented Master's project, this approach allows for a focused implementation effort on the core TEE functionalities and their interaction with World Guard.
   - Pedagogical Value: Building the interface provides deeper insight into TEE mechanics and inter-world communication protocols.

   The primary challenge of this approach is ensuring compliance, even with a subset, and providing sufficient functionality for meaningful Trusted Applications.

   #### 3.1.1.3 Experimental of Research Prototypes
   The academic and research community has proposed various TEE designs and inter-world communication mechanisms, particularly for RISC-V, often focusing on novel hardware features or specific security properties. Some prototypes explore custom RPC mechanisms, differing memory sharing models, or entirely new API paradigms distinct from GlobalPlatform.

   While these research prototypes offer valuable insights into potential TEE enhancements and specialized security solutions (e.g., fine-grained compartmentalization, advanced attestation methods), they often lack standardization and broader ecosystem support critical for developing portable Trusted Applications. Adopting an entirely experimental API would deviate from industry-recognized standards, increasing the learning curve for potential developers and limiting compatibility. However, concepts from such prototypes, particularly those related to efficient use of RISC-V-specific features or lightweight communication, could inform the implementation of a standard-based subset.

   #### 3.1.1.4 Rationale for Adopting a Global Platform-based API Subset
   After evaluating the alternatives, the decision was made to adopt a carefully selected subset of the GlobalPlatform (GP) TEE Client API for inter-world communication. This approach aims to balance standardization with the specific requirements and constraints of the project.

   The rationale for this choice is as follows:
   - Standardization and Familiarity: The GlobalPlatform TEE specifications provide a well-defined, industry-recognized standard for TEE client-TA interaction. Adopting a subset leverages this existing knowledge base, making it easier for developers familiar with TEE concepts to understand and use the system.
   - Core Functionality: The GP TEE Client API defines essential concepts like contexts, sessions, shared memory, and command invocation that are fundamental to most TEE interactions. Implementing a subset containing these core elements provides sufficient functionality for a range of Trusted Applications.
   - Reduced Implementation Effort and TCB: By selecting only essential API calls, the implementation complexity within the Secure OS is significantly reduced compared to a full GP implementation. This contributes to a smaller TCB, which is crucial for security, and makes the development feasible within the project's timeframe.
   - Alignment with Project Goals: A minimal subset can be more easily tailored to the specifics of the Secure OS's monolithic, capability-based architecture and its single-core design for the secure world. It also aligns well with the two-shared-page communication mechanism provided by the World Guard integration. The API subset was chosen to map directly to the intended communication primitives, ensuring efficient use of the shared memory queues.
   - Future Extensibility: While starting with a minimal subset, the GP framework offers a clear path for potential future extensions if more features become necessary. The modular nature of the GP specifications allows for incremental additions.
   - Interoperability (Conceptual): Even with a subset, adhering to GP concepts promotes a degree of conceptual interoperability. Trusted Applications written for this API, while not directly portable without recompilation, would follow familiar design patterns.

   The chosen subset focuses on TEEC_InitializeContext, TEEC_FinalizeContext, TEEC_OpenSession, TEEC_CloseSession, TEEC_InvokeCommand, TEEC_AllocateSharedMemory, and TEEC_ReleaseSharedMemory, providing the foundational blocks for secure communication and computation. This selection allows for the development and execution of TAs while minimizing the interface exposed by the Secure OS.

 ## System Architecture Overview
  - section provides a high-level perspective on how the Secure OS is structured and how it interacts with the Normal World and hardware.
Here's the content for the requested sections:

   #### 3.2.1.1 Architectural Layers
   The system architecture is structured in distinct layers, each fulfilling specific roles and operating at different privilege levels. At the foundational layer, the RISC-V hardware platform is initialized by OpenSBI (Open Supervisor Binary Interface), which acts as the firmware. OpenSBI provides essential low-level hardware abstraction, performs initial security configurations, and manages the handover process to the operating systems.

   Above the firmware, the Secure OS operates within the dedicated Secure World, enabled by the RISC-V World Guard extension. This monolithic kernel is designed with a minimal Trusted Computing Base (TCB). Its primary responsibilities include executing Trusted Applications (TAs) in isolation, managing secure resources, and enforcing the system's security policies.

   Concurrently, the Normal World OS, typically a feature-rich operating system such as Linux, runs in a separate domain. It provides the environment for general-purpose applications and user interactions.

   The RISC-V World Guard extension is the core hardware mechanism that underpins this layered structure, enforcing strong isolation boundaries between the Secure World (hosting the Secure OS and TAs) and the Normal World (hosting Linux). This separation is fundamental to preventing unauthorized access or interference between the two environments.

   #### 3.2.1.2 Secure vs. Normal World Overview
   The system utilizes a static partitioning of CPU resources to maintain a strict separation between security domains. The Secure OS is permanently resident on and executes exclusively on the first CPU core (core0). This core is dedicated to secure operations and the execution of Trusted Applications.

   All other CPU cores are allocated to the Normal World, where the Linux operating system runs. The Normal World provides a rich, general-purpose computing environment but is considered untrusted from the perspective of the Secure World.

   The primary roles and responsibilities are distinct:
  - Secure World (Secure OS):
   - Provides an isolated execution environment for Trusted Applications (TAs).
   - Manages secure system resources, such as cryptography hardware or protected memory regions.
   - Enforces the capability-based security model, where TAs operate using handles granted to them via a manifest by a root task, dictating their permissible actions and resource access.
   - Handles sensitive operations and services requested by the Normal World through a well-defined interface.

  - Normal World (Linux):
   - Executes general-purpose applications and manages untrusted system resources.
   - Interacts with the Secure World exclusively through a predefined communication
           interface (based on a subset of the Global Platform API) to request secure services.
   - Cannot directly access memory or resources belonging to the Secure World unless explicitly permitted and mediated by the Secure OS.

   Boundary enforcement is achieved through a combination of hardware and software mechanisms:
  - The RISC-V World Guard extension provides hardware-enforced isolation, preventing the Normal World from directly accessing memory regions or peripherals assigned to the Secure World.
  - Inter-world communication is strictly managed through dedicated shared memory queues for requests and responses, along with Inter-Processor Interrupts (IPIs) for signaling. This controlled channel ensures that all interactions are explicit and auditable.

  ### Core System Components
   #### 3.2.2.1 Kernel, Resource Managers, and TEE Services
   The Secure OS is architected around a microkernel running on the dedicated secure core (CPU0). This kernel provides fundamental services essential for the TEE, including secure context switching between Trusted Applications (TAs) and internal kernel tasks, trap handling specific to the Secure World, and the core enforcement mechanisms for the capability-based security model. It is responsible for managing the low-level hardware resources allocated to the Secure World.

   Built upon the kernel are several key resource managers:
  - Task Manager: Oversees the lifecycle of TAs and internal Secure OS tasks. It handles their creation (typically initiated by the Root Task based on Normal World requests), scheduling, and termination. Each TA, and potentially other managed entities like threads, are represented as kernel objects accessible and controllable via handles, adhering to the capability model.
  - Memory Manager: Governs the allocation, deallocation, and protection of memory within the Secure World. This includes memory for the kernel itself, for individual TAs, and for buffers used in inter-world communication. It leverages underlying hardware mechanisms, such as RISC-V Physical Memory Protection (PMP) in conjunction with the World Guard extension, to enforce strict memory isolation between different TAs, and between the Secure World and the Normal World. Memory resources are often managed as Virtual Memory Objects (VMOs), also accessed via handles.
  - IPC (Inter-Process Communication) Manager: Facilitates secure communication pathways, primarily within the Secure World, such as between different TAs or between TAs and Secure OS services. This is typically achieved using kernel objects like channels or_pipes, where access and operations are controlled by capabilities represented by handles. The IPC manager also supports the Root Task in its role of relaying communication to and from the Normal World.

   TEE (Trusted Execution Environment) Service Layers are implemented above the kernel and resource managers. These layers expose the Secure OS functionalities to TAs through a defined API, which in this project is a subset of the GlobalPlatform TEE API. Services include managing TA sessions, handling command invocations from the Normal World, and managing shared memory operations from the perspective of a TA. All TEE service requests are mediated by these layers, which interact with the underlying kernel and resource managers while strictly adhering to the enforced capability model. Collectively, the kernel, resource managers, and TEE services establish a trusted foundation, providing security, controlled resource allocation, and a managed runtime environment for Trusted Applications.

   #### 3.2.2.2 Shared Memory and IPI-Based Communication
   Inter-world communication between the Normal World (Linux) and the Secure OS relies critically on two primary mechanisms: shared memory and Inter-Processor Interrupts (IPIs).

   Two pre-allocated physical memory pages form the data exchange fabric. One page is designated as the Request Queue, enabling the Normal World to enqueue requests for the Secure OS. The second page serves as the Response Queue, through which the Secure OS delivers results and notifications back to the Normal World. These queues are typically implemented as lock-free or minimally-locking ring buffers to ensure efficient data transfer and reduce contention. The World Guard extension ensures that these shared memory regions are accessible only in the manner defined by the system security policy; for instance, the Normal World can write to the request queue which the Secure OS reads, and the Secure OS writes to the response queue which the Normal World reads.

   RISC-V standard Inter-Processor Interrupts (IPIs) are employed as the signaling mechanism to notify the other world of pending messages in the shared queues, thereby avoiding inefficient polling.
  - Normal World to Secure World Signaling: When Linux (running on a non-secure core) places a new request into the shared request queue, it subsequently issues an IPI to the dedicated secure core (CPU0), alerting the Secure OS that a new request is available for processing.
  - Secure World to Normal World Signaling: Conversely, after the Secure OS has processed a request and placed a response (or an asynchronous event notification) into the shared response queue, it sends an IPI to a designated Normal World core. This informs Linux that a response is ready to be retrieved.

   This combination of explicitly defined shared memory regions for data payload and IPIs for event notification forms a robust and efficient asynchronous communication channel, fundamental to the cooperative operation of the Secure and Normal Worlds.

  ### Memory Layout and Addressing
   #### 3.2.3.1 Physical and Virtual Addressing
   The Secure OS establishes and manages its own distinct set of page tables, governing the translation of virtual addresses to physical addresses within the Secure World. During its initialization, the Secure OS configures the Supervisor Address Translation and Protection (SATP) register for the dedicated secure core (CPU0) to point to its root page table. This enables virtual addressing for the Secure OS kernel, Trusted Applications (TAs), and any secure peripherals assigned to the Secure World. Each TA typically operates within its own isolated virtual address space, managed by the Secure OS, ensuring that TAs cannot directly access each other's memory or kernel memory unless explicitly permitted through shared memory object capabilities.

   Physical memory is partitioned by the Secure OS, leveraging the World Guard extension. Certain physical memory regions are designated as exclusive to the Secure World, while others are allocated to the Normal World, and specific, limited regions are designated as shared. Consequently, memory mappings within the Secure World (established by the Secure OS) provide access to secure physical memory regions that are invisible or inaccessible (or access-restricted) to the Normal World's memory management unit (MMU) configuration, which operates independently on the other CPU cores under Linux's control. The Secure OS's view of physical memory includes awareness of these distinct regions to enforce overarching system memory policies.

   #### 3.2.3.2 Isolation Mechanisms
   The primary hardware mechanism for enforcing memory isolation between the Secure World and the Normal World is the RISC-V World Guard extension. World Guard associates a "world ID" with memory transactions originating from CPU harts and with peripheral accesses. The Secure OS, during its boot process and ongoing operation on the dedicated secure core, configPSIures World Guard checkers. These checkers are programmed with rules that define which physical memory regions and peripherals are accessible by which world ID.

   For instance, memory pages allocated for the Secure OS kernel, Trusted Applications, and private Secure World data are configured to be accessible only when transactions originate from a hart operating in the Secure World (i.e., with the Secure World ID). If the Normal World OS (Linux), operating on other cores with a Normal World ID, attempts to access a physical memory page exclusively assigned to the Secure World, the World Guard hardware checkers detect this policy violation. Such unauthorized access attempts result in a hardware exception or fault, which is handled as per the World Guard error reporting configuration, effectively preventing the Normal World from directly reading, writing, or executing code within protected Secure World pages. This hardware-enforced boundary is fundamental to the TEE's security guarantees.

   #### 3.2.3.3 Shared Memory Queues
   Communication between the Secure World and the Normal World is facilitated by reserved physical memory regions configured as shared buffers. Specifically, two dedicated L1-cache aligned physical memory pages are employed: one for requests from the Normal World to the Secure OS (request queue) and another for responses from the Secure OS back to the Normal World (response queue). The Secure OS, in conjunction with World Guard checker configurations, grants both worlds appropriate access permissions to these specific shared pages—typically, the Normal World has write access to the request queue and read access to the response queue, while the Secure OS has read access to the
   request queue and write access to the response queue.

   These queues are implemented as lock-free ring buffers (also known as circular buffers) to manage concurrent access without traditional locking overhead, which is critical for efficient inter-world communication. The use of lock-free algorithms minimizes contention and latency, particularly as the Normal World might enqueue requests from multiple contexts (though processed sequentially by the single-core Secure OS). Careful management of head and tail pointers, often utilizing atomic operations, ensures data integrity and synchronization between the two worlds when enqueuing and dequeuing messages. The fixed size and predefined location of these queues simplify the memory management and trust model for inter-world data exchange. Context propagation, canary protection and other security considerations for these shared queues are elaborated in section 3.6.

  ### Secure OS Execution Flow
   #### 3.2.4.1 Boot Process Overview
   The boot process commences with OpenSBI, which performs initial platform setup. OpenSBI identifies and loads the Secure OS payload, passing control to it on the designated first CPU core (core 0). The Secure OS then initializes its core components, including memory management for its exclusive use and setting up the World Guard extension to isolate core 0 as the Secure World. This involves configuring World Guard checkers to protect Secure World memory. After its initialization, the Secure OS signals back to OpenSBI. OpenSBI subsequently proceeds to boot the Normal World OS (Linux) on the remaining CPU cores. These cores are configured by OpenSBI to operate in the Normal World, ensuring they cannot interfere with or access the resources dedicated to the Secure OS on core 0 unless explicitly permitted through the defined communication channels.

   #### 3.2.4.2 Inter-World Transitions
   Execution transitions between the Secure and Normal Worlds are strictly controlled. When the Normal World (Linux) needs to invoke a service from the Secure OS, it prepares a request in the designated shared memory request queue and then typically issues an Inter-Processor Interrupt (IPI) to core 0. This IPI serves as a signal for the Secure OS to check the request queue. The World Guard hardware mechanism facilitates the switch of core 0 from a (potentially) Normal World context (if it was idled awaiting IPIs) to the Secure World context to process the IPI and subsequently the request.
   The Secure OS processes the request and places a response in the shared memory response queue. The Normal World typically polls this response queue to retrieve the result.
   Before processing any request from the Normal World, the Secure OS performs validation checks based on the message content and source, adhering to the defined API and security policies. Secure state persistence during transitions is ensured by the World Guard extension, which manages the hardware context (e.g., registers, world ID) for the current world executing on the core. The Secure OS is responsible for saving and restoring specific Trusted Application contexts within the Secure World if multiple TAs or internal tasks are being managed.

   #### 3.2.4.3 Scheduling in Secure OS
   The Secure OS operates on a single, dedicated CPU core (core 0) and employs a uniprocessor scheduling strategy for managing its internal tasks and any Trusted Applications (TAs) it hosts. A pre-emptive, round-robin scheduling policy is implemented to ensure fair access to the CPU for all runnable entities within the Secure World.
   Context switching within the Secure OS involves saving the execution context (registers, stack pointer, program counter) of the current TA or task and restoring the context of the next scheduled entity. Given that the Secure OS and its TAs execute exclusively on core 0, their scheduling activities are entirely independent of and do not interfere with the Linux kernel's scheduler, which manages tasks on the other CPU cores operating in the Normal World. The design aims for Secure OS operations to be relatively short-lived to ensure timely responses to TAs and Normal World requests.

  ### Security and Policy Enforcement
  The Secure OS employs a multi-layered approach to security and policy enforcement, combining hardware-level isolation mechanisms provided by the RISC-V World Guard extension with a software-defined, fine-grained access control model. This ensures that both the Secure World itself and the Trusted Applications (TAs) running within it are protected from the non-secure Normal World and, crucially, from each other, adhering to the principle of least privilege.

   #### 3.2.5.1 Capability-Based Security Model
   The Secure OS implements a capability-based security model, where access to all system resources and kernel services is mediated through *handles*. A handle acts as an unforgeable token representing a specific *capability*—a grant of authority to perform a defined set of operations on an associated kernel object (e.g., memory regions, communication channels, task control blocks). This model contrasts with traditional identity-based access control by focusing on specific permissions tied to object instances rather than broad user privileges.

   Trusted Applications are initially endowed with a set of handles through a predefined *Manifest*, provisioned by the system's root task upon TA instantiation. New objects, and consequently new handles with specific capabilities, are generally created by invoking methods on *fabric objects* (factory objects), for which the TA must also possess an appropriate handle. Operations on these objects are requested via *secure syscalls*, which are the primary interface between TAs and the kernel. By presenting a handle during a syscall, a TA implicitly asserts its right to perform the requested action. This mechanism enables *fine-grained access control*, as each handle explicitly defines the permissible interactions with its corresponding object.

   Runtime enforcement is central to this model. Upon receiving a secure syscall, the kernel performs rigorous validation. It first verifies the authenticity and validity of the
    Cmodel handlespresented handle, ensuring it corresponds to an active kernel object and is appropriate for use by the calling TA's context. Subsequently, the kernel checks if the capability encapsulated by the handle explicitly permits the requested operation on the target object. If the capability is insufficient or the handle is invalid, the operation is denied, and an error is returned to the TA. This per-operation check is critical for preventing TAs from forging capabilities or escalating privileges beyond what was explicitly granted. Since TAs cannot directly manipulate handle contents or manufacture new capabilities arbitrarily, they are confined to the authorities given to them through their initial Manifest or legitimately acquired from fabric objects, robustly enforcing the principle of least privilege.

   #### 3.2.5.2 World Guard Integration
   The RISC-V World Guard extension underpins the Secure OS's security posture by providing fundamental hardware-enforced memory and peripheral isolation between the Secure World (SW) and the Normal World (NW). Its primary role is to create a distinct execution environment for the Secure OS and TAs, operating on a dedicated CPU core, shielded from the Linux environment running on other cores. World Guard achieves this by associating a World ID with each CPU core's memory transactions and comparing this ID against configured access permissions for different physical memory regions and peripheral devices. Attempts by the Normal World to directly access resources exclusively assigned to the Secure World are thus blocked at the hardware level.

   The Secure OS's software-defined capability-based security model complements this coarse-grained hardware isolation by providing fine-grained access control *within* the Secure World. While World Guard prevents the NW from illicitly accessing or disrupting the SW, the capability model meticulously governs how TAs and Secure OS components interact with each other's kernel-managed objects and resources. For instance, World Guard protects the entirety of a TA's private memory from direct access by Linux; simultaneously, the capability system prevents one TA from accessing another TA's private data or invoking its services unless explicit permission is granted via a shared object handle. This layered approach creates a defense-in-depth strategy: World Guard establishes the robust inter-world perimeter, while the capability system enforces strict compartmentalization and adherence to policies inside that perimeter. Policies for inter-world communication via shared memory queues and world transitions are also co-enforced; World Guard validates the legality of these transitions and shared memory accesses at a hardware level, while the Secure OS software policies manage the content, synchronization, and lifecycle of the shared data structures.

   When the World Guard hardware checker detects an unauthorized memory access attempt (e.g., NW code attempting to read SW private memory) or an invalid world transition (e.g., an improper instruction attempting to illicitly change the current world state of a core), it generates a precise hardware trap or fault. The system's response to such a fault is determined by handlers configured by the Secure OS (or OpenSBI, during early boot on behalf of the Secure World).
   Violations originating from the Normal World typically result in the offending Normal World core being trapped; the specific handling (e.g., signaling an error to the Linux kernel) allows the Normal World to manage the fault within its own context without compromising the Secure World. If a software component within the Secure World itself were to trigger a World Guard violation (a scenario made less likely by the internal memory management and capability checks), it would also result in a trap handled by the Secure OS, potentially leading to the termination of the errant TA or a controlled system halt if the violation is critical to system integrity. World Guard thus acts as a non-bypassable enforcement mechanism for the high-level security policy of world separation, with defined failure handling pathways for transgressions against these hardware-enforced rules. Error reporting mechanisms ensure that such violations can be logged and, where appropriate, communicated to system administrators or the Normal World if a request cannot be safely processed.

  ### TA Lifecycle
   #### Creation
   The lifecycle of a Trusted Application (TA) within the Secure OS commences upon an TEEC_OpenSession request from the Normal World. This request is processed by the Root Task, which is responsible for managing TA instantiation. If a TA is not already running and is registered (e.g., its metadata is known to the Secure OS, possibly through pre-loaded manifest information), the Root Task initiates its creation.

   The creation process involves several steps coordinated by the Root Task and core Secure OS services:
   1.  TA Image Loading: The Secure OS loads the TA's binary image (e.g., an ELF file listed in a predefined manifest or located in a simple RAM-based filesystem) into a newly allocated, isolated memory space. This involves parsing the executable format and mapping its code, data, and BSS segments into the TA's virtual address space.
   2.  Memory Allocation: Dedicated memory regions are allocated for the TA's stack, heap, and its private data. This memory is protected and isolated from other TAs and the Secure OS kernel itself using mechanisms like World Guard and the MMU.
   3.  Handle Initialization: Based on the TA's manifest, the Root Task provisions the TA with an initial set of handles. These handles represent capabilities, granting the TA specific access rights to system resources (e.g., a handle to a fabric object for creating further objects, handles for communication channels, or pre-configured service interfaces). The TA's handle page is initialized with these capabilities.
   4.  Process/Thread Spawning: A new process or task construct is created within the Secure OS to host the TA. An initial thread is spawned within this task, with its entry point set to the TA's designated startup routine (e.g., TA_CreateEntryPoint).
   5.  Initial State: Upon successful creation and initialization, the TA process is typically brought to a state where it has executed its TA_CreateEntryPoint, performed any necessary self-initialization, and is ready to receive commands but is initially inactive.

   The TEEC_OpenSession call returns a session identifier to the Normal World client if the TA creation and session establishment are successful. This session ID is used for subsequent interactions with this specific TA instance.

   #### Compute
   Once a TA session is successfully established (via TEEC_OpenSession) and the TA's TA_CreateEntryPoint has completed, the TA typically enters an idle state or yields control back to the Secure OS scheduler. It remains dormant, awaiting specific commands from the Normal World.

   Further interaction is driven by TEEC_InvokeCommand calls from the Normal World client. When such a call arrives:
   1.  Wake-up and Dispatch: The Root Task, or a designated communication manager within the Secure OS, receives the InvokeCommand request. It identifies the target TA session and the specific command ID (method ID) to be executed. The TA thread is then woken up (scheduled for execution).
   2.  Argument Passing: Parameters associated with the InvokeCommand, including the command ID and any input/output buffers (often mapped via shared memory), are made available to the TA. The Secure OS ensures that the TA receives these arguments in a secure and defined manner, typically through its execution context or pre-arranged memory locations.
   3.  TA Execution: The TA executes its TA_InvokeCommandEntryPoint function. Based on the received command ID, the TA performs the requested computation. This may involve:
      - Accessing its private data and resources.
      - Utilizing its granted capabilities (handles) to interact with Secure OS services (e.g., cryptographic operations if available, secure storage access).
      - Communicating with other TAs or the Root Task via secure inter-process W-Pcommunication (IPC) channels, using handles obtained during creation or through service discovery.
      - Requesting allocation of new shared memory regions, if the command requires passing larger data back and forth with the Normal World. The TEEC_AllocateSharedMemory API call, when invoked by the Normal World client, may relate to memory needs identified during a TEEC_InvokeCommand. Data is then exchanged by the Normal World client and the TA writing to and reading from this shared memory.

   Upon completion of the command, the TA prepares any results (in output buffers or by modifying shared memory) and returns a status code. The Secure OS then relays this status and any relevant data back to the Normal World client as a response to the TEEC_InvokeCommand. The TA might then yield again, awaiting further commands.

   #### Teardown
   The termination of a Trusted Application instance and the "reclaim" of its resources are initiated when the Normal World client application explicitly closes the session using the TEEC_CloseSession call. This request signals that the TA's services for that particular session are no longer required.

   The teardown process involves the following key steps managed by the Secure OS, often facilitated by or communicated to the Root Task:
   1.  Session Closure Notification: The TA is notified that its session is being closed, typically by invoking its TA_CloseSessionEntryPoint function. This allows the TA to perform any session-specific cleanup, such as releasing resources allocated specifically for that session.
   2.  TA Destruction: If no other active sessions are associated with the TA instance (or if the TA is designed as single-session), the Secure OS proceeds to terminate the TA entirely by invoking its TA_DestroyEntryPoint. This function is the TA's final opportunity to perform global cleanup.
   3.  Resource Deallocation:
      - Object Release: All handles owned by the TA are systematically invalidated and released. The underlying kernel objects associated with these handles (e.g., memory objects, communication channels) are unreferenced. If the TA was the last holder of a reference, the object itself is deallocated by the respective resource manager in the Secure OS.
      - Shared Memory Release: Any shared memory regions explicitly allocated for communication between this TA instance and the Normal World (e.g., via TEEC_AllocateSharedMemory) are unmapped from both the Secure World TA's address space and flagged for reclamation. The Linux driver on the Normal World side is typically responsible for also unmapping these regions.
      - Private Memory Reclamation: The private memory regions allocated for the TA's code, data, stack, and heap are reclaimed by the Secure OS memory manager. The TA's task/process construct and associated threads are destroyed.

   Upon successful completion of these steps, the TA instance ceases to exist, and its resources become available for reallocation. A result code indicating the success or failure of the TEEC_CloseSession operation is returned_ to the Normal World client. The Secure OS ensures that the teardown process is orderly and does not compromise the integrity of the Secure World or other active TAs.

 ## WorldGuard Integration
Here is the content for Chapter 3, Section 3.3.1 "WorldGuard Configuration":
  ### 3.3.1 WorldGuard Configuration
  The RISC-V WorldGuard extension is pivotal for establishing hardware-enforced isolation between the Secure World, hosting the Secure OS, and the Normal World, where Linux operates. Proper configuration of WorldGuard is essential to define these isolated domains and control their interactions. This configuration primarily involves defining the worlds themselves and programming the WorldGuard checkers to enforce memory access policies.

   #### 3.3.1.1 World Configuration (Two-World Model)

   The foundation of the system's security architecture is the division of hardware and software resources into two distinct "worlds": a Secure World (SW) and a Normal World (NW). This partitioning is realized through the WorldGuard extension.

  - System Resource Partitioning:
       The WorldGuard extension enables a fundamental split of system resources. Physical memory is partitioned into regions exclusively accessible by the Secure World, regions exclusively accessible by the Normal World, and specific, limited regions designated as shared memory for inter-world communication. In this project, CPU core 0 is statically assigned to the Secure World to execute the Secure OS and its Trusted Applications (TAs). All other CPU cores are allocated to the Normal World for Linux execution.

  - Two-World Design Rationale:
       This two-world model provides strong, hardware-enforced isolation between the trusted environment (Secure World) and the general-purpose, potentially compromised environment (Normal World). This architectural choice is influenced by established TEE designs, offering a clear separation of concerns. It simplifies the Trusted Computing Base (TCB) by dedicating a world to security-critical operations, distinct from the complexities of a feature-rich OS environment.

  - Roles of Each World:
      - Secure World (SW): Operates with World ID 0 (WID 0). It hosts the Secure OS, which is responsible for executing Trusted Applications, managing cryptographic keys and other secrets, performing security-sensitive computations, and enforcing the capability-based security model. All operations within the Secure World are considered privileged from a security standpoint.
      - Normal World (NW): Operates with World ID 1 (WID 1). It hosts the Rich OS (Linux) and its applications. The Normal World is treated as untrusted by the Secure World. It interacts with the Secure World only through a strictly defined interface, typically to request services from TAs.

  - World ID Assignment and Management:
       WorldGuard associates a World ID (WID) with transactions originating from CPU cores. In this system, WID 0 is assigned to the Secure World and WID 1 to the Normal World.
       The assignment of WIDs to CPU cores is performed by OpenSBI during the early boot stages, leveraging its M-mode privileges. OpenSBI configures CPU core 0 to operate with WID 0 (Secure World) before transferring control to the Secure OS. Other CPU cores are configured with WID 1 (Normal World) before Linux is booted on them.
       The Secure OS, once initialized and running within the Secure World on core 0, operates under WID 0. It ensures that its memory accesses and, by extension, those of the TAs it manages, are correctly associated with this WID. The mlwid CSR (Machine Lower-privilege World ID) can be used by M-mode (OpenSBI) to set the WID for S-mode (where the Secure OS runs). This static assignment of WIDs forms the basis of the hardware isolation.

   #### 3.3.1.2 WorldGuard Checker Configuration for Secure Isolation

   WorldGuard checkers are hardware units integrated into the system's memory fabric. They monitor memory transactions, compare the WID of the initiator against pre-programmed rules associated with memory regions, and enforce access permissions. The Secure OS is responsible for configuring these checkers during its initialization phase to establish and maintain secure isolation.

  - Configuration of Secure RAM with WG Slots:
      - Secure Memory Partitioning Approach: The physical address space is partitioned by programming the WorldGuard checker slots. Each slot defines a rule for a specific memory range, associating it with permissions for different WIDs. The Secure OS allocates distinct regions for its own kernel code and data, private memory for each TA, and the shared memory pages used for inter-world communication. These allocations are translated into rules for the WG checker slots. This partitioning is typically static and established at boot time. Default policy dictates that any memory region not explicitly configured by a WG slot might be inaccessible or subject to a default platform-specific rule (often denying all access).
      - Locking Down Memory Regions to the Secure World: Memory regions designated for the exclusive use of the Secure World (e.g., Secure OS image, TA private heaps and stacks) are configured in WG checker slots. These slots specify that only transactions originated by WID 0 (Secure World) are permitted Read and/or Write access. Any attempt by WID 1 (Normal World) to access these regions is intercepted by the WG checker, resulting in a memory access fault. To ensure the immutability of these critical security configurations, the L (lock) bit in each WG checker slot's configuration register (cfg) is set by the Secure OS after initialization. Once locked, a slot's configuration cannot be altered until the next system reset.

  - Setting up Partition Boundaries:
       The primary partition enforced by WorldGuard is between the Secure World and the Normal World. This boundary is defined by the collective rules programmed into the WG checker slots.
      - Normal World Memory: Regions intended for Normal World use (e.g., main RAM for Linux) are configured to allow R/W access by WID 1 and deny access by WID 0. This prevents the Secure World from unintentionally or maliciously accessing Normal World private data, adhering to the principle of least privilege.
      - Shared Memory Regions: For inter-world communication, specific pages (e.g., for request and response queues) are configured in WG slots to be accessible by both WID 0 and WID 1. However, permissions can be asymmetric: for the request queue, WID 1 (NW) might have Write access while WID 0 (SW) has Read access, and vice-versa for the response queue.
      - Policy for Controlling Access: The policy is straightforward:
          - Access from NW to SW private memory is strictly denied (Read, Write, Execute).
          - Access from SW to NW private memory is generally denied to maintain isolation and prevent SW from becoming a vector for NW attacks.
          - Access to shared memory is explicitly allowed with carefully defined permissions.

  - Integration of Memory Attributes (Read/Write/Execute) with WorldGuard Checks:
      - WorldGuard checkers primarily enforce permissions based on Read and Write access types for specified WIDs over memory ranges. The perm field within each checker slot directly encodes these R/W permissions for each world. Violation of these permissions triggers an immediate fault by the checker.
      - Instruction fetches by a CPU are treated as memory read operations by the bus fabric and thus by the WorldGuard checkers. If a WID is denied read access to a memory region by a WG checker, it will also be implicitly denied instruction fetch (execute) access from that region at the WorldGuard level.
      - Finer-grained execute permissions (e.g., No-Execute bits for data pages) *within* a world are managed by the Memory Management Unit (MMU) of that world. For instance, the Secure OS uses its MMU (configured via PTEs) to mark its data pages as non-executable for TAs, even if WorldGuard permits WID 0 to read those pages. Thus, WorldGuard provides coarse-grained inter-world isolation (e.g., "this memory block is SW-only"), while the MMU provides finer-grained intra-world protection and virtual memory management.

  ### Integration with the Secure OS
   #### 3.3.2.1 Error Reporting
   Integration with the Secure Operating System concerning error reporting for WorldGuard violations involves immediate detection, structured logging, and defined responses. Hardware-level WorldGuard controllers detect unauthorized access attempts or configuration errors, populating their errcause and erraddr registers with details such as the offending World ID (WID), access type (read/write), and the target physical address.

   Upon detection of a violation pertinent to the Secure World's domain or its configured resources:
   1.  Violation Detection and Notification: If a WorldGuard controller is configured with its IR (Interrupt on Read)/IW (Interrupt on Write) or ER (Error on Read)/EW (Error on Write) bits set for a specific rule, a violation triggers a corresponding response. An interrupt, if configured via IR/IW, can be routed to the Secure OS running on core 0. The Secure OS interrupt service routine (ISR) then queries the memory-mapped WorldGuard controller's errcause and erraddr registers to retrieve fault information. Alternatively, critical faults might manifest as precise bus errors or access faults directly trapped by the Secure OS.
   2.  Logging Structure: The Secure OS maintains a secure log, inaccessible to the Normal World. WorldGuard-related violations are recorded with:
      - Timestamp of the event.
      - Contents of errcause: offending WID, type of access (read/write), whether a bus error (be) or interrupt (ip) was signaled by the controller.
      - Contents of erraddr: physical address of the attempted access.
      - Identifier of the Secure OS component or Trusted Application (TA) context, if the fault originated from within the Secure World and can be reliably determined.
       This log serves debugging, auditing, and potential forensic analysis. After logging, the errcause.ip and errcause.be bits are cleared by the Secure OS to allow the controller to report new faults.
   3.  Response Strategies:
      - Violations by Normal World (NWd): If the offending WID indicates the Normal World attempting unauthorized access to Secure World (SWd) memory, the Secure OS logs the incident. The primary enforcement is by the WorldGuard hardware blocking the access. Further action by SWd is typically limited to logging, as the NWd is responsible for handling faults on its own cores.
      - Violations by TA: If a TA within the Secure World triggers a WorldGuard violation (e.g., by attempting to access memory outside its permitted regions not caught by the MMU but by a broader WG rule), the Secure OS will typically:
          - Log the critical error.
          - Terminate the offending TA immediately to prevent further compromise or instability.
          - Release resources held by the TA.
          - Report an error to the Normal World client that had an active session with the TA.
      - Violations by Secure OS Kernel: If a WorldGuard violation is attributed to the Secure OS kernel itself, this indicates a severe internal inconsistency or bug. The Secure OS will:
          - Attempt to log diagnostic information, if possible.
          - Enter a controlled panic state, halting further operations in the Secure World to prevent potential propagation of an insecure state. This might involve disabling interrupts on core 0 and ceasing further TA execution.

   #### 3.3.2.2 Managing World Transitions

   In the implemented two-world model with WorldGuard, where the Secure OS is statically bound to core 0 (Secure World, WID 0) and Linux to other cores (Normal World, WID 1), "world transitions" primarily refer to the controlled interaction and signaling flows between these statically separated execution environments, rather than dynamic WID changes on a single core for routine calls.

   1.  Control Flow (NWd to SWd):
      - A Normal World entity (e.g., Linux driver) wishing to invoke a Secure World service prepares a request message and places it into the shared request queue.
      - The Normal World then triggers an Inter-Processor Interrupt (IPI) targeting core 0. This is typically done via an SBI call (sbi_send_ipi).
      - The Secure OS, running on core 0, receives this IPI. Its IPI handler, or a task woken by it, then inspects the request queue, dequeues the message, and dispatches it to the appropriate TA or internal service.
   2.  Control Flow (SWd to NWd):
      - After processing a request, the Secure OS or TA places a response message into the shared response queue.
      - In the current design, the Secure OS does not send an IPI back to the Normal World. Instead, the Linux driver in the Normal World employs a polling mechanism (e.g., a dedicated kernel thread) that periodically checks the response queue for completed messages.
   3.  Interrupt Handling:
      - The primary interrupt-driven transition is the IPI from NWd to SWd, signaling a new request. The Secure OS's IPI handler must be lightweight, typically deferring actual request processing to a task context to keep ISR execution time minimal.
      - WorldGuard fault exceptions, if configured to generate interrupts to core 0, are also a form of interrupt-driven event that the Secure OS handles to manage security violations.
   4.  CPU Instructions/Registers: Traditional world-switching instructions (like Arm's SMC) are not directly applicable here for inter-world calls since WIDs are statically assigned per core by OpenSBI during boot using M-mode CSRs (e.g., mlwid). The hardware (core and WorldGuard checkers) inherently associates memory accesses from core 0 with WID 0 and accesses from other cores with WID 1. The interaction relies on standard IPI mechanisms and shared memory access, policed by WorldGuard.
   5.  Overhead and Security:
      - Minimal overhead is pursued by using lock-free algorithms for shared queues, reducing contention and eliminating lock/unlock latencies.
      - The IPI mechanism for NWd → SWd signaling is direct. The polling mechanism for SWd → NWd responses is chosen to avoid potential complexities or security concerns with SWd-originated IPIs being indistinguishable from other IPI sources by a generic Linux kernel.
      - Security guarantees are primarily enforced by WorldGuard at the hardware level, ensuring that:
          - Direct memory access across world boundaries is prevented, except for explicitly configured shared regions.
          - The integrity of the Secure OS on core 0 is maintained against interference from other cores.

   #### 3.3.2.3 Communication Pages

   The secure integration of communication pages (shared memory regions used for request and response queues) is critical and relies heavily on correct WorldGuard configuration by the Secure OS.

   1.  Shared Memory Region Definition: Two primary shared memory regions are pre-defined, typically each consisting of one or more physical pages (e.g., 4KiB aligned):
      - Request Queue Page: Used by the Normal World to send requests to the Secure World.
      - Response Queue Page: Used by the Secure World to send responses back to the Normal World.
       The physical addresses of these pages are communicated to the Secure OS during boot (e.g., via device tree) and are also known to the Linux driver.
   2.  WorldGuard Configuration for Shared Pages: During its initialization, the Secure OS programs the WorldGuard controller(s) to enforce specific access permissions for these communication pages:
      - Request Queue Page Permissions:
          - The slot(s) in the WorldGuard controller corresponding to the request queue's physical address range are configured.
          - The perm field for this slot will grant:
              - Normal World (WID 1): Write access (and potentially Read access if the queue implementation on the NWd side requires it for its own metadata management, though primarily Write).
              - Secure World (WID 0): Read access.
          - Execute permissions are denied for both worlds.
      - Response Queue Page Permissions:
          - The slot(s) corresponding to the response queue's physical address range are configured.
          - The perm field for this slot will grant:
              - Secure World (WID 0): Write access (and potentially Read access for its queue management).
              - Normal World (WID 1): Read access.
          - Execute permissions are denied for both worlds.
   3.  Layout and Alignment:
      - The shared regions are physically contiguous and aligned to page boundaries (e.g., 4KiB) to match memory management granularity and simplify WorldGuard rule configuration (e.g., using NA4 or NAPOT encoding if a single slot covers the region).
      - To prevent accidental overflows from corrupting adjacent memory, canary pages (non-accessible guard pages) can be configured around these shared communication pages by the Secure OS using additional WorldGuard rules, if deemed necessary and supported by the number of available slots.
   4.  Enforcement and Locking:
      - WorldGuard hardware continuously monitors all memory accesses. Any attempt by either world to access a communication page in a manner violating the configured perm bits (e.g., SWd trying to write to the request queue, or NWd trying to write to the response queue) results in a WorldGuard fault, as described in the Error Reporting section.
      - After the Secure OS configures the WorldGuard slots for these communication pages (and all other critical memory regions), it sets the L (lock) bit in the cfg register of each relevant slot. This makes the rule immutable until the next system hardware reset, preventing any runtime modification, whether malicious or accidental, by any software component (including the Secure OS M-mode if it were to be compromised post-boot and OpenSBI restricted M-mode access to WG configuration CSRs or memory-mapped regions).

 ## Secure Boot Process and Initialization
 - This section describes how the Secure OS is bootstrapped, transitioning from platform firmware (OpenSBI) to a fully initialized secure environment.
 - It covers early assembly-level initialization, kernel relocation, MMU enablement, and higher-level subsystem initialization, ultimately concluding with the handover to any “rich OS” components.

  ### 3.4.1 Secure OS Early Initialization
   #### 3.4.1.1 OpenSBI Handover
   OpenSBI, serving as the Supervisor Execution Environment (SEE), initiates the boot process. It loads the Secure OS firmware payload, designated by FW_PAYLOAD_PATH, into physical memory on the primary CPU core (hart 0), which is designated for secure operations. Execution control is then transferred to the Secure OS entry point, _start. At this juncture, OpenSBI provides critical system parameters to the Secure OS via general-purpose registers: a0 holds the hart ID of the booting core, and a1 contains the physical address of the Flattened Device Tree (FDT). The _start routine in head.S captures these parameters, saving them for subsequent C-level initialization routines, such as early_boot, which utilizes the FDT for platform configuration.

   #### 3.4.1.2 Setting Up the Stack and Basic Memory Layout
   Prior to enabling the MMU and establishing a full C runtime, an initial stack is essential for assembly routines and early C function calls. This stack is statically allocated within the Secure OS's memory image, its size defined by STACK_SIZE (specified as PAGE_SIZE * 6 in head.S). The _start routine calculates the virtual address for the top of this stack. It determines the physical top of the stack area (derived from the stacks symbol and STACK_SIZE) and adds KERNEL_VIRTUAL_OFFSET (the difference between KERNEL_VIRTUAL_BASE and the kernel's physical load address) to establish the stack pointer (sp) at its final virtual address. The stack's base address is page-aligned, ensuring adherence to RISC-V ABI alignment requirements for the stack pointer. At this stage, the kernel operates with an understanding of its own physical memory layout as loaded by OpenSBI.

   #### 3.4.1.3 First Kernel Relocation
   The Secure OS is compiled as a Position-Independent Executable (PIE), allowing it to be loaded at arbitrary physical addresses while its internal components are linked to operate from a consistent high virtual address space, KERNEL_VIRTUAL_BASE. To facilitate this, the early MMU setup performs a "first relocation" by establishing two concurrent mappings for the kernel's code and data segments in the initial page tables:
   1.  An identity mapping (Physical Address = Virtual Address) is created for the region where the kernel is loaded. This ensures that instruction fetching continues uninterrupted from the kernel's physical load address immediately after the MMU is enabled.
   2.  A high virtual address mapping is also created, mapping the same physical kernel segments to KERNEL_VIRTUAL_BASE. This allows all linked absolute virtual addresses (for functions and global data) within the kernel to resolve correctly once execution transitions to this virtual space.
   The head.S assembly code implements these dual mappings using large pages (e.g., 2MB pages for Sv39 architecture) to simplify the early page table structures and enhance efficiency for covering the kernel image.

   #### 3.4.1.4 Enabling the MMU
   Once the initial page tables are populated with the identity and KERNEL_VIRTUAL_BASE mappings for the kernel, the Memory Management Unit (MMU) is activated. This is achieved by configuring the Supervisor Address Translation and Protection (SATP) register. The enable_mmu routine in head.S writes to SATP:
   1.  The Physical Page Number (PPN) of the root page table (obtained from the physical address of the ptable_cache structure).
   2.  The address translation mode (Sv39 for 64-bit RISC-V systems, indicated by MODE=8 in the SATP value).
   Upon writing to SATP, address translation becomes active for all supervisor-mode memory accesses on the core. The pre-established dual mappings ensure operational continuity for the currently executing code. The kernel then performs a jump from its current physical program counter to the corresponding offset within the KERNEL_VIRTUAL_BASE address range (specifically, to the virtual address of the early_boot C function). This action transfers execution fully into the kernel's designated virtual address space, enabling correct C runtime operation and access to global symbols via their linked virtual addresses.

  ### 3.4.2 Secure OS Initialization
  Upon transitioning to the C environment after the initial assembly-level setup and MMU activation, the Secure OS undertakes a comprehensive initialization sequence to bring its core components online. This phase is orchestrated primarily within the early_boot and subsequent main C functions.

   #### 3.4.2.1 Register Console
   The first step in the C environment is to establish a means for outputting diagnostic information and logs.
  - The console driver, utilizing the SBI (Supervisor Binary Interface) console services, is initialized and registered as the primary I/O channel via sbi_register_console().
  - This enables early S-mode print functions (e.g., LOG() macro used in main.c), crucial for debugging and reporting the progress or errors during the subsequent initialization stages.

   #### 3.4.2.2 Initialize Page Tables
   While basic MMU mappings are active, the Secure OS now refines its memory layout with more detailed page table configurations.
  - The kernel's primary page table structures are initialized further by mmu_init_kernel_page_table(), moving beyond the initial large, coarse-grained mappings established in head.S.
  - The virtual memory manager (VMM) then defines and maps various memory regions:
      - Known memory regions are collected via vmm_collect_regions().
      - Specific regions, such as the Flattened Device Tree (FDT) and a linear mapping of all secure RAM, are registered as dynamic regions using vmm_register_dynamic_region().
      - Kernel code and data sections are subsequently mapped to their final virtual addresses within these refined page tables by vmm_map_kernel_regions().
  - This process establishes the definitive virtual memory layout for the kernel, enabling page-level protections and dynamic allocation capabilities.

   #### 3.4.2.3 Second Kernel Relocation (If Needed)
   With more sophisticated page table management available, the kernel ensures all its components reside at their link-time virtual addresses.
  - The vmm_relocate_kernel_regions() function handles the re-mapping of kernel sections if they were loaded at a physical address different from their final virtual address minus the kernel virtual offset.
  - Any temporary mappings established during the initial MMU activation, such as the 1:1 identity map in head.S for early code execution, are implicitly superseded or cleaned up as vmm_map_kernel_regions() establishes the final, more granular mappings for all kernel segments based on their VMA (Virtual Memory Area) definitions.

   #### 3.4.2.4 Initialize Trap Handler
   To manage exceptions, interrupts, and system calls, the Secure OS sets up its trap handling mechanisms.
  - The vector_table_init() function is called to configure the S-mode trap vector, directing CPU exceptions and interrupts to the Secure OS's central trap dispatcher.
  - This includes setting up handlers for synchronous exceptions (like environment calls from Trusted Applications), asynchronous interrupts (e.g., timer, IPIs), and fault conditions.

   #### 3.4.2.5 Initialize Timers
   Timers are essential for scheduling and timekeeping within the Secure OS.
  - Platform-specific timer hardware is initialized first, typically using information from the FDT, via arch_timer_init(fdt). This configures the underlying hardware timer for generating periodic interrupts.
  - Subsequently, the kernel's timer subsystem is initialized by timer_init(). This sets up software timer structures and prepares the system to use the hardware timer for scheduling ticks and managing timed events.

   #### 3.4.2.6 Initialize Page Allocator
   To manage the physical memory available to the Secure World, a physical page allocator is crucial.
  - The Secure OS's memory layout, including available RAM regions, is determined by arch_mem_initilize(fdt).
  - The physical memory manager (PMM) is then initialized via pmm_init(). This function creates data structures (e.g., free lists or bitmaps) to track the status of all physical memory pages designated for secure use, enabling dynamic allocation and deallocation of page frames.

   #### 3.4.2.7 Initialize Slab Allocator
   For efficient management of smaller, frequently allocated kernel objects, a slab allocator is established on top of the page allocator.
  - The kernel_slabs_init() function initializes the slab allocator. This sets up caches for various common object sizes, reducing fragmentation and improving the performance of allocating and freeing kernel data structures (e.g., task control blocks, thread structures, IPC message Suffer).

   #### 3.4.2.8 Initialize Scheduler
   The scheduler is responsible for managing the execution of threads within the Secure OS.
  - The foundational tasking structures are prepared by init_system_task(), which may set up initial kernel task contexts or the idle thread.
  - The scheduler's data structures (e.g., run queues) are set up, and it's integrated with the timer subsystem (initialized via timer_init()) to enable preemptive, time-sliced scheduling based on the Round-Robin policy.

   #### 3.4.2.9 Initialize Root Task
   The Root Task is a critical component, acting as the first privileged process in the Secure World, responsible for managing Trusted Applications and inter-world communication requests.
  - Following scheduler initialization, spawn_root_task() is called (unless specific test configurations like BLOWFISH_TEST are active).
  - This involves loading the Root Task's ELF binary, setting up its dedicated address space, allocating its initial resources (including handles specified in its manifest), and creating its main thread, making it ready to process requests.

   #### 3.4.2.10 Initialize Normal World Communication Channel
   To enable interaction with the Normal World (Linux), the dedicated communication infrastructure is initialized.
  - The nwd_channel_init(fdt) function sets up the shared memory queues. This involves:
      - Identifying the physical memory regions for the request and response queues from the FDT.
      - Mapping these shared pages into the Secure OS's address space.
      - Initializing the MPMC (Multi-Producer Multi-Consumer) lock-free queue data structures for both request and response paths.
  - Mechanisms for IPI (Inter-Processor Interrupt) signaling, particularly for Normal World to Secure World notifications, are also readied, relying on the already initialized trap handler.

   #### 3.4.2.11 Initialize Trusted Applications
   While most Trusted Applications (TAs) are spawned dynamically by the Root Task upon request from the Normal World via TEEC_OpenSession, this stage ensures the foundational environment for TA execution is in place.
  - The primary action is the initialization and spawning of the Root Task itself (as covered in 3.4.2.9), which is the main entity responsible for loading, managing, and interfacing with all other TAs.
  - The underlying Secure OS services that TAs rely on are now active: an initialized memory management system capable of creating isolated TA address spaces, a scheduler to run TA threads, and a system call interface for TAs to request kernel services.
  - Any pre-installed or built-in system-level TAs, if designed to start alongside the Root Task, would be loaded and initialized by the Root Task as part of its own startup sequence, often by parsing their respective manifests from the system's simple file system (e.g., linear RAM FS).

 ## Cross-World Communication
 - This chapter describes the mechanisms enabling data exchange and signaling between the Secure OS running on the primary CPU core(s) and the Normal World (e.g., Linux). It focuses on the shared memory queues, the message structure used for TEE commands, and the IPI mechanism for sending interrupts across RISC-V cores.

  ### 3.5.1 Lock-Free Queue Algorithm
  Communication between the Normal World (Linux) and the Secure World (Secure OS) relies on shared memory queues. To ensure efficient and safe concurrent access from both worlds without traditional locks, a lock-free Multi-Producer Multi-Consumer (MPMC) queue algorithm is employed. This section describes the general principles of lock-free algorithms and details the specific MPMC queue implementation used.

   #### 3.5.1.1 General Introduction to Lock-Free Algorithms

   Lock-free algorithms are a class of concurrent algorithms that ensure system-wide progress: if one or more threads are executing operations on a data structure, at least one thread must complete its operation within a finite number of its own steps, regardless of the state (e.g., suspension, crash) of other threads. This is a stronger guarantee than mutual exclusion using locks, which can suffer from issues such as:
   *   **Deadlocks**: Where threads indefinitely wait for resources held by each other.
   *   **Priority Inversion**: Where a high-priority thread is blocked waiting for a low-priority thread holding a lock.
   *   **Convoying**: Where a queue of threads forms waiting for a lock held for an extended period.

   Lock-free algorithms typically rely on atomic hardware primitives, such as Compare-And-Swap (CAS) or Load-Linked/Store-Conditional (LL/SC), to manage concurrent state changes.

   **Benefits:**
   *   **Improved Scalability**: Reduced contention points can lead to better performance in multi-core systems.
   *   **Fault Tolerance**: The progress guarantee means slower or crashed threads do not necessarily block the entire system (for operations on that data structure).
   *   **Interrupt Safety**: Suitable algorithms can often be used safely in interrupt handlers or other restricted contexts where blocking is not permissible.

   **Challenges:**
   *   **Complexity**: Designing correct lock-free algorithms is significantly more complex than lock-based ones.
   *   **ABA Problem**: A common pitfall where a memory location is read twice, has the same value both times, but was modified by another thread in between. Naive CAS operations can incorrectly succeed in such scenarios. Careful design, often using version counters or tags, is needed to avoid it.
   *   **Memory Reordering**: Compilers and CPUs can reorder memory operations, requiring explicit memory barriers or atomic operations with specific memory ordering semantics (e.g., acquire, release) to ensure correctness.

   #### 3.5.1.2 The Implemented MPMC Queue Algorithm

   The chosen MPMC queue is a bounded, array-based (ring buffer) queue designed for high performance by leveraging atomic operations and careful management of sequence numbers to coordinate producers and consumers. This algorithm is similar in principle to designs like Dmitry Vyukov's bounded MPMC queue.

   ##### 3.5.1.2.1 Core Idea
   Each slot in the queue's ring buffer is associated with a sequence number (seq). Producers and consumers use global atomic counters (enqueue and dequeue respectively) to obtain "tickets" for accessing specific logical slots. A producer attempting to write to logical slot pos can only do so if the target physical cell's seq matches pos. After writing, the producer updates the cell's seq to pos + 1. A consumer attempting to read from logical slot pos can only do so if the target physical cell's seq matches pos + 1. After reading, the consumer updates the cell's seq to pos + N (where N is the queue capacity), marking it available for a future enqueue operation at pos + N. This scheme ensures that cells are processed in order and correctly handed off between producers and consumers.

   ##### 3.5.1.2.2 Data Structures
   The queue implementation relies on two main structures:

   *   **mpmc_queue**: Represents the shared queue.
       c
       typedef struct {
           void *data;             // Pointer to the backing circular buffer of queue_cell
           size_t size_mask;       // Mask for calculating index in circular buffer (capacity - 1)
           size_t cell_size;       // Size of a single queue_cell (including data)
           size_t data_size;       // Size of the user data within a cell
           _Atomic size_t enqueue cacheline_aligned; // Global counter for next enqueue ticket
           _Atomic size_t dequeue cacheline_aligned; // Global counter for next dequeue ticket
       } mpmc_queue;

       The enqueue and dequeue counters are aligned to cache lines to prevent false sharing between cores that might be simultaneously trying to produce and consume. The queue capacity must be a power of 2 allowing for efficient index calculation using size_mask.

   *   **queue_cell**: Represents an individual slot in the queue.
       c
       typedef struct {
           _Atomic int seq;        // Sequence number for this cell
           unsigned char data[];   // Flexible array member for storing the actual data
       } queue_cell;

       The seq field is atomic, as it's the primary mechanism for synchronization between producers and consumers for a given cell.


   ##### 3.5.1.2.3 Initialization
   The mpmc_queue_init function initializes the queue:
   1.  The backing memory buffer, its total size, the size of the data elements, and the calculated cell size are provided.
   2.  The enqueue and dequeue atomic counters are initialized to 0 using atomic_store_explicit with __ATOMIC_RELAXED memory order.
   3.  The size_mask is calculated as capacity - 1.
   4.  Crucially, each queue_cell at index i in the buffer has its seq field initialized to i (atomic_store_explicit(&cell->seq, i, __ATOMIC_RELAXED)). This state (cell[i].seq == i) signifies that cell i is ready for the i-th enqueue operation (i.e., when the global enqueue counter equals i).

   ##### 3.5.1.2.4 Enqueue Operation (mpmc_queue_push)
   A producer wishing to add an item to the queue performs the following steps:
   1.  **Get Ticket**: Atomically load the current enqueue counter value, pos (atomic_load_explicit(&queue->enqueue, __ATOMIC_RELAXED)). This pos is the logical slot the producer aims to fill.
   2.  **Attempt to Claim Slot**:
       a.  Calculate the physical cell index: idx = pos & queue->size_mask.
       b.  Atomically load the seq from cell[idx] with __ATOMIC_ACQUIRE memory order. This ensures any previous writes to this cell (e.g., by a consumer freeing it) are visible.
       c.  **Verify Slot State**: Check if cell[idx].seq == pos.
           *   If true, a consumer has prepared this cell for the pos-th enqueue operation. The producer can try to claim this ticket. It attempts to atomically increment queue->enqueue from pos to pos + 1 using atomic_compare_exchange_weak_explicit with __ATOMIC_RELAXED for both success and failure.
               *   If CAS succeeds, the producer has successfully claimed the ticket pos. It breaks a retry loop.
               *   If CAS fails, another producer claimed ticket pos. The current producer's pos is updated by CAS to the current queue->enqueue value and it re-evaluates its claim in the loop.
           *   If cell[idx].seq < pos, the queue is full at this cell. The cell is from a previous lap and still holds data that hasn't been dequeued, or it's concurrently being dequeued. The push operation returns false (queue full).
           *   If cell[idx].seq > pos, the current pos might be stale or based on an older view of queue->enqueue. The producer reloads pos from queue->enqueue (atomic_load_explicit(&queue->enqueue, __ATOMIC_RELAXED)) and retries the claim process.
   3.  **Write Data**: Once a slot is successfully claimed, memcpy the user's data into cell[idx].data.
   4.  **Signal Data Ready**: Atomically store pos + 1 into cell[idx].seq using atomic_store_explicit with __ATOMIC_RELEASE memory order. This makes the data write visible to consumers and signals that the pos-th item is ready for dequeue. The pos + 1 value is what a consumer will expect for this slot.

   ##### 3.5.1.2.5 Dequeue Operation (mpmc_queue_pop)
   A consumer wishing to retrieve an item from the queue performs these steps:
   1.  **Get Ticket**: Atomically load the current dequeue counter value, pos (atomic_load_explicit(&queue->dequeue, __ATOMIC_RELAXED)). This pos is the logical slot the consumer aims to read.
   2.  **Attempt to Claim Item**:
       a.  Calculate the physical cell index: idx = pos & queue->size_mask.
       b.  Atomically load the seq from cell[idx] with __ATOMIC_ACQUIRE memory order. This ensures the data write from the producer and its seq update are visible.
       c.  **Verify Slot State**: Check if cell[idx].seq == pos + 1.
           *   If true, the pos-th enqueue operation has completed for this cell, and it contains data ready for dequeue. The consumer can try to claim this ticket. It attempts to atomically increment queue->dequeue from pos to pos + 1 using atomic_compare_exchange_weak_explicit with __ATOMIC_RELAXED for success and failure.
               *   If CAS succeeds, the consumer has successfully claimed the item at ticket pos. It breaks a retry loop.
               *   If CAS fails, another consumer claimed this item. The current consumer's pos is updated by CAS and it re-evaluates its claim in the loop.
           *   If cell[idx].seq < pos + 1, the queue is empty at this cell. The cell is either in its initial state (seq == pos) or has been freed by a previous dequeue from an earlier lap. The pop operation returns false (queue empty).
           *   If cell[idx].seq > pos + 1, the current pos might be stale. The consumer reloads pos from queue->dequeue (atomic_load_explicit(&queue->dequeue, __ATOMIC_RELAXED)) and retries.
   3.  **Read Data**: Once an item is successfully claimed, memcpy the data from cell[idx].data to the user's buffer.
   4.  **Signal Slot Empty**: Atomically store pos + queue->size_mask + 1 (which is pos + capacity) into cell[idx].seq using atomic_store_explicit with __ATOMIC_RELEASE memory order. This marks the cell as empty and available for a future enqueue operation, specifically the one identified by ticket pos + capacity.

   ##### 3.5.1.2.6 Correctness and Performance Considerations
   *   **Atomicity and Ordering**: The use of atomic operations on enqueue, dequeue, and seq fields, along with appropriate memory ordering semantics (__ATOMIC_ACQUIRE on reads of seq that gate data access, __ATOMIC_RELEASE on writes to seq after data operations), ensures correct synchronization and visibility of data between producers and consumers.
   *   **ABA Problem Avoidance**: The seq numbers and the global enqueue/dequeue ticket counters are monotonically increasing (modulo counter overflow for extremely long-lived queues). A cell's seq value cycles through X, X+1, X+capacity, X+capacity+1, etc. The specific checks (cell->seq == pos for enqueue, cell->seq == pos + 1 for dequeue) target unique states in this progression relative to the global ticket pos, effectively avoiding the ABA problem for the control variables of the queue cell state.
   *   **Lock-Freedom**: In case of contention on enqueue or dequeue counters (multiple producers or consumers), the CAS operation ensures that only one thread succeeds at a time, advancing the counter. If a thread's CAS fails, it implies another thread made progress. Thus, system-wide progress is guaranteed.
   *   **False Sharing**: The cacheline_aligned attribute for enqueue and dequeue counters in the mpmc_queue struct is critical for performance. It prevents these frequently updated atomic variables, which are typically modified by different cores (producer core vs consumer core), from residing on the same cache line and causing excessive cache coherency traffic (false sharing).
   *   **Suitability**: This type of queue is well-suited for inter-world communication via shared memory as it avoids kernel intervention (locks, semaphores) for synchronization, reducing overhead. It can operate efficiently even when producers and consumers are in different privilege levels or running on different types of OS environments, provided they map the shared memory and can perform atomic operations.

  ### Shared Memory Queues
  Inter-world communication relies on shared memory queues, which are implemented as ring buffers situated in memory regions accessible by both the Normal World (NWd) and Secure World (SWd). These queues utilize the lock-free MPMC algorithm described in section 3.5.1 for concurrent access.

   #### 3.5.2.1 Shared Memory Ring Buffers
   The communication queues are implemented as ring buffers residing within two dedicated physical memory pages. These pages are configured by the Secure OS using WorldGuard to grant shared read/write access permissions to both the Secure World and the Normal World, specifically tailored for each queue's producer/consumer roles.

   Each ring buffer is a circular array of fixed-size message slots, designed to hold wg_tee_cmd structures. The MPMC queue algorithm, as detailed in section 3.5.1, manages access to these slots using atomic enqueue (head) and dequeue (tail) counters rather than explicit head/tail pointers directly manipulated by the worlds. This mechanism obviates the need for locks.

   Memory alignment is critical. The mpmc_queue structure itself aligns its atomic enqueue and dequeue counters to cache line boundaries to mitigate false sharing between the CPU core executing the Secure OS and the core(s) executing Linux. Message slots within the ring buffer are also appropriately aligned to accommodate the wg_tee_cmd structure, preventing performance degradation due to unaligned accesses.

   #### 3.5.2.2 Requests Queue
   A dedicated ring buffer, hosted on one of the shared memory pages, serves as the Requests Queue. The Normal World (Linux driver) acts as the producer, placing requests for the Secure World to process. The Secure OS is the consumer of this queue.

   The process for the Normal World to enqueue a request involves:
   1.  The Linux driver serializes the TEE command into a wg_tee_cmd structure.
   2.  The driver attempts to push this structure into an available slot in the Requests Queue using the mpmc_queue_push operation. This function internally handles claiming a slot and atomically updating the queue's enqueue counter.
   3.  Upon successful enqueueing, the Linux driver typically sends an Inter-Processor Interrupt (IPI) to the Secure OS core to notify it of the new request, as detailed in section 3.5.5.2.

   #### 3.5.2.3 Responses Queue
   A-separate ring buffer, utilizing the second shared memory page, functions as the Responses Queue. The Secure OS acts as the producer, placing results of processed TEE commands or event notifications into this queue. The Normal World (Linux driver) is the consumer.

   The Secure OS enqueues a response by:
   1.  Populating a wg_tee_cmd structure with the result of an operation.
   2.  Pushing this structure into the Responses Queue using its mpmc_queue_push (or equivalent internal) function. This atomically updates the enqueue counter for the Responses Queue.
   3.  The Normal World driver relies on a polling mechanism to check this queue for completed responses, as described in section 3.5.5.3.

   #### 3.5.2.4 Canary Around Shared Pages
   To detect and prevent buffer overflow or underflow conditions on the shared queue pages, canary pages are implemented. The Secure OS, during initialization (as mentioned in section 3.3.2.3), configures WorldGuard rules for the physical pages immediately adjacent to (before and after) the two shared memory pages used for the queues.

   These canary pages are marked by WorldGuard with permissions denying all types of access (read, write, execute) from both WID 0 (Secure World) and WID 1 (Normal World). If an erroneous operation by either world attempts to access memory beyond the allocated boundaries of a shared queue, it will touch one of these canary pages. This unauthorized access attempt triggers a hardware fault (trap) reported by WorldGuard, allowing the system to detect such memory safety violations and take appropriate action, such as loggingthe error or terminating the offending component.

  ### 3.5.3 Shared Memory Regions
  Aside from the primary queues used for command and response signaling, the system supports the dynamic allocation and sharing of larger memory regions. These regions facilitate bulk data transfer between the Normal World and Trusted Applications running in the Secure World.

   #### 3.5.3.1 Memory Region Allocation
   The allocation of a shared memory region is initiated by the Normal World (Linux) by invoking the TEE_CMD_ID_MAP_SHARED_MEM secure operation. This request is processed by the Secure OS as follows:

   1.  **Page Allocation in Secure World**: The Secure OS allocates the requested number of physical memory pages from its own managed pool.
   2.  **Access Configuration**: WorldGuard checker rules are configured for these allocated pages to grant simultaneous access permissions (e.g., read, write) to both the Secure World (acting on behalf of a Trusted Application) and the Normal World. The specific permissions granted can be tailored to the use case.
   3.  **Secure OS Mapping**: The Secure OS maps these physical pages into its own kernel address space. This allows the Secure OS itself, or subsequently the designated Trusted Application, to access the shared memory. The physical address and size of the region are prepared for return to the Normal World.
   4.  **Normal World Mapping**: Upon successful allocation and configuration in the Secure World, the Linux driver receives the physical base address and size of the shared region. The driver is then responsible for mapping these physical pages into the Linux kernel's virtual address space, making the region accessible from the Normal World. An identifier for this shared memory region (shmem_id) is also returned to the Normal World for future reference.

   #### 3.5.3.2 Memory Region Deallocation
   Deallocation is initiated by the Normal World by invoking the TEE_CMD_ID_UNMAP_SHARED_MEM secure operation, typically referencing the shmem_id obtained during allocation. The Secure OS handles this request through the following steps:

   1.  **Secure World Revocation**: The Secure OS first ensures that the Trusted Application (if any) has ceased using the memory. It then reconfigures the WorldGuard checker rules associated with the physical pages of the shared region to revoke all access permissions for both the Secure World and the Normal World.
   2.  **Secure OS Unmapping**: The Secure OS unmaps the region from its kernel address space.
   3.  **Page Deallocation**: The physical pages are returned to the Secure OS's free memory pool.
   4.  **Normal World Unmapping**: After the Secure OS confirms deallocation, the Linux driver unmaps the corresponding memory region from the Linux kernel's virtual address space, releasing the virtual addresses.

   #### 3.5.3.3 Data Transfer
   Once a shared memory region is successfully allocated and mapped into the virtual address spaces of both the Linux kernel and the Secure OS (making it accessible to a Trusted Application), data transfer between the two worlds can occur directly through standard memory read and write operations.

   *   Both the Normal World and the Secure World component (e.g., a Trusted Application) holding a valid mapping can access the shared data by simply reading from or writing to the virtual addresses corresponding to the shared physical pages.
   *   No specialized communication primitives or inter-world calls are required for the actual data movement within an established shared_memory region, beyond ensuring appropriate synchronization between the producer and consumer of the data if concurrent access is involved. The efficiency of this transfer is only limited by memory bandwidth and cache coherency mechanisms.

  ### Message Structure
  All commands passed through the request and response queues adhere to a consistent message format. This subsection details the wg_tee_cmd structure, which is designed to encapsulate TEE operation parameters and results. The structure serves as the fundamental unit of communication, holding command identifiers, session tracking information, error codes, and payload parameters for TEE operations. Adherence to this fixed structure simplifies parsing and processing logic in both the Normal and Secure Worlds.

   #### 3.5.4.1 struct wg_tee_cmd
   The wg_tee_cmd structure is the primary data packet for inter-world communication via shared memory queues. It standardizes the format for all TEE command requests originating from the Normal World and responses from the Secure OS. Key components include a command identifier, a sequence number for tracking, session and Trusted Application identifiers, operational parameters or memory mapping details, and a field for return codes. The structure is padded to a fixed size (256 bytes) to ensure predictable alignment within the shared memory queues.

   #### 3.5.4.2 field id
   The uint32_t id field specifies the type of TEE operation being requested or responded to. It allows the receiving world to dispatch the command to the appropriate handler. Defined command identifiers include:
   *   TEE_CMD_ID_OPEN_SESSION: Initiates a new session with a Trusted Application.
   *   TEE_CMD_ID_CLOSE_SESSION: Terminates an existing session with a Trusted Application.
   *   TEE_CMD_ID_INVOKE_CMD: Calls a specific function within an active Trusted Application session.
   *   TEE_CMD_ID_MAP_SHARED_MEM: Requests the Secure OS to map a region of physical memory as shared between the Normal and Secure Worlds.
   *   TEE_CMD_ID_UNMAP_SHARED_MEM: Requests the Secure OS to unmap a previously shared memory region.

   #### 3.5.4.3 field seq
   The uint32_t seq field provides a unique identifier for each command instance. This sequence number is generated by the Normal World by atomically incrementing a counter for each new request. The Secure OS includes this seq number in its response, enabling the Normal World client to correlate responses with their original requests, especially in asynchronous communication models.

   #### 3.5.4.4 field session_id
   The uint32_t session_id field identifies the specific session to which a command pertains. Upon successful execution of a TEE_CMD_ID_OPEN_SESSION command, the Secure OS returns a session_id to the Normal World. Subsequent TEE_CMD_ID_INVOKE_CMD and TEE_CMD_ID_CLOSE_SESSION commands must include this session_id to target the correct TA instance and its associated context. This allows a single Client Application in the Normal World to manage multiple concurrent sessions with one or more TAs.

   #### 3.5.4.5 field func_id
   The uint32_t func_id field is utilized specifically with the TEE_CMD_ID_INVOKE_CMD command. Each Trusted Application may expose multiple functions or commands. This field allows the Normal World client to stipulate which specific action or function, identified by func_id, should be executed by the TA during an InvokeCommand operation.

   #### 3.5.4.6 field err
   The uint32_t err field is predominantly used in responses from the Secure OS to the Normal World. It conveys the outcome of the requested TEE operation. A value of TEEC_SUCCESS (typically 0) indicates successful completion, while other values signify various error conditions, such as TEEC_ERROR_BAD_PARAMETERS, TEEC_ERROR_ACCESS_DENIED, or TA-specific errors.

   #### 3.5.4.7 field uuid
   The uint8_t uuid[16] field contains a 128-bit Universally Unique Identifier that uniquely identifies a Trusted Application. This field is primarily used during the TEE_CMD_ID_OPEN_SESSION operation, where the Normal World client provides the UUID of the TA it wishes to connect to. The Secure OS uses this UUID to locate and instantiate the correct TA.

   #### 3.5.4.8 field paddr
   The uint64_t paddr field is relevant for shared memory operations, specifically for command TEE_CMD_ID_MAP_SHARED_MEM. It specifies the starting physical address of the memory region in the Normal World that is to be mapped into the Secure World as shared memory. For other command IDs, this field typically remains unused.

   #### 3.5.4.9 field num_pages
   The uint32_t num_pages field complements the paddr field for TEE_CMD_ID_MAP_SHARED_MEM operations. It specifies the number of contiguous physical memory pages, starting from paddr, that should be included in the shared memory mapping. This field is unused for other command IDs.

   #### 3.5.4.10 field shmem_id
   The uint32_t shmem_id field serves as a handle or identifier for a successfully mapped shared memory region. When the Secure OS processes a TEE_CMD_ID_MAP_SHARED_MEM request, it returns a shmem_id in the response. This identifier must then be provided by the Normal World client in subsequent TEE_CMD_ID_UNMAP_SHARED_MEM requests to specify which shared memory region to deallocate and unmap.

   #### 3.5.4.11 struct wg_param params
   The struct wg_param params[4] field is an array of four structures, each of 24 bytes, designed to pass parameters to and from a Trusted Application during a TEE_CMD_ID_INVOKE_CMD operation. This mirrors the GlobalPlatform TEE Client API's TEEC_Operation structure, which allows up to four parameters.

   Each wg_param can represent either a small value passed directly or a reference to a memory region. Specifically:
   *   **Simple arguments (values):** Small data values can be stored directly within the 24-byte space of a wg_param. The interpretation of these values is TA-specific.
   *   **Memory references:** For larger data buffers, a wg_param can represent a memory reference. In this implementation, a memory reference is structured as three 64-bit values: size (the size of the referenced memory region), offset (the offset within a shared memory region identified by shmem_id, or an absolute physical address if contextually appropriate), and world_id (identifying whether the memory resides in the Normal or Secure World, or if it is shared memory).

   The type of each parameter (value or memory reference direction: input, output, inout) is typically communicated through a separate paramTypes field, implicitly handled by the TEE API implementation or associated context not detailed in this wg_tee_cmd specific overview, but crucial for interpreting params.

   #### 3.5.4.12 padding
   The uint8_t padding[108] field consists of reserved space used to align the total size of the wg_tee_cmd structure to 256 bytes. This fixed overall size simplifies queue management by ensuring that each message occupies a predictable number of cache lines and facilitates easier calculation of slot offsets within the shared memory ring buffers. Explicit padding prevents variations due to compiler-specific alignment behaviors across different toolchains or platforms.

   ### 3.5.5 IPI Based Signaling
   While shared memory queues provide the data structures for exchanging command and response messages between the Normal and Secure Worlds, an Inter-Processor Interrupt (IPI) mechanism is employed to trigger real-time notifications about new messages. This ensures that the recipient world can process incoming messages promptly without resorting to continuous, high-frequency polling of the queues, thereby reducing CPU overhead.

   #### 3.5.5.1 RISC-V IPI Mechanism
   The RISC-V architecture provides mechanisms for sending IPIs between harts (hardware threads or cores). Software running on one hart can trigger an interrupt on another target hart. This is typically achieved by writing to a memory-mapped register associated with the target hart's interrupt controller, such as the Supervisor Software Interrupt Pending (SSIP) bit in the sip CSR, or by using platform-level interrupt controllers like the Core Local Interruptor (CLINT) through its memory-mapped software interrupt registers (msip).

   Alternatively, and more commonly in systems utilizing a Supervisor Binary Interface (SBI) implementation like OpenSBI, IPIs are sent via an SBI call (e.g., sbi_send_ipi). The SBI call abstracts the underlying hardware details, allowing privileged software (like the Linux kernel or the Secure OS) to request an IPI to be sent to a specified set of harts. The OpenSBI implementation running in M-mode then handles the hardware-specific actions to deliver the IPI.

   #### 3.5.5.2 Normal to Secure World Signaling
   When the Linux driver in the Normal World needs to send a command to the Secure OS, it follows this procedure:
   1.  The driver populates a wg_tee_cmd structure with the command details and parameters.
   2.  This structure is then pushed onto the shared request queue using the lock-free MPMC queue algorithm.
   3.  After successfully enqueuing the command, the driver triggers an IPI specifically targeting the hart on which the Secure OS is executing (core 0 in this project). This IPI is typically sent via an sbi_send_ipi call provided by OpenSBI.
   4.  The IPI serves as a signal to the Secure OS, prompting it to check the request queue for new messages. The requesting thread in the Linux driver then typically waits (e.g., blocks on a completion variable) for the response to appear in the response queue.

   This IPI-based notification minimizes the latency between a command being sent and the Secure OS beginning its processing.

   #### 3.5.5.3 Secure to Normal World Signaling
   In the reverse direction, when the Secure OS has processed a command and placed a response into the shared response queue, the signaling mechanism is different. Due to architectural considerations and the desire to simplify interrupt handling in the Normal World Linux kernel, the Secure OS does not send an IPI back to the Normal World cores.

   A primary reason for this design choice is the potential difficulty in the Linux kernel reliably distinguishing an IPI specifically originating from the Secure OS for TEE communication from other types of IPIs it might receive (e.g., for scheduler KSM, TLB shootdowns, or other kernel subsystems). Incorrectly handling or misinterpreting such IPIs could lead to instability.

   Consequently, the communication flow for responses is as follows:
   1.  The Secure OS processes the request and places the wg_tee_cmd response structure into the shared response queue.
   2.  The Linux driver in the Normal World employs a polling mechanism. A dedicated kernel thread or a periodic timer checks the response queue for completed commands.
   3.  When the polling mechanism finds a response corresponding to a pending request (matched via the seq field), it retrieves the response and wakes up the original requesting thread, delivering the result.

   While polling can introduce some latency compared to a direct interrupt, it simplifies the interrupt management on the Linux side and avoids the complexities of a bidirectional IPI signaling protocol for this specific TEE interaction. The polling frequency can be tuned to balance responsiveness and CPU overhead.

 ## TEE API
  ### Global Platform API
   #### Introduction to Global Platform API
   - *introduction from OP-TEE Global Platfrom API spec*
  ### TEE Client API
   #### TEE Contexts
   - *contexts chapter*
   #### TEE Sessions
   - *sessions chapter*
   #### TEE Shared Memory
   - *shared memory chapter*

  ### TEE API Specification
   #### TEEC_UUID
   - describe ...
   #### TEEC_Result
   - describe ...
   #### TEEC_Context;
   - describe ...
   #### TEEC_Session;
   - describe ...
   #### TEEC_Value;
   - describe ...
   #### TEEC_RegisteredMemoryReference;
   - describe ...
   #### TEEC_Parameter;
   - describe ...
   #### TEEC_Operation;
   - describe ...
   #### TEEC_SharedMemory;
   - describe ...
   #### TEEC_InitializeContext
   - describe ...
   #### TEEC_FinalizeContext
   - describe ...
   #### TEEC_OpenSession
   - describe ...
   #### TEEC_CloseSession
   - describe ...
   #### TEEC_InvokeCommand
   - describe ...
   #### TEEC_AllocateSharedMemory
   - describe ...
   #### TEEC_ReleaseSharedMemory
   - describe ...

 ## Дизайн и реализация ядра Secure OS
 - В данной секции рассматриваются основные аспекты проектирования и реализации ядра защищённой операционной системы (Secure OS).
 - Предложенный подход основан на использовании объектно-ориентированного (capability-based) подхода и позволяет обеспечить высокий уровень изоляции между задачами (tasks) и сервисами (threads), а также гарантировать безопасность при взаимодействии с внешними ресурсами и другими компонентами системы.
 - Рассмотрим детальную структуру, начиная с ключевых сущностей и механизмов управления.
  ### Kernel Objects and Handles
  - Взаимодействие с ресурсами внутри ядра построено вокруг объектной модели. Каждый объект в системе (например, задача, поток, виртуальный объект памяти, канал связи и т.д.) имеет свой уникальный дескриптор (handle). Доступ к функциональным методам объекта и внутреннему состоянию определяется набором capability-флагов (прав доступа).
   #### Tasks (Processes)
   - Задачи (tasks) являются основными изолированными сущностями в Secure OS.
   - Они содержат собственное адресное пространство (vm_space) и набор потоков (threads).
   - Кодовая составляющая задачи находится в пользовательском адресном пространстве безопасной среды (для Trusted Applications).
   - Каждая задача имеет таблицу объектов (object_table), где регистрируются все ресурсы (включая каналы, объекты памяти и др.), предназначенные для её использования.
   - создание задачи состоит из следующих этапов:
   1. Создание пустой пользовательской задачи (task_create_empty) – формирование объектов структуры task, включая инициализацию отдельных полей (handle_page, object_table и т.д.).
   2. Запуск задачи (task_run) – настройка защиты памяти для страницы дескрипторов (handle_page), установка состояния (TASK_SPAWNED) и добавление главного потока задачи в планировщик (sched_insert).
   3. Уничтожение задачи (task_destroy) – освобождение адресного пространства (vm_space_destroy) и освобождение динамически выделенной памяти.
   - Пример создания задачи на основе системного вызова task_spawn показывает, как пользователь может передать в ядро указатель на точку входа (ep) и handle задачи, а ядро создаёт в ней начальный поток и переводит задачу в состояние выполнения.
   - *пример*
   #### Threads
   - Каждая задача содержит по крайней мере один поток (thread).
   - Потоки отвечают за выполнение кода внутри адресного пространства задачи.
   - При создании пользовательского потока ядро настраивает контекст выполнения (регистры, стек, текущее окружение и т.д.).
   - При создании процесса (task), ядро создаёт «главный поток» задачи, устанавливая ему точку входа (ep). После этого поток регистрируется в списке потоков (list_head_add_tail) и может быть запланирован планировщиком.
   #### Pipes (или Channels)
   - Вместо классических «каналов» (pipes) в ядре используются объекты «channel» (двухсторонние каналы связи). Они создаются фабрикой (см. factory.c, syscall channel_create) и позволяют процессам или компонентам ядра обмениваться сообщениями по дескрипторам с установленными привилегиями.
   - Канал представлен двумя концами (rx/tx), которые могут принадлежать одной или разным задачам.
   #### Virtual Memory Objects
   - Объекты виртуальной памяти (VM Object) отображают некоторый участок памяти (обычно физической) в адресное пространство задачи.
   - В ОС реализован системный вызов vmo_create, который позволяет создавать vm_object через фабрику (factory_object).
   - После создания объект регистрируется в таблице дескрипторов c соответствующими правами (OBJECT_CAP_TRANSFER, VMO_CAP_FULL и пр.), что позволяет разграничивать операции чтения, записи и копирования.
   #### Synchronization Primitives
   - В ядре имеется набор примитивов синхронизации
   - spin_lock
   - mutex
   - semaphore
   - Очереди ожидания (wait_queue_init, wait_object_many) – абстракция, позволяющая потокам ждать появление событий (например, данных в канале).

  ### Task Management
  - Механизм управления задачами (Task Management) в Secure OS определяет подсистему, в рамках которой задачи создаются, запускаются и завершаются.
   #### Process Model
   - Процессная модель предполагает, что каждая задача имеет собственное адресное пространство и набор ресурсов, зарегистрированных в ядре.
   - Создание задачи происходит по запросу пользовательского процесса либо при создании сессии для новой TA, через системный вызов (task_create). Перед запуском задачи ядро выделяет нужные структуры данных, инициализирует объект задачи и подключает его к планировщику. При этом задача находится в состоянии TASK_CREATED, пока не будет вызвана функция task_spawn, переводящая её в состояние TASK_SPAWNED.
   #### IPC Service
   - В системе используется механизм IPC на основе каналов (channels). Каждая задача может получить дескрипторы двух сторон канала, позволящие выполнять операции чтения/записи (channel_read()/channel_send()).
   - Кроме того, для организации группового ожидания сообщений служит вызов wait_object_many, позволяющий одним системным вызовом ожидать события от нескольких объектов.
   - Затем сообщение извлекается (channel_read) и, результат работы, отправляется обратно (channel_send).
   #### Root Task
   - Root Task (root_task.c) является важной задачей, поддерживающей цикл обработки входящих запросов и сообщений от других процессов и ядровых сервисов. Здесь можно заметить:
   - Использование структуры wait_entry для инициализации нескольких объектов ожидания (каналов).
   - Циклическую обработку arriving-сообщений.
   - Вызов nwd_proccess_message для обработки поступивших команд от Normal World
   - Таким образом, root task служит центральной точкой обмена сообщениями между Secure OS и Normal World.

  ### Scheduling
  - Планировщик отвечает за распределение ресурсов процессора между потоками, находящимися в состоянии готовности к выполнению. В ядре реализованы базовые механизмы планирования, ориентированные на простоту и расширяемость.
   #### Scheduling Service
   - Scheduling Service управляет структурами данных, хранящими информацию о потоках (thread) и их состояниях.
   - При создании потока он добавляется в очередь работы планировщика (sched_insert), где ему присваивается базовый приоритет и используется политика Round-Robin (SCHED_RR), которая обеспечивает циклическое распределение времени процессора между всеми runnable-потоками.
   #### Scheduling Policies
   - В качестве политики планирования используется Round-Robin, чтобы обеспечить максимальную простоту и уменьшить количество доверенного кода, так как доверенные приложения не обладают сложной логикой, требующей более точной диспетчеризации
   - В данной реализации (task_create_initial_thread инициализирует потоки с SCHED_RR) применяется классическая политика Round-Robin. Однако архитектура планировщика может быть расширена для поддержки:
    - Приоритетного планирования (приоритеты на основе критичности задачи).
    - Планирования на основе квантования времени (time-slices).
    - Специальных политик для реального времени (real-time scheduling).

  ### Memory Management Subsystem
  - Подсистема управления памятью (Memory Management Subsystem) обеспечивает надежную изоляцию памяти между задачами, а также предоставляет безопасный интерфейс распределения памяти в пространстве ядра и пользовательских задач.
   #### Secure Memory Allocator
   - Для работы с динамически распределяемой памятью в ядре используются следующие механизмы:
   1. Kmalloc/kvfree (или kfree) для управления небольшими блоками памяти в пространстве ядра (см. пример в factory_destroy или task_create_empty).
   2. Специализированные аллокаторы страниц (vm_allocate, vm_space_init_kernel, vm_space_init_user), которые выделяют виртуальные адреса и сопоставляют их с физической памятью, учитывая защитные атрибуты (VMA_READ, VMA_WRITE, VMA_USER).
   - В момент инициализации задачи (task_create_empty) вызывается vm_space_init_user для подготовки пользовательского адресного пространства
   #### Memory Isolation
   - Механизм изоляции достигается с помощью:
   1. Различных адресных пространств (space) для каждой задачи.
   2. Управления таблицами страниц (mmu_switch_space), что позволяет ядру переключаться между контекстами задач и гарантировать, что одна задача не может получить доступ к памяти другой.
   3. Контроля прав доступа к памяти при вызове vm_protect. Данная функция устанавливает соответствующие флаги (VMA_READ, VMA_WRITE) и обеспечивает недоступность памяти для неавторизованных задач.
   - В коде виден пример, когда при запуске задачи (task_run) вызывается vm_protect для установки в памяти read-only доступа к странице дескрипторов (handle page). Таким образом, даже сама задача ограничена в манипуляции с полями, ответственными за управление дескрипторами, если это не предусмотрено соглашениями по доступу.
  ### File System
   #### linear RAM fs
   #### elf files

 ## Capability-Based Security Model
 - This chapter focuses on the design and implementation of the capability-based security model within the Secure OS.
 - It explains how the system uses handles to encapsulate capabilities, how these handles are created and managed, and how capability-based access control is enforced through task manifests and the root task.

  ### MAC and DAC
   #### MAC
   - introduction to MAC
   - advantages
   - disadvantages
   - ...
   #### DAC
   - introduction to DAC
   - advantages
   - disadvantages
   - ...
   #### Cooperative MAC and DAC Security Model
   - Capability-Based access control has granularity of DAC and security of MAC
   - it serves least privilege principle
   - lightweight
   - *other advantages*

  ### Handles as Encapsulated Capabilities
  - Handles in the Secure OS function as references to system resources (objects). Each handle has associated permissions and metadata defining how it may be accessed or manipulated. Internally, handles map to kernel-managed descriptors that maintain the state, permission bits, and relevant object pointers.
   #### Design Rationale
   - Least Privilege Principle: Capabilities ensure that tasks and trusted applications only have the minimum set of privileges needed.
   - Fine-Grained Access Control: Provides precise control over which resources can be accessed and how they are used.
   - Lightweight: MAC is very heavy system that includes database in kernel and control list parsers, and it inflates TCB size
   #### Objects
   - Definition: Objects represent protected resources (e.g., memory regions, tasks, communication channels).
   - Creation: created by a specialized factory object
   - Management: The kernel and corresponding resource managers maintain object lifecycles (allocation, reference counting, destruction).
   #### Object Handles
   - Semantics: An object handle is an token referencing an underlying object.
   - Security Properties: Handles cannot be duplicated or guessed; only the kernel can create valid handles.
   #### Factory Objects
   - Factory Concept: There is a singleton act as “factory” capable of creating other objects (e.g., tasks, pipes, or memory objects).
   - Controlled Creation: A Manifest ensures that only permitted tasks can spawn or instantiate new objects.
   - Lifecycle: Factoty themselve is created by the kernel.
   #### Object Methods
   - Method Calls: Operations on objects (e.g., read, write, map) are exposed as system calls.
   - Capability Checks: Before performing any operation, the kernel verifies that the caller’s handle has sufficient permissions.
   - Extensibility: New object types can not define custom methods, which stricts permission volations

  ### Capability-Based Access Control
  - The system enforces a strict capability-based security policy, ensuring only authorized handles may invoke methods on objects.
   #### Permissions
   - since syscalls act as object methods - there is a fixed number of methods that can be executed on object
   - each handle has its own permission bits for each syscall
   - Permission Propagation: When a handle is shared between tasks, permissions can only be stricted, to increased.
   - Revocation: The kernel can invalidate or downgrade a handle’s permissions at runtime if security conditions change.
   #### Task Manifests
   - Manifest Format: Each task has a manifest specifying its initial handles and allowed permissions on those handles.
   - Initialization: On task creation, the kernel reads the manifest to populate the task’s handle table.
   - Dynamic Policy: The root task or a privileged controller can update or revoke handles from TA
   #### Root Task
   - Privilege Level: The root task is endowed with the highest level of privilege, including the ability to create new tasks and objects
   - Handle Distribution: Upon launching a new trusted application, the root task provides the necessary initial handles listed in the manifest.
   - Security Enforcement: The root task can audit or modify the capabilities of any other task if required.
   #### Method Invocation
   - Invocation Flow:
     1. Trusted application issues a syscall to invoke a method on a handle.
     2. Kernel checks handle validity and permission bits.
     3. Kernel executes the method if authorized; otherwise returns an error.
   - Parameter Passing: Depending on the object type, additional data (e.g., memory buffer addresses or message payload) must be specified.
   - Audit Logging: A log of handle usage may be maintained for debugging, accountability, and forensics.
   #### Performance Implications
   - Lookup Overheads: A balanced design attempts to keep handle operations lightweight to avoid excessive overhead.

 ## Secure Syscalls
 - The Secure Operating System exposes a set of privileged system calls (“secure syscalls”) available only to code running in the Trusted Execution Environment (TEE). These syscalls form the backbone of the secure OS abstraction layer and are fundamental to the capability-based model which enforces strict access and isolation. In this section, we describe the secure syscall mechanism, their capability enforcement, and the secure object operations made available to Trusted Applications (TAs).

  ### Secure Entry Points
  - The secure syscall interface is the only gateway through which TAs and system objects interact. These system calls are verified and dispatched via central syscall routing infrastructure based on a syscall table indexed by syscall number.
   #### Background on OS System Calls
   - A system call facilitates user mode code (in this case, Trusted Applications) to invoke kernel functionality in a controlled and verified manner. Syscalls operate strictly on handles referencing kernel-managed secure objects. The handle list is process-local and authorized through task manifests at TA launch time.
   #### Secure Syscall Lifecycle
   - Each secure syscall follows the canonical secure OS object lifecycle:
   1. User passes handle(s) and optional state.
   2. Kernel resolves the handle reference and asserts access rights using capability tags.
   3. Operation is executed atomically.
   4. Ownership of resulting objects or memory copies is well defined (copy vs. move semantics).
   5. Errors from any stage are returned to the user-space Trusted Application.
   Syscalls involving inter-task communication (e.g., SYS_CHANNEL_WRITE or SYS_TASK_SHARE_HANDLE) often cooperate with internal kernel structures like queues or per-process handle pages. These components are designed to be strictly partitioned and race-free.
   #### Argument Passing Format
   - Syscall arguments are passed following the calling convention of the Secure OS, and include the handle identifiers, pointers to user data, data lengths, and capability-specific flags. Data is validated before being dereferenced or mutation occurs. Shared memory is always accessed via secure copies using kernel-managed copy_from_user and copy_to_user primitives.
   #### Validation of Handle Permissions
   - Each syscall entry validates whether the calling task has the needed capabilities for the given object type. Handles are looked up in the invoking task’s object table, and if the lookup fails or lacks the proper capability flags (TRANSFER, WAIT, SEND, RECV, etc.), the syscall returns an error. This fine-grained check ensures robust per-object and per-action filtering in line with the capability-based security model.
   - Syscalls rely entirely on the underlying capability-based object model:
   - Handles are opaque 32-bit values resolved into kernel pointers via per-task object tables.
   - Each handle links to an internal object and permission mask.
   - All syscall-side object accesses invoke a type+capability check.
   For example, in the channel_write syscall, the following enforcement occurs:
   1. Validate caller owns the provided handle with CHANNEL_CAP_SEND.
   2. Validate all message-passed handles include the TRANSFER capability.
   3. Receiver will only receive transferred handles if it has adequate handle table space.
   This guarantees that:
   - Object accesses are never implicit — they must be manifested in the task manifest.
   - No object leaks across Trusted Application boundaries.
   - Origin and access pathway of each resource is traceable through the handle fabric.

  ### Syscall Specification
  - Each system call operates on one or more kernel object handles. Object types include tasks, threads, virtual memory objects (VMOs), factory objects, and channels. Below is an overview of the currently defined syscalls.
   #### SYS_LOG
   - Logging interface for debugging output from the secure world.
   #### SYS_VM_ALLOCATE
   - Allocates anonymous virtual memory inside a task’s virtual address space.
   #### SYS_VMO_CREATE
   - Requests creation of a virtual memory object (VMO) via a factory. The new handle is stored in user-writable memory. Capability FACTORY_CREATE_VMO_CAP must be present.
   #### SYS_CHANNEL_CREATE
   - Asks the factory to produce bidirectional channel endpoints. Returns two handle values referencing peer-connected channel_endpoint objects. Requires FACTORY_CREATE_CHANNEL_CAP.
   #### SYS_CHANNEL_READ
   - Attempts to retrieve a pending message from the associated channel endpoint. Caller must possess CHANNEL_CAP_RECV. The syscall verifies receiver-side buffer, optional handle array, and copies message from kernel space.
   #### SYS_CHANNEL_WRITE
   - Enqueues a message to be sent over a channel endpoint. Requires capability CHANNEL_CAP_SEND. Handles being transferred are verified for OBJECT_CAP_TRANSFER.
   #### SYS_TASK_CREATE
   - Asks a factory to create an empty task object (stub process). Returns a handle with TASK_GET_SPACE_CAP and TRANSFER. Initial state is TASK_CREATED.
   #### SYS_TASK_GET_SPACE
   - Grants the caller access to another task’s virtual memory address space (typically for explicit handle passing or object serialization). Requires handle with TASK_GET_SPACE_CAP.
   #### SYS_VM_MAP_VMO
   - Maps an existing VMO into a task address space with specified offset and permissions.
   #### SYS_VM_FREE
   - Unmaps a virtual address range from a VM space.
   #### SYS_TASK_SPAWN
   - Spawns a previously created task. Initializes the main thread with a provided entry point. Transitions the task’s state from CREATED to SPAWNED.
   #### SYS_OBJECT_CLOSE
   - Releases the given handle in the caller’s object table.
   #### SYS_OBJECT_WAIT_MANY
   - Waits on multiple kernel objects, useful for synchronization/IPC.
   #### SYS_PHYSMAPPER_MAP
   - Maps physical memory ranges for I/O accesses, used by device drivers or MMIO facilities (access controlled based on TA manifest and task capabilities).
   #### SYS_TASK_SHARE_HANDLE
   - Allows handle transfer from one task to another. The handle is written along with an identifier string into a memory area expected by the recipient. Available only when receiver is in CREATED state. Enforced via handle-page layout in receiver’s address context.
   #### SYS_OBJECT_COPY
  - Duplicates a handle within the same task, assigning the requested capability mask. Used to derive restricted-view handles (e.g. remove TRANSFER).

 ## Trusted Application Framework
 - The Trusted Application (TA) Framework provides a lightweight, secure runtime environment and development interface for writing user-mode Trusted Applications atop the Secure OS.
 - It defines a standard C runtime environment enriched with system capabilities accessible via a handle-based capability model.
 - Its primary role is to facilitate secure software development, ensuring alignment with both TEE security policies and performance constraints in constrained environments.
  ### Standard Library for Trusted Applications
   #### Standard Library Overview
   - The standard library is a minimal libc equivalent tailored to the Secure OS TEE context. It provides essential functionality typically found in a standard C runtime, excluding non-secure system calls. Implemented entirely in secure world userspace, the library avoids dynamic linking or unnecessary runtime overhead. It includes:
    - Memory functions (e.g., memcpy, memset)
    - Formatting and I/O (e.g., printf)
    - Math functions (including support for hardware-accelerated routines if available)
    - Cryptographic primitives
    - Concurrent synchronization mechanisms
    - Container utilities (e.g., lists, maps)
    - Typed object and handle access abstraction

  ### Handle Operations Specification
   #### Channel Functions
   - channel_read - Read data from a secure communication channel.
   - channel_write - Send data over a secure communication channel.
   - channel_from_handle - Cast a generic handle into a channel type.
   #### Factory Functions (Fabric Object Handle Interface)
   - factory_init - Prepare a factory object for spawning or object creation.
   - factory_create_vmo - Create a Virtual Memory Object (VMO).
   - factory_channel_create - Create a new communication channel.
   - factory_task_create - Create and launch a new Trusted Application task.
   - factory_get_handle - Retrieve system/manually assigned handles.
   #### Object Functions
   - object_copy - Duplicate a handle reference.
   - object_close - Close and discard a handle.
   #### Task Functions
   - task_spawn - Spawn a new task using a manifest.
   - task_share_handle - Share handle(s) with another task securely.
   #### Memory Management Functions
   - vm_init - Initialize virtual memory structures.
   - vm_map_vmp - Map memory pages into a task's virtual space.
   - vm_free - Free allocated virtual memory regions.
  ### I/O Standard Library Specification
   #### Printf-Compatible Functions
   - printf - Wrapper using tee_log syscall.
   - sprintf - Internal memory-safe string writing variant.
   - vprintf - Variadic-style printf handler.
   #### Logging Function
   - tee_log - Internal secure log syscall (invokes SYS_LOG, tagged output).

  ### Strings Standard Library Specification
   #### String Utility Functions
   - memset
   - memcmp
   - memcpy
   - memmove
   - memchr
   - strlen
   - strchr
   - strcmp
   - strtol
   - These are implemented using size-optimized and alignment-aware techniques for low-overhead TA memory environments.
  ### Math Standard Library Specification
   #### Algebraic Functions
   - sqrt, pow, log, exp, abs, floor, ceil
   #### Trigonometric Functions
   - sin, cos, tan, asin, acos, atan
   #### Mathematical Constants
   - pi, e, inf, nan
   #### Complex Math Functions
   - Complex number support is syntactically mirrored from real-number APIs.
  ### Crypto Standard Library Specification
   #### Hashing Functions
   - sha256(data, len)
   - sha512(data, len)
   - md5(data, len)
   #### Encryption/Decryption Functions
   - in future work support for functionality like:
   - aes_encrypt, aes_decrypt - Support for AES-GCM/CTR if hardware-accelerated
   - chacha20_encrypt, chacha20_decrypt
   #### Key Management and Derivation
   - in future work support for functionality like:
   - hkdf implementation
   - Insecure vs. hardware-sealed key storage distinction
   #### Random Number Generation
   - in future work support for functionality like:
   - crypto_rng - Hardware-backed RNG where available
   - crypto_rng_init_seed - Optional API for seed injection
  ### Container Standard Library Specification
   - Note: Trees are all reentrant and zero-alloc in TA context
   #### List Functions
   - Singly Linked List: Init, Push, Pop, Find, Remove
   - Doubly Linked List: Bidirectional traversal APIs with embedded nodes
   #### Radix Tree Functions
   - Insertion, deletion, lookup optimized for dense ID spaces
   #### WAVL Tree Functions
   - Self-balancing tree, relaxed AVL variant, with logarithmic insert/remove
   #### Red-Black Tree Functions
   - Balanced binary tree implemented using node-color rules
  ### Concurrency Standard Library Specification
   #### Atomic Operations
   - atomic_add_fetch
   - atomic_sub_fetch
   - atomic_or_fetch, atomic_and_fetch
   - atomic_read, atomic_write
   - Memory barrier primitives: smp_rb() (read barrier), smp_wb() (write barrier)
   #### Mutex API
   - mutex_init(), mutex_lock(), mutex_unlock(), mutex_destroy()
   #### Spinlock API
   - spinlock_init(), spin_lock(), spin_unlock(), spin_trylock()
   #### Semaphore API
   - sem_init(), sem_wait(), sem_post(), sem_destroy()
   #### Conditional Variables
   - cond_init(), cond_wait(), cond_signal(), cond_broadcast()
  ### Misc Library Functions Specification
   #### Align Macros
   - align_up(x, a)
   - align_up_ptr(p, a)
   - align_down(x, a)
   - align_down_ptr(p, a)
   - is_aligned(x, a)
   - is_aligned_ptr(p, a)
   #### Bit Manipulation
   - bit32(n), bit64(n)
   - is_power_of_two(x)
   - clz32(x) - Count Leading Zeros (32-bit)
   - clz64(x) - Count Leading Zeros (64-bit)
   - log2(x)
   #### Compiler and Intrinsic Macros
   - barrier() - Compiler-level memory fence
   - container_of(ptr, type, member) - Offset-based typed accessor
   - Standardized __attribute__ usage for alignment/enforced inlining.
   - same_type() - Static type matching check (debug-mode only)

 ## Implementation Challenges and Optimizations
 - This section discusses the practical challenges encountered during the development of the Secure OS and outlines optimizations applied to ensure a balanced trade-off between performance, security, and maintainability.
 - It also examines developer tooling, build considerations, and key lessons learned from implementation.
 - The intent is to provide transparency about the engineering process and to offer insights to future developers working in similar environments.
  ### Performance vs. Security Trade-Offs
   #### Balancing Isolation with Speed
   - Design decisions around compartmentalization, memory isolation, and privilege levels.
   - Trade-offs in choosing monolithic kernel vs microkernel OS
   - Trade-offs in choosing user/kernel boundaries for TAs vs. monolithic kernel TAs.
   - Security isolation for TAs vs. higher communication overhead through system call boundaries.
   #### Inter-World Communication Overhead
   - Overhead from shared region polling, memory copy costs, and IPI-based signaling.
   - Use of lock-free ring queues to reduce latency.
   - Minimizing trap/return paths for better inter-world round-trip latency.
   #### Scalability Limits on a Single-Core Secure OS
   - Implications of limiting Secure OS execution to a single core (core 0).
   - Managing multiple active TAs and long-running calls to maintain responsiveness.
   - Use of concurrent threads within Secure OS vs. thread serialization.
  ### Memory Footprint Optimizations
   #### Static Allocation vs. Dynamic Allocation
   - When and why static memory regions were used (boot sequence, early kernel sections).
   - Justification for dynamic allocation fallback features (slab and page pool management).
   - Minimal boot allocator and on-demand zeroing mechanisms.
   #### Slab Allocator and Page Pool Efficiency
   - Custom lightweight slab allocator optimized for isolated heaps.
   - Fit-to-size classes to reduce fragmentation.
   #### Minimal Kernel Subsystem Design
   - Avoiding traditional bloated kernel designs (e.g., no sysfs, vfs).
   - Core components only: task/thread scheduling, IPC, memory isolation, syscalls.
   - Benefits of small Trusted Computing Base (TCB) in verification and auditability.
  ### Debugging Considerations
   #### Logging from Secure OS
   - Secure and minimalistic logging channel
   - Multiple logging levels (panic, error, info, debug).
   #### Debugging TAs in Isolation
   - tracing
   - remote debugger hooks (gdb)
   #### Instrumentation Techniques
   - Internal counters for scheduling decisions, memory allocations, syscall hit counts.
   - Tracing memory allocator usage (per-task page count or slab lifetime tracking).
   #### Fault Isolation and Crash Analysis
   - Handling invalid syscalls in Secure OS and malformed commands from untrusted Linux driver.
   - Watchdog for runaway tasks and per-task isolation to reduce blast radius.
  ### Build System and Packaging for TAs
   #### Trusted Application Build Flow
   - TA toolchain constraints (compiler hardening in libtacore).
   - Source tree layout that enforces separation of kernel, libraries, and apps.
   - Manifests for capabilities, memory regions, and initial handles.
   - Options for static TA linking into kernel image vs. runtime TA loading.
   - Binary format (e.g., ELF) parsing from kernel for runtime spawning.
   #### Kernel Build System
   - CMake based build system for Secure OS
   #### Development Tooling Support
   - QEMU and hardware launch wrappers (scripts for OpenSBI + Secure OS + Linux images).
   - Secure OS runtime shell commands for debugging tasks and memory maps.
   - Developer stubs and host-side tools for image generation, symbol resolution.
  ### Testing and Validation
   #### Unit Testing Secure OS Components
   - Internal test cases for linked list manipulation, allocator correctness, timer behavior.
   - Framework for checking invariants (vmspace protections, handle tables).
   - Building unit tests into kernel image and controlled via boot parameters.
   #### Integration Testing with Linux
   - End-to-end TEE client interface validation: context creation, open session, invoke command.
   #### Security-Oriented Tests
   - Handle table fuzzing framework (e.g., reusing/releasing invalid handles).
   - Fault injection infrastructure via Linux-side IPI storms, memory overwrites, syscall replay.
  ### Summary of Implementation
   #### Overview
   - Summary of major challenges solved during implementation
   - Design principles that proved effective (e.g., capability model, static memory layout).
   #### Codebase Structure Summary
   - Secure OS code structuring: split into
    - ta (contains trusted applications)
    - kernel (contains arch, lib, mem, sched, sync, tasks, tests)
    - libtee (contains user space library)
    - scripts (contains build scripts, codegeneration scripts, backtrace, etc)
   - Tools and CMake-based build system granularity.
   #### Opportunities for Improvement
   - Feature hardening: memory encryption, exploit mitigations like stack canaries.
   - Potential for multicore support within Secure OS given future WorldGuard changes.
   - Technical debt around early bootloader glue code and MMU bring-up code.

---
