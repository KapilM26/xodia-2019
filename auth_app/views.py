# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render, redirect
from django.contrib.auth import authenticate, login, logout
from django.http import HttpResponseRedirect, HttpResponse
from django.urls import reverse
from .models import User
from .models import Profile
from django.views.generic import View
from django.db.utils import IntegrityError
import urllib2
import urllib
import json
from django.conf import settings
from django.core.files.storage import FileSystemStorage
from .__init__ import path
import os
from .tests import parseCompileTest
from .RequestQueue import RequestQueue, request_queue
from .Sandbox import SandboxRequest
from sys import argv

# Create your views here.

bot_path = path + "files/"
match_path = path + "matches/"
# parallel thread which executes match requests one at a time
match_runner = RequestQueue()
if "runserver" not in argv:
    match_runner.daemon = True  # enable Ctrl-C to terminate the whole program + thread
match_runner.start()


class LoginView(View):
    template_name = 'auth_app/index.html'

    def get(self, request):
        if request.user.is_authenticated():
            # user = request.user.username
            # return render(request, 'auth_app/postlogin.html', {'username': user})
            return HttpResponseRedirect(reverse('login_success'))
        else:
            return render(request, self.template_name)

    def post(self, request):
        context = {}
        username = request.POST['username']
        password = request.POST['password']
        user = authenticate(
            request=request, username=username, password=password)
        if user:
            login(request, user)
            return HttpResponseRedirect(reverse('login_success'))
        else:
            context["error"] = "Incorrect Credentials!"
            return render(request, self.template_name, context)


class LogoutView(View):
    def post(self, request):
        logout(request)
        return HttpResponseRedirect(reverse('user_login'))

    def get(self, request):
        logout(request)
        return HttpResponseRedirect(reverse('user_login'))


class SuccessView(View):
    template_name = 'auth_app/postlogin.html'

    def get(self, request):
        if request.user.is_authenticated():
            context = {}
            context['user'] = request.user
            return render(request, self.template_name, context)
        else:
            return HttpResponseRedirect(reverse('user_login'))


class RegisterView(View):
    template_name = 'auth_app/register.html'

    def get(self, request):
        if request.user.is_authenticated():
            # user = request.user.username
            # return render(request, 'auth_app/postlogin.html', {'username': user})
            return HttpResponseRedirect(reverse('login_success'))
        else:
            return render(request, self.template_name)

    def post(self, request):
        try:
            profile = Profile()
            user = User()
            user.username = request.POST['username']
            user.set_password(request.POST['password'])
            user.first_name = request.POST['first_name']
            user.last_name = request.POST['last_name']
            user.email = request.POST['email']
            recaptcha_response = request.POST.get('g-recaptcha-response')
            url = 'https://www.google.com/recaptcha/api/siteverify'
            values = {
                'secret': settings.GOOGLE_RECAPTCHA_SECRET_KEY,
                'response': recaptcha_response
            }
            data = urllib.urlencode(values)
            req = urllib2.Request(url, data)
            response = urllib2.urlopen(req)
            result = json.load(response)
            if not result['success']:
                return render(request, self.template_name, {'error': 'Invalid Captcha!'})
            user.save()
            profile.user = user
            profile.college_name = request.POST['college_name']
            profile.phone_no = request.POST['phone_no']
            profile.create_myuser()
            profile.save()
            login(request, user)

        except IntegrityError:
            context = {'error': 'Username already exists!'}
            return render(request, self.template_name, context)

        return HttpResponseRedirect(reverse('user_login'))


class PlayableUI(View):
    template_name = 'auth_app/playable_ui.html'

    def get(self, request):
        au = request.user.is_authenticated
        return render(request, self.template_name, {'au': au})


