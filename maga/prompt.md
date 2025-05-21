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

# Chapter 3: Design and Implementation of the Secure Operating System**
 ## Interface Considerations**
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
   #### struct wg_tee_cmd
   #### field id
   #### field seq
   #### field session_id
   #### field func_i
   #### field err
   #### field uuid
   #### field paddr
   #### field num_pages
   #### field shmem_id
   #### struct wg_param params
   #### padding
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
  ### Shared Queues From Linux Side
   #### Requests queue
   #### Responses queue
  ### Linux Communication Interface
   #### Communication Initialization
   #### Queue Initialization
   #### Commnication polling kthread
   #### Message Sending
   #### Getting Result
   #### Communication Finalization
 ## Secure Kernel Design
  ### Kernel Objects and Handles
   #### Tasks (Processes)
   #### Threads
   #### Pipes
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
 ## Capability-Based Security Model
  ### Handles as Encapsulated Capabilities
   #### Objects
   #### Object Handles
   #### Factory Objects
   #### Object Methods
  ### Capabily-Based Access Control
   #### Permissions
   #### Task Manifests
   #### Root Task
   #### Method Invocation
 ## Secure Syscalls
  ### Secure Entry Points
   #### validation of TA requests
   #### ...
  ### Syscall Specification
   #### SYS_LOG
   #### SYS_VM_ALLOCATE
   #### SYS_VMO_CREATE
   #### SYS_CHANNEL_CREATE
   #### SYS_CHANNEL_READ
   #### SYS_TASK_CREATE
   #### SYS_TASK_GET_SPACE
   #### SYS_VM_MAP_VMO
   #### SYS_VM_FREE
   #### SYS_TASK_SPAWN
   #### SYS_CHANNEL_WRITE
   #### SYS_OBJECT_CLOSE
   #### SYS_OBJECT_WAIT_MANY
   #### SYS_PHYSMAPPER_MAP
   #### SYS_TASK_SHARE_HANDLE
   #### SYS_OBJECT_COPY
 ## Trusted Application Framework
  ### Standard Library for Trusted Applications
   #### Standard Library Overview
  ### I/O Standard Library Specification
  ### Strings Standard Library Specification
  ### Math Standard Library Specification
  ### Crypto Standard Library Specification
  ### Communication Standard Library Specification
  ### Concurrency Standard Library Specification
 ## Implementation Challenges and Optimizations
  ### Performance vs. Security Trade-Offs
  ### Memory Footprint optimizations
  ### Debugging Considerations
  ### Build System and Packaging for TAs
 ## Summary of Implementation
  ### ...

Starting with 3.10 Capability-Based Security Model:
I have a draft of structure:
 ## Capability-Based Security Model
  ### Handles as Encapsulated Capabilities
   #### Objects
   #### Object Handles
   #### Factory Objects
   #### Object Methods
  ### Capabily-Based Access Control
   #### Permissions
   #### Task Manifests
   #### Root Task
   #### Method Invocation

Chapter is about how capability-based model is used in system design:
If needed - rename some sub chapters if there is more suitable naming, or maybe add some sub chapters or points if there is anything else to say to enhance the structure.
print answer in raw markdown format
