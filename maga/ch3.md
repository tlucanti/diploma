
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

   The chosen subset focuses on `TEEC_InitializeContext`, `TEEC_FinalizeContext`, `TEEC_OpenSession`, `TEEC_CloseSession`, `TEEC_InvokeCommand`, `TEEC_AllocateSharedMemory`, and `TEEC_ReleaseSharedMemory`, providing the foundational blocks for secure communication and computation. This selection allows for the development and execution of TAs while minimizing the interface exposed by the Secure OS.

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
   *   Secure World (Secure OS):
   - Provides an isolated execution environment for Trusted Applications (TAs).
   - Manages secure system resources, such as cryptography hardware or protected memory regions.
   - Enforces the capability-based security model, where TAs operate using handles granted to them via a manifest by a root task, dictating their permissible actions and resource access.
   - Handles sensitive operations and services requested by the Normal World through a well-defined interface.

   *   Normal World (Linux):
   - Executes general-purpose applications and manages untrusted system resources.
   - Interacts with the Secure World exclusively through a predefined communication
           interface (based on a subset of the Global Platform API) to request secure services.
   - Cannot directly access memory or resources belonging to the Secure World unless explicitly permitted and mediated by the Secure OS.

   Boundary enforcement is achieved through a combination of hardware and software mechanisms:
   *   The RISC-V World Guard extension provides hardware-enforced isolation, preventing the Normal World from directly accessing memory regions or peripherals assigned to the Secure World.
   *   Inter-world communication is strictly managed through dedicated shared memory queues for requests and responses, along with Inter-Processor Interrupts (IPIs) for signaling. This controlled channel ensures that all interactions are explicit and auditable.

  ### Core System Components
   #### Kernel, Resource Managers, and TEE Services
   - Details the internal architecture of the Secure OS, covering the Secure Kernel, resource managers (for tasks, memory, and IPC), and TEE service layers.
   - Describes how these components collectively provide security, resource allocation, and runtime services to Trusted Applications.
   #### Shared Memory and IPI-Based Communication
   - Introduces the fundamental inter-world communication channels, such as shared rings/buffers used for request and response queues.
   - Describes how RISC-V inter-processor interrupts (IPIs) are employed for signaling events and synchronizing data transfer between Normal and Secure Worlds.
  ### Memory Layout and Addressing
   #### Physical and Virtual Addressing
   - Provides a high-level overview of how the Secure OS configures its page tables and manages physical/virtual addresses.
   - Explains how memory mappings differ between the Secure World and the Normal World.
   #### Isolation Mechanisms
   - Details how World Guard extension enforces secure boundaries at the hardware level.
   - Shows how the Secure and Normal Worlds remain isolated, preventing unauthorized access to protected pages.
   #### Shared Memory Queues
   - Explains the reserved memory regions that serve as shared buffers for secure–normal communication.
   - Highlights concurrency concerns and locking strategies for ring-buffer manipulation.
  ### Secure OS Execution Flow
   #### Boot Process Overview
   - Summarizes the critical steps in transitioning from OpenSBI to the Secure OS, and eventually handing over the remaining cores to Linux.
   - Points to more detailed discussion in the “Secure Boot Process and Initialization” section.
   #### Inter-World Transitions
   - Outlines the mechanism by which execution moves between Secure and Normal Worlds (e.g., SMC calls, interrupts).
   - Covers validation checks before granting world transitions and how the OS ensures secure state persistence.
   #### Scheduling in Secure OS
   - Highlights how the Secure OS manages tasks and threads in a uniprocessor environment (the first core).
   - Discusses scheduling policies, context switching logic, and how TEE tasks do not interfere with Linux scheduling.
  ### Security and Policy Enforcement
   #### Capability-Based Security Model
   - Introduces the core concepts behind object handles, secure syscalls, and fine-grained access control.
   - Explains how capabilities are validated and enforced at runtime to prevent privilege escalation.
   #### World Guard Integration
   - Consolidates the hardware-based checks provided by the World Guard extension with the Secure OS’s software policy.
   - Provides an overview of failure handling when unauthorized accesses or invalid world transitions occur.
  ### TA Lifecycle
   #### Creation
   - Describes how Trusted Applications (TAs) are registered or loaded by the Secure OS.
   - Explores memory allocation, initial code setup, and the procedure for spawning a TA process or thread.
   #### Compute
   - Outlines how a TA executes in the Secure OS, including interaction with system calls, access to resources, and concurrency.
   - Discusses how TAs can communicate with other tasks or the Normal World during their operational phases.
   #### Teardown
   - Explains the orderly shutdown of a TA, covering handle cleanup, memory deallocation, and final status reporting.
   - Ensures that no sensitive data remains accessible and that the system reclaims all resources.

 ## WorldGuard Integration
  ### WorldGuard Configuration
   #### World Configuration (Two-World Model)
   - Overview of how the system hardware and memory are split between Secure World and Normal World.
   - Explanation of the two-world design rationale, focusing on isolation guarantees.
   - Definition of the roles of each world (e.g., Secure OS vs. Linux).
   - Description of how World IDs (or similar identifiers) are assigned and managed.
   #### WorldGuard Checker Configuration for Secure Isolation
   - Overview of the hardware/software checker mechanism for enforcing world-based isolation.
   - Configuration of Secure RAM slots and memory regions:
     - Secure memory partitioning approach.
     - Locking down memory regions to the Secure World
   - Setting up enclave/partition boundaries:
     - Handling multiple enclaves (if applicable) within the Secure World.
     - Policy for controlling access across enclaves or from Normal World.
   - Integration of memory attributes (e.g., read/write/exec permissions) with WorldGuard checks.
  ### Integration with the Secure OS
   #### Error Reporting
   - Mechanisms to detect and report WorldGuard-related violations (e.g., unauthorized access attempts).
   - Logging and reporting structure within the Secure OS for debugging and auditing.
   - strategies for halting offending tasks in case of critical errors.
   #### Managing World Transitions
   - Description of the control flow when switching between Normal World and Secure World.
   - Handling interrupt-driven transitions across worlds.
   - Use of specific CPU instructions or registers to invoke transitions (if applicable).
   - Ensuring minimal overhead while maintaining security guarantees.
   #### Communication Pages
   - Shared memory pages allocated with permissions for both worlds:
     - Shared memory region layout and alignment considerations.
     - Ensuring read/write restrictions are enforced by WorldGuard.

 ## Secure Boot Process and Initialization
 - This section describes how the Secure OS is bootstrapped, transitioning from platform firmware (OpenSBI) to a fully initialized secure environment.
 - It covers early assembly-level initialization, kernel relocation, MMU enablement, and higher-level subsystem initialization, ultimately concluding with the handover to any “rich OS” components.
  ### Secure OS Early Initialization
   #### OpenSBI Handover
   - Explanation of the OpenSBI boot protocol, which provides the Secure OS with the initial register context (e.g., a0, a1 containing specific parameters).
   - SBI boots FW_PAYLOAD_PATH (TEEOS futher) on boot core, making this core secure
   - High-level overview of how the Secure OS entry point (_start) is invoked by OpenSBI.
   - Handling or storing system parameters (such as the device tree pointer) for further use.
   #### Setting Up the Stack and Basic Memory Layout
   - Allocating a stack in physical memory for secure execution.
   - How the assembly code (head.S) calculates the stack location (via PAGE_SIZE * 6).
   - Ensuring stack alignment for correct RISC-V operation.
   #### First Kernel Relocation
   - performing a “relocation” step due to pie (position-independent executable) nuances.
   - Creating an identity mapping (physical == virtual) at the kernel load address while also mapping the kernel at its designated virtual base (KERNEL_VIRTUAL_BASE).
   - Use of large page mappings (e.g., 2MB or 1GB mappings) for simplicity during early boot.
   #### Enabling the MMU
   - Explanation of how the SATP register is configured
   - Ensuring the kernel text, data, and bss segments are accessible at both the physical region and the kernel virtual address.
  ### Secure OS Initialization
  - Once the minimal MMU and basic mapping are established, the Secure OS transitions to its primary C environment for final setup.
   #### Register Console
   - Initializing and registering the console driver (e.g., SBI console) as the primary I/O channel.
   - Setting up early debug/log printing to assist with error reporting.
   #### Initialize Page Tables
   - Creation and configuration of more granular page tables beyond the initial large block mappings.
   - Structures for dynamic region registration and page-level protections.
   #### Second Kernel Relocation (If Needed)
   - Further re-mapping kernel virtual addresses after early-boot.
   - Cleanup of temporary mappings used during the first relocation phase.
   #### Initialize Trap Handler
   - Setting up the vector table or exception table to handle synchronous exceptions and interrupts.
   - Registering fault handlers, system call handlers, and other critical exception vectors.
   #### Initialize Timers
   - Configuring RISC-V timer CSRs or platform-specific timer hardware.
   - Setting up the early tick or scheduling timers.
   #### Initialize Page Allocator
   - Creation of a physical page allocator (pmm_init()) to manage secure RAM.
   - Data structures (e.g., contiguous free-lists, bitmaps) for tracking page usage.
   #### Initialize Slab Allocator
   - A higher-level memory allocator (kmalloc or slab-based).
   - Allocation of kernel objects (e.g., tasks, threads, pipes) efficiently.
   #### Initialize Scheduler
   - Setup of the scheduler data structures to manage secure OS threads or tasks.
   - Timer-driven scheduler hooks using the timer subsystem.
   #### Initialize Root Task
   - Creation of the root task (or initial user-mode process in the Secure World).
   - Loading or spawning any essential system services.
   #### Initialize Normal World Communication Channel
   - Setting up shared memory regions or queues for Normal World <-> Secure World communication.
   - Configuring interrupt mechanisms or other signaling channels (e.g., IPI).
   #### Initialize Trusted Applications
   - Loading and initializing built-in or pre-installed Trusted Applications (TAs).
   - Setting up an environment for TAs, including memory isolation, scheduling, and system call interfaces.
 ### Rich OS Initialization
  #### Initialization by OpenSBI
   - Handing control back to OpenSBI to continue its normal boot flow for a Linux or other rich OS.
   - TEEOS setups itself and does special ecall that indicates that it has finished
   - SBI boots NWD_FW_PAYLOAD_PATH (REEOS futher) on other cpus
  #### Core Startup
   - after returing to sbi on secure core - sbi will start second non secure core
   - second core will start Linux Kernel, and Linux will hotplug other cores by itself
   - Linux will not try to run on first secure core, because it was marked "secure" at the begining of OpenSBI startup

 ## OpenSBI modifications
  ### ...

 ## Cross-World Communication
 - This chapter describes the mechanisms enabling data exchange and signaling between the Secure OS running on the primary CPU core(s) and the Normal World (e.g., Linux). It focuses on the shared memory queues, the message structure used for TEE commands, and the IPI mechanism for sending interrupts across RISC-V cores.
  ### Shared Memory Queues
   - One of the fundamental mechanisms for communication between the Secure World (SWd) and Normal World (NWd) is through shared memory queues. This approach allows concurrent message passing without requiring complex locking operations.
   #### Lock-Free Queue Algorithm
   - *https://pskrgag.github.io/post/mpmc_vuykov/*
   #### Shared Memory Ring Buffers
   - Overview of how the queues are physically placed in shared memory pages accessible to both SWd and NWd.
   - Ring buffer layout: circular array of message slots, head/tail pointers, and optional “sequence” fields for synchronization.
   - Memory alignment considerations for preventing false sharing or alignment-related issues.
   #### Requests Queue
   - A dedicated ring buffer where the Normal World places requests that the Secure World must handle.
   - Steps for enqueuing:
     1. Normal World driver writes the message into the ring slot.
     2. Driver updates the queue head pointer using an atomic operation.
     3. IPI sent (or polling mechanism invoked) to notify Secure World.
   #### Responses Queue
   - A separate ring buffer for the Secure World to provide responses or event notifications back to the Normal World.
   - The Secure World writes its response into the ring slot, increments the tail pointer, and relies on NWd polling.
   #### Canary Around Shared Pages
   - Canary pages are placed around Shared pages with no access bits, so any access by overflowing will trap
  ### Shared Memory Regions
  - Aside from the primary queues, certain larger buffers or data structures may be shared.
   #### Memory Region Allocation
   - allocation is done by calling secure operation TEE_CMD_ID_MAP_SHARED_MEM
   - allocation is done in Secure World, it will allocate pages and set access to Secure world and normal world
   - then Secure OS will map pages to Secure Kernel address space to be able to access them
   - them Linux should map these pages to Linux Kernel address space
   #### Memory Region Deallocation
   - deallocation is done by calling secure operation TEE_CMD_ID_UNMAP_SHARED_MEM
   - Secure World will deallocate pages, and remove access from both Secure world and Normal world
   - them Secure os will unmap pages from Secure Kernel address space
   - then Linux should unmap pages from Linux Kernel address space
   #### Data transfer
   - since memory is mapped to Linux Kernel and Secure OS, Operating Systems can transfer data just by regular memory reads and writes
  ### Message Structure
  - All commands passed through the request/response queues typically adhere to a consistent message format. This section details the wg_tee_cmd structure, which encapsulates TEE operation parameters and results.
   #### struct wg_tee_cmd
   This structure holds command identifiers, session tracking, error codes, and additional parameters.
   #### field id
   - uint32_t id
   - Identifies the type of TEE operation.
   - Possible values include:
     - TEE_CMD_ID_OPEN_SESSION
     - TEE_CMD_ID_CLOSE_SESSION
     - TEE_CMD_ID_INVOKE_CMD
     - TEE_CMD_ID_MAP_SHARED_MEM
     - TEE_CMD_ID_UNMAP_SHARED_MEM
   #### field seq
   - uint32_t seq
   - filed seq is a unique identifier of command
   - it's value is generated just by atomically incremented sequence counter
   #### field session_id
   - uint32_t session_id
   - Identifies which session within a TA this command belongs to.
   - Allows a single TA to manage multiple open sessions simultaneously.
   #### field func_i
   - uint32_t func_id
   - each Trusted Application implements it's own functionality, and TA can do multiple actions
   - field func_id describes what action to do inside TA
   #### field err
   - uint32_t err
   - Used by the Secure World to return error codes or status results.
   - possible results include indicating success, permission failures, or other errors.
   #### field uuid
   - uint8_t uuid[16]
   - A unique identifier for the Trusted Application.
   - Used during TEE_CMD_ID_OPEN_SESSION to select the correct TA.
   #### field paddr
   - uint64_t paddr
   - A physical address relevant to TEE_CMD_ID_MAP_SHARED_MEM; indicates the start page to map as shared.
   - field remain unused for other command IDs.
   #### field num_pages
   - uint32_t num_pages
   - The number of contiguous pages to map starting at paddr, for TEE_CMD_ID_MAP_SHARED_MEM.
   - field remain unused for other command IDs.
   #### field shmem_id
   - uint32_t shmem_id
   - A handle returned by the Secure OS to reference a mapped shared memory region.
   - Allows subsequent TEE_CMD_ID_UNMAP_SHARED_MEM to unmap region
   #### struct wg_param params
   - Holds 4 arguments (each is 24 bytes).
   - Simple arguments are stored directly
   - memory references are stored as three 64-bit values (size, offset, world_id).
   #### padding
   - field padding has size of 96 bytes
   - Reserved space to align the structure to 256 bytes overall.
   - Prevents unwanted compiler padding from interfering with the queue alignment.
  ### IPI Based Signaling
  - While the shared queues provide a data structure for messages, an Inter-Processor Interrupt (IPI) mechanism triggers real-time notifications.
   #### RISC-V IPI Mechanism
   - High-level overview of the RISC-V interrupt controller and how software sets an IPI to a target hart.
   - Explanation of relevant CSRs, memory-mapped interrupt lines, or OpenSBI calls for sending IPIs.
   - Typical flows: setting a bit in the IPI register or invoking sbi_send_ipi with a hart mask.
   #### Normal to Secure World Signaling
   - Procedure in which the Linux driver or NWd service:
     1. Fills out wg_tee_cmd struct
     2. push struct in the request queue.
     3. Triggers an IPI to the secure hart via an OpenSBI call.
     4. Waits for response by polling the response queue
   #### Secure to Normal World Signaling
   - Due to the RISC-V architecture constraints, the simplest approach is for the Secure OS to place responses in the response queue without any other signaling of Normal World
   - An IPI back is restricted because of limitations of RISC-V ISA - we can not distinguish Secure OS notification IPI from other types of IPI, so Linux will not be able to handle IPI correctly
   - so the NWd driver periodically checks the response queue
   - The requesting thread is then woken, a result is available.

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

 ## Linux Driver Implementation
 - This section details the design and implementation of the Linux driver responsible for communication with the Secure OS.
 - The driver uses the kernel's TEE subsystem interfaces to expose the Secure OS functionality to user-space applications.
 - It establishes shared queues for request and response messages, initializes kernel threads for communication polling, handles incoming replies, and provides TEE-driver–compliant operations such as open session, close session, and invoke command.
  ### Driver Overview and Registration
  - Before diving into the shared queues and communication routines, the driver must be discoverable by the Linux kernel and properly registered within the TEE subsystem:
   #### Linux Driver Initialization
   1. The device tree node "riscv-wg/nwd_channel" is parsed to read the physical addresses of the shared request and response queues (SQ and CQ).
   2. Memory for the driver control structure (struct wgtee) is allocated.
   3. Shared queues are remapped into kernel space (ioremap) and initialized with the lock-free MPMC queue mechanism.
   4. A TEE device (struct tee_device) is allocated and registered using tee_device_alloc() and tee_device_register().
   5. The driver registers a set of callbacks (wgtee_ops), including open_session, invoke_func, etc., which allow user space to interact with the Secure OS through the standard TEE_IOCTL API.
   - Key driver entry points:
    - module_init(wgtee_driver_init) — For device instantiation and registration.
    - module_exit(wgtee_driver_exit) — For cleanup and teardown.
   #### Linux Driver Interface
   - The Linux driver implements TEE-driver–compliant operations exposed via wgtee_ops:
    - get_version() — Returns the TEE driver version (implementation ID and capabilities).
    - open() / release() — Allocate or free per-context data (in wg_user_context).
    - open_session() — Handle TEE_CMD_ID_OPEN_SESSION.
    - close_session() — (Currently returns -ENODEV as a placeholder).
    - invoke_func() — Handle TEE_CMD_ID_INVOKE_CMD, forwarding parameters to the Secure OS.
    - cancel_req() — Not currently implemented.
   - To accommodate the TEE subsystem’s generic parameter structures (struct tee_param), the driver provides helper routines:
    - wg_convert_params_in() — Converts Linux TEE parameters into wg_param structures.
    - wg_convert_params_out() — Converts results back into Linux TEE param outputs.
  ### Shared Queues from the Linux Side
  - Shared memory queues form the primary communication channel between the Normal World (Linux) and the Secure World (Secure OS). There are two distinct types of queues in use:
   #### Requests Queue
   - The Requests Queue (SQ - Submission Queue) holds commands that the Normal World wishes to send to the Secure OS. For instance, when a user space application issues a TEE_IOCTL command (such as open session or invoke function), that request is packaged into a wgtee_cmd structure and placed into this queue.
   - The queue is initialized via wg_communication_init().
   - The driver uses mpmc_queue_push() to insert a command (wgtee_cmd) onto the queue.
   - Each command is tagged with a unique sequence number (seq) to match responses.
   #### Responses Queue
   - The Responses Queue (CQ - Completion Queue) collects asynchronous responses sent back by the Secure OS. Whenever the Secure OS finishes handling a command from the SQ, it places a completed wgtee_cmd structure, including any output parameters or errors, onto the CQ.
   - The driver polls this queue in a dedicated kernel thread.
   - The mpmc_queue_pop() routine removes the next response command.
   - The driver matches responses to ongoing requests by seq number.
   ### Linux Communication Interface
   - Communication with the Secure OS involves several key steps: initialization, creating the polling thread, enqueueing commands, waiting for replies, and finalizing when the system is shut down or the module is removed.
   #### Communication Initialization
   - The wg_communication_init() routine is responsible for:
   1. Mapping the physical memory for the CQ and SQ into kernel virtual addresses (ioremap).
   2. Initializing both mpmc queue data structures with mpmc_queue_init().
   3. Starting a dedicated kernel thread (polling_thread) that continuously checks for completed commands in the CQ.
   #### Queue Initialization
   - Each queue (SQ and CQ) is implemented using the lock-free MPMC (Multiple Producer Multiple Consumer) circular queue:
    - Memory layout is backed by a contiguous region (one page for SQ, one page for CQ in the current setup).
    - mpmc_queue_init() sets up the ring buffer indices (head and tail) and ensures alignment.
    - ioremap_prot() is used to obtain a kernel virtual address for these pages.
   #### Communication Polling kthread
   - A single kernel thread (wg_polling_thread) handles responses from the Secure OS by:
   1. Checking the CQ queue for any ready responses.
   2. Matching each retrieved response to a waiting request via the seq field.
   3. Signaling the appropriate completion object (struct completion) so the requesting context can proceed.
   - The thread runs until the driver is unloaded or the system is halted.
   #### Message Sending
   - When a Normal World request is issued to the Secure OS (e.g., open session, invoke command, or close session):
   1. The driver constructs a wgtee_cmd structure, populating fields such as id, func_id, parameters, etc.
   2. A unique sequence number is generated with atomic_fetch_inc(&seq_number).
   3. The request is placed into the SQ using wg_queue_push().
   4. An IPI (sbi_send_ipi) is dispatched to wake up the Secure OS core.
   #### Getting the Result
   - Each inflight request has an associated completion entry (wg_completion_entry). The list of waiting requests is protected by a spinlock (waiting_lock). When the Secure OS writes a response onto the CQ:
   1. The polling thread pops it from the CQ.
   2. The polling thread scans the waiting_requests list for a matching seq.
   3. Once found, it copies fields into the original wgtee_cmd, calls complete() on the associated completion, and removes it from the waiting list.
   #### Communication Finalization
   - During driver removal (module_exit) or general teardown:
   1. The polling thread is stopped (kthread_stop).
   2. Mapped I/O memory for both queues is unmapped (iounmap).
   3. The TEE device is unregistered, and any allocated kernel structures are freed.

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
  - Механизм управления задачами (Task Management) в Secure OS определяет систему, в рамках которой задачи создаются, запускаются и завершаются.
   - В коде ядра представлены несколько ключевых подсистем, реализующих данный функционал.
   #### Process Model
   - Процессная (task) модель предполагает, что каждая задача имеет собственное адресное пространство и набор ресурсов, зарегистрированных в ядре.
   - Создание задачи обычно происходит по запросу пользовательского процесса либо при создании сессии для новой TA, через системный вызов (task_create). Перед запуском задачи ядро выделяет нужные структуры данных, инициализирует объект задачи и подключает его к планировщику. При этом задача находится в состоянии TASK_CREATED, пока не будет вызвана функция task_spawn, переводящая её в состояние TASK_SPAWNED.
   #### IPC Service
   - В системе используется механизм IPC на основе каналов (channels). Каждая задача может получить дескрипторы двух сторон канала, позволящие выполнять операции чтения/записи (channel_read()/channel_send()).
   - Кроме того, для организации группового ожидания сообщений служит вызов wait_object_many, позволяющий одним системным вызовом ожидать события от нескольких объектов.
   - Пример кода root_task демонстрирует задачу, которая ожидает сообщения в канале kernel_channel. При появлении нового сообщения конструкция wait_object_many(...) возвращает события от одного или нескольких объектов.
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
  ### Handles as Encapsulated Capabilities
  - Handles in the Secure OS function as references to system resources (objects). Each handle has associated permissions and metadata defining how it may be accessed or manipulated. Internally, handles map to kernel-managed descriptors that maintain the state, permission bits, and relevant object pointers.
   #### Design Rationale
   - Least Privilege Principle: Capabilities ensure that tasks and trusted applications only have the minimum set of privileges needed.
   - Fine-Grained Access Control: Provides precise control over which resources can be accessed and how they are used.
   - Composability: The handle-based model allows different system components (tasks, services, etc.) to dynamically create and share capabilities in a structured manner.
   #### Objects
   - Definition: Objects represent protected resources (e.g., memory regions, tasks, communication channels).
   - Creation: created by a specialized factory object or created initally by kernel
   - Management: The kernel and corresponding resource managers maintain object lifecycles (allocation, reference counting, destruction).
   #### Object Handles
   - Semantics: An object handle is an token referencing an underlying object.
   - Handle Table: Each task or trusted application maintains a handle table
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
   For example, in the `channel_write` syscall, the following enforcement occurs:
   1. Validate caller owns the provided handle with `CHANNEL_CAP_SEND`.
   2. Validate all message-passed handles include the `TRANSFER` capability.
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
   - Requests creation of a virtual memory object (VMO) via a factory. The new handle is stored in user-writable memory. Capability `FACTORY_CREATE_VMO_CAP` must be present.
   #### SYS_CHANNEL_CREATE
   - Asks the factory to produce bidirectional channel endpoints. Returns two handle values referencing peer-connected `channel_endpoint` objects. Requires `FACTORY_CREATE_CHANNEL_CAP`.
   #### SYS_CHANNEL_READ
   - Attempts to retrieve a pending message from the associated channel endpoint. Caller must possess `CHANNEL_CAP_RECV`. The syscall verifies receiver-side buffer, optional handle array, and copies message from kernel space.
   #### SYS_CHANNEL_WRITE
   - Enqueues a message to be sent over a channel endpoint. Requires capability `CHANNEL_CAP_SEND`. Handles being transferred are verified for `OBJECT_CAP_TRANSFER`.
   #### SYS_TASK_CREATE
   - Asks a factory to create an empty task object (stub process). Returns a handle with `TASK_GET_SPACE_CAP` and `TRANSFER`. Initial state is `TASK_CREATED`.
   #### SYS_TASK_GET_SPACE
   - Grants the caller access to another task’s virtual memory address space (typically for explicit handle passing or object serialization). Requires handle with `TASK_GET_SPACE_CAP`.
   #### SYS_VM_MAP_VMO
   - Maps an existing VMO into a task address space with specified offset and permissions.
   #### SYS_VM_FREE
   - Unmaps a virtual address range from a VM space.
   #### SYS_TASK_SPAWN
   - Spawns a previously created task. Initializes the main thread with a provided entry point. Transitions the task’s state from `CREATED` to `SPAWNED`.
   #### SYS_OBJECT_CLOSE
   - Releases the given handle in the caller’s object table.
   #### SYS_OBJECT_WAIT_MANY
   - Waits on multiple kernel objects, useful for synchronization/IPC.
   #### SYS_PHYSMAPPER_MAP
   - Maps physical memory ranges for I/O accesses, used by device drivers or MMIO facilities (access controlled based on TA manifest and task capabilities).
   #### SYS_TASK_SHARE_HANDLE
   - Allows handle transfer from one task to another. The handle is written along with an identifier string into a memory area expected by the recipient. Available only when receiver is in `CREATED` state. Enforced via handle-page layout in receiver’s address context.
   #### SYS_OBJECT_COPY
  - Duplicates a handle within the same task, assigning the requested capability mask. Used to derive restricted-view handles (e.g. remove `TRANSFER`).

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
   - `channel_read` - Read data from a secure communication channel.
   - `channel_write` - Send data over a secure communication channel.
   - `channel_from_handle` - Cast a generic handle into a channel type.
   #### Factory Functions (Fabric Object Handle Interface)
   - `factory_init` - Prepare a factory object for spawning or object creation.
   - `factory_create_vmo` - Create a Virtual Memory Object (VMO).
   - `factory_channel_create` - Create a new communication channel.
   - `factory_task_create` - Create and launch a new Trusted Application task.
   - `factory_get_handle` - Retrieve system/manually assigned handles.
   #### Object Functions
   - `object_copy` - Duplicate a handle reference.
   - `object_close` - Close and discard a handle.
   #### Task Functions
   - `task_spawn` - Spawn a new task using a manifest.
   - `task_share_handle` - Share handle(s) with another task securely.
   #### Memory Management Functions
   - `vm_init` - Initialize virtual memory structures.
   - `vm_map_vmp` - Map memory pages into a task's virtual space.
   - `vm_free` - Free allocated virtual memory regions.
  ### I/O Standard Library Specification
   #### Printf-Compatible Functions
   - `printf` - Wrapper using `tee_log` syscall.
   - `sprintf` - Internal memory-safe string writing variant.
   - `vprintf` - Variadic-style printf handler.
   #### Logging Function
   - `tee_log` - Internal secure log syscall (invokes `SYS_LOG`, tagged output).
  ### Strings Standard Library Specification
   #### String Utility Functions
   - `memset`
   - `memcmp`
   - `memcpy`
   - `memmove`
   - `memchr`
   - `strlen`
   - `strchr`
   - `strcmp`
   - `strtol`
   - These are implemented using size-optimized and alignment-aware techniques for low-overhead TA memory environments.
  ### Math Standard Library Specification
   #### Algebraic Functions
   - `sqrt`, `pow`, `log`, `exp`, `abs`, `floor`, `ceil`
   #### Trigonometric Functions
   - `sin`, `cos`, `tan`, `asin`, `acos`, `atan`
   #### Mathematical Constants
   - `pi`, `e`, `inf`, `nan`
   #### Complex Math Functions
   - Complex number support is syntactically mirrored from real-number APIs.
  ### Crypto Standard Library Specification
   #### Hashing Functions
   - `sha256(data, len)`
   - `sha512(data, len)`
   - `md5(data, len)`
   #### Encryption/Decryption Functions
   - in future work support for functionality like:
   - `aes_encrypt`, `aes_decrypt` - Support for AES-GCM/CTR if hardware-accelerated
   - `chacha20_encrypt`, `chacha20_decrypt`
   #### Key Management and Derivation
   - in future work support for functionality like:
   - `hkdf` implementation
   - Insecure vs. hardware-sealed key storage distinction
   #### Random Number Generation
   - in future work support for functionality like:
   - `crypto_rng` - Hardware-backed RNG where available
   - `crypto_rng_init_seed` - Optional API for seed injection
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
   - `atomic_add_fetch`
   - `atomic_sub_fetch`
   - `atomic_or_fetch`, `atomic_and_fetch`
   - `atomic_read`, `atomic_write`
   - Memory barrier primitives: `smp_rb()` (read barrier), `smp_wb()` (write barrier)
   #### Mutex API
   - `mutex_init()`, `mutex_lock()`, `mutex_unlock()`, `mutex_destroy()`
   #### Spinlock API
   - `spinlock_init()`, `spin_lock()`, `spin_unlock()`, `spin_trylock()`
   #### Semaphore API
   - `sem_init()`, `sem_wait()`, `sem_post()`, `sem_destroy()`
   #### Conditional Variables
   - `cond_init()`, `cond_wait()`, `cond_signal()`, `cond_broadcast()`
  ### Misc Library Functions Specification
   #### Align Macros
   - `align_up(x, a)`
   - `align_up_ptr(p, a)`
   - `align_down(x, a)`
   - `align_down_ptr(p, a)`
   - `is_aligned(x, a)`
   - `is_aligned_ptr(p, a)`
   #### Bit Manipulation
   - `bit32(n)`, `bit64(n)`
   - `is_power_of_two(x)`
   - `clz32(x)` - Count Leading Zeros (32-bit)
   - `clz64(x)` - Count Leading Zeros (64-bit)
   - `log2(x)`
   #### Compiler and Intrinsic Macros
   - `barrier()` - Compiler-level memory fence
   - `container_of(ptr, type, member)` - Offset-based typed accessor
   - Standardized `__attribute__` usage for alignment/enforced inlining.
   - `same_type()` - Static type matching check (debug-mode only)

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
