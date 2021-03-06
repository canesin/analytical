#include <math.h>

double SourceQ_rho_N2 (double x)
{
  double Q_rho_N2;
  double RHO_N;
  double RHO_N2;
  double U;
  double T;
  double TV;
  double kf1_N;
  double kf1_N2;
  double K;
  double R1;
  double w_dot_N2;
  double T_bar;
  RHO_N = rho_N_0 + rho_N_x * sin(a_rho_N_x * PI * x / L);
  RHO_N2 = rho_N2_0 + rho_N2_x * cos(a_rho_N2_x * PI * x / L);
  U = u_0 + u_x * sin(a_ux * PI * x / L);
  T = T_0 + T_x * cos(a_Tx * PI * x / L);
  TV = Tv_0 + Tv_x * cos(a_Tvx * PI * x / L);
  T_bar = pow(T, q) * pow(TV, 0.1e1 - q);
  K = calculate_equilibrium_constant_K(T);
  kf1_N2 = Cf1_N2 * pow(T_bar, etaf1_N2) * exp(-Ea_N2 / R / T_bar);
  kf1_N = Cf1_N * pow(T_bar, etaf1_N) * exp(-Ea_N / R / T_bar);
  R1 = kf1_N * pow(RHO_N, 0.3e1) / K * pow(M_N, -0.3e1) - kf1_N * RHO_N2 * RHO_N * pow(M_N, -0.2e1) / 0.2e1 + kf1_N2 * RHO_N * RHO_N * RHO_N2 / K * pow(M_N, -0.3e1) / 0.2e1 - kf1_N2 * RHO_N2 * RHO_N2 * pow(M_N, -0.2e1) / 0.4e1;
  w_dot_N2 = 0.2e1 * M_N * R1;
  Q_rho_N2 = -a_rho_N2_x * PI * rho_N2_x * U * sin(a_rho_N2_x * PI * x / L) / L + a_ux * PI * u_x * RHO_N2 * cos(a_ux * PI * x / L) / L - w_dot_N2;
  return(Q_rho_N2);
}
