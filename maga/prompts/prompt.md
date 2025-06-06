project background:
Secure OS is a microkernel OS with capability based model, so the idea is that everything is a handle, all handles (that are listed at predefined Manifest) are given by root task to Trusted Application when it spawned. Creation of objects are done with fabric object handle. Every action to handle is checked with capability model and granted or denied.
Secure OS always works on first cpu core, other cores are left for Linux. Communication between Linux and Secure OS is provided using two shared pages. One page for requests (to secure OS) queue, second page for responses queue. It uses subset of Global Platform API as interface for communications.

Paper should have 4 chapters:

# Chapter 1: Foundations and Motivation for an Open Secure OS on RISC-V
# Chapter 2: Core Principles of Trusted Execution Environment and Threat Model
# Chapter 3: Design and Implementation of the Secure Operating System
# Chapter 4: Evaluation and Security Analysis

So, 4th chapter is about Evaluation and Security Analysis
I have a draft of chapter 4:

# Chapter 4: Evaluation and Security Analysis
 ## Software Stack Setup
  ### Toolchains
   #### Development Environment
  ### Emulation Environment
   #### QEMU with WorldGuard Support
   #### QEMU Configuration
  ### Linux
   #### Linux with WorldGuard Support
   #### Linux Configuration
   #### Linux Image
  ### Build System
   #### CMake Configuration
   #### CMake Build System Design
   #### Trusted Application (TA) Build Flow
  ### CI Integration
   #### Continuous Integration Setup
   #### Automated Testing Scripts
 ## Demonstration of Secure OS Functionality
  ### Building the Software Stack
   #### Cloning Project Repositories
   #### Building the Cross Toolchain
   #### Building the WorldGuard-Enabled QEMU
   #### Building the Patched OpenSBI
   #### Building a WorldGuard-Aware Linux Image
   #### Building Secure OS
   #### Assembling Bootable Image
  ### Example Trusted Application: Simple Arithmetic TA
   #### Writing a Simple Trusted Application
   #### Defining TA Manifest for Capability Model
   #### Building the Trusted Application
  ### Demonstration and Execution
   #### Booting the System
   #### Initializing the Linux Driver for Secure OS Communication
   #### Opening a Session to Trusted Application
   #### Invoking the TA Function and Receiving Response
   #### Visualizing Capability Enforcement (Optional)
   #### Debugging and Logging Support
 ## Security Analysis
  ### Resilience against Normal World Attacks
   #### Unauthorized Access to Secure Memory
   #### Unauthorized Access to Secure OS/TA Code
   #### Attempts to Corrupt Shared Memory Queues
   #### Exploiting CWC Protocol (Cross World Communication)
  ### Resilience against Buggy Trusted Applications
   #### Inter-TA Isolation
   #### Capability Enforcement Engine
   #### TA Resource Misuse Protection
   #### Side-Channel Attacks
  ### Additional Attack Scenarios and Limitations
   #### Physical Attacks
   #### Complexity of Trusted Computing Base (TCB)
   #### Chain of Trust Attacks
 ## Performance Evaluation
  ### Latency of Secure OS Operations
   #### Session Open Latency
   #### Command Invocation Latency
   #### Session Close Latency
  ### Communication Performance
   #### Throughput of CWC Channel
   #### IPI Signaling Overhead
   #### TA Context Switch Overhead
   #### Kernel Entry/Exit Transition Overhead
  ### Memory and Resource Footprint
   #### Memory Footprint of Secure OS
   #### Per-TA Resource Consumption
   #### Shared Queue Overhead
   #### Scalability Limits and Bottlenecks

Starting with following chapters:
I have a draft of section:

 ## Performance Evaluation
 - This section evaluates the runtime behavior, efficiency, and resource usage of the Secure OS, with emphasis on inter-world communication, Trusted Application (TA) execution overhead, and system resource constraints in a constrained RISC-V environment.
 - Measurements are taken on an emulated platform using WorldGuard-enabled QEMU.
  ### Latency of Secure OS Operations
  - This subsection presents a detailed breakdown of the latency involved in interaction between the Normal World (Linux) and the Secure World (Secure OS), following the GlobalPlatform API lifecycle: session open, command invocation, session close.
  - Note: All latency measurements should include mean, standard deviation, and max/min values with multiple runs.
   #### Session Open Latency
   - Time required to open a session to a TA via TEEC_OpenSession()
   - Includes context switch, message construction, capability validation, and TA instantiation
   - Factors influencing latency (TA manifest size, cold start vs. warm start)
   #### Command Invocation Latency
   - Latency of TEEC_InvokeCommand() to a previously opened TA Session
   - Breakdown of fixed syscall overhead, scheduling delay, and parameter marshalling
   - Synchronous vs. asynchronous (if supported)
   #### Session Close Latency
   - Time to teardown the session and reclaim resources
   - Includes cleanup of handles, session state, and Secure OS bookkeeping
  ### Communication Performance
  - Evaluation of the throughput and timing characteristics of the CWC (Cross World Communication) mechanism, emphasizing Serializable Command Queues backed by Shared Memory.
   #### Throughput of CWC Channel
   - Maximum achievable throughput of request/response cycles through shared memory queues
   - Impact of message size
   #### IPI Signaling Overhead
   - Cost of using Inter-Processor Interrupt (IPI) for signaling between worlds
   - Measurement of context switch delay due to IPI
   - Comparison of IPI costs under load and idle scenarios
   #### TA Context Switch Overhead
   - Cost of switching between multiple TAs or restoring TA context for a scheduled operation
   #### Kernel Entry/Exit Transition Overhead
   - Benchmark the time overhead to perform Secure OS syscalls (without actual work)
   - Use of synthetic minimal syscall to isolate context switch cost
  ### Memory and Resource Footprint
  - Analysis of memory usage of the Secure OS and associated components under typical workloads.
   #### Memory Footprint of Secure OS
   - Static memory usage (text/data/bss sizes)
   - Dynamic memory usage at runtime (heap usage, page tables)
   - Total footprint with N TAs loaded
   #### Per-TA Resource Consumption
   - Memory consumption per individual TA context
   - Number of handles, stack size, VMO usage
   #### Shared Queue Overhead
   - Memory and CPU overhead of shared ring buffers for communication queues
   - Lock-free implementation impact
   #### Scalability Limits and Bottlenecks
   - Maximum number of concurrently active TAs
   - System behavior under memory pressure
   - Fragmentation and memory management limitations

write contents of these section based on draft.
If needed - maybe add some points if there is anything else to say by topic.
full structure of whole paper is in the attached file.
Do not write very much, only a few sentencies!
Do not repeat yourself! Do not repeat points from other chapters! Keep it concise! Write only section contents, no summary or reasoning.