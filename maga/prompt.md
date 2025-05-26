I am doing a project with 3 parts:
 1. Secure OS for RISC-V World Guard extension.
 2. Linux driver for communication with Secure OS.
 3. OpenSBI modification to support World Guard extension.

Secure OS is a monolith OS with capability based model, so the idea is that everething is a handle, all handles (that are listed at predefined Manifest) are given by root task to Trusted Application when it spawned. Creation of objects are done with fabric object handle. Every action to handle is checked with capability model and granted or denied.
Secure OS always works on first cpu core, other cores are left for Linux. Communication between Linux and Secure OS is provided using two shared pages. One page for requests (to secure OS) queue, second page for responses queue. It uses subset of Global Platform API as interface for communications.

I need to write Master's thesis abort part with Secure OS.
It should have 4 chapters:

# Chapter 1: Foundations and Motivation for an Open Secure OS on RISC-V
# Chapter 2. Core Principles of Trusted Execution Environment and Threat Model
# Chapter 3: Design and Implementation of the Secure Operating System
# Chapter 4: Evaluation and Security Analysis

So, 4th chapter is about Evaluation and Security Analysis
I have a draft of chapter 4:

# Chapter 4: Evaluation and Security Analysis
 ## Software Stack Setup
  ### Toolchains
  ### Emulation Environment
  ### Linux
  ### Build System
  ### CI Integration
 ## Demonstration of Secure OS Functionality
  ### Building the Software Stack
  ### Example Trusted Application: Simple Arithmetic TA
  ### Demonstration and Execution
 ## Security Analysis
  ### Resilience against Normal World Attacks
  ### Resilience against Buggy Trusted Applications
  ### Additional Attack Scenarios and Limitations
 ## Performance Evaluation
  ### Latency of operations
  ### Communication Performance
 ## Conclusions
 ## Future Work
  ### Advanced TA Features
  ### Trusted User Interface Implementation
  ### Multicore Support for Secure World
  ### Formal Verification of Secure Components
  ### Dynamic TA Loading
  ### Porting to Real RISC-V Hardware with WorldGuard
  ### Hardenings against Attacks

Starting with 4.4 Performance Evaluation:
I have a draft of structure:

 ## Performance Evaluation
  ### Latency of operations
   #### Latency for open
   #### Latency for invoke
   #### Latency for close
  ### Communication Performance
   #### Throughtput of CWC channel
   #### TA Context switch overhead
   #### Memory footprint

Create a plan of sub chapters with brief description
If needed - rename some sub chapters if there is more suitable naming, or maybe add some sub chapters or points if there is anything else to say to enhance the structure.
full draft of whole paper is in attached file
print answer in raw markdown format