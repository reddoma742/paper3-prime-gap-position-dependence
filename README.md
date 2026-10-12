# Paper 3 — Position Dependence of Phase-Decomposed Lag-One Covariance in Prime-Gap Data

**Author:** Reddouane Berramdane
**Preprint DOI:** [10.5281/zenodo.23319686](https://doi.org/10.5281/zenodo.23319686)
**Date:** 2026-10-12
**License:** CC-BY-4.0

## Summary

This repository contains the full reproducibility package for
Paper 3, a preregistered empirical study of the position
dependence of the phase-decomposed lag-one covariance of
consecutive prime gaps.

A preregistered prediction — that the non-D covariance share
S(M) would not decrease as the window moves upward on the
prime axis — is **falsified**. Across eight fixed-count windows
spanning prime locations from 10^8 to 10^13, both S(M) and
|ρ_resid(M)| decrease monotonically with log p. No unique
functional form is identified; logarithmic, power-law, and
reciprocal descriptions receive comparable support over the
observed range.

## Repository structure

- `paper3_final.pdf` — final manuscript (34 pages)
- `paper3_metadata.yaml` — pandoc metadata for the PDF build
- `manuscript/` — Markdown sources of the paper
- `code/` — C++ and Python sources
- `data/` — CSV outputs and model comparison log
- `protocols/` — frozen preregistered protocols (v1, v2)
- `documentation/` — inventory, changelog, sieve verification log

## Reproducibility

All numerical results can be regenerated from `code/` and
`data/` alone. SHA-256 hashes for every file are recorded in
`documentation/paper3_data_inventory.txt`.

## Companion papers

- Paper 1: [10.5281/zenodo.23162269](https://doi.org/10.5281/zenodo.23162269)
- Paper 2: [10.5281/zenodo.23222536](https://doi.org/10.5281/zenodo.23222536)

## Citation

If you use this work, please cite:

Reddouane Berramdane. *Position Dependence of Phase-Decomposed
Lag-One Covariance in Prime-Gap Data*. Zenodo, 2026.
DOI: [10.5281/zenodo.23319686](https://doi.org/10.5281/zenodo.23319686).
