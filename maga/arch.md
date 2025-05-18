# Abstract

# Table of contents

# Введение
 ## Актуальность
  - sensual user data
  - emergence of TEEs
  - emergence of OS to server Trusted Execution Environment
 ## Цель исследования
  - create Secure OS to server TEE
 ## Задачи исследования
  - analysis of exising TEEs and Secure Operating Systems
  - Designing an capability based security model
  - Designing an Secure OS
  - Implementing an Secure OS with capability based security model
 ## Объект исследования
  - Trusted Execution Enviroments on CPUs with RISC-V architecture
 ## Предмет исследования
  - Secure Operating Systems on CPUs with RISC-V architecture
 ## Методы исследования
  - Take Halip's methods
 ## Научная новизна
  - Creation of Secure OS for CPUs with RISC-V Architecture
 ## Практическая значимость работы
  - Serving a Trusted Execution Environment for WorldGuard Extension
 ## Достоверность полученных результатов и выводов
  - Reliability is based on Experemental results
 ## Положения выносимые на защиту
  ### Secure OS
 ## Публикации автора по теме
  ### bruh
 ## Структура работы
  ### chapter 1:
   ####
  ### chapter 2:
   ####
  ### chapter 3:
   ####
  ### chapter 4:
   ####

# Chapter 1: Foundations and Motivation for an Open Secure OS on RISC-V
 ## Background and Motivation
  ### Background on Trusted Execution Environments
   #### Introduction to Trusted Execution Environments
   - Modern device execution paradigms: Today’s devices — from smartphones to IoT and servers — often run more than one operating system concurrently on the same processor.
   - Parallel operating environments: Typically, there is a Normal Execution Environment where the main OS and applications run, and a separate Secure Execution Environment designed to protect sensitive code and data.
   - Purpose of this separation: Provides hardware-enforced isolation that allows sensitive computations (e.g., cryptography, DRM, payment processing) to occur securely without interference from normal system components or potential attackers.
   - the normal OS manages everyday tasks, but sensitive operations happen inside a protected environment.
   #### Evolution of Trusted Execution Environments
   - Brief history of TEEs in modern computing
   - dedicated secure coprocessors or special hardware modules (e.g., SmartCards, TPMs).
   - Comparison of different TEE implementations: typical architecture, communication methods, ecosystem maturity
   #### The Role of TEEs in Modern Security Archoitectures
   - Modern TEEs like ARM TrustZone and Intel SGX provide tightly integrated, hardware-enforced isolation within the main CPU, able to run complex trusted applications alongside a rich OS environment
   - modern TEEs support a wide range of complex applications beyond simple cryptographic tasks, including secure UI, attestation, and trusted computing on the cloud and edge
   - but regardless such popularity, there is still demand for transparent, open-source TEEs to overcome vendor lock-in and improve security audits
   - Growing needs to support more heterogeneous and multi-core environments
  ### Current State of TEEs on Proprietary Architectures
   #### Limitations of existing TEEs on Proprietary Architectures
   - Vendor Lock-in and Dependency
   - Closed and Proprietary Ecosystems
   #### Technical and Operational Challenges
   - Hardware Complexity and Rigidity
   - Fixed ISA with no scope for tailoring or extension
   #### Licensing in Proprietary Architectures
   - Economic Impact of Proprietary Licensing
   - Licensing fees increase development and production costs
   - Licensing terms can limit usage scenarios or product variants
   - Uncertainty and Risks Due to Licensing Models
   - License terms or availability may change over time
   - Potential legal and compliance risk for long-term projects dependent on vendor licenses
  ### The RISC-V Opportunity: Openness and Extensibility
   #### Open-Source Hardware and RISC-V’s Emergence
   - the majority of architectures are closed and has proprietary ISAs and implications
   - How openness promotes collaborative development, transparency, and trust
   - Growing industry adoption and ecosystem maturity
   #### The RISC-V Instruction Set Architecture (ISA)
   - Modular and extensible ISA design
   - scalable
   - free
   - RISC
   - opensource
   #### Advantages of an Open Architecture for Security
   - Reduced risk of hidden backdoors or proprietary vulnerabilities
   - Community-driven security audits and improvements
   - Facilitates experimentation with custom security extensions

 ## Problem Statement
  ### Current State of TEEs on RISC-V Architecture
   #### Current Status of RISC-V’s Security Ecosystem
   - Immaturity of RISC-V Security Ecosystem
   - Fragmented and Limited Software Support
   - Lack of mature, standardized Secure OS implementations and TEE management tools
   - Early-stage experimental projects with limited stability and adoption
   #### WorldGuard State
   - World Guard are recent and still evolving
   - depite not having ratified specification, WG has complete set of features that support secure enclaves
   - but there is no software support of TEE over WG enclaves like Secure OS
  ### The Emerging Need for Open and Flexible Solutions
   #### Deficiency of Open TEE Standards and Interfaces for RISC-V
   - Current TEEs lack public source code or are tightly coupled to vendor hardware or platforms.
   - Difficult for external developers to adopt, audit, or extend.
   #### Motivation for an Open-Source Trusted Operation System
   - need of Open Secure OS for RISC-V
   - To provide a minimal trusted computing base, flexible scheduling, and lifecycle management of trusted applications
   - Facilitates seamless and secure communication channels between normal and secure worlds
   - Establish transparent, extensible, and standard communication protocols that can evolve with hardware capabilities
   #### Ecosystem Benefits
   - Democratizes secure computing capabilities on RISC-V platforms
   - Encourages research, community-driven security audits, and faster innovation cycles
   - Lowers costs and removes vendor lock-in risks, favoring adoption in academia, startups, and industry alike

 ## Relevance and Applications
  ### Rapid Growth of RISC-V in Commercial and Industrial Domains
   #### Wide Deployment Across Diverse Product Areas
   - RISC-V has seen accelerating adoption in real-world commercial products, including
   - Industrial control and factory automation systems
   - On-premise and edge cloud computing platforms
   - Networking equipment and embedded consumer electronics
   - Highlights that RISC-V is no longer just experimental or academic; it’s establishing a growing footprint
   #### Absence of Security-Integrated Products to Date
   - Despite broad usage, existing RISC-V products largely lack integrated security features or trusted execution environments
   - Contrasted with ARM and x86 ecosystems where security technologies (TrustZone, SGX, SEV) are deeply embedded in many products
   - This absence is partly due to RISC-V’s relative architectural youth and evolving security extensions
   #### Motivation to Develop Secure RISC-V Solutions
   - Strong market motivation: given how critical security is in analogous ARM/x86 use cases, similar secure RISC-V products will inevitably emerge
   - Early engagement is crucial to shape and lead this upcoming market
   - a very good opportunity to provide open-source secure OS and TEE stack harnessing RISC-V-specific features (e.g., World Guard).
  ### Expanding Security Requirements in Modern Computing
   #### Essential Security Functions in Contemporary Products
   - Security features like cryptographic key management, secure boot, and firmware integrity are baseline expectations today in mobile devices, automotive electronics, and cloud servers
  #### RISC-V’s Untapped Potential for Secure Applications
  - Opportunity for RISC-V to enter markets currently dominated by proprietary ISAs with an open and transparent security story
  - Potential applications demanding trustworthiness:
  - secure personal devices
  - automotive systems
  - confidential cloud workloads
  - IoT ecosystems
  - Open-source secure components can drastically lower barriers for adoption and innovation

 ## Comparison with Existing Architectures
  ### ARM TrustZone: Centralized Secure World Model
   #### Overview
   - Hardware-enforced split between Normal World and Secure World running on the same CPU cores
   - Secure World hosts a Secure OS managing Trusted Applications
   #### Advantages
   - Mature ecosystem with broad adoption (mobile, embedded)
   - Efficient context switching between secure and normal worlds
   - Well-supported industry standards (e.g., GlobalPlatform TEE)
   #### Disadvantages
   - Centralized model: single secure world may become a bottleneck
   - Limited scalability on multi-core systems (single Secure World across cores).
   - Security boundary depends strongly on software (Trusted OS) correctness.
  ### Intel Software Guard Extensions (SGX): Enclave-Based Isolation
   #### Overview
   - Enclaves are isolated regions of memory with hardware enforced encryption and integrity protection
   - Applications selectively isolate sensitive code/data inside enclaves with fine granularity
   #### Advantages
   - Flexible on a per-application basis; multiple enclaves can co-exist
   - Strong memory encryption and attestation capabilities
   - Does not require a separate secure OS
   #### Disadvantages
   - Limited enclave size and complexity constraints
   - Complex programming model and compatibility issues
   - Vulnerabilities found in side-channels and speculative execution attacks
  ### AMD Secure Encrypted Virtualization (SEV)
   #### Overview
   - Encrypts entire VM memory transparently to protect guest VMs from a compromised hypervisor
   - Targets cloud scenarios with multi-tenant isolation
   #### Advantages
   - Seamless protection for virtual machines with little change to guest OS.
   - Strong hardware encryption of memory with real-time decryption
   #### Disadvantages
   - Focused on virtualization; not suitable for all embedded or mobile scenarios
   - Trust anchored primarily on hypervisor and hardware
   - Limited granularity compared to enclave or secure world models
  ### RISC-V’s World Guard Extension: Decentralized Isolation
   #### Overview
   - Hardware extensions enabling memory and execution partitioning at finer granularity than TrustZone
   - Supports multiple isolated domains (“worlds”) potentially running in parallel on multi-core systems
   #### Advantages
   - Decentralized design enhances scalability and flexibility for multi-core/multi-tenant use cases
   - Open ISA allows community-driven security extensions and transparent implementation
   - Enables novel Secure OS designs with tailored isolation policies
   - WorldGuard has a superset of capabilities compared with TrustZone, so if only two worlds used - this will closely match TrustZone model and GlobalPlatform TEE API can be used with WorldGuard
   #### Disadvantages
   - Early Stage of Standardization and Development: lacking wide hardware and software support
   - Limited Ecosystem and Tooling Support: Unlike ARM TrustZone or Intel SGX, which have mature SDKs, secure OSes, middleware, and developer tools, World Guard currently lacks a rich ecosystem
   - Need for Accompanying Secure Software Stack: Hardware support alone is insufficient; a complete trusted execution environment requires well-designed Secure OS, runtime environments, drivers, and APIs — these are still under development or experimental for World Guard
   - Adoption and Interoperability Challenges: Fragmentation or vendor-specific variations could impede standardization and cross-platform TEE portability
  ### Summary and Comparative Analysis
   - *Side-by-side comparison table or structured summary across key dimensions*
   - ...

 ## Related Work
  ### Academic Research on RISC-V TEEs
   #### Survey of recent research on trusted execution for RISC-V
   - some papers on RISC-V, like
   - SoK: Understanding the Prevailing Security Vulnerabilities in TrustZone-assisted TEE Systems
   - Enclave-Aware Compartmentalization and Secure Sharing with Sirius
   #### Gaps identified in academia researches
   - Lack of ...
  ### Proprietary vs- Opsn-Source TEE Solutions
   #### Alibaba Cloud Link
   - tightly integrated with Alibaba ecosystem
   - used in:
   - Alibaba Cloud
   - IoT Platform
   - IoT Edge Computing
   #### Apple Secure Enclave
   - Hardware-backed TEE in Apple SoCs
   - used in:
   - all apple devices: phones, TVs, ...
   #### Huawei iTrustee
   - Platform security solution deployed across Huawei devices; proprietary and closed ecosystem
   - used in:
   - all huawei devices: phones, TVs, ...
   #### Google Trusty
   - Android’s open-source TEE OS managed by Google
   - used in:
   - google pixel
   - chromebook
   #### Samsung TEEgris
   - Samsung's own TEE implementation
   - used in:
   - all samsung devices: phones, TVs, ...
   - also licensed to automotive OEMs
   #### SiFive's private Secure OS for WorldGuard
   - proprietary
   - ...
  ### Complementary Papers
   #### Linux Integration for Secure OS Communication
   - Prior art and current solutions enabling Linux driver support for TEE communication, IPC, and session management
   #### TEE Interface and OpenSBI Extensions
   - Existing works on modifying trusted firmware (like OpenSBI) to support new RISC-V security extensions (including WorldGuard)

