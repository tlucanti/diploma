project background:
Secure OS is a monolith OS with capability based model, so the idea is that everything is a handle, all handles (that are listed at predefined Manifest) are given by root task to Trusted Application when it spawned. Creation of objects are done with fabric object handle. Every action to handle is checked with capability model and granted or denied.
Secure OS always works on first cpu core, other cores are left for Linux. Communication between Linux and Secure OS is provided using two shared pages. One page for requests (to secure OS) queue, second page for responses queue. It uses subset of Global Platform API as interface for communications.

Paper should have 4 chapters:

# Chapter 1: Foundations and Motivation for an Open Secure OS on RISC-V
# Chapter 2: Core Principles of Trusted Execution Environment and Threat Model
# Chapter 3: Design and Implementation of the Secure Operating System
# Chapter 4: Evaluation and Security Analysis

So, 2nd chapter is about Core Principles of Trusted Execution Environment and Threat Model
I have a draft of chapter 2:

# Chapter 2. Core Principles of Trusted Execution Environment and Threat Model
 ## TEE Overview
  ### Definition and Core Principles
   #### Trusted Execution Environment
   #### Isolation
   #### Integrity
   #### Confidentiality
   #### Secure Storage
   #### Attestation
   #### Trusted Execution
   #### Minimal Trusted Computing Base (TCB)
  ### Security Requirements and Design Goals
   #### Core Components
   #### Isolated Execution Unit
   #### Normal World
   #### Secure World
   #### Trusted Applications
   #### Secure Storage
   #### Memory Isolation
   #### Cryptographic Engine
   #### Attestation Mechanism
   #### Secure APIs
 ## Threat Model
  ### Normal World Assumptions
   #### untrasted OS
   #### Hostile OS
   #### Limited Visibility
   #### Control over Non-secure resources
   #### Schedule priorities
  ### Attack vectors
   #### Direct Memory Access Attacks
   #### Side-Channel Attacks
   #### Physical Attacs
   #### API Exploitation
   #### Man-in-the-Middle Attacks
   #### Denial of Service Attacs
   #### Boot and Firmware Attacks
 ## World Guard Extension
  ### Overview of the World Guard Concept
   #### ...
  ### RISC-V ISA WorldGuard
   #### ISA WorldGuard Extensions
   #### WorldGuard CSRs
   #### One world per hart
   #### Response to permission violations
  ### Non-ISA WorldGuard Hardware Platform Components
   #### WorldGuard Markers and Checkers
   #### Generic WG Checker
   #### Configuration Register Memory Map
   #### Rule Slot Format
   #### Error-reporting registers
   #### Operation of the Checker
   #### Checker Reset
 ## Boot Sequence and Chain of Trust
  ### RISC-V Boot Sequence Overview
   #### Background on RISC-V System Booting
   #### First Stage Bootloader (FSBL)
   #### OpenSBI Initialization
   #### Secure OS Startup
   #### Rich OS Startup
  ### Chain of Trust
   #### Principles of Secure Boot and Chain of Trust
   #### RISC-V Root of Trust
   #### One-Time Programmable (OTP) Memory
   #### Secure Boot Implementation

Starting with 2.4.1 RISC-V Boot Sequence Overview
I have a draft of thess sections:

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

write contents of sections based on draft.
If needed - maybe add some points if there is anything else to say by topic.
full structure of whole paper is in the attached file
Do not repeat yourself! Keep it concise! Do not include statements from other chapters! Write only section contents, no summary or reasoning.