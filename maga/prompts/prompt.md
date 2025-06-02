project background:
Secure OS is a microkernel OS with capability based model, so the idea is that everything is a handle, all handles (that are listed at predefined Manifest) are given by root task to Trusted Application when it spawned. Creation of objects are done with fabric object handle. Every action to handle is checked with capability model and granted or denied.
Secure OS always works on first cpu core, other cores are left for Linux. Communication between Linux and Secure OS is provided using two shared pages. One page for requests (to secure OS) queue, second page for responses queue. It uses subset of Global Platform API as interface for communications.

Paper should have 4 chapters:

# Chapter 1: Foundations and Motivation for an Open Secure OS on RISC-V
# Chapter 2: Core Principles of Trusted Execution Environment and Threat Model
# Chapter 3: Design and Implementation of the Secure Operating System
# Chapter 4: Evaluation and Security Analysis

So, 3rd chapter is about Design and Implementation of the Secure Operating System
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
   #### TEEC_UUID
   #### TEEC_Result
   #### TEEC_Context;
   #### TEEC_Session;
   #### TEEC_Value;
   #### TEEC_RegisteredMemoryReference;
   #### TEEC_Parameter;
   #### TEEC_Operation;
   #### TEEC_SharedMemory;
   #### TEEC_InitializeContext
   #### TEEC_FinalizeContext
   #### TEEC_OpenSession
   #### TEEC_CloseSession
   #### TEEC_InvokeCommand
   #### TEEC_AllocateSharedMemory
   #### TEEC_ReleaseSharedMemory
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
  ### Handle Operations Specification
  ### I/O Standard Library Specification
  ### Strings Standard Library Specification
  ### Math Standard Library Specification
  ### Crypto Standard Library Specification
  ### Container Standard Library Specification
  ### Concurrency Standard Library Specification
  ### Misc Library Functions Specification
 ## Implementation Challenges and Optimizations
  ### Performance vs. Security Trade-Offs
   #### Balancing Isolation with Speed
   #### Inter-World Communication Overhead
   #### Scalability Limits on a Single-Core Secure OS
  ### Memory Footprint Optimizations
   #### Static Allocation vs. Dynamic Allocation
   #### Slab Allocator and Page Pool Efficiency
   #### Minimal Kernel Subsystem Design
  ### Debugging Considerations
   #### Logging from Secure OS
   #### Debugging TAs in Isolation
   #### Instrumentation Techniques
   #### Fault Isolation and Crash Analysis
  ### Build System and Packaging for TAs
   #### Trusted Application Build Flow
   #### Kernel Build System
   #### Development Tooling Support
  ### Testing and Validation
   #### Unit Testing Secure OS Components
   #### Integration Testing with Linux
   #### Security-Oriented Tests
  ### Summary of Implementation
   #### Overview
   #### Codebase Structure Summary
   #### Opportunities for Improvement


Starting with chapter 3.2.7 WorldGuard Configuration
I have a draft of chapter sections:

  ### WorldGuard Configuration
   #### World Configuration (Two-World Model)
   - Overview of how the system hardware and memory are split between Secure World and Normal World.
   - Explanation of the two-world design rationale, focusing on isolation guarantees.
   - Definition of the roles of each world (e.g., Secure OS vs. Linux).
   - Description of how World IDs are assigned and managed.
   #### WorldGuard Checker Configuration for Secure Isolation
   - Overview of the hardware/software checker mechanism for enforcing world-based isolation.
   - Configuration of Secure RAM slots and memory regions:
     - Secure memory partitioning approach.
     - Locking down memory regions to the Secure World
   - Setting up enclave/partition boundaries:
     - Handling enclaves within the Secure World.
     - Policy for controlling access across enclaves or from Normal World.
   - Integration of memory attributes (e.g., read/write/exec permissions) with WorldGuard checks.


secure regions mappings for context:

#define ARCH_USERMEM_BEGIN 0x1000
#define ARCH_USERMEM_END (30UL << 30)

/* -128G */
#define KERNEL_VIRTUAL_BASE 0xffffffe000000000
#define KERNEL_VIRTUAL_OFFSET (KERNEL_VIRTUAL_BASE - 0x0000000080200000)

/* 30G */
#define KERNEL_LINEAR_MAP_BEGIN KERNEL_VIRTUAL_BASE
#define KERNEL_LINEAR_MAP_END (KERNEL_VIRTUAL_BASE + (30UL << 30))

/* 20G */
#define KERNEL_DEVICE_BEGIN KERNEL_LINEAR_MAP_END
#define KERNEL_DEVICE_END (KERNEL_DEVICE_BEGIN + (20UL << 30))

/* 10G */
#define KERNEL_VMALLOC_BEGIN KERNEL_DEVICE_END
#define KERNEL_VMALLOC_END (KERNEL_VMALLOC_BEGIN + (10UL << 30))

#define KERNEL_VIRTUAL_END      KERNEL_VMALLOC_END

write contents of these sections based on draft.
If needed - maybe add some points if there is anything else to say by topic.
full structure of whole paper is in the attached file
Do not repeat yourself! Keep it concise! Do not include statements from other chapters! Write only section contents, no summary or reasoning.