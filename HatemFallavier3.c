
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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


typedef struct bloc_image
{ 
    bool quatre ;
    struct bloc_image *hg, *hd, *bg, *bd ;
} bloc_image ;

typedef bloc_image *image ;

/*************************************************/
/*                                               */
/*                Questions                      */
/*                                               */
/*************************************************/

/*****************Question  1*********************/
image Blanc() {
    // On utilise sizeof(bloc_image) car c'est la taille de la structure
    image res = (image)malloc(sizeof(bloc_image));

    // On vérifie que le malloc a fonctionné
    if (res ISNOT NULL) {
        res->quatre = FALSE;
        res->hg = NULL;
        res->hd = NULL;
        res->bg = NULL;
        res->bd = NULL;
    }

    return res;
}

image Noir() {
    return NULL;
}

image Compose(image i0, image i1, image i2, image i3) {
    // On utilise sizeof(bloc_image) car c'est la taille de la structure
    image res = (image)malloc(sizeof(bloc_image));

    // On vérifie que le malloc a fonctionné
    if (res ISNOT NULL) {
        res->quatre = TRUE;
        res->hg = i0;
        res->hd = i1;
        res->bg = i2;
        res->bd = i3;
    }

    return res;
}

void testBlancNoirCompose () {
    printf("\nTest de BlancNoirCompose\n");
    printf("Test de l'image blanche\n");
    image blanc = Blanc();
    assert(blanc ISNOT NULL);
    assert(blanc->quatre == FALSE);
    assert(blanc->hg == NULL);
    assert(blanc->hd == NULL);
    assert(blanc->bg == NULL);
    assert(blanc->bd == NULL);

    printf("Test de l'image noire\n");
    image noir = Noir();
    assert(noir == NULL);

    printf("Test de l'image composée\n");
    image blanc2 = Blanc();
    image noir2 = Noir();
    image comp = Compose(blanc, noir, blanc2, noir2);

    assert(comp->hg == blanc);
    assert(comp->hd == noir);
    assert(comp->bg == blanc2);
    assert(comp->bd == noir2);

    free(blanc);
    free(noir);
    free(blanc2);
    free(noir2);
    free(comp);
}

/*****************Question  2*********************/
void Affichage(image img) {
    // Test de l'image noire, on affiche X
    if (img == NULL) then
        printf("X");
    
    // Test de l'image blanche, on affiche o
    else if (NOT img->quatre) then
        printf("o");
    
    // Sinon l'image est composée
    else {
        // On affiche les 4 composantes puis on affiche *
        Affichage(img->hg);
        Affichage(img->hd);
        Affichage(img->bg);
        Affichage(img->bd);
        printf("*");
    }

}

void testAffichage () {
    printf("\nTest de Affichage\n");
    printf("Test de l'image blanche : ");
    image blanc = Blanc();
    Affichage(blanc);
    printf("\n");

    printf("Test de l'image noire : ");
    image noir = Noir();
    Affichage(noir);
    printf("\n");

    printf("Test de l'image composée oXoX : ");
    image comp = Compose(blanc, noir, blanc, noir);
    Affichage(comp);
    printf("\n");

    free(blanc);
    free(noir);
    free(comp);
}

/*****************Question  3*********************/
void AffichageProfondeurAux(image img, int p) {
    // Test de l'image noire, on affiche X
    if (img == NULL) then
        printf("X%d", p);
    
    // Test de l'image blanche, on affiche o
    else if (NOT img->quatre) then
        printf("o%d", p);
    
    // Sinon l'image est composée
    else {
        // On affiche les 4 composantes puis on affiche *
        AffichageProfondeurAux(img->hg, p+1);
        AffichageProfondeurAux(img->hd, p+1);
        AffichageProfondeurAux(img->bg, p+1);
        AffichageProfondeurAux(img->bd, p+1);
        printf("*%d", p);
    }

}

void AffichageProfondeur(image img) {
    // On ajoute un paramètre de profondeur
    AffichageProfondeurAux(img, 0);
}

