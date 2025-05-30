
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
   Trusted Execution Environments (TEEs) have undergone significant evolution since their inception, driven by the need for secure execution of sensitive code and data in modern computing systems. The concept of TEEs emerged as a response to the growing demand for secure environments that can protect against various types of attacks and threats.

   The earliest forms of TEEs were dedicated secure coprocessors or special hardware modules, such as SmartCards and Trusted Platform Modules (TPMs). These early implementations were designed to provide a secure environment for specific tasks, like cryptographic operations and secure authentication. They were typically isolated from the main processor and had their own secure storage and processing capabilities.

   Compared to old TEE implementations, modern TEEs have evolved to become more integrated with the main processor and operating system. They now offer more advanced security features, such as memory encryption, secure boot, and attestation mechanisms. Modern TEEs also provide a more flexible and programmable environment, allowing for the execution of complex applications and services.

   The evolution of TEEs has provided valuable lessons and insights into the design and implementation of secure execution environments. Future TEE developments are expected to focus on addressing emerging threats and challenges, such as side-channel attacks and quantum computer attacks. Additionally, TEEs are likely to become even more integrated with mainstream computing systems, enabling more efficient and secure execution of sensitive code and data.

   #### The Role of TEEs in Modern Security Architectures
   Trusted Execution Environments (TEEs) play a crucial role in modern security architectures by providing a secure environment for executing sensitive code and handling confidential data. Modern TEEs, such as ARM TrustZone and Intel SGX, offer tightly integrated, hardware-enforced isolation within the main CPU. This isolation enables the execution of complex trusted applications alongside a rich OS environment, ensuring the confidentiality and integrity of sensitive operations.

   The capabilities of modern TEEs extend beyond simple cryptographic tasks. They support a wide range of complex applications, including secure UI, attestation, and trusted computing on the cloud and edge. For instance, TEEs can be used to create secure environments for authentication processes, protecting user credentials from compromise. They also facilitate the execution of trusted applications that require secure storage and processing of sensitive data.

   Despite their popularity and the significant benefits they offer, there remains a demand for transparent, open-source TEEs. The primary motivations behind this demand are to overcome vendor lock-in and to improve security through rigorous audits. Open-source TEEs can be scrutinized by a broader community, potentially leading to more secure implementations as vulnerabilities can be identified and addressed more effectively.

   Furthermore, as computing environments become increasingly heterogeneous and multi-core, there is a growing need for TEEs that can efficiently support these architectures. The ability to manage and secure diverse computing resources is becoming essential for maintaining the overall security posture of modern systems.

   In summary, TEEs are foundational to modern security architectures, providing the necessary isolation and security features for sensitive operations. The evolution towards more open and flexible TEE solutions is driven by the need for greater transparency, security, and adaptability in an increasingly complex computing landscape.

  ### Current State of TEEs on Proprietary Architectures
   #### Limitations of existing TEEs on Proprietary Architectures
   Despite their widespread deployment, traditional Trusted Execution Environments (TEEs) on proprietary architectures—such as ARM, Intel, and AMD platforms—impose several fundamental limitations. These constraints impact both the flexibility of security solutions and the broader technology ecosystem. The primary limitations are discussed below:

   Vendor Lock-in and Dependency
   Most proprietary TEEs are intimately tied to the hardware vendor's platform, creating an environment of strong vendor lock-in. Consumers of these technologies, whether systems integrators or application developers, become reliant on the hardware manufacturer for long-term security updates, support, and ecosystem compatibility. This dependency restricts the deployment of custom security features and inhibits rapid innovation, as all enhancements must align with the vendor's roadmap and approval process.

   Сlosed and Proprietary Ecosystems
   The implementations of proprietary TEEs are typically closed-source, with crucial architectural details kept undisclosed. This lack of transparency means users and researchers cannot fully audit, modify, or verify the correctness and security of TEE implementations. Furthermore, trusted application development is subject to tightly controlled vendor toolchains, restrictive SDKs, and proprietary APIs, which hinder portability, independent validation, and third-party ecosystem growth.

   Hardware Complexity and Rigidity
   Proprietary architectures often implement TEEs as fixed-function hardware modules (such as Arm TrustZone or Intel SGX enclaves) with rigid boundaries and strictly defined isolation mechanisms. This rigid design limits the ability to adapt the TEE to novel use cases or to tune the level of isolation and performance characteristics for specific workloads. For example, the secure world and normal world division on ARM TrustZone is architecturally constrained, which can impede fine-grained security policies or optimized resource sharing. Additionally, these fixed designs may prove insufficient for emerging workloads, such as edge computing or rapidly evolving IoT environments.

   Fixed ISA with No Scope for Tailoring or Extension
   Traditional proprietary CPU vendors expose only a fixed instruction set, with little to no possibility for customization or extension by system integrators. As security threats evolve and new defense mechanisms are researched, the lack of ability to extend the instruction set or add novel CPU security features at the hardware level impedes both rapid prototyping and the deployment of advanced security primitives. This lack of ISA flexibility slows response to emerging threats and constrains researchers' ability to explore alternative TEE designs.

   Limited Interoperability and Ecosystem Fragmentation
   Each proprietary architecture typically provides its own unique TEE implementation, interface specifications, and lifecycle management. As a result, TEEs are generally not interoperable between vendors or even across different product lines from the same vendor. This siloed approach causes fragmentation, complicates cross-platform secure application development, and reduces opportunities for broader standardization and industry-wide adoption of best security practices.

   Barriers to Academic Research and Independent Innovation
   Due to NDA requirements, licensing agreements, and lack of documentation, proprietary TEE platforms pose high barriers to academic researchers and third-party developers. This restricts exploration of alternative TEE security models, formal verification of TEE code, and collaborative security research, thereby slowing overall progress in the field.

   In summary, the proprietary and inflexible nature of traditional TEEs limits security innovation, adaptability, and transparency. These deficiencies highlight the need for open and extensible secure execution environments, paving the way for open architectures—such as RISC-V—to address these shortcomings and foster a more flexible, auditable, and collaborative approach to trusted computing.

   #### Licensing in Proprietary Architectures
   The licensing requirements associated with proprietary architectures—such as ARM TrustZone and Intel SGX—play a significant role in shaping the landscape of trusted execution environments (TEEs). These licenses carry important economic, legal, and technical implications that influence every stage of secure operating system development and deployment.

   One of the foremost consequences of proprietary licensing is its direct influence on the economics of device and systems development. Access to proprietary security extensions or TEEs commonly entails substantial licensing fees, which must be paid either upfront as development costs or continuously through royalties tied to production volumes. For emerging companies and innovative projects working with constrained resources, these costs can present significant barriers to entry. Even for well-established vendors, these fees increase the total cost of ownership, reducing profit margins and potentially translating into higher costs for end-users.

   Furthermore, the presence of licensing boundaries may restrict scalability. For instance, experimenting with new use-cases, developing custom hardware extensions, or deploying product variants to address niche or regional markets can become prohibitively expensive if each variation requires renegotiation or additional licensing outlays.

   Beyond financial costs, licensing agreements explicitly define and often constrain the permissible use-cases, usage scenarios, and device profiles for licensed security technologies. These restrictions may outline hardware configurations, specific software stacks, or deployment geographies. They can also impede technical innovation, as any desired deviation from the vendor's reference platforms or software requirements likely demands renewed legal vetting and new licensing negotiations.

   Operational flexibility is therefore limited. This is especially problematic in research environments, rapid prototyping contexts, and bespoke industrial applications, where experimentation and fast iteration are essential. The presence of closed-source reference designs and proprietary firmware further limits the ability of users to inspect or customize low-level security mechanisms, inhibiting transparency and independent validation.

   Perhaps most concerning for many long-term projects is the uncertainty inherent in reliance on third-party licensing. Vendors may unilaterally change licensing conditions—introducing new restrictions, increasing costs, or even withdrawing rights altogether. Such unpredictability is especially acute for products intended for long life cycles (e.g., industrial controllers, automotive ECUs, healthcare devices), where secure operation and maintenance may be required for a decade or more. Over-reliance on external licensing presents potential threats to project sustainability, maintainability, and even regulatory compliance.

   Additionally, the legal complexity of proprietary licenses introduces compliance challenges. Ambiguities or unforeseen clauses within licensing agreements can become legal liabilities, with the potential for significant penalties or forced redesigns if violations occur. For open-source projects, integrating proprietary components may introduce conflicting license obligations, hampering community collaboration or driving projects toward technical lock-in.

   These constraints collectively create silos around proprietary TEEs, impeding interoperability and independent ecosystem growth. Collaborations between independent vendors, research institutions, and the open-source community are restricted by legal uncertainties and a lack of access to underlying technology. As a result, the overall pace of innovation in secure computing is slowed; the technical community is inhibited from collectively responding to new threats or developing and fielding novel security features.

   In summary, proprietary licensing regimes for TEEs and secure architectural extensions impose not only direct economic costs, but also operational constraints, legal uncertainties, and long-term risks. These factors collectively impede the free exploration, adoption, and maturation of secure execution technology. This reality points to a clear and urgent motivation for open architectures and open-source secure OS solutions—particularly on platforms such as RISC-V, where openness and extensibility underpin ecosystem growth and collective innovation.

  ### The RISC-V Opportunity: Openness and Extensibility
   #### Open-Source Hardware and RISC-V’s Emergence
   In stark contrast to this established paradigm, the rise of the open-source hardware (OSHW) movement, exemplified by the emergence and rapid ascent of RISC-V, offers a transformative alternative. RISC-V is not a specific processor implementation but rather an open-standard ISA, meaning its base specification and related documentation are freely available for anyone to use, implement, design, or extend without licensing fees or restrictive agreements. This fundamental shift away from proprietary control has profound implications for the semiconductor industry and beyond.

   The openness inherent in RISC-V promotes a truly collaborative development model. It allows a diverse global community—comprising academic researchers, industry consortia, startups, and established corporations—to contribute to the ISA's evolution, develop a wide array of core implementations (from deeply embedded microcontrollers to high-performance server-class processors), and share supporting tools and software. This collective effort accelerates innovation, facilitates the exploration of novel architectural features, and allows for rapid iteration on designs.

   Furthermore, the transparency afforded by an open ISA is paramount, especially in the context of security. With the specification publicly accessible, and many core implementations also being open-source (e.g., available as Register Transfer Level - RTL - code), designs can be meticulously scrutinized, audited for potential security vulnerabilities by independent third parties, and formally verified. This "many eyes" approach significantly enhances the potential for identifying and mitigating security flaws, as opposed to relying solely on the claims of a single vendor controlling a proprietary, opaque design. Such transparency is crucial for building trust, as it reduces concerns about undisclosed functionalities, intentional backdoors, or undocumented behaviors within the processor hardware itself—a critical consideration for any secure system.

   The growing industry adoption and ecosystem maturity of RISC-V further solidify its position as a viable and compelling platform. Initially an academic project at the University of California, Berkeley, RISC-V has rapidly gained significant traction across various market segments. RISC-V International, the global non-profit organization responsible for stewarding the ISA, now boasts a membership of hundreds of organizations, including major semiconductor companies, cloud providers, software developers, and research institutions. This burgeoning ecosystem is driving the development of a mature software toolchain (compilers, debuggers, simulators), a rich portfolio of IP cores, and an increasing number of commercial products shipping with RISC-V processors. The availability of diverse hardware implementations and robust software support is essential for laying the groundwork upon which complex systems, such as Trusted Execution Environments, can be reliably built and deployed. This momentum indicates a clear trend towards a more open, flexible, and secure future for hardware, positioning RISC-V as a prime candidate for innovative security solutions.

   #### The RISC-V Instruction Set Architecture (ISA)
    The RISC-V Instruction Set Architecture (ISA) stands as a pivotal development in the evolution of processor design, offering a modern, open, and extensible foundation for computing across a wide range of applications. Its characteristics are particularly relevant when considering the development of secure systems, including the Secure OS explored in this thesis. The core attributes of the RISC-V ISA include its adherence to RISC principles, its modularity and extensibility, its scalability, and its open and free nature.

    RISC-V is fundamentally a RISC architecture. This design philosophy emphasizes a small, highly optimized set of instructions. Key characteristics include a load-store architecture (where only explicit load and store instructions access memory), fixed-length instruction encoding (typically 32-bits, with a compressed 16-bit option for density), and a relatively large number of general-purpose registers. This simplicity not only contributes to efficient hardware implementations with potentially lower power consumption and higher clock speeds but also reduces the complexity for formal verification and security analysis, potentially leading to a smaller and more verifiable Trusted Computing Base (TCB) when designing secure execution environments.

    A hallmark of RISC-V is its modularity. The ISA is designed as a small base integer instruction set (e.g., RV32I or RV64I), upon which standardized optional extensions can be added. These extensions cover common functionalities like multiplication and division (M extension), atomic operations (A extension), single and double-precision floating-point (F and D extensions), compressed instructions (C extension), vector operations (V extension), and bit manipulation (B extension). Beyond these standard extensions, RISC-V explicitly reserves encoding space for custom, domain-specific extensions. This inherent extensibility is crucial for security, as it allows for the seamless integration of specialized security-focused extensions. The WorldGuard extension, which is central to this thesis, is an example of such a security-enhancing architectural feature that can be incorporated into the RISC-V framework without altering the fundamental ISA or requiring permission from a central authority. This allows designers to tailor processors with precisely the security features needed for a given application, avoiding unnecessary complexity.

    The RISC-V ISA is designed to be scalable across a vast spectrum of computing devices. It supports 32-bit (RV32), 64-bit (RV64), and has a reserved encoding for a future 128-bit (RV128) address space variant. This scalability enables RISC-V to power devices ranging from deeply embedded microcontrollers and IoT devices to high-performance servers and supercomputers. For security architectures, this means that principles and mechanisms developed for one class of RISC-V system can often be adapted or directly applied to others, fostering a consistent security model across diverse platforms.

    Perhaps the most disruptive aspect of RISC-V is that its specification is free and open-source, managed by RISC-V International, a global non-profit organization.
    *   **Free:** The "free" aspect refers to its royalty-free licensing model. Unlike many proprietary ISAs, designers can implement RISC-V cores without paying licensing fees for the use of the ISA itself. This significantly lowers the barrier to entry for hardware innovation.
    *   **Open-Source Specification:** The "open-source" nature of the specification promotes unparalleled transparency and collaboration. The ISA documents are publicly available, allowing anyone to inspect, scrutinize, and contribute to their development. For security, this openness is a considerable advantage. It allows the ISA specification to be audited by a global community of researchers and security experts, facilitating the identification and mitigation of potential vulnerabilities at the architectural level. It also prevents vendor lock-in for core architectural features, including security mechanisms, and encourages the development of open-source hardware implementations (cores) and software toolchains. This contrasts sharply with proprietary ISAs where security features might be opaque, tied to specific vendor implementations, or carry restrictive licensing terms, hindering broad adoption, independent verification, and community-driven security enhancements.

    In summary, the RISC-V ISA provides a flexible, transparent, and economically accessible foundation. Its RISC principles, modularity, scalability, and particularly its free and open approach, create a fertile ground for innovation in secure computing, enabling the development of specialized hardware extensions like WorldGuard and fostering an ecosystem where open, auditable secure operating systems can thrive. These attributes directly support the goals of this thesis in building an open Secure OS for the RISC-V WorldGuard extension.

 ## Problem Statement
  ### Current State of TEEs on RISC-V Architecture
   #### Current Status of RISC-V’s Security Ecosystem
   The RISC-V architecture, with its open and extensible nature, presents a promising foundation for building secure computing systems. However, the security ecosystem surrounding RISC-V is, at present, in a nascent stage, particularly when compared to the mature security frameworks available for proprietary architectures like ARM or x86. This immaturity manifests in several key areas that create both challenges and opportunities for the development of robust Trusted Execution Environments (TEEs).

   While RISC-V International has active groups working on security specifications (such as cryptography extensions, trusted execution, and memory protection), the overall security landscape is still evolving. The rapid innovation in core designs and custom extensions means that security features, and the software to support them, often lag behind general processing capabilities. This creates a dynamic but also somewhat unsettled environment for security development.

   A significant characteristic of the current RISC-V security ecosystem is the fragmentation of software efforts. Unlike the well-established TEE solutions like ARM TrustZone or Intel SGX, which have a relatively cohesive software stack (albeit often proprietary), the RISC-V space features a diverse array of independent projects. This fragmentation means that software support for security features, including TEEs, is often specific to certain hardware implementations or research initiatives. Consequently, there is limited availability of broadly compatible, off-the-shelf software components crucial for building comprehensive security solutions. This includes a scarcity of readily available secure monitors, trusted bootloaders specifically hardened for diverse RISC-V platforms, and standardized libraries for secure application development.

   Directly stemming from the software fragmentation is the absence of mature and widely adopted, standardized Secure Operating System (SecOS) implementations for RISC-V. While several academic and vendor-specific SecOS projects exist, they often lack the maturity, comprehensive feature sets (e.g., full GlobalPlatform API compliance), rigorous testing, and broad community support seen in established TEE ecosystems. Similarly, TEE management tools – essential for provisioning, deploying, updating, and attesting Trusted Applications (TAs) – are not yet standardized or widely available for RISC-V platforms. This forces developers to either build these components from scratch or rely on vendor-specific, potentially non-interoperable solutions.

   Much of the current work on RISC-V TEEs and SecOSs consists of early-stage experimental projects. These are often born out of academic research or as proofs-of-concept by silicon vendors to demonstrate the capabilities of their hardware security extensions (like early work with WorldGuard). While these projects are invaluable for exploring new security paradigms and pushing the boundaries of what's possible on RISC-V, they typically exhibit limitations in terms of stability, feature completeness, documentation, and long-term maintenance. Their adoption in production environments is therefore constrained, highlighting a gap between research potential and deployable solutions.

   While RISC-V defines a base ISA, security-critical hardware extensions (like Physical Memory Protection - PMP, and emerging TEE-specific extensions such as WorldGuard or the proposed "Keystone" or "PUMP" mechanisms) are still in various stages of standardization, adoption, and implementation across different RISC-V cores. This variability means that a SecOS designed for one RISC-V platform with a specific set of security features might not be directly portable to another, further contributing to software fragmentation and delaying the emergence of a unified security software ecosystem.

   Developing and debugging secure software, especially components that operate in isolated execution environments, is inherently complex. The RISC-V ecosystem currently lacks mature and specialized toolchains, debuggers (aware of different privilege modes and world states), and formal verification tools tailored for TEE development. This increases the development effort and the risk of introducing vulnerabilities.

   In summary, while the RISC-V ISA offers fundamental building blocks for security, its security ecosystem is characterized by ongoing development, software fragmentation, a shortage of mature and standardized TEE solutions and management tools, and a reliance on early-stage projects. This collective state underscores the significant opportunity and pressing need for the development of open, robust, and standardized Secure OS implementations, such as the one proposed in this thesis, to foster a more secure and cohesive RISC-V ecosystem.

   #### WorldGuard State
   The RISC-V WorldGuard extension represents a recent and actively developing approach to hardware-enforced security on the RISC-V architecture. As an emerging specification, it is characteristic of RISC-V's open and extensible nature, allowing for community contribution and iterative refinement. However, this also means that, as of this writing, WorldGuard has not yet achieved the status of a fully ratified RISC-V standard. This evolving nature implies that the specification is still subject to potential refinements and formalization processes within the RISC-V community.

   Despite its non-ratified status, the existing WorldGuard proposal and its available implementations (e.g., in configurable cores or emulators like QEMU with WorldGuard support) provide a comprehensive set of hardware features designed to enable the creation and management of isolated execution environments. These features are sufficient to support the concept of secure enclaves or "worlds," offering mechanisms crucial for a Trusted Execution Environment, such as memory isolation, distinct privilege levels for different execution contexts, and controlled transitions between them. These capabilities form the foundational building blocks upon which a robust TEE can be constructed, allowing for the separation of secure and non-secure processing domains.

   However, a significant gap currently exists in the software ecosystem necessary to fully leverage these hardware primitives. While WorldGuard provides the hardware capabilities for enclave-like isolation, there is a distinct lack of mature, open-source, and standardized software layers, such as a full-fledged Secure Operating System, specifically designed to manage these WorldGuard-defined worlds and expose TEE functionalities to applications. Current software support is largely limited to low-level proof-of-concepts, specific academic research projects, or proprietary, vendor-specific solutions that are not broadly accessible or standardized for wider ecosystem adoption.

   This absence of a readily available and open Secure OS framework means that developers cannot easily build, deploy, and manage Trusted Applications (TAs) that would utilize WorldGuard's hardware security features in a standardized manner. Consequently, the potential of WorldGuard to facilitate robust and widely adopted TEEs on the RISC-V platform remains largely untapped at the software application level. This situation highlights a critical need and opportunity for the development of an open-source Secure OS specifically tailored for the WorldGuard extension, which would bridge the gap between the hardware capabilities and the software infrastructure required for deploying secure applications within the burgeoning RISC-V ecosystem.

  #### Software support on WorldGuard extension
   ...

 ## Relevance and Applications
  ### Rapid Growth of RISC-V in Commercial and Industrial Domains
   #### Wide Deployment Across Diverse Product Areas
   The RISC-V architecture is witnessing an accelerating adoption curve, transitioning decisively from a subject predominantly of academic and experimental interest into a tangible presence in a diverse array of real-world commercial products. This penetration is evident across several key sectors, demonstrating its versatility and growing industry confidence.

   Industrial control and factory automation systems, for instance, are increasingly leveraging RISC-V for its customization capabilities, which are crucial for specialized tasks and real-time processing requirements. In the rapidly expanding domain of data processing, RISC-V is finding applications in on-premise and edge cloud computing platforms, where its open nature allows for tailored NVM Express (NVMe) solutions and application-specific accelerators, contributing to power-efficient and optimized performance.

   Furthermore, networking equipment, including routers, switches, and network interface cards, is incorporating RISC-V cores for packet processing and control plane management. The architecture's scalability makes it suitable for a range of embedded consumer electronics, from low-power microcontrollers in smart home devices and wearables to more complex System-on-Chips (SoCs) in automotive applications and multimedia devices.

   This broad deployment across varied product categories underscores RISC-V's maturation beyond niche applications. It signifies a clear trend towards establishing a significant and expanding footprint in the commercial hardware landscape, solidifying its position as a viable and competitive architecture for future innovation.

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
