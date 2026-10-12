// test_multiwindow_quad_v1.cpp
// Paper 3 — Quadratic detrending diagnostic
//
// Question: is the systematic decrease of S(M,L) with L (seen in W1, W2, W3
//           under linear detrending) an artifact of the linear-only form
//           g ≈ a + b·log p, or a real feature?
//
// Test: replace global detrending by a quadratic fit
//           g ≈ a + b·u + c·u²,   u = log p − 0.5(log LO + log HI)
//       and compare S(M,L) across W1, W2, W3.
//
// Everything else identical to test_multiwindow_v1.cpp.
//
// Build:
//   g++ -O2 -std=c++17 -Wall -static test_multiwindow_quad_v1.cpp \
//       -o test_multiwindow_quad_v1.exe

#include <bits/stdc++.h>
using namespace std;

uint64_t isqrt(uint64_t n) {
    if (n == 0) return 0;
    uint64_t r = (uint64_t)std::sqrt((double)n);
    while (r * r > n) r--;
    while ((r + 1) * (r + 1) <= n) r++;
    return r;
}

uint64_t phi_of(uint64_t M) {
    uint64_t res = M, m = M;
    for (uint64_t p = 2; p*p <= m; ++p) if (m % p == 0) {
        res = res/p*(p-1);
        while (m % p == 0) m /= p;
    }
    if (m > 1) res = res/m*(m-1);
    return res;
}

vector<uint32_t> base_primes(uint32_t limit) {
    vector<bool> s(limit + 1, true);
    s[0] = s[1] = false;
    for (uint32_t i = 2; (uint64_t)i*i <= limit; ++i)
        if (s[i])
            for (uint64_t j = (uint64_t)i*i; j <= limit; j += i)
                s[(size_t)j] = false;
    vector<uint32_t> out;
    for (uint32_t i = 2; i <= limit; ++i)
        if (s[i]) out.push_back(i);
    return out;
}

template<class F>
void stream_gaps(uint64_t lo, uint64_t hi, F callback) {
    if (lo < 3) lo = 3;
    if (lo % 2 == 0) lo++;
    uint64_t root = isqrt(hi) + 100;
    vector<uint32_t> base = base_primes((uint32_t)root);
    const uint64_t SEG_ODDS = 50000000ULL;
    uint64_t prev_prime = 0;
    bool closed = false;
    uint64_t closing_prime = 0;
    for (uint64_t s = lo; !closed; s += 2 * SEG_ODDS) {
        uint64_t seg_end = s + 2 * SEG_ODDS;
        vector<bool> flag(SEG_ODDS, true);
        for (uint32_t q : base) {
            if (q == 2) continue;
            uint64_t q2 = (uint64_t)q * q;
            if (q2 >= seg_end) break;
            uint64_t first = max(q2, ((s + q - 1) / q) * q);
            if ((first & 1ULL) == 0) first += q;
            if (first >= seg_end) continue;
            for (uint64_t j = first; j < seg_end; j += 2ULL * q)
                flag[(size_t)((j - s) / 2)] = false;
        }
        for (uint64_t j = 0; j < SEG_ODDS; ++j) {
            if (!flag[(size_t)j]) continue;
            uint64_t p = s + 2 * j;
            if (p < lo) { prev_prime = p; continue; }
            if (prev_prime > 0 && prev_prime >= lo && prev_prime < hi) {
                callback(prev_prime, p - prev_prime);
                if (p > hi) { closing_prime = p; closed = true; }
            }
            prev_prime = p;
            if (closed) break;
        }
    }
    if (!closed) throw runtime_error("Window boundary was not closed");
    if (closing_prime <= hi) throw runtime_error("closing_prime <= HI");
}

