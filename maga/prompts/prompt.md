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

write contents of these section based on draft.
If needed - maybe add some points if there is anything else to say by topic.
full structure of whole paper is in the attached file.
Do not write very much, only a few sentencies!
Do not repeat yourself! Do not repeat points from other chapters! Keep it concise! Write only section contents, no summary or reasoning.