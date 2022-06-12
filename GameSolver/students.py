import random

from agents import Agent
import math
from threading import Thread
from multiprocessing.pool import ThreadPool
# Example agent, behaves randomly.
# ONLY StudentAgent and his descendants have a 0 id. ONLY one agent of this type must be present in a game.
# Agents from bots.py have successive ids in a range from 1 to number_of_bots.
class StudentAgent(Agent):
    def __init__(self, position, file_name):
        super().__init__(position, file_name)
        self.id = 0

    @staticmethod
    def kind():
        return '0'

    # Student shall override this method in derived classes.
    # This method should return one of the legal actions (from the Actions class) for the current state.
    # state - represents a state object.
    # max_levels - maximum depth in a tree search. If max_levels eq -1 than the tree search depth is unlimited.
    def get_next_action(self, state, max_levels):
        actions = self.get_legal_actions(state)  # equivalent of state.get_legal_actions(self.id)
        chosen_action = actions[random.randint(0, len(actions) - 1)]
        # Example of a new_state creation (for a chosen_action of a self.id agent):
        # new_state = state.apply_action(self.id, chosen_action)
        return chosen_action


class MinimaxAgent(StudentAgent):
    def minimax(self,state, player, level, max_levels):
        actions = state.get_legal_actions(player)
        if len(actions) == 0:
            if (0 == player):
                return -10
            else:
                return 10
        if (level == max_levels):
            return len(state.get_legal_actions(0)) - len(state.get_legal_actions(1))
        if player == 0:
            score = -math.inf
            for succ in actions:
                maybe_new_score = self.minimax(state.apply_action(player,succ),1, level+1, max_levels)
                if maybe_new_score > score:
                    score = maybe_new_score
            return score
        else:
            score = +math.inf
            for succ in actions:
                score = min(score, self.minimax(state.apply_action(player,succ),0, level+1, max_levels))
            return score
    def get_next_action(self, state, max_levels):
        actions = state.get_legal_actions(0)
        if len(actions) == 1:
            return actions[0]
        score = -math.inf
        definitive_action = actions[0]
        for succ in actions:
            maybe_new_score = self.minimax(state.apply_action(0,succ),1, 1, max_levels)
            if maybe_new_score > score:
                score = maybe_new_score
                definitive_action = succ
        return definitive_action




class MinimaxABAgent(StudentAgent):

    def minimaxAB(self, state, player, level, max_levels, alfa, beta):
        my_player = player
        if (self.kind() == '3' and player == 0):
            my_player = 1
        elif self.kind() == '3' and player == 1:
            my_player = 0
        actions = state.get_legal_actions(my_player)
        if len(actions) == 0:
            if player == 0:
                return -10
            else:
                return 10
        if (level == max_levels):
            return len(state.get_legal_actions(my_player)) - len(state.get_legal_actions(1 - my_player))
        if player == 0:
            score = -math.inf
            for succ in actions:
                maybe_new_score = self.minimaxAB(state.apply_action(my_player,succ),1, level+1, max_levels, alfa, beta)
                if maybe_new_score > score:
                    score = maybe_new_score
                alfa = max(alfa, score)
                if alfa >= beta : break 
            return score
        else:
            score = +math.inf
            for succ in actions:
                score = min(score, self.minimaxAB(state.apply_action(my_player,succ),0, level+1, max_levels, alfa, beta))
                beta = min(beta, score)
                if alfa >= beta : break    
            return score

    def get_next_action(self, state, max_levels):
        alfa = -math.inf
        beta = +math.inf
        actions = state.get_legal_actions(self.get_id())
        score = -math.inf
        definitive_action = actions[0]
        for succ in actions:
            maybe_new_score = self.minimaxAB(state.apply_action(self.get_id(),succ),1, 1, max_levels, alfa, beta)
            if maybe_new_score > score:
                score = maybe_new_score
                definitive_action = succ
            alfa = max(alfa, score)
            if alfa >= beta : break 
        return definitive_action


def probability(state, player):
    return len(state.get_legal_actions(player)) / 8

class ExpectAgent(StudentAgent):

    def expectimax(self,state, player, level, max_levels):
        actions = state.get_legal_actions(player)
        if len(actions) == 0:
            if (0 == player):
                return -10
            else:
                return 10
        if (level == max_levels):
            return len(state.get_legal_actions(0)) - len(state.get_legal_actions(1))
        
        if player == 0:
            score = -math.inf
            for succ in actions:
                maybe_new_score = self.expectimax(state.apply_action(player,succ),1, level+1, max_levels)
                if maybe_new_score > score:
                    score = maybe_new_score
            return score
        else:
            score = 0
            for succ in actions:
                prob = probability(state.apply_action(player,succ), player)
                score += prob * self.expectimax(state.apply_action(player,succ), 0, level+1,max_levels)
            return score

    def get_next_action(self, state, max_levels):
        actions = state.get_legal_actions(0)
        if len(actions) == 1:
            return actions[0]
        if (max_levels == 0):
            return actions[0]
        score = -math.inf
        definitive_action = actions[0]
        for succ in actions:
            maybe_new_score = self.expectimax(state.apply_action(0,succ),1, 1, max_levels)
            if maybe_new_score > score:
                score = maybe_new_score
                definitive_action = succ
        return definitive_action


