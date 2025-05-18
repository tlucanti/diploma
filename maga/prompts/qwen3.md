## **Chapter 1: Introduction**
1.1 **Background on Trusted Execution Environments (TEEs)**
- Evolution of TEEs in modern computing: From TrustZone to SGX.
- Role of TEEs in secure computing: Confidentiality, integrity, and isolation guarantees.

1.2 **Problem Statement and Motivation**
- Limitations of existing TEEs (e.g., vendor lock-in, closed ecosystems, hardware complexity).
- Need for an open-source, RISC-V-based TEE framework.

1.3 **Relevance and Applications**
- Use cases: IoT device security, edge computing, secure boot, cryptographic operations.
- Advantages of RISC-V for customizable, transparent, and scalable TEEs.

1.4 **Comparison with Existing Architectures**
- ARM TrustZone, Intel SGX, and OpenTitan vs. RISC-V World Guard.
- Trade-offs in hardware/software co-design for TEEs.

1.5 **Related Work**
- Overview of OpenSBI, Keystone Enclave, and other RISC-V TEE projects.
- Gaps in current RISC-V TEE ecosystems (e.g., standardization, cross-world communication).

---

## **Chapter 2: Trusted Execution Environment Architecture**
2.1 **TEE Fundamentals**
- Definition: Secure world vs. normal world, Trusted Applications (TAs).
- Core principles: Isolation, tamper resistance, minimal trusted computing base (TCB).

2.2 **Threat Model and Security Objectives**
- Attack vectors: Side-channel attacks, memory corruption, IPI spoofing.
- Protection goals: Confidentiality of TA data, integrity of Secure OS, denial-of-service mitigation.

2.3 **Hardware-Assisted Isolation Mechanisms**
- CPU core partitioning: Secure OS on core 0, Linux on remaining cores.
- Memory isolation: Physical memory regions for Secure OS (RAM/ROM), Linux, and shared pages.
- Peripheral partitioning: Secure vs. non-secure device access via World Guard.

2.4 **World Guard Extension: Technical Deep Dive**
- RISC-V privilege modes (M/S/U) and World Guard’s "Secure" mode.
- World Switching: Triggers, context saving, and entry/exit handling.
- Protection of Secure OS resources: MMU configuration, exception handling, and IPI routing.

2.5 **TEE Interface and Trusted User Interface (TUI)**
- Secure monitor call (SMC) interface for cross-world transitions.
- TUI design: Secure input/output pathways for Trusted Applications.

2.6 **Boot Sequence and Chain of Trust**
- Secure boot flow: OpenSBI → Secure OS → Linux.
- Measurement and verification of Secure OS and TA images.

---

## **Chapter 3: Secure OS Implementation**
3.1 **System Architecture Overview**
- Components: Secure kernel, TA framework, cross-world communication (CWC) layer.
- Integration with OpenSBI and Linux driver.

3.2 **World Guard Integration**
- Modifications to OpenSBI for Secure world initialization.
- Handling World Switches: Context preservation and restoration.

3.3 **Boot Process and Initialization**
- Secure OS startup on core 0: Memory mapping, task creation, and capability setup.
- Linux initialization on secondary cores: Resource partitioning and driver registration.

3.4 **Cross-World Communication Protocol**
- Shared memory queues: Request/response page structures and synchronization.
- IPI-based signaling: Mechanisms for Linux → Secure OS notifications.
- Session management: `open`, `invoke`, `close` lifecycle.

3.5 **Secure Kernel Design**
3.5.1 **Microkernel Architecture**
- Minimalist design: Core services (scheduling, IPC, memory management).
- Protection against TA crashes and resource exhaustion.

3.5.2 **Capability-Based Security Model**
- Object handles: Tasks, threads, memory regions, and peripherals.
- Method handles: Revocation, delegation, and fine-grained permissions.
- Task manifests: Static declaration of required resources and syscalls.
- Root task: Initial authority and dynamic capability distribution.

3.5.3 **Syscall and Access Control**
- Secure entry points: Validation of TA requests.
- Policy enforcement: Capability checks for device access and memory allocation.

3.6 **Secure Userspace: TA Framework**
- SDK for Trusted Applications: API for syscalls, memory sharing, and communication.
- Standard library: Crypto primitives, memory management, and logging.

3.7 **Linux Driver for Secure Communication**
- Device file operations: `ioctl` for session management.
- Shared page mapping and IPI triggering via RISC-V PLIC.

---

## **Chapter 4: Evaluation and Security Analysis**
4.1 **Software Stack and Testbed**
- Setup: QEMU RISC-V virt platform, Linux kernel, modified OpenSBI, and Secure OS.
- Workflow: Building, flashing, and launching TAs.

4.2 **Demonstration of Trusted Application Execution**
- Example TA: Secure encryption/decryption service.
- Step-by-step communication: Session creation, request submission, response handling.

4.3 **Performance Evaluation**
- Latency measurements: World Switching overhead, IPC throughput.
- Memory footprint: Secure OS and TA resource utilization.

4.4 **Security Analysis**
- Attack surface reduction: Isolation validation via fault injection.
- Capability enforcement: Testing unauthorized access attempts.
- Robustness against IPI flooding and memory exhaustion.

4.5 **Conclusion and Future Work**
- Summary of contributions: Lightweight Secure OS, capability model, CWC design.
- Limitations: Current scalability, single-core constraint.
- Future directions: Multi-core Secure OS support, formal verification, integration with physical Trusted Platform Modules (TPMs).

---

### **Appendices**
- A: RISC-V Assembly Code for World Switching
- B: Capability Model Formalization (Optional)
- C: Benchmark Data and Testbed Configuration

---
