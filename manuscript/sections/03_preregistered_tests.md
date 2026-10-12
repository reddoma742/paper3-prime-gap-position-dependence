# 3. Preregistered Tests and Falsification of T6

## 3.1 Protocol v1

Prior to any computation, a protocol (paper3_protocol_v1.md, 2026-10-09) specified seven predictions T1–T7 to be tested on three windows:

| Window | Range | n_gaps | L = log p center |
|--------|-------|--------|------------------|
| W1 | [10⁸, 3×10⁸) | 10,490,870 | 18.9700 |
| W2 | [10⁹, 3×10⁹) | 93,602,003 | 21.2726 |
| W3 | [10¹⁰, 3×10¹⁰) | 844,953,415 | 23.5752 |

The protocol contained an abort condition: if any of T1–T7 failed, computation was to stop and the failure reported without modification of the predictions.

## 3.2 Methods Used in the Preregistered Tests

For each window we computed the lag-one covariance Cov(e_n, e_{n+1}) of consecutive prime gaps g_n = p_{n+1} − p_n with opening prime p_n ∈ [LO, HI), a global detrending g ≈ α + β·log p fitted by OLS, giving e_n = g_n − (alpha + beta · log p_n), per-residue-class means μ[r] of residuals for each M ∈ {6, 30, 210, 2310, 30030, 510510, 9699690} with r = p mod M, and the ABCD decomposition

Cov(e_n, e_{n+1}) = A + X + Y + D,

where A = E[μ_prev · μ_cur], X = E[μ_prev · res_cur], Y = E[res_prev · μ_cur], D = E[res_prev · res_cur]. The non-D covariance share is S(M) = (A + X + Y) / Cov, and the residual correlation is ρ_resid(M) = D / var_within. Block bootstrap confidence intervals used 40 blocks, 1000 replicates, and seed base 20261006 + k·1000.

Modulus eligibility was determined dynamically by the minimum class count over all residues, with classes below 50 samples excluded and classes between 50 and 99 flagged diagnostic. This rule replaced the fixed seven-modulus list that had been used in Paper 2, and constitutes the only logical change to the inherited pipeline.

## 3.3 Results

**Table 3.1 — Preregistered test outcomes.**

| ID | Prediction | Outcome | Evidence |
|----|-----------|---------|----------|
| T1 | \|A+X+Y+D − Cov\| < 10⁻⁶ every row | PASS | max deviation 7.1×10⁻¹⁵ (W1), 7.1×10⁻¹⁵ (W2), 7.1×10⁻¹⁴ (W3) |
| T2 | var_between + var_within = var_e every row | PASS | max deviation ≤ 5.7×10⁻¹⁴ |
| T3 | S(M) monotone increasing in M each window | PASS | 6/6 monotone in all three windows |
| T4 | ρ_resid < 0 for every M in every window | PASS | 18/18 values negative |
| T5 | Bootstrap 95% CIs exclude zero | PASS | 18/18 intervals strictly negative |
| T6 | S(M) at higher window ≥ S(M) at lower window | FAIL | all adjacent window pairs decrease, and all 18 pairwise window–modulus comparisons decrease |
| T7 | A, X, Y, D vary smoothly across windows | Descriptive; not formally testable as preregistered | see §3.3.1 |

### 3.3.1

Protocol v1 did not define a numerical smoothness criterion for T7. The A, X, Y, D components show no visually apparent discontinuity across W1–W3, but T7 is reported descriptively rather than scored as pass or fail.

## 3.4 Falsification of T6

T6 predicted that S(M) would be greater in windows at higher position than at lower position, for every M. The data falsify this in every case.

**Table 3.2 — S(M) across W1, W2, W3.**

| M | S(W1) | S(W2) | S(W3) | W1→W3 decrease |
|---|-------|-------|-------|----------------:|
| 6 | 0.019670 | 0.017458 | 0.015317 | 22.1% |
| 30 | 0.162635 | 0.142455 | 0.125040 | 23.1% |
| 210 | 0.323706 | 0.296759 | 0.272725 | 15.7% |
| 2310 | 0.437143 | 0.410226 | 0.385438 | 11.8% |
| 30030 | 0.525091 | 0.500907 | 0.475868 | 9.4% |
| 510510 | 0.592241 | 0.568517 | 0.544106 | 8.1% |
| 9699690 | — | — | 0.604431 | (n/a) |

S(M) decreases monotonically from W1 to W3 for every modulus tested. Across the six moduli common to W1–W3, the W1-to-W3 decrease ranges from approximately 8% at M = 510510 to 23% at M = 30. The sign of the change is opposite to the prediction: all adjacent window pairs decrease, and all 18 pairwise window–modulus comparisons decrease.

W1, W2, W3 differ simultaneously in gap count n and in window position L = log p. The falsification of T6 does not by itself distinguish between these two explanatory variables. Section 4 addresses this ambiguity with a fixed-count diagnostic.

## 3.5 Reproduction of Paper 2

The window W3 = [10¹⁰, 3×10¹⁰) is the window used in Paper 2. Re-running the v1 pipeline on W3 reproduces the central result of Paper 2:

| Quantity at M = 9699690 | Paper 2 | This work (W3) |
|--------------------------|---------|----------------|
| S(M) | 60.4% | 60.4431% |
| ρ_resid | −0.010306 | −0.010306 |
| \|ABCD − Cov\| | < 10⁻⁶ | < 10⁻¹³ |

This confirms that the prime-generation, detrending, and ABCD calculation reproduce the Paper 2 result at W3. Paper 3 additionally applies a documented post-Pass-1 modulus-eligibility rule based on the observed minimum class count; this rule does not affect the W3 M=9699690 calculation.

## 3.6 What the Falsification Does and Does Not Establish

The failure of T6 is decisive as a statistical fact: across three windows spanning a factor of approximately 300 in prime location (p from 10⁸ to 3×10¹⁰), and with bootstrap intervals quantifying within-window uncertainty in rho_resid, S(M) decreases monotonically with position for every modulus tested.

The falsification does not identify the cause of the decrease. Two candidate explanations remain open:

- **H1 (size):** S depends on the number of gaps n.
- **H2 (position):** S depends on the location of the window on the prime axis, represented by L = log p.

W1, W2, W3 vary both quantities together, so H1 and H2 are not distinguishable from Table 3.2 alone. Section 4 reports a diagnostic designed to separate them.

## 3.7 Protocol Abort Clause

Protocol v1 specified that if any of T1–T7 failed, computation would stop. In accordance with this clause, the execution of the original phase order (W1 → W2 → W3 → W4 → W5 → W6) was halted after W3.

The follow-up diagnostics in Sections 4–6 were conducted under a separate exploratory protocol (paper3_protocol_v2.md), frozen before their execution, and are presented as exploratory rather than preregistered.
