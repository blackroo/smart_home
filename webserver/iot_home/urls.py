from django.urls import path
# from .views import index, detail, answer_create
from . import views

app_name = 'home'
urlpatterns = [
    path('', views.index, name='index'),
]