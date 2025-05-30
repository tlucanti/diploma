### Key considerations before discussing TEEs:

- RISC-V is still emerging in the TEE space. Unlike ARM TrustZone, RISC-V does not yet have a dominant, widely adopted TEE standard or ecosystem. The hardware isolation features like PMP (Physical Memory Protection) and WorldGuard are lower-level primitives, but the software stack (secure OS, trusted apps, TEE APIs) is largely up to you or the community projects you adopt or extend.

- You want something compatible with your hardware isolation model (WorldGuard), and the ability to support a Linux normal world plus your secure world OS with TEE functionality.

---

### TEE options you can consider for RISC-V + WorldGuard / Linux + secure OS:

#### 1. OP-TEE on RISC-V (experimental/porting efforts)
- OP-TEE is the most mature open-source GlobalPlatform-compliant TEE and running it on ARM TrustZone is common.
- There are community efforts to port OP-TEE to RISC-V platforms, leveraging PMP and newer extensions like WorldGuard for isolation.
- You could consider either:
  - Porting OP-TEE to your RISC-V platform and WorldGuard (which will require substantial integration work).
  - Or using OP-TEE codebase as inspiration or starting point for implementing GlobalPlatform APIs in your Secure OS.

Advantages:
- Standardized GlobalPlatform APIs for the secure apps and normal world clients.
- Existing ecosystem and tooling.
- Open source, so you can adapt it to RISC-V and WorldGuard.

Limitations:
- Porting effort is non-trivial.
- Hardware support and ecosystem on RISC-V still immature compared to ARM.

#### 2. Develop your own minimal GlobalPlatform TEE interface
- Since you’re implementing your own Secure OS, it’s feasible to implement a minimal subset of the GlobalPlatform TEE Client API and Core API so that existing or new secure applications can be ported or written against a known TEE API.
- This approach gives you flexibility to tailor the OS to your hardware’s isolation model while maintaining compatibility with existing trusted app concepts.

#### 3. Use existing RISC-V-specific projects or research prototypes
Though still early, some research projects and prototype TEEs for RISC-V exist:

- Keystone Enclave: An open-source secure enclave framework for RISC-V. Keystone uses PMP and custom runtime to provide isolated enclaves — more like Intel SGX than a split world TEE.
  - Works with Linux.
  - Provides APIs for enclave apps.
  - Could potentially be integrated or inspired for your secure world OS, but the model is different (no secure world/normal world split; more enclaves inside normal OS).

- Berkeley’s TEE efforts for RISC-V: Some academic projects are exploring TEE models on RISC-V.

- These are generally enclave-like rather than dual-world TEEs, so depending on WorldGuard's design, they might or might not fit seamlessly.

#### 4. TrustZone-style RISC-V splits in the future
- WorldGuard is a RISC-V extension inspired by TrustZone, aiming for a secure/normal world split.
- When such features mature, operating systems and TEE runtimes will emerge.
- You are pioneering this, so part of your architecture will define how communication, context switching, and secure apps APIs work.

---

### Summary / Recommendations:

| Option                              | Pros                                                  | Cons                                                 | Suitability for your scenario                     |
|-----------------------------------|-------------------------------------------------------|------------------------------------------------------|---------------------------------------------------|
| OP-TEE port on RISC-V + WorldGuard | Mature TEE concept, GlobalPlatform compliant         | Requires porting effort, hardware support availability| Good if you want industry-standard interface       |
| Implement own GlobalPlatform subset | Full control, allows compatibility with GlobalPlatform apps | Development overhead, no existing ecosystem support  | Good if you want a custom tailored TEE             |
| Keystone Enclave (RISC-V enclave) | Available today, supports RISC-V, open-source         | Enclave model (no secure world), less isolation from Linux | Possible if open to enclave model vs secure world  |
| Research/experimental TEEs          | May provide ideas or early code                        | Early stage, incomplete tooling                       | Useful for inspiration, not production-ready       |

---