class GridView(View):
    template_name = 'auth_app/submit_ui.html'

    def get(self, request):
        au = request.user.is_authenticated
        if request.user.is_authenticated:
            all_players = User.objects.all()
            return render(request, self.template_name, {'pro': all_players, 'au': au, 'opp': 39})
        else:
            return HttpResponseRedirect(reverse('user_login'))

    def post(self, request):
        if request.user.is_authenticated:
            if 'upload' in request.POST:
                return self.uploadBot(request)
            elif 'matchreq' in request.POST:
                return self.matchGame(request)
            elif 'viewlog' in request.POST:
                return self.viewLogs(request)
        else:
            return redirect('user_login')

    def uploadBot(self, request):
        player = Profile.objects.get(user=request.user)
        au = request.user.is_authenticated
        all_players = User.objects.all()
        play = request.FILES['botup']

        ext = play.name.split('.')[-1]
        if play.size > 1000000:
            return render(request, self.template_name, {'ms': 'File size should be less than 1 MB!', 'pro': all_players, 'au': au, 'opp': 39})

        if ext in ['cpp', 'c']:
            old_file = player.bot_path + '.' + player.bot_ext
            new_file = player.bot_path + '.' + ext
            os.rename(old_file, new_file)
            f = open(new_file, 'w+')

            for chunk in play.chunks():
                f.write(chunk)
            f.close()

            player.bot_ext = ext

            player.save()
            return render(request, self.template_name, {'ms': 'Bot uploaded!', 'pro': all_players, 'au': au, 'opp': 39})

        else:
            return render(request, self.template_name, {'ms': 'File should be a C or C++ file!', 'pro': all_players, 'au': au, 'opp': 39})

    def matchGame(self, request):
        pro = User.objects.all()
        au = request.user.is_authenticated
        curr_obj = request.user
        prof = Profile.objects.get(user=curr_obj)
        opp_id = request.POST['oppid']
        if not opp_id:
            return render(request, self.template_name,
                          {'ms': 'Please Select an opponent', 'au': au, 'pro': pro, 'opp': 39})
        my_id = curr_obj.pk
        match = str(my_id) + 'v' + opp_id
        reverse_match = opp_id + 'v' + str(my_id)
        for match_temp in request_queue:
            if match_temp.identifier_string == match:
                return render(request, self.template_name, {'ms': 'Match is already in queue', 'au': au, 'pro': pro,
                                                            'username': request.user.username, 'opp': int(opp_id)})

        ext1 = prof.bot_ext
        opp_user = User.objects.get(pk=int(opp_id))
        ext2 = Profile.objects.get(user=opp_user).bot_ext
        result = parseCompileTest(my_id, ext1, opp_id, ext2)
        if result is not None:
            print(result)
            return render(request, self.template_name,
                          {'ms': result, 'au': au, 'pro': pro, 'username': request.user.username, 'opp': int(opp_id)})
        if os.path.isfile(match_path + 'log' + match):
            os.remove(match_path + 'log' + match)
            os.remove(match_path + 'error' + match)
        if os.path.isfile(match_path + 'log' + reverse_match):
            os.remove(match_path + 'log' + reverse_match)
            os.remove(match_path + 'error' + reverse_match)
        match_obj = SandboxRequest(
            user1_id=my_id, user2_id=opp_id, bot1_ext=ext1, bot2_ext=ext2)
        print("Temp", match_obj)
        request_queue.append(match_obj)
        match_runner.set_flag()
        return render(request, self.template_name, {'ms': 'Match requested!', 'au': au, 'pro': pro, 'username': request.user.username, 'opp': int(opp_id)})

    def viewLogs(self, request):
        player = request.user
        opp_id = request.POST['oppid']
        opp = User.objects.get(pk=opp_id)
        pro = User.objects.all()
        au = request.user.is_authenticated
        p2flag = request.POST.get('p2flag')
        print("p2flag"+str(p2flag))
        if not p2flag:
            try:
                error_file = open(
                    (match_path + "error" + str(player.pk) + "v" + str(opp.pk)), "r")
                error_pass = error_file.read().split('\n')
                error_file.close()
            except:
                return render(request, self.template_name, {'ms': 'Match not processed yet!', 'au': au, 'pro': pro, 'username': request.user.username, 'opp': int(opp_id)})

            if os.path.isfile(match_path + "log" + str(player.pk) + "v" + str(opp.pk)):
                log_file = open(match_path + "log" +
                                str(player.pk) + "v" + str(opp.pk), "r")
                log_pass = log_file.read().split('\n')
                log_file.close()

        else:
            try:
                error_file = open(
                    (match_path + "error" + str(opp.pk) + "v" + str(player.pk)), "r")
                error_pass = error_file.read().split('\n')
                error_file.close()
            except:
                return render(request, self.template_name, {'ms': 'Match not processed yet!', 'au': au, 'pro': pro, 'username': request.user.username, 'opp': int(opp_id)})

            if os.path.isfile(match_path + "log" + str(opp.pk) + "v" + str(player.pk)):
                log_file = open(match_path + "log" +
                                str(opp.pk) + "v" + str(player.pk), "r")
                log_pass = log_file.read().split('\n')
                log_file.close()

        return render(request, self.template_name, {'error': error_pass, 'log': log_pass, 'au': au, 'pro': pro, 'username': request.user.username, 'opp': int(opp_id)})


class LeaderBoard(View):
    template_name = 'auth_app/leaderboard.html'

    def get(self, request):
        au = request.user.is_authenticated
        pro = Profile.objects.all().order_by('-score')
        return render(request, self.template_name, {'au': au, 'pro': pro})
