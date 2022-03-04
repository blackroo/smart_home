import time
import Adafruit_DHT as dht
import pymysql
import datetime
import os


conn = pymysql.connect(host='localhost', user='iot', password='iot', db='iot', charset='utf8')
cur = conn.cursor()
file = "../../temp/request"
scantime=600
i=scantime

def check_request():
    if os.path.isfile(file):
        time.sleep(10)
        return 1
    else:
        return 0


while 1:
    if i==scantime:
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
    if(check_request()==1):
        i=scantime
    time.sleep(1)



cur.close()
conn.close()