void testAffichageProfondeur () {
    printf("\nTest de AffichageProfondeur\n");
    printf("Test de l'image blanche : ");
    image blanc = Blanc();
    AffichageProfondeur(blanc);
    printf("\n");

    printf("Test de l'image noire : ");
    image noir = Noir();
    AffichageProfondeur(noir);
    printf("\n");

    printf("Test de l'image composée oXoX : ");
    image comp = Compose(blanc, noir, blanc, noir);
    AffichageProfondeur(comp);
    printf("\n");

    printf("Test de l'image composée 2 fois (oXoX)ooX : ");
    image comp2 = Compose(comp, blanc, blanc, noir);
    AffichageProfondeur(comp2);
    printf("\n");

    free(blanc);
    free(noir);
    free(comp);
    free(comp2);
}

/*****************Question  4*********************/
image imageFromString(char s[], int deb, int length) {
    // Si c'est une image non composée
    if (length == 1) {
        // Si le caractère est 'X', retourner une image noire
        if (s[deb] == 'X') return Noir();       
        // Si le caractère est 'o', retourner une image blanche
        else if (s[deb] == 'o') return Blanc(); 
        // Si le caractère n'est ni 'X' ni 'o', c'est une erreur
        else {
            printf("Ce n'est pas une image\n");
            exit(1);
        }
    } 
    // Si c'est une image composée
    else {
        int i_start[4] = {0};
        int i_end[4] = {0};
        int i[4] = {0};
        int cursor = length - 1;

        // Trouver la position du dernier '*' qui sépare les sous-images
        while (s[deb+cursor] ISNOT '*')
            cursor -= 1;

        // Diviser la chaîne en 4 sous-chaînes, chacune représentant une sous-image
        for (int k = 3; k >= 0; k -= 1) {
            int size = 1;
            i_end[k] = cursor;
            while (i[k] < size) {
                cursor -= 1;
                if (s[deb+cursor] ISNOT '*')
                    i[k] += 1;
                else
                    size = size + 3;
            }
            i_start[k] = i_end[k] - i[k] - (size - 1) / 3;
        }
        
        image img_res[4];
        // Traiter récursivement chaque sous-image
        for (int k = 3; k >= 0; k -= 1)
            img_res[k] = imageFromString(s, deb+i_start[k], i_end[k] - i_start[k]);

        // Combiner les quatre sous-images en une seule image
        return Compose(img_res[0], img_res[1], img_res[2], img_res[3]);
    }
}

image Lecture() {
    // Obtenir la chaîne de caractère
    int c;
    int longeur = 0;
    char buf[1024];
    printf("Début de la lecture\n");

    // On lit des char et on ajoute tant que c'est pas '!'
    do {
        c = getchar();
        buf[longeur] = c;
        longeur += 1;
    } while (c ISNOT '!');

    printf("Fin de la lecture\n");

    // Créer l'image
    return imageFromString(buf, 0, longeur-1); // On enlève 1 pour le !
}

void testLecture() {
    printf("\nTest de Lecture : \n");
    // printf("Test de la saisie \n");
    // image i = Lecture();
    // Affichage(i);
    // printf("\n");

    printf("Test avec valeurs préféfinies \n");
    printf("o -> "); Affichage(imageFromString("o", 0, 1)); printf("\n");
    printf("X -> "); Affichage(imageFromString("X", 0, 1)); printf("\n");
    printf("oooX*ooXo*oXoo*Xooo** -> "); Affichage(imageFromString("oooX*ooXo*oXoo*Xooo**", 0, 21)); printf("\n");

    // free(i);
}

/*****************Question  5*********************/
bool EstNoire(image i) {
    return (i == NULL OR (i->quatre == TRUE AND (EstNoire(i->bd) AND EstNoire(i->bg) AND EstNoire(i->hd) AND EstNoire(i->hg))));
}

bool EstBlanche(image i) {
    return (i ISNOT NULL AND ((i->quatre == FALSE) OR (i->quatre == TRUE AND EstBlanche(i->bd) AND EstBlanche(i->bg) AND EstBlanche(i->hd) AND EstBlanche(i->hg))));
}

