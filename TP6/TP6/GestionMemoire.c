#include "./libs/lib.h"

unsigned int calculerNumeroDePage(unsigned long adresse) {
	// Taille d'une page : 2¹⁰ octets
	unsigned long taillePage = 1024;
    return adresse / taillePage;
}

unsigned long calculerDeplacementDansLaPage(unsigned long adresse) {
	unsigned long taillePage = 1024;
    return adresse % taillePage;
}

unsigned long calculerAdresseComplete(unsigned int numeroDePage, unsigned long deplacementDansLaPage) {
	// TODO
	unsigned long taillePage = 1024;
    return numeroDePage * taillePage + deplacementDansLaPage;
}

void rechercherTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
	const int numeroDePageReq = calculerNumeroDePage(req->adresseVirtuelle);
	const int deplacement = calculerDeplacementDansLaPage(req->adresseVirtuelle);

	req->estDansTLB = 0;
	req->adressePhysique = 0;

	for(int i = 0; i < TAILLE_TLB; i++) {
		if (mem->tlb->numeroPage[i] == numeroDePageReq && mem->tlb->entreeValide[i]) {
			mem->tlb->dernierAcces[i] = req->date;
			req->estDansTLB = 1;
			req->adressePhysique = calculerAdresseComplete(mem->tlb->numeroCadre[i], deplacement);
			break;
		}		
	}
}

void rechercherTableDesPages(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
	const int numeroDePageReq = calculerNumeroDePage(req->adresseVirtuelle);
	const int deplacement = calculerDeplacementDansLaPage(req->adresseVirtuelle);

	req->adressePhysique = 0;
	req->estDansTablePages = 0;
	if (mem->tp->entreeValide[numeroDePageReq]) {
		req->estDansTablePages = 1;
		req->adressePhysique = calculerAdresseComplete(mem->tp->numeroCadre[numeroDePageReq], deplacement);
	}
}

void ajouterDansMemoire(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	//TODO
	const int numeroDePageReq = calculerNumeroDePage(req->adresseVirtuelle);
	const int deplacement = calculerDeplacementDansLaPage(req->adresseVirtuelle);

	for(int i = 0; i < TAILLE_MEMOIRE; i++) {
		if(mem->memoire->utilisee[i] == 0) {
			mem->memoire->numeroPage[i] = numeroDePageReq;
			mem->memoire->dateCreation[i] = req->date;
			mem->memoire->dernierAcces[i] = req->date;
			mem->memoire->utilisee[i] = 1;
			req->adressePhysique = calculerAdresseComplete(i, deplacement);
			break;
		}
	}
}

void mettreAJourTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
	int index = 0;

	if (mem->tlb->entreeValide[TAILLE_TLB - 1] == 1) {
		// TLB Plein
		for(int i = 0; i < TAILLE_TLB; i++) {
			if (mem->tlb->dateCreation[i] <= mem->tlb->dateCreation[index])
				index = i;
		}
	} else {
		for(int i = 0; i < TAILLE_TLB; i++) {
			if (mem->tlb->entreeValide[i] == 0) {
				index = i;
				break;
			}
		}
	}
	
	mem->tlb->numeroPage[index] = calculerNumeroDePage(req->adresseVirtuelle);
	mem->tlb->numeroCadre[index] = calculerNumeroDePage(req->adressePhysique);
	mem->tlb->dateCreation[index] = req->date;
	mem->tlb->dernierAcces[index] = req->date;
	mem->tlb->entreeValide[index] = 1;
}

// NE PAS MODIFIER
int main() {
    evaluate(
		&calculerNumeroDePage, 
		&calculerDeplacementDansLaPage, 
		&calculerAdresseComplete, 
        &rechercherTLB, 
		&rechercherTableDesPages,
		&mettreAJourTLB,
		&ajouterDansMemoire
    );
    return 0;
}
