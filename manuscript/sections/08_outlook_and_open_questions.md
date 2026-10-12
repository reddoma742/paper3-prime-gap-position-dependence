# 8. Outlook and Open Questions

## 8.1 The Central Open Question

The empirical result of this paper can be stated in one sentence: the phase-decomposed lag-one covariance of prime gaps weakens systematically with window position L = log p, at approximately fixed gap count, across the range L ∈ [19.96, 29.93]. No single two-parameter functional form is uniquely identified by the data.

This raises a question the paper does not answer: what is the mechanism?

The question can be phrased in several equivalent ways:

- Why does the non-D covariance share S(M) decrease as the window moves to higher position?
- Why does the residual correlation ρ_resid — the part not captured by any finite-modulus phase structure — weaken in the same direction?
- Is the weakening a property of the prime sequence itself, or of the estimation of residue-class means over a finite window?

Several explanations have been examined and, in some cases, disfavoured by the analyses; the mechanism remains open.

## 8.2 What Has Been Disfavoured

**(a) Sample size.** The fixed-count set holds n within 5.1%, while S varies by 14–37%. The design removes the most direct sample-size confounding; a pure sample-size explanation is strongly disfavoured.

**(b) Linear detrending artifact.** The quadratic diagnostic of Section 2.4 shows that the decrease survives a specific smooth-curvature alternative.

**(c) Position-calibration artifact.** No evidence of a position-calibration artifact appears in the duplicated-window check: B/P2 and C/P4 agree to five or six significant digits for M ≤ 30030, and to four significant digits for M = 510510. This does not exclude a systematic error shared by all runs.

Beyond these three exclusions, the cause of the position dependence remains open.

## 8.3 Candidate Directions

The following directions are recorded as possible explanations. None is advanced as a claim.

**(i) Finite-range effect.** If the underlying phase structure of prime gaps is position-independent, the observed weakening might reflect the finiteness of the window: as L grows, the per-class sample mean becomes a poorer estimator of the underlying structure, and S declines without any change in the true structure. A finite-range explanation could produce curvature, slowing, saturation, or a crossover outside the observed range. The present data do not distinguish these possibilities from continued decay.

**(ii) Genuine structural drift.** Alternatively, the weakening could reflect a change in the distribution of consecutive gaps as the prime axis is traversed, with residue-class structure becoming less informative at high position. Under this hypothesis, the weakening continues beyond the observed range.

The present data cannot distinguish (i) from (ii). This distinction is the principal open question raised by the paper.

**(iii) Residue-class sparsity interaction.** The decrease in S is greater at small M and smaller at large M. If the mechanism operated through the number of classes per modulus φ(M), a different pattern might be expected. The observed pattern does not point to a simple class-count mechanism.

**(iv) Estimator-distribution interaction.** The per-residue-class means μ[r] are estimated from the same gap sequence as the residuals. If the estimation error decreases with sample size more slowly than the true phase signal, S may appear to decline. This hypothesis is related to (i) but distinct: it concerns the interaction between the estimator and the underlying distribution.

No mechanism is identified. The four directions are listed to guide future work, not to select among them.

## 8.4 Concrete Experimental Paths

The following experiments would advance the open questions and are feasible within the current computational setup.

**(a)** Extend the L range. Current range: L ∈ [19.96, 29.93], factor 1.50. Windows at 10¹⁴ and 10¹⁵ would extend this to factors of approximately 1.60 and 1.76 respectively; a factor of 2 would require a window near 2×10¹⁷. With the current sieve, a window at 10¹⁴ with n ≈ 10⁸ gaps requires approximately 10–15 minutes; at 10¹⁵, approximately 1–2 hours. This is the most direct route to test whether the weakening slows or continues.

**(b)** Add additional squarefree CRT-aligned moduli, ideally intermediate primorial products or explicitly documented products of distinct small primes.

**(c)** Independent sieve verification. Extend the independent comparison to a second high-position window, preferably near 10¹³. Compare counts, first and last primes, and gap sums. This would eliminate residual concern about systematic error at large position.

**(d)** Broader detrending forms. A systematic study using local polynomial regression, splines, or detrending on log log p would test whether the ABCD decomposition is robust to broader families of detrending choices.

**(e)** Joint bootstrap across windows. A joint bootstrap would provide confidence intervals for the fitted exponents and for the crossing point of the α-ladder. This is a methodological improvement, not a new empirical question.

## 8.5 What This Paper Does Not Attempt

Paper 3 is an empirical report. It does not attempt a theoretical model of prime-gap phase structure, a connection to analytic number theory, a prediction for other arithmetic sequences, or computational optimization of the current pipeline. These omissions are deliberate.

## 8.6 A Note on Method

This project began with a preregistered protocol (v1) containing seven predictions. One of them, T6, failed. The failure drove the subsequent investigation reported here.

A falsified prediction is data, not embarrassment. The choice to freeze a prediction in advance and to report its failure without modification is what makes the surprising direction of the effect credible. Had T6 been formulated after seeing the data, the observed decrease of S with position would carry much less evidential weight.

This is recorded as a description of how the present results were obtained, not as a methodological prescription.

## 8.7 Closing

The phase-decomposed lag-one covariance of prime gaps decreases systematically with window position L = log p, at approximately fixed gap count, across the range L ∈ [19.96, 29.93]. The decrease is monotone in every modulus tested, robust to the choice of global detrending form, reproduced at duplicated positions, and not attributable to a pure sample-size effect.

The decrease is not described by any single two-parameter functional form that the available data identify. Logarithmic, power-law, and reciprocal descriptions receive comparable support over the observed range, with the logarithmic form closest to the leader at every modulus; the linear-in-L form is substantially disfavored.

Whether the weakening slows at higher position or continues indefinitely is the principal open question. The answer lies beyond the range accessible to the present study.

We offer the result as an empirical finding, not a theoretical claim.

## 8.8 Acknowledgments

This work was carried out with extensive assistance from
large-language-model systems at every stage of the project:

- **DeepSeek** contributed the initial theoretical framing
  of the ABCD decomposition, the design of the preregistered
  protocol v1, the analysis of the T6 falsification, and the
  fixed-count diagnostic that separates gap count from window
  position.

- **Claude, accessed via Perplexity**, provided four rounds
  of critical methodological review. These reviews identified
  the algebraic redundancy between the lag-one covariance, the
  residual correlation, and the residual variance; the
  non-identifiability of power-law, logarithmic, and reciprocal
  descriptions over the observed narrow range of L; the nested
  structure of the paired windows B ⊂ P2 and C ⊃ P4; the
  numerical under-determination of the OLS slope in
  high-position windows; and numerous textual and statistical
  corrections throughout the manuscript.

- **OpenCode** served as the local execution platform. Within
  it, three successive models carried out the computational
  work: **Big Pickle**, **Long Cat**, and finally **Muse Spark**.
  Together they executed all numerical runs, generated the CSV
  outputs, performed the independent sieve verification at 10^12
  against primesieve 12.16, ran the numerical-stability check
  with the centered-variable implementation, and produced the
  LaTeX/PDF build and the reproducibility package.

- **Kimi** and **GPT 6.1 Sol** provided additional critical
  reviews that identified further numerical and conceptual
  inconsistencies, including the AICc comparison error, the
  significant-digits claim in the paired-window check, and
  several reference and citation issues.

The human author (R.B.) is solely responsible for the
scientific claims, the design decisions, the choice of
methods, and any errors that remain.

A full reproducibility package — source code, CSV outputs,
frozen protocols, data inventory with SHA-256 hashes, and the
verification logs — is deposited alongside this manuscript on
Zenodo.
