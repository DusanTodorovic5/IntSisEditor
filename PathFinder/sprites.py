import pygame
import os
import config


class BaseSprite(pygame.sprite.Sprite):
    images = dict()

    def __init__(self, row, col, file_name, transparent_color=None):
        pygame.sprite.Sprite.__init__(self)
        if file_name in BaseSprite.images:
            self.image = BaseSprite.images[file_name]
        else:
            self.image = pygame.image.load(os.path.join(config.IMG_FOLDER, file_name)).convert()
            self.image = pygame.transform.scale(self.image, (config.TILE_SIZE, config.TILE_SIZE))
            BaseSprite.images[file_name] = self.image
        # making the image transparent (if needed)
        if transparent_color:
            self.image.set_colorkey(transparent_color)
        self.rect = self.image.get_rect()
        self.rect.topleft = (col * config.TILE_SIZE, row * config.TILE_SIZE)
        self.row = row
        self.col = col


class Agent(BaseSprite):
    def __init__(self, row, col, file_name):
        super(Agent, self).__init__(row, col, file_name, config.DARK_GREEN)

    def move_towards(self, row, col):
        row = row - self.row
        col = col - self.col
        self.rect.x += col
        self.rect.y += row

    def place_to(self, row, col):
        self.row = row
        self.col = col
        self.rect.x = col * config.TILE_SIZE
        self.rect.y = row * config.TILE_SIZE

    # game_map - list of lists of elements of type Tile
    # goal - (row, col)
    # return value - list of elements of type Tile
    def get_agent_path(self, game_map, goal):
        pass


class ExampleAgent(Agent):
    def __init__(self, row, col, file_name):
        super().__init__(row, col, file_name)

    def get_agent_path(self, game_map, goal):
        path = [game_map[self.row][self.col]]
        row = self.row
        col = self.col
        while True:
            if row != goal[0]:
                row = row + 1 if row < goal[0] else row - 1
            elif col != goal[1]:
                col = col + 1 if col < goal[1] else col - 1
            else:
                break
            path.append(game_map[row][col])
        return path


class Tile(BaseSprite):
    def __init__(self, row, col, file_name):
        super(Tile, self).__init__(row, col, file_name)

    def position(self):
        return self.row, self.col

    def cost(self):
        pass

    def kind(self):
        pass

    def __lt__(self, other):
         return self.cost() < other.cost()


class Stone(Tile):
    def __init__(self, row, col):
        super().__init__(row, col, 'stone.png')

    def cost(self):
        return 1000

    def kind(self):
        return 's'


class Water(Tile):
    def __init__(self, row, col):
        super().__init__(row, col, 'water.png')

    def cost(self):
        return 500

    def kind(self):
        return 'w'


class Road(Tile):
    def __init__(self, row, col):
        super().__init__(row, col, 'road.png')

    def cost(self):
        return 2

    def kind(self):
        return 'r'


class Grass(Tile):
    def __init__(self, row, col):
        super().__init__(row, col, 'grass.png')

    def cost(self):
        return 3

    def kind(self):
        return 'g'


class Mud(Tile):
    def __init__(self, row, col):
        super().__init__(row, col, 'mud.png')

    def cost(self):
        return 5

    def kind(self):
        return 'm'


class Dune(Tile):
    def __init__(self, row, col):
        super().__init__(row, col, 'dune.png')

    def cost(self):
        return 7

    def kind(self):
        return 's'


class Goal(BaseSprite):
    def __init__(self, row, col):
        super().__init__(row, col, 'x.png', config.DARK_GREEN)


class Trail(BaseSprite):
    def __init__(self, row, col, num):
        super().__init__(row, col, 'trail.png', config.DARK_GREEN)
        self.num = num

    def draw(self, screen):
        text = config.GAME_FONT.render(f'{self.num}', True, config.WHITE)
        text_rect = text.get_rect(center=self.rect.center)
        screen.blit(text, text_rect)

class SearchTree:
    def __init__(self, x, y, tile, parent=None, cost=0, depth=0):
        self.x = x
        self.y = y
        self.tile = tile
        self.left = None
        self.right = None
        self.up = None
        self.down = None
        self.parent = parent
        self.cost = cost
        self.depth = depth

    def getPathFromRoot(self):
        path = []
        node = self
        path.append(node.tile)
        while (node.parent != None):
            node = node.parent
            path.append(node.tile)
            
        return path[::-1]

    def __lt__(self, other):
         return self.tile.cost() < other.tile.cost()

