//
//  listele.h
//  parcala
//
//  Created by cagatay on 31.12.2015.
//  Copyright © 2015 cagatay. All rights reserved.
//

#ifndef listele_h
#define listele_h

struct gol_krallari gol_krali[50];
struct oyuncular oyuncu[100];
struct hattricks hattrick[50];

void oyunculari_sirala(struct oyuncular *oyuncu) 
{

    int j,i,n = istatistik.oyuncu_sayisi;

    for(i=1;i<n;i++)
    {
        for(j=0;j<n-i;j++)
        {
            if(oyuncu[j].gol_sayisi < oyuncu[j+1].gol_sayisi)
            {
                struct oyuncular temp = oyuncu[j];
                oyuncu[j] =oyuncu[j+1];
                oyuncu[j+1] = temp;
            }
        }
    }

}

void puanlari_sirala(struct takimlar *takim) 
{

    int j,i,n = istatistik.takim_sayisi;

    for(i=1;i<n;i++)
    {
        for(j=0;j<n-i;j++)
        {
            if(takim[j].puan < takim[j+1].puan) // Puana göre sıralama
            {
                struct takimlar temp = takim[j];
                takim[j] =takim[j+1];
                takim[j+1] = temp;
            }
        }
    }

    for(i=1;i<n;i++)
    {
        for(j=0;j<n-i;j++)
        {
            if(takim[j].puan == takim[j+1].puan) // Eğer takımların puanları eşitse
            {
                struct takimlar temp = takim[j];
                takim[j] =takim[j+1];
                takim[j+1] = temp;
            }
        }
    }

}


int oyuncular()
{
	/* Oyuncuları gollerine göre sıralayalım. */
	oyunculari_sirala(oyuncu);

	/* En çok gol atan bir oyuncuyu yakalayacağız */
	for (int k = 0; k < istatistik.oyuncu_sayisi; k++)
	{
		printf("%s %s  - Gol :  %d  Takım :  %s  %s \n",
			oyuncu[k].oyuncu_on_ad,
			oyuncu[k].oyuncu_son_ad,
			oyuncu[k].gol_sayisi,
			oyuncu[k].takim->takim_on_ad,
			oyuncu[k].takim->takim_son_ad );
	}

	return 0;
}

/* Gol kralını/larını bulacağımız fonksiyon */
int goller()
{
	/* Tüm oyuncuları goller ile listeleyelim */
	int oyuncu_sayisi = istatistik.oyuncu_sayisi;
	int gol_krallari[20],gol_sayisi = oyuncu[0].gol_sayisi; /* Gol sayısını ilk oyuncunun gol sayısından başlatarak bir if'den kurtuluyoruz. */

	/* En çok gol atan bir oyuncuyu yakalayacağız */
	for (int i = 0; i < oyuncu_sayisi; i++)
	{
		//printf("%s %d %s  \n",	oyuncu[i].oyuncu_on_ad,oyuncu[i].gol_sayisi,oyuncu[i].takim->takim_on_ad );

		if(gol_sayisi < oyuncu[i].gol_sayisi) /* Eğer gelen gol sayısı mevcut gol sayısından küçükse onu kaydedeceğiz, En büyük değeri bulmaya çalışacağız. */
		{
			gol_sayisi = oyuncu[i].gol_sayisi;
		}
	}

	int gol_krali_sayisi = 0;
	/* En çok gol atan oyuncunun gol sayısını alıp yapımızda başka varsa içerisinde arama yapacağız ve bu değerlerin hepsini gol krallarına kaydedeceğiz */
	for (int k = 0; k < oyuncu_sayisi; k++)
	{
		if(gol_sayisi == oyuncu[k].gol_sayisi) /* Gol krallarına yazacağız. */
		{
			gol_krali[gol_krali_sayisi].oyuncu = &oyuncu[k];
			gol_krali_sayisi++;
			istatistik.gol_krali_sayisi++;
		}
	}

	//oyuncu_sirala(); // Oyuncuları sıraladıktan sonra tekrar diziyi kaydedeceğiz.

	//printf(" ! --- !  ! --- ! ! --- ! ! --- !  \n");

	/* En çok gol atan bir oyuncuyu yakalayacağız */
	for (int k = 0; k < oyuncu_sayisi; k++)
	{
		//printf("%s %d %s  \n",
		//	oyuncu[k].oyuncu_on_ad,

		//	oyuncu[k].gol_sayisi,
		
		//	oyuncu[k].takim->takim_on_ad );
	}

	//printf("%d Gol kralı mevcut! \n",istatistik.gol_krali_sayisi );

	return 0;
}

