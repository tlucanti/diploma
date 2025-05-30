# Chapter 1: Introduction
1.1. Background: The Evolving Landscape of Secure Computing
1.2. Introduction to Trusted Execution Environments (TEEs)
    1.2.1. Core Principles of TEEs
    1.2.2. Why TEEs are Necessary
1.3. The RISC-V Opportunity: Openness and Extensibility
    1.3.1. The RISC-V Instruction Set Architecture (ISA)
    1.3.2. Advantages of an Open Architecture for Security
1.4. Problem Statement: The Gap in Open Source RISC-V TEEs
    1.4.1. Current State of TEEs on Proprietary Architectures
    1.4.2. The Need for Open, Verifiable TEE Implementations for RISC-V
1.5. Relevance and Contributions of This Work
    1.5.1. Novel Secure OS Design for RISC-V World Guard
    1.5.2. Capability-Based Security Model
    1.5.3. Open Source Approach and Community Impact
1.6. Potential Applications of RISC-V TEEs
    1.6.1. Secure Data Processing and Confidential Computing
    1.6.2. Digital Rights Management (DRM)
    1.6.3. Secure Firmware Updates
    1.6.4. IoT Security
    1.6.5. Blockchain and Cryptocurrency Applications
1.7. Comparison with TEEs on Other Architectures
    1.7.1. ARM TrustZone
    1.7.2. Intel SGX (Software Guard Extensions)
    1.7.3. AMD SEV (Secure Encrypted Virtualization)
    1.7.4. Key Differentiators for a RISC-V Based Solution
1.8. Related Work
    1.8.1. Existing RISC-V TEE Research and Prototypes
    1.8.2. Open Source TEE Frameworks (e.g., OP-TEE) and Their Applicability
    1.8.3. Research on Capability-Based Operating Systems
1.9. Paper Structure

---

# Chapter 2: Foundations of Trusted Execution Environments on RISC-V
2.1. Defining Trusted Execution Environments (TEEs)
    2.1.1. Goals: Confidentiality, Integrity, Attestation
    2.1.2. Components: Secure World, Normal World, Trusted Applications
2.2. Threat Model
    2.2.1. Assumptions about the Normal World (Untrusted OS, Privileged Software)
    2.2.2. Attacker Capabilities (Software, Side-Channel, Limited Physical)
    2.2.3. Assets to Protect (TA Code, TA Data, Secure OS State)
    2.2.4. Security Guarantees Provided by the TEE
2.3. Isolation Mechanisms
    2.3.1. Principle of Least Privilege
    2.3.2. Hardware-Enforced Isolation: The Cornerstone of TEEs
        2.3.2.1. CPU Core Separation (Dedicated Secure Core)
        2.3.2.2. Memory Isolation (Secure vs. Non-Secure RAM regions)
        2.3.2.3. ROM and Secure Storage Considerations
        2.3.2.4. Peripheral Segregation and Secure Access
2.4. RISC-V World Guard Extension
    2.4.1. Overview and Motivation
    2.4.2. Architectural Features: Worlds, Gates, Transitions
    2.4.3. Memory Protection Mechanisms provided by World Guard
    2.4.4. Privilege Levels within World Guard
    2.4.5. Integration with Physical Memory Protection (PMP)
2.5. TEE Interface Design Considerations
    2.5.1. Normal World (Client) to Secure World API (e.g., GlobalPlatform TEE Client API)
    2.5.2. Trusted Application to Secure OS API (Internal API)
2.6. Trusted User Interface (TUI)
    2.6.1. Purpose: Secure Input and Output
    2.6.2. Challenges and Design Considerations for TUI on RISC-V
    2.6.3. TUI in the Context of this Project (conceptual, if not fully implemented)
2.7. Boot Sequence and Chain of Trust
    2.7.1. Secure Boot Principles
    2.7.2. Role of the First Stage Bootloader (FSBL) / Mask ROM
    2.7.3. OpenSBI's Role in Establishing the Secure Environment
        2.7.3.1. OpenSBI Modifications for World Guard Support
        2.7.3.2. Loading and Verifying the Secure OS
    2.7.4. Handover to the Secure OS and Normal World OS

---