void testEstNoireBlanche () {
    printf("\nTest de EstNoireBlanche\n");
    printf("Test de l'image blanche : ");
    image blanc = Blanc();
    printf("Noire : %d ; Blanche : %d\n", EstNoire(blanc), EstBlanche(blanc));

    printf("Test de l'image noire : ");
    image noir = Noir();
    printf("Noire : %d ; Blanche : %d\n", EstNoire(noir), EstBlanche(noir));

    printf("Test de l'image composée oXoX : ");
    image comp = Compose(blanc, noir, blanc, noir);
    printf("Noire : %d ; Blanche : %d\n", EstNoire(comp), EstBlanche(comp));

    printf("Test de l'image composée XXXX : ");
    image compNoir = Compose(noir, noir, noir, noir);
    printf("Noire : %d ; Blanche : %d\n", EstNoire(compNoir), EstBlanche(compNoir));

    printf("Test de l'image composée oooo : ");
    image compBlanc = Compose(blanc, blanc, blanc, blanc);
    printf("Noire : %d ; Blanche : %d\n", EstNoire(compBlanc), EstBlanche(compBlanc));

    free(blanc);
    free(noir);
    free(comp);
    free(compNoir);
    free(compBlanc);
}

/*****************Question  6*********************/
float Aire(image i) {
    // On regarde si c'est noir(1) ou blanc(0), ou sinon on fait la moyenne
    if (i == NULL) then return 1.0;
    else if (i->quatre == FALSE) then return 0.0;
    else return (Aire(i->bd) + Aire(i->bg) + Aire(i->hd) + Aire(i->hg)) / 4;
}

void testAire() {
    printf("\nTest de Aire\n");
    printf("Test de l'image blanche : ");
    image blanc = Blanc();
    printf("Aire : %f\n", Aire(blanc));

    printf("Test de l'image noire : ");
    image noir = Noir();
    printf("Aire : %f\n", Aire(noir));

    printf("Test de l'image composée oXoX : ");
    image comp = Compose(blanc, noir, blanc, noir);
    printf("Aire : %f\n", Aire(comp));

    printf("Test de l'image composée 2 fois (oXoX)ooX : ");
    image comp2 = Compose(comp, blanc, blanc, noir);
    printf("Aire : %f\n", Aire(comp2));

    free(blanc);
    free(noir);
    free(comp);
    free(comp2);
}

/*****************Question  7*********************/

// Fonction pour générer un triangle basé sur la profondeur 'p'
image TriangleBD(int p) {
    // Si la profondeur est 0, retourner une image blanche
    if (p == 0) then return Blanc();
    // Sinon, composer l'image en utilisant la récursion :
    // on met du blanc en haut à gauche, du noir en bas à droite et les zones bas-gauche et haut-droite sont réalisées à partir des triangles préalablement construits
    else return Compose(Blanc(), TriangleBD(p - 1), TriangleBD(p - 1), Noir());
}

// Fonction de test pour la fonction TriangleBD
void testTriangleBD() {
    printf("\nTest de TriangleBD\n");
    printf("Test de profondeur 0 : ");
    image p0 = TriangleBD(0);
    Affichage(p0);
    printf("\n");

    printf("Test de profondeur 1 : ");
    image p1 = TriangleBD(1);
    Affichage(p1);
    printf("\n");

    printf("Test de profondeur 3 : ");
    image p3 = TriangleBD(3);
    Affichage(p3);
    printf("\n");


    free(p0);
    free(p1);
    free(p3);
}

/*****************Question  8*********************/
void Arrondit(image *i, int p) {
    if (p == 0) {
        /* On regarde la couleur dominante dans l'image pour savoir si on la transforme en noir ou en blanc */
        if (Aire(*i) >= 0.5) then *i = Noir();
        else *i = Blanc();
    }
    else {
        // On arrondi les sous-images de l'image composée à p-1
        if (*i ISNOT NULL AND (*i)->quatre) {
            Arrondit(&(*i)->hg, p - 1);
            Arrondit(&(*i)->hd, p - 1);
            Arrondit(&(*i)->bg, p - 1);
            Arrondit(&(*i)->bd, p - 1);
        }
    }
}

void testArrondit() {
    printf("\nTest de Arrondit\n");
    printf("Test de l'image blanche vers 0 : ");
    image blanc = Blanc();
    Arrondit(&blanc, 0);
    Affichage(blanc);
    printf("\n");


    printf("Test de l'image noire vers 0 : ");
    image noir = Noir();
    Arrondit(&noir, 0);
    Affichage(noir);
    printf("\n");

    printf("Test de l'image composée oooX vers 0 : ");
    image comp = Compose(blanc, blanc, blanc, noir);
    Arrondit(&comp, 0);
    Affichage(comp);
    printf("\n");

    printf("Test de l'image composée oooX vers 1 : ");
    image comp2 = Compose(blanc, blanc, blanc, noir);
    Arrondit(&comp2, 1);
    Affichage(comp2);
    printf("\n");

    printf("Test de l'image composée XXXooX*oXXo*oooX**oXo*oXXoooXXX**oX** vers 2 : ");
    image comp3 = imageFromString("XXXooX*oXXo*oooX**oXo*oXXoooXXX**oX**", 0, 37);
    Arrondit(&comp3, 2);
    Affichage(comp3);
    printf("\n");

    free(blanc);
    free(noir);
    free(comp);
    free(comp2);
    free(comp3);
}

