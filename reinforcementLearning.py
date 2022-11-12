import random
from typing import List

class SampleEnvironment:
    def __init__(self):
        self.steps_left = 7

    def get_observation (self) -> List[float]:
        return [0.0, 0.0, 0.0]

    def get_actions(self) -> List[int]:
        return [0, 1]
    
    def is_done(self) -> bool:
        return self.steps_left == 0

    def action(self, action: int) -> float:
        if self.is_done():
            raise Exception("Game is over")
        self.steps_left -= 1 
        return random.random()


class Agent:
    def __init__(self):
        self.total_reward = 0.0

    def step(self, env: SampleEnvironment):
        current_obs = env.get_observation()
        print(f"Observations: {current_obs}")
        actions = env.get_actions()
        print (f"Actions: {actions}")
        reward = env.action(random.choice(actions))
        self.total_reward += reward
        print (f"Total rewards: {self.total_reward}")



env = SampleEnvironment()
agent = Agent()
i = 0

while not env.is_done():
    i += 1
    print(f"Step: {i}")
    agent.step(env)
    print()

print(f"Total rewards got: {agent.total_reward}")