---

# Chapter 2. Core Principles of Trusted Execution Environment and Threat Model
 ## TEE Overview
  ### Definition and Core Principles
   #### Trusted Execution Environment
   - descrption: secure area of a main processor ...
   - list core principles
   #### Isolation
   - separaion on Rich Environment and Trusted Environment
   #### Integrity
   - guarantees that the code and data within it are untampered
   #### Confidentiality
   - Data and code inside the TEE are kept confidential
   - No software outside the TEE can access data inside the TEE
   #### Secure Storage
   - storage of sensitive data even when powered off
   #### Attestation
   - integrity approval from remote server
   #### Trusted Execution
   - Only authorized and verified code can run within the TEE
   #### Minimal Trusted Computing Base (TCB)
   - minimizing ccomponents that must be trusted
   - root of trust

  ### Security Requirements and Design Goals
   #### Core Components
   -
   #### Isolated Execution Unit
   - dedicated CPU core
   - or isolated CPU state
   #### Normal World
   - where Rich Execution Environment runs
   #### Secure World
   - where Trusted Execution environment runs
   #### Trusted Applications
   - Applications running inside the TEE that perform sensitive tasks
   #### Secure Storage
   - data stored outside TEE and always encrypted
   - but keys can never leave TEE
   #### Memory Isolation
   - RAM is divided to Normal, Secure and Shared areas
   - Normal area can not be accesed by TEE
   - Secure area can not be accessed by REE
   - only shared area can be used to transfer data
   #### Cryptographic Engine
   - hardware or software module providing secure cryptographic functions
   #### Attestation Mechanism
   - hashes of TEE components signed with secure keys
   #### Secure APIs
   - Interfaces through which normal applications or the Rich Execution Environment can request services from the TEE

 ## Threat Model
  ### Normal World Assumptions
   #### untrasted OS
   - The Normal World is assumed to be fully untrusted
   - Normal World can be compromised by malware, user-level or kernel-level rootkits
   - No sensitive data can be placed in Normal World
   #### Hostile OS
   - The Normal World may attempt to attack the TEE by using privileged access
   - read or tamper with TEE memory
   - intercept or replay communication with the TEE
   - Launching DoS (Denial of Service) attacks against TEE services
   #### Limited Visibility
   - The TEE assumes that the Normal World cannot access TEE data
   #### Control over Non-secure resources
   - Normal World is responsible for forwarding requests between trusted applications in the TEE and external sources / user
   #### Schedule priorities
   - The Normal World may refuse to schedule or service TEE requests
   - so by desigh - not Normal world should call TEE, but TEE should check requests by itself
  ### Attack vectors
   #### Direct Memory Access Attacks
   - If DMA engines (e.g., from peripherals) are not properly restricted, they might access Secure World memory
   - Usage of IOMMU is crucial
   #### Side-Channel Attacks
   - Exploit indirect information leakage (timing, power, electromagnetic radiation, cache behavior)
   - like Meltdown, Spectre, Red Bleeding
   - Constant-time algorithms in the TEE, side-channel resistant hardware, noise introduction, cache partitioning or flushing techniques should be used
   #### Physical Attacs
   - Physical attacs Using power glitches, clock glitches, voltage variations, or electromagnetic interference to cause faults
   - Physical access combined with Normal World privileges could help mount attacks like probing or injecting malicious signals
   #### API Exploitation
   - Malicious Normal World software crafts malicious inputs or sequences of calls to the Secure World, causing buffer overflows, logic bugs, or privilege escalation within the Secure World
   - Strict input validation robust secure OS design should be used
   #### Man-in-the-Middle Attacks
   - The communication channel between Normal and Secure World is a major interface
   - Normal World manipulates, replays, or drops messages to confuse or exploit Secure World services
   - Use cryptographic nonce, session tokens, to validate integrity and freshness
   #### Denial of Service Attacs
   - Flooding Secure World with calls, starves it of resources, or blocks communication
   - Rate limiting, watchdog timers, graceful degradation
   #### Boot and Firmware Attacks
   - Compromise of bootloader or firmware update process can undermine Secure World trust (load malicious secure OS or patch trusted apps).
   - Secure boot, cryptographic verification of firmware and Secure World images should be used

 ## World Guard Extension
  ### Overview of the World Guard Concept
   #### ...
   - *chapter 1 from wg spec*
  ### RISC-V ISA WorldGuard
   #### ISA WorldGuard Extensions
   - *chapter 2.0 from wg spec*
   #### WorldGuard CSRs
   - *chapter 2.1*
   #### One world per hart
   - *chapter 2.2*
   #### Response to permission violations
   - *chapter 2.5*
  ### Non-ISA WorldGuard Hardware Platform Components
   #### WorldGuard Markers and Checkers
   - *chapter 3.0*
   #### Generic WG Checker
   - *chapter 3.1.0*
   #### Configuration Register Memory Map
   - *chapter 3.1.1*
   #### Rule Slot Format
   - *chapter 3.1.2*
   #### Error-reporting registers
   - *chapter 3.1.4*
   #### Operation of the Checker
   - *chapter 3.1.5*
   #### Checker Reset
   - *chapter 3.1.6*

 ## Boot Sequence and Chain of Trust
  ### RISC-V Boot Sequence Overview
   #### Background on RISC-V System Booting
   - Explains the general concept of booting in RISC-V systems. This includes initialization of hardware, loading of firmware components, and establishing the runtime environment for subsequent software layers. It discusses the challenges and constraints in secure boot design.
   - An introduction outlining the overall boot process in the RISC-V system integrating both the Secure OS and the Rich OS (Linux)
   #### First Stage Bootloader (FSBL)
   - Describes the role of the First Stage Bootloader in the secure boot process
   - It is responsible for initial hardware setup, integrity verification of subsequent images, and loading the next boot stage into memory
   - This stage is often stored in One-Time Programmable (OTP) memory, establishing the Root of Trust.
   #### OpenSBI Initialization
   - Details how OpenSBI initializes the RISC-V Supervisor Binary Interface and prepares the system for both the Secure OS and the Rich OS
   - This section explains how OpenSBI manages multi-core initialization while isolating the first core for the Secure OS.
   #### Secure OS Startup
   - Describes the booting and initialization of the Secure OS on the first core
   - setup of secure and non-secure memory
   #### Rich OS Startup
   - Outlines the initialization and booting of the Rich OS (Linux) on the remaining cores
   - Explains how linux starts and initializes a driver for communication with Secure World
   - Then continue booting as normal
  ### Chain of Trust
   #### Principles of Secure Boot and Chain of Trust
   - Introduces fundamental concepts behind establishing a chain of trust
   - where each stage of the boot process verifies the integrity and authenticity of the next
   - Explains how root keys and cryptographic signatures enforce this trust model.
   #### RISC-V Root of Trust
   - Discusses hardware and firmware components acting as roots of trust on RISC-V platforms
   - Includes details on embedded ROM or OTP memory used for storing immutable secrets and the first authenticated boot stage.
   #### One-Time Programmable (OTP) Memory
   - Examines the use of OTP memory technologies in storing cryptographic keys, bootloader code, or other critical data that forms the immutable basis of system trust
   - Explains how this hardware feature prevents modification and enhances security guarantees.
   #### Secure Boot Implementation
   - describes that secure boot is out of scope of this project, but that Secure OS is implemented with consideration of Chain Of Trust, and that there is no limitaion of implementing it in future work

