//
//  parcala.h
//  parcala
//
//  Created by cagatay on 30.12.2015.
//  Copyright © 2015 cagatay. All rights reserved.
//

#ifndef parcala_h
#define parcala_h
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "yapilar.h"
#include "listele.h"

struct istatistikler istatistik;
struct hattricks hattrick[50];




 /* İlgili satırı istenen yere kaydeden fonksiyon. */
 char kaydet(char sutun1[],char sutun2[],char sutun3[],char sutun4[],char nereyeKaydedilecek[],int sayac)
 {

 	/* Takımları kaydedelim */
 	if(strcmp(nereyeKaydedilecek,"dosyalar/takimlar.txt") == 0)
	{
    	istatistik.takim_sayisi++;

		/* Takımı struct'a yazalım */
		takim[sayac].id = atoi ( sutun1 );
		strcpy(takim[sayac].takim_on_ad,sutun2);
		strcpy(takim[sayac].takim_son_ad,sutun3);

		//printf("%d %s %s \n",takim[sayac].id,takim[sayac].takim_on_ad,takim[sayac].takim_son_ad);
	}
	else if( strcmp(nereyeKaydedilecek,"dosyalar/futbolcular.txt") == 0 )/* Futbolcularımızı kaydedelim */
	{

    	istatistik.oyuncu_sayisi++;
		/* Futbolcu id,takim id , futbolcu adı. */
		//printf("%s %s %s %s \n",sutun1,sutun2,sutun3,sutun4 );

		/* Takım id değerini integer'e çevirelim */
		int takim_id = atoi (sutun2);

		/* İlgili takıma oyuncumuzu ekleyelim */
		oyuncu[sayac].takim = &takim[takim_id];
		oyuncu[sayac].id = sayac; /* Oyuncu id değeri */
		strcpy(oyuncu[sayac].oyuncu_on_ad,sutun3); /* Oyuncu adı örn: Çağatay */
		strcpy(oyuncu[sayac].oyuncu_son_ad,sutun4); /* Oyuncu soyadı örn: Çalı  takim[takim_id]*/ 

	}
	else if( strcmp(nereyeKaydedilecek,"dosyalar/maclar.txt") == 0 )/* Maçlarımızı kaydedelim */
	{

    	istatistik.mac_sayisi++;

		int mac_id = atoi (sutun1);
		int ev_sahibi_id = atoi (sutun2);
		int misafir_id = atoi (sutun3);

		mac[sayac].id = mac_id;
		mac[sayac].ev_sahibi = &takim[ev_sahibi_id];
		mac[sayac].misafir = &takim[misafir_id];

		/* Takımların oynadığı maç sayısını birer arttıralım */
		takim[ev_sahibi_id].oynadigi_mac_sayisi++;
		takim[misafir_id].oynadigi_mac_sayisi++;



		//printf("%d %d %d \n",mac[sayac].id,mac[sayac].ev_sahibi->id,mac[sayac].misafir->id );

	}
	else if( strcmp(nereyeKaydedilecek,"dosyalar/goller.txt") == 0 )/* Gollerimizi kaydedelim */
	{

		/* İstatistiklere gol sayısını girelim */
    	istatistik.gol_sayisi++;

    	/* ---------------------- Txt'den gelen gol bilgilerini işleyelim ---------------------- */

		int mac_id = atoi (sutun1);
		int dakika = atoi (sutun2);
		int takim_id = atoi (sutun3);
		int oyuncu_id = atoi (sutun4);
		/* ---------------------- Txt'den gelen gol bilgilerini kaydettik ---------------------- */

    	/* ---------------------- Maç nesnesine golü ekleyelim ---------------------- */
		gol[sayac].mac = &mac[mac_id];
		gol[sayac].dakika = dakika; /* x. Maç y. Dakikada z. Oyuncu Tarafından k. Takım üyesi olarak gol attı. */
		gol[sayac].takim = &takim[takim_id]; /* Golü atan takım kim? */
		gol[sayac].oyuncu = &oyuncu[oyuncu_id]; /* Golü atan oyuncu kim? */

		/* ---------------------- Maç nesnesine golleri kaydettik ---------------------- */


		/* ---------------------- Gollerin dakikalarına göre devrelere golleri kaydedeceğiz ---------------------- */

		if(dakika < 45)
		{
			istatistik.birinci_devrede_atilan_gol_sayisi++;
		}
		else
		{
			istatistik.ikinci_devrede_atilan_gol_sayisi++;
		}

		/* ---------------------- Gollerin dakikalarına göre devrelere golleri kaydettik ---------------------- */


		/* ---------------------- Takımlara golleri kaydedeceğiz ---------------------- */
		/* Takımların gol hanelerine birer gol ekleyelim maclar'a ev sahibi_gol ve misafir_gol olarak ekleyelim*/
		if(gol[sayac].takim->id == mac[mac_id].ev_sahibi->id )
		{
			mac[mac_id].ev_sahibi_gol_sayisi++; // Golü atan takıma gol +1 ekleyelim
			mac[mac_id].misafir->yenilen_gol_sayisi++; // Rakip takımın yediği golude kaydedelim.
			mac[mac_id].ev_sahibi->atilan_gol_sayisi++; 
		} 
		else
		{
			mac[mac_id].misafir_gol_sayisi++; // Golü atan takıma gol +1 ekleyelim
			mac[mac_id].ev_sahibi->yenilen_gol_sayisi++; // Rakip takımın yediği golude kaydedelim.
			mac[mac_id].misafir->atilan_gol_sayisi++; 
		} 

		/* ---------------------- Takımlara golleri kaydettik ---------------------- */

	   /* ---------------------- Oyunculara golleri kaydedeceğiz ---------------------- */

		if(gol[sayac].takim->id != gol[sayac].oyuncu->takim->id)
		{
			//gol[sayac].kendi_kalesine =  1; KULLANILMIYOR

			/* Oyuncunun kendi kalesine attığı gol sayısı olarak kaydedelim. */
			oyuncu[oyuncu_id].kendi_kalesine_gol_sayisi++;
		}
		else
		{
			/* Oyuncunun gol sayısını arttıralım */
			oyuncu[oyuncu_id].gol_sayisi++; 

			//gol[sayac].kendi_kalesine =  0; KULLANILMIYOR

			/* 
				Oyuncu bu maçta kaç adet gol atmış?
				Bütün goller içerisinden bu maçta atılmış olanları eğer ben attıysam
				Ve attığım goller kendi kaleme değilse hattrick olarak işle!
			 */
			int hattrick_sayac = 0;
			int hattrick_veri_sayaci = 0;
			for (int o = 0; o < istatistik.gol_sayisi; o++)
			{
				/* İlgili maçta */
				if(gol[o].mac->id == gol[sayac].mac->id)
				{
					/* Aynı oyuncu gol attı ise. */
					if(gol[sayac].oyuncu->id == gol[o].oyuncu->id)
					{
						++hattrick_sayac; /* Hattrick sayacımızı bir arttıralım ve bunu hemen yapalım ;) */
					}
				}
				if(hattrick_sayac > 2)
				{
					//printf("%s %s , %d.dakikada %s %s takımı ile hattrick yaptı. \n\n",gol[o].oyuncu->oyuncu_on_ad,gol[o].oyuncu->oyuncu_son_ad,gol[o].dakika,gol[o].oyuncu->takim->takim_on_ad,gol[o].oyuncu->takim->takim_son_ad );

					/* Hattrick verisini kaydedelim */
					hattrick[hattrick_veri_sayaci].id = hattrick_veri_sayaci;
					hattrick[hattrick_veri_sayaci].oyuncu = &oyuncu[oyuncu_id];
					hattrick[hattrick_veri_sayaci].mac = &mac[mac_id];
					hattrick_veri_sayaci++;

					//printf("%s %s oyuncusu maçta hattrick yaptı \n",hattrick[0].oyuncu->oyuncu_on_ad,hattrick[0].oyuncu->oyuncu_son_ad );

					/* Hattrick sayısını tutacağız. */
					istatistik.hattrick_sayisi = hattrick_veri_sayaci;
				}
			}
		}

		/* ---------------------- Oyunculara golleri kaydettik ---------------------- */
		//printf("%d %s %s %s \n",gol[sayac].dakika, gol[sayac].takim->takim_on_ad, gol[sayac].oyuncu->oyuncu_on_ad, gol[sayac].oyuncu->oyuncu_son_ad );
	}


 	return 0;
 }

