#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then 

typedef enum { false, true} bool;

/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long fact (int n) 
{ if (n==0) return 1 ;
  else return n * fact(n-1) ; 
}

// itou avec un arg out => passage par adresse

void bisfact(int n, long * r) 
{ if (n==0) 
         *r=1.0 ;
  else { bisfact(n-1,r) ;
         *r = *r *n ;
       }
}

long fact2 (int n)
{ long r ;
  bisfact(n,&r) ;
  return r ;
}

/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

     // Il est proposé de faire 3 versions pour observer des phénomènes de précision.
     // C'est le même code, seul le type change.

/*************************************************/

float Efloat () { 
    long double epsilon = 1e-5;
    float e = 0.0;
    int n = 0;
    long n_fact = 1;
    float u = 1/n_fact;
    e += u;
    while (u>epsilon) {
        n = n+1;
        n_fact = n * n_fact;
        u = 1./n_fact;
        e += u;
    }
    return e;
}

/*************************************************/

double Edouble () { 
    long double epsilon = 1e-5;
    double e = 0.0;
    int n = 0;
    long n_fact = 1;
    double u = 1/n_fact;
    e += u;
    while (u>epsilon) {
        n = n+1;
        n_fact = n * n_fact;
        u = 1./n_fact;
        e += u;
    }
    return e;
}
  
/*************************************************/

long double Elongdouble () { 
    long double epsilon = 1e-5;
    long double e = 0.0;
    int n = 0;
    long n_fact = 1;
    long double u = 1/n_fact;
    e += u;
    while (u>epsilon) {
        n = n+1;
        n_fact = n * n_fact;
        u = 1./n_fact;
        e += u;
    }
    return e;
}

/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

void afficheYfloat (int n) {
    float y = Efloat() - 1;
    printf("y_0 = %f\n", y);
    for (int i = 1; i < n; i+=1) {
        y = i * y - 1;
        printf("y_%i = %f\n", i, y);
    }
}

/*************************************************/

void afficheYdouble (int n) {
    double y = Edouble() - 1;
    printf("y_0 = %lf\n", y);
    for (int i = 1; i < n; i+=1) {
        y = i * y - 1;
        printf("y_%i = %lf\n", i, y);
    }
}

/*************************************************/

void afficheYlongdouble (int n) {
    long double y = Elongdouble() - 1;
    printf("y_0 = %Lf\n", y);
    for (int i = 1; i < n; i+=1) {
        y = i * y - 1;
        printf("y_%i = %Lf\n", i, y);
    }
}

/*************************************************/
/*                                               */
/*            Puissance                          */
/*                                               */
/*************************************************/


double power1 (double x, long n) { 
    if (n==0 && x!=0.0) { return 1.0;}
    if (n>0) {return power1(x,n-1)*x;}
    if (n<0 && x!=0) {return 1/power1(x,-n);}
    printf("Erreur dans power1 : calcul de %lf^%li irréalisable",x,n);
    return 0;
}

/*************************************************/

double power2a (double x, long n) { 
    double r = 1.0;
    bool neg = false;
    if (n==0 && x!=0.0) { return r;} 
    if (n<0) {neg = true; n = -n;}
    for (int i = 1; i < n+1; i+=1) {
        r *= x;
    }
    if (neg && x!=0) {return 1/r;}
    else if (!neg) {return r;}
    printf("Erreur dans power2a : calcul de %lf^%li irréalisable",x,n);
    return 0;
}

/*************************************************/

double power2b (double x, long n) { 
    double r = 1.0;
    while(n>0) {
        r = r*x;
        n -= 1;
    }
    return r;
}

/*************************************************/

void power3bis(double x, long n, double *r) {
    if (n==0) return;
    *r = *r *x;
    power3bis(x,n-1,r);
}

double power3 (double x, long n) { 
    double r = 1.0;
    power3bis(x,n,&r);
    return r;
}

/*************************************************/

double power4bis(double x, long n, double r) {
    if (n==0) return r;
    return power4bis(x,n-1,r*x);
}

double power4 (double x, long n) { return power4bis(x,n,1.);}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : rame : 8 en 1/2s, 9 en qqs s, 10 en 1m

double power5 (double x, long n)
{
    if (n == 0)
         return 1 ;
    else if (n % 2 == 0)
              return (power5(x,n/2)*power5(x,n/2)   ) ;
         else return (power5(x,n/2)*power5(x,n/2) *x) ;   
}

/*************************************************/

double power6 (double x, long n) { 
    if (n==0) return 1;
    double y = power6(x,n/2);
    if (n%2 == 0) return y*y;
    return y*y*x;
}

/*************************************************/

double power7 (double x, long n) {
    if (n==0) return 1;
    if (n%2 == 0) return power7(x*x,n/2);
    return power7(x*x,n/2)*x;
}

