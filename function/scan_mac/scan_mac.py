from ipaddress import ip_address
import os


ROUTER_IP = "172.30.1.254/24"

def main():
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
                    print(mac)
                    mac_list.append(mac)





main()