/* 
	Gelen satırın her bir parçasını istenen yere kaydedecek.
	Kaç adet sutun olacaksa okadar değişkene atayıp değişkenleri yazdıracak.
	Nereye kaydedileceği
 */
char parcala(char line[],char nereyeKaydedilecek[],int sayac)
{
	/* Kullanacağımız geçici sutun değişkenlerini açalım */
	char sutun1[20],sutun2[20],sutun3[20],sutun4[20];

    char * pch;

    pch = strtok (line," ,-");

	for (int i = 1; i < 5; i++)
	{
		if(i == 1)
		{
			strcpy(sutun1,pch);
		} 
		else if (i == 2)
		{
			strcpy(sutun2,pch);
		}
		else if (i == 3)
		{
			strcpy(sutun3,pch);
		}
		else if (i == 4)
		{
			if(strcmp(nereyeKaydedilecek,"dosyalar/takimlar.txt") != 0 && strcmp(nereyeKaydedilecek,"dosyalar/maclar.txt") != 0)
			{
				strcpy(sutun4,pch);
			}
			else
			{
				strcpy(sutun4,"-");
			}
		}
		//printf ("%s ",pch);
		pch = strtok (NULL, " ,-");
	}

	/* Verileri kaydediyoruz. */
	kaydet(sutun1,sutun2,sutun3,sutun4,nereyeKaydedilecek,sayac); /* Sayaç kaçıncı düğüme veri girişi olacağını temsil eder. */

    return 0;
}

/* Okunacak txt'yi satır satır okuyacak fonksiyon. */
char oku(char okunacak_txt[])
{
    FILE* file = fopen(okunacak_txt, "r");
    char line[100];

    int sayac = 0;
    /* Okunacak txt'yi satır satır okuyacak ve \n'ye ihtiyaç duymayan fonksiyon. */
    while (fgets(line, sizeof(line), file)) {
       
        parcala(line,okunacak_txt,sayac);

        sayac++;
    }


    //printf("%d %s %s \n",takim[2].oyuncu[7].id,takim[2].oyuncu[7].oyuncu_on_ad,takim[2].oyuncu[7].oyuncu_son_ad);

    //printf("Takım %d %s %s \n",takim[0].id,takim[0].takim_on_ad,takim[0].takim_son_ad );
    
    fclose(file);
    return 0;
}


int dosyalariOku()
{
	oku("dosyalar/takimlar.txt");
    oku("dosyalar/futbolcular.txt");
    oku("dosyalar/maclar.txt");
    oku("dosyalar/goller.txt");

    puan(); // Puan hesaplama fonksiyonumuz
  

    return 0;
}




#endif /* parcala_h */
