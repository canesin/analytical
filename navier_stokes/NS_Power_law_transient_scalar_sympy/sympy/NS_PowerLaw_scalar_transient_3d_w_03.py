
# Loading the file for the equations, manufactured solutions and original soource terms

execfile("NS_PowerLaw_scalar_transient_3d_w_02.py")

#Checking manipulations

#Q1 and Q1n -----------------------------------------------------------------------------
Q=Q1n.subs(Rho,rho_0 + rho_x * sin(a_rhox * pi * x / L) + rho_y * cos(a_rhoy * pi * y / L) + rho_z * sin(a_rhoz * pi * z / L) + rho_t * sin(a_rhot *
pi * t / Lt));
Q=Q.subs(U, u_0 + u_x * sin(a_ux * pi * x / L) + u_y * cos(a_uy * pi * y / L) + u_z * cos(a_uz * pi * z / L) + u_t * cos(a_ut * pi * t / Lt));
Q=Q.subs(V, v_0 + v_x * cos(a_vx * pi * x / L) + v_y * sin(a_vy * pi * y / L) + v_z * sin(a_vz * pi * z / L) + v_t * sin(a_vt * pi * t / Lt));
Q=Q.subs(W, w_0 + w_x * sin(a_wx * pi * x / L) + w_y * sin(a_wy * pi * y / L) + w_z * cos(a_wz * pi * z / L) + w_t * cos(a_wt * pi * t / Lt));
Q=Q.subs(P, p_0 + p_x * cos(a_px * pi * x / L) + p_y * sin(a_py * pi * y / L) + p_z * cos(a_pz * pi * z / L) + p_t * cos(a_pt * pi * t / Lt));


Res1=expand(Q1-Q)
Res1==0 #true

Q_w_convection=Q1n

#Q2 and Q2n -----------------------------------------------------------------------------
Res2=expand(Q2-Q2n)
Res2==0 #true

Q_w_gradp=Q2n

#Q3 and Q3n -----------------------------------------------------------------------------
Q=Q3.subs(LAMBDA, (alpha-Rational(2,3))*Mu);
Q=Q.subs(Mu,mu);
Q=Q.subs(DMu_Dx,diff(mu,x));
Q=Q.subs(DMu_Dy,diff(mu,y));
Q=Q.subs(DMu_Dz,diff(mu,z));

Res3=expand(Q3-Q)
Res3==0 #true


Q_w_viscous=Q3n

#Q4 and Q4n -----------------------------------------------------------------------------
Q=Q4n.subs(Rho,rho_0 + rho_x * sin(a_rhox * pi * x / L) + rho_y * cos(a_rhoy * pi * y / L) + rho_z * sin(a_rhoz * pi * z / L) + rho_t * sin(a_rhot *
pi * t / Lt));
Q=Q.subs(U, u_0 + u_x * sin(a_ux * pi * x / L) + u_y * cos(a_uy * pi * y / L) + u_z * cos(a_uz * pi * z / L) + u_t * cos(a_ut * pi * t / Lt));
Q=Q.subs(V, v_0 + v_x * cos(a_vx * pi * x / L) + v_y * sin(a_vy * pi * y / L) + v_z * sin(a_vz * pi * z / L) + v_t * sin(a_vt * pi * t / Lt));
Q=Q.subs(W, w_0 + w_x * sin(a_wx * pi * x / L) + w_y * sin(a_wy * pi * y / L) + w_z * cos(a_wz * pi * z / L) + w_t * cos(a_wt * pi * t / Lt));
Q=Q.subs(P, p_0 + p_x * cos(a_px * pi * x / L) + p_y * sin(a_py * pi * y / L) + p_z * cos(a_pz * pi * z / L) + p_t * cos(a_pt * pi * t / Lt));


Res4=expand(Q4-Q)
Res4==0 #true

Q_w_time=Q4n


# Q_w -----------------------------------------------------------------------------------
Q_w=Q_w_convection+Q_w_gradp+Q_w_viscous+Q_w_time
#print(Q_w)
#print('\n')


# Saving to C files ---------------------------------------------------------------------
Results=Res1+Res2+Res3+Res4

# Saving to C files ---------------------------------------------------------------------
# Asking for futher numerical tests------------------------------------------------------
var('y,Y')
name = input("Save results to C files? [y/n]:") 
if name == y or name==Y:
  if Results == 0:
    execfile("NS_PowerLaw_scalar_transient_3d_viscosity.py") #calculating the derivatives of mu
    print 'Successfull factorization: Q_w'
    print 'Writing C code for Q_w  -> ../C_codes/NS_PowerLaw_scalar_transient_3d_w.c'
    execfile("NS_PowerLaw_scalar_transient_3d_w_codes.py")  
    print 'Done.'
  else:
    print 'ERROR: Possible problems in the factorization!'
    
print '\n'

numerical_tests  = input("Perform numerical test to address correctness in the mapinulations? [y/n]:") 

if numerical_tests == y or numerical_tests == Y:
 execfile("NS_PowerLaw_scalar_transient_3d_w_check_numerically.py")
 print 'Done.'


