from django.db import models

# Create your models here.


class Dht22(models.Model):
    temperature = models.FloatField()
    humidity = models.FloatField()
    date =  models.DateTimeField()
    
    def __str__(self):
        return self.temperature

class Macaddress(models.Model):
    mac_data = models.TextField()
    date =  models.DateTimeField()

    def __str__(self):
        return self.mac_data