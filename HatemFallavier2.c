
#include <stdio.h>
#include <stdlib.h>

/***************************************************************/
/* NOM       Prenom @email                                     */
/* FALLAVIER Jessy  jessy.fallavier@universite-paris-saclay.fr */
/* HATEM     Sandra sandra.hatem@universite-paris-saclay.fr    */
/***************************************************************/

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

typedef enum
{
  FALSE,
  TRUE
} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
  int nombre;
  struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste *L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste *l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec(Liste l);
int longueur_iter(Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD(Liste *L);
void VireDernier_rec(Liste *L);
void VireDernier_iter(Liste *L);

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

void initVide(Liste *L)
{
  *L = NULL;
}

bool estVide(Liste l)
{
  return l == NULL;
}

int premier(Liste l)
{
  return l->nombre;
}

Liste ajoute(int x, Liste l)
{
  Liste tmp = (Liste)malloc(sizeof(Bloc));
  tmp->nombre = x;
  tmp->suivant = l;
  return tmp;
}

void empile(int x, Liste *L)
{
  *L = ajoute(x, *L);
}

Liste suite(Liste l)
{
  return l->suivant;
}

void depile(Liste *L)
{
  Liste tmp = *L;
  *L = suite(*L);
  free(tmp);
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
  if (estVide(l))
    printf("\n");
  else
  {
    printf("%d ", premier(l));
    affiche_rec(suite(l));
  }
}

void affiche_iter(Liste l)
{
  Liste L2 = l;
  while (NOT estVide(L2))
  {
    printf("%d ", premier(L2));
    L2 = suite(L2);
  }
  printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec(Liste l)
{
  if (l == NULL)
    return 0;
  else
    return (1 + longueur_rec(l->suivant));
}

int longueur_iter(Liste l)
{
  Liste P = l;
  int cpt = 0;
  while (P ISNOT NULL)
  {
    P = P->suivant;
    cpt++;
  }
  return cpt;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD(Liste *L)
// *L non NULL ie liste non vide
{
  if (((**L).suivant) == NULL)
    depile(L); // moralement : depile(& (*L));
  else
    VD(&((**L).suivant));
}

void VireDernier_rec(Liste *L)
{
  if ((*L)ISNOT NULL)
    VD(L); // moralement : VD(& (*L));
}

void VireDernier_iter(Liste *L)
{
  if ((*L)ISNOT NULL)
  {
    while (((**L).suivant)ISNOT NULL)
      L = &((**L).suivant);
    free(*L);
    *L = NULL;
  }
}

/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
  if (NOT(estVide(*L)))
  {
    depile(L);
    VideListe(L);
  }
}

/*************************************************/
/*                                               */
/*           2.1                                 */
/*                                               */
/*************************************************/

/*****UnPlusDeuxEgalTrois*************************/
bool UnPlusDeuxEgalTrois(Liste L) {
  int somme = 0;

  // On ne regarde que les 3 premières valeurs
  for (int i = 0; i < 3; i++) {
    int val;
    // C'est vide, on consière que c'est 0
    if (estVide(L)) then
      val = 0;
    else {
      // On récupère la valeur du premier élément et on passe à la suite
      val = premier(L);
      L = suite(L);
    }

    if (i ISNOT 2) then// Soit on ajoute à la somme des 1e+2e
      somme += val;
    else     // Soit on vérifie que 1e+2e = 3e
      return (somme == val);
  }

  return FALSE; // Pas de valeurs
}

void testUnPlusDeuxEgalTrois() {
  Liste LProf1;
  initVide(&LProf1);
  empile(29, &LProf1);
  empile(4, &LProf1);
  empile(8, &LProf1);
  empile(5, &LProf1);
  empile(3, &LProf1);

  Liste LProf2;
  initVide(&LProf2);
  empile(-2, &LProf2);
  empile(2, &LProf2);

  Liste LProf3;
  initVide(&LProf3);

  Liste LProf4;
  initVide(&LProf4);
  empile(1, &LProf4);
  empile(7, &LProf4);
  empile(3, &LProf4);
  empile(2, &LProf4);

  Liste LProf5;
  initVide(&LProf5);
  empile(2, &LProf5);
  empile(2, &LProf5);

  // UnPlusDeuxEgalTrois
  printf("\nUnPlusDeuxEgalTrois :\n");
  
  printf("Liste : " ); affiche_rec(LProf1);
  printf("Res V : %d\n", UnPlusDeuxEgalTrois(LProf1));

  printf("Liste : " ); affiche_rec(LProf2);
  printf("Res V : %d\n", UnPlusDeuxEgalTrois(LProf2));

  printf("Liste : " ); affiche_rec(LProf3);
  printf("Res V : %d\n", UnPlusDeuxEgalTrois(LProf3));

  printf("Liste : " ); affiche_rec(LProf4);
  printf("Res X : %d\n", UnPlusDeuxEgalTrois(LProf4));

  printf("Liste : " ); affiche_rec(LProf5);
  printf("Res X : %d\n", UnPlusDeuxEgalTrois(LProf5));

  VideListe(&LProf1);
  VideListe(&LProf2);
  VideListe(&LProf3);
  VideListe(&LProf4);
  VideListe(&LProf5);
}

/*****Croissante**********************************/
bool Croissante(Liste L) {
  while (NOT estVide(L) AND NOT estVide(suite(L))) { // Tant qu'il en reste 2 à comparer
    if (premier(suite(L)) <= premier(L)) then // Si la suite est plus petite on retourne faux
      return FALSE;

    L = suite(L); // on passe à la suite
  }

  return TRUE;
}

void testCroissante() {
  Liste LVide;
  initVide(&LVide);

  Liste L1;
  initVide(&L1);
  empile(4, &L1);

  Liste L3;
  initVide(&L3);
  empile(5, &L3);
  empile(3, &L3);
  empile(2, &L3);

  Liste L5;
  initVide(&L5);
  empile(5, &L5);
  empile(6, &L5);
  empile(7, &L5);
  empile(10, &L5);
  empile(9, &L5);

  // UnPlusDeuxEgalTrois
  printf("\nCroissante :\n");
  
  printf("Liste : " ); affiche_rec(LVide);
  printf("Res V : %d\n", Croissante(LVide));

  printf("Liste : " ); affiche_rec(L1);
  printf("Res V : %d\n", Croissante(L1));

  printf("Liste : " ); affiche_rec(L3);
  printf("Res V : %d\n", Croissante(L3));

  printf("Liste : " ); affiche_rec(L5);
  printf("Res X : %d\n", Croissante(L5));

  VideListe(&LVide);
  VideListe(&L1);
  VideListe(&L3);
  VideListe(&L5);
}

/*****NombreMemePosition**************************/
// Une version r ́ecursive sans sous-fonctionnalit ́e (et non terminale)
int NombreMemePosition1(Liste L1, Liste L2) {
  if (NOT estVide(L1) AND NOT estVide(L2)) then // Si la liste n'est pas vide
    return (premier(L1) == premier(L2)) + NombreMemePosition1(suite(L1), suite(L2)); // On passe à la suite et on ajoute 1 si les deux nombres sont égaux
  else
    return 0;
}

// Une version itérative
int NombreMemePosition2(Liste L1, Liste L2) {
  int meme = 0;

  while (NOT estVide(L1) AND NOT estVide(L2)) { // Tant que les listes ne sont pas vides
    meme += (premier(L1) == premier(L2)); // On ajoute si les nombres sont égaux
    L1 = suite(L1); // On passe à la suite
    L2 = suite(L2);
  }

  return meme;
}

// Une version qui utilise une sous-fonction r ́ecursive terminale.
int NombreMemePosition3Aux(Liste L1, Liste L2, int meme) {
  if (NOT estVide(L1) AND NOT estVide(L2)) then
    return NombreMemePosition3Aux(suite(L1), suite(L2), meme + (premier(L1) == premier(L2)));
  else
    return meme;
}

int NombreMemePosition3(Liste L1, Liste L2) {
  return NombreMemePosition3Aux(L1, L2, 0);
}

// Une version qui utilise une sous-proc ́edure r ́ecursive terminale
void NombreMemePosition4Aux(Liste L1, Liste L2, int *meme) {
  if (NOT estVide(L1) AND NOT estVide(L2)) {
    *meme += (premier(L1) == premier(L2));
    NombreMemePosition4Aux(suite(L1), suite(L2), meme);
  }
}

int NombreMemePosition4(Liste L1, Liste L2) {
  int meme = 0;
  NombreMemePosition4Aux(L1, L2, &meme);
  return meme;
}

void testNombreMemePosition() {
  Liste LProfA;
  initVide(&LProfA);
  empile(2, &LProfA);
  empile(9, &LProfA);
  empile(2, &LProfA);
  empile(4, &LProfA);
  empile(3, &LProfA);
  empile(0, &LProfA);
  empile(9, &LProfA);
  empile(6, &LProfA);
  empile(3, &LProfA);

  Liste LProfB;
  initVide(&LProfB);
  empile(5, &LProfB);
  empile(2, &LProfB);
  empile(2, &LProfB);
  empile(2, &LProfB);
  empile(2, &LProfB);
  empile(2, &LProfB);
  empile(2, &LProfB);
  empile(0, &LProfB);
  empile(6, &LProfB);
  empile(9, &LProfB);
  empile(3, &LProfB);
  
  printf("\nNombreMemePosition :\n");
  printf("\nV1 :\n");
  printf("Liste 1 : " ); affiche_rec(LProfA);
  printf("Liste 2 : " ); affiche_rec(LProfB);
  printf("Res 4 : %d\n", NombreMemePosition1(LProfA, LProfB));

  printf("\nV2 :\n");
  printf("Liste 1 : " ); affiche_rec(LProfA);
  printf("Liste 2 : " ); affiche_rec(LProfB);
  printf("Res 4 : %d\n", NombreMemePosition2(LProfA, LProfB));

  printf("\nV3 :\n");
  printf("Liste 1 : " ); affiche_rec(LProfA);
  printf("Liste 2 : " ); affiche_rec(LProfB);
  printf("Res 4 : %d\n", NombreMemePosition3(LProfA, LProfB));

  printf("\nV4 :\n");
  printf("Liste 1 : " ); affiche_rec(LProfA);
  printf("Liste 2 : " ); affiche_rec(LProfB);
  printf("Res 4 : %d\n", NombreMemePosition4(LProfA, LProfB));

  VideListe(&LProfA);
  VideListe(&LProfB);
}

/*****FonctVireDernier***************************/
// version r ́ecursive simple (non terminale
Liste FonctVireDernier1(Liste L) {
  Liste res;

  if (NOT estVide(L) AND NOT estVide(suite(L))) {
    res = FonctVireDernier1(suite(L));
    empile(premier(L), &res); // On reconsitue la liste

  } else
    initVide(&res); // C'est le dernier élément, on ne renvoit qu'une liste vide
    
  return res;
}

//  (plus technique) une version itérative
Liste FonctVireDernier2(Liste L) {
    Liste res;
    initVide(&res);

    Liste *courant; // Représente l'endroit où on va ajouter dans notre liste res de retour
    courant = &res;

    while (NOT estVide(L) AND NOT estVide(suite(L))) {
      empile(premier(L), courant); // On ajoute au bon endroit

      courant = &((*courant)->suivant); // On décale l'endroit
      L = suite(L); // On passe à la suite
    }

    return res;
}

void testFonctVireDernier() {
  Liste LProf;
  initVide(&LProf);
  empile(1, &LProf);
  empile(0, &LProf);
  empile(8, &LProf);
  empile(0, &LProf);
  empile(5, &LProf);
  empile(0, &LProf);
  empile(4, &LProf);
  
  printf("\nFonctVireDernier :\n");
  printf("V1 :\n");
  printf("Liste : " ); affiche_rec(LProf);
  Liste resV1 = FonctVireDernier1(LProf);
  printf("Res   : "); affiche_rec(resV1);

  printf("\nV2 :\n");
  printf("Liste : " ); affiche_rec(LProf);
  Liste resV2 = FonctVireDernier2(LProf);
  printf("Res   : "); affiche_rec(resV2);

  VideListe(&LProf);
  VideListe(&resV1);
  VideListe(&resV2);
}

/*****AjouteDevantPremierZero*********************/
void AjouteDevantPremierZero(Liste *L, int x) {
  if (NOT estVide(*L) AND premier(*L) ISNOT 0) then
    // On est ni à la fin ni sur un 0, on passe à la suite
    AjouteDevantPremierZero(&((*L)->suivant), x);
  else
    // Soit on est arrivé à la fin de la liste ou est tombé sur le 1er 0, on empile
    empile(x, L); 
}

void testAjouteDevantPremierZero() {
  Liste LVide;
  initVide(&LVide);

  Liste L1;
  initVide(&L1);
  empile(0, &L1);

  Liste L3;
  initVide(&L3);
  empile(5, &L3);
  empile(0, &L3);
  empile(2, &L3);

  Liste L4;
  initVide(&L4);
  empile(5, &L4);
  empile(0, &L4);
  empile(2, &L4);
  empile(0, &L4);


  Liste L5;
  initVide(&L5);
  empile(5, &L5);
  empile(6, &L5);
  empile(7, &L5);
  empile(10, &L5);
  empile(9, &L5);

  Liste LProf;
  initVide(&LProf);
  empile(1, &LProf);
  empile(0, &LProf);
  empile(8, &LProf);
  empile(0, &LProf);
  empile(5, &LProf);
  empile(0, &LProf);
  empile(4, &LProf);

  
  printf("\nAjouteDevantPremierZero :\n");
  printf("Liste : " ); affiche_rec(LVide);
  AjouteDevantPremierZero(&LVide, 42);
  printf("Res   : "); affiche_rec(LVide);

  printf("Liste : " ); affiche_rec(L1);
  AjouteDevantPremierZero(&L1, 42);
  printf("Res   : "); affiche_rec(L1);

  printf("Liste : " ); affiche_rec(L3);
  AjouteDevantPremierZero(&L3, 42);
  printf("Res   : "); affiche_rec(L3);
  
  printf("Liste : " ); affiche_rec(L4);
  AjouteDevantPremierZero(&L4, 42);
  printf("Res   : "); affiche_rec(L4);

  printf("Liste : " ); affiche_rec(L5);
  AjouteDevantPremierZero(&L5, 42);
  printf("Res   : "); affiche_rec(L5);

  printf("Liste : " ); affiche_rec(LProf);
  AjouteDevantPremierZero(&LProf, 42);
  printf("Res   : "); affiche_rec(LProf);

  VideListe(&LVide);
  VideListe(&L1);
  VideListe(&L3);
  VideListe(&L4);
  VideListe(&L5);
  VideListe(&LProf);
}

/*****AjouteDevantDernierZero*********************/
// version r ecursive avec argument inout
void AjouteDevantDernierZero1Aux(Liste *L, int x, int *zerosApres) {
  // Dans la liste
  if (NOT estVide(*L)) {
    if (premier(*L) == 0) {
      // On ajoute 1 au compteur et on conserve cette valeur pour la comparer ensuite
      *zerosApres += 1;
      int zerosAvant = *zerosApres;
      
      AjouteDevantDernierZero1Aux(&((*L)->suivant), x, zerosApres);

      //Le dernier 0 est ici et on a pas ajouté ensuite
      if (zerosAvant == *zerosApres) then
        empile(x, L);

    } else
      AjouteDevantDernierZero1Aux(&((*L)->suivant), x, zerosApres);
  // Fin de la liste
  } else
      if (*zerosApres == 0) then
        empile(x, L);
}

void AjouteDevantDernierZero1(Liste *L, int x) {
  int zerosApres = 0;
  AjouteDevantDernierZero1Aux(L, x, &zerosApres);
}

// (plus d ́elicat) une version r ́ecursive terminale
Liste AjouteDevantDernierZero2Aux(Liste *L, int x, Liste *courant) {
  if (NOT estVide(*L)) {
    if (premier(*L) == 0) then
      courant = L; // Si on est à zéro on va ajouter là

    AjouteDevantDernierZero2Aux(&((*L)->suivant), x, courant);
  } else if (NOT estVide(*courant)) // Si on a trouvé un 0 on ajouter au dernier
    empile(x, courant);
    else // Si on n'en a pas trouvé on ajouter à la fin
      empile(x, L);
}

void AjouteDevantDernierZero2(Liste *L, int x) {
  Liste courant;
  initVide(&courant);
  AjouteDevantDernierZero2Aux(L, x, &courant);
}

// version itérative.
void AjouteDevantDernierZero3(Liste *L, int x) {
  Liste *courant;
  courant = NULL;

  while(NOT estVide(*L)) {
    // On est sur un zéro
    if (premier(*L) == 0) then
      courant = L;
    
    L = &((*L)->suivant);
  }

  // On a trouvé un zéro, on le met à la dernière occurence
  if (courant ISNOT NULL) then
    empile(x, courant);
  // On n'a pas trouvé de zéro, on le met à la fin
  else
    empile(x, L);
}

void testAjouteDevantDernierZero() {
  Liste LProf;
  initVide(&LProf);
  empile(1, &LProf);
  empile(0, &LProf);
  empile(8, &LProf);
  empile(0, &LProf);
  empile(5, &LProf);
  empile(0, &LProf);
  empile(4, &LProf);

  Liste LFin;
  initVide(&LFin);
  empile(1, &LFin);
  empile(2, &LFin);
  empile(3, &LFin);
  empile(4, &LFin);

  Liste LVide;
  
  printf("\nAjouteDevantDernierZero :\n");
  printf("V1 :\n");
  initVide(&LVide);
  printf("Liste : " ); affiche_rec(LProf);
  AjouteDevantDernierZero1(&LProf, 7);
  printf("Res   : "); affiche_rec(LProf);
  printf("Liste : " ); affiche_rec(LVide);
  AjouteDevantDernierZero1(&LVide, 7);
  printf("Res   : "); affiche_rec(LVide);
  printf("Liste : " ); affiche_rec(LFin);
  AjouteDevantDernierZero1(&LFin, 7);
  printf("Res   : "); affiche_rec(LFin);

  printf("V2 :\n");
  initVide(&LVide);
  printf("Liste : " ); affiche_rec(LProf);
  AjouteDevantDernierZero2(&LProf, 7);
  printf("Res   : "); affiche_rec(LProf);
  printf("Liste : " ); affiche_rec(LVide);
  AjouteDevantDernierZero2(&LVide, 7);
  printf("Res   : "); affiche_rec(LVide);
  printf("Liste : " ); affiche_rec(LFin);
  AjouteDevantDernierZero2(&LFin, 7);
  printf("Res   : "); affiche_rec(LFin);

  printf("V3 :\n");
  initVide(&LVide);
  printf("Liste : " ); affiche_rec(LProf);
  AjouteDevantDernierZero3(&LProf, 7);
  printf("Res   : "); affiche_rec(LProf);
  printf("Liste : " ); affiche_rec(LVide);
  AjouteDevantDernierZero3(&LVide, 7);
  printf("Res   : "); affiche_rec(LVide);
  printf("Liste : " ); affiche_rec(LFin);
  AjouteDevantDernierZero3(&LFin, 7);
  printf("Res   : "); affiche_rec(LFin);

  VideListe(&LProf);
  VideListe(&LFin);
}

/*****Tic*****************************************/
void Tic(Liste *L) {
  // Si la liste est non vide et qu'on n'est pas sur un 0, ajouter un 0 et passer deux fois
  if (NOT estVide(*L) AND premier(*L) ISNOT 0) {
    empile(0, L);
    Tic(&((*L)->suivant->suivant));
  }
  // Si on a touché un zéro ou qu'on est à la fin de la liste
  else
    // Tant que la liste n'est pas vide et qu'on est sur un zéro, dépiler les 0
    while (NOT estVide(*L) AND premier(*L) == 0)
      depile(L);
}

void testTic() {
  Liste LVide;
  initVide(&LVide);

  Liste L2;
  initVide(&L2);
  empile(3, &L2);
  empile(4, &L2);

  Liste L4;
  initVide(&L4);
  empile(5, &L4);
  empile(0, &L4);
  empile(0, &L4);
  empile(2, &L4);

  Liste L5;
  initVide(&L5);
  empile(0, &L5);
  empile(3, &L5);
  empile(0, &L5);
  empile(5, &L5);
  empile(2, &L5);

  Liste LProf;
  initVide(&LProf);
  empile(1, &LProf);
  empile(2, &LProf);
  empile(0, &LProf);
  empile(0, &LProf);
  empile(9, &LProf);
  empile(8, &LProf);
  empile(0, &LProf);
  empile(0, &LProf);
  empile(0, &LProf);
  empile(2, &LProf);
  empile(7, &LProf);
  empile(3, &LProf);

  
  printf("\nTic :\n");
  printf("Liste : " ); affiche_rec(LVide);
  Tic(&LVide);
  printf("Res   : "); affiche_rec(LVide);

  printf("Liste : " ); affiche_rec(L2);
  Tic(&L2);
  printf("Res   : "); affiche_rec(L2);
  
  printf("Liste : " ); affiche_rec(L4);
  Tic(&L4);
  printf("Res   : "); affiche_rec(L4);

  printf("Liste : " ); affiche_rec(L5);
  Tic(&L5);
  printf("Res   : "); affiche_rec(L5);

  printf("Liste : " ); affiche_rec(LProf);
  Tic(&LProf);
  printf("Res   : "); affiche_rec(LProf);

  VideListe(&LVide);
  VideListe(&L2);
  VideListe(&L4);
  VideListe(&L5);
  VideListe(&LProf);
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup(Liste l)
{
  printf("Double Affichage \n");
  affiche_rec(l);
  affiche_iter(l);

  printf("Longueur en double %d %d \n\n",
         longueur_rec(l),
         longueur_iter(l));
}

void testProf() {
  Liste l;

  initVide(&l);
  poup(l);

  empile(4, &l);
  poup(l);

  empile(5, &l);
  empile(6, &l);
  empile(7, &l);
  empile(8, &l);
  empile(9, &l);
  poup(l);

  VireDernier_rec(&l);
  VireDernier_iter(&l);
  depile(&l);
  poup(l);

  VideListe(&l);
}

int main(int argc, char **argv)
{
  testProf();
  testUnPlusDeuxEgalTrois();
  testCroissante();
  testNombreMemePosition();
  testFonctVireDernier();
  testAjouteDevantPremierZero();
  testAjouteDevantDernierZero();
  testTic();

  return 0;
}
