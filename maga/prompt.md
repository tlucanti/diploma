I am doing a project with 3 parts:
 1. Secure OS for RISC-V World Guard extension.
 2. Linux driver for communication with Secure OS.
 3. OpenSBI modification to support World Guard extension.

Secure OS is a monolith OS with capability based model, so the idea is that everething is a handle, all handles (that are listed at predefined Manifest) are given by root task to Trusted Application when it spawned. Creation of objects are done with fabric object handle. Every action to handle is checked with capability model and granted or denied.
Secure OS always works on first cpu core, other cores are left for Linux. Communication between Linux and Secure OS is provided using two shared pages. One page for requests (to secure OS) queue, second page for responses queue. It uses subset of Global Platform API as interface for communications.

I need to write Master's thesis abort part with Secure OS.
It should have 4 chapters:

# Chapter 1: Foundations and Motivation for an Open Secure OS on RISC-V
 ## Background and Motivation
 ## Problem Statement
 ## Relevance and Applications
 ## Comparison with Existing Architectures
 ## Related Work
# Chapter 2. Core Principles of Trusted Execution Environment and Threat Model
 ## TEE Overview
 ## Threat Model
 ## World Guard Extension
 ## Boot Sequence and Chain of Trust
# Chapter 3: Design and Implementation of the Secure Operating System
 ## Interface Considerations
 ## System Architecture Overview
 ## WorldGuard Integration
 ## Secure Boot Process and Initialization
 ## OpenSBI modifications
 ## Cross-World Communication
 ## TEE API
 ## Linux Driver Implementation
 ## Secure Kernel Design
 ## Capability-Based Security Model
 ## Secure Syscalls
 ## Trusted Application Framework
 ## Implementation Challenges and Optimizations
 ## Summary of Implementation
# Chapter 4: Evaluation and Security Analysis
 ## Software Stack Setup
 ## Demonstration of Secure OS Functionality
 ## Security Analysis
 ## Performance Evaluation
 ## Conclusions
 ## Future Work
# References
# Appendices
## Sample TA Code
## TA Manifests
## Secure OS Code
## Secure Standard Library Code

So, 3nd chapter is about Design and Implementation of the Secure Operating System
I have a draft of chapter 3:

# Chapter 3: Design and Implementation of the Secure Operating System
 ## Interface Considerations
  ### TEE Client API: Inter-World Communication Interface
   #### OP-TEE on RISC-V
   #### Develop own minimal GlobalPlatform TEE interface
   #### Experemental of Research Prototypes
   #### Rationale for Adopting a Global Platform-based API Subset
 ## System Architecture Overview
  ### High-Level Architecture
   #### Architectural Layers
   #### Secure vs. Normal World Overview
  ### Core System Components
   #### Kernel, Resource Managers, and TEE Services
   #### Shared Memory and IPI-Based Communication
  ### Memory Layout and Addressing
   #### Physical and Virtual Addressing
   #### Isolation Mechanisms
   #### Shared Memory Queues
  ### Secure OS Execution Flow
   #### Boot Process Overview
   #### Inter-World Transitions
   #### Scheduling in Secure OS
  ### Security and Policy Enforcement
   #### Capability-Based Security Model
   #### World Guard Integration
  ### TA Lifecycle
   #### Creation
   #### Compute
   #### Teardown
 ## WorldGuard Integration
  ### WorldGuard Configuration
   #### World Configuration (Two-World Model)
   #### WorldGuard Checker Configuration for Secure Isolation
  ### Integration with the Secure OS
   #### Error Reporting
   #### Managing World Transitions
   #### Communication Pages
 ## Secure Boot Process and Initialization
  ### Secure OS Early Initialization
   #### OpenSBI Handover
   #### Setting Up the Stack and Basic Memory Layout
   #### First Kernel Relocation
   #### Enabling the MMU
  ### Secure OS Initialization
   #### Register Console
   #### Initialize Page Tables
   #### Second Kernel Relocation (If Needed)
   #### Initialize Trap Handler
   #### Initialize Timers
   #### Initialize Page Allocator
   #### Initialize Slab Allocator
   #### Initialize Scheduler
   #### Initialize Root Task
   #### Initialize Normal World Communication Channel
   #### Initialize Trusted Applications
 ### Rich OS Initialization
  #### Initialization by OpenSBI
  #### Core Startup
 ## OpenSBI modifications
  ### ...
 ## Cross-World Communication
  ### Shared Memory Queues
   #### Lock-Free Queue Algorithm
   #### Shared Memory Ring Buffers
   #### Requests Queue
   #### Responses Queue
   #### Canary Around Shared Pages
  ### Shared Memory Regions
   #### Memory Region Allocation
   #### Memory Region Deallocation
   #### Data transfer
  ### Message Structure
  ### IPI Based Signaling
   #### RISC-V IPI Mechanism
   #### Normal to Secure World Signaling
   #### Secure to Normal World Signaling
 ## TEE API
  ### Global Platform API
   #### Introduction to Global Platform API
  ### TEE Client API
   #### TEE Contexts
   #### TEE Sessions
   #### TEE Shared Memory
  ### TEE API Specification
 ## Linux Driver Implementation
  ### Driver Overview and Registration
   #### Linux Driver Initialization
   #### Linux Driver Interface
  ### Shared Queues from the Linux Side
   #### Requests Queue
   #### Responses Queue
   ### Linux Communication Interface
   #### Communication Initialization
   #### Queue Initialization
   #### Communication Polling kthread
   #### Message Sending
   #### Getting the Result
   #### Communication Finalization
 ## Дизайн и реализация ядра Secure OS
  ### Kernel Objects and Handles
   #### Tasks (Processes)
   #### Threads
   #### Pipes (или Channels)
   #### Virtual Memory Objects
   #### Synchronization Primitives
  ### Task Management
   #### Process Model
   #### IPC Service
   #### Root Task
  ### Scheduling
   #### Scheduling Service
   #### Scheduling Policies
  ### Memory Management Subsystem
   #### Secure Memory Allocator
   #### Memory Isolation
  ### File System
   #### linear RAM fs
   #### elf files
 ## Capability-Based Security Model
  ### Handles as Encapsulated Capabilities
   #### Design Rationale
   #### Objects
   #### Object Handles
   #### Factory Objects
   #### Object Methods
  ### Capability-Based Access Control
   #### Permissions
   #### Task Manifests
   #### Root Task
   #### Method Invocation
   #### Performance Implications
 ## Secure Syscalls
  ### Secure Entry Points
   #### Background on OS System Calls
   #### Secure Syscall Lifecycle
   #### Argument Passing Format
   #### Validation of Handle Permissions
  ### Syscall Specification
 ## Trusted Application Framework
  ### Standard Library for Trusted Applications
   #### Standard Library Overview
  ### Handle Operations Specification
   #### channel functions
   #### factory functions
   #### object functions
   #### task functions
   #### memory management functions
  ### I/O Standard Library Specification
   #### printf functions
   #### log function
  ### Strings Standard Library Specification
   #### string functions
  ### Math Standard Library Specification
   #### algebraic functions
   #### thrigonometry functions
   #### math constants
   #### complex math functions
  ### Crypto Standard Library Specification
   #### Hashing Functions
   #### Encryption/Decryption Functions
   #### Key Management and Derivation
   #### Random Number Generation
  ### Container Standard Library Specification
   #### list container functions
   #### radix tree functions
   #### wavl tree functions
   #### red-black tree functions
  ### Concurrency Standard Library Specification
   #### atomic operations
   #### mutex functions
   #### spinlock functions
   #### semaphore functions
   #### conditional variables
  ### Misc Library Functions Specification
   #### align macros
   #### bit manipulation
   #### compiler macros ## Implementation Challenges and Optimizations
  ### Performance vs. Security Trade-Offs
  ### Memory Footprint optimizations
  ### Debugging Considerations
  ### Build System and Packaging for TAs
 ## Summary of Implementation
  ### ...

