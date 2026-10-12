# 4. Fixed-Count Diagnostic

## 4.1 Motivation

Section 3 established that S(M) decreases from W1 to W3 for every M, but W1, W2, W3 differ simultaneously in gap count n and in position L = log p. To distinguish between H1 (size) and H2 (position), we designed a set of windows in which n is held approximately fixed and L is varied.

If S depends on n, it should remain approximately constant across this set. If S depends on position, it should vary.

## 4.2 Window Design

Eight windows were constructed, each calibrated to yield approximately 10⁸ gaps.

**Table 4.1 — Fixed-count window set.**

| Label | Range | n_gaps | L = log p center |
|-------|-------|--------|-------------------|
| A | [10⁸, 2.18×10⁹) | 100,849,143 | 19.9616 |
| P1 | [10⁹, 3.145×10⁹) | 100,239,099 | 21.2962 |
| B | [10¹⁰, 1.222×10¹⁰) | 95,979,254 | 23.1261 |
| P2 | [10¹⁰, 1.2305×10¹⁰) | 99,639,099 | 23.1296 |
| P3 | [10¹¹, 1.02535×10¹¹) | 100,039,703 | 25.3410 |
| C | [10¹², 1.00277×10¹²) | 100,245,924 | 27.6324 |
| P4 | [10¹², 1.002765×10¹²) | 100,064,944 | 27.6324 |
| P5 | [10¹³, 1.0002995×10¹³) | 100,055,061 | 29.9338 |

The gap count varies between 95.98×10⁶ and 100.85×10⁶, a spread of 5.1%. The window set spans five decades in prime location p (10⁸ to 10¹³), corresponding to a factor of approximately 1.50 in L = log p (from 19.96 to 29.93).

Two pairs of windows were placed at nearly identical positions as an internal reproducibility check: (B, P2) at L ≈ 23.13 and (C, P4) at L ≈ 27.63.

## 4.3 S(M) Across the Fixed-Count Set

**Table 4.2a — S(M) across the fixed-count set (M = 6, 30, 210).**

| Window | L | S(6) | S(30) | S(210) |
|--------|---|------|-------|--------|
| A | 19.9616 | 0.018154 | 0.148372 | 0.304672 |
| P1 | 21.2962 | 0.017385 | 0.142180 | 0.296332 |
| B | 23.1261 | 0.015694 | 0.127535 | 0.275772 |
| P2 | 23.1296 | 0.015679 | 0.127509 | 0.275648 |
| P3 | 25.3410 | 0.014028 | 0.113996 | 0.255664 |
| C | 27.6324 | 0.012484 | 0.102751 | 0.240956 |
| P4 | 27.6324 | 0.012483 | 0.102733 | 0.240951 |
| P5 | 29.9338 | 0.011521 | 0.092723 | 0.226046 |

**Table 4.2b — S(M) across the fixed-count set (M = 2310, 30030, 510510).**

| Window | L | S(2310) | S(30030) | S(510510) |
|--------|---|---------|----------|-----------|
| A | 19.9616 | 0.418677 | 0.509198 | 0.576448 |
| P1 | 21.2962 | 0.409693 | 0.500101 | 0.567502 |
| B | 23.1261 | 0.387465 | 0.477681 | 0.546156 |
| P2 | 23.1296 | 0.387432 | 0.477455 | 0.545785 |
| P3 | 25.3410 | 0.366755 | 0.456336 | 0.525676 |
| C | 27.6324 | 0.351249 | 0.442187 | 0.511301 |
| P4 | 27.6324 | 0.351294 | 0.442255 | 0.511412 |
| P5 | 29.9338 | 0.334435 | 0.423067 | 0.494000 |

For every M, S decreases monotonically with L across the eight windows. The relative decrease from A to P5 (ΔL = 9.9722) is:

| M | S(A) | S(P5) | Relative decrease |
|---|------|-------|--------------------|
| 6 | 0.018154 | 0.011521 | 36.5% |
| 30 | 0.148372 | 0.092723 | 37.5% |
| 210 | 0.304672 | 0.226046 | 25.8% |
| 2310 | 0.418677 | 0.334435 | 20.1% |
| 30030 | 0.509198 | 0.423067 | 16.9% |
| 510510 | 0.576448 | 0.494000 | 14.3% |

The relative decrease varies with M, from 14% at M = 510510 to 37% at M = 30.

## 4.4 ρ_resid(M) Across the Fixed-Count Set

**Table 4.3a — ρ_resid(M) across the fixed-count set (M = 6, 30, 210).**

| Window | L | ρ(6) | ρ(30) | ρ(210) |
|--------|---|------|-------|--------|
| A | 19.9616 | −0.029194 | −0.025414 | −0.020913 |
| P1 | 21.2962 | −0.027907 | −0.024444 | −0.020197 |
| B | 23.1261 | −0.025513 | −0.022675 | −0.018940 |
| P2 | 23.1296 | −0.025530 | −0.022691 | −0.018956 |
| P3 | 25.3410 | −0.022949 | −0.020667 | −0.017453 |
| C | 27.6324 | −0.020527 | −0.018682 | −0.015874 |
| P4 | 27.6324 | −0.020526 | −0.018678 | −0.015871 |
| P5 | 29.9338 | −0.018701 | −0.017189 | −0.014718 |

