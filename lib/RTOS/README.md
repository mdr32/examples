

## Установка FreeRTOS с укороченной историей

Установка операционной системы полностью

```bash
git clone --depth 1 --branch 202112.00 git@github.com:FreeRTOS/FreeRTOS.git ./second --recurse-submodules
```

Установка только ядра

```bash
git clone --depth 1 --branch V10.6.0 git@github.com:FreeRTOS/FreeRTOS-Kernel.git ./FreeRTOS-Kernel --recurse-submodules
```