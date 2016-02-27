
/*
* ÇAĞATAY ÇALI
* 14253019
*/
#include "parcala.h" /* Verileri okuyan ve okunan her satırı parçalayıp ilgili yere kaydeden fonksiyon. */
#include "listele.h"


int main() {
    
    dosyalariOku();

    printf(" ------------- Devreler -------------  : \n\n");
    devreler(); // Parçala.h içerisinde ilgili dosyalar mevcut.

    printf(" ------------- Kendi kalesine gol atan oyuncu -------------  \n\n");
    kendi_kalesine_gol_atan_oyuncu();

    printf(" ------------- Hattrick yapan oyuncular -------------  \n\n");
    hattrickYapanOyuncular();
    
 	goller(); // Goller ile ilgili işlemler

 	printf(" ------------- Gol kralları -------------  \n\n");
    gol_krallari();

 	printf(" ------------- Oyuncular -------------  : \n\n");
 	oyuncular(); //Sıralama yapılacak.

	printf(" ------------- Puan tablosu -------------  \n\n");
    puan_tablosu(); // sıralama yapıp dosyaya yazılacak.

    

    

    return 0;
}
