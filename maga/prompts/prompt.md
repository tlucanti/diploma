project background:
Secure OS is a microkernel OS with capability based model, so the idea is that everything is a handle, all handles (that are listed at predefined Manifest) are given by root task to Trusted Application when it spawned. Creation of objects are done with fabric object handle. Every action to handle is checked with capability model and granted or denied.
Secure OS always works on first cpu core, other cores are left for Linux. Communication between Linux and Secure OS is provided using two shared pages. One page for requests (to secure OS) queue, second page for responses queue. It uses subset of Global Platform API as interface for communications.

Paper should have 4 chapters:

# Chapter 1: Foundations and Motivation for an Open Secure OS on RISC-V
# Chapter 2: Core Principles of Trusted Execution Environment and Threat Model
# Chapter 3: Design and Implementation of the Secure Operating System
# Chapter 4: Evaluation and Security Analysis
# Conclusion

Starting with conclusion:
I have a draft of chapter:

В ходе выполнения работы были решены поставленные задачи, что позволило достичь цели проекта.

1. В результате анализа и современных ДСИ
   и Доверенных Операционных Систем

2. В результате анализа и сравнения
   моделей управления доступом,
   таких как MAC и DAC, было принято решение
   разработать собственную
   модель управления доступом, для получения
   достоинств от обеих моделей, и так же
   невелирования недостатков рассмотреных моделей.

3. Разработана архитектура Доверенной ОС

4. Разработана Capability-Based
   модель безопасности ОС.

5. Адаптирован интерфейс
   GlobalPlatform TEE Internal Core API
   под архитектуру RISC-V с расширением WorldGuard

6. Реализована программная реализация доверенной ОС
   с Capability-Based моделью безопасности

7. Экспериментально проверена работоспособность
   разработанной доверенной операционной системы

8. Экспериментально проверена
   устойчивость к атаками на ДСИ


expand contents of each section based on draft.
full structure of whole paper is in the attached file.
Do not write very much, only a few sentencies!
Keep it concise! Write only section contents, no summary or reasoning.