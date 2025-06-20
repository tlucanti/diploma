
<p style="text-align: center;">
  МИНОБРНАУКИ РОССИИ
</p>
<p style="text-align: center;">
  Федеральное государственное автономное образовательное учреждение
  высшего образования
</p>
<p style="text-align: center;">
  «Национальный исследовательский университет
</p>
<p style="text-align: center;">
  «Московский институт электронной техники»
</p>
<br></br>
<p style="text-align: center;">
  Институт микроприборов и систем управления
</p>
<br></br>
<br></br>
<p style="text-align: center;">
  Семичастнов Константин Владиславович
</p>
<br></br>
<p style="text-align: center;">
  Магистерская работа
</p>
<p style="text-align: center;">
  по направлению 09.04.01 «Информатика и вычислительная техника»
</p>
<br></br>
<p style="text-align: center;">
  <b>
   Разработка SecurityOS для платформы RISC-V с расширением WorldGuard
  </b>
</p>
<br></br>
<br></br>
<br></br>
<br></br>
<br></br>
<pre>
Студент                      ______________     Семичастнов К. В.
Руководитель, к.т.н.         ______________     Лупин С. А.
</pre>
<br></br>
<p style="text-align: center;">
  Москва 2025
</p>
<div style="page-break-after: always;"></div>

# Аннотация
<br></br>
...
<br></br>
<br></br>

# Abstract
<br></br>
...
<br></br>
<br></br>
<div style="page-break-after: always;"></div>

# Содержание
<br></br>
...
<br></br>
<br></br>
<div style="page-break-after: always;"></div>

 ## Список аббривеатур
  - ДСИ (TEE) - Доверенная Среда Исполнения (Trusted Execution Environment)
  - УСИ (REE) - Универсальная Среда Исполнения (Rich Execution Environment)
  - СнК (SoC) - Система На Кристале (System On Chip)
  - ОС (OS) - Операционная Систем (Operating System)
  - IoT - Internet Of Things (Интернет Вещей)
  - DRM - Digital Rights Management (Управление Цифровыми Правами)
  - OSHW - Open Source Hardware (Аппаратное Обеспечение с Открытым Исходным Кодом)
  - ISA - Instruction Set Architecture (Архитектура Набора Команд)
  - RTL - Register Transfer Level (Уровень Регистровых Передач)
  - RISC - Reduced Instruction Set Computer (Вычислитель с Сокращённым Набором Команд)
  - TCB - Trusted Computing Base (Доверенная Вычислительная База)
  - PMP - Physical Memory Protection (Защита Физической Памяти)
  - FPGA - Field Programmable Gate Array (Программируемая Пользователем Вентильная Матрица)
  - ПО - Программное Обеспечение
  - TA - Trusted Application (Доверенное Приложение)
  - OTA - Over-the-Air (Обновления по сети интернет)
  - TLS - Transport Layer Security (Безопасность Транспортного Уровня)
  - SSL - Secure Sockets Layer (Уровень Защищённых Сокетов)
  - ADAS - Advanced Driver-Assistance Systems (Усовершенствованная Система Помощи Водителю)
  - V2X - Vehicle-to-everything (Транспортное средство-ко-всему)
  - CCC - Confidential Cloud Computing (Конфиденциальные Облачные Вычисления)
  - SMC - Secure Monitor Call (Вызов Защищенного Диспетчера)
  - EPC - Enclave Page Cache (Кэша Страниц Анклава)
  - VM (ВМ) - Virtual Machine (Виртуальная Машина)
  - SGX - Software Guard Extensions
  - SEV - Secure Encrypted Virtualization
  - TZ - TrustZone
  - WG - WorldGuard
  - CSR - Control and Status Registers (Контрольные и Статусные Регистры)
  - SBI - Supervisor Binary Interface (Бинарный Интерфейс Супервизора)
  - SEE - Supervisor Execution Environment (Среда Выполнения Супервизора)
  - TOR - Top of Range (Верхняя Граница Диапазона)
  - NA4 - Naturally Aligned Four-byte (Естественно Выровненные Четыре Байта)
  - NAPOT - Naturally Aligned Power-of-Two (Естественно Выровненные по Степени Двойки)
  - CPU (ЦП) - Central Processing Unit (Центральный Процессор)
  - PoC - Proof of Concept (Концептуальный прототип)
  - OEM - Original Equipment Manufacturer (Оригинальный Производитель Оборудования)
  - RoT - Root of Trust (Корень Доверия)
  - DoS - Denial of Service (Отказ в Обслуживании)
  - DMA (ПДП) - Direct Memory Access (Прямой Доступ к Памяти)
  - IOMMU - Input/Output Memory Management Unit (Блок Управления Памятью Ввода/Вывода)
  - MITM - Man-in-the-Middle (Человек Посередине)
  - WID - World Identifier (Идентификатор Мира)
  - LSB (МЗБ) - Least Significant Bit (Младший Значащий Бит)
  - MSB (СЗБ) - Most Significant Bit (Старший Значащий Бит)
  - FSBL - First Stage Boot Loader (Загрузчик Первой Ступени)
  - ОЗУ - Оперативное Запоминающее Устройство
  - ПЗУ - Постоянное Запоминающее Устройство
  - RAM - Random Access Memory
  - OTP - One-Time Programmable (Одноразовая Программируемая Память)
  - ROM - Read Only Memory (Постоянное Запоминающее Устройство)
  - JTAG - Joint Test Action Group
  - RPC - Remote Procedure Call (Удаленный Вызов Процедуры)
  - GP - Global Platform
  - IPI - Inter Processor Interrupt (Межпроцессорное Прерывание)
  - VMO - Virtual Memory Object (Объект Виртуальной Памяти)
  - IPC - Inter Process Communication (Межпроцессное Взаимодействие)
  - SATP - Supervisor Address Translation and Protection
  - MMU - Memory Management Unit (Блок Управления Памятью)
  - PTE - Page Table Entry (Запись в Таблице Страниц)
  - UART - Universal Asynchronous Receiver-Transmitter (Универсальный Асинхронный Приёмопередатчик)
  - FDT - Flattened Device Tree (Дерево Устройств)
  - VMM - Virtual Memory Manager (Менеджер Виртуальной Памяти)
  - PMM - Physical Memory Manager (Менеджер Физической Памяти)
  - MPMC - Multi-Producer Multi-Consumer (Множество Производителей - Множество Потребителей)
  - CAS - Compare And Swap (Сравнение с обменом)
  - LL/SC - Load-Linked/Store-Conditional (Связанная загрузка/Условное сохранение)
  - UUID - Universally Unique Identifier (Универсальный Уникальный Идентификатор)
  - SSIP - Supervisor Software Interrupt Pending
  - CLINT - Core Local Interruptor
  - MMS - Memory Management Subsistem (Подсистема Управления Памятью)
  - ELF - Executable and Linkable Format (Формат Исполнимых и Компонуемых Файлов)
  - FS - File System (Файловая Система)
  - MAC - Mandatory Access Control (Мандатное Управление Доступом)
  - DAC - Discretionary Access Control (Дискреционное Управление Доступом)
  - HKDF - HMAC-based Key Derivation Function (Функция Генерации Ключей на основе HMAC)
  - HMAC - Hash-based Message Authentication Code
  - GDB - GNU Debugger
  - DTB - Device Tree Blob (Двоичное Дерево Устройств)
  - CI - Continuous Integration (Непрерывная Интеграция)