Starting with 3.12 Trusted Application Framework:
I have a draft of structure:
 ## Trusted Application Framework
  ### Standard Library for Trusted Applications
   #### Standard Library Overview
  ### Handle Operations Specification
   #### channel functions
   - channel_read
   - channel_write
   - channel_from_handle
   #### factory functions
   - factory_init
   - factory_create_vmo
   - factory_channel_create
   - factory_task_create
   - factory_get_handle
   #### object functions
   - object_copy
   - object_close
   #### task functions
   - task_spawn
   - task_share_handle
   #### memory management functions
   - vm_init
   - vm_map_vmp
   - vm_free
  ### I/O Standard Library Specification
   #### printf functions
   - printf (calls tee_log)
   - sprintf
   - vprintf
   #### log function
   - tee_log (calls SYS_LOG)
  ### Strings Standard Library Specification
   #### string functions
   - memset
   - memcmp
   - memcpy
   - memmove
   - memchr
   - strlen
   - strchr
   - strcmp
   - strtol
  ### Math Standard Library Specification
   #### algebraic functions
   - sqrt
   - pow
   - log
   - exp
   - abs
   - floor
   - ceil
   #### thrigonometry functions
   - sin
   - cos
   - tan
   - asin
   - acos
   - atan
   #### math constants
   - pi
   - e
   - inf
   - nan
   #### complex math functions
   - same as for real numbers
  ### Crypto Standard Library Specification
   #### Hashing Functions
   - sha256
   - sha512
   - md5
   #### Encryption/Decryption Functions
   #### Key Management and Derivation
   #### Random Number Generation
  ### Container Standard Library Specification
   #### list container functions
   - functions for single linked list
   - functions for double linked list
   #### radix tree functions
   - functions for radix tree
   #### wavl tree functions
   - functions for wavl tree
   #### red-black tree functions
   - functions for red-black tree
  ### Concurrency Standard Library Specification
   #### atomic operations
   - atomic_add_fetch
   - atomic_sub_fetch
   - atomic_or_fetch
   - atomic_and_fetch
   - atomic_read
   - atomic_write
   - smp_rb
   - smp_wb
   #### mutex functions
   - standard api
   #### spinlock functions
   - standard api
   #### semaphore functions
   - standard api
   #### conditional variables
   - standard api
  ### Misc Library Functions Specification
   #### align macros
   - align_up
   - align_up_ptr
   - align_down
   - align_down_ptr
   - is_aligned
   - is_aligned_ptr
   #### bit manipulation
   - bit32 (value with 1 << shift)
   - bit64 (value with 1 << shift)
   - is_power_of_two
   - clz32
   - clz64
   - log2
   #### compiler macros
   - barrier (compiler barrier)
   - container_of
   - various __attribute__ macros
   - same_type

Chapter is about secure userspace C library for Trusted Applications:
If needed - rename some sub chapters if there is more suitable naming, or maybe add some sub chapters or points if there is anything else to say to enhance the structure.
print answer in raw markdown format