/* Takımların maçlardaki performanslarına göre galibiyet ve malubiyetlerini yakalaylım ve puanlarını hesaplayalım */
int puan()
{
	/* Maç sayısını alalım */
	int mac_sayisi = istatistik.mac_sayisi;

	/* Maç sayısı */
	//printf("Maç sayısı :  %d \n",mac_sayisi );

	for (int i = 0; i < mac_sayisi; i++)
	{
		/* Maçların ev sahiplerini ve misafirlerini bulalım */
		//printf("%s - %s ( %d - %d )\n",mac[i].ev_sahibi->takim_on_ad,mac[i].misafir->takim_on_ad,mac[i].ev_sahibi_gol_sayisi,mac[i].misafir_gol_sayisi );

		/* Maçı ev sahibi takım kazandıysa onun kazanma hanesine +1 ekleyelim değilse malubiyet ekleyelim. */
		if(mac[i].ev_sahibi_gol_sayisi > mac[i].misafir_gol_sayisi) 
		{
			mac[i].ev_sahibi->galibiyet_sayisi++;
			mac[i].misafir->malubiyet_sayisi++;

			// Takımın puan hanesine 3 puan ekleyelim!
			mac[i].ev_sahibi->puan = mac[i].ev_sahibi->puan + 3;

		}
		else if(mac[i].ev_sahibi_gol_sayisi == mac[i].misafir_gol_sayisi) /* Berabere kalınan durumlarda! */
		{
			mac[i].ev_sahibi->beraberlik_sayisi++;
			mac[i].misafir->beraberlik_sayisi++;

			// Beraberlik durumunda her iki takımın hanesinede 1 er puan ekleyelim.
			mac[i].ev_sahibi->puan = mac[i].ev_sahibi->puan + 1;
			mac[i].misafir->puan = mac[i].misafir->puan + 1;

		}
		else
		{
			mac[i].misafir->galibiyet_sayisi++;
			mac[i].ev_sahibi->malubiyet_sayisi++;

			// Takımın puan hanesine 3 puan ekleyelim!
			mac[i].misafir->puan = mac[i].misafir->puan + 3;
		}
	}

	return 0;
}

/* Kendi kalesine en çok gol atan oyuncuyu bulacağız / Projede birden çok oyuncu bulunuz demediği için direkt olarak en çok atanı alacağız. */
int kendi_kalesine_gol_atan_oyuncu()
{
	int oyuncu_sayisi = istatistik.oyuncu_sayisi;
	int gol_sayisi = oyuncu[0].kendi_kalesine_gol_sayisi; // Gereksiz if'den kurtulduk.

	/* En çok gol atan bir oyuncuyu yakalayacağız */
	for (int i = 0; i < oyuncu_sayisi; i++)
	{
		if(gol_sayisi < oyuncu[i].kendi_kalesine_gol_sayisi)
		{
			gol_sayisi = oyuncu[i].kendi_kalesine_gol_sayisi; // Gol sayısı en fazla olanı bulduk.
		}
	}
	/* Kendi kalesine en çok gol atan oyuncuyu bulduk ve onu bu array içerisinden ayıklayıp istatistiklere kaydedeceğiz */

	for (int l = 0; l < oyuncu_sayisi; l++)
	{
		if(gol_sayisi == oyuncu[l].kendi_kalesine_gol_sayisi)
		{
			if(gol_sayisi != 0)
			{
				istatistik.kendi_kalesine_en_cok_atan_oyuncu = &oyuncu[l]; // İlişkimizi kurduk.
				printf("Kendi kalesine en çok gol atan oyuncu : %s %s \n",istatistik.kendi_kalesine_en_cok_atan_oyuncu->oyuncu_on_ad,istatistik.kendi_kalesine_en_cok_atan_oyuncu->oyuncu_son_ad );
			}
			else
			{
				printf("Kendi kalesine en çok gol atan oyuncu mevcut değildir\n.");
			}
		}
		
	}


	printf("\n");

	return 0;

}

