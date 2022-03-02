import time
import Adafruit_DHT as dht
while 1: 
    h,t = dht.read_retry(dht.DHT22, 4)
    print ('Temp={0:0.1f}*C  Humidity={1:0.1f}%'.format(t, h))
    time.sleep(2)
