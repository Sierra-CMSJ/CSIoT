# 📚 Librerías de Criptografía CSIoT

Este repositorio reúne un conjunto de **librerías de criptografía implementadas para entornos IoT**, con el objetivo de proporcionar ejemplos prácticos y documentación clara para su uso en proyectos de seguridad.  

## 🎯 Objetivo del proyecto:

Este proyecto busca:

- Proporcionar implementaciones ligeras y eficientes de algoritmos criptográficos para sistemas embebidos de recursos limitados empleados en proyectos IoT.
- Servir como recurso educativo para estudiantes, investigadores y desarrolladores.
- Medir el impacto en rendimiento y consumo energético de cada algoritmo en microcontroladores.

Cada algoritmo incluye:  
- 📂 **`src/`** → Código fuente de la librería.  
- 📂 **`Examples/`** → Ejemplos prácticos (uso básico, encriptar, desencriptar, medir tiempo, consumo energético, conversión a hexadecimal).  
- 📄 **Explicación en PDF** → Documentación técnica de cada librería.  
- ⚙️ **`library.properties`** → Archivo de propiedades de la librería.  

---

## 🔑 Algoritmos Incluidos

### 🔒 AES (Advanced Encryption Standard)
- **Ejemplos disponibles:** uso básico, encriptar, desencriptar, medir tiempo, consumo energético, conversión a hexadecimal.  
- 📄 [Explicación AES](./Librer%C3%ADas%20Criptograf%C3%ADa%20CSIoT/AES/Explicacion%20AES.pdf)
- 📂 [Ejemplos AES](./Librer%C3%ADas%20Criptograf%C3%ADa%20CSIoT/AES/Examples)

---

### ⚡ ChaCha20
- **Ejemplos disponibles:** uso básico, encriptar, desencriptar, medir tiempo, consumo energético, conversión a hexadecimal.  
- 📄 [Explicación ChaCha20](./Librer%C3%ADas%20Criptograf%C3%ADa%20CSIoT/ChaCha20/Explicacion%20ChaCha20.pdf)  
- 📂 [Ejemplos ChaCha20](./Librer%C3%ADas%20Criptograf%C3%ADa%20CSIoT/ChaCha20/Examples)  

---

### 🧮 ECCTiny (Elliptic Curve Cryptography)
- **Ejemplos disponibles:** uso básico, encriptar, desencriptar, medir tiempo, consumo energético, conversión a hexadecimal.  
- 📂 [Ejemplos ECCTiny](./Librer%C3%ADas%20Criptograf%C3%ADa%20CSIoT/ECCTiny/Examples)  

---

### 🔐 RSA
- **Ejemplos disponibles:** uso básico, encriptar, desencriptar, medir tiempo, consumo energético, conversión a hexadecimal.  
- 📄 [Explicación RSA](./Librer%C3%ADas%20Criptograf%C3%ADa%20CSIoT/RSA/Explicacion%20RSA.pdf)  
- 📂 [Ejemplos RSA](./Librer%C3%ADas%20Criptograf%C3%ADa%20CSIoT/RSA/Examples)  

---

### 📝 SHA-256
- **Ejemplos disponibles:** uso básico, hash de cadenas, medir tiempo, consumo energético, conversión a hexadecimal.  
- 📄 [Explicación SHA-256](./Librer%C3%ADas%20Criptograf%C3%ADa%20CSIoT/SHA-256/Explicacion%20SHA256.pdf)  
- 📂 [Ejemplos SHA-256](./Librer%C3%ADas%20Criptograf%C3%ADa%20CSIoT/SHA-256/Examples)  

---

## 🚀 Ejecución de Ejemplos

1. Clona este repositorio o descarga como .zip el repositorio:  
   ```bash
   git clone https://github.com/Sierra-CMSJ/CSIoT.git

2. Importa la librería en tu entorno (Arduino IDE / PlatformIO)
3. Abre la carpeta del algoritmo que quieras usar.
4. Explora los códigos dentro de Examples/ para aprender y probar.

## 📖 Documentación

Cada carpeta incluye un PDF explicativo con la documentación técnica detrás de cada algoritmo y detalles relevantes para comprender su funcionamiento en sistemas embebidos e IoT.
Usa esta documentación para implementar algoritmos de criptografía en tus proyectos IoT e implementa capas de seguridad en cada proyecto.

## 📊 Resultados Obtenidos

En esta sección se presentan los resultados experimentales obtenidos al ejecutar los ejemplos en diferentes microcontroladores IoT como ESP32, STM32, Arduino Uno y Raspberry Pi Pico:

- Medición de tiempos de ejecución para cada algoritmo.
- Evaluación del consumo energético asociado a los procesos de cifrado/descifrado.
- Comparación de eficiencia entre algoritmos en entornos de recursos limitados.

## 💡 Recomendaciones de Uso en IoT

Este repositorio está pensado como un recurso técnico para proyectos que busquen implementar seguridad mediante criptografía en proyectos IoT que empleen microcontroladores de bajo costo como ESP32, STM32, Arduino Uno y Raspberry Pi Pico.

### Algunas recomendaciones de uso:

* Utilizar AES o ChaCha20 para cifrado simétrico en comunicaciones de baja latencia.
* Emplear RSA o ECC para el intercambio seguro de llaves y autenticación.
* Integrar SHA-256 para verificación de integridad y autenticación de mensajes.
* Validar el impacto en rendimiento y energía antes de elegir un algoritmo para un dispositivo específico.

## 🙎‍♂️🙎‍♂️ Autores:

- **Cristian Manuel Sierra Jerez**
- **Abad Plata Vera**
