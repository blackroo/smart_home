from django.urls import path
# from .views import index, detail, answer_create
from . import views

app_name = 'iot'
urlpatterns = [
    path('', views.index, name='index'),
    path('temperatur', views.temperatur, name='temperatur'),
    path('users', views.users, name='users'),
    path('datasetting/', views.datasetting, name='datasetting'),
    path('request/', views.request, name='request'),
    path('datacode/', views.datacode, name='datacode'),
    path('delete/', views.delete, name="delete"),
]