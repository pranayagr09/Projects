from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^see', views.see, name='see'),
    url(r'^Login', views.Login, name='Login'),
    url(r'^InsLogin', views.InsLogin, name='InsLogin'),
    url(r'^courseadd', views.courseadd, name='courseadd'),
    url(r'^update', views.update, name='update'),
    url(r'^Logout', views.logout_view, name='logout'),
    url(r'^InsLogout', views.logout_ins, name='logout_ins'),
    url(r'^adminPage', views.adminPage, name='adminPage'),
    url(r'^signup', views.signup, name='signup'),
    url(r'^register', views.register, name='register'),
    url(r'^addStudent', views.addStudent, name='addStudent'),
    url(r'^insPage', views.insPage, name='insPage'),
    url(r'^facebook', views.facebook, name='facebook'),
    url(r'^app_login', views.app_login, name='app_login'),
    url(r'^addDeadline', views.addDeadline, name='addDeadline'),
    url(r'^addFeedback', views.addFeedback, name='addFeedback'),
    url(r'^viewFeedback/(\d+)', views.viewFeedback, name='viewFeedback'),
    url(r'^viewGraph/(\w+)', views.viewGraph, name='viewGraph'),
    url(r'^viewAg/(\d+)', views.viewAg, name='viewAg'),
]