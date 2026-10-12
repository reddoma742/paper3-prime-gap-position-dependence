# 5. Empirical Position Dependence

## 5.1 Scope

This section quantifies the position dependence established in Section 4. Three questions are addressed: how much S(M, L) and ρ_resid(M, L) decrease across the observed range; whether the rate of decrease depends on M; and whether any simple rescaling renders the dependence universal across moduli. All quantities are computed from the eight fixed-count windows of Table 4.1. No new runs are used.

## 5.2 Total Decrease of S(M, L)

**Table 5.1 — Total relative decrease of S from A (L = 19.96) to P5 (L = 29.93).**

| M | S(A) | S(P5) | ΔS | Relative decrease |
|---|-------|-------|----|--------------------|
| 6 | 0.018154 | 0.011521 | 0.006633 | 36.5% |
| 30 | 0.148372 | 0.092723 | 0.055649 | 37.5% |
| 210 | 0.304672 | 0.226046 | 0.078626 | 25.8% |
| 2310 | 0.418677 | 0.334435 | 0.084242 | 20.1% |
| 30030 | 0.509198 | 0.423067 | 0.086131 | 16.9% |
| 510510 | 0.576448 | 0.494000 | 0.082448 | 14.3% |

Two observations follow. The absolute decrease grows across the lower part of the modulus ladder and flattens at the largest tested moduli. The relative decrease provides the more comparable scale-free summary. The relative decrease is not strictly monotone in M: it is 36.5% at M = 6 and 37.5% at M = 30, then falls monotonically to 14.3% at M = 510510. The rate of decrease is not uniform across the modulus ladder.

## 5.3 Total Decrease of ρ_resid(M, L)

**Table 5.2 — Total relative decrease of |ρ_resid| from A to P5.**

| M | ρ(A) | ρ(P5) | \|ρ(P5)/ρ(A)\| | Relative decrease |
|---|------|-------|------------------|--------------------|
| 6 | −0.029194 | −0.018701 | 0.6406 | 35.9% |
| 30 | −0.025414 | −0.017189 | 0.6764 | 32.4% |
| 210 | −0.020913 | −0.014718 | 0.7037 | 29.6% |
| 2310 | −0.017636 | −0.012711 | 0.7207 | 27.9% |
| 30030 | −0.015026 | −0.011071 | 0.7367 | 26.3% |
| 510510 | −0.013090 | −0.009762 | 0.7457 | 25.4% |

The pattern matches that of S: larger relative decrease at small M, smaller at large M. The contrast is weaker than for S (35.9% versus 25.4%, a ratio of 1.4, compared with 2.6 for S), but the direction is the same.

Both S and ρ_resid therefore share the same qualitative behaviour: they weaken with L, and they weaken faster at small M.

## 5.4 Descriptive Power-Law Fits

For each M we fit S(M, L) = a · L^(−α) and |ρ_resid(M, L)| = a · L^(−α) to the eight fixed-count points by least squares. The fitted exponents are reported below as descriptive summaries over the observed range, not as claimed asymptotic laws. Section 6 shows that the power-law form is not preferred over alternative two-parameter forms within the range L ∈ [19.96, 29.93].

**Table 5.3 — Descriptive power-law fits S(M, L) = a · L^(−α).**

| M | a | α | R² |
|---|---|---|-----|
| 6 | 0.6143 | 1.170 | 0.994 |
| 30 | 5.110 | 1.177 | 0.995 |
| 210 | 2.932 | 0.753 | 0.997 |
| 2310 | 2.275 | 0.564 | 0.998 |
| 30030 | 2.016 | 0.458 | 0.999 |
| 510510 | 1.831 | 0.385 | 0.999 |

\needspace{12\baselineskip}

**Table 5.4 — Descriptive power-law fits |ρ_resid(M, L)| = a · L^(−α).**

