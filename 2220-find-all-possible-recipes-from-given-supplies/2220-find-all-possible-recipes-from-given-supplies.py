class Solution:
    def findAllRecipes (self, recipes : List [str], ingredients : List [List [str]], supplies : List [str]) -> List [str]:
        adj = defaultdict (list)
        in_degree = {recipe : 0 for recipe in recipes}
        for i, recipe in enumerate (recipes):
            for ingredient in ingredients [i]:
                adj [ingredient].append (recipe)
            in_degree [recipe] = len (ingredients [i])
        result = []
        queue = deque (supplies)
        while queue:
            curr = queue.popleft ()
            for recipe in adj [curr]:
                in_degree [recipe] -= 1
                if in_degree [recipe] == 0:
                    result.append (recipe)
                    queue.append (recipe)
        return result