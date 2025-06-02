#include "geneticcontrollergenerator.h"
#include <QFile>
#include <QTextStream>

QString GeneticControllerGenerator::generateGeneticAlgorithmScript(
    int populationSize,
    double crossoverProbability,
    double mutationRate,
    int maxGenerations,
    int earlyStopGen)
{
    QString script = QString(
R"(import random
import copy
from typing import List, Optional # для "типизации" функций

POPULATION_SIZE = %1
P_CROSSOVER = %2
MUTATION_RATE = %3
MAX_GENERATIONS = %4
EARLY_STOP_GEN = %5

class Individual:
    def __init__(self, path: List[int], matrix: list):
        self.path = path
        self.weights = self.calculate_weights(matrix)
        self.fitness = sum(self.weights) if self.weights else float('inf')

    def calculate_weights(self, matrix: list) -> List[int]:
        if len(self.path) < 2:
            return []

        weights = []
        for i in range(1, len(self.path)):
            weight = matrix[self.path[i - 1]][self.path[i]]
            if weight == 0:
                return []
            weights.append(weight)
        return weights

    def is_valid(self) -> bool:
        return len(self.weights) == len(self.path) - 1

    def __lt__(self, other):
        return self.fitness < other.fitness


def generate_individual(matrix: list, start: int, end: int) -> Optional[Individual]:
    path = [start]
    current = start
    visited = {start}
    backtrack_count = 0
    max_backtrack = len(matrix) * 2

    while current != end and backtrack_count < max_backtrack:
        neighbors = [
            n for n, w in enumerate(matrix[current])
            if w != 0 and n != current and n not in visited
        ]

        if not neighbors:
            if len(path) <= 1:
                return None
            visited.remove(path.pop())
            current = path[-1]
            backtrack_count += 1
            continue

        next_node = random.choice(neighbors)
        path.append(next_node)
        visited.add(next_node)
        current = next_node

    if current != end or len(path) < 2:
        return None

    individual = Individual(path, matrix)
    return individual if individual.is_valid() else None


def initialize_population(size: int, matrix: list, start: int, end: int) -> List[Individual]:
    population = []
    attempts = 0
    max_attempts = size * 10

    while len(population) < size and attempts < max_attempts:
        ind = generate_individual(matrix, start, end)
        if ind:
            population.append(ind)
        attempts += 1

    return population


def tournament_selection(population: List[Individual], size: int) -> List[Individual]:
    selected = []
    for _ in range(size):
        contestants = random.sample(population, min(3, len(population)))
        winner = min(contestants)
        selected.append(copy.deepcopy(winner))
    return selected


def ordered_crossover(parent1: Individual, parent2: Individual, matrix: list) -> List[Individual]:
    path1, path2 = parent1.path, parent2.path
    if len(path1) < 3 or len(path2) < 3:
        return [parent1, parent2]

    common = set(path1[1:-1]) & set(path2[1:-1])
    if not common:
        return [parent1, parent2]

    chosen_node = random.choice(list(common))
    slice1 = path1.index(chosen_node)
    slice2 = path2.index(chosen_node)

    def create_child(p1, p2, s1, s2):
        child_path = p1[:s1] + p2[s2:]
        child_path = list(dict.fromkeys(child_path))
        child = Individual(child_path, matrix)
        return child if child.is_valid() else None

    child1 = create_child(path1, path2, slice1, slice2)
    child2 = create_child(path2, path1, slice2, slice1)

    return [
        child1 if child1 else copy.deepcopy(parent1),
        child2 if child2 else copy.deepcopy(parent2)
    ]


def mutate(individual: Individual, matrix: list) -> Individual:
    path = individual.path.copy()
    if len(path) < 3:
        return individual

    idx = random.randint(1, len(path) - 2)

    valid_nodes = [
        n for n in range(len(matrix))
        if matrix[path[idx - 1]][n] != 0 and
           matrix[n][path[idx + 1]] != 0 and
           n not in path[:idx]
    ]

    if valid_nodes:
        path[idx] = random.choice(valid_nodes)
        mutated = Individual(path, matrix)
        return mutated if mutated.is_valid() else individual

    return individual


def genetic_algorithm(graph: list, start: int, end: int):
    population = initialize_population(POPULATION_SIZE, graph, start, end)
    if not population:
        print("Не удалось создать начальную популяцию!")
        return

    best_individual = min(population)
    no_improvement = 0
    history = []

    for generation in range(MAX_GENERATIONS):
        selected = tournament_selection(population, len(population))

        offspring = []
        for i in range(0, len(selected) - 1, 2):
            if random.random() < P_CROSSOVER:
                child1, child2 = ordered_crossover(selected[i], selected[i + 1], graph)
            else:
                child1, child2 = copy.deepcopy(selected[i]), copy.deepcopy(selected[i + 1])
            offspring.extend([child1, child2])

        for i in range(len(offspring)):
            if random.random() < MUTATION_RATE:
                offspring[i] = mutate(offspring[i], graph)

        population = sorted(population + offspring, key=lambda x: x.fitness)[:POPULATION_SIZE]

        current_best = min(population)
        if current_best.fitness < best_individual.fitness:
            best_individual = copy.deepcopy(current_best)
            no_improvement = 0
        else:
            no_improvement += 1

        history.append((generation + 1, best_individual.fitness, best_individual.path))

        if no_improvement >= EARLY_STOP_GEN:
            break

    print("\nЛучший найденный путь:")
    print(f"Путь: {best_individual.path}")
    print(f"Вес: {best_individual.fitness}")
    return best_individual.path
)").arg(populationSize)
   .arg(crossoverProbability, 0, 'f')
   .arg(mutationRate, 0, 'f')
   .arg(maxGenerations)
   .arg(earlyStopGen);

    return script;
}

bool GeneticControllerGenerator::saveScript(const QString& script, const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    out << script;
    file.close();

    return true;
}
