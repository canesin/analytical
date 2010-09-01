#include<math.h>
#include<stdio.h>
#include<stdlib.h>

//---------------------------------------------------------------------
// Koomie Note: found this online somewhere.  Am leaving it mostly in 
// its original form but converting to C for convenience. Also
// converting to a form which provides output as a funcion of 
// time and spatial location.  
//
// Output: out_soln[0] = rho
//         out_soln[1] = rho*u
//         out_soln[2] = rho*e
//
// 1/26/09
//---------------------------------------------------------------------

//  Program calculates the exact solution to Sod-shock tube class
//  problems -- namely shock tubes which produce shocks, contact
//  discontinuities, and rarefraction waves.
//
//  Solution is computed at locations x at time t. (Though   
//  due to self-similarity, the exact solution is identical for
//  identical values of x/t).
//
//  NOTE : Since the post-shock flow is nonadiabatic, whereas
//  the flow inside the rarefraction fan is adiabatic, the problem
//  is not left-right symmetric. In particular, the high-density
//  initial state MUST BE input on the left side.
// 

#define GAMMA 1.4e0
static double mu2  =  (GAMMA - 1.e0) / (GAMMA + 1.e0);

double pl, pr, rhol, rhor, cl, cr;

double rtbis(double x1,double x2,double xacc);
double func(double pm);

void sod1_analytic(double x,double t, double out_soln[])
{
  double xm;

  // xmax determines the size of the computational domain (-xmax, +xmax).
  // numcells determines the number of cells in the output table.          
  // double xmax 	= 5.e0;

  double pm, pressure;
  double rhoml, vs, vt, rhomr, vm, density, velocity;
  int i;
  FILE *fp;

  // Define the Sod problem initial conditions for the left and right states.

  pl = 1.e0;
  pr = 0.125;

  rhol = 1.e0;
  rhor = 0.125;

  // Define sound speeds for the left and right sides of tube.

  cl = sqrt (GAMMA * pl / rhol);
  cr = sqrt (GAMMA * pr / rhor);

  // Solve for the postshock pressure pm.

  pm = rtbis (pr, pl, 1.e-16);

  // Define the density to the left of the contact discontinuity rhoml.
 
  rhoml = pow(rhol * (pm / pl),(1.e0 / GAMMA));

  // Define the postshock fluid velocity vm.

  vm = 2.e0 * cl / (GAMMA - 1.e0) * (1.e0 - pow((pm / pl),
               ( (GAMMA - 1.e0) / (2.e0 * GAMMA) )));

  // Define the postshock density rhomr.

  rhomr = rhor *  ( (pm + mu2 * pr) / (pr + mu2 * pm) );

  // Define the shock velocity vs.

  vs = vm / (1.e0 - rhor / rhomr);

  // Define the velocity of the rarefraction tail, vt.

  vt = cl - vm / (1.e0 - mu2);

  // Output tables of density, velocity, and pressure at time t.

  //  for(i=0;i<numnodes;i++)
  //    {
  //x = - xmax +  2.e0 * xmax * i / numnodes;
 
      if (x <= (-cl*t) )
	  density = rhol;
      else if (x <= (-vt*t) )
	  density = pow(rhol * (-mu2 * (x / (cl * t) ) + (1 - mu2) ),
			  (2.e0 / (GAMMA - 1.e0))) ;
      else if (x <= (vm*t) )
	  density = rhoml;
      else if (x <= (vs*t) )
	density = rhomr;
      else
	density = rhor;
      
      if (x <= (-cl*t) )
	pressure = pl;
      else if (x <= (-vt*t) )
	pressure = pow(pl * (-mu2 * (x / (cl * t) ) + (1 - mu2) ),
			 (2.e0 * GAMMA / (GAMMA - 1.e0)));
      else if (x <= vs * t)
	pressure = pm;
      else            
	pressure = pr;
      
      if (x <= (-cl*t) )
	velocity = 0.0;
      else if (x <= (-vt*t) )
	velocity = (1 - mu2) * (x / t + cl);
      else if (x <= (vs*t) )
	velocity = vm;
      else 
	velocity = 0.0;

      out_soln[0] = density;
      out_soln[1] = density*velocity;
      out_soln[2] = 0.0;		/* koomie need to fix */

      //    }

      //  fclose(fp);

}

double func(double pm)
{

///////////////////////////////////////////////////////////////////////
//
//  func is obtained from an identity matching the post-shocked      
//  pressure to the post-rarefraction pressure (true since there is
//  no pressure jump across the contact discontinuity). We use it to
//  numerically solve for pm given the left and right initial states.
//
///////////////////////////////////////////////////////////////////////
 
  double myval;
 
  myval = -2*cl*(1 - pow((pm/pl),((-1 + GAMMA)/(2*GAMMA))))/
    (cr*(-1 + GAMMA)) +
    (-1 + pm/pr)*sqrt((1 - mu2)/(GAMMA*(mu2 + pm/pr)));
  
    return(myval);
}

//////////////////////////////////////////////////////////////////////////
//
// rtbis is borrowed from Numerical Recipes. It is a bisection algorithm,
// which we use to solve for pm using a call to func.
//
// Note that the arguments to rtbis have been altered and the value of
// JMAX increased. Otherwise, it is identical to the NR version.
//
//////////////////////////////////////////////////////////////////////////

double rtbis(double x1,double x2,double xacc)
{
  int JMAX=100;
  int j;
  double dx,f,fmid,xmid;
  double myval;

  fmid=func(x2);

  f=func(x1);
  if(f*fmid >= 0.)
    {
      printf("root must be bracketed in rtbis\n");
      exit(1);
    }
     
  if(f < 0.)
    {
      myval=x1;
      dx=x2-x1;
    }
  else
    {
      myval=x2;
      dx=x1-x2;
    }
  
  for(j=0;j<JMAX;j++)
    {
      dx=dx*5.e-1;
      xmid=myval+dx;
      fmid=func(xmid);
      if(fmid <= 0.) myval=xmid;
      if(fabs(dx) < xacc || fmid == 0.) 
	return(myval);
    }
    
  printf("** Error: Too many bisection in rtbis\n");

}