# Chapter 3: Design and Implementation of the Secure OS
3.1. Overall System Architecture
    3.1.1. High-Level Component Diagram (Secure OS, Linux, OpenSBI, Hardware)
    3.1.2. Interaction Model between Components
3.2. Leveraging RISC-V World Guard
    3.2.1. Mapping Secure OS and TAs to the Secure World
    3.2.2. Managing World Transitions (Entry/Exit to Secure World)
    3.2.3. Configuring Memory Protection using World Guard and PMP
3.3. Secure Boot Process and Initialization
    3.3.1. OpenSBI Handover: Entry into Secure OS on the First Core
    3.3.2. Secure OS Kernel Initialization
        3.3.2.1. Hardware Abstraction Layer (HAL) Setup
        3.3.2.2. Memory Management Initialization (for Secure World)
        3.3.2.3. Scheduler and Root Task Creation
    3.3.3. Initialization of Normal World Environment for Linux (by OpenSBI/Secure OS)
3.4. Cross-World Communication (CWC)
    3.4.1. Design Philosophy: Explicit, Minimized Interface
    3.4.2. Shared Memory Buffers: Request and Response Queues
        3.4.2.1. Structure and Management of Queues
        3.4.2.2. Synchronization Primitives (if any, beyond IPIs)
    3.4.3. Inter-Processor Interrupts (IPIs) for Signaling
        3.4.3.1. IPI Handling in Secure OS
        3.4.3.2. IPI Handling in Linux Driver
    3.4.4. CWC Protocol:
        3.4.4.1. Session `open`: TA Selection and Resource Allocation
        3.4.4.2. `invoke` Command: Parameter Marshalling and TA Execution
        3.4.4.3. Response Handling and Data Return
        3.4.4.4. Session `close`: Resource Deallocation
    3.4.5. Linux Driver Interface (from Secure OS perspective)
        3.4.5.1. Driver's Role in Managing Shared Pages and IPIs
        3.4.5.2. Exposing CWC to User-space Linux Applications
3.5. Secure Kernel (Microkernel-inspired Design)
    3.5.1. Rationale for Microkernel Architecture (Security, Modularity)
    3.5.2. Core Kernel Abstractions: Objects and Handles
        3.5.2.1. Tasks (Processes)
        3.5.2.2. Threads
        3.5.2.3. Inter-Process Communication (IPC) Objects (e.g., Pipes, Message Queues)
        3.5.2.4. Virtual Memory Objects (VMOs) / Memory Regions
        3.5.2.5. Other synchronization primitives if any (e.g., Mutexes, Semaphores within Secure World)
    3.5.3. Task Management and Scheduling
        3.5.3.1. TA Process Model (creation, yielding as per spec)
        3.5.3.2. Scheduling Policy within the Secure World
    3.5.4. Memory Management within the Secure OS
        3.5.4.1. Secure Memory Allocator
        3.5.4.2. Per-TA Memory Isolation
    3.5.5. System Call (Syscall) Interface
        3.5.5.1. Syscall Dispatch Mechanism
        3.5.5.2. Available System Calls for TAs
    3.5.6. Capability-Based Access Control
        3.5.6.1. Handles as Encapsulated Capabilities
        3.5.6.2. Task Manifests: Declaring Required Capabilities and Permissions
        3.5.6.3. Root Task: Initial Owner of All Resources and Capabilities
        3.5.6.4. Capability Delegation and Restriction
        3.5.6.5. Factory Objects for Creating New Kernel Objects (e.g., TaskFactory, ThreadFactory)
        3.5.6.6. "Method-as-Handle" Invocation:
            3.5.6.6.1. Obtaining Method Handles
            3.5.6.6.2. Invoking Methods using (Object Handle, Method Handle) Pair
            3.5.6.6.3. Implicit Permission via Handle Ownership
    3.5.7. Communication Control for Trusted Applications
        3.5.7.1. Mediating TA-to-TA Communication (if supported)
        3.5.7.2. Controlling Access to CWC Resources