---

# Chapter 3: Design and Implementation of the Secure Operating System**

 ## Interface Considerations**
 - This section outlines the critical interface design choices for the Secure OS, encompassing communication with the Normal World, interaction with Trusted Applications (TAs), and the underlying system call mechanisms.
 - These choices significantly impact the system's usability, security, and portability.
 - We evaluated several approaches for each interface, aiming for a balance between established standards, security principles, and the specific requirements of our monolith architecture.
  ### TEE Client API: Inter-World Communication Interface
  - This subsection discusses the API exposed by the Secure OS to the Normal World (Linux) for requesting TEE services.
  - The choice of this API is crucial for compatibility and ease of integration for Normal World applications seeking to utilize secure functionalities.
   ####  Analysis of Global Platform TEE Client API**
   - The Global Platform (GP) TEE Client API is an industry-standard specification for communication between a client application in the Rich OS (Normal World) and a Trusted Application in the Secure OS.
   - We analyze its comprehensive nature, ubiquity, and how its well-defined semantics for session management, shared memory, and command invocation could benefit our system.
   - We considered its suitability for our OS, potentially implementing a well-defined subset.
   #### Comparison with Existing TEE Implementations (e.g., OP-TEE)
   - We reviewed existing TEE solutions, such as OP-TEE, which largely implements the Global Platform API.
   - This comparison helped understand common practices, potential implementation challenges, and the de-facto expectations for a TEE client interface.
   - The resulting API was influenced by OP-TEE API, because it's simplicity, but sufficient functionality
   #### Exploration of Custom or Lightweight API Alternatives
   - The option of designing a bespoke, experimental, or minimalist API tailored specifically for our OS and the World Guard extension was considered.
   - This could offer simplicity and a smaller attack surface but would sacrifice standardization and portability, requiring custom client libraries and tooling.
   #### Rationale for Adopting a Global Platform-based API Subset
   - Following the evaluation, we concluded that adopting a subset of the Global Platform TEE Client API provides the best balance
   - It offers standardization and familiarity for developers, leveraging existing concepts, while allowing us to tailor the implementation to out OS resource constraints and security model.
   - This decision facilitates future interoperability and adoption.
  ### Trusted Application Interface Considerations
  - This subsection details the considerations for the interface provided to Trusted Applications running within the Secure OS.
  - This includes how TAs request services from the Secure Kernel and access any provided libraries.
   #### TA Development Model: Libraries vs. Direct Syscalls
   - We considered whether TAs should primarily interact with the Secure OS kernel via direct system calls or through a higher-level abstraction, such as a standard C library (libc) tailored for the secure environment
   - A library approach enhances portability and ease of development for TA authors, while direct syscalls offer finer control at the cost of complexity.
   #### Defining the Scope of a TA Standard Library
   - The design of a standard library for TAs requires careful consideration of essential functionalities (e.g., basic I/O for debugging, string manipulation, memory management, cryptographic operations)
   - The interface to this library forms a key part of the TA development experience.
   #### Secure OS Kernel Syscall Interface Considerations
   - This subsection addresses the design of the low-level system call interface, which is the fundamental boundary between Trusted Applications and the Secure OS kernel. This interface must be minimal, robust, and enforce the system's security policies rigorously.
   #### Principles for Syscall Design in a Secure OS
   - For a Secure OS, the syscall interface should be minimal, well-defined, and primarily focus on inter-process communication (IPC), capability management, and basic resource control.
   - We evaluated how these principles apply to secure system calls, ensuring each entry point is essential and strictly validated.

 ## System Architecture Overview
  ### High Level Component Diagram
   #### ...
  ### Interaction Model between components
   #### ...
  ### TA Lifecycle
   #### Creation
   #### Compute
   #### Teardown

 ## World Guard Integration
  ### WorldGuard Configuration
   #### World Configuration
   - Two-World Design
   #### WorldGuard Checker Configuration for Secure Isolation
   - Secure RAM Slots configuration
   - enclave partitioning
  ### Integration in the Secure OS
   #### Error reporting
   #### Managing World Transitions
   - Entry/Exit to Secure World)
   #### Communication Mechanism
   - Shared Memory Pages with permissions for both worlds

 ## Secure Boot Process and Initialization
  ### Secure OS Early Initialization
   #### OpenSBI Handover
   #### Kernel Mapping
   #### Firsr Kernel Relocation
   #### Enable MMU
  ### Secure OS Initialization
   #### Register Console
   #### Initialize Page Tables
   #### Second Kernel Relocation
   #### Initialize Trap Handler
   #### Initialize Timers
   #### Initialize Page Allocator
   #### Initialize Slab Allocator
   #### Initiazlie Scheduler
   #### Initialize Root Task
   #### Initialize Normal World Communication Channel
   #### Initialize Trasted Applications
  ### Rich OS Initialization
   #### Initialization by OpenSBI

 ## OpenSBI modifications
  ### ...

 ## Cross-World Communication
  ### Shared Memory Queues
   #### LockFree Queue Algorithm
   #### Shared Memory Ring Buffers
   #### Requests Queue
   #### Responses Queue
  ### IPI Based Signaling
   #### RISC-V IPI Mechanism
   #### Normal to Secure world signaling
   #### Secure to Normal world signaling

 ## TEE API
  ### Global Platform API
   #### Introduction to Global Platform API
   - *introduction from OP-TEE Global Platfrom API spec*
  ### TEE Client API
   #### TEE Contexts
   - *contexts chapter*
   #### TEE Sessions
   - *sessions chapter*
   #### TEE Shared Memory
   - *shared memory chapter*
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
   #### printf
   #### sprintf
   #### vprintf
  ### Strings Standard Library Specification
   #### string functions
  ### Math Standard Library Specification
   #### algebraic functions
   #### thrigonometry functions
   #### complex math functions
  ### Crypto Standard Library Specification
   #### crypto functions
   #### hashes
  ### Communication Standard Library Specification
   #### shared memory
   #### pipes
  ### Concurrency Standard Library Specification
   #### mutexes
   #### spinlocks

 ## Implementation Challenges and Optimizations
  ### Performance vs. Security Trade-Offs
  ### Memory Footprint optimizations
  ### Debugging Considerations
  ### Build System and Packaging for TAs

 ## Summary of Implementation
  ### ...