/*****************Question  9*********************/
bool MemeDessin(image i1, image i2) {
    // une est Noire, les deux doivent l'être
    if (i1 == NULL OR i2 == NULL) then
        return (EstNoire(i1) AND EstNoire(i2));
    // une est Blanche, les deux doivent l'être
    else if (NOT i1->quatre OR NOT i2->quatre) then
        return (EstBlanche(i1) AND EstBlanche(i2));
    // Les deux sont composées, on regarde les sous-images
    else
        MemeDessin(i1->bd, i2->bd) AND MemeDessin(i1->bg, i2->bg) AND MemeDessin(i1->hg, i2->hg) AND MemeDessin(i1->hd, i2->hd);
}

void testMemeDessin () {
    printf("\nTest de MemeDessin\n");
    printf("Test de l'image blanche : ");
    image blanc = Blanc();
    image compBlanc = Compose(blanc, blanc, blanc, blanc);
    printf("Blanc-Blanc : %d ; Blanc-oooo : %d\n", MemeDessin(blanc, blanc), MemeDessin(blanc, compBlanc));

    printf("Test de l'image noire : ");
    image noir = Noir();
    image compNoir = Compose(noir, noir, noir, noir);
    printf("Noir-Noir : %d ; Noir-XXXX: %d\n", MemeDessin(noir, noir), MemeDessin(noir, compNoir));

    printf("Test de l'image composée oXoX : ");
    image comp = Compose(blanc, noir, blanc, noir);
    printf("Blanc-oXoX : %d ; Noir-oXoX: %d ; ", MemeDessin(blanc, comp), MemeDessin(noir, comp));
    printf("oXoX-Blanc : %d ; oXoX-Noir: %d ; ", MemeDessin(comp, blanc), MemeDessin(comp, noir));
    printf("oXoX-oXoX : %d\n", MemeDessin(comp, comp));

    free(blanc);
    free(noir);
    free(compNoir);
    free(compBlanc);
    free(comp);
}

/*****************Question  10********************/
void InterUnionAux(image *res, image image1, image image2, bool forUnion) {
    // Les deux sont noires, le résultat est noir
    if (EstNoire(image1) AND EstNoire(image2)) then
        *res = Noir();

    // Les deux sont blanches, le résultat est blanc
    else if (EstBlanche(image1) AND EstBlanche(image2)) then
        *res = Blanc();

    // Une est blanche, et l'autre noire, mais pas les deux en même temps (via else)
    else if ((EstNoire(image1) OR EstNoire(image2)) AND (EstBlanche(image1) OR EstBlanche(image2))) {
        // Si c'est une union c'est noir, sinon blanc
        if (forUnion) then
            *res = Noir();
        else
            *res = Blanc();
    }
    // Au moins une est composée et multicolore
    else {
        // Si c'est une non-composée, on l'a compose
        if (image1 == NULL OR NOT image1->quatre) then
            image1 = Compose(image1, image1, image1, image1);
        else if (image2 == NULL OR NOT image2->quatre) then
            image2 = Compose(image2, image2, image2, image2);

        // On fait l'InterUnion sur les fils
        *res = Compose(NULL, NULL, NULL, NULL);
        InterUnionAux(&((*res)->hg), image1->hg, image2->hg, forUnion);
        InterUnionAux(&((*res)->hd), image1->hd, image2->hd, forUnion);
        InterUnionAux(&((*res)->bg), image1->bg, image2->bg, forUnion);
        InterUnionAux(&((*res)->bd), image1->bd, image2->bd, forUnion);
    }
   
}

void InterUnion(image *image1, image *image2) {
    // On stocke les résultats inter et union
    image intersectionResult, unionResult;
    InterUnionAux(&intersectionResult, *image1, *image2, FALSE);
    InterUnionAux(&unionResult, *image1, *image2, TRUE);

    // Mise à jour des images d'origine
    *image1 = intersectionResult;
    *image2 = unionResult;
}