class Aki(Agent):
    def __init__(self, row, col, file_name):
        super().__init__(row, col, file_name)
    
    def get_agent_path(self, game_map, goal):
        path = [game_map[self.row][self.col]]
        row = self.row
        col = self.col
        visited = set()
        queue = []
        bt =  SearchTree(row, col, game_map[row][col])
        i = 0
        while True:
            if (row,col) in visited:
                bt = queue.pop(0)
                row = bt.x
                col = bt.y
                continue
            visited.add((row,col))
            if (row == goal[0] and col == goal[1]):
                return bt.getPathFromRoot()
            unsortedCost = []
            if ((col > 0) and (row,col - 1) not in visited):
                bt.left = SearchTree(row, col - 1, game_map[row][col - 1], bt)
                unsortedCost.append(bt.left)

            if ((row < len(game_map) - 1) and ((row + 1,col) not in visited)):
                bt.down = SearchTree(row + 1, col, game_map[row + 1][col],bt)
                unsortedCost.append(bt.down)

            if ((col < len(game_map[row]) - 1) and ((row,col + 1) not in visited)):
                bt.right = SearchTree(row, col + 1, game_map[row][col + 1],bt)
                unsortedCost.append(bt.right)

            if ((row > 0) and ((row - 1, col) not in visited)):
                bt.up = SearchTree(row - 1, col, game_map[row - 1][col],bt)
                unsortedCost.append(bt.up)

            if (len(unsortedCost) == 0):
                if (bt.parent == None):
                    break
                bt = bt.parent
                row = bt.x
                col = bt.y
            else:
                for tile in sorted(unsortedCost, reverse=True):
                    queue.append(tile)
                bt = queue.pop()
                row = bt.x
                col = bt.y
        return bt.getPathFromRoot()

class Jocke(Agent):
    def __init__(self, row, col, file_name):
        super().__init__(row, col, file_name)

    def get_agent_path(self, game_map, goal):
        path = [game_map[self.row][self.col]]
        row = self.row
        col = self.col
        visited = set()
        queue = []
        bt =  SearchTree(row, col, game_map[row][col])
        while True:
            if (row,col) in visited:
                bt = queue.pop(0)
                row = bt.x
                col = bt.y
                continue
            visited.add((row,col))

            if (row == goal[0] and col == goal[1]):
                return bt.getPathFromRoot()
            
            unsortedCost = []

            if ((row > 0) and (row-1,col) not in visited):#(game_map[row - 1][col] not in visited)):
                bt.up = SearchTree(row - 1, col, game_map[row - 1][col],bt)
                avg_price = 0
                count = 0
                if (col > 0):
                    avg_price += game_map[row- 1][col - 1].cost()
                    count += 1
                if (row - 1 > 0):
                    avg_price += game_map[row - 2][col].cost()
                    count += 1
                if (col < len(game_map[row - 1]) - 1):
                    avg_price += game_map[row - 1][col + 1].cost()
                    count += 1
                if (count == 0):
                    avg_price = 0
                    count = 1
                unsortedCost.append([bt.up, avg_price/count])
                
            if ((col < len(game_map[row]) - 1) and (row,col+1) not in visited):#and (game_map[row][col + 1] not in visited)):
                bt.right = SearchTree(row, col + 1, game_map[row][col + 1],bt)
                avg_price = 0
                count = 0
                if (row > 0):
                    avg_price += game_map[row - 1][col + 1].cost()
                    count += 1
                if (row < len(game_map) - 1):
                    avg_price += game_map[row + 1][col + 1].cost()
                    count += 1
                if (col < len(game_map[row]) - 2):
                    avg_price += game_map[row][col + 2].cost()
                    count += 1
                if (count == 0):
                    avg_price = 0
                    count = 1
                unsortedCost.append([bt.right, avg_price/count])

            if ((row < len(game_map) - 1) and (row+1,col) not in visited):#and (game_map[row + 1][col] not in visited)):
                bt.down = SearchTree(row + 1, col, game_map[row + 1][col],bt)
                avg_price = 0
                count = 0
                if (col > 0):
                    avg_price += game_map[row + 1][col - 1].cost()
                    count += 1
                if (row < len(game_map) - 2):
                    avg_price += game_map[row + 2][col].cost()
                    count += 1
                if (col < len(game_map[row + 1]) - 1):
                    avg_price += game_map[row + 1][col + 1].cost()
                    count += 1
                if (count == 0):
                    avg_price = 0
                    count = 1
                unsortedCost.append([bt.down, avg_price/count])

            if ((col > 0) and (row,col-1) not in visited):#and (game_map[row][col - 1] not in visited)):
                bt.left = SearchTree(row, col - 1, game_map[row][col - 1], bt)
                avg_price = 0
                count = 0
                if (col - 1 > 0):
                    avg_price += game_map[row][col - 2].cost()
                    count += 1
                if (row > 0):
                    avg_price += game_map[row - 1][col - 1].cost()
                    count += 1
                if (row < len(game_map) - 2):
                    avg_price += game_map[row + 1][col - 1].cost()
                    count += 1
                if (count == 0):
                    avg_price = 0
                    count = 1
                unsortedCost.append([bt.left,avg_price/count])

            if (len(unsortedCost) == 0):
                if (bt.parent == None):
                    break
                if (len(queue) == 0):
                    break
                bt = queue.pop(0)
                row = bt.x
                col = bt.y
            else:
                unsortedCost.sort(key=lambda x: x[1])
                for tile in unsortedCost:
                    queue.append(tile[0])
                bt = queue.pop(0)
                row = bt.x
                col = bt.y
        return bt.getPathFromRoot()


