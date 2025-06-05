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


Starting with chapter 3.8.2. Handles as Encapsulated Capabilities
I have a draft of chapter sections:

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

write contents of these sections based on draft.
If needed - maybe add some points if there is anything else to say by topic.
full structure of whole paper and some of secure kernel boot code is in the attached file.Do not repeat yourself! Do not repeat points from other chapters! Keep it concise! Write only section contents, no summary or reasoning.