
# Chapter 1: Foundations and Motivation for an Open Secure OS on RISC-V
 ## Background and Motivation
  ### Background on Trusted Execution Environments
   #### Introduction to Trusted Execution Environments
   Modern computing devices, ranging from smartphones and IoT devices to servers, often run multiple operating systems concurrently on the same processor. This parallel execution environment typically consists of a Normal Execution Environment, where the main operating system and applications run, and a separate Secure Execution Environment designed to protect sensitive code and data. The primary purpose of this separation is to provide hardware-enforced isolation, allowing sensitive computations such as cryptography, digital rights management (DRM), and payment processing to occur securely without interference from the normal system components or potential attackers.

   In this dual-environment setup, the normal operating system manages everyday tasks, while sensitive operations are executed within a protected environment. This separation is crucial for ensuring the security and integrity of sensitive data and operations. The normal world, where the main OS runs, is typically considered untrusted or less trusted compared to the secure world, which is designed to be secure and isolated.

   The concept of Trusted Execution Environments (TEEs) has emerged as a critical component in modern security architectures. TEEs provide a secure environment for executing sensitive code and handling sensitive data, isolated from the normal execution environment. This isolation is enforced by hardware mechanisms, ensuring that even if the normal world operating system or applications are compromised, the security of the sensitive operations in the secure world remains intact.

   The role of TEEs in modern security architectures is multifaceted. They not only protect sensitive information and operations but also provide a foundation for various security services, including secure storage, cryptographic operations, and secure boot mechanisms. As the need for secure processing continues to grow, driven by the increasing complexity of modern devices and the expanding range of sensitive applications, the importance of TEEs in ensuring the security and trustworthiness of computing environments becomes ever more pronounced.

   In summary, Trusted Execution Environments are a fundamental component of contemporary security architectures, providing the necessary isolation and protection for sensitive operations and data. Their hardware-enforced separation from the normal execution environment ensures the integrity and confidentiality of critical computations, making them indispensable in today's computing landscape.
   #### Evolution of Trusted Execution Environments
   - Brief history of TEEs in modern computing
   - dedicated secure coprocessors or special hardware modules (e.g., SmartCards, TPMs).
   - Comparison of different TEE implementations: typical architecture, communication methods, ecosystem maturity
   #### The Role of TEEs in Modern Security Architectures
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
