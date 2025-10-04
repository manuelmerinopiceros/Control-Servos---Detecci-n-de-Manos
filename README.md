# Control de Servos con Detección de Manos

Sistema de control de servomotores mediante reconocimiento de gestos de mano usando OpenCV y Arduino.

## 📋 Descripción

Este proyecto permite controlar 5 servomotores (uno por cada dedo de la mano) mediante la detección de gestos en tiempo real usando una cámara web. Utiliza la librería cvzone para detectar la posición de los dedos y envía comandos al Arduino vía puerto serial.

## 🔧 Hardware Requerido

- Arduino (Uno, Mega, Nano, etc.)
- 5 Servomotores
- Cables de conexión
- Cámara web

## 🔌 Conexiones Arduino

| Servo | Pin Arduino |
|-------|-------------|
| Pulgar (Thumb) | 9 |
| Índice (Index) | 10 |
| Meñique (Pinky) | 11 |
| Anular (Ring) | 12 |
| Medio (Middle) | 13 |

## 🚀 Instalación

### 1. Clonar el repositorio

```bash
git clone <url-del-repositorio>
cd <nombre-del-repositorio>
```

### 2. Crear entorno virtual

```bash
python -m venv venv
```

### 3. Activar entorno virtual

**Windows:**
```bash
venv\Scripts\activate
```

**Linux/Mac:**
```bash
source venv/bin/activate
```

### 4. Instalar dependencias

```bash
pip install -r requirements.txt
```

### 5. Cargar código Arduino

1. Abre `ArduinoSerial.ino` con el IDE de Arduino
2. Conecta tu Arduino al PC
3. Selecciona el puerto y placa correctos
4. Sube el código al Arduino

### 6. Configurar puerto COM

Edita `main.py` y ajusta la variable `COM_PORT`:

```python
COM_PORT = "COM14"  # Cambia según tu puerto
```

Para encontrar tu puerto:
- **Windows:** Abre el Administrador de Dispositivos → Puertos (COM y LPT)
- **Linux:** `ls /dev/ttyUSB*` o `ls /dev/ttyACM*`
- **Mac:** `ls /dev/tty.*`

## ▶️ Uso

1. Asegúrate de que el entorno virtual esté activado
2. Conecta el Arduino al PC
3. Ejecuta el programa:

```bash
python main.py
```

4. Coloca tu mano frente a la cámara
5. Los servos se moverán según los dedos que levantes
6. Presiona `q` para salir

## 📊 Formato de Datos

El sistema envía datos en formato: `[pinky, ring, middle, index, thumb]`

- `1` = Dedo levantado → Servo a 180°
- `0` = Dedo cerrado → Servo a 0°

Ejemplo: `[1, 0, 0, 0, 0]` = Solo meñique levantado

## 🛠️ Solución de Problemas

### Error de conexión serial
- Verifica que el Arduino esté conectado
- Confirma el puerto COM correcto
- Asegúrate de que ningún otro programa esté usando el puerto
- Cierra el Serial Monitor del IDE de Arduino

### No detecta la mano
- Ajusta la iluminación
- Modifica `detectionCon` en `main.py` (valores entre 0.5 y 1)
- Acerca o aleja la mano de la cámara

### Error con cvzone
- Asegúrate de tener la versión correcta instalada
- Verifica que la cámara funcione correctamente

## 📦 Dependencias

- Python 3.7+
- opencv-python
- cvzone
- pyserial
- mediapipe

## 📝 Licencia

MIT License

## 👤 Autor

Manuel Merino

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor, abre un issue primero para discutir los cambios que te gustaría realizar.