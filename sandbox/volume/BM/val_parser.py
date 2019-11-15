
# We are using 0 and 1 to denote players. 0->makes 1st move.


def parser_func(data, popen_val_obj):
    data = data.rstrip('\n')
    data = data + '\n'
    popen_val_obj.stdin.write(data)
    bucket = popen_val_obj.stdout.readline()
    if bucket == "VALID\n":
        return popen_val_obj.stdout.readline()
    elif bucket == "WIN\n":
        #player_num = popen_val_obj.stdout.readline().rstrip('\n')
        #scores_string = popen_val_obj.stdout.readline().rstrip('\n')
        end_move = popen_val_obj.stdout.readline().rstrip('\n')
        who_won = popen_val_obj.stdout.readline().rstrip('\n')
        how_won = popen_val_obj.stdout.readline().rstrip('\n')
        exception_obj = EndGameError(
            'w,' + who_won + ',' + end_move + ',' + how_won, int(who_won))
        raise exception_obj
    elif bucket == "DRAW\n":
        #scores_string = popen_val_obj.stdout.readline().rstrip('\n')
        #end_move = popen_val_obj.stdout.readline().rstrip('\n')
        #turn_string = popen_val_obj.stdout.readline().rstrip('\n')
        exception_obj = EndGameError(
            'GAME DRAWN,', -1)  # change 0 to -1?
        raise exception_obj
    else:
        raise ValueError(bucket)


class EndGameError(Exception):
    def __init__(self, string, winner):
        super(EndGameError, self).__init__(string)
        if winner is 0:
            self.winner = 100 + 1
        elif winner is 1:
            self.winner = 100 + 2
        elif winner is -1:
            self.winner = 100
