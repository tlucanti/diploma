
# Chapter 2. Core Principles of Trusted Execution Environment and Threat Model
 ## TEE Overview
  ### Definition and Core Principles
   #### Trusted Execution Environment
   A Trusted Execution Environment (TEE) is a secure, isolated area within a main processor. It is designed to execute code and process data with higher levels of confidentiality and integrity than the standard operating environment, often referred to as the Rich Execution Environment (REE) or Normal World. The TEE ensures that assets, such as sensitive data and critical code, stored and processed within it are protected, even if the REE's operating system or applications are compromised. This protection is achieved through a combination of hardware and software mechanisms that enforce strong isolation between the TEE (Secure World) and the REE (Normal World). The operation and security guarantees of a TEE are founded upon several core principles, which are elaborated upon in the subsequent sections.

   #### Isolation
   Isolation in a TEE refers to the fundamental principle of separating the execution environment into two distinct domains: the Rich Execution Environment (REE), also known as the Normal World, and the Trusted Execution Environment, or Secure World. This separation ensures that operations and data within the Secure World are protected from interference or unauthorized access by software running in the Normal World, including the main operating system and its applications. Hardware-enforced boundaries are typically employed to maintain this separation, preventing code in one world from directly accessing resources or memory allocated to the other, unless explicitly permitted through controlled interfaces.

   #### Integrity
   Integrity assurances within a TEE guarantee that the code and data residing and processed in the Secure World remain untampered and in their intended state. This means that neither external entities in the Normal World nor unauthorized processes within the Secure World can modify sensitive code, such as the TEE's operating system or Trusted Applications (TAs), or critical data they manage. Integrity is typically upheld through mechanisms like secure boot, code signing, runtime memory protection, and cryptographic checksums, ensuring that only verified and authentic software components execute and that data is not maliciously altered.

   #### Confidentiality
   Confidentiality is the TEE principle ensuring that data and code within the Secure World are protected from unauthorized disclosure. This means that no software component operating outside the TEE, including a potentially compromised Normal World operating system or privileged applications, can read or access the TEE's private memory regions. Confidentiality applies to data in use (e.g., cryptographic keys being processed, sensitive application logic) and, when combined with secure storage, to data at rest. This protection is critical for safeguarding secrets and proprietary algorithms.

   #### Secure Storage
   Secure Storage is a TEE capability that provides a mechanism for persistently storing sensitive data, such as cryptographic keys, user credentials, or other confidential information, in a way that protects its confidentiality and integrity even when the system is powered off. Data stored using this mechanism is typically encrypted and integrity-protected using keys managed within the TEE. Access to this stored data is strictly controlled and mediated by the TEE, ensuring that only authorized TAs can retrieve or modify their respective sensitive information.

   #### Attestation
   Attestation allows a TEE to prove its authenticity and the integrity of the software environment running within it to a remote party. This process typically involves the TEE generating a signed report containing measurements of its hardware, firmware, TEE OS, and loaded Trusted Applications. The remote party can verify this report using a trusted key, thereby gaining confidence that they are communicating with a genuine TEE and that the software configuration is as expected and has not been tampered with. This is crucial for establishing trust in secure services.

   #### Trusted Execution
   Trusted Execution ensures that only authorized and verified code is permitted to run within the confines of the TEE. This involves mechanisms to authenticate the code (e.g., through digital signatures) before it is loaded and executed inside the Secure World. By restricting execution to known and vetted software components, the TEE maintains a controlled and secure environment, preventing the execution of malicious or untrusted code that could compromise its security objectives or the assets it protects.

   #### Minimal Trusted Computing Base (TCB)
   The Minimal Trusted Computing Base (TCB) principle dictates that the set of all hardware, firmware, and software components critical to enforcing the system's security policy should be as small as possible. By minimizing the TCB, the attack surface is reduced, simplifying security analysis and verification, and lowering the probability of vulnerabilities that could compromise the entire TEE. The TCB typically includes the secure hardware elements, secure boot firmware, the TEE OS kernel, and potentially a minimal set of core trusted services. The foundation of the TCB's trustworthiness often relies on a hardware-based Root of Trust.

  ### Security Requirements and Design Goals
   #### Core Components
   The design of the Trusted Execution Environment (TEE) is predicated on a set of fundamental components, each contributing to the overall security architecture. These components, detailed in the subsequent sections, collectively establish and maintain the trusted environment by defining its structure, operational boundaries, and interaction protocols.

   #### Isolated Execution Unit
   A fundamental requirement is an Isolated Execution Unit, which provides hardware-enforced separation for executing secure code. In this project, this is realized as a dedicated CPU core (the first core) exclusively assigned to the Secure OS. This unit ensures that operations within the TEE are shielded from direct observation or interference by untrusted software operating on other cores or in less privileged execution states.

   #### Normal World
   The Normal World (NW) represents the untrusted execution domain where the Rich Execution Environment (REE), such as a general-purpose operating system like Linux, and its applications operate. All software in the Normal World is considered potentially compromised from the TEE's perspective and is prevented by hardware mechanisms from directly accessing Secure World resources.

   #### Secure World
   Conversely, the Secure World (SW) is the hardware-protected domain where the TEE, comprising the Secure OS and Trusted Applications (TAs), executes. It is designed to be resistant to threats originating from the Normal World, guaranteeing the confidentiality and integrity of the assets it manages and the computations it performs.

   #### Trusted Applications
   Trusted Applications (TAs) are specialized software modules that execute within the Secure World to perform security-sensitive operations on behalf of Normal World clients or internal TEE services. These applications are further isolated (as per the capability model) by the Secure OS, providing functionalities such as secure data processing, cryptographic operations, or management of sensitive credentials, invoked through well-defined and controlled interfaces.

   #### Secure Storage
   Secure Storage mechanisms are required to protect the confidentiality and integrity of sensitive data when persisted outside the TEE's volatile memory, typically in Normal World storage systems. This is achieved by ensuring that all such data is cryptographically protected (e.g., encrypted and integrity-protected) using keys managed exclusively within the TEE; these keys are never exposed to the Normal World.

   #### Memory Isolation
   Robust memory isolation, enforced by hardware mechanisms like the RISC-V World Guard extension, is a critical design goal. Physical Random Access Memory (RAM) must be partitioned into distinct regions: a Secure area, accessible only by Secure World components; a Normal area, accessible only by Normal World components; and specifically designated Shared memory areas. Direct access from the Normal World to the Secure area (and vice-versa for non-shared regions) must be strictly prohibited by the hardware. The Shared memory regions, such as the inter-world communication pages, serve as the sole configured conduits for data exchange, operating under strict TEE supervision and predefined protocols.

   #### Cryptographic Engine
   A Cryptographic Engine is an essential component for providing fundamental security services within the TEE. This engine, which can comprise dedicated hardware accelerators (if available) or a rigorously vetted software library executing within the Secure World, offers functions such as encryption, decryption, hashing, digital signatures, and secure random number generation, accessible to both the Secure OS and Trusted Applications.

   #### Attestation Mechanism
   An Attestation Mechanism is required to enable the TEE to prove its authenticity and current integrity state to a challenging party (either local or remote). This involves cryptographically measuring the TEE's software components (e.g., Secure OS, TAs) and signing these measurements with a private key whose corresponding public key is part of a trusted certificate chain. This chain should be rooted in a hardware-protected secret, forming a Root of Trust for Measurement and Reporting.

   #### Secure APIs
   Secure APIs define the controlled interfaces through which Normal World software can request services from the Secure World, specifically from Trusted Applications. These APIs, such as the subset of the GlobalPlatform TEE Client API used in this project, act as rigorously controlled gateways. They are responsible for marshalling data and ensuring that all interactions are explicitly defined, validated, and authorized according to the TEE’s security policies before any service is executed within the Secure World.

 ## Threat Model
  ### Normal World Assumptions
   #### Untrusted OS
   The Normal World operating system (e.g., Linux) and all applications executing within it are fundamentally considered untrusted from the Secure World's perspective.
   This assumption acknowledges the Normal World's susceptibility to compromise by various forms of malware, including user-level or kernel-level rootkits, due to its larger codebase and attack surface.
   Consequently, no sensitive data, such as cryptographic keys or private information processed by Trusted Applications, can be stored or processed in the Normal World without robust TEE-managed protection. Code executing in the Normal World cannot be presumed to maintain its integrity.

   #### Hostile OS
   Beyond being merely untrusted, the Normal World OS is assumed to be potentially hostile, implying it may actively attempt to undermine the security an integrity of the TEE.
   It might leverage its privileged access to physical resources to attempt unauthorized access, such as trying to read or tamper with memory regions allocated to the Secure World, despite hardware protections.
   The Normal World OS could attempt to intercept, analyze, modify, or replay communications passing through the shared memory interfaces between the Normal World and the Secure World.
   Attacks on the TEE's availability, such as Denial of Service (DoS), could be initiated from the Normal World by flooding communication channels with spurious requests or by manipulating non-secure resources critical for TEE operation.

   #### Limited Visibility
   A critical assumption, enforced by hardware mechanisms such as the RISC-V World Guard extension, is that the Normal World OS has no direct visibility into the private memory regions (code and data) of the Secure OS and its Trusted Applications.
   Even with kernel-level privileges in the Normal World, the Normal World OS principal should be prevented by the hardware from directly reading, writing, or executing code within the Secure World's protected memory. This is the primary basis for TEE confidentiality and integrity guarantees.

   #### Control over Non-secure Resources
   The Normal Word retains control over all system esources not explicitly designated as secure or managed by the Secure OS. This includes most peripherals (e.g., networking, general-purpose storage, user interfaces) and system-wide resource management functions.
   As such, the Normal World OS is responsible for multiplexing access to these shared peripherals and typically acts as an intermediary for external communication required by Trusted Applications, forwarding requests from external entities or Normal World applications to the TEE and relaying results back. However, the *content* of sensitive payloads within these communications is protected by the TEE.

   #### Schedule Priorities and Control
   The Normal World OS maintains full scheduling authority over applications and tasks executing on CPU cores allocated to it. The execution priority and timing of Normal World processes, including those that will initiate communication with the TEE, are determined by Normal World OS policies.
   In contrast, the Secure OS operates with execution autonomy on its dedicated core (CPU0). Once this core is in the Secure World state, the Secure OS directly manages its own execution flow and the scheduling of any internal tasks or Trusted Applications, independent of Normal World OS scheduling decisions.
   The Secure OS polls shared memory queues for incoming requests issued by Normal World client applications. This design ensures that the TEE autonomously drives the consumption of requests, rather than being passively scheduled by or waiting for explicit signals from the Normal World for each transaction.
   While the Secure OS's internal processing on CPU0 is independent, aggressive de-prioritization of TEE client applications by the Normal World OS can delay request submission to the shared queues. This could extend the overall latency for services requiring TEE interaction, though the TEE's capacity to process requests once they are available remains unhindered by Normal World OS scheduling policies concerning the Secure OS itself.

  ### Attack vectors
   #### Direct Memory Access Attacks
   Unrestricted Direct Memory Access (DMA) engines, particularly those controlled by peripherals in the Normal World, pose a significant threat. If not properly isolated, these engines could be programmed by malicious Normal World software to arbitrarily read from or write to Secure World memory, bypassing CPU-enforced isolation mechanisms.
   A compromised Normal World driver, for instance, could instruct its associated peripheral's DMA controller to target memory regions allocated to the Secure OS or Trusted Applications, leading to confidentiality and integrity breaches.
   The employment of an Input/Output Memory Management Unit (IOMMU) is essential. The IOMMU can enforce memory protection by translating device addresses to physical addresses and checking permissions, ensuring that peripherals can only access authorized memory regions. Proper IOMMU configuration, typically managed by a trusted entity like the Secure OS or supervisor-level software, is crucial to prevent such attacks.

   #### Side-Channel Attacks
   These attacks exploit indirect information leakage from the system's physical implementation rather than direct software vulnerabilities. Information can be inferred through observations of execution time, power consumption patterns, electromagnetic emissions, or cache access patterns.
   Examples include attacks like Meltdown and Spectre, which exploit microarchitectural features (e.g., speculative execution, caches), and power/EM analysis which can reveal cryptographic keys or other sensitive data processed within the TEE.
   Mitigation strategies involve designing cryptographic operations and sensitive code paths using constant-time algorithms to avoid data-dependent timing variations. Hardware support for side-channel resistance, introduction of noise into physical emanations, and software techniques like cache partitioning or flushing between security contexts can reduce leakage, though complete elimination is often challenging.

   #### Physical Attacks
   Physical attacks involve direct interaction with the hardware to compromise the TEE. This includes fault injection techniques, such as inducing power or clock glitches, varying voltage, or using focused electromagnetic interference, to cause malfunctions in the CPU or memory, potentially bypassing security checks or corrupting critical operations within the Secure World.
   If an attacker gains physical access to the device, they might combine this with Normal World privileges to mount more sophisticated attacks, such as microprobing internal buses or cryptographic coprocessors, or injecting malicious signals directly into the hardware.
   While robust logical isolation is the primary goal of TEEs like the one extending RISC-V World Guard, physical security measures for the underlying hardware platform (e.g., tamper resistance, shielding) are necessary complements, as purely software-based TEEs cannot defend against all physical threats.

   #### API Exploitation
   The interface exposed by the Secure World to the Normal World represents a critical attack surface. Malicious or compromised Normal World software can meticulously craft inputs or sequences of API calls (e.g., to the Global Platform API subset implemented by the Secure OS) to trigger vulnerabilities within the Secure OS or Trusted Applications.
   Such an exploitation could lead to buffer overflows, integer overflows, use-after-free, logic bugs, or Time-of-Check-to-Time-of-Use (TOCTOU) vulnerabilities, potentially resulting in denial of service, information disclosure, or privilege escalation within the Secure World.
   Robust defense requires rigorous input validation for all data received from the Normal World, secure coding practices, formal verification of critical API handlers, and a robust Secure OS design adhering to the principle of least privilege, even for internal components.

   #### Man-in-the-Middle Attacks
   The communication channel between the Normal World and Secure World, such as the shared memory queues used in this project, is a prime target. The untrusted Normal World, by its nature, controls its side of this communication.
   A malicious Normal World can attempt to intercept, modify, replay, or drop messages exchanged between a Normal World client and a Secure World service or Trusted Application. This could lead to confusing the Secure World logic, transaction manipulation, or session hijacking.
   To counter these threats, communication protocols between worlds must incorporate cryptographic mechanisms such as message authentication codes (MACs) to ensure integrity, sequence numbers or nonces to prevent replay attacks, and potentially session tokens or encrypted channels to ensure freshness and confidentiality of parameters or results.

   #### Denial of Service Attacks
   The Normal World can attempt to disrupt the operation of the Secure World or specific Trusted Applications by launching Denial of Service (DoS) attacks. Given the Secure OS operates on a dedicated core, these attacks could manifest as flooding the Secure World with an excessive number of service requests, thereby exhausting CPU resources of the secure core.
   Other DoS vectors include consuming all available resources allocated for inter-world communication (e.g., filling shared memory queues faster than they can be processed), or repeatedly invoking computationally expensive operations, thus starving legitimate Secure World tasks or Trusted Applications.
   Mitigations include implementing rate-limiting mechanisms on API calls from the Normal World, using watchdog timers to detect unresponsive secure services, and designing the Secure OS for graceful degradation of non-critical services under heavy load.

   #### Boot and Firmware Attacks
   The security guarantees of the TEE fundamentally rely on a trusted boot process and the integrity of its foundational firmware and software. Compromising any stage of the boot sequence (e.g., First Stage Bootloader, OpenSBI) or the firmware update process can undermine the entire trust model of the Secure World.
   An attacker with the ability to modify these early components could load a malicious or compromised Secure OS, patch trusted applications with malicious code before they are loaded, or disable/misconfigure hardware security mechanisms like the World Guard extension itself.
   A secure boot process, anchored in a hardware Root of Trust (RoT), is essential. This involves cryptographic verification of the digital signatures of each software component in the boot chain, from the initial immutable boot ROM or OTP-stored code up to the Secure OS and Trusted Applications, ensuring their authenticity and integrity before execution.

 ## World Guard Extension
  ### RISC-V ISA WorldGuard
   #### ISA WorldGuard Extensions
   RISC-V cores (harts) that incorporate WorldGuard functionality ensure that every memory access originating from that hart is associated with a World Identifier (WID). The WorldGuard extensions provide a mechanism for different privilege levels operating on a hart to be identified with distinct WIDs.

   There are three distinct tiers of WorldGuard (WG) support for RISC-V harts.
   *   The most basic tier does not necessitate any Instruction Set Architecture (ISA) extensions; it assigns a single, fixed WID for all privilege modes on a particular hart.
   *   The second tier introduces the Smwg extension, which grants M-mode the capability to determine the WID used by privilege modes operating at lower levels.
   *   The third tier, known as the Smwgd extension, further allows M-mode to delegate the responsibility of assigning WIDs to lower-privilege modes to the [H]S-mode; this in turn incorporates the Sswg extension for [H]S-mode operations.

   All types of memory accesses, which include indirect memory operations like fetching instructions and performing page-table walks, are required to be tagged with the correct WID. From the perspective of WG permission enforcement, instruction fetches are considered equivalent to memory read operations.

   > NOTE: Bus interconnect systems usually do not differentiate between instruction fetches and general memory read operations. As a result, WG permission enforcement units (checkers) situated on the far side of the bus interconnect are incapable of distinguishing these two scenarios.

   WorldGuard's design prohibits any privilege mode from altering its own WID. The WID assigned to M-mode on a hart is configured by the external system environment and remains unchanged between system resets.

   > NOTE: It is possible for different harts within a single system to operate with distinct WIDs in M-mode.

   #### WorldGuard CSRs
   The WorldGuard extensions, namely Smwg, Smwgd, and Sswg, provide a mechanism for a hardware thread (hart) to allocate World Identifiers (WIDs) to its various privilege levels. These extensions introduce new Control and Status Registers (CSRs), which are outlined in the table that follows.

   Table 1. WorldGuard Control and Status Registers (CSRs)

   | Register     | Access     | Proposed CSR Address | Size in bits | Description                                                                                                                               |
   | :----------- | :--------- | :------------------- | :----------- | :---------------------------------------------------------------------------------------------------------------------------------------- |
   | mlwid      | RW for M   | 0x390                | XLEN         | Designates the WID to be utilized by privilege modes lower than M-mode. The Ceil(Log<sub>2</sub>NWorlds) least significant bits (LSBs) are active; all other bits are zero. |
   | mwiddeleg  | RW for M   | 0x748                | XLEN         | Represents the set of WID values that M-mode delegates to [H]S-mode, structured as a bit vector. The NWorlds LSBs are active; all other bits are zero. |
   | slwid      | RW for [H]S | 0x190                | XLEN         | Specifies the WID value to be employed in modes with lower privilege than [H]S-mode (i.e., U-mode, VS-mode, or VU-mode). The Ceil(Log<sub>2</sub>NWorlds) LSBs are active; all other bits are zero. |

   These extensions accommodate a number of worlds (NWorlds) up to the native integer register width (XLEN) of the processor.

   #### One world per hart
   With this configuration, the RISC-V hart does not undergo any modifications observable at the Instruction Set Architecture (ISA) level. Upon system reset, the hart is initialized to operate within one specific world. Consequently, every memory access initiated by this hart, irrespective of its privilege level, is marked with the World Identifier (WID) associated with that singular world. The mechanisms for allocating a hart to its world, as well as the provisions for a hart to obtain details about the WorldGuard (WG) setup, are determined by the specific design of the hardware platform.

   #### Response to permission violations
   When a hart (processor core) attempts a memory operation, whether explicit or implicit, that encounters a WorldGuard (WG) permission failure, this action may or may not result in an access-fault exception of the corresponding type (e.g., instruction-access, load-access, or store/AMO-access fault). If an access-fault exception is not triggered, the instruction initiating the memory operation can still complete (retire). However, in such cases, any writes directed to the protected physical memory address are ignored. Similarly, any memory reads from that protected location will return data that is deliberately unconnected to the actual stored value, ensuring that memory isolation is not compromised.

   NOTE:
   It is typical for secure system designs to incorporate a mechanism for notifying a designated agent whenever an illicit access is attempted. This notification is intended to occur even if the hart context itself does not experience an access-fault exception.

   NOTE:
   It is not possible to enforce a requirement that reads failing permission checks (but not causing access-fault exceptions) must return a specific, predetermined value (for instance, zero) to the hart. Such a requirement would conflict with certain cache-coherence protocols. These protocols might need to allow for the modification of data already present in the cache, even when the underlying physical memory locations are protected and previous bus transactions for those locations had returned zero.

  ### Non-ISA WorldGuard Hardware Platform Components
   #### WorldGuard Markers and Checkers
   The specific way WorldGuard is integrated into a hardware platform can differ from one system to another. A hardware platform might incorporate components known as *markers*, which are responsible for attaching World Identifiers (WIDs) to accesses initiated by hardware agents. Additionally, it may feature *checkers*, which verify access permissions at certain points along the data path leading to system resources. It is essential that all accesses aimed at a resource protected by WorldGuard are linked to a WID.

   The design of these WorldGuard markers and checkers can be specifically adapted for individual device agents and the resources they interact with, respectively.

   > *A primary motivation behind WorldGuard is to make platform-level security more cost-effective. This is achieved by customizing WID checks directly at the resources, rather than mandating that all access control information be handled in a standardized, generic manner by the initiating agents.*

   The settings for WorldGuard markers and checkers can either be permanently established during the hardware design phase or be managed through alterable (writable) states. When markers and checkers utilize dynamic configuration states, it is advisable that these states revert upon reset to a known, platform-specific configuration or to a secure default state that disallows unauthorized accesses. Typically, this dynamic configuration state is set up by trusted software during the system's boot sequence. A mechanism ought to be in place to lock this configuration after its initial setup, preventing modifications until the next system reset.

   > *Commonly, the assignment of agents and resources to their respective worlds is carried out once when the system boots. Locking these configurations subsequently provides an additional layer of security.*

   #### Generic WG Checker
   While WorldGuard (WG) checkers can be tailored for specific resource types within a system, this section presents a standardized interface for a general-purpose checker. This proposed design is suitable for direct use in scenarios that demand adaptable world configurations across extensive resource address spaces. Furthermore, it can serve as a foundational model for developing more specialized checker implementations.

   The core function of this generic checker is to oversee a predefined range of physical addresses. It permits software to set up access permissions within this specified range. The checker contains several programmable "slots." Each slot has the capability to define a "rule" that applies to a continuous segment of addresses within the checker's total monitored memory area. This rule specifies the read and write access rights for each world concerning that particular address segment.

   A checker is typically positioned at a certain point within a platform's bus system. The address space monitored by the checker may be more extensive than the actual address space of the devices it is protecting. For instance, a peripheral device occupying the address range 0x1000_0000-0x2FFF_FFFF could be secured by a checker that covers a wider range, such as 0x0_0000_0000-0x3_FFFF_FFFF. To make the checker's circuitry less complex, its entire monitored address range will generally align with a naturally aligned power-of-2 (NAPOT) sized area. The checker's designated region might be considerably larger than the address space of the devices it protects; this facilitates the reuse of the same checker design in various locations within the bus hierarchy. The checker's operation is not affected even if the system's bus matrix does not direct all addresses within the checker's full range to it.

   This part of the document focuses solely on the software programming interface for such a checker.

   *A Note on Implementation:*
   It is important to understand that complete specifications for implementation would necessitate numerous additional platform-specific details, such as those concerning bus interfaces, reset procedures, clocking mechanisms, and power management, among others.

   #### Configuration Register Memory Map
   The generic checker's configuration registers reside in a distinct area of physical memory addresses, accessible via memory mapping. This region is typically secured to ensure that only trusted software, generally during the system boot process, can modify the configuration.
   The memory-mapped interface is designed to function using individual 32-bit read and write accesses. Support for wider accesses is advisable where possible, as they can offer improved performance.

   Table 2. WG Generic Checker Configuration Register
   Offset      Bytes          Access   Name            Description
   0x00        4              R        vendor          Vendor ID
   0x04        4              R        impid           Implementation revision
   0x08        4              R        nslots          Number of rule slots
   0x0C        4                                       Reserved
   0x10        8              RW       errcause        Information about a permissions violation
   0x18        8              RW       erraddr         Address of a permissions violation
   0x20        (nslots+1)*32  RW       slot[nslots:0]  Array of slots

   The read-only vendor and impid registers offer details about the checker's vendor and its implementation version.
   The nslots parameter, also read-only, is represented as a 4-byte unsigned integer. It specifies the quantity of configurable rule slots present in the checker. A minimum value of 1 is required for nslots. It should be noted that the read-only slot[0] is not included in this nslots count.
   The errcause and erraddr registers are utilized for reporting permission violations, the specifics of which are detailed in a subsequent section.

   #### 3.1.2. Rule Slot Structure
   Every slot establishes a single rule and utilizes 32 bytes of address space, structured as detailed below:

   Table 3. WG Generic Checker Slot Configuration (32 bytes total per slot)
   | Offset | Bytes | Name                | Description                                                     |
   | :----- | :---- | :------------------ | :-------------------------------------------------------------- |
   | 0x00   | 4     | addr[33:2]        | Address for the rule                                            |
   | 0x04   | 4     | addr[65:34]       | Address for the rule (specific to RV64 systems; zero for RV32)  |
   | 0x08   | 8     | perm[nWorlds-1:0] | Read and Write permissions applicable to a maximum of 32 worlds |
   | 0x10   | 4     | cfg               | Configuration settings for the rule                             |
   | 0x14   | 12    |                     | Reserved for future use                                         |

   The addr[65:2] register stores a unique physical address for the rule. This address is shifted right by two bits, enabling the initial 32-bit register to encompass the 34-bit physical address space characteristic of an Sv32 system. It's possible for address registers to be restricted (WARL) to exclusively contain addresses that are naturally aligned to a specific protection granularity, such as 4KiB.

   The perm register contains two bits for each World Identifier (WID), defining that WID's read and write access rights for the rule. Specifically, bit 2*i signifies the read permission for WID i, while bit 2*i+1 signifies the write permission for WID i.

   The cfg register dictates the operational characteristics of the rule and is organized into distinct fields as outlined below:

   Table 4. WG Rule Configuration Register
   | Bits   | Name    | Description                                  |
   | :----- | :------ | :------------------------------------------- |
   | 1:0    | A[1:0]| Configuration for the address range          |
   | 7:2    |         | Reserved (must be written as zero)           |
   | 8      | ER    | Signal read violations as bus errors         |
   | 9      | EW    | Signal write violations as bus errors        |
   | 10     | IR    | Signal read violations via interrupts        |
   | 11     | IW    | Signal write violations via interrupts       |
   | 30:12  |         | Reserved (must be written as zero)           |
   | 31     | L     | Bit for locking the entry                    |

   The A[1:0] field determines the method used to construct the rule's address range, as detailed in the table below:

   Table 5. WG A[1:0] encoding
   | A[1:0] | Name    | Description                                                                 |
   | :------- | :------ | :-------------------------------------------------------------------------- |
   | 0        | OFF   | Rule is inactive (confers no access permissions)                            |
   | 1        | TOR   | Upper boundary of the range                                                 |
   | 2        | NA4   | Region of four bytes, naturally aligned                                     |
   | 3        | NAPOT | Naturally aligned region with a size that is a power of two, 8 bytes or larger |

   If A is set to OFF, the rule confers no access permissions.

   If A is set to TOR, the rule's addr register defines the upper limit of its address range. The lower limit of this range is provided by the addr register of the immediately preceding slot, provided that the cfg field of that preceding slot is configured as OFF or TOR. A TOR rule applies to an address y if the condition slot[i-1].addr <= y < slot[i].addr # slot[i-1].cfg = OFF or TOR is met.

   The A=NA4 and A=NAPOT encoding schemes draw from the RISC-V PMP encoding format. These allow a single addr register to specify both a base address and the size of a naturally aligned power-of-two (NAPOT) region.

   The subsequent illustration demonstrates the differences in NAPOT range encoding for a slot compared to RISC-V PMPs. Generally, the entire checker oversees a substantial, fixed NAPOT portion of the total physical address space. Address bits denoted by b signify the non-modifiable bits within addr; these bits store the base address for the complete NAPOT checker region. Modifiable address bits within the addr registers are indicated by a. The specific sizes supported by any given checker are dependent on its implementation; notably, smaller sizes, NA4 included, may not be available.

   Table 6. WG NAPOT range encoding for a checker covering a NAPOT total address range.
   | addr[65:2]     | A[1:0] | Match type and size                                   |
   | :--------------- | :------- | :---------------------------------------------------- |
   | bb…bb000…0000  |          | Address of first byte in checker range (slot[0].addr) |
   | bb…bbaaa…aaaa  | NA4    | 4-byte NAPOT range                                    |
   | bb…bbaaa…aaa0  | NAPOT  | 8-byte NAPOT range                                    |
   | bb…bbaaa…aa01  | NAPOT  | 16-byte NAPOT range                                   |
   | bb…bbaaa…a011  | NAPOT  | 32-byte NAPOT range                                   |
   | …                | …        | …                                                     |
   | bb…bba01…1111  | NAPOT  | half of checker range                                 |
   | bb…bb011…1111  | NAPOT  | all of checker range                                  |
   | bb…bb111…1111  | NAPOT  | all of checker range                                  |
   |                  |          | Address of last four-byte word in checker range (slot[nslots].addr - 4) |

   In the A=NA4 configuration, the addr value, which consists of fixed b bits and variable a bits, contains the base address for the four-byte NAPOT range.

   For the A=NAPOT configuration, a sequence of consecutive '1's in the lower bits of addr determines the size of the slot's NAPOT region. The least-significant '0' bit indicates the most-significant bit that is excluded from the slot's base address (for instance, addr[3] is zero for a 16-byte NAPOT region). The addr bits positioned above this least-significant '0' bit (comprising both fixed b bits and variable a bits) establish the base address for the slot's NAPOT region. If the highest modifiable a bit is set to '0', the slot's NAPOT range encompasses the complete address space monitored by the checker. Similarly, if all modifiable a bits are set to '1', the range also covers the entire checker's address space; in this NAPOT encoding scenario, the state of the highest a bit becomes irrelevant when all lower a bits are '1'.

   NOTE: The thermometer encoding method for NAPOT masked address bits was chosen to streamline the logic required for NAPOT address comparisons.

   Diverging further from the RISC-V PMP encoding, if a NAPOT slot serves as the base address for a TOR configuration in the subsequent higher-numbered slot, the address employed for comparison is incremented by one beyond the highest byte address within the NAPOT slot's region. That is, a TOR rule applies to an address y under the condition:
   slot[i-1].napot_top <= y < slot[i].addr # slot[i-1].cfg = NA4 or NAPOT
   where napot_top represents an address that is one greater than the highest-addressed byte in the NAPOT range of slot[i-1].

   NOTE: In comparison to the standard RISC-V PMP encoding, this enhancement diminishes by one the quantity of slots required to delineate a variably-sized region succeeding a NAPOT region within the address map. This approach does not necessitate substantial supplementary comparator logic beyond that of the standard PMP design.

   The IR and IW bits determine if an interrupt should be triggered when an access attempt fails the global permission checks yet falls within the rule's defined address range. The IR bit pertains to read transactions, and the IW bit pertains to write transactions. If either the IR or IW bit is not set (clear), no interrupts are signaled. Conversely, if the IR or IW bits are set, interrupts are signaled for permission breaches associated with this rule.

   The ER and EW bits signify whether bus-error responses should be issued for bus transactions that do not pass global permission checks but are within the rule's address range. The ER bit dictates the handling of read transactions, whereas the EW bit dictates write transaction handling. If ER is set, read operations yield zero data along with an error response. If EW is set, write operations are disregarded but an error response is returned. The specific type and encoding of these error responses depend on the bus protocol. If the ER bit is clear, reads return zero data, and the transaction response does not signal an error. If the EW bit is clear, writes are ignored, and the transaction response also does not signal an error.

   NOTE: The IR, IW, ER, and EW bits serve to customize the checker's actions for memory areas that may be cacheable, idempotent, or non-idempotent.

   The L bit signifies that the current entry is locked. After this bit is activated, the slot's data cannot be altered or unlocked unless the checker undergoes a reset. It is important to note that if two slots are utilized to define a range, both must be locked independently to safeguard the range from modifications.

   Any remaining bits within the cfg register are designated for future purposes and must be written with the value zero.

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