/*************************************************/

double power8bis(double x,long n,double r) {
    if (n==0) return r;
    if (n%2 ==0) return power8bis(x*x,n/2,r);
    return power8bis(x*x,n/2,r*x);
}

double power8 (double x, long n) { return power8bis(x,n,1.0); }

/*************************************************/

void power9bis(double x, long n, double *r) {
    if (n==0) return;
    if (n%2==1) *r = *r * x;
    power9bis(x*x,n/2,r);
}

double power9 (double x, long n) { 
    double r = 1.0;
    power9bis(x,n,&r);
    return r;
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : calcul immédiat

double power10 (double x, long n)
{
    double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

double power (double x, long n, int i)
{ switch (i)  
   {
   case 1 : return power1(x,n) ; break ;
   case 2 : return power2a(x,n) ; break ;  // 2 pour 2a
   case 0 : return power2b(x,n) ; break ; // 0 pour 2b
   case 3 : return power3(x,n) ; break ;
   case 4 : return power4(x,n) ; break ;
   case 5 : return power5(x,n) ; break ;
   case 6 : return power6(x,n) ; break ;
   case 7 : return power7(x,n) ; break ;
   case 8 : return power8(x,n) ; break ;
   case 9 : return power9(x,n) ; break ;
  case 10 : return power10(x,n) ; break ;
     default : return 0 ; 
   }
}

   // remarque : les break sont ici inutiles car les returns font déjà des break

/*************************************************/

    // memes versions que la 10 mais avec des long double, puis des floats
    // but du jeu : observer des variations de precision

   // observation :
   //   imprécision à partir de k~5 (float), k~12 (double), k~14 (long double)
   //   rend 1 à partir de k=8 (float), k=16 (double)
   //   rend 1 non observé sur les long double, maxint atteint avant

long double power11 (long double x, long n)
{
    long double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

float power12 (float x, long n)
{
    float r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}


/*************************************************/
/*                                               */
/*             Ackermann                         */
/*                                               */
/*************************************************/


int A1(int m, int n) { 
    if (m==0) return n+1;
    if (n==0) return A1(m-1,1);
    return A1(m-1,A1(m,n-1));
}

int Ackermann1 (int m) { return A1(m,0); }

/*************************************************/

int A2(int m, int n) { 
    if (m==0) return n+1;
    int r = 1;
    for (int i = 1; i <=n+1; i+=1) {
        r = A2(m-1,r);
    }
    return r;
}

int Ackermann2 (int m) { return A2(m,0);}

/*************************************************/

int A3(int m, int n) { 
    while (m >= 0) {
        if (m == 0) {
            return n + 1;
        } else if (m > 0 && n == 0) {
            m -= 1;
            n = 1;
        } else {
            n = A3(m, n-1);
            m -= 1;
        }
    }
}

int Ackermann3 (int m) { return A3(m,0); }

/*************************************************/

int Ackermann4 (int m) { return 0 ; }

/*************************************************/

int Ackermann5 (int m) { return 0 ; }

/*************************************************/
  
int Ackermann (int m, int i)
{ switch (i)  
   {
   case 1 : return Ackermann1 (m) ; // break ;
   case 2 : return Ackermann2 (m) ; // break ;
   case 3 : return Ackermann3 (m) ; // break ;
   case 4 : return Ackermann4 (m) ; // break ;
   case 5 : return Ackermann5 (m) ; // break ;
   default : return 0 ; 
   }
}

/*************************************************/
/*                                               */
/*            Suite X                            */
/*                                               */
/*************************************************/

// LogEntier version itérative

int ln2ite(int n) {
    int cpt = 0;
    while (n>1) {
        cpt++;
        n=n/2;
    }
    return cpt;
}

// LogEntier version récursive

int ln2rec(int n) {
    if (n==1) return 0;
    return 1 + ln2rec(n/2);
}

// Version itérative

int suiteXv1(int n)  {
    int x = 2;
    for (int i = 1; i < n; i++) {
        x = x + ln2ite(x);
    }
    return x;
}

// Version récursive

int suiteXv2(int n)  {
    if (n==0) return 2;
    int x = suiteXv2(n-1);
    return x+ln2rec(x);
}

// Version récursive terminale avec sous-fonction

int suiteXv3f(int n, int m) {
    if (n==0) return m;
    return suiteXv3f(n-1,m+ln2rec(m));
}

int suiteXv3(int n)  {
    return suiteXv3f(n,2);
}

// Version récursive terminale avec sous-procédure

void suiteXv4p(int n, int *r) {
    if (n==0) return;
    *r = *r + ln2rec(*r);
    suiteXv4p(n-1,r);
}

int suiteXv4(int n)  {
    int r = 2;
    suiteXv4p(n,&r);
    return r;
}

/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{

       double x ;
       long double y ;
       float z ;
       
       int cptx ;
  
       long nx ;
       
       int i,j ; 
       
/******************************************************************************/
 
    // mettre "if true" vs "if false" selon que vous voulez les tests ou non
  
/****************  petit test sur le fonctionnement du switch  ************/

if (false) {

 switch (2)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }


 switch (4)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }

   printf("\n") ; 

}
      
      
/************************  taille des nombres  *************************/
      
if (false) {     
       
       printf("ce programme suppose que les long font 8 octets\n") ;
       printf("S'ils n'en font que 4, il faudra utiliser long long\n") ;

       printf("short : %d octets\n", (int) sizeof(short));
       printf("int : %d octets\n", (int) sizeof(int));
       printf("long : %d octets\n", (int) sizeof(long));
       printf("long long : %d octets\n", (int) sizeof(long long));
       printf("float : %d octets\n", (int) sizeof(float));
       printf("double : %d octets\n", (int) sizeof(double));
       printf("long double : %d octets\n", (int) sizeof(long double));
       printf("\n") ;
 
       x = 1.0 ;
       cptx = 0 ;
       while ( (1.0 + x) - 1.0 != 0 )
          { x = x/10 ; cptx ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cptx) ; 
       printf("et 1+1/10^%d vaut en fait 1+%lf\n", cptx-1, (1.0 + 10*x) - 1.0) ;
        
       printf("ce programme suppose que les doubles font au moins 8 octets\n") ;
       printf("et que ((double) 1+1/10^-15) n'est pas 1 \n") ;       
       printf("Si ce n'est pas le cas, utiliser des long double \n") ;
       
       printf("\n") ;      
}

/************************  factorielle  *************************/

if (false) {

     printf("%ld \n",fact(5)) ;
     printf("%ld \n",fact2(5)) ;
     printf("\n") ;
}


/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

if (false) {  
       

        printf(" e1 = %.20f \n", Efloat()) ;
        printf(" e3 = %.30lf \n", Edouble()) ; 
        printf(" e3 = %.40Lf \n", Elongdouble()) ; 
        
}

if (false) {  
            afficheYfloat(30) ;
            afficheYdouble(30) ;
            afficheYlongdouble(30) ;
}

// On constate qu'à partir d'un certain rang (toujours autour de n=10 environ) la suite s'arrête de tendre vers 0 et diverge vers -inf
// Surement du à un manque de précision de la représentation des nombres décimaux.
        
/******************    power     *******************************/

if (false) {  

        //   test simplet, vérifie le B.A. BA, test de 2^10 pour toutes les versions
        
        for(i=0 ; i<=10 ; i++)
        printf("Power %d dit que power(2,10) vaut %.0lf \n", i, power(2,10,i) ) ;
        
        printf("\n") ;
      
}

        
if (false) {  

        i=8 ;  // numéro de la version que l'on teste

        // test de la résistance de power version i, calcul de (1+1/N)^N
        // pour des N puissances de 10 de plus en plus grosses
     
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=15 ; j++)
        {
        printf("power %d ((1+10^-%2d)^(10^%2d)) rend %.12lf\n", i, j, j, power(1+x,nx,i)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;
       
}
     
if (false) {

        // tests sur la précision que l'on obtient suivant que
        // l'on utilise float, double, long double

        printf("VERSION 12 avec float \n") ;
        z = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12f\n", j, j, power12(1+z,nx)) ;
        z = z/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 10 avec double \n") ;
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12lf\n", j, j, power10(1+x,nx)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 11 avec long double \n") ;
        y = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12LF\n", j, j, power11(1+y,nx)) ;
        y = y/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;



}

// La suite (1+1/N)^N semble tendre vers exp(1)

// Certaines versions sont très rapides (calcul quasi instantané, ex : 8) ou assez lentes (ex : 5)

// Le compilateur semble effectuer l'optimisation du récursif terminal

/******************    Ackermann    *******************************/
                
if (false) { 
 
        for(i=1 ; i<=3 ; i++)  // numéro de version
        
        for(j=0 ; j<=6 ; j++)  // test de A(j,0) pour j de 0 à 5
        
        printf("Ack%d(%d) = %d \n", i, j, Ackermann(j,i)) ;
}

// Les trois versions ont le même comportement : elles tournent sans donner de résultats

/***********************************************************************/

/************************  suite X  *************************/

if (false) {

    long int x1 = suiteXv1(100);
    long int x2 = suiteXv2(100);
    long int x3 = suiteXv3(100);
    long int x4 = suiteXv4(100);

    printf("Première méthode du calcul de X_100 : %li\n",x1);
    printf("Deuxième méthode du calcul de X_100 : %li\n",x1);
    printf("Troisième méthode du calcul de X_100 : %li\n",x1);
    printf("Quatrième méthode du calcul de X_100 : %li\n",x1);


}
    return 0;
}





