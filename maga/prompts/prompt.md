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


Starting with chapter 3.5.4. Message Structure
I have a draft of chapter sections:

#### struct wg_tee_cmd
- All commands passed through the request/response queues adhere to a consistent message format. This section details the wg_tee_cmd structure, which encapsulates TEE operation parameters and results.
- This structure holds command identifiers, session tracking, error codes, and additional parameters.
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

write contents of these sections based on draft.
If needed - maybe add some points if there is anything else to say by topic.
full structure of whole paper and some of secure kernel boot code is in the attached file.
Do not repeat yourself! Do not repeat points from other chapters! Keep it concise! Write only section contents, no summary or reasoning.