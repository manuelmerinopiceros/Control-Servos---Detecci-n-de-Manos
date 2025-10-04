import cv2
import cvzone
import serial
import time

# Configuración del puerto serial
COM_PORT = "COM14"  # Ajusta según tu Arduino
BAUD_RATE = 9600

# Iniciar conexión serial
try:
    ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Esperar a que el Arduino reinicie
    print(f"Conectado a {COM_PORT}")
except Exception as e:
    print(f"No se pudo conectar al puerto {COM_PORT}: {e}")
    ser = None

# Inicializar cámara y detector
cap = cv2.VideoCapture(0)
detector = cvzone.HandDetector(detectionCon=1, maxHands=2)

print("Sistema iniciado. Presiona 'q' para salir.")

while True:
    success, img = cap.read()
    if not success:
        continue

    # ✅ Versión antigua de cvzone
    img = detector.findHands(img)  # Dibuja la mano en img
    lmList, bbox = detector.findPosition(img)  # Obtiene landmarks

    if lmList:
        fingers = detector.fingersUp()  # Ej: [1, 0, 0, 0, 0]
        print("Dedos:", fingers)

        # Crear cadena tipo [1, 0, 0, 0, 0]
        data_str = "[" + ", ".join(str(f) for f in fingers) + "]\n"
        print("Enviando:", data_str.strip())

        if ser and ser.is_open:
            ser.write(data_str.encode('utf-8'))

    cv2.imshow("Image", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
if ser:
    ser.close()
cv2.destroyAllWindows()
