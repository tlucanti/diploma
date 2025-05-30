# Chapter 1: Introduction
 ## + 1.1 Background and Motivation
  - Emergence of Trusted Execution Environments (TEEs) in modern computing.
  - Security challenges in heterogeneous computing environments.
  - Role of hardware extensions like RISC-V World Guard in enhancing secure computing.

 ## + 1.2 Problem Statement
  - Limitations of existing TEE implementations (e.g., ARM TrustZone, Intel SGX).
  - Gaps in RISC-V ecosystem for lightweight, flexible TEE frameworks.
  - Need for cross-world communication with minimal performance overhead.

 ## + 1.3 Relevance of the Work
  - Addressing RISC-V’s growing adoption and security demands.
  - Enabling secure IoT, edge computing, and confidential machine learning.

 ## 1.4 Comparison with Existing TEE Architectures
  - ARM TrustZone vs. RISC-V World Guard.
  - Isolation trade-offs: hardware-based vs. software-assisted models.
  - Performance and flexibility metrics.

 ## 1.5 Applications of TEE
  - Secure firmware updates, cryptographic key management, digital rights management (DRM).
  - Use cases in healthcare, industrial control systems, and confidential AI inferencing.

 ---

# Chapter 2: Trusted Execution Environment (TEE) Fundamentals
 ## 2.1 TEE Overview
  - Definition, core principles (confidentiality, integrity, availability).
  - TEE components: secure boot, isolation, attestation.

 ## 2.2 Threat Model
  - Attacker capabilities: physical attacks, side-channel exploits, runtime tampering.
  - Protected assets: TAs (Trusted Applications), secure communication channels.

 ## 2.3 Isolation Mechanisms
  - Hardware-enforced isolation: memory domains, privilege levels.
  - Role of RISC-V World Guard extension:
    . World IDs: Defining secure and normal worlds.
    . Context Switching: Hardware-assisted world transitions.
    . Memory Tagging: Fine-grained access control.

 ## 2.4 Chain of Trust
  - Secure boot process: OpenSBI, bootloader, and secure OS handoff.
  - Measurement and attestation of TEE components.

 ## 2.5 TEE Interface and Services
  - APIs for trusted application management (session lifecycle, resource allocation).
  - Secure storage, cryptographic primitives, and real-time attestation.

 ---

# Chapter 3: Secure OS Implementation
 ## 3.1 System Architecture
  ### World Guard Integration:
   - Modifying OpenSBI for world context management.
   - Configuring memory protection units (MPUs) for isolated worlds.
  ### Boot Process:
   - Secure OS initialization on core 0.
   - Linux OS boot on secondary cores.

 ## 3.2 Cross-World Communication
  ### Design and Protocol:
   - Shared memory architecture (request/response queues).
   - Command formats: open/invoke/close session primitives.
  ### Buffer Management:
   - Cryptographic integrity checks (e.g., HMACs) on shared pages.
   - Lock-free ring buffer implementation for low-latency IPC.
  ### Interrupt Handling and IPIs:
   - Linux driver-initiated IPIs to Secure OS.
   - Secure OS scheduler synchronization with Linux.

 ## 3.3 Linux Driver Implementation
  ### Kernel Module Design:
   - Character device interface for user-space interaction.
   - Memory mapping of shared pages.
  ### IPI Handling:
   - Core-to-core interrupt routing using SBI interfaces.

 ## 3.4 Secure Kernel
  ### Task Management:
   - TA process creation, scheduling policies (cooperative/preemptive).
   - Context switching between secure and normal worlds.
  ### Secure Syscalls:
   - Gatekeeper mechanism for validating TA requests.
   - Secure hypercalls for resource allocation (e.g., encrypted memory regions).

 ## 3.5 Secure Userspace Framework
  ### TA Framework:
   - Lifecycle hooks (TA initialization, command processing, teardown).
   - API libraries for inter-TA communication and secure storage.
  ### Standard Library and SDK:
   - Lightweight C runtime optimized for TEE constraints.
   - Debugging tools for secure-world developers.

 ---

# Chapter 4: Evaluation and Case Study
 ## 4.1 Software Stack Configuration
  ### QEMU Emulation:
   - RISC-V virtualization with World Guard extension.
   - Integration of modified OpenSBI and Linux kernel.
  ### Trusted Application Demo:
   - Example workflow: secure key generation and cryptographic operations.

 ## 4.2 Cross-World Communication Demo
  ### Latency Measurements:
   - IPI response times, shared page access overhead.
  ### End-to-End Workflow:
   - Linux user-space client invoking TA via driver.
   - Secure response validation and session teardown.

 ## 4.3 Security Analysis
  ### Attack Surface Assessment:
   - Exploit mitigations: buffer overflow protection, world ID spoofing resistance.
   - Penetration testing results (e.g., DMA attacks on shared memory).
  ### Formal Verification:
   - Model-checking critical components (e.g., session state machine).

 ## 4.4 Performance Benchmarks
  - Overhead introduced by Secure OS (CPU utilization, memory footprint).
  - Comparison with baseline Linux without TEE.

 ## 4.5 Future Work
  - Support for multi-party TEEs (collaborative secure computations).
  - Hardware acceleration for cryptographic operations.

 ## 4.6 Conclusion
  - Summary of contributions to TEE ecosystem for RISC-V.
  - Broader implications for open-source security architectures.

 ---

# Appendices
- A. RISC-V World Guard Extension Specifications.
- B. Secure OS Source Code Repository and Build Instructions.
- C. Example Trusted Application Code Snippets.
- D. Detailed Performance Metrics.
