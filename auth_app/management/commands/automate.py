from django.core.management.base import BaseCommand, CommandError
from game.models import Profile as MyUser
from game.stage3 import resetScores, startLeague

class Command(BaseCommand):
    help = "The automated third stage. Automatically clears all scores and starts the tournament."

    def handle(self, *args, **kwargs):
        resetScores()
        startLeague()
        print "Reached here"