3.6. Secure Userspace for Trusted Applications
    3.6.1. TA Framework and Lifecycle Management
        3.6.1.1. TA Loading and Verification (Signature Check, Hashing)
        3.6.1.2. TA Instantiation (Process Creation, Resource Allocation)
        3.6.1.3. TA Execution and State Management
        3.6.1.4. TA Termination and Cleanup
    3.6.2. TA API: Interacting with the Secure Kernel
        3.6.2.1. System Call Wrappers
        3.6.2.2. Accessing Shared Memory for CWC
        3.6.2.3. Requesting Cryptographic Services (if applicable)
    3.6.3. Standard Library for TAs (Secure LibC subset)
        3.6.3.1. Essential Functions (Memory, String, etc.)
        3.6.3.2. Restrictions and Security Considerations
    3.6.4. SDK for TA Development
        3.6.4.1. Toolchain (Compiler, Linker)
        3.6.4.2. Build System and Packaging for TAs
        3.6.4.3. Debugging Support (if any)

---

# Chapter 4: Demonstration, Evaluation, and Security Analysis
4.1. Experimental Setup
    4.1.1. Emulation Environment: QEMU with World Guard Support
        4.1.1.1. QEMU Configuration and Patches (if any)
    4.1.2. Software Stack:
        4.1.2.1. Modified OpenSBI Version
        4.1.2.2. Linux Kernel Version and Configuration (with CWC driver)
        4.1.2.3. Secure OS Image and Sample Trusted Applications
4.2. Demonstration of Secure OS Functionality
    4.2.1. Booting the System: Secure OS and Linux Co-existence
    4.2.2. A Sample Trusted Application Walkthrough
        4.2.2.1. TA Design (e.g., simple cryptographic operation, secure counter)
        4.2.2.2. Linux Client Application invoking the TA
    4.2.3. Cross-World Communication in Action:
        4.2.3.1. Tracing `open` Session Request and TA Creation
        4.2.3.2. Tracing `invoke` Command and TA Execution
        4.2.3.3. Observing Response Delivery via Response Queue
        4.2.3.4. Tracing `close` Session Request and TA Termination
    4.2.4. Performance Evaluation (Optional, but valuable)
        4.2.4.1. Latency for `open`, `invoke`, `close` operations
        4.2.4.2. Throughput of CWC channel
        4.2.4.3. Context Switch Overhead within Secure World (TA yield/resume)
4.3. Security Analysis
    4.3.1. Review of Threat Model and Security Goals
    4.3.2. Resilience against Normal World Attacks:
        4.3.2.1. Unauthorized Access to Secure Memory (Prevented by World Guard/PMP)
        4.3.2.2. Unauthorized Access to Secure OS/TA Code (Prevented by World Guard/PMP)
        4.3.2.3. Attempts to Corrupt Shared Memory Queues (Validation, Secure OS checks)
        4.3.2.4. Exploiting CWC Protocol (Input validation, state management)
        4.3.2.5. Bypassing Capability Checks (Integrity of handle system)
    4.3.3. Resilience against Malicious/Compromised TAs (if applicable and designed for)
        4.3.3.1. Inter-TA Isolation (Memory, Capabilities)
    4.3.4. Discussion of Potential Vulnerabilities and Limitations
        4.3.4.1. Side-Channel Attacks (Brief discussion, future work)
        4.3.4.2. Physical Attacks (Out of scope for software TEEs generally)
        4.3.4.3. Complexity of TCB (Trusted Computing Base)
4.4. Conclusion
    4.4.1. Summary of Achievements
    4.4.2. Reiteration of Contributions
    4.4.3. Answering the Problem Statement
4.5. Future Work
    4.5.1. Enhanced TA Features (Secure Storage, Attestation, Cryptographic Services)
    4.5.2. Full Trusted User Interface (TUI) Implementation
    4.5.3. Multi-core Support within the Secure World
    4.5.4. Formal Verification of Kernel Components or Capability System
    4.5.5. Support for Dynamic TA Loading/Unloading
    4.5.6. Porting to Real RISC-V Hardware with World Guard
    4.5.7. Hardening against Side-Channel Attacks
    4.5.8. Integration with standardized TEE APIs (e.g., GlobalPlatform)

---

References
*(List of all cited works)*

Appendices (Optional)
A. CWC Protocol Data Structures
B. Sample TA Code
C. Kernel Configuration Snippets
*(Any supplementary material that doesn't fit well in the main body)*

---

This structure provides a logical flow, covers all the aspects you mentioned, and allows for detailed discussion where necessary. Remember to use figures and diagrams, especially in # Chapter 3, to illustrate your architecture and communication flows. Good luck with your paper!
