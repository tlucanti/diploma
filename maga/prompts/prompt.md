project background:
Secure OS is a microkernel OS with capability based model, so the idea is that everything is a handle, all handles (that are listed at predefined Manifest) are given by root task to Trusted Application when it spawned. Creation of objects are done with fabric object handle. Every action to handle is checked with capability model and granted or denied.
Secure OS always works on first cpu core, other cores are left for Linux. Communication between Linux and Secure OS is provided using two shared pages. One page for requests (to secure OS) queue, second page for responses queue. It uses subset of Global Platform API as interface for communications.

Paper should have 4 chapters:

# Chapter 1: Foundations and Motivation for an Open Secure OS on RISC-V
# Chapter 2: Core Principles of Trusted Execution Environment and Threat Model
# Chapter 3: Design and Implementation of the Secure Operating System
# Chapter 4: Evaluation and Security Analysis

So, 3rd chapter is about Design and Implementation of the Secure Operating System
I have a draft of chapter 3:

# Chapter 3: Design and Implementation of the Secure Operating System
 ## Interface Considerations
  ### TEE Client API: Inter-World Communication Interface
   #### OP-TEE on RISC-V
   #### Develop own minimal GlobalPlatform TEE interface
   #### Experemental of Research Prototypes
   #### Rationale for Adopting a Global Platform-based API Subset
 ## System Architecture Overview
  ### High-Level Architecture
   #### Architectural Layers
   #### Secure vs. Normal World Overview
  ### Core System Components
   #### Kernel, Resource Managers, and TEE Services
   #### Shared Memory and IPI-Based Communication
  ### Memory Layout and Addressing
   #### Physical and Virtual Addressing
   #### Isolation Mechanisms
   #### Shared Memory Queues
  ### Secure OS Execution Flow
   #### Boot Process Overview
   #### Inter-World Transitions
   #### Scheduling in Secure OS
  ### Security and Policy Enforcement
   #### Capability-Based Security Model
   #### World Guard Integration
  ### TA Lifecycle
   #### Creation
   #### Compute
   #### Teardown
 ## WorldGuard Integration
  ### WorldGuard Configuration
   #### World Configuration (Two-World Model)
   #### WorldGuard Checker Configuration for Secure Isolation
  ### Integration with the Secure OS
   #### Error Reporting
   #### Managing World Transitions
   #### Communication Pages
 ## Secure Boot Process and Initialization
  ### Secure OS Early Initialization
   #### OpenSBI Handover
   #### Setting Up the Stack and Basic Memory Layout
   #### First Kernel Relocation
   #### Enabling the MMU
  ### Secure OS Initialization
   #### Register Console
   #### Initialize Page Tables
   #### Second Kernel Relocation (If Needed)
   #### Initialize Trap Handler
   #### Initialize Timers
   #### Initialize Page Allocator
   #### Initialize Slab Allocator
   #### Initialize Scheduler
   #### Initialize Root Task
   #### Initialize Normal World Communication Channel
   #### Initialize Trusted Applications
 ### Rich OS Initialization
  #### Initialization by OpenSBI
  #### Core Startup
 ## OpenSBI modifications
  ### ...
 ## Cross-World Communication
  ### Shared Memory Queues
   #### Lock-Free Queue Algorithm
   #### Shared Memory Ring Buffers
   #### Requests Queue
   #### Responses Queue
   #### Canary Around Shared Pages
  ### Shared Memory Regions
   #### Memory Region Allocation
   #### Memory Region Deallocation
   #### Data transfer
  ### Message Structure
  ### IPI Based Signaling
   #### RISC-V IPI Mechanism
   #### Normal to Secure World Signaling
   #### Secure to Normal World Signaling
 ## TEE API
  ### Global Platform API
   #### Introduction to Global Platform API
  ### TEE Client API
   #### TEE Contexts
   #### TEE Sessions
   #### TEE Shared Memory
  ### TEE API Specification
   #### TEEC_UUID
   #### TEEC_Result
   #### TEEC_Context;
   #### TEEC_Session;
   #### TEEC_Value;
   #### TEEC_RegisteredMemoryReference;
   #### TEEC_Parameter;
   #### TEEC_Operation;
   #### TEEC_SharedMemory;
   #### TEEC_InitializeContext
   #### TEEC_FinalizeContext
   #### TEEC_OpenSession
   #### TEEC_CloseSession
   #### TEEC_InvokeCommand
   #### TEEC_AllocateSharedMemory
   #### TEEC_ReleaseSharedMemory
 ## Linux Driver Implementation
  ### Driver Overview and Registration
   #### Linux Driver Initialization
   #### Linux Driver Interface
  ### Shared Queues from the Linux Side
   #### Requests Queue
   #### Responses Queue
   ### Linux Communication Interface
   #### Communication Initialization
   #### Queue Initialization
   #### Communication Polling kthread
   #### Message Sending
   #### Getting the Result
   #### Communication Finalization
 ## Дизайн и реализация ядра Secure OS
  ### Kernel Objects and Handles
   #### Tasks (Processes)
   #### Threads
   #### Pipes (или Channels)
   #### Virtual Memory Objects
   #### Synchronization Primitives
  ### Task Management
   #### Process Model
   #### IPC Service
   #### Root Task
  ### Scheduling
   #### Scheduling Service
   #### Scheduling Policies
  ### Memory Management Subsystem
   #### Secure Memory Allocator
   #### Memory Isolation
  ### File System
   #### linear RAM fs
   #### elf files
 ## Capability-Based Security Model
  ### Handles as Encapsulated Capabilities
   #### Design Rationale
   #### Objects
   #### Object Handles
   #### Factory Objects
   #### Object Methods
  ### Capability-Based Access Control
   #### Permissions
   #### Task Manifests
   #### Root Task
   #### Method Invocation
   #### Performance Implications
 ## Secure Syscalls
  ### Secure Entry Points
   #### Background on OS System Calls
   #### Secure Syscall Lifecycle
   #### Argument Passing Format
   #### Validation of Handle Permissions
  ### Syscall Specification
 ## Trusted Application Framework
  ### Standard Library for Trusted Applications
  ### Handle Operations Specification
  ### I/O Standard Library Specification
  ### Strings Standard Library Specification
  ### Math Standard Library Specification
  ### Crypto Standard Library Specification
  ### Container Standard Library Specification
  ### Concurrency Standard Library Specification
  ### Misc Library Functions Specification
 ## Implementation Challenges and Optimizations
  ### Performance vs. Security Trade-Offs
   #### Balancing Isolation with Speed
   #### Inter-World Communication Overhead
   #### Scalability Limits on a Single-Core Secure OS
  ### Memory Footprint Optimizations
   #### Static Allocation vs. Dynamic Allocation
   #### Slab Allocator and Page Pool Efficiency
   #### Minimal Kernel Subsystem Design
  ### Debugging Considerations
   #### Logging from Secure OS
   #### Debugging TAs in Isolation
   #### Instrumentation Techniques
   #### Fault Isolation and Crash Analysis
  ### Build System and Packaging for TAs
   #### Trusted Application Build Flow
   #### Kernel Build System
   #### Development Tooling Support
  ### Testing and Validation
   #### Unit Testing Secure OS Components
   #### Integration Testing with Linux
   #### Security-Oriented Tests
  ### Summary of Implementation
   #### Overview
   #### Codebase Structure Summary
   #### Opportunities for Improvement


