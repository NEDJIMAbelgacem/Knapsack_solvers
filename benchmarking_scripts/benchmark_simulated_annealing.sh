# run from project's directory
cd datasets/
mkdir ../benchmark_results&
rm "../benchmark_results/benchmark_simulated_annealing.txt"&
for f in ./*
do
    "../build/bin/benchmark_simulated_annealing" 100 0 $f >> "../benchmark_results/benchmark_simulated_annealing.txt"
done
cd ..