/* Gol krallarını listeleyelim */
int gol_krallari()
{
	int gol_krali_sayisi = istatistik.gol_krali_sayisi;

	//printf("%d Gol kralı mevcut \n",gol_krali_sayisi );

	if(gol_krali_sayisi == 2)
	{
		for (int i = 0; i < gol_krali_sayisi; i++)
		{
			printf("%d gol ile %s %s gol krallığını %s %s ile paylaşıyor. \n",
				gol_krali[i].oyuncu->gol_sayisi,
				gol_krali[i].oyuncu->oyuncu_on_ad,
				gol_krali[i].oyuncu->oyuncu_son_ad,
				gol_krali[i+1].oyuncu->oyuncu_on_ad,
				gol_krali[i+1].oyuncu->oyuncu_son_ad
				);
		}
	}

	for (int i = 0; i < gol_krali_sayisi; i++)
	{
		printf("%d gol ile %s %s gol kralıdır. \n",gol_krali[i].oyuncu->gol_sayisi,gol_krali[i].oyuncu->oyuncu_on_ad,gol_krali[i].oyuncu->oyuncu_son_ad);
	}

    printf("\n");
	return 0;
}

int puan_tablosu() 
{
	/* Takım sayısını puan listesini dökmek için aldık */
	int takim_sayisi = istatistik.takim_sayisi;

	printf("Takım adı O G B M A Y P\n");

    /* Takımların puanlarını dökelim */
	for (int t = 0; t < takim_sayisi; t++)
	{
		printf("%s %s ",takim[t].takim_on_ad,takim[t].takim_son_ad );
		printf("%d ",takim[t].oynadigi_mac_sayisi );
		printf("%d ",takim[t].galibiyet_sayisi );
		printf("%d ",takim[t].beraberlik_sayisi );
		printf("%d ",takim[t].malubiyet_sayisi );
		printf("%d ",takim[t].atilan_gol_sayisi );
		printf("%d ",takim[t].yenilen_gol_sayisi );
		printf("%d \n",takim[t].puan );

	}

	puanlari_sirala(takim);

	printf("Puanların sıralı hali txt'ye kaydedildi..\n");

	/* Puanların sıralı halini txt'ye kaydedelim */

	FILE *dosya2;

	dosya2 = fopen("puandurumu.txt","w");   /* Dosya -> Yazılacak dosya */


	fprintf(dosya2,"Takım adı O G B M A Y P\n");

	/* Takımların puanlarını dökelim */
	for (int t = 0; t < takim_sayisi; t++)
	{
		fprintf(dosya2,"%s %s ",takim[t].takim_on_ad,takim[t].takim_son_ad );
		fprintf(dosya2,"%d ",takim[t].oynadigi_mac_sayisi );
		fprintf(dosya2,"%d ",takim[t].galibiyet_sayisi );
		fprintf(dosya2,"%d ",takim[t].beraberlik_sayisi );
		fprintf(dosya2,"%d ",takim[t].malubiyet_sayisi );
		fprintf(dosya2,"%d ",takim[t].atilan_gol_sayisi );
		fprintf(dosya2,"%d ",takim[t].yenilen_gol_sayisi );
		fprintf(dosya2,"%d \n",takim[t].puan );

	}

	printf("\n");

	return 0;
}

int devreler()
{
	//printf("Birinci devrede atılan gol sayısı : %d İkinci devrede atılan gol sayısı : %d  \n",istatistik.birinci_devrede_atilan_gol_sayisi,istatistik.ikinci_devrede_atilan_gol_sayisi );

	if(istatistik.birinci_devrede_atilan_gol_sayisi < istatistik.ikinci_devrede_atilan_gol_sayisi)
	{
		printf("En çok gol ikinci devrede atılmıştır \n");
	}
	else
	{
		printf("En çok gol birinci devrede atılmıştır \n");
	}

	printf("\n");
	return 0;
}

