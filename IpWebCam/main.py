import cv2
import sys
import serial

faceCascade = cv2.CascadeClassifier('faceCascade.xml')

url = 'http://192.168.1.66:8080/shot.jpg'
cap = cv2.VideoCapture(url)

### serialArduino = serial.Serial("COM4",9600)

if cap.isOpened():
    print("Ip Cam initializatized")
else:
    print("Ip Cam disconnected")
    sys.exit(1)

winName = 'IP_CAM'
cv2.namedWindow(winName, cv2.WINDOW_AUTOSIZE)

while True:

    cap.open(url)
    ret, frame = cap.read()

    if ret:
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces = faceCascade.detectMultiScale(gray, scaleFactor=1.3, minNeighbors=5)

        for (x, y, w, h) in faces:
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
            print(x - 255, y - 255, x + w - 255, y + h - 255)

            if (y - 255 > -20):
                print("moviendo hacia adelante")
                ### cad = 'u'
                ### serialArduino.write(cad.encode('ascii'))
                ### cad2 = serialArduino.readline().decode('ascii')
                ### print(cad2)
            else:
                if (y - 255 < -100):
                    print("moviendo hacia atras")
                    ### cad = 'd'
                    ### serialArduino.write(cad.encode('ascii'))
                    ### cad2 = serialArduino.readline().decode('ascii')
                    ### print(cad2)
            if (x - 255 < -125):
                print("moviendo hacia la derecha")
                ### cad = 'r'
                ### serialArduino.write(cad.encode('ascii'))
                ### cad2 = serialArduino.readline().decode('ascii')
                ### print(cad2)
            else:
                if (x - 255 > 125):
                    print("moviendo hacia la izquierda")
                    ### cad = 'l'
                    ### serialArduino.write(cad.encode('ascii'))
                    ### cad2 = serialArduino.readline().decode('ascii')
                    ### print(cad2)

        cv2.circle(frame, (int(frame.shape[1] / 2), int(frame.shape[0] / 2)), 20, (0, 0, 255), 3)
        cv2.imshow(winName, frame)
    else:
        print("Ip Cam disconnected")
        break

    if (cv2.waitKey(10) & 0xFF == 27):
        break

cap.release()
cv2.destroyAllWindows()