class MaxNAgent(StudentAgent):

    def maxN1(self, state, player, level, max_levels, index, avaliable_agents):
        player = player % len(avaliable_agents)
        my_player = avaliable_agents[(player + index)%len(avaliable_agents)]
        actions = state.get_legal_actions(my_player)
        if len(actions) == 0:
            if player == 0:
                return -10
            else:
                return 10
        if (level == max_levels):
            psk = 0
            psk_number = 0
            for i in range(0,len(avaliable_agents)):
                if (avaliable_agents[i] != my_player):
                    psk = psk + len(state.get_legal_actions(i))
                    psk_number = psk_number + 1
            return len(state.get_legal_actions(my_player)) - psk/psk_number
        if player == 0:
            score = -math.inf
            for succ in actions:
                maybe_new_score = self.maxN(state.apply_action(my_player,succ),player + 1, 
                        level+1, max_levels, index, avaliable_agents)
                if maybe_new_score > score:
                    score = maybe_new_score
            return score
        else:
            score = +math.inf
            for succ in actions:
                score = min(score, self.maxN(state.apply_action(my_player,succ),player + 1, 
                        level+1, max_levels, index, avaliable_agents))  
            return score

    def maxN2(self, state, player, level, max_levels, index, avaliable_agents):
        player = player % len(avaliable_agents)
        my_player = avaliable_agents[(player + index)%len(avaliable_agents)]
        actions = state.get_legal_actions(my_player)
        if len(actions) == 0:
            if player == 0:
                return -len(avaliable_agents)*8
            elif level < max_levels:
                if (len(avaliable_agents) < 3):
                    return 16
                if (index > player):
                    index = index - 1
                new_avaliable_agents = []
                new_avaliable_agents = avaliable_agents.copy()
                new_avaliable_agents.remove(my_player)
                player = player % len(new_avaliable_agents)
                ret_val = self.maxN2(state, player, level+1, max_levels, index, new_avaliable_agents)
                return 8 + ret_val
        if (level == max_levels):
            evaluated_score = 0
            for i in range(0, len(avaliable_agents)):
                evaluated_score = evaluated_score + (len(actions) - len(state.get_legal_actions(avaliable_agents[i])))
            return evaluated_score
        if player == 0:
            score = -math.inf
            for succ in actions:
                maybe_new_score = self.maxN2(state.apply_action(my_player,succ),player + 1, 
                        level+1, max_levels, index, avaliable_agents)
                if maybe_new_score > score:
                    score = maybe_new_score
            return score
        else:
            score = +math.inf
            for succ in actions:
                score = min(score, self.maxN2(state.apply_action(my_player,succ),player + 1, 
                        level+1, max_levels, index, avaliable_agents))  
            return score

    def negamax(self, state, player, level, max_levels, avaliable_agents,offset):
        player = player % len(avaliable_agents)
        my_player = avaliable_agents[(player + offset) % len(avaliable_agents)]
        if len(state.get_legal_actions(my_player)) == 0:
            if my_player == self.get_id():
                return -10
            else:
                return 10
        if (level == max_levels):
            return len(state.get_legal_actions(my_player))
        
        score = -math.inf
        for succ in state.get_legal_actions(my_player):
            maybe_new_score = -self.negamax(state.apply_action(my_player,succ), player + 1,  level+1, max_levels, avaliable_agents,offset)
            if maybe_new_score > score:
                score = maybe_new_score
        return score

    def maxN(self, state, player, level, max_levels, avaliable_agents, offset):
        player = player % len(avaliable_agents)
        my_player = avaliable_agents[(player + offset) % len(avaliable_agents)]
        actions = state.get_legal_actions(my_player)
        if len(actions) == 0:
            if (len(avaliable_agents) == 2):
                my_scores = []
                for agent in state.agents:
                    if len(state.get_legal_actions(agent.get_id())) == 0:
                        my_scores.append(-10)
                    else:
                        my_scores.append(10)
                return my_scores
            elif level != max_levels:
                if (offset > player):
                    offset = offset - 1
                new_avaliable_agents = []
                new_avaliable_agents = avaliable_agents.copy()
                new_avaliable_agents.remove(my_player)
                player = player % len(new_avaliable_agents)
                return self.maxN(state, player, level+1, max_levels, new_avaliable_agents, offset)
        if (level == max_levels):
            my_scores = []
            for agent in state.agents:
                if len(state.get_legal_actions(agent.get_id())) == 0:
                    my_scores.append(-10)
                else:
                    my_scores.append(len(state.get_legal_actions(agent.get_id())))
            return my_scores
        my_score = []
        my_max_score = -math.inf
        maybe_new_score = []
        for succ in actions:
            maybe_new_score = self.maxN(state.apply_action(my_player,succ), player + 1,  
                                            level+1, max_levels, avaliable_agents,offset)
            if my_max_score < maybe_new_score[my_player]:
                my_max_score = maybe_new_score[my_player]
                my_score = maybe_new_score.copy()
        return my_score


    def get_next_action(self, state, max_levels):
        if (len(state.get_legal_actions(self.get_id())) == 1):
            return state.get_legal_actions(self.get_id())[0]
        if (max_levels == 0):
            return state.get_legal_actions(self.get_id())[0]
        avaliable_agents = []
        for agent in state.agents:
            if (agent.is_active()):
                avaliable_agents.append(agent.get_id())
        offset = 0
        for i in range(0,len(avaliable_agents)):
            if avaliable_agents[i] == self.get_id():
                offset = i
                break
        my_max_score = -math.inf
        maybe_new_score = []
        actions = state.get_legal_actions(self.get_id())
        for succ in actions:
            maybe_new_score = self.maxN(state.apply_action(self.get_id(),succ), 1,  
                                            1, max_levels, avaliable_agents,offset)
            if my_max_score < maybe_new_score[self.get_id()]:
                my_max_score = maybe_new_score[self.get_id()]
                definitive_action = succ
        return definitive_action
