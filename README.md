# arduino-basics
> A collaborative repo used for keeping track of our very basic arduino projects

## Repo structure:
### servomotor/
<ul>
    <li>servo/</li>
    <ul>
        <li> <strong>servo.ino</strong>: servomotor moves to chosen positions</li>
        <li> <strong>servopot.ino</strong>: servomotor moves mapped to potentiometer value</li>
        <li><strong>servous.ino</strong>: servometer moves mapped to ultrasonic sensor values </li>
    </ul>
</ul>

### us/
<ul>
<li><strong>us.ino</strong>: three LEDs (green, yellow, red) light up as ultrasonic sensor deetects a closer object</li>
</ul>

### led/
<ul>
<li><strong>led.ino</strong>: traffic light using green, yellow, red LEDs</li>
</ul>

### joystick/
<ul>
<li><strong>joystick.ino</strong>: green LED lights up when x axis is changed, red LED when y axis is changed, clicking turns everything off</li>
</ul>

### 2distante/
-  <strong>2distante.ino</strong>: two distance sensors being read

### infrared/
-  <strong>infreared.ino</strong>: read signals from infrared remote using IR sensor and its library

### irled/
-  <strong>irled.ino</strong>: power on&off an LED with the power button on an IR remote

### map_humid_to_servo/
-  <strong>map_humid_to_servo.ino</strong>: using DHT11 module, map servomotor to the humidity that's being read 

### motorfataspate/
-  <strong>motorfataspate.ino</strong>: multiple functions for two DC motors

### temp/
-  <strong>temp.ino</strong>: using DHT11 read temperature and humidity
