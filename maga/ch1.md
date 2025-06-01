
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
    Free: The "free" aspect refers to its royalty-free licensing model. Unlike many proprietary ISAs, designers can implement RISC-V cores without paying licensing fees for the use of the ISA itself. This significantly lowers the barrier to entry for hardware innovation.
    Open-Source Specification: The "open-source" nature of the specification promotes unparalleled transparency and collaboration. The ISA documents are publicly available, allowing anyone to inspect, scrutinize, and contribute to their development. For security, this openness is a considerable advantage. It allows the ISA specification to be audited by a global community of researchers and security experts, facilitating the identification and mitigation of potential vulnerabilities at the architectural level. It also prevents vendor lock-in for core architectural features, including security mechanisms, and encourages the development of open-source hardware implementations (cores) and software toolchains. This contrasts sharply with proprietary ISAs where security features might be opaque, tied to specific vendor implementations, or carry restrictive licensing terms, hindering broad adoption, independent verification, and community-driven security enhancements.

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
   Despite the increasing adoption and versatility of RISC-V across various domains, a notable characteristic of the current market is the general absence of deeply integrated, hardware-backed Trusted Execution Environments (TEEs) in commercially available products. While many System-on-Chips (SoCs) based on RISC-V are being deployed, they predominantly lack the comprehensive security features typically found in mature, proprietary architectures.

   This presents a clear distinction from ecosystems such as ARM, where TrustZone technology is a widespread and fundamental component of numerous processors, or the x86 architecture, which offers robust TEE solutions like Intel Software Guard Extensions (SGX) and AMD Secure Encrypted Virtualization (SEV) extensively embedded in their product lines. The relative architectural youth of RISC-V contributes to this disparity, as its security extensions, including WorldGuard, are still in the process of standardization, maturation, and importantly, widespread commercial implementation.

   Consequently, while foundational security mechanisms like Physical Memory Protection (PMP) are often present in RISC-V cores, providing a basic level of memory isolation, these do not equate to the full capabilities and assurances offered by a dedicated TEE. This absence of readily available, TEE-equipped RISC-V products currently limits their deployment in application areas with stringent, pre-existing security requirements, or necessitates custom, non-standardized security solutions.

   #### Motivation to Develop Secure RISC-V Solutions
   The current landscape of RISC-V, characterized by rapid growth (as outlined in 1.3.1) but a notable absence of mature, integrated security products (see 1.3.1.1), provides compelling motivations for the development of dedicated secure solutions. Key drivers include:

   Addressing Inevitable Market Demand: The critical role of security in analogous ARM and x86 application domains indicates a similar, strong market requirement for secure RISC-V products as the architecture matures and expands into these commercial and industrial areas. Proactive development is essential to meet this anticipated demand for trusted computing capabilities.

   Shaping an Emerging Ecosystem: Early engagement in creating secure RISC-V solutions offers a significant opportunity to influence the development of standards, establish best practices, and contribute to foundational technologies. This leadership can help define the future of secure computing on RISC-V and foster a robust security ecosystem.

   Capitalizing on RISC-V’s Openness and Specific Extensions: The open nature of the RISC-V ISA, combined with its evolving security-specific architectural extensions like World Guard, presents a unique occasion. This facilitates the creation of open-source, auditable, and highly optimized secure operating systems and Trusted Execution Environment (TEE) software stacks, designed to fully leverage these advantages for robust security.

  ### Expanding Security Requirements in Modern Computing
   #### Essential Security Functions in Contemporary Products
   Contemporary computing products, spanning from mobile devices and automotive systems to cloud infrastructure and Internet of Things (IoT) deployments, now mandate a robust set of security functions as baseline requirements. These functions are critical for protecting sensitive data, ensuring system integrity, and maintaining user trust. Key among these essential security functions are:

   Secure Boot: This process ensures that each software component loaded during the system startup, from the initial bootloader to the operating system kernel, is authentic and unmodified. It establishes a chain of trust, preventing the execution of unauthorized or malicious code at the earliest stages of system operation.

   Firmware and Software Integrity: Beyond secure boot, mechanisms are required to continuously verify the integrity of critical firmware and software components at runtime or before execution. This guards against persistent threats and sophisticated attacks that might modify system components post-boot.

   Cryptographic Key Management: The secure generation, storage, protection, and usage of cryptographic keys are fundamental. These keys underpin most security services, including data encryption, digital signatures, secure communication (TLS/SSL), and device identity. Hardware-backed key stores are often preferred for maximum security.

   Secure Storage: Sensitive data, such as user credentials, personal information, encryption keys, and proprietary application data, must be protected at rest. Secure storage mechanisms ensure confidentiality and integrity even if the non-secure operating system or storage medium is compromised.

   Attestation: This capability allows a device to provide verifiable proof of its identity and the integrity of its software stack (including firmware and TEE components) to a remote party. Attestation is crucial for services like remote device management, content protection (DRM), and secure access to cloud resources.

   Secure Over-the-Air (OTA) Updates: The ability to remotely and securely update firmware and software is vital for patching vulnerabilities, introducing new features, and maintaining long-term device security and functionality. This requires verifying the authenticity and integrity of update packages before installation.

   Trusted Path / Protected I/O: For specific sensitive operations, it's crucial to ensure that user input (e.g., from a secure keypad or biometric sensor) and output (e.g., to a secure display region) are protected from interception or manipulation by the potentially compromised Normal World operating system.

   These functions are no longer niche requirements but are integral to the design and operation of modern computing systems, driven by increasing connectivity, the value of processed data, and the evolving threat landscape.

  #### RISC-V’s Untapped Potential for Secure Applications
   The unique combination of RISC-V's open and extensible nature with robust, open-source security solutions presents a significant opportunity to penetrate markets traditionally dominated by proprietary ISAs. This is largely due to the potential for a transparent security narrative, fostering greater trust and verifiability. The untapped potential manifests across numerous applications demanding high levels of trustworthiness:

   Secure Personal Devices: Smartphones, tablets, laptops, and wearables can leverage open TEEs on RISC-V to protect sensitive user data such as biometrics, financial credentials, and private communications, ensuring both confidentiality and device integrity against increasingly sophisticated threats.

   Automotive Systems: Modern vehicles, with their complex network of ECUs controlling everything from Advanced Driver-Assistance Systems (ADAS) to infotainment and Vehicle-to-Everything (V2X) communication, require strong isolation and security to ensure passenger safety, protect against unauthorized access, and secure vehicle data.

   Confidential Cloud Workloads: RISC-V based TEEs can enable secure enclaves for processing sensitive data in multi-tenant cloud environments, offering "data-in-use" protection where even the cloud provider cannot access the unencrypted data or computation.

   Internet of Things (IoT) Ecosystems: The vast and diverse IoT landscape, encompassing smart home devices, industrial control systems, wearable technology, and critical infrastructure monitors, can benefit immensely. RISC-V's scalability, coupled with an open TEE, can provide secure boot, attested firmware updates, secure communication channels, and data protection for resource-constrained devices across this wide spectrum.

   Critical Infrastructure: Sectors such as energy distribution, water management, and public transportation systems can utilize secure RISC-V platforms to protect control systems from cyber-attacks, ensuring operational reliability and public safety.

   Defense and Aerospace: The demand for verifiable security and supply chain integrity makes open hardware and software solutions attractive for mission-critical systems, secure communications, and applications where national sovereignty over technology is paramount.

   Medical Devices: Implantable and wearable medical devices, as well as diagnostic equipment, require robust security to protect patient data privacy (e.g., HIPAA compliance) and ensure the integrity and reliable operation of life-sustaining functions.

   Financial Technology (FinTech): Secure RISC-V TEEs can underpin next-generation FinTech solutions, safeguarding financial transactions, protecting cryptographic keys, and enabling secure authentication mechanisms for mobile banking and payment systems.

   The availability of open-source secure components, including the Secure OS described in this work, is poised to drastically lower barriers to entry for developing and deploying such trusted applications. This fosters innovation, reduces dependency on proprietary vendors, encourages wider community auditing, and allows for tailored security solutions across these diverse domains.

 ## Comparison with Existing Architectures
  ### ARM TrustZone: Centralized Secure World Model
   #### Overview
   ARM TrustZone technology establishes a hardware-enforced division of a system-on-chip (SoC) into two distinct execution environments: the Normal World (NWd) and the Secure World (SWd). This separation is achieved at the processor level, with a special processor mode (Monitor Mode) and system-level hardware controlling access to memory and peripherals based on the current security state of the executing core. The Normal World typically runs a rich operating system, such as Linux or Android, while the Secure World is designed to host a smaller, more trusted operating system (Trusted OS or Secure OS). This Secure OS, in turn, manages and executes Trusted Applications (TAs), providing them with a protected environment. Transitions between the Normal World and Secure World are mediated by a Secure Monitor Call (SMC) instruction, which triggers a switch into Monitor Mode, responsible for securely managing the context switch. Both worlds can operate on the same CPU cores, with the hardware ensuring that Normal World software cannot directly access resources allocated to the Secure World.

   #### Advantages
   Mature Ecosystem and Broad Adoption: TrustZone has been available for many years and is widely deployed across a vast range of devices, particularly in mobile and embedded systems. This has resulted in a mature ecosystem with extensive tooling, documentation, developer expertise, and readily available Secure OS implementations.

   Efficient Context Switching: The hardware-assisted mechanism for switching between the Normal and Secure Worlds, primarily through the SMC instruction and dedicated hardware support, is generally efficient. This allows for relatively low-latency transitions when secure services are invoked from the Normal World.

   Well-Supported Industry Standards: TrustZone implementations often adhere to industry standards, notably those defined by GlobalPlatform. These standards specify APIs and system behaviors for TEEs, promoting interoperability between different TAs and Secure OS implementations, and facilitating the development of a common TEE software stack.

   #### Disadvantages
   Centralized Architecture: The Secure World in TrustZone typically operates as a single, monolithic entity managed by one Secure OS instance. All secure operations from all cores often funnel through this centralized Secure World, which can become a performance bottleneck if many Normal World applications or cores simultaneously require secure services.

   High Cost for Full Communication Cycle: A complete request from a Normal World user-space application (EL0) to a Trusted Application in the Secure World (often also at EL0 equivalent) and a response back can involve up to eight distinct context switches through various privilege levels and monitor mode. This significantly increases the overall latency and processing overhead for inter-world communication, despite the efficiency of individual hardware-assisted switches.

   Blocking Secure Operations: When a Normal World application on a specific core makes a call (e.g., via SMC) to the Secure World, that core is typically blocked, waiting for the Secure World operation to complete and return. This can negatively impact the responsiveness and performance of the Normal World application running on that core.

   Limited Scalability on Multi-Core Systems: While individual cores can switch to the Secure World, the common model involves a single instance of the Secure OS governing the entire Secure World across all cores. This can lead to contention for shared secure resources and complexities in managing concurrent secure operations, potentially limiting scalability in highly parallel multi-core scenarios.

   Large Trusted Computing Base (TCB): The security of the entire TrustZone-based TEE heavily relies on the correctness and integrity of the Secure OS running in the Secure World. The Secure OS itself is part of the Trusted Computing Base (TCB), and any vulnerability within it can potentially compromise the entire Secure World and all TAs it hosts.

   Susceptibility to Side-Channel Attacks: Despite the hardware-enforced isolation, the sharing of underlying physical hardware resources (such as caches, memory controllers, and buses) between the Normal and Secure Worlds can still expose vulnerabilities to side-channel attacks, potentially leaking information across the security boundary.

  ### Intel Software Guard Extensions (SGX): Enclave-Based Isolation
   #### Overview
   Intel Software Guard Extensions (SGX) enable the creation of enclaves, which are private regions of memory isolated within an application's address space. These enclaves are protected by the CPU, providing hardware-enforced confidentiality and integrity for the code and data residing within them, even from privileged software such as the operating system or hypervisor. Memory associated with an enclave is encrypted by the processor. Applications can selectively place sensitive portions of their code and data into these enclaves, offering fine-grained isolation on a per-process basis.

   #### Advantages
   SGX offers notable flexibility, as applications can define and manage their own enclaves independently, allowing multiple enclaves from different applications to coexist on a system. It incorporates strong memory encryption capabilities for data within enclaves and provides robust remote attestation mechanisms. Attestation allows a remote party to verify the authenticity and integrity of the software running inside an enclave. A key architectural distinction is that SGX does not require a separate, dedicated secure operating system; enclaves operate as protected user-mode environments managed, yet not accessed, by the host OS.

   #### Disadvantages
   A primary limitation of SGX is the typically restricted size of the Enclave Page Cache (EPC), the secure RAM area where enclave pages are stored, which can impact the performance and feasibility of porting large applications. The programming model for SGX is complex, often necessitating significant code restructuring and potentially introducing compatibility challenges with existing libraries or system call-heavy applications. SGX enclaves are constrained to execute only in user mode (CPU ring 3), which means a full-fledged, privileged secure operating system cannot be hosted within an SGX enclave. Furthermore, SGX has been the target of numerous side-channel and speculative execution attacks, requiring ongoing research and mitigations. Performance overhead associated with enclave entry (ECALL) and exit (OCALL) operations, as well as memory encryption, can also be a factor for certain workloads.

  ### AMD Secure Encrypted Virtualization (SEV): VM-Level Memory Encryption
   #### Overview
   AMD's Secure Encrypted Virtualization (SEV) technology is engineered to bolster security within virtualized environments. It achieves this by providing transparent full memory encryption for guest Virtual Machines (VMs), thereby shielding them from potential threats originating from a compromised or malicious hypervisor. SEV is primarily oriented towards cloud computing scenarios, where robust isolation between multiple tenants coexisting on shared physical hardware is paramount. Each guest VM's memory can be encrypted using a unique key, managed by the AMD Secure Processor, ensuring that data remains confidential even if the hypervisor gains unauthorized access to the guest's memory pages.

   #### Advantages
   One of the significant benefits of SEV is the largely seamless manner in which it provides protection for virtual machines; guest operating systems and their applications typically require little to no modification to leverage this encrypted memory. The technology employs strong, hardware-accelerated AES encryption for VM memory. This encryption and decryption process is performed in real-time by dedicated hardware within the CPU and memory controllers during memory accesses, aiming to safeguard the confidentiality of guest VM data while it resides in DRAM or is in transit.

   #### Disadvantages
   Despite its effectiveness in protecting VM memory, SEV's design, centered on entire VM encryption, makes it inherently less suited for the role of a general-purpose Trusted Execution Environment (TEE) in the context of isolating individual applications. Its primary focus on virtualization security means it operates at a much coarser granularity—the entire VM—compared to enclave-based models like Intel SGX or distinct secure world architectures like ARM TrustZone. Consequently, SEV is fundamentally a mechanism to protect VMs from an untrusted hypervisor, rather than providing a dedicated, isolated environment for running specific trusted applications with fine-grained control within a single operating system, which is a typical use case for TEEs. This distinction limits its applicability for scenarios requiring application-level isolation and a specific programming model for trusted code execution distinct from the main OS.

  ### 1.4.4 RISC-V's Physical Memory Protection (PMP): Privilege-Level Memory Isolation

   #### Overview
   RISC-V Physical Memory Protection (PMP) is a standard hardware feature defined in the RISC-V Privileged ISA Specification. It provides a mechanism for controlling access rights to physical memory regions. PMP allows privileged software, typically executing in Machine Mode (M-mode), to define multiple memory regions, each with specific access permissions (Read, Write, Execute). These permissions can be set independently for different privilege levels (Machine, Supervisor, User). PMP configuration is managed through a set of Control and Status Registers (CSRs), primarily `pmpcfgN` for configuration and `pmpaddrN` for addresses, where N denotes the PMP entry index.

   #### Advantages
   - Standardized Inclusion: Being part of the base Privileged ISA, PMP is available on most RISC-V processors, offering a baseline memory protection capability without requiring custom extensions or incurring additional licensing costs for this feature.

   - Hardware-Enforced Security: Access permission checks are performed by the hardware for every memory access, ensuring low performance overhead and robust enforcement of the defined memory protection policies.

   - Privilege Level Isolation: PMP is effective for establishing fundamental isolation boundaries between different privilege modes. For instance, it can prevent User-mode (U-mode) applications from accessing Supervisor-mode (S-mode) OS memory or M-mode firmware regions.

   - Flexible Region Definition: PMP supports various region matching modes, including Top of Range (TOR), Naturally Aligned Four-byte (NA4), and Naturally Aligned Power-of-Two (NAPOT). NAPOT, in particular, allows for efficient protection of power-of-two sized and aligned memory blocks with a single entry.

   - Simplicity for Basic Use Cases: For straightforward memory protection tasks like securing firmware or isolating basic OS components, PMP offers a relatively simple configuration model compared to more complex MMUs or dedicated security extensions.

   #### Disadvantages
   - Privilege-Level Centric Isolation: PMP primarily enforces isolation based on privilege levels (M, S, U). It does not inherently provide mechanisms to isolate software components running *within* the same privilege level, nor does it establish distinct "worlds" or security domains independent of privilege level, which is a foundational requirement for TEEs like the one proposed. Thus, it is not suitable on its own for comprehensive TEE implementations.
   - Limited Number of Regions: The RISC-V standard specifies a modest number of PMP entries (e.g., 8, 16, or up to 64 for RV64). This limited count can be insufficient for complex systems needing fine-grained compartmentalization of many memory regions.
   - Primarily Static Configuration: PMP entries are typically configured by M-mode software during early boot. While reconfigurable, PMP is not designed for the highly dynamic creation and management of isolated memory regions at runtime by less privileged entities, as often required by TEEs for enclave-like functionalities or managing multiple Trusted Applications.
   - No Intrinsic Cryptographic Protection: PMP controls memory access permissions (read, write, execute) but offers no built-in mechanisms for memory encryption or integrity verification. Data in PMP-protected regions remains vulnerable to physical attacks or access by sufficiently privileged software if not otherwise cryptographically protected.
   - Absence of TEE-Specific Features: PMP lacks dedicated hardware support for core TEE functionalities such as secure attestation, trusted storage primitives, or controlled context switching mechanisms between a Normal World and a Secure World. It serves as a basic building block for memory protection rather than a complete TEE solution.
   - Configuration Management Complexity: As the number of PMP entries used increases, managing their configurations, ensuring no unintended overlaps or gaps, and verifying the correctness of the overall protection scheme can become complex and error-prone.

  ### RISC-V’s World Guard Extension: Decentralized Isolation
   #### Overview
   RISC-V WorldGuard is a hardware extension designed to enable robust memory and execution partitioning. It offers a more granular approach to isolation than traditional two-world models like ARM TrustZone. WorldGuard facilitates the creation of multiple, independent isolated execution domains, referred to as "worlds." These worlds can be assigned distinct privileges and resources, and on multi-core systems, different worlds can potentially operate in parallel on separate CPU cores. The extension provides mechanisms to control access to memory regions and peripherals, enforcing isolation between these worlds at the hardware level.

   #### Advantages
   -   Decentralized Design and Scalability: The architecture supports multiple independent worlds, enhancing scalability and flexibility, particularly for multi-core processors and multi-tenant environments. Each core can operate in a distinct world context, allowing for true parallelism between isolated environments.
   -   Openness and Transparency: As part of the open RISC-V ISA, WorldGuard benefits from community-driven development and scrutiny, leading to transparent security extension implementations.
   -   Support for Novel Secure OS Architectures: The fine-grained, multi-world isolation enables innovative Secure OS designs with tailored security policies, moving beyond traditional monolithic secure monitors.
   -   Enhanced Capabilities and Compatibility: WorldGuard offers a superset of security features compared to simpler models. For instance, a two-world configuration can closely emulate the TrustZone model, facilitating the use of established APIs like the GlobalPlatform TEE API.
   -   Non-Blocking Secure Services: The ability to dedicate specific cores to secure worlds (e.g., a Secure OS) allows for non-blocking calls from other worlds (e.g., a Rich OS like Linux), improving system responsiveness compared to architectures requiring a world switch on the same core.
   -   Multiple Concurrent TEEs: The design inherently supports the co-existence and concurrent operation of multiple TEE instances, each potentially serving different security requirements or tenants.
   -   Fine-grained Resource Control: WorldGuard allows for precise and configurable partitioning of system resources, including memory and peripherals, among different worlds.

   #### Disadvantages
   -   Early Standardization and Ecosystem Maturity: WorldGuard is a relatively new extension. Standardization is ongoing, and widespread, mature hardware implementations and comprehensive software support are still emerging.
   -   Requirement for a Comprehensive Secure Software Stack: The hardware capabilities of WorldGuard alone are insufficient. A complete TEE solution necessitates a robust and specifically designed Secure OS, runtime environments, trusted application development tools, secure boot mechanisms, and drivers. This foundational software ecosystem is currently under active development or exists primarily in experimental stages.
   -   Potential for Increased Complexity: Managing multiple isolated worlds, their distinct security policies, and inter-world communication protocols can introduce additional complexity in system design, development, and verification compared to simpler two-world models.

  ### Summary and Comparative Analysis
   #### Summary
   The following table provides a side-by-side comparison of the discussed TEE-enabling architectures and mechanisms across several key dimensions.

   | Feature                     | ARM TrustZone                            | Intel SGX                                     | AMD SEV                                         | RISC-V PMP                                      | RISC-V World Guard                              |
   |-----------------------------|------------------------------------------|-----------------------------------------------|-------------------------------------------------|-------------------------------------------------|-------------------------------------------------|
   | Core Isolation Mechanism    | Hardware-enforced Secure & Normal Worlds | CPU-protected enclaves (memory & execution)   | Encrypted Virtual Machines                      | M-mode configured memory access permissions     | Hardware-defined, isolated execution "Worlds"   |
   | Isolation Granularity       | OS-level (Secure OS vs. Rich OS)         | Application functions/modules                 | Entire Virtual Machines                         | Physical memory regions                         | Configurable (e.g., OS-level per World)         |
   | Typical Software Model      | Full Secure OS in Secure World           | SDK for enclave development; managed by OS    | Hypervisor manages encrypted guest OS           | M-mode firmware/monitor configures regions      | Full Secure OS within a dedicated World         |
   | Openness (Architecture/Spec)| ISA licensed; implementations proprietary| Proprietary Intel technology                  | Proprietary AMD technology; interfaces openable | Open RISC-V standard                            | Open RISC-V standard (emerging)                 |
   | Designed for Full Secure OS?| Yes                                      | No (Enclave-centric)                          | No (VM-centric)                                 | No (Building block only)                        | Yes                                             |
   | Key Strength                | Mature, system-wide TEE model            | Strong application isolation from OS/VMM      | Strong VM isolation from hypervisor             | Basic, flexible memory protection primitive     | Open, flexible world-based isolation on RISC-V  |
   | Key Limitation              | Proprietary ecosystem, licensing         | Not for monolithic Secure OS; complex TCB     | Not for co-resident Secure/Rich OS model        | Insufficient alone for TEE; lacks world concept | Newer, ecosystem still developing               |

   #### Comparative Analysis
   This comparative analysis of existing TEE-enabling architectures and mechanisms reveals distinct approaches to achieving isolated execution, each with implications for developing a Secure OS:

   ARM TrustZone offers a well-established model for a comprehensive Secure OS running alongside a Rich OS, bifurcating the system into Secure and Normal Worlds. While effective, its deployment is tied to the proprietary ARM architecture and its associated licensing models.

   Intel SGX focuses on protecting application-specific code and data within enclaves, isolating them from a potentially malicious OS or VMM. This model, while providing fine-grained protection for targeted application portions, is not designed for hosting a full, independent Secure OS with system-wide responsibilities as pursued in this work. The underlying hardware and microcode also represent a significant and complex proprietary TCB.

   AMD SEV aims to secure entire virtual machines by encrypting their memory, protecting them from a compromised or untrusted hypervisor. This is valuable for cloud environments but, like SGX, SEV's VM-centric isolation is not architected for the co-resident, dual-OS model typical of TrustZone-style TEEs and envisioned for this project.

   RISC-V's Physical Memory Protection (PMP) mechanism is a standard feature providing fundamental hardware-enforced memory region access controls. PMP is an essential building block for any secure system on RISC-V, including TEEs, by enabling memory isolation. However, PMP alone does not define distinct execution "worlds" or provide the comprehensive architectural support needed for a full TEE; it primarily serves M-mode in segmenting memory access for less privileged modes and lacks inherent mechanisms for distinct world switching or complex privilege management beyond standard RISC-V modes.

   RISC-V's World Guard Extension specifically addresses the need for a robust, hardware-enforced TEE framework on the open RISC-V architecture. By enabling the creation of multiple, isolated "worlds," it provides a direct architectural counterpart to concepts like ARM TrustZone's Secure World, and potentially offers more decentralized isolation capabilities. This makes World Guard highly suitable for implementing a dedicated, monolithic Secure OS. Its characteristic openness and flexibility align with the goals of fostering a transparent and adaptable security ecosystem for RISC-V, representing a key enabler for the Secure OS developed in this thesis, which aims to leverage these features for a capability-based secure environment.

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
