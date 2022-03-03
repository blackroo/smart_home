import pymysql
import os
import time
import datetime


file = "../../temp/request"
ROUTER_IP = "172.30.1.254/24"
scantime=3600
i=scantime


def mac_scan():
    print("ip스캔중...")
    ip_linux = os.popen(f"nmap -sn {ROUTER_IP}").read()
    ip_list=[]
    mac_list=[]
    #print(data)

    data_split=ip_linux.split('\n')

    for line in data_split:
        if(line.find("Nmap scan report for"))!=-1:
            ip=line.split("Nmap scan report for ")
            ip_list.append(ip[1])

            mac_linux = os.popen(f"arp {ip[1]}").read()
            #print(mac_linux)
            mac_split = mac_linux.split('\n')

            for i in mac_split:
                location = i.find("ether   ")
                if location!=-1:
                    mac=i[location+8:location+25]
                    mac_list.append(mac)

    
    # for m in mac_list:
    #     print(m)

    db_mac = ','.join(map(str,mac_list))
    print(db_mac)


    return db_mac

def check_request():
    if os.path.isfile(file):
        time.sleep(5)
        try:
            os.remove(file)
        except:
            pass
        return 1
    else:
        return 0



def main():
    i=scantime
    conn = pymysql.connect(host='localhost', user='iot', password='iot', db='iot', charset='utf8')
    cur = conn.cursor()

    while(1):
        if i==scantime:
            i=0
            db_mac = mac_scan()
            now = datetime.datetime.now()
            date = f'{now}'

            sql =f"""
                insert into iot_home_macaddress(mac_data,date) values
                ('{db_mac}','{now}');
                """
            cur.execute(sql)
            conn.commit()
            print("db저장")
        i+=1
        if(check_request()==1):
            i=scantime

        time.sleep(1)


main()