void testInterUnion() {
    printf("\nTest de InterUnion\n");
    printf("Deux Blanc \n");
    image image1Blanc = Blanc();
    image image2Blanc = Blanc();

    Affichage(image1Blanc); printf(" et ");
    Affichage(image2Blanc); printf(" -> ");

    InterUnion(&image1Blanc, &image2Blanc);
    Affichage(image1Blanc); printf(" et ");
    Affichage(image2Blanc); printf("\n");

    printf("Deux Noir \n");
    image image1Noir = Noir();
    image image2Noir = Noir();

    Affichage(image1Noir); printf(" et ");
    Affichage(image2Noir); printf(" -> ");

    InterUnion(&image1Noir, &image2Noir);
    Affichage(image1Noir); printf(" et ");
    Affichage(image2Noir); printf("\n");

    printf("Noir et Blanc \n");
    Affichage(image1Noir); printf(" et ");
    Affichage(image1Blanc); printf(" -> ");

    InterUnion(&image1Noir, &image1Blanc);
    Affichage(image1Noir); printf(" et ");
    Affichage(image1Blanc); printf("\n");

    printf("Exmple du prof \n");
    image i1 = imageFromString("oXoXXo*oXoX*oXX**", 0, 17);
    image i2 = imageFromString("XoXoXooX*ooXX*X**", 0, 17);
    Affichage(i1); printf(" et ");
    Affichage(i2); printf(" -> ");

    InterUnion(&i1, &i2);
    Affichage(i1); printf(" et ");
    Affichage(i2); printf("\n");


    free(image1Blanc);
    free(image2Blanc);
    free(image1Noir);
    free(image2Noir);
    free(i1);
    free(i2);
}


/*****************Question  11********************/
int CompteDamiersAux(image image, int *profDamier) {
    // Si ce n'est pas composé, il n'y a pas de damier
    if (image == NULL OR NOT image->quatre) then
        return 0;
    
    // Si c'est un damier de profondeur 1
    else if ((image->hg AND NOT image->hg->quatre) AND image->hd == NULL AND image->bg == NULL AND (image->bd AND NOT image->bd->quatre)) {
        *profDamier = 1;
        return 1;
    }

    // C'est peut être un damier, il faut vérifier les fils
    else {
        // On compte le nombre de damiers et la profondeur d'eux
        int cpt = 0;
        int profDamierRec[4] = {0};
        cpt += CompteDamiersAux(image->hg, &profDamierRec[0]);
        cpt += CompteDamiersAux(image->hd, &profDamierRec[1]);
        cpt += CompteDamiersAux(image->bg, &profDamierRec[2]);
        cpt += CompteDamiersAux(image->bd, &profDamierRec[3]);
        
        bool damierValide = TRUE;

        // Si la profondeur du damier fils 0 est 0 (pas de damier), le damier est invalide
        if (profDamierRec[0] == 0) then
            damierValide = FALSE;
        // Si le fils 0 est bon, il faut que les autres damiers fils aient la même profondeur que le fils 0 (NOT 0 via condition 1)
        else
            for (int i = 1; i < 4; i += 1)
                if (profDamierRec[i] ISNOT profDamierRec[0]) then
                    damierValide = FALSE;
        
        // Si le damier est valide, on ajoute 1 au compteur et à la profondeur
        if (damierValide) {
            cpt += 1;
            *profDamier = profDamierRec[0]+1;
        }
        // Sinon la profondeur est de 0 (pas de damier)
        else
            *profDamier = 0;
            
        return cpt;
    }
}

int CompteDamiers(image image) {
    int profDamier = 0;
    return CompteDamiersAux(image, &profDamier);
}

void testCompteDamiers() {
    printf("\nTest de CompteDamiers\n");
    printf("Hauteur 0 : ");
    image blanc = Blanc();
    printf("%d\n", CompteDamiers(blanc));

    printf("Hauteur 1 : ");
    image noir = Noir();
    image comp = Compose(blanc, noir, noir, blanc);
    printf("%d\n", CompteDamiers(comp));

    printf("Hauteur 2 : ");
    image comp2 = Compose(comp, comp, comp, comp);
    printf("%d\n", CompteDamiers(comp2));

    printf("Hauteur 3 : ");
    image comp3 = Compose(comp2, comp2, comp2, comp2);
    printf("%d\n", CompteDamiers(comp3));

    printf("Exemple du prof : ");
    image prof = imageFromString("oXXo*oXXo*oXXo*oXXo**oXXo*oXXo*oXXo*oXXo**oXXo*oXXo*oXXo**oXXo*oXXo*XX*oooo*XXoooooo*o***", 0, 89);
    printf("%d\n", CompteDamiers(prof));

    free(blanc);
    free(noir);
    free(comp);
    free(comp2);
    free(comp3);
    free(prof);
}