int hattrickYapanOyuncular() // Txt'ye yazacağız.
{

	FILE *dosya; /* Dosya -> Yazılacak dosya */

	dosya = fopen("hattricks.txt","w");   /* Dosya -> Yazılacak dosya */

	int hattrickYapanOyuncuSayisi = istatistik.hattrick_sayisi;

	for (int i = 0; i < hattrickYapanOyuncuSayisi; i++)
	{
		if(hattrick[i].mac->ev_sahibi_gol_sayisi > hattrick[i].mac->misafir_gol_sayisi ) // Ev sahibi kazandıysa
		{
			if(hattrick[i].oyuncu->takim->id == hattrick[i].mac->ev_sahibi->id) // Ve oyuncunun takımı kazandıysa.
			{
				fprintf(dosya,"%s %s adlı oyuncu %s %s (%d) - %s %s (%d) maçında  hattrick yapmıştır. Takımına kendi evinde zaferi getirmiştir! \n",
				hattrick[i].oyuncu->oyuncu_on_ad,
				hattrick[i].oyuncu->oyuncu_son_ad,
				hattrick[i].mac->ev_sahibi->takim_on_ad,
				hattrick[i].mac->ev_sahibi->takim_son_ad,
				hattrick[i].mac->ev_sahibi_gol_sayisi,

				hattrick[i].mac->misafir->takim_on_ad,
				hattrick[i].mac->misafir->takim_son_ad,
				hattrick[i].mac->misafir_gol_sayisi
				 );
			}
			else // Oyuncunun takımı yinede kaybettiyse.
			{
				fprintf(dosya,"%s %s adlı oyuncu %s %s (%d) - %s %s (%d) maçında hattrick yapmıştır. Takımı yinede kendi evinde malup olmuştur! \n",
				hattrick[i].oyuncu->oyuncu_on_ad,
				hattrick[i].oyuncu->oyuncu_son_ad,
				hattrick[i].mac->ev_sahibi->takim_on_ad,
				hattrick[i].mac->ev_sahibi->takim_son_ad,
				hattrick[i].mac->ev_sahibi_gol_sayisi,

				hattrick[i].mac->misafir->takim_on_ad,
				hattrick[i].mac->misafir->takim_son_ad,
				hattrick[i].mac->misafir_gol_sayisi
				 );
			}
		}
		else // Misafir kazandıysa
		{
			if(hattrick[i].oyuncu->takim->id == hattrick[i].mac->misafir->id) // Ve oyuncunun takımı kazandıysa.
			{
				fprintf(dosya,"%s %s adlı oyuncu %s %s (%d) - %s %s (%d) maçında  hattrick yapmıştır. Takımına deplasmanda zaferi getirmiştir!\n",
				hattrick[i].oyuncu->oyuncu_on_ad,
				hattrick[i].oyuncu->oyuncu_son_ad,
				hattrick[i].mac->ev_sahibi->takim_on_ad,
				hattrick[i].mac->ev_sahibi->takim_son_ad,
				hattrick[i].mac->ev_sahibi_gol_sayisi,

				hattrick[i].mac->misafir->takim_on_ad,
				hattrick[i].mac->misafir->takim_son_ad,
				hattrick[i].mac->misafir_gol_sayisi
				 );
			}
			else // Oyuncunun takımı yinede kaybettiyse.
			{
				fprintf(dosya,"%s %s adlı oyuncu %s %s (%d) - %s %s (%d) maçında  hattrick yapmıştır. Fakat takımı deplasmandan evine malubiyet ile geri dönmüştür. \n",
				hattrick[i].oyuncu->oyuncu_on_ad,
				hattrick[i].oyuncu->oyuncu_son_ad,
				hattrick[i].mac->ev_sahibi->takim_on_ad,
				hattrick[i].mac->ev_sahibi->takim_son_ad,
				hattrick[i].mac->ev_sahibi_gol_sayisi,

				hattrick[i].mac->misafir->takim_on_ad,
				hattrick[i].mac->misafir->takim_son_ad,
				hattrick[i].mac->misafir_gol_sayisi
				 );
			}
		}
		
	}
	printf("Dosyaya yazılmıştır..\n\n");

	return 0;
}

#endif /* listele_h */
