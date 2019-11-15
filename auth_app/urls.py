from django.conf.urls import url
from auth_app.views import *

urlpatterns = [
    url(r'^$', LoginView.as_view(), name="user_login"),
    url(r'^success/$', SuccessView.as_view(), name="login_success"),
    url(r'^logout/$', LogoutView.as_view(), name="user_logout"),
    url(r'^register/$', RegisterView.as_view(), name="user_register"),
    url(r'^play/$', PlayableUI.as_view(), name="playable_ui"),
    url(r'^submit/$', GridView.as_view(), name="grid"),
    url(r'^leader/$', LeaderBoard.as_view(), name="leader")
]
