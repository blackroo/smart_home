from django.shortcuts import render
from .models import Dht22,Macaddress
import os
# Create your views here.

file = "../temp/request"

mac_addr = {
    'BA:D3:BC:5D:EA:D9' : "재찬",
    'D6:4E:A0:6D:52:20'  : "엄마",
}



def index(request):
    try :
        dht=Dht22.objects.last()
        mac=Macaddress.objects.last()
    except:
        dht=None
        mac=None
    
    if mac:
        mac_value=[]
        data=mac.mac_data.split(',')

        for d in data:
            data_upper = d.upper()
            if data_upper in mac_addr:
                mac_value.append(mac_addr.get(data_upper))

    context = {
        'dht': dht,
        'mac' : mac_value,
        'mac_time' : mac.date,
        }
    return render(request, 'main/index.html',context)

def request(request):

    if os.path.isfile(file):
        context = {
            "txt" : "이미 요청했습니다."
        }
    else:
        f = open(file,'w')
        f.close()
        context = {
            "txt" : "요청 완료"
        }
    
    return render(request, 'main/request.html',context)
    