/*****************Question  12********************/
void CompressAux(image *image, bloc_image *registre[], int *nbReg) {
    // Si c'est une image composée, on compresse les fils d'abord
    if (*image ISNOT NULL AND (*image)->quatre) {
        CompressAux(&(*image)->hg, registre, nbReg);
        CompressAux(&(*image)->hd, registre, nbReg);
        CompressAux(&(*image)->bg, registre, nbReg);
        CompressAux(&(*image)->bd, registre, nbReg);
    }

    // On essaye de trouver un élement déjà enregistré et identique
    bool trouve = FALSE;
    for (int i = 0; i < *nbReg; i++) {
        // Si on en trouve un, on remplace l'image par l'élement enregistré
        if (MemeDessin(*image, registre[i])) {
            trouve = TRUE;
            *image = registre[i];
        }
    }

    // Si on en a pas trouvé, on l'ajoute au registre
    if (NOT trouve) {
        registre[*nbReg] = *image;
        *nbReg += 1;
    }
}

void Compress(image *image) {
    bloc_image* registre[1024];
    int nbReg = 0;
    CompressAux(image, registre, &nbReg);

    //Affichage de débogage
    printf("(%d)\n", nbReg); 
    printf("[");
    for (int i = 0; i < nbReg; i++)
        printf("%d; ", &registre[i]);
    printf("]");
    printf("\n[");
    for (int i = 0; i < nbReg; i++) {
        Affichage(registre[i]); printf("; ");
    }
    printf("]");
}

void Dilate(image *image) {
    // On crée un nouveau noeud

    if (*image == NULL) then 
        *image = NULL;
    else if (NOT (*image)->quatre) then
        *image = Blanc();
    else {
        // On recrée les fils d'abord
        Dilate(&(*image)->hg);
        Dilate(&(*image)->hd);
        Dilate(&(*image)->bg);
        Dilate(&(*image)->bd);

        *image = Compose((*image)->hg, (*image)->hd, (*image)->bg, (*image)->bd);
    }

    // Affichage de débogage
    printf("%d; ", image);
}

void testCompressDilate() {
    printf("\nTest de CompressDilate\n");
    printf("Test de Compress : \n");
    printf("Simple : \n");
    image blanc = Blanc();
    Affichage(blanc); printf("\n");
    Compress(&blanc); printf("\n");
    Affichage(blanc); printf("\n");

    printf("Composée : \n");
    image noir = Noir();
    image comp = Compose(blanc, noir, noir, blanc);
    Affichage(comp); printf("\n");
    Compress(&comp); printf("\n");
    Affichage(comp); printf("\n");

    printf("Prof : \n");
    image prof = imageFromString("oXXo*XoXXo*oXXo*XooX**XoXXo*oXXo*XooX**XXooX*XooX*o**", 0, 53);
    Affichage(prof); printf("\n");
    Compress(&prof); printf("\n");
    Affichage(prof); printf("\n");


    printf("\nTest de Dilate : \n");
    printf("Simple : \n");
    Affichage(blanc); printf("\n[");
    Dilate(&blanc); printf("]\n");
    Affichage(blanc); printf("\n");

    printf("Composée : \n");
    Affichage(comp); printf("\n[");
    Dilate(&comp); printf("]\n");
    Affichage(comp); printf("\n");

    printf("Prof : \n");
    Affichage(prof); printf("\n[");
    Dilate(&prof); printf("]\n");
    Affichage(prof); printf("\n");


    free(blanc);
    free(noir);
    free(comp);
    free(prof);
}


int main() {
    // testBlancNoirCompose();
    // testAffichage();
    // testAffichageProfondeur();
    // testLecture();
    // testAire();
    // testEstNoireBlanche();
    // testTriangleBD();
    // testArrondit();
    // testMemeDessin();
    // testInterUnion();
    // testCompteDamiers();
    // testCompressDilate();
    return 0;
}