#include "../lab06/02.cpp"
#include "../genetic/classes.cpp"
#include <memory>

vector<Organism> initOrganism(vector<Organism> organisms, int genesNum = 128, int n = 1)
{
    for (int x = 0; x < n; x++)
    {
        Genotype genotype;

        //np. 1 genotyp = 32 chromosomy(16 par po 2 geny)
        //TODO: sensowne przydzielenie par chromosomów na podstawie wartości `genesNum`
        for (int i = 0; i < 16; i++)
        {
            vector<Gene> genes;
            for (int j = 0; j < 8; j++)
            {
                Gene gene;
                gene.initGene();
                genes.push_back(gene);
            }
            Chromosome chromosome(genes);
            // chromosome.grayCode();
            genotype.chromosomes.push_back(chromosome);
        }
        genotype.calculateX();
        genotype.calculateY();
        Organism organism(genotype);
        organisms.push_back(organism);
    }
    return organisms;
};

vector<Organism> fitness(vector<Organism> organisms, FunctionToOptI *goal)
{
    for (int i = 0; i < organisms.size(); i++)
    {
        organisms.at(i).genotype.calculateX();
        organisms.at(i).genotype.calculateY();
        // cout << "goal " << goal->calculate(organisms.at(i).genotype.x,organisms.at(i).genotype.y) << endl;
        organisms.at(i).fitness = 1 / (1 + abs(goal->calculate(organisms.at(i).genotype.x, organisms.at(i).genotype.y)));
    }
    return organisms;
}

void showPopulationFitness(Population population)
{
    cout << "\nOrganisms fitness: \n[";
    for (int i = 0; i < population.organisms.size(); i++)
    {
        cout << "  {" << population.organisms.at(i).fitness << "}";
        if (i % 4 == 0 && i != 0)
            cout << '\n';
    }
    cout << " ]\n";
}

void showPopulation(Population population)
{
    for (int i = 0; i < population.organisms.size(); i++)
    {
        cout << "Organism [" << i + 1 << "]\n------\n";
        for (int j = 0; j < 1; j++)
        {
            cout << "Genotype \n-------\n";
            for (int k = 0; k < population.organisms.at(i).genotype.chromosomes.size(); k++)
            {
                cout << "\tGenes of Chromosome [" << k + 1 << "]\n";
                cout << "\t";
                for (int l = 0; l < population.organisms.at(i).genotype.chromosomes.at(k).genes.size(); l++)
                {
                    cout << population.organisms.at(i).genotype.chromosomes.at(k).genes.at(l).value << " ";
                }
                cout << "\n";
            }
        }
    }
}

Population crossover(Population population, double p_crossover)
{
    Population ret_pop;
    uniform_real_distribution<double> r_pcross(0.0, 1.0);
    for (int i = 0; i < (population.organisms.size() - 1); i += 2)
    {
        Organism a = population.organisms.at(i);
        Organism b = population.organisms.at(i + 1);

        if (r_pcross(rdev) < p_crossover)
        {
            uniform_int_distribution<int>(0, a.genotype.chromosomes.size() - 1);
            auto crossover_p = dist(rdev);
            for (int g = crossover_p; g < a.genotype.chromosomes.size(); g++)
            {
                try
                {
                    swap(a.genotype.chromosomes.at(g).genes, b.genotype.chromosomes.at(g).genes);
                }
                catch (exception e)
                {
                    cout << e.what();
                }
            }
        }
        ret_pop.organisms.push_back(a);
        ret_pop.organisms.push_back(b);
    }
    return ret_pop;
};

Population get_crossover_one_point(Population pop, double p_crossover = 0.2)
{
    Population crossover_one_point = crossover(pop, p_crossover);
    return crossover_one_point;
};

Population mutation_uniform(Population population, double p_mutation)
{
    Population ret_pop;
    uniform_real_distribution<double> r_mut(0.0, 1.0);
    for (int i = 0; i < population.organisms.size(); i++)
    {
        Organism a = population.organisms.at(i);
        for (int g = 0; g < a.genotype.chromosomes.size(); g++)
        {
            if(r_mut(rdev) < p_mutation){
                vector<Gene> genes = a.genotype.chromosomes.at(g).genes;
                if(a.genotype.chromosomes.at(g).genes.at(genes.size()/2).value == '1'){
                    a.genotype.chromosomes.at(g).genes.at(genes.size()/2).value = '0';
                }else {
                    a.genotype.chromosomes.at(g).genes.at(genes.size()/2).value = '1';
                }
            }
        }
        ret_pop.organisms.push_back(a);
    }
    return ret_pop;
};

Population get_mutation_uniform(Population pop, double p_mutation = 0.1)
{
    Population mutationPop = mutation_uniform(pop, p_mutation);
    return mutationPop;
};

Population selection_roulette(Population population)
{
    Population selected_population;
    double sum_fitness = accumulate(population.organisms.begin(), population.organisms.end(), 0.0, [](auto a, auto b) {
        return a + b.fitness;
    });
    cout << "sum fit: " << sum_fitness << endl;

    uniform_real_distribution<double> dist(0.0, sum_fitness);
    for (int x = 0; x < population.organisms.size(); x++)
    {
        double randomVal = dist(rdev);
        double s = 0.0;
        Organism selected = population.organisms.at(0);
        for (unsigned int i = 0; i < population.organisms.size(); i++)
        {
            s += population.organisms.at(i).fitness;
            if (randomVal < s)
            {
                selected_population.organisms.push_back(population.organisms.at(i));
                break;
            }
        }
    }
    return selected_population;
};

int main()
{
    Population population;
    // shared_ptr<Levi> goal(new Levi());

    FunctionToOptI *goal = new Levi();
    population.organisms = initOrganism(population.organisms, 128, 20);
      population.organisms = fitness(population.organisms, goal);
   
    ofstream fileTxt;
    fileTxt.open("./population.txt");
    for (int i = 0; i < 5; i++)
    {
        showPopulationFitness(population);
        population = selection_roulette(population);
        population = get_crossover_one_point(population);
        population = get_mutation_uniform(population);
        population.organisms = fitness(population.organisms, goal);
        for(int j = 0; j < population.organisms.size(); j++){
            fileTxt << i << " "  << j << " " << population.organisms.at(j).fitness << endl;
        }
        
    }

    // showPopulation(population);
}