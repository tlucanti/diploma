
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
   - ...
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
