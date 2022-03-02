import time
import Adafruit_DHT as dht
import pymysql
import datetime


conn = pymysql.connect(host='localhost', user='iot', password='iot', db='iot', charset='utf8')
cur = conn.cursor()

i=300

while 1:
    if i==300:
        i=0; 
        h,t = dht.read_retry(dht.DHT22, 4)
        temperature = round(t,2)
        humidity = round(h,2)
        #print ('Temp={0:0.1f}*C  Humidity={1:0.1f}%'.format(t, h))
        print(f"temperature={temperature}  humidity={humidity}")

        now = datetime.datetime.now()
        date = f'{now}'
        
        sql =f"""
            insert into iot_home_dht22(temperature,humidity,date) values
            ({temperature},{humidity},'{now}');
            """
        cur.execute(sql)
        conn.commit()
    i+=1
    time.sleep(1)



cur.close()
conn.close()