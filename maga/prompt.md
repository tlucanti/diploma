I am doing a project with 3 parts:
 1. Secure OS for RISC-V World Guard extension.
 2. Linux driver for communication with Secure OS.
 3. OpenSBI modification to support World Guard extension.

Secure OS is a monolith OS with capability based model, so the idea is that everething is a handle, all handles (that are listed at predefined Manifest) are given by root task to Trusted Application when it spawned. Creation of objects are done with fabric object handle. Every action to handle is checked with capability model and granted or denied.
Secure OS always works on first cpu core, other cores are left for Linux. Communication between Linux and Secure OS is provided using two shared pages. One page for requests (to secure OS) queue, second page for responses queue. It uses subset of Global Platform API as interface for communications.

I need to write Master's thesis abort part with Secure OS.
It should have 4 chapters:

# Chapter 1: Foundations and Motivation for an Open Secure OS on RISC-V
# Chapter 2: Core Principles of Trusted Execution Environment and Threat Model
# Chapter 3: Design and Implementation of the Secure Operating System
# Chapter 4: Evaluation and Security Analysis

So, 1th chapter is about Foundations and Motivation for an Open Secure OS on RISC-V
I have a draft of chapter 1:

# Chapter 1: Foundations and Motivation for an Open Secure OS on RISC-V
 ## Background and Motivation
  ### Background on Trusted Execution Environments
   #### Introduction to Trusted Execution Environments
   #### Evolution of Trusted Execution Environments
   #### The Role of TEEs in Modern Security Architectures
  ### Current State of TEEs on Proprietary Architectures
   #### Limitations of existing TEEs on Proprietary Architectures
   #### Licensing in Proprietary Architectures
  ### The RISC-V Opportunity: Openness and Extensibility
   #### Open-Source Hardware and RISC-V’s Emergence
   #### The RISC-V Instruction Set Architecture (ISA)
 ## Problem Statement
  ### Current State of TEEs on RISC-V Architecture
   #### Current Status of RISC-V’s Security Ecosystem
   #### WorldGuard State
  ### The Emerging Need for Open and Flexible Solutions
   #### Deficiency of Open TEE Standards and Interfaces for RISC-V
   #### Motivation for an Open-Source Trusted Operation System
   #### Ecosystem Benefits
 ## Relevance and Applications
  ### Rapid Growth of RISC-V in Commercial and Industrial Domains
   #### Wide Deployment Across Diverse Product Areas
   #### Absence of Security-Integrated Products to Date
   #### Motivation to Develop Secure RISC-V Solutions
  ### Expanding Security Requirements in Modern Computing
   #### Essential Security Functions in Contemporary Products
  #### RISC-V’s Untapped Potential for Secure Applications
 ## Comparison with Existing Architectures
  ### ARM TrustZone: Centralized Secure World Model
   #### Overview
   #### Advantages
   #### Disadvantages
  ### Intel Software Guard Extensions (SGX): Enclave-Based Isolation
   #### Overview
   #### Advantages
   #### Disadvantages
  ### AMD Secure Encrypted Virtualization (SEV)
   #### Overview
   #### Advantages
   #### Disadvantages
  ### RISC-V’s World Guard Extension: Decentralized Isolation
   #### Overview
   #### Advantages
   #### Disadvantages
  ### Summary and Comparative Analysis
 ## Related Work
  ### Academic Research on RISC-V TEEs
   #### Survey of recent research on trusted execution for RISC-V
   #### Gaps identified in academia researches
  ### Proprietary vs- Opsn-Source TEE Solutions
   #### Alibaba Cloud Link
   #### Apple Secure Enclave
   #### Huawei iTrustee
   #### Google Trusty
   #### Samsung TEEgris
   #### SiFive's private Secure OS for WorldGuard
  ### Complementary Papers
   #### Linux Integration for Secure OS Communication
   #### TEE Interface and OpenSBI Extensions

Starting with 1.3.2.1. Essential Security Functions in Contemporary Products:
I have a draft of this section:

- Security features like cryptographic key management, secure boot, and firmware integrity are baseline expectations today in mobile devices, automotive electronics, and cloud servers

write contents of section based on draft.
If needed - maybe add some points if there is anything else to say by topic.
full structure of whole paper is in the attached file
Do not repeat yourself! Keep it concise! Do not include statements from other chapters! Write only section contents, no summary or reasoning.
