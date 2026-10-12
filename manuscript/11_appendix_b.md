# Appendix B — Independent Sieve Verification

## B.1 Purpose

The scientific claims of this paper depend on an accurate
enumeration of prime gaps at positions up to 10^13. This
appendix documents an independent cross-check of the
enumeration at position 10^12 against a separate, widely-used
sieve implementation.

## B.2 Method

Prime enumeration in test_multiwindow_v1.exe was compared
against primesieve, version 12.16, an independently developed
library for prime generation. The comparison window was

  [10^12, 10^12 + 10^7),

chosen to be small enough to run quickly (~2 seconds for our
binary) and large enough to exercise the high-position
arithmetic pathways.

For each window, five quantities were compared:

  1. Total count of primes in the window (n_gaps).
  2. First prime in the window.
  3. Last opening prime in the window.
  4. Closing prime (the smallest prime greater than HI).
  5. Sum of gaps from first to closing.

Additionally, SHA-256 digests of the first 1000 and last 1000
primes were compared.

## B.3 Results

\needspace{6\baselineskip}

| Quantity          | primesieve 12.16     | test_multiwindow_v1 | Verdict |
|-------------------|----------------------|---------------------|---------|
| n_gaps            | 361,726              | 361,726             | MATCH   |
| first_prime       | 1,000,000,000,039    | 1,000,000,000,039   | MATCH   |
| last_open         | 1,000,009,999,981    | 1,000,009,999,981   | MATCH   |
| closing_prime     | 1,000,010,000,023    | 1,000,010,000,023   | MATCH   |
| sum_of_gaps       | 9,999,984            | 9,999,984           | MATCH   |
| sha256 first 1000 | a3cf8071...          | a3cf8071...         | MATCH   |
| sha256 last 1000  | 070bfb13...          | 070bfb13...         | MATCH   |

All quantities agree exactly. No discrepancy was observed.

## B.4 Notes on the verification script

The verification script (sieve_verify.py) invokes
primesieve.exe directly through Python's subprocess module,
rather than through the Python wrapper. The executable path is
platform-dependent and must be adjusted by the reader to run
the script on a different system. On the author's system the
path was of the form

    <drive>:\<user-directory>\primesieve-<version>\primesieve.exe

The script is otherwise platform-independent in logic.

## B.5 Technical caveat

The verification window is narrow: the standard deviation of log p is only about 3 × 10^-6
(the range is about 10^-5), and the OLS detrending within this window
is therefore statistically under-determined. The S(M) and
ρ_resid(M) values from this window are not used as data
points anywhere in the paper; the window serves solely for
sieve verification, which does not depend on detrending.

In the eight fixed-count windows used in Sections 4–6, the
raw variance of log p ranges from approximately 0.54 (window A)
to approximately 7.5 × 10^-9 (window P5). The OLS slope β in
the highest-position windows is correspondingly imprecise. A
dedicated numerical-stability check (Appendix C) confirms that
the reported S(M) and ρ_resid(M) are insensitive to this: an
independent implementation using a centered log variable
(u = log1p((p − p_mid)/p_mid)) reproduces both quantities
to six decimal places at every modulus and in the four narrow
windows tested (P3, P4, P5, C).

## B.6 Artifacts

Verification artifacts are recorded in paper3_data_inventory.txt:

  sieve_verify.py sha256=22a4261d...\
  sieve_verify_1e12.log sha256=1f5e18ac...\
  phase_decomp_1000000000000_1000010000000.csv sha256=785be809...

## B.7 Statement

We conclude that the enumeration agrees with primesieve 12.16
on the specified verification window near 10^12. No
discrepancy was observed in the compared quantities.
