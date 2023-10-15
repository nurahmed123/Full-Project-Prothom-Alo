import cv2
import serial

# Initialize the serial port
ser = serial.Serial('COM3', 9600)  # Update with your Arduino's serial port

# Initialize the camera
cap = cv2.VideoCapture(0)  # Use the appropriate camera index if you have multiple cameras

# Loop over the captured frames
while True:
    # Read a frame from the video stream
    ret, frame = cap.read()

    # Process the frame (add your own image processing code here)
    # For example, you can convert the frame to grayscale:
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Determine the corresponding servo positions based on finger movement
    # Modify this logic based on your specific requirements
    # Here, we assume you have calculated servo positions as angles in the range [0, 180]
    servo1_angle = 90  # Example servo angle
    servo2_angle = 120  # Example servo angle
    servo3_angle = 60  # Example servo angle
    servo4_angle = 30  # Example servo angle
    servo5_angle = 150  # Example servo angle

    # Send servo positions to the Arduino
    # Format: "s1_angle s2_angle s3_angle s4_angle s5_angle\n"
    command = "{} {} {} {} {}\n".format(servo1_angle, servo2_angle, servo3_angle, servo4_angle, servo5_angle)
    ser.write(command.encode())

    # Display the processed frame (optional)
    cv2.imshow('Processed Frame', gray)

    # Check for key press to exit the loop
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the video capture and close the serial connection
cap.release()
ser.close()
cv2.destroyAllWindows()
