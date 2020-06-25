# run from project's directory
cd datasets/
mkdir ../benchmark_results&
cd /home/nedjima/Desktop/Knapsack_solvers/datasets/
rm "../benchmark_results/benchmark_genetic.txt"&
for f in ./*
do
    "../build/bin/benchmark_genetic_algorithm" 70 100 0 $f >> "../benchmark_results/benchmark_genetic.txt"
    "../build/bin/benchmark_genetic_algorithm" 70 200 0 $f >> "../benchmark_results/benchmark_genetic.txt"
    "../build/bin/benchmark_genetic_algorithm" 70 300 0 $f >> "../benchmark_results/benchmark_genetic.txt"
done
cd ..