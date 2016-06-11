les fichiers floppyOS_X_XXX.IMA sont des images de disquette elles peuvent etre montées dans le lecteur disque d'une machine virtuelle 
ou être copié sur une disquette vierge 

version
floppyOS_X_XXX

x_xxx

0_xxx ->  version en developement 

x_xxx_bx -> version bug n° x de la version x_xxx 

changelog: 
version :
	0_001 secteur de boot seulement
	0_002 secteur de boot charge un noyaux asm 16bit
	0_003 secteur de boot initialisent le GDT et boot un noyaux 32bit , le processeur est passé en mode protected
	*0_004 noyaux utilisent des fonctions c
	
	0_010 premier noyaux entièrement en c et utilisation de fonction d'affichage (print putcar scrollup )
	0_011 chargement un nouveau GDT par le noyau et integration de la fonction main
	0_012 implementation des interuptions horloge et clavier (non gere) et gestion du curseur(de saisi, interaction avec le peripherique vga)
	0_013 gestion des interuptions clavier (qwerty) pas de retoure a la ligne
	0_013_b1 gestion du backspace, affichage d'une variable u32
	0_014 execution d'une tache en mode utilisateur
	0_015 premier appel systeme print
	0_016 pagination simple
 
by alexis berger
