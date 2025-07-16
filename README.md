#Real-Time Alarm Clock 

This project uses an ESP32 to create a Wi-Fi-synced alarm clock. It connects to an NTP server to get real-time updates and displays the current time and date on a 16x2 I2C LCD. Users can set an alarm using four buttons. When the set time is reached, a buzzer plays a melody until stopped.

The LCD shows live time updates. Button 4 enters alarm setup mode, while Buttons 1–3 are used to adjust hours, minutes, seconds, day, month, and year. Pressing Button 4 again saves the alarm. If the alarm time matches the current time, the buzzer sounds until the user stops it with Button 4.

Update the ssid and password in the code to connect to your Wi-Fi.
