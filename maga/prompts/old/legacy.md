# 1. Normal World
 - Основные задачи Rich OS
 - Сценарии использования Rich OS
 - Rich OS хранит уязвимые данные
 - например биометрия, ключи шифрования и тд
 ## 1.1. Безопасность данных на пользовательском уровне
  - мандатный контроль (SELinux, AppArmor, SecureBSD)
 ## 1.2. Защита данных на уровне ядра.
  - изоляция виртуальных адресных пространств, физических устройств
 ## 1.3. Защита данных на аппаратном уровне.
  - использование ARM exception level
  - x86 кольца защиты
  - RISC-V PMP + IOMMU
 ## 1.3. Безопасность процесса загрузки Rich OS
  ### 1.3.1. Порядок загрузки Rich OS
   - ранний загрузчик
   - загрузчик
   - запуск ядра
  ### 1.3.2. Атаки во время загрузки
   - проверка подписи образа ОС
   - подмена подписи образа ОС
 ## 1.4. Атаки в Rich OS
  - получение данных возможно при: при ошибках настройки мандатного доступа
  - чтение памяти других процессов,
  - уязвимости повышения привелегий,
  - компрометации драйверов = ядра, 
  - эксплуатации CVE,
  - эксплуатации hardware уязвимостей (meltdown, spectre), и тд
 ## 1.5. Выводы
  - таким образом нет гарантий ни со стороны железа, ни со стороны софта, что пользовательские данные будут
  - Необходимость Secure World

# 2. Secure World
 - разделение миров, физическое разделение памяти, ограничение доступа к устройствам
 - доступ только доверенных вендоров
 ## 2.1. Специфика Secure OS
  - Отличие Secure OS от Rich OS
  - Задачи Secure OS
 ## 2.2. Порядок загрузки Secure OS
  - доверенная цепочка загрузки (Trust Chain)
 ## 2.2. Аппаратный доверенный режим
  ### 2.2.1. доверенный режим в x86
   - x86 Trusted Execution Technology + TPM
  ### 2.2.2. доверенный режим в  ARM
   - ARM TrustZone
  ### 2.2.2. доверенный режим в RISC-V
   - WorldGuard

# 3. Реализация
 - Загрузчик
 - Ядро
 - системные вызовы

# 4. Валидация
 - пересылка сообщений из Normal World в Secure World
 - примеры атак
