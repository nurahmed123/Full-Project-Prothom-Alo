# import cvzone
# import cv2

# cap = cv2.VideoCapture(1)
# detector = cvzone.HandDetector(maxHands=1, detectinCon=0.7)


# while True:
#     success, image = cap.read()
#     img = detector.findHands(img)
#     lmList, bbox = detector.findPosition(img)
#     cv2.imshow("image", img)
#     cv2.waitKey(1)

# import cvzone
# import cv2

# cap = cv2.VideoCapture(1)


# while True:
#     success, img = cap.read()
    
#     cv2.imshow("Image", img)
#     cv2.waitKey(1)

# import cv2
# import HandTrackingModule as htm

# wCam, hCam = 440, 480, 

# cap = cv2.VideoCapture(1)
# cap.set(3, wCam)
# cap.set(4, hCam)

# detector = htm.handDetector(maxHands=1)

# while True:
#     success , img = cap.read()
#     img = detector.findHands(img)
#     lmList, bbox = detector.findPosition(img)
#     cv2.imshow("Image", img)
#     cv2.waitKey(1)




# import cv2
# import mediapipe as mp
# import time

# cap = cv2.VideoCapture(0)

# mp_hands = mp.solutions.hands
# hands = mp_hands.Hands()
# mp_draw = mp.solutions.drawing_utils

# prev_time = 0
# cur_time = 0


# while True:
#     _, img = cap.read()
#     imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
#     results = hands.process(imgRGB)
#     fingers = hands.fingersUP()
#     print(fingers)
#     # print("[INFO] handmarks: {}".format(results.multi_hand_landmarks))

#     if results.multi_hand_landmarks:
#         for hand_landmarks in results.multi_hand_landmarks:
#             for index, lm in enumerate(hand_landmarks.landmark):
#                 height, width, channel = img.shape
#                 cx, cy = int(lm.x * width), int(lm.y * height)
#                 cv2.circle(img, (cx, cy), 10, (255, 0, 255), cv2.FILLED)
#             mp_draw.draw_landmarks(img, hand_landmarks, mp_hands.HAND_CONNECTIONS)

#     cur_time = time.time()
#     fps = 1/(cur_time-prev_time)
#     prev_time = cur_time

#     cv2.putText(img, str(int(fps)), (10, 70), cv2.FONT_HERSHEY_PLAIN, 3, (255, 0, 255), 3)

#     cv2.imshow("Image", img)
#     if cv2.waitKey(1) & 0xFF == ord('q'):
#         break

import cv2
import mediapipe as mp

cap = cv2.VideoCapture(0)
mp_Hands = mp.solutions.hands
hands = mp_Hands.Hands()
mpDraw = mp.solutions.drawing_utils
finger_Coord = [(8, 6), (12, 10), (16, 14), (20, 18)]
thumb_Coord = (4,2)

while True:
    success, image = cap.read()
    RGB_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    results = hands.process(RGB_image)
    multiLandMarks = results.multi_hand_landmarks
    if multiLandMarks:
        handList = []
        for handLms in multiLandMarks:
            mpDraw.draw_landmarks(image, handLms, mp_Hands.HAND_CONNECTIONS)
            for idx, lm in enumerate(handLms.landmark):
                h, w, c = image.shape
                cx, cy = int(lm.x * w), int(lm.y * h)
                handList.append((cx, cy))
                for point in handList:
                    cv2.circle(image, point, 10, (255, 255, 0), cv2.FILLED)
                    upCount = 0
        for coordinate in finger_Coord:
            if handList[coordinate[0]][1] < handList[coordinate[1]][1]:
                upCount += 1
        if handList[thumb_Coord[0]][0] > handList[thumb_Coord[1]][0]:
            upCount += 1
            cv2.putText(image, str(upCount), (150,150), cv2.FONT_HERSHEY_PLAIN, 12, (0,255,0), 12)

    cv2.imshow("Counting number of fingers", image)
    cv2.waitKey(1)