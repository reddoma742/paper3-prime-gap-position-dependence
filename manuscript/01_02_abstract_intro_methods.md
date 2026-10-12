# 1. Introduction

## 1.1 Background

Papers 1 and 2 established two empirical facts about the lag-one covariance of consecutive prime gaps g_n = p_{n+1} − p_n.

Paper 1 (Zenodo DOI 10.5281/zenodo.23162269) reported persistent negative lag-one dependence in locally detrended prime-gap windows up to N = 10⁹. The elementary independent-gap version of the Cramér heuristic does not encode the observed negative lag-one dependence [3, 4].

Paper 2 (Zenodo DOI 10.5281/zenodo.23222536) introduced an ABCD decomposition of the lag-one covariance. Let
e_n = g_n − (α + β · log p_n)
denote the residual after the global detrending g ≈ α + β · log p used throughout this work. For each primorial modulus M, the residual sequence is partitioned by the opening-prime residue r_n = p_n mod M, and the residual is written as e_n = μ(r_n) + u_n, where μ(r) is the phase mean for residue r and u_n is the within-class residual. The lag-one covariance of the detrended gaps then decomposes exactly as
Cov(e_n, e_{n+1}) = A + X + Y + D,
where A = E[μ_prev · μ_cur], X = E[μ_prev · u_cur], Y = E[u_prev · μ_cur], D = E[u_prev · u_cur]. The non-D covariance share is
S(M) = (A + X + Y) / Cov(e_n, e_{n+1}) = 1 − D / Cov(e_n, e_{n+1}),
an algebraic ratio of the non-D covariance components to the total; it is not a causal 'fraction explained' and may exceed one or be negative if the cross terms X or Y dominate. In the single window [10¹⁰, 3×10¹⁰) with 844,953,415 gaps, S(M) ranged from approximately 1.5% at M = 6 to 60.4% at M = 9699690. The residual correlation ρ_resid(M) = D / var_within was strictly negative at every modulus tested.

## 1.2 The preregistered question

The present work asked whether the phase-decomposed covariance structure changes across a sequence of logarithmic windows at different prime locations. The preregistered question was whether the non-D share S(M) would be nondecreasing as the window moved upward on the prime axis.

A protocol (paper3_protocol_v1.md) was committed to the source repository before any computation (commit 13d16db, 2026-10-12; file SHA-256 in the data inventory). No third-party timestamp registry was used; the hash establishes file integrity, not the timing of its conception. It specified seven predictions T1–T7 to be tested on a fixed set of three windows:
W1 = [10⁸, 3×10⁸), W2 = [10⁹, 3×10⁹), W3 = [10¹⁰, 3×10¹⁰) (the window of Paper 2).
The three windows span a factor of approximately 300 in prime location p (from 10⁸ to 3×10¹⁰), corresponding to a factor of approximately 1.24 in L = log p (from L ≈ 18.97 in W1 to L ≈ 23.57 in W3). The protocol contained an abort condition: if any of T1–T7 failed, computation was to stop and the failure reported without modification of the predictions.

## 1.3 What happened

The algebraic checks T1–T2, the within-window empirical patterns T3–T5, and the W3 reproduction check were successful. T6 failed. T7 was descriptive because protocol v1 did not specify a numerical smoothness criterion.

T6 predicted that S(M) would be greater at higher windows than at lower windows, for every modulus M. The data falsify this prediction for every modulus tested: S(M) decreases monotonically from W1 to W3.

The failure motivated — not predetermined — the exploratory fixed-count diagnostic reported in Section 4. Across eight windows with approximately 10⁸ gaps each, spanning prime locations from 10⁸ to 10¹³, S(M) and |ρ_resid(M)| both decrease monotonically with L = log p for every M, while the gap count varies by 5.1%. A four-model comparison shows that the functional form of this dependence is not identified by the available data.

## 1.4 Structure of this paper

Section 2 describes the methods inherited from Papers 1–2 and the modifications introduced in Paper 3. Section 3 reports the preregistered tests and the falsification of T6. Sections 4–6 are explicitly exploratory and are distinguished from the preregistered analysis of Section 3: Section 4 describes the fixed-count diagnostic designed to separate gap count from window position, Section 5 quantifies the position dependence, and Section 6 compares candidate functional forms. Section 7 states the paper's claims and non-claims. Section 8 discusses open questions.

# 2. Methods

## 2.1 Overview

The methods of this paper are inherited from Papers 1 and 2 with three documented additions: runtime window arguments, a dynamic modulus-eligibility rule, and a model-comparison layer. This section describes the shared computational pipeline, the definitions used throughout the paper, and the specific additions. The source code, binary, and data files are recorded with their SHA-256 hashes in the data inventory (paper3_data_inventory.txt).

