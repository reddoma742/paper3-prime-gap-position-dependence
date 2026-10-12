import subprocess
import hashlib

LO = 10**12
HI = 10**12 + 10**7

print(f"Window: [{LO}, {HI})")

# Run primesieve to generate primes in the window
result = subprocess.run([r"C:\Users\pc\Documents\Projet par défaut\primesieve-12.16\primesieve.exe", str(LO), str(HI - 1), "-p"], capture_output=True, text=True)
if result.returncode != 0:
    print(f"Error: {result.stderr}")
    exit(1)

primes_str = result.stdout.strip()
primes_in = [int(x) for x in primes_str.split()]

# Get the next prime after the window
result = subprocess.run([r"C:\Users\pc\Documents\Projet par défaut\primesieve-12.16\primesieve.exe", str(HI), str(HI + 1000), "-p"], capture_output=True, text=True)
if result.returncode != 0:
    print(f"Error getting next prime: {result.stderr}")
    exit(1)
next_prime_lines = result.stdout.strip().split('\n')
next_prime_val = int(next_prime_lines[0]) if next_prime_lines else HI

n_gaps = len(primes_in)
first_prime = primes_in[0]
last_open = primes_in[-1]
closing = next_prime_val

print(f"n_gaps           = {n_gaps}")
print(f"first_prime      = {first_prime}")
print(f"last_open        = {last_open}")
print(f"closing_prime    = {closing}")
print(f"sum_of_gaps      = {closing - first_prime}")

h = hashlib.sha256()
for p in primes_in[:1000]:
    h.update(str(p).encode() + b"\n")
print(f"sha256_first1000 = {h.hexdigest()}")

h2 = hashlib.sha256()
for p in primes_in[-1000:]:
    h2.update(str(p).encode() + b"\n")
print(f"sha256_last1000  = {h2.hexdigest()}")