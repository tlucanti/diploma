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

Starting with 2.2.1. Normal World Assumptions
I have a draft of thess sections:

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

write contents of sections based on draft.
If needed - maybe add some points if there is anything else to say by topic.
full structure of whole paper is in the attached file
Do not repeat yourself! Keep it concise! Do not include statements from other chapters! Write only section contents, no summary or reasoning.