## 2.2 Prime-gap enumeration

Prime gaps are enumerated by an odd-only segmented sieve of Eratosthenes over the interval [LO, HI). The sieve uses a base-prime set up to ⌈√HI⌉ + 100. Segments contain 2 × 50,000,000 odd candidates each (approximately 10⁸ integers per segment). For each window, we record the sequence
g_n = p_{n+1} − p_n,
where p_n is the n-th prime in [LO, HI) and p_{n+1} is the next prime, possibly greater than HI. The first and last opening primes, the minimum and maximum gap, and the total gap count n are recorded for each window.

The sieve is validated on two small windows, [10⁶, 10⁷) and [10⁷, 10⁸), where the counted numbers of primes match the values 586,081 and 5,096,876 exactly [7, 8] (derived from known prime-counting data). The same prime-generation pipeline was used in Paper 2 and reproduces the Paper 2 result at W3 (Section 3.5). These checks verify the implementation at small scale and reproduce the Paper 2 computation at 10¹⁰. An independent enumeration check at 10¹² is reported in Appendix B; a second independent check near 10¹³ remains desirable but is not performed here.

## 2.3 Window definitions

Three window families are used.

**Preregistered windows (Section 3).** Three windows of the form [10^k, 3 × 10^k) for k = 8, 9, 10:
W1 = [10⁸, 3×10⁸), W2 = [10⁹, 3×10⁹), W3 = [10¹⁰, 3×10¹⁰).
W3 is the window analysed in Paper 2.

**Fixed-count windows (Sections 4–6).** Eight windows, each calibrated to yield approximately 10⁸ gaps, spanning prime locations from 10⁸ to 10¹³:
A, P1, B, P2, P3, C, P4, P5
with parameters listed in Table 4.1. Gap counts range from 95.98 × 10⁶ to 100.85 × 10⁶, a spread of 5.1%. Window A and window P5 differ by a factor of approximately 1.5 in L = log p.

Window parameters are supplied at runtime. In the source used for Papers 1–2, the window bounds LO and HI were compile-time constants. The present paper modifies the linear-analysis executable so that LO and HI are passed as command-line arguments, permitting any specified window to be analysed without recompilation. This is a code-level change; it does not affect the arithmetic.

## 2.4 Detrending

For each window we fit a global trend g ≈ α + β · log p by ordinary least squares over the full window. The residual sequence is
e_n = g_n − (α + β · log p_n).
The linear form is retained as the primary detrending throughout Sections 3–6.

A quadratic diagnostic is also used as a robustness check. For the quadratic fit, we use
g ≈ a + b · z + c · z², z = log p − 0.5 · (log LO + log HI),
so that z is centred within the window. The quadratic diagnostic is reported with the exploratory robustness checks and is referenced again among the paper's limitations and claims.

The symbol u_n denotes the within-class residual throughout; the centered detrending variable in §2.4 and Appendix C is written z to avoid collision.

The numerical stability of the detrending is verified explicitly for the four narrowest fixed-count windows. The raw variance of log p varies from approximately 0.54 in the lowest-position window (A) to approximately 10^-8 in the highest (P5). The OLS slope β is therefore imprecise at high position; its standard error reaches ~31 in P5. We verified by running an independent implementation (Appendix C) with a centered variable z = log1p((p − p_mid)/p_mid) that the reported S(M) and ρ_resid(M) are identical to six decimal places in the four narrow windows tested (P3, P4, P5, C) and at every modulus in those windows, and that the residual variance Var(e) is also unchanged.

## 2.5 ABCD decomposition

For a modulus M, let r_n = p_n mod M denote the residue of the opening prime. Let μ(r) denote the mean of e_n over all n in the window with r_n = r, and let u_n = e_n − μ(r_n) denote the within-class residual. Then the lag-one covariance of the detrended gaps decomposes exactly as
Cov(e_n, e_{n+1}) = A + X + Y + D.
Covariance here denotes the lag-one second moment (1/(N−1)) Σ e_n e_{n+1} over pairs with both indices in the window; it is not the fully centered sample covariance, since the two endpoint residuals do not appear in both roles. The distinction contributes at the 10^-13 level for windows of the size used here.
The four components are defined as
A(M) = E[μ(r_n) · μ(r_{n+1})], X(M) = E[μ(r_n) · u_{n+1}], Y(M) = E[u_n · μ(r_{n+1})], D(M) = E[u_n · u_{n+1}].
The expectation is taken over pairs (n, n+1) in the window. The final gap remains in one-point quantities such as class means and variances; only the final lag-one pair is absent from covariance and ABCD sums because e_{n+1} is not available within the analysed gap sequence.