| M | a | α | R² |
|---|---|---|-----|
| 6 | 0.8412 | 1.117 | 0.989 |
| 30 | 0.4869 | 0.980 | 0.995 |
| 210 | 0.2973 | 0.881 | 0.998 |
| 2310 | 0.2114 | 0.824 | 0.999 |
| 30030 | 0.1556 | 0.775 | 0.999 |
| 510510 | 0.1231 | 0.742 | 0.999 |

The α_S ladder is approximately decreasing in M, with a small non-monotonicity at M = 6 and M = 30 (α_S = 1.170 and 1.177 respectively); it declines smoothly thereafter, from 1.170 at M = 6 to 0.385 at M = 510510. The α_ρ ladder declines monotonically from 1.117 to 0.742 over the same range. The two ladders cross between M = 30 and M = 210.

The crossing is an empirical feature of the selected fit and is not assigned a mechanism. No claim is made that the crossing corresponds to any structural property of the modulus ladder.

## 5.5 Normalised Ratios

To test whether the position dependence is universal across moduli, we normalise each S-curve to its value at the reference window A:

R(M, L) ≡ S(M, L) / S(M, A).

\needspace{10\baselineskip}

**Table 5.5 — Normalised ratios R(M, L).**

| Window | L | R(6) | R(30) | R(210) | R(2310) | R(30030) | R(510510) |
|--------|---|------|-------|--------|---------|----------|-----------|
| A | 19.96 | 1.000 | 1.000 | 1.000 | 1.000 | 1.000 | 1.000 |
| P1 | 21.30 | 0.958 | 0.958 | 0.973 | 0.979 | 0.982 | 0.985 |
| B | 23.13 | 0.865 | 0.860 | 0.905 | 0.925 | 0.938 | 0.948 |
| P2 | 23.13 | 0.864 | 0.859 | 0.905 | 0.925 | 0.938 | 0.947 |
| P3 | 25.34 | 0.773 | 0.768 | 0.839 | 0.876 | 0.896 | 0.912 |
| C | 27.63 | 0.688 | 0.692 | 0.791 | 0.839 | 0.868 | 0.887 |
| P4 | 27.63 | 0.688 | 0.692 | 0.791 | 0.839 | 0.868 | 0.887 |
| P5 | 29.93 | 0.635 | 0.625 | 0.742 | 0.799 | 0.831 | 0.857 |

No exact collapse is observed. At the smallest displacement (P1, ΔL ≈ 1.33), the six M-curves nearly coincide (R between 0.958 and 0.985). As L increases, the curves separate: at P5, R ranges from 0.625 (M = 30) to 0.857 (M = 510510), a spread of about 1.37 across the modulus ladder.

The position dependence is therefore not described by a single universal shape. At the smallest tested displacement, the normalized values are numerically close across the tested moduli. With only one such displacement, this observation is not interpreted as local universality.

## 5.6 Summary of Section 5

The following are empirical observations over the fixed-count set, independent of any specific functional form:

- **F1.** For every M, S(M, L) decreases monotonically with L across the eight windows.
- **F2.** For every M, |ρ_resid(M, L)| decreases monotonically with L.
- **F3.** The total relative decrease from A to P5 depends on M: 36.5% at M = 6 versus 14.3% at M = 510510 for S; 35.9% versus 25.4% for ρ_resid.
- **F4.** The fitted power-law exponent α_S(M) is approximately decreasing in M, with a small non-monotonicity at M = 6 and M = 30 (α_S = 1.170 and 1.177 respectively), declining smoothly thereafter; α_ρ(M) is monotone decreasing over the observed ladder. The two sequences cross between M = 30 and M = 210.
- **F5.** No simple normalisation collapses all M-curves onto a single shape.

The following are not established:

- **N1.** A specific mathematical form for S(M, L) or ρ_resid(M, L).
- **N2.** Independently validated values for α_S(M) or α_ρ(M); the fitted exponents are descriptive summaries from a single dataset.
- **N3.** Universality of the L-dependence across M.

Section 6 examines N1 and the identifiability of the functional form.
