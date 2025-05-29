
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
