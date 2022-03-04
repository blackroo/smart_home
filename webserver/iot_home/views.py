from django.shortcuts import render,redirect
from .models import Dht22,Macaddress
import os
# Create your views here.

file = "../temp/request"

mac_addr = {
    'BA:D3:BC:5D:EA:D9' : "재찬",   #2G
    '16:4D:D7:B5:B7:CF' : "재찬",   #5G
    'D6:4E:A0:6D:52:20' : "엄마",   #2G
    '2A:B4:1E:49:46:66' : "엄마",   #5G
    #'20:55:31:AE:DF:E9' : "노트5",     
    '7A:F6:E3:B9:3D:04' : "형",     #5G
    '04:39:26:D4:29:B4' : "아빠",   #2G
    '0E:26:18:28:60:C7' : "할머니", #2G
}



def index(request):

    return render(request, 'main/index.html')

def temperatur(request):
    try :
        dht=Dht22.objects.last()
    except:
        dht=None

    context = {
        'dht': dht,
    }

    return render(request, 'main/temperatur.html',context)

def users(request):
    try :
        mac=Macaddress.objects.last()
    except:
        mac=None

    if mac:
        mac_value=[]
        data=mac.mac_data.split(',')

        for d in data:
            data_upper = d.upper()
            print(d)
            if data_upper in mac_addr:
                mac_value.append(mac_addr.get(data_upper))

        context = {
            'mac' : mac_value,
            'mac_time' : mac.date,
            }
    else:
        context = {
            'mac' : mac,
            'mac_time' : mac,
        }

    return render(request, 'main/users.html',context)


def datasetting(request):

    return render(request, 'main/data/datasetting.html')


def request(request):

    if os.path.isfile(file):
        context = {
            "txt" : "이미 요청했습니다.",
            "txt2" : "최대 1분이 소요됩니다."
        }
    else:
        f = open(file,'w')
        f.close()
        context = {
            "txt" : "요청 완료",
            "txt2" : "1분뒤에 확인하세요"
        }
    
    return render(request, 'main/data/request.html',context)


def datacode(request):

    return render(request, 'main/data/datacode.html')


def delete(request):
    # data = camping.objects.filter(location__contains=id).values()
    # camping_list = data.order_by("location")


    if request.method == "POST":
        code= request.POST.get('code', '')

        if code=="delete5477":

            try:
                dht22 = Dht22.objects.all()
                mac = Macaddress.objects.all()
                dht22.delete()
                mac.delete()

            except:
                pass

            return redirect('iot:datasetting')

        

        else :
            return redirect('iot:index')
    
    else:
        return redirect('iot:index')