Starting with chapter 3.7.1. Kernel Objects and Handles
I have a draft of chapter sections:

- Взаимодействие с ресурсами внутри ядра построено вокруг объектной модели. Каждый объект в системе (например, задача, поток, виртуальный объект памяти, канал связи и т.д.) имеет свой уникальный дескриптор (handle). Доступ к функциональным методам объекта и внутреннему состоянию определяется набором capability-флагов (прав доступа).
#### Tasks (Processes)
- Задачи (tasks) являются основными изолированными сущностями в Secure OS.
- Они содержат собственное адресное пространство (vm_space) и набор потоков (threads).
- Кодовая составляющая задачи находится в пользовательском адресном пространстве безопасной среды (для Trusted Applications).
- Каждая задача имеет таблицу объектов (object_table), где регистрируются все ресурсы (включая каналы, объекты памяти и др.), предназначенные для её использования.
- создание задачи состоит из следующих этапов:
1. Создание пустой пользовательской задачи (task_create_empty) – формирование объектов структуры task, включая инициализацию отдельных полей (handle_page, object_table и т.д.).
2. Запуск задачи (task_run) – настройка защиты памяти для страницы дескрипторов (handle_page), установка состояния (TASK_SPAWNED) и добавление главного потока задачи в планировщик (sched_insert).
3. Уничтожение задачи (task_destroy) – освобождение адресного пространства (vm_space_destroy) и освобождение динамически выделенной памяти.
- Пример создания задачи на основе системного вызова task_spawn показывает, как пользователь может передать в ядро указатель на точку входа (ep) и handle задачи, а ядро создаёт в ней начальный поток и переводит задачу в состояние выполнения.
- *пример*
#### Threads
- Каждая задача содержит по крайней мере один поток (thread).
- Потоки отвечают за выполнение кода внутри адресного пространства задачи.
- При создании пользовательского потока ядро настраивает контекст выполнения (регистры, стек, текущее окружение и т.д.).
- При создании процесса (task), ядро создаёт «главный поток» задачи, устанавливая ему точку входа (ep). После этого поток регистрируется в списке потоков (list_head_add_tail) и может быть запланирован планировщиком.
#### Pipes (или Channels)
- Вместо классических «каналов» (pipes) в ядре используются объекты «channel» (двухсторонние каналы связи). Они создаются фабрикой (см. factory.c, syscall channel_create) и позволяют процессам или компонентам ядра обмениваться сообщениями по дескрипторам с установленными привилегиями.
- Канал представлен двумя концами (rx/tx), которые могут принадлежать одной или разным задачам.
#### Virtual Memory Objects
- Объекты виртуальной памяти (VM Object) отображают некоторый участок памяти (обычно физической) в адресное пространство задачи.
- В ОС реализован системный вызов vmo_create, который позволяет создавать vm_object через фабрику (factory_object).
- После создания объект регистрируется в таблице дескрипторов c соответствующими правами (OBJECT_CAP_TRANSFER, VMO_CAP_FULL и пр.), что позволяет разграничивать операции чтения, записи и копирования.
#### Synchronization Primitives
- В ядре имеется набор примитивов синхронизации
- spin_lock
- mutex
- semaphore
- Очереди ожидания (wait_queue_init, wait_object_many) – абстракция, позволяющая потокам ждать появление событий (например, данных в канале).

write contents of these sections based on draft.
If needed - maybe add some points if there is anything else to say by topic.
full structure of whole paper and some of secure kernel boot code is in the attached file.Do not repeat yourself! Do not repeat points from other chapters! Keep it concise! Write only section contents, no summary or reasoning.