**Table 4.3b — ρ_resid(M) across the fixed-count set (M = 2310, 30030, 510510).**

| Window | L | ρ(2310) | ρ(30030) | ρ(510510) |
|--------|---|---------|----------|-----------|
| A | 19.9616 | −0.017636 | −0.015026 | −0.013090 |
| P1 | 21.2962 | −0.017080 | −0.014589 | −0.012734 |
| B | 23.1261 | −0.016130 | −0.013857 | −0.012136 |
| P2 | 23.1296 | −0.016142 | −0.013873 | −0.012153 |
| P3 | 25.3410 | −0.014935 | −0.012904 | −0.011335 |
| C | 27.6324 | −0.013634 | −0.011786 | −0.010386 |
| P4 | 27.6324 | −0.013630 | −0.011791 | −0.010388 |
| P5 | 29.9338 | −0.012711 | −0.011071 | −0.009762 |

All 48 values are strictly negative. All 48 marginal bootstrap intervals within windows exclude zero. These intervals support the persistence of negative residual correlation within the analysed windows; they are not treated as 48 independent tests, since the values across M within a single window are derived from the same gap sequence and are strongly dependent.

The magnitude of ρ_resid decreases monotonically with L for every M, mirroring the behaviour of S.

## 4.5 Internal Reproducibility Check

Two pairs of windows lie at nearly identical positions: B (L = 23.1261) and P2 (L = 23.1296), separated by ΔL = 0.0035; and C (L = 27.6324) and P4 (L = 27.6324), with identical L.

**Table 4.4 — Reproducibility at duplicated positions.**

| Pair | ΔL | \|ΔS(6)\| | \|ΔS(510510)\| | \|Δρ(6)\| | \|Δρ(510510)\| |
|------|-----|-----------|----------------|-----------|----------------|
| B vs P2 | 0.0035 | 1.5×10⁻⁵ | 3.7×10⁻⁴ | 1.7×10⁻⁵ | 1.7×10⁻⁵ |
| C vs P4 | 0.0000 | 1.0×10⁻⁶ | 1.1×10⁻⁴ | 1.0×10⁻⁶ | 4.0×10⁻⁶ |

The differences between the paired estimates are ≤ 3.7×10^-4 in S and ≤ 1.7×10^-5 in ρ. Since the tables report six decimal places, these differences exceed the last printed digit for the larger-modulus S values, but they remain roughly 200 times smaller than the total A-to-P5 decrease reported in Section 5. Because the paired windows overlap substantially (B is a strict subset of P2, with ~96% of P2's gap count shared; C contains P4, with ~99.8% of C's gap count shared with P4), the numerical agreement reported here is not an independent replication. It demonstrates insensitivity of the estimates to small changes in the window endpoint at essentially fixed position. It does not rule out a systematic error shared by all runs.

## 4.6 Interpretation

Under the constraint n ≈ 10⁸ ± 5.1%, S and |ρ_resid| both decrease monotonically with L for every M tested. Because n varies by less than 5.1% while S varies by 14–37%, the fixed-count diagnostic strongly disfavours a pure sample-size explanation. The design does not establish a unique causal variable; see §4.7.

H1 (pure sample-size explanation) is strongly disfavoured by this diagnostic, given the approximately fixed n and the smooth, monotone decline of S across positions. A quantitative exclusion of every conceivable sample-size mechanism would require sampling multiple n values at each position; this is not attempted here.

## 4.7 Caveats

Three limitations must be stated explicitly.

**(a)** The gap count is approximately, not exactly, fixed. n varies from 95.98×10⁶ to 100.85×10⁶, a spread of 5.1%. This is small compared to the 14–37% variation in S, but it is not zero.

**(b)** Window width in x varies. Holding n approximately fixed requires widening the window as position increases, since prime density decreases. Window A spans 2.08×10⁹ in x; window P5 spans 2.995×10⁹ in x. The width in x varies only by a factor of about 1.44 across the eight windows; the quantity that varies strongly is the relative span Δx/x, which falls from ~20.8 in window A to ~3×10^-4 in P5.

**(c)** Position is represented by L = log p. We use L as a proxy for window location. This is the natural choice given the heuristic scale of prime gaps, but it does not exclude the possibility that the true explanatory variable is some other monotone function of position.

An additional note: the fixed-count set and the variable-count set of Section 3 are not directly comparable. They differ in design and should not be pooled without accounting for this difference; the model comparison of Section 6 is presented separately for this reason.

## 4.8 Summary

Within eight fixed-count windows spanning L ∈ [19.96, 29.93] at n ≈ 10⁸:

- S(M) decreases monotonically with L for every M tested.
- ρ_resid(M) decreases in magnitude monotonically with L for every M tested.
- The total relative decrease is 14–37% depending on M.
- Duplicated positions agree to five or six significant digits for M ≤ 30030, and to four significant digits for M = 510510.
- The fixed-count diagnostic strongly disfavours a pure sample-size explanation. The functional form of the position dependence is examined in Section 5.