Two derived quantities are used throughout:
S(M) = (A(M) + X(M) + Y(M)) / Cov(e_n, e_{n+1}) = 1 − D(M) / Cov(e_n, e_{n+1}) (non-D covariance share),
ρ_resid(M) = D(M) / var_within (residual correlation),
where var_within is the empirical within-class second moment of the residuals, equal to the within-class variance under the sample centring used here.

The ABCD decomposition closes to machine precision in every window computed for this paper; the maximum absolute deviation |A + X + Y + D − Cov(e_n, e_{n+1})| is reported per window and never exceeds 7.1 × 10⁻¹⁴.

## 2.6 Modulus eligibility

The candidate ladder is M ∈ {6, 30, 210, 2310, 30030, 510510, 9699690}. After Pass 1, we compute the smallest non-empty residue-class count for each candidate modulus. A modulus is retained as standard when this count is at least 100, retained as diagnostic when it lies between 50 and 99, and excluded when it is below 50.

This rule was introduced for the multi-window extension after the small W1 window revealed that the largest candidate modulus could contain sparse classes. The preregistered W1–W3 analysis was initiated with the fixed candidate ladder of protocol v1. After the W1 sparsity issue was observed, the minimum-class eligibility rule was documented and used for the multi-window extension. The rule does not affect the retained W1–W3 standard moduli, nor the W3 reproduction of Paper 2 at M = 9699690.

Relative to the Paper 2 statistical calculation, the minimum-class eligibility rule is the only change to the set of moduli entering a window-level analysis. Runtime arguments, expanded diagnostics, and output handling are implementation changes; the prime-generation, detrending, and ABCD formulas are otherwise inherited.

## 2.7 Bootstrap

Within-window uncertainty in ρ_resid is estimated by a non-overlapping block bootstrap based on 40 contiguous blocks per window [5, 6]. Each replicate samples 40 of these pre-defined blocks with replacement and concatenates their within-block and boundary contributions. For each modulus M, 1000 replicate resamples are drawn. The seed base for the random number generator is 20261006, incremented per modulus as 20261006 + k · 1000.

The bootstrap confidence intervals reported throughout this paper are marginal within-window intervals. They are not used to assign a joint probability to any cross-window pattern, and they are not treated as independent tests across moduli, because the values of ρ_resid across M within a single window are derived from the same gap sequence and are strongly dependent. Confidence intervals for the fitted exponents α(M) of Section 5.4 are not computed; those values are reported as descriptive summaries only.

## 2.8 Computational structure

Each window is analysed in two passes over the gap sequence.

Pass 1 accumulates the ordinary-least-squares moments for the detrending fit, and the per-residue sums of g_n and log p_n for each modulus. It produces the OLS coefficients α and β, the class means μ(r), and the minimum class count used for eligibility.

Pass 2 re-streams the gap sequence and accumulates, for each modulus, the four ABCD components, the residual variance, the within-class variance, and the block-level quantities used in the bootstrap. The final covariance, S(M), and ρ_resid(M) are computed at the end of Pass 2 from the accumulated sums.

The two-pass structure avoids storing the full gap sequence. Memory usage is independent of the number of gaps, apart from fixed arrays indexed by the selected moduli and by the 40 bootstrap blocks. The largest window analysed in this paper has 844,953,415 gaps.

## 2.9 Model comparison

Section 6 compares four two-parameter models for S(M, L) and |ρ_resid(M, L)|:

| Label | Form | Parameters |
|-------|------|------------|
| power | y = a · L^(−α) | (a, α) |
| reciprocal | y = a + b / L | (a, b) |
| log | y = a + b · log(L) | (a, b) |
| linear | y = a + b · L | (a, b) |

All four have two free parameters. Fits use nonlinear least squares with moment-based starting values. Two metrics are reported in the main text: the residual sum of squares from the full fit, and the small-sample corrected Akaike Information Criterion
AICc = n · ln(RSS / n) + 2k + 2k(k + 1) / (n − k − 1). All comparisons are made on the same data (fixed-count set or combined set) and use the same metric definitions. Because n = 8 for the fixed-count set, AICc rankings are treated as descriptive sensitivity summaries rather than decisive model-selection evidence (Section 6.2).

## 2.10 Data and code

The linear-analysis executable test_multiwindow_v1.exe performs the pipeline of Sections 2.2–2.8 for any window passed as LO HI arguments. A separate executable test_multiwindow_quad_v1.exe performs the quadratic diagnostic of Section 2.4. The Python script paper3_model_comparison.py performs the model comparison of Section 6. All source files, binaries, and CSV outputs are recorded with their SHA-256 hashes in paper3_data_inventory.txt.

The seed base for the bootstrap is 20261006 in every source. Any value of 20260106 appearing in earlier drafts is a typographical error.