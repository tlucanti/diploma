
# Chapter 4: Evaluation and Security Analysis
 ## Software Stack Setup
 - This section provides a detailed description of the full software environment used to support and validate the Secure OS, focusing on emulation, build infrastructure, and integration with toolchains.
 - This chapter is essential to reproduce the development setup and benchmark context.
  ### Toolchains
  - Description of RISC-V GCC or LLVM toolchain versions, secure OS and TA compilation flags, linker scripts used, and build script wrappers.
   #### Development Environment
   - Recommended dev environment setup: OS dependencies, Make/CMake/gcc versions, scripting helpers, debugging support (e.g., GDB hooks to Secure OS), and virtual machine setup, if applicable.
  ### Emulation Environment
  - A robust emulation setup using QEMU provides a virtual platform to simulate the RISC-V World Guard hardware and enables rapid development and testing.
   #### QEMU with WorldGuard Support
   - Explanation of QEMU version used and modifications or forks maintained to support the World Guard extension.
   #### QEMU Configuration
   - QEMU settings used during emulation: memory map, number of harts, device tree blob (DTB) settings, and boot arguments necessary to launch both Secure OS and Linux.
   - Also covers usage of debugging options and UART output customization.
  ### Linux
  - A Secure World-aware Linux kernel build is a key part of the integration testing, providing the userland-controlled "Normal World" for Secure OS interaction.
   #### Linux with WorldGuard Support
   - Brief explanation of the version/fork of the Linux kernel used, including any upstream or out-of-tree patches to support Secure OS interaction and WorldGuard.
   #### Linux Configuration
   - Kernel config menu options (e.g., minimal init system, character device support, TEE driver integration) and explanation of chosen configurations.
   #### Linux Image
   - Process of creating the kernel image and initial RAM filesystem (initramfs); integration into QEMU boot flow and linkage with rootfs/init and Secure OS debug output collection.
  ### Build System
  - The build system is centralized and modular to build various components including the kernel, trusted applications, OpenSBI, and Linux.
   #### CMake Configuration
   - How the overall build system is managed using CMake files: compiler toolchains, cross-compilation targets, component path registration, and reusability across Secure OS kernel and TA build systems.
   #### CMake Build System Design
   - Code organization and dependency separation. Build phases: TA compilation, kernel linking, staging and image generation. Covers options or build presets (e.g., debug vs release), and the way it cooperates with toolchains and QEMU images.
   #### Trusted Application (TA) Build Flow
   - Explains how a TA is built, manifests are generated, linking to standard libraries, and embedding into final system images.
  ### CI Integration
  - Automated testing ensures regression-free development and reliable build stability.
   #### Continuous Integration Setup
   - Framework used for testing (e.g., GitHub Actions, GitLab CI, Jenkins), pipeline stages—such as QEMU boot test, TA invocation test—and artifacts generation.
   #### Automated Testing Scripts
   - Details on scripts and system outputs validated within CI. Boot success, basic syscall availability and secure/normal world boundary integrity.

 ## Demonstration of Secure OS Functionality
 - In this section, we showcase the practical use and integration of the Secure OS, including building the software stack, developing a minimal Trusted Application (TA), and demonstrating its execution using the Linux-side communication driver.
  ### Building the Software Stack
   - This subsection outlines detailed steps to build all required components for running the full software stack in a QEMU-based RISC-V emulated environment.
   #### Cloning Project Repositories
   - Steps to clone Secure OS, OpenSBI, Linux kernel, QEMU, and any required dependency sources.
   #### Building the Cross Toolchain
   - Building or fetching a RISC-V cross-compilation toolchain.
   - Required versions and environment setup.
   #### Building the WorldGuard-Enabled QEMU
   - Building QEMU with required patches for WorldGuard support.
   - Notes on configuration flags and validation of WorldGuard support.
   #### Building the Patched OpenSBI
   - Compilation of an OpenSBI fork with additional code to support WorldGuard boot flow.
   - Integration of Secure OS handoff from M-mode.
   #### Building a WorldGuard-Aware Linux Image
   - Configuration options for enabling WorldGuard awareness in Linux.
   - Applying required patches, configuring the kernel, and generating an image.
   #### Building Secure OS
   - Step-by-step instructions on configuring and compiling the Secure OS kernel.
   - Overview of CMake-based build, memory layout specification, and output binaries.
   - Preparing and including predefined TA manifests.
   #### Assembling Bootable Image
   - Integrating OpenSBI, Linux, and Secure OS into a QEMU-bootable image.
   - Image layout overview and loading addresses.
  ### Example Trusted Application: Simple Arithmetic TA
  - Presents the practical development of a basic trusted application that offers simple arithmetic operations, to serve as a demonstrative example.
   #### Writing a Simple Trusted Application
   - Creating a minimal TA: hello world service (or similar).
   #### Defining TA Manifest for Capability Model
   - Creating a manifest describing required permissions and object handles.
   - Integrating the TA in root task’s manifest for launch.
   #### Building the Trusted Application
   - Using build system to compile and link the TA.
   - Output format (ELF) and file placement for boot.
  ### Demonstration and Execution
  - This subsection illustrates booting full system with communication between Linux and Secure OS via the sample TA.
   #### Booting the System
   - Launching QEMU with appropriate flags and verifying CPU/world isolation.
   - Boot logs highlighting OpenSBI handoff and Secure OS initialization.
   #### Initializing the Linux Driver for Secure OS Communication
   - Loading the Linux kernel module for Secure OS communication.
   - Debug output validating setup of shared communication queues.
   #### Opening a Session to Trusted Application
   - Using the TEE Client API to initialize a session to the sample TA.
   - Debug logs showing session creation and rendezvous with Secure OS.
   #### Invoking the TA Function and Receiving Response
   - Sending invoke command (e.g., multiplication request) from Linux-side.
   - Observing execution through debug output from Secure OS and TA.
   - Logging TA's output and Linux-side response resolution.
   #### Visualizing Capability Enforcement (Optional)
   - Showing an attempt to call unauthorized method or access restricted handle.
   - Logging access denial via kernel enforcement logic.
   #### Debugging and Logging Support
   - Tail of secure log buffer dumped through secure syscall.
   - Logging from TAs printed using standard I/O libraries.

 ## Security Analysis
 - In this section, we evaluate the security posture of the Secure OS by analyzing the resilience of its architecture to a variety of threats according to the threat model defined in Chapter 2.
 - For each scenario, we describe the setup, the simulated or real attack, and the system's actual response.
 - The analysis is grounded in practical testing on an emulation environment backed by software instrumentation and tracing.
  ### Resilience against Normal World Attacks
  - This subsection evaluates the Secure OS against a potentially hostile rich OS (Linux) running in the Normal World.
   #### Unauthorized Access to Secure Memory
   - Attack Setup: Linux kernel driver attempts to read/write physical page mappings belonging to Secure OS.
   - Observation: Memory protection enforced with World Guard prevents access; bus errors raised correctly.
   #### Unauthorized Access to Secure OS/TA Code
   - Attack Setup: Linux attempts to scan Trusted Application code or Secure OS binary via /dev/mem or similar - - methods.
   Observation: Memory remains inaccessible due to hardware separation and lack of mapping in the normal world.
   #### Attempts to Corrupt Shared Memory Queues
   - Attack Setup: Malformed or oversized requests injected into shared communication pages.
   - Observation: Secure OS validates request format; invalid requests rejected and logged, avoiding buffer overflows.
   #### Exploiting CWC Protocol (Cross World Communication)
   - Attack Setup: Linux attempts to race against a Secure OS processing request by overwriting in-flight messages.
   - Observation: Lock-free queue only uses relative indexes in accesses, so it prevents reads and writes from unexpected pointers. So if index is corrupted (out of bounds) - it will be ignored
  ### Resilience against Buggy Trusted Applications
  - Important to ensure Secure OS protects itself even in case of flawed Trusted Applications.
   #### Inter-TA Isolation
   Attack Setup: One TA attempts to access memory or channel of another TA.
   Observation: Physical and logical isolation enforced; failed access due to missing capabilities; Secure OS rejects request.
   #### Capability Enforcement Engine
   Attack Setup: Malformed syscall using an invalid or forged handle; fuzzing against the Secure OS syscall interface.
   Observation: Consistent rejection due to absence of capability introspection in root task's manifest.
   #### TA Resource Misuse Protection
   Attack Setup: Malicious or buggy TA requests excess memory, opens too many handles.
   Observation: Secure OS enforces per-task quotas; resource exhaustion attempts fail gracefully.
   #### Side-Channel Attacks
   Scenario: Timing variation attacks on Secure OS execution; cache access pattern leakage.
   Observation: Not possible separation due to architecture-level isolation (e.g., cores/cache).
  ### Additional Attack Scenarios and Limitations
  - This section groups attacks that are currently outside the full mitigation scope or require future hardening efforts.
   #### Physical Attacks
   Scenario: Direct DRAM probing, bus sniffer or glitching attacks on OTP or memory controller.
   Observation: Physical attack resistance not yet applied; relies on external platform features.
   #### Complexity of Trusted Computing Base (TCB)
   Exploration: How large and auditable is the TCB?
   Observation: Secure OS kernel remains minimal and auditable, but Trusted Applications contribute to overall TCB and must be vetted.
   #### Chain of Trust Attacks
   Scenario: Malicious OpenSBI image or Secure OS loader.
   Observation: Evaluation based on boot integrity; Secure Boot implementation assumed but not fully integrated in prototype.

 ## Performance Evaluation
 - This section evaluates the runtime behavior, efficiency, and resource usage of the Secure OS, with emphasis on inter-world communication, Trusted Application (TA) execution overhead, and system resource constraints in a constrained RISC-V environment.
 - Measurements are taken on an emulated platform using WorldGuard-enabled QEMU.
  ### Latency of Secure OS Operations
  - This subsection presents a detailed breakdown of the latency involved in interaction between the Normal World (Linux) and the Secure World (Secure OS), following the GlobalPlatform API lifecycle: session open, command invocation, session close.
  - Note: All latency measurements should include mean, standard deviation, and max/min values with multiple runs.
   #### Session Open Latency
   - Time required to open a session to a TA via `TEEC_OpenSession()`
   - Includes context switch, message construction, capability validation, and TA instantiation
   - Factors influencing latency (TA manifest size, cold start vs. warm start)
   #### Command Invocation Latency
   - Latency of `TEEC_InvokeCommand()` to a previously opened TA Session
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

 ## Future Work
 - This chapter outlines promising directions for extending and improving the Secure OS platform for the RISC-V WorldGuard architecture. It includes technical enhancements, additional security features, hardware support expansions, and rigorous verification procedures.
  ### Advanced TA Features
  - This section discusses enhancements to the Trusted Application (TA) framework that would allow TAs to offer more sophisticated services while still retaining minimal TCB and robust isolation.
   #### Secure Storage
   - Introduce support for tamper-resistant persistent storage to enable confidential data access, including sealed key-value storage SDK for TAs.
   #### Attestation
   - Add support for both local and remote attestation with cryptographic proof of measurement and TA identity, potentially backed by a platform Root-of-Trust chain.
   #### Root of Trust
   - Define or integrate a hardware/software Root of Trust, including secure provisioning mechanisms and interaction with system boot.
   #### Cryptographic Services
   - Provide Trusted Applications with a standardized, hardware-accelerated crypto runtime offering: symmetric encryption/decryption, asymmetric crypto, hashing, digital signatures, and secure RNG.
   #### Porting to Real RISC-V Hardware with WorldGuard
   - Move from QEMU-based evaluation to physical RISC-V hardware that implements the WorldGuard extension for real-world performance measurements and evaluation under physically observable systems.
   - Identify WorldGuard-compatible silicon platforms
   - Implement board-specific OpenSBI and bootloader adaptations
   - Hardware debugging framework integration
  ### Performance and memory
   #### Multicore Support for Secure World
   - Extend the Secure OS runtime to allow execution on multiple cores, introducing challenges around synchronization, inter-core TA instance affinity, and capability tracking in a multithreaded environment.
   - Secure world scheduling policy for multiple harts
   - Shared state consistency between cores
   - Scalability tuning and bottleneck analysis
   #### Dynamic TA Loading
   - Introduce support for on-demand loading and unloading of TAs to reduce secure world memory usage and enable more complex applications.
   - TA cryptographic signature verification before loading
   - TA manifest validation and integration with runtime capability system
   - Secure memory isolation upon load/unload
  ### Security enhancments
   #### Formal Verification of Secure Components
   - Augment Secure OS with formal verification techniques for core components, especially the kernel, capability system, and secure IPC primitives, in order to reduce the Trusted Computing Base risk and improve assurance.
   - Kernel API model verification
   - Memory safety guarantees via static analysis
   - Proofs for capability propagation correctness
   #### Enhanced Hardening Against Attacks
   - Additional work on increasing robustness of the Secure OS and its communication mechanisms against advanced offensive threats.
   - Side-channel mitigation techniques (cache partitioning, temporal fuzzing, constant-time algorithms)
   - Memory fault injection resilience
   - Kernel fuzzing and semi-automated stress testing
   - System defenses against speculative execution and timing inference

---

