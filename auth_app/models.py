# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models
from django.contrib.auth.models import User
from django.db.models.signals import post_save
from django.dispatch import receiver
from .__init__ import path
# Create your models here.


class Profile(models.Model):
    user = models.OneToOneField(
        User, on_delete=models.CASCADE, related_name='userprofile')
    phone_no = models.CharField(max_length=10)
    college_name = models.CharField(max_length=20)
    score = models.IntegerField(default=0)
    gwon = models.IntegerField(default=0)
    glost = models.IntegerField(default=0)
    gdrawn = models.IntegerField(default=0)
    bot_ext = models.CharField(max_length=5, default="cpp")
    bot_path = models.CharField(max_length=50, default="")

    def __str__(self):
        return self.user.username

    def create_myuser(self, *args, **kwargs):  # Overriding default save method
        # First set bot_path. No extension included
        self.bot_path = path + "files/bot" + str(self.user.pk)
        print(self.bot_path)
        f = open(self.bot_path + '.' + self.bot_ext, 'w')
        f.close()
        try:
            super(Profile, self).save()  # Call default save method
        except:
            print("Exception occurred:")

    def update(self):
        try:
            super(Profile, self).save()
        except:
            return False
        return True
