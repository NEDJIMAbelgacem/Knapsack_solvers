# run from project's directory
cd datasets/
mkdir ../benchmark_results&
rm "../benchmark_results/benchmark_exact_methods.txt"&
## same number of items :
"../build/bin/benchmark_dynamic_programming" 0 15 100 15 200 15 500 15 800 >> "../benchmark_results/benchmark_exact_methods.txt"
"../build/bin/benchmark_branch_and_bound"    0 15 100 15 200 15 500 15 800 >> "../benchmark_results/benchmark_exact_methods.txt"

## same values
"../build/bin/benchmark_dynamic_programming" 0 5 300 10 300 20 300 >> "../benchmark_results/benchmark_exact_methods.txt"
"../build/bin/benchmark_branch_and_bound" 0 5 300 15 300 20 300 >> "../benchmark_results/benchmark_exact_methods.txt"

cd ..