class Draza(Agent):
    def __init__(self, row, col, file_name):
        super().__init__(row, col, file_name)

    def get_agent_path(self, game_map, goal):
        path = [game_map[self.row][self.col]]
        row = self.row
        col = self.col
        visited = set()
        queue = []
        bt =  SearchTree(row, col, game_map[row][col])
        while True:
            if (row, col) in visited:
                bt = queue.pop(0)
                row = bt.x
                col = bt.y
                continue
            visited.add((row, col))
            if (row == goal[0] and col == goal[1]):
                return bt.getPathFromRoot()

            if ((col > 0) and ((row, col - 1) not in visited)):
                bt.left = SearchTree(row, col - 1, game_map[row][col - 1], bt,bt.cost + game_map[row][col - 1].cost(), bt.depth + 1)
                queue.append(bt.left)

            if ((row < len(game_map) - 1) and ((row + 1,col) not in visited)):
                bt.down = SearchTree(row + 1, col, game_map[row + 1][col],bt, bt.cost + game_map[row + 1][col].cost(), bt.depth + 1)
                queue.append(bt.down)

            if ((col < len(game_map[row]) - 1) and ((row, col + 1) not in visited)):
                bt.right = SearchTree(row, col + 1, game_map[row][col + 1],bt,bt.cost + game_map[row][col + 1].cost(), bt.depth + 1)
                queue.append(bt.right)

            if ((row > 0) and ((row - 1,col) not in visited)):
                bt.up = SearchTree(row - 1, col, game_map[row - 1][col], bt, bt.cost + game_map[row - 1][col].cost(), bt.depth + 1)
                queue.append(bt.up)

            queue.sort(key=lambda x : (x.cost, x.depth), reverse=True)
            bt = queue.pop()
            row = bt.x
            col = bt.y
        return bt.getPathFromRoot()

class Bole(Agent):
    def __init__(self, row, col, file_name):
        super().__init__(row, col, file_name)

    def get_agent_path(self, game_map, goal):
        path = [game_map[self.row][self.col]]
        row = self.row
        col = self.col
        visited = set()
        queue = []
        bt =  SearchTree(row, col, game_map[row][col])
        while True:
            if (row, col) in visited:
                bt = queue.pop(0)
                row = bt.x
                col = bt.y
                continue
            visited.add((row,col))
            if (row == goal[0] and col == goal[1]):
                return bt.getPathFromRoot()

            if ((col > 0) and ((row,col - 1) not in visited)):
                newCost = bt.cost + game_map[row][col - 1].cost() + calc_heuristic((row, col -1),goal)  - calc_heuristic((row, col),goal)
                bt.left = SearchTree(row, col - 1, game_map[row][col - 1],bt , newCost, bt.depth + 1)
                queue.append(bt.left)

            if ((row < len(game_map) - 1) and ((row + 1,col) not in visited)):
                newCost = bt.cost + game_map[row + 1][col].cost() + calc_heuristic((row + 1, col),goal)  - calc_heuristic((row, col),goal)
                bt.down = SearchTree(row + 1, col, game_map[row + 1][col],bt, newCost, bt.depth + 1)
                queue.append(bt.down)

            if ((col < len(game_map[row]) - 1) and ((row, col + 1) not in visited)):
                newCost = bt.cost + game_map[row][col + 1].cost() + calc_heuristic((row, col + 1),goal)  - calc_heuristic((row, col),goal)
                bt.right = SearchTree(row, col + 1, game_map[row][col + 1],bt,newCost, bt.depth + 1)
                queue.append(bt.right)

            if ((row > 0) and ((row - 1, col) not in visited)):
                newCost = bt.cost + game_map[row - 1][col].cost() + calc_heuristic((row - 1, col),goal) - calc_heuristic((row, col),goal)
                bt.up = SearchTree(row - 1, col, game_map[row - 1][col], bt, newCost, bt.depth + 1)
                queue.append(bt.up)
                
            queue.sort(key=lambda x : (x.cost, x.depth), reverse=True)
            bt = queue.pop()
            row = bt.x
            col = bt.y
        return bt.getPathFromRoot()
    
def calc_heuristic(start, finish):
    return ((start[0] - finish[0])**2 + (start[1] - finish[1])**2)**(1/2)