int main(int argc, char** argv) {
    uint64_t LO = 10000000000ULL;
    uint64_t HI = 30000000000ULL;
    if (argc >= 3) {
        LO = strtoull(argv[1], nullptr, 10);
        HI = strtoull(argv[2], nullptr, 10);
    }
    string csvname = "phase_decomp_quad_" + to_string(LO) + "_" + to_string(HI) + ".csv";
    string logname = "log_quad_"          + to_string(LO) + "_" + to_string(HI) + ".txt";

    cerr << "=== QUADRATIC detrend test, window [" << LO << ", " << HI << ") ===\n";

    auto T0 = chrono::steady_clock::now();
    ofstream fout(logname);
    auto P = [&](const string& s){ cout << s; fout << s; };

    // ---- PART 0: small-scale validation ----
    cerr << "\n=== PART 0: Validation ===\n";
    struct VC { uint64_t lo, hi, exp; };
    vector<VC> val = {
        {1000000ULL,   10000000ULL,  664579-78498},
        {10000000ULL, 100000000ULL, 5761455-664579}
    };
    for (auto& v : val) {
        uint64_t n = 0;
        stream_gaps(v.lo, v.hi, [&](uint64_t, uint64_t){ n++; });
        ostringstream ss;
        ss << "  [" << v.lo << "," << v.hi << "): n=" << n
           << " expected=" << v.exp
           << " " << (n==v.exp ? "PASS" : "FAIL") << "\n";
        P(ss.str());
    }

    const vector<uint64_t> M_cand = { 6, 30, 210, 2310, 30030, 510510, 9699690 };
    const size_t nCand = M_cand.size();

    // ---- PASS 1: quadratic moments ----
    long double y0 = 0.5L * (logl((long double)LO) + logl((long double)HI));
    cerr << "PASS 1: quadratic moments (y0=" << (double)y0 << ")\n";

    uint64_t n1 = 0;
    long double Su=0, Suu=0, Suuu=0, Suuuu=0;
    long double Sg=0, Sgu=0, Sguu=0, Sgg=0;

    vector<vector<long double>> sum_g(nCand), sum_u(nCand), sum_uu(nCand);
    vector<vector<uint32_t>>    cnt(nCand);
    vector<uint64_t> phiM(nCand);
    for (size_t k = 0; k < nCand; ++k) {
        phiM[k] = phi_of(M_cand[k]);
        sum_g[k].assign(M_cand[k], 0.0L);
        sum_u[k].assign(M_cand[k], 0.0L);
        sum_uu[k].assign(M_cand[k], 0.0L);
        cnt[k].assign(M_cand[k], 0);
    }

    stream_gaps(LO, HI, [&](uint64_t p, uint64_t g) {
        long double u  = logl((long double)p) - y0;
        long double uu = u*u;
        long double gd = (long double)g;
        n1++;
        Su += u; Suu += uu; Suuu += uu*u; Suuuu += uu*uu;
        Sg += gd; Sgu += gd*u; Sguu += gd*uu; Sgg += gd*gd;

        for (size_t k = 0; k < nCand; ++k) {
            uint32_t r = (uint32_t)(p % M_cand[k]);
            sum_g[k][r]  += gd;
            sum_u[k][r]  += u;
            sum_uu[k][r] += uu;
            cnt[k][r]++;
        }
    });

    long double dn = (long double)n1;

    // 3x3 normal equations: g ≈ a + b·u + c·u²
    long double A00=dn, A01=Su,  A02=Suu;
    long double A10=Su, A11=Suu, A12=Suuu;
    long double A20=Suu,A21=Suuu,A22=Suuuu;
    long double r0=Sg,  r1=Sgu,  r2=Sguu;

    long double det = A00*(A11*A22 - A12*A21)
                    - A01*(A10*A22 - A12*A20)
                    + A02*(A10*A21 - A11*A20);
    if (fabsl(det) < 1e-30L) throw runtime_error("Singular 3x3");
    long double det_a = r0*(A11*A22-A12*A21) - A01*(r1*A22-A12*r2) + A02*(r1*A21-A11*r2);
    long double det_b = A00*(r1*A22-A12*r2) - r0*(A10*A22-A12*A20) + A02*(A10*r2-r1*A20);
    long double det_c = A00*(A11*r2-r1*A21) - A01*(A10*r2-r1*A20) + r0*(A10*A21-A11*A20);
    long double qa = det_a/det, qb = det_b/det, qc = det_c/det;

    cerr << "  Quadratic: g ≈ " << (double)qa
         << " + " << (double)qb << "·u + " << (double)qc << "·u²\n";

    // Class means of quadratic residuals
    vector<vector<double>> mu(nCand);
    vector<uint32_t> min_class_cand(nCand);
    for (size_t k = 0; k < nCand; ++k) {
        mu[k].assign(M_cand[k], 0.0);
        uint32_t mc = UINT32_MAX;
        for (uint64_t r = 0; r < M_cand[k]; ++r) {
            if (cnt[k][r] == 0) continue;
            if (cnt[k][r] < mc) mc = cnt[k][r];
            long double nc = (long double)cnt[k][r];
            mu[k][r] = (double)((sum_g[k][r] - qa*nc - qb*sum_u[k][r]
                                - qc*sum_uu[k][r]) / nc);
        }
        min_class_cand[k] = mc;
    }

    // Modulus eligibility
    vector<string> category(nCand);
    vector<uint64_t> Ms;
    vector<size_t>   cand_of;
    for (size_t k = 0; k < nCand; ++k) {
        uint32_t mc = min_class_cand[k];
        string st = (mc >= 100) ? "standard" : (mc >= 50) ? "diagnostic" : "eliminated";
        category[k] = st;
        if (st == "eliminated") {
            cerr << "  [modulus] SKIP   M=" << M_cand[k] << " min_class=" << mc << "\n";
        } else {
            Ms.push_back(M_cand[k]);
            cand_of.push_back(k);
            cerr << "  [modulus] KEEP   M=" << M_cand[k] << " min_class=" << mc
                 << " -> " << st << "\n";
        }
    }
    size_t nM = Ms.size();
    for (auto& v : sum_g) v.clear();
    for (auto& v : sum_u) v.clear();
    for (auto& v : sum_uu) v.clear();

    // OLS closure for quadratic: var_e_ols = (Sgg - a·Sg - b·Sgu - c·Sguu)/n
    long double Sg2_model = qa*Sg + qb*Sgu + qc*Sguu;
    double var_g_raw  = (double)(Sgg/dn - (Sg/dn)*(Sg/dn));
    double var_e_ols  = (double)((Sgg - Sg2_model)/dn);
    double mean_g     = (double)(Sg/dn);
    var_e_ols -= mean_g*mean_g - mean_g*mean_g;  // residuals have mean 0
    // More directly:
    var_e_ols = (double)(Sgg/dn) - 2.0*mean_g*(double)(Sg/dn) + mean_g*mean_g
              - (double)((Sg2_model - 2.0*mean_g*Sg)/dn) + mean_g*mean_g;

    // ---- PASS 2 ----
    cerr << "PASS 2: Var, Cov, ABCD, rho_res\n";
    long double sum_e = 0, sum_e2 = 0, sum_ee = 0;
    uint64_t n2 = 0;
    long double prev_e = 0;

    struct MA {
        long double A=0,B=0,C=0,D=0;
        long double sum_res2=0, sum_resres=0;
        uint64_t cnt_ABCD=0, cnt_res=0;
        double prev_mu=0, prev_res=0;
        bool has_prev=false;
    };
    vector<MA> acc(nM);

    const int N_BLOCKS = 40;
    const int N_BOOT   = 1000;
    const uint64_t SEED_BASE = 20261006ULL;
    const size_t block_size = (size_t)n1 / N_BLOCKS;
    if (block_size == 0) throw runtime_error("block_size == 0");
    vector<array<double,40>> bsum_u(nM), bsum_u2(nM), bsum_uu(nM),
                             bfirst(nM), blast(nM);
    for (size_t k = 0; k < nM; ++k) {
        bsum_u[k].fill(0.0); bsum_u2[k].fill(0.0); bsum_uu[k].fill(0.0);
        bfirst[k].fill(0.0); blast[k].fill(0.0);
    }

    stream_gaps(LO, HI, [&](uint64_t p, uint64_t g) {
        long double u  = logl((long double)p) - y0;
        long double e  = (long double)g - (qa + qb*u + qc*u*u);
        n2++;
        sum_e += e; sum_e2 += e*e;
        if (n2 > 1) sum_ee += prev_e * e;
        prev_e = e;

        for (size_t k = 0; k < nM; ++k) {
            uint32_t r = (uint32_t)(p % Ms[k]);
            double mu_cur = mu[cand_of[k]][r];
            double res_cur = (double)e - mu_cur;

            acc[k].sum_res2 += (long double)res_cur*res_cur;
            acc[k].cnt_res++;

            if (acc[k].has_prev) {
                acc[k].A += (long double)acc[k].prev_mu * mu_cur;
                acc[k].B += (long double)acc[k].prev_mu * res_cur;
                acc[k].C += (long double)acc[k].prev_res * mu_cur;
                acc[k].D += (long double)acc[k].prev_res * res_cur;
                acc[k].sum_resres += (long double)acc[k].prev_res * res_cur;
                acc[k].cnt_ABCD++;
            }

            size_t gi = n2 - 1;
            size_t bi = gi / block_size;
            if (bi >= (size_t)N_BLOCKS) bi = N_BLOCKS - 1;
            bsum_u[k][bi]  += res_cur;
            bsum_u2[k][bi] += res_cur*res_cur;
            if (acc[k].has_prev && ((gi-1)/block_size) == bi)
                bsum_uu[k][bi] += acc[k].prev_res * res_cur;
            if (gi == bi*block_size) bfirst[k][bi] = res_cur;
            blast[k][bi] = res_cur;

            acc[k].prev_mu  = mu_cur;
            acc[k].prev_res = res_cur;
            acc[k].has_prev = true;
        }
    });

    assert(n1 == n2);
    double mean_e = (double)(sum_e/dn);
    double var_e  = (double)(sum_e2/dn) - mean_e*mean_e;
    double cov_1  = (double)(sum_ee/(long double)(n2-1)) - mean_e*mean_e;
    double rho_1  = cov_1/var_e;
    double logp_center = 0.5*(log((double)LO) + log((double)HI));

    cerr << "  Var(e) quad = " << var_e << "   (linear was different)\n";
    cerr << "  Cov_1 quad  = " << cov_1 << "\n";
    cerr << "  rho_1 quad  = " << rho_1 << "\n";

    vector<double> var_btw(nM), var_wth(nM);
    for (size_t k = 0; k < nM; ++k) {
        double vb = 0;
        for (uint64_t r = 0; r < Ms[k]; ++r) {
            if (cnt[cand_of[k]][r] == 0) continue;
            double w = (double)cnt[cand_of[k]][r]/(double)n2;
            double dmu = mu[cand_of[k]][r] - mean_e;
            vb += w*dmu*dmu;
        }
        var_btw[k] = vb;
        var_wth[k] = var_e - vb;
    }

    vector<double> bl(nM), bm(nM), bh(nM);
    for (size_t k = 0; k < nM; ++k) {
        mt19937_64 rng(SEED_BASE + k*1000);
        uniform_int_distribution<int> pick(0, N_BLOCKS-1);
        vector<double> rho_b;
        rho_b.reserve(N_BOOT);
        for (int b = 0; b < N_BOOT; ++b) {
            double su2=0, suu=0, pl=0;
            for (int j = 0; j < N_BLOCKS; ++j) {
                int bi = pick(rng);
                su2 += bsum_u2[k][bi];
                suu += bsum_uu[k][bi];
                if (j > 0) suu += pl * bfirst[k][bi];
                pl = blast[k][bi];
            }
            if (su2 > 0) rho_b.push_back(suu/su2);
        }
        sort(rho_b.begin(), rho_b.end());
        bl[k] = rho_b[(size_t)(0.025*rho_b.size())];
        bm[k] = rho_b[rho_b.size()/2];
        bh[k] = rho_b[(size_t)(0.975*rho_b.size())];
        cerr << "  M=" << Ms[k] << ": CI95=[" << bl[k] << "," << bm[k] << "," << bh[k] << "]\n";
    }

    // ---- CSV ----
    ofstream csv(csvname);
    csv << "window,M,n_gaps,logp_center,n_c,min_class,modulus_status,"
        << "var_e,var_g_raw,var_e_ols,cov_e_lag1,rho_e_lag1,"
        << "A,X,Y,D,ABCD_minus_cov,ABCD_over_cov,"
        << "S_nonD,rho_resid,var_between,var_within,"
        << "boot_lo,boot_med,boot_hi,quad_a,quad_b,quad_c\n";

    for (size_t k = 0; k < nM; ++k) {
        double A = (double)(acc[k].A/acc[k].cnt_ABCD);
        double X = (double)(acc[k].B/acc[k].cnt_ABCD);
        double Y = (double)(acc[k].C/acc[k].cnt_ABCD);
        double D = (double)(acc[k].D/acc[k].cnt_ABCD);
        double sum_ABCD = A+X+Y+D;
        double var_res = (double)(acc[k].sum_res2/acc[k].cnt_res);
        double cov_res = (double)(acc[k].sum_resres/(acc[k].cnt_res-1));
        double rho_res = cov_res/var_res;
        double n_c = (double)n2/(double)phiM[cand_of[k]];
        double S_nonD = (A+X+Y)/cov_1;

        csv << "\"[" << LO << "," << HI << ")\""
            << "," << Ms[k]
            << "," << n2
            << "," << fixed << setprecision(6) << logp_center
            << "," << setprecision(2) << n_c
            << "," << min_class_cand[cand_of[k]]
            << "," << category[cand_of[k]]
            << "," << setprecision(6) << var_e
            << "," << var_g_raw
            << "," << var_e_ols
            << "," << cov_1
            << "," << rho_1
            << "," << A << "," << X << "," << Y << "," << D
            << "," << (sum_ABCD - cov_1)
            << "," << (sum_ABCD / cov_1)
            << "," << S_nonD
            << "," << rho_res
            << "," << var_btw[k]
            << "," << var_wth[k]
            << "," << bl[k] << "," << bm[k] << "," << bh[k]
            << "," << (double)qa
            << "," << (double)qb
            << "," << (double)qc
            << "\n";
    }
    csv.close();
    fout.close();

    double dt = chrono::duration<double>(chrono::steady_clock::now()-T0).count();
    cout << "  total time = " << (int)dt << " s\n";
    cout << "  [saved to " << csvname << "]\n";
    return 0;
}