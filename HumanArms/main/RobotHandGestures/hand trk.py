import cv2
from cvzone.HandTrackingModule import HandDetector
import time
import serial
import cvzone

detector = HandDetector(maxHands=1, detectionCon=0.8)
video = cv2.VideoCapture(0)
arduino=serial.Serial("COM4", 9600, 1)
# sendData = cvzone.SerialObject("COM4", 9600, 1)

while True:
    _, img = video.read()
    img = cv2.flip(img, 1)
    hand = detector.findHands(img, draw=False)
    if hand:
        lmlist = hand[0]
        if lmlist:
            fingerup = detector.fingersUp(lmlist)
            print(fingerup)
            sendData.sendData(fingerup)
            if fingerup == [0, 0, 0, 0, 0]:
                # arduino.write(bytes('0','utf-8'))
                print("0")
            if fingerup == [0, 1, 0, 0, 0]:
                # arduino.write(bytes('1','utf-8'))
                print("1")
            if fingerup == [0, 1, 1, 0, 0]:
                # arduino.write(bytes('2','utf-8'))
                print("2")
            if fingerup == [0, 1, 1, 1, 0]:
                # arduino.write(bytes('3','utf-8'))
                print("3")
            if fingerup == [0, 1, 1, 1, 1]:
                # arduino.write(bytes('4','utf-8'))
                print("4")
            if fingerup == [1, 1, 1, 1, 1]:
                # arduino.write(bytes('5','utf-8'))
                print("5")

    cv2.imshow("Video",img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    time.sleep(0.1)

video.release()
cv2.destroyAllWindows()