---

# Chapter 4: Evaluation and Security Analysis

 ## Software Stack Setup
  ### Emulations Enviroment
   #### QEMU with WorldGuard Support
   #### QEMU modifications
   #### QEMU Configuration
  ### Linux
   #### Linux with WorldGuard Support
   #### Linux modifications
   #### Linux Configuration
   #### Linux Image
  ### Build System
   #### Cmake configuration
   #### Cmake build system design
  ### CI Integration
   #### ...

 ## Demonstration of Secure OS Functionality
  ### Building Porcess
   #### Clone repos
   #### building toolchain
   #### building QEMU
   #### building OpenSBI
   #### building Linux
   #### building Secure OS
  ### Example of Simple Trusted Application service
   #### creating simple application
   #### building TA
  ### Demostration of TA Execution
   #### booting the system
   #### starting linux driver and opening session
   #### Invoking Sample TA

 ## Security Analysis
  ### Review of Threat Model and Security Goals
   #### Potential Attack Vectors and Mitigations
   #### Compiance wth the Threat Model

  ### Resilience against Normal World Attacks
   #### Unauthorized Access to Secure Memory
   - (Prevented by World Guard/PMP)
   #### Unauthorized Access to Secure OS/TA Code
   - (Prevented by World Guard/PMP)
   #### Attempts to Corrupt Shared Memory Queues
   - (Validation, Secure OS checks)
   #### Exploiting CWC Protocol
   - (Input validation, state management)
  ### Resilience against buggy TAs
   #### Inter-TA Isolation
   - Memory
   #### Capabilities
  ### Potential Vulnerabilities and Limitations
   #### Side-Channel Attacks
   - (Brief discussion, future work)
   #### Physical Attacks
   - (Out of scope for software TEEs generally)
   #### Complexity of TCB (Trusted Computing Base)
   #### Attacks on Root of Trust

 ## Performance Evaluation
  ### Latency of operations
   #### Latency for open
   #### Latency for invoke
   #### Latency for close
  ### Communication Performance
   #### Throughtput of CWC channel
   #### TA Context switch overhead
   #### Memory footprint

 ## Conclusions

 ## Future Work
  ### Advanced TA Features
   #### Secure Storage
   #### Attestation
   #### Root of Trust
   #### Cryptographic Services
  ### Trusted User Interface Implementation
  ### Multicore Support for Secure World
  ### Formal Verification of Secure Components
  ### Dynamic TA Loading
  ### Porting to Real RISC-V Hardware with WorldGuard
  ### Hardenings against Attacks

# References

# Appendices
## Sample TA Code
## TA Manifests
## Secure OS Code
## Secure Standard Library Code