<div style="page-break-after: always;"></div>

# Введение
 ## Актуальность
 В настоящее время почти каждое вычислительное устройство подвержено
 проблеме уязвимости данных.
 Примером могут служить такие устройства как:
 телефоны, планшеты, ПК, консоли, устройства умного дома (IoT),
 автомобили, смарт-карты, банкоматы, серверы,
 и т.д.
 Для обеспечения защиты пользовательских данных
 могут применяться различные методы, такие как
 программная проверка полномочий, шифрование,
 использование выделенных физических носителей.
 Одним из самых надежных способом обеспечить безопасность является
 предоставление доверенной среды исполнения (ДСИ)
 с архитектурной поддержкой.
 Например, TrustZone в архитектуре ARM, или WorldGuard в архитектуре RISC-V.

 Однако, для обеспечения доверенной среды исполнения,
 помимо аппаратной поддержки, необходимо программное обеспечение
 (Доверенная Операционная Система - Secure OS),
 которое будет исполняться в выделенной среде.
 Поэтому потребность в легковесной,
 безопасной и открытой операционной системе, которая способна,
 работая совместно с Универсальной Средой Исполнения (Liunx OS),
 обеспечить Доверенную Среду Исполнения
 для сохранности чувствительных пользовательских данных
 является актуальной.

 ## Цель исследования
 Целью работы является создание доверенной операционной системы
 для обеспечения Доверенной Среды Исполнения
 для СнК на архитектуре RISC-V

 ## Задачи исследования
 Для достижения поставленной цели поставлены следующие основные задачи:

 - Анализ современных ДСИ и Доверенных Операционных Систем
 - Анализ и сравнение моделей управления доступом.
 - Разработка архитектуры доверенной ОС
 - Разработка Capability-Based модели безопасности ОС
 - Адаптация интерфейса GlobalPlatform TEE Internal Core API под архитектуру RISC-V с расширением WorldGuard
 - Программная реализация доверенной ОС с Capability-Based моделью безопасности
 - Экспериментальная проверка работоспособности разработанной доверенной операционной системы
 - Экспериментальная проверка устойчивости к атаками на ДСИ

 ## Предмет исследования
 Предметом исследования является доверенная операционная система
 для СнК на архитектуре RISC-V с расширением WorldGuard

 ## Объект исследования
 Объектом исследования являются доверенные системы исполнения
 для СнК на архитектуре RISC-V

 ## Методы исследования
 В ходе проведения диссертационных исследований были использованы
 методы компьютерного моделирования СнК syntacore-scr9
 с помошью эмулятора QEMU с расширением WorldGuard
 ОС Linux в качестве УСИ.

 ## Научная новизна
 Научная новизна диссертационной работы заключается в создании
 открытой Доверенной Операционной Системы
 для СнК на архитектуре RISC-V с расширением WorldGuard

 ## Практическая значимость работы
 Практическая значимости диссертационной работы заключается в
 обеспечении Доверенной Среды Исполнения
 для СнК на архитектуре RISC-V с расширением WorldGuard
 благодаря использованию Доверенной Операционной Системы

 ## Достоверность полученных результатов и выводов
 Достоверность полученных результатов и работоспособности разработанной
 Доверенной ОС базируется на корректном использовании методов исследования
 и подтверждается экспериментальными результатами.

 ## Личный вклад автора
 Все основные результаты диссертационной работы,
 включая положения, выносимые на защиту,
 получены автором диссертации лично или при его непосредственном участии.

 ## Положения выносимые на защиту
 - Программная реализация Доверенной Операционной Системы
   для СнК на архитектуре RISC-V с расширением WorldGuard
 - Программная реализация Фреймворка Доверенных Приложений
 - Результаты устойчивости к атаками на ДСИ

 ## Структура работы
 Выпускная квалификационная работа состоит из
 введения, четырех глав, заключения,
 списка литературы из ____ наименований и приложения.
 Общий объем диссертации - ___ страницы,
 включая ___ рисунка и ___ таблиц


<div style="page-break